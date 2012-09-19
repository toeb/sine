
#include "GlWidget.h"

#include <QMouseEvent>
#include <iostream>
#include <QInputDialog>
using namespace std;
using namespace nspace;

QtInputHandler & GlWidget::inputHandler(){return _inputHandler;}

GlWidget::GlWidget(QWidget * parent)
  : QGLWidget(parent) 
	, _inputHandler(* new QtInputHandler())
  , captureTimer(0)
  , grabFrame(false)
  , capturing(false)
  , sequence(0)
{

  sequence= new vector<QImage>();
  setMouseTracking(true);
  renderTimer = new QTimer();
  timer = new QElapsedTimer();
  timer->start();
  setFocusPolicy(Qt::StrongFocus);
  captureTimer = new QTimer();
  setCaptureInterval(0.03);
	initMappings(_keyMap, _mouseButtonMap);
  
  connect(renderTimer,SIGNAL(timeout()),this,SLOT(updateGL()));
  connect(captureTimer,SIGNAL(timeout()),this,SLOT(captureOnce()));
}

bool GlWidget::initializeGlRenderEngine(){
	return true;
}
void GlWidget::cleanupGlRenderEngine(){
}

/**
 * \brief Gets the desired render interval.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \return The desired render interval.
 */
Time GlWidget::getDesiredRenderInterval(){
  return renderTimer->interval()/1000.0;
}

/**
 * \brief Gets the desired framerate.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \return The desired framerate.
 */
Real GlWidget::getDesiredFramerate(){
  return 1.0/getDesiredRenderInterval();
}

/**
 * \brief Sets the framerate by creating a dialog to query the user
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::setFramerate(){
   bool ok;
   double framerate = QInputDialog::getDouble(this,"Set frame rate","Enter desired framerate",getDesiredFramerate(),0.01,9999.0,3,&ok);
   setFramerate(framerate);
}

/**
 * \brief Sets the render interval.
 * 				sets the timeout intervall of the render timer to timeout*1000ms/s
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \param timeout The timeout.
 */
void GlWidget::setRenderInterval(Time timeout){
  renderTimer->setInterval(static_cast<int>(1000*timeout));
}

/**
 * \brief Sets the framerate.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \param framerate The framerate.
 */
void GlWidget::setFramerate(double framerate){
  setRenderInterval(1.0/framerate);
}

/**
 * \brief Gets the desired capture interval by querying the capture timer
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \return The desired capture interval.
 */
Time GlWidget::getDesiredCaptureInterval(){
  return captureTimer->interval()/1000.0;
}

/**
 * \brief Query if this object is rendering.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \return true if rendering, false if not.
 */
bool GlWidget::isRendering(){
  return rendering;
}

/**
 * \brief Starts rendering by starting hte rendertimer
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::startRendering(){
  rendering = true;
  renderTimer->start();
}

/**
 * \brief Stops rendering by stopping the render timer
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::stopRendering(){
  rendering = false;
  renderTimer->stop();
}

/**
 * \brief Sets rendering to true or false.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \param flag true to flag.
 */
void GlWidget::setRendering(bool flag){
  if(flag)startRendering();
  else stopRendering();
}

/**
 * \brief Toggles rendering.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::toggleRendering(){
  setRendering(!isRendering());
}

/**
 * \brief Sets the capture interval.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 *
 * \param timeout The timeout.
 */
void GlWidget::setCaptureInterval(Time timeout){
  captureTimer->setInterval(static_cast<int>(timeout*1000));
}
void GlWidget::captureOnce(){
  grabFrame = true;
}
void GlWidget::setCapturing(bool flag){
  if(flag == isCapturing())return;
  if(flag){
    startCapture();
  }else{
    stopCapture();
  }
}
void GlWidget::startCapture(){
  capturing=true;
  captureTimer->start();
}
void GlWidget::stopCapture(){
  capturing=false;
  captureTimer->stop();
}
void GlWidget::toggleCapture(){
  setCapturing(!isCapturing());
}

void GlWidget::initializeGL(){
	  
};

void GlWidget::resizeGL(int w, int h){
	resizeScene(w,h);
};

 /**
  * \brief renders the scene
  * 			 measures the elapsed time and passes it to the camera (which might need the elapsed time) (todo: make camera iintegratable)
  *        checks if screen needs to be captured
  * \author Tobias Becker
  * \date 05.04.2012
  */
 void GlWidget::paintGL(){   
   
  //measure elapsed time since last render call
  int elapsed = this->timer->elapsed();      
  //convert to seconds
  Time elapsedInSeconds = elapsed / 1000.0;
  //start measuring time for next render call
  timer->restart();

	RenderModule::render();

  //if capturing is turned on the this frame needs to be grabbed
  if(capturing)grabFrame = true;
  //if frame needs to be grabbed ...
  if(grabFrame){
    // ...set grabFrame to false...
    grabFrame = false;
    // ...and store the current frame 
    storeCurrentFrame();
  }
};

 /**
  * \brief Sets the capture interval by querying the user in a dialog
  *
  * \author Tobias Becker
  * \date 05.04.2012
  */
 void GlWidget::setCaptureInterval(){
   bool ok;
   double framerate = QInputDialog::getDouble(this,"Set Capture Rate","Enter desired framerate",getDesiredCaptureInterval(),0.01,100.0,3,&ok);
   setCaptureInterval(1/framerate);
 }

 /**
  * \brief Query if this object is capturing.
  *
  * \author Tobias Becker
  * \date 05.04.2012
  *
  * \return true if capturing, false if not.
  */
 bool GlWidget::isCapturing(){
   return capturing;
 }

