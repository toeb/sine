#include "QtInputHandler.h"

using namespace nspace;

void QtInputHandler::keyPressEvent(QKeyEvent* ke){
  Qt::Key key = static_cast<Qt::Key>(ke->key());
  if(_keys.mappingExists(key)){
    onKeyDown(_keys(key));
  }else{
    onKeyDown(nspace::KEY_UNKNOWN);
  }
};

void QtInputHandler::keyReleaseEvent(QKeyEvent* ke){
  Qt::Key key = static_cast<Qt::Key>(ke->key());
  if(_keys.mappingExists(key)){
    onKeyUp(_keys(key));
  }else{
    onKeyUp(nspace::KEY_UNKNOWN);
  }
};

void QtInputHandler::mouseMoveEvent(QMouseEvent* me){
  onMouseMove(me->pos().x(), me->pos().y());
};

void QtInputHandler::mousePressEvent(QMouseEvent* me){
  if(_buttons.mappingExists(me->button())){
    onMouseButtonDown(_buttons(me->button()));
  }else{
    onMouseButtonDown(nspace::BUTTON_UNKNOWN);
  }
};

void QtInputHandler::mouseReleaseEvent(QMouseEvent* me){
  if(_buttons.mappingExists(me->button())){
    onMouseButtonUp(_buttons(me->button()));
  }else{
    onMouseButtonUp(nspace::BUTTON_UNKNOWN);
  }
};

QtInputHandler::QtInputHandler(){
  setName("QtInputHandler");
  logInfo("Creating Inputhandler");
  _buttons.addMapping(Qt::LeftButton,  nspace::BUTTON_LEFT);
  _buttons.addMapping(Qt::RightButton, nspace::BUTTON_RIGHT);
  _buttons.addMapping(Qt::MiddleButton,nspace::BUTTON_MIDDLE);

  _keys.addMapping(Qt::Key_0, nspace::KEY_0);
  _keys.addMapping(Qt::Key_1, nspace::KEY_1);
  _keys.addMapping(Qt::Key_2, nspace::KEY_2);
  _keys.addMapping(Qt::Key_3, nspace::KEY_3);
  _keys.addMapping(Qt::Key_4, nspace::KEY_4);
  _keys.addMapping(Qt::Key_5, nspace::KEY_5);
  _keys.addMapping(Qt::Key_6, nspace::KEY_6);
  _keys.addMapping(Qt::Key_7, nspace::KEY_7);
  _keys.addMapping(Qt::Key_8, nspace::KEY_8);
  _keys.addMapping(Qt::Key_9, nspace::KEY_9);
  _keys.addMapping(Qt::Key_A, nspace::KEY_A);
  _keys.addMapping(Qt::Key_B, nspace::KEY_B);
  _keys.addMapping(Qt::Key_C, nspace::KEY_C);
  _keys.addMapping(Qt::Key_D, nspace::KEY_D);
  _keys.addMapping(Qt::Key_E, nspace::KEY_E);
  _keys.addMapping(Qt::Key_F, nspace::KEY_F);
  _keys.addMapping(Qt::Key_G, nspace::KEY_G);
  _keys.addMapping(Qt::Key_H, nspace::KEY_H);
  _keys.addMapping(Qt::Key_I, nspace::KEY_I);
  _keys.addMapping(Qt::Key_J, nspace::KEY_J);
  _keys.addMapping(Qt::Key_K, nspace::KEY_K);
  _keys.addMapping(Qt::Key_L, nspace::KEY_L);
  _keys.addMapping(Qt::Key_M, nspace::KEY_M);
  _keys.addMapping(Qt::Key_N, nspace::KEY_N);
  _keys.addMapping(Qt::Key_O, nspace::KEY_O);
  _keys.addMapping(Qt::Key_P, nspace::KEY_P);
  _keys.addMapping(Qt::Key_Q, nspace::KEY_Q);
  _keys.addMapping(Qt::Key_R, nspace::KEY_R);
  _keys.addMapping(Qt::Key_S, nspace::KEY_S);
  _keys.addMapping(Qt::Key_T, nspace::KEY_T);
  _keys.addMapping(Qt::Key_U, nspace::KEY_U);
  _keys.addMapping(Qt::Key_V, nspace::KEY_V);
  _keys.addMapping(Qt::Key_W, nspace::KEY_W);
  _keys.addMapping(Qt::Key_X, nspace::KEY_X);
  _keys.addMapping(Qt::Key_Y, nspace::KEY_Y);
  _keys.addMapping(Qt::Key_Z, nspace::KEY_Z);
  _keys.addMapping(Qt::Key_Space				, nspace::KEY_SPACE			);
  _keys.addMapping(Qt::Key_Tab					, nspace::KEY_TAB			  );
  _keys.addMapping(Qt::Key_Enter				, nspace::KEY_ENTER			);
  _keys.addMapping(Qt::Key_F1  				  , nspace::KEY_F1      	);
  _keys.addMapping(Qt::Key_F2  				  , nspace::KEY_F2      	);
  _keys.addMapping(Qt::Key_F3  				  , nspace::KEY_F3      	);
  _keys.addMapping(Qt::Key_F4  				  , nspace::KEY_F4      	);
  _keys.addMapping(Qt::Key_F5  				  , nspace::KEY_F5      	);
  _keys.addMapping(Qt::Key_F6  			  	, nspace::KEY_F6      	);
  _keys.addMapping(Qt::Key_F7  			  	, nspace::KEY_F7      	);
  _keys.addMapping(Qt::Key_F8  			  	, nspace::KEY_F8      	);
  _keys.addMapping(Qt::Key_F9  			  	, nspace::KEY_F9      	);
  _keys.addMapping(Qt::Key_F10					, nspace::KEY_F10     	);
  _keys.addMapping(Qt::Key_F11					, nspace::KEY_F11     	);
  _keys.addMapping(Qt::Key_F12 			  	, nspace::KEY_F12     	);
  _keys.addMapping(Qt::Key_Left			  	, nspace::KEY_LEFT    	);
  _keys.addMapping(Qt::Key_Up				  	, nspace::KEY_UP      	);
  _keys.addMapping(Qt::Key_Right				, nspace::KEY_RIGHT   	);
  _keys.addMapping(Qt::Key_Down			  	, nspace::KEY_DOWN    	);
  _keys.addMapping(Qt::Key_PageUp		  	, nspace::KEY_PAGE_UP 	);
  _keys.addMapping(Qt::Key_PageDown		  , nspace::KEY_PAGE_DOWN	);
  _keys.addMapping(Qt::Key_Home			  	, nspace::KEY_HOME    	);
  _keys.addMapping(Qt::Key_End					, nspace::KEY_END     	);
  _keys.addMapping(Qt::Key_Insert			  , nspace::KEY_INSERT  	);
  _keys.addMapping(Qt::Key_NumLock			, nspace::KEY_NUM_LOCK	);
  _keys.addMapping(Qt::Key_Home				  , nspace::KEY_BEGIN 		);
  _keys.addMapping(Qt::Key_Delete		  	, nspace::KEY_DELETE  	);
  _keys.addMapping(Qt::Key_Control			, nspace::KEY_CTRL			);
  _keys.addMapping(Qt::Key_Alt					, nspace::KEY_ALT			  );
  _keys.addMapping(Qt::Key_Shift				, nspace::KEY_SHIFT			);
  _keys.addMapping(Qt::Key_Period			  , nspace::KEY_PERIOD		);
  _keys.addMapping(Qt::Key_Backspace		, nspace::KEY_BACKSPACE	);
}