/**
 * \brief Stores the current frame.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::storeCurrentFrame(){
  //gets the opengl framebuffer (afaik does not capture shader effects)
  const QImage & frame =grabFrameBuffer(true);
  //adds the image to the sequence vector
  sequence->push_back(frame);
}

/**
 * \brief Stores the sequence to a file
 * 				the format of the filename is queried. 
 * 				%1 is a wildcard replaced by the number of image in the sequence
 * 				%2 is a wildcard replaced by the total number of images in the sequence
 * 				the format used to store file is detected by qt interna.  see QImage documentation.
 * 				
 *    todo: add wildcards for time of capture, total frames captured, add helpfull text to dialog
  * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::storeSequence(){
  bool ok;
  QString filename = QInputDialog::getText(this,"Enter filename","Filename",QLineEdit::Normal,"capture_%1_of_%2.jpg",&ok);
  int i=0; 
  for(vector<QImage>::iterator it=sequence->begin(); it != sequence->end(); it++){
    //saves each qimage as a file.
    (*it).save(filename.arg(i++).arg(sequence->size()));
  }
}

/**
 * \brief Clears the sequence.
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
void GlWidget::clearSequence(){
  sequence->clear();
}



void GlWidget::keyPressEvent(QKeyEvent* ke){
  Qt::Key key = static_cast<Qt::Key>(ke->key());
	if(_keyMap.mappingExists(key)){
    _inputHandler.onKeyDown(_keyMap(key));
	}else{
		_inputHandler.onKeyDown(nspace::KEY_UNKNOWN);
	}
};

void GlWidget::keyReleaseEvent(QKeyEvent* ke){
	Qt::Key key = static_cast<Qt::Key>(ke->key());
	if(_keyMap.mappingExists(key)){
		_inputHandler.onKeyUp(_keyMap(key));
	}else{
		_inputHandler.onKeyUp(nspace::KEY_UNKNOWN);
	}
};

void GlWidget::mouseMoveEvent(QMouseEvent* me){
	inputHandler().onMouseMove(me->pos().x(), me->pos().y());
};

void GlWidget::mousePressEvent(QMouseEvent* me){
 	if(_mouseButtonMap.mappingExists(me->button())){
		_inputHandler.onMouseButtonDown(_mouseButtonMap(me->button()));
	}else{
		_inputHandler.onMouseButtonDown(nspace::BUTTON_UNKNOWN);
	}
};

void GlWidget::mouseReleaseEvent(QMouseEvent* me){
	if(_mouseButtonMap.mappingExists(me->button())){
		_inputHandler.onMouseButtonUp(_mouseButtonMap(me->button()));
	}else{
		_inputHandler.onMouseButtonUp(nspace::BUTTON_UNKNOWN);
	}
};
 
void GlWidget::initMappings(PairMap<Qt::Key, nspace::Keys> & keyMap, PairMap<Qt::MouseButton, nspace::MouseButtons> & mouseButtonMap){
	mouseButtonMap.addMapping(Qt::LeftButton,  nspace::BUTTON_LEFT);
	mouseButtonMap.addMapping(Qt::RightButton, nspace::BUTTON_RIGHT);
	mouseButtonMap.addMapping(Qt::MiddleButton,nspace::BUTTON_MIDDLE);

  keyMap.addMapping(Qt::Key_0, nspace::KEY_0);
  keyMap.addMapping(Qt::Key_1, nspace::KEY_1);
  keyMap.addMapping(Qt::Key_2, nspace::KEY_2);
  keyMap.addMapping(Qt::Key_3, nspace::KEY_3);
  keyMap.addMapping(Qt::Key_4, nspace::KEY_4);
  keyMap.addMapping(Qt::Key_5, nspace::KEY_5);
  keyMap.addMapping(Qt::Key_6, nspace::KEY_6);
  keyMap.addMapping(Qt::Key_7, nspace::KEY_7);
  keyMap.addMapping(Qt::Key_8, nspace::KEY_8);
  keyMap.addMapping(Qt::Key_9, nspace::KEY_9);
  keyMap.addMapping(Qt::Key_A, nspace::KEY_A);
  keyMap.addMapping(Qt::Key_B, nspace::KEY_B);
  keyMap.addMapping(Qt::Key_C, nspace::KEY_C);
  keyMap.addMapping(Qt::Key_D, nspace::KEY_D);
  keyMap.addMapping(Qt::Key_E, nspace::KEY_E);
  keyMap.addMapping(Qt::Key_F, nspace::KEY_F);
  keyMap.addMapping(Qt::Key_G, nspace::KEY_G);
  keyMap.addMapping(Qt::Key_H, nspace::KEY_H);
  keyMap.addMapping(Qt::Key_I, nspace::KEY_I);
  keyMap.addMapping(Qt::Key_J, nspace::KEY_J);
  keyMap.addMapping(Qt::Key_K, nspace::KEY_K);
  keyMap.addMapping(Qt::Key_L, nspace::KEY_L);
  keyMap.addMapping(Qt::Key_M, nspace::KEY_M);
  keyMap.addMapping(Qt::Key_N, nspace::KEY_N);
  keyMap.addMapping(Qt::Key_O, nspace::KEY_O);
  keyMap.addMapping(Qt::Key_P, nspace::KEY_P);
  keyMap.addMapping(Qt::Key_Q, nspace::KEY_Q);
  keyMap.addMapping(Qt::Key_R, nspace::KEY_R);
  keyMap.addMapping(Qt::Key_S, nspace::KEY_S);
  keyMap.addMapping(Qt::Key_T, nspace::KEY_T);
  keyMap.addMapping(Qt::Key_U, nspace::KEY_U);
  keyMap.addMapping(Qt::Key_V, nspace::KEY_V);
  keyMap.addMapping(Qt::Key_W, nspace::KEY_W);
  keyMap.addMapping(Qt::Key_X, nspace::KEY_X);
  keyMap.addMapping(Qt::Key_Y, nspace::KEY_Y);
  keyMap.addMapping(Qt::Key_Z, nspace::KEY_Z);
	
  keyMap.addMapping(Qt::Key_Space				, nspace::KEY_SPACE																		);
  keyMap.addMapping(Qt::Key_Tab					, nspace::KEY_TAB																		);
  keyMap.addMapping(Qt::Key_Enter				, nspace::KEY_ENTER																		);
  keyMap.addMapping(Qt::Key_F1  				, nspace::KEY_F1       																		);
  keyMap.addMapping(Qt::Key_F2  				, nspace::KEY_F2       																		);
  keyMap.addMapping(Qt::Key_F3  				, nspace::KEY_F3       																		);
  keyMap.addMapping(Qt::Key_F4  				, nspace::KEY_F4       																		);
  keyMap.addMapping(Qt::Key_F5  				, nspace::KEY_F5       																		);
  keyMap.addMapping(Qt::Key_F6  				, nspace::KEY_F6       																		);
  keyMap.addMapping(Qt::Key_F7  				, nspace::KEY_F7       																		);
  keyMap.addMapping(Qt::Key_F8  				, nspace::KEY_F8       																		);
  keyMap.addMapping(Qt::Key_F9  				, nspace::KEY_F9       																		);
  keyMap.addMapping(Qt::Key_F10					, nspace::KEY_F10      																		);
  keyMap.addMapping(Qt::Key_F11					, nspace::KEY_F11      																		);
  keyMap.addMapping(Qt::Key_F12 				, nspace::KEY_F12      																		);
  keyMap.addMapping(Qt::Key_Left				, nspace::KEY_LEFT     																		);
  keyMap.addMapping(Qt::Key_Up					, nspace::KEY_UP       																		);
  keyMap.addMapping(Qt::Key_Right				, nspace::KEY_RIGHT    																		);
  keyMap.addMapping(Qt::Key_Down				, nspace::KEY_DOWN     																		);
  keyMap.addMapping(Qt::Key_PageUp			, nspace::KEY_PAGE_UP  																		);
  keyMap.addMapping(Qt::Key_PageDown		, nspace::KEY_PAGE_DOWN																		);
  keyMap.addMapping(Qt::Key_Home				, nspace::KEY_HOME     																		);
  keyMap.addMapping(Qt::Key_End					, nspace::KEY_END      																		);
  keyMap.addMapping(Qt::Key_Insert			, nspace::KEY_INSERT   																		);
  keyMap.addMapping(Qt::Key_NumLock			, nspace::KEY_NUM_LOCK 																		);
  keyMap.addMapping(Qt::Key_Home				, nspace::KEY_BEGIN 																		);
  keyMap.addMapping(Qt::Key_Delete			, nspace::KEY_DELETE   																		);
  keyMap.addMapping(Qt::Key_Control			, nspace::KEY_CTRL																		);
  keyMap.addMapping(Qt::Key_Alt					, nspace::KEY_ALT																		);
  keyMap.addMapping(Qt::Key_Shift				, nspace::KEY_SHIFT																		);
  keyMap.addMapping(Qt::Key_Period			, nspace::KEY_PERIOD																		);
  keyMap.addMapping(Qt::Key_Backspace		, nspace::KEY_BACKSPACE																		);
}