/*
 * Copyright (C) 2011
 * Simulation, Systems Optimization and Robotics Group (SIM)
 * Technische Universitaet Darmstadt
 * Hochschulstr. 10
 * 64289 Darmstadt, Germany
 * www.sim.tu-darmstadt.de
 *
 * This file is part of the mbslib.
 * All rights are reserved by the copyright holder.
 *
 * The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You may use the mbslib or parts of it only with the written permission of the copyright holder.
 * You may NOT modify or redistribute any part of the mbslib without the prior written
 * permission by the copyright holder.
 *
 * Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
 * Any expenses associated with the prosecution will be charged against the violator.
 */

/**
 * \file src/vis/qt_model_viewer/GlWidget.h
 * 
 */
#pragma once

#include <QGLWidget>
#include <QElapsedTimer>
#include <QTimer>

#include <visualization.opengl/OpenGLRenderModule.h>
#include <simulation.interaction/InputHandler.h>

#include <map>

namespace nspace{
	class QtInputHandler : public InputHandler{
	public:
		
	};
  /**
   * \brief The Gl widget
   * 				
   * 				Can capture screen shots
   * 				Can capture sequences at specific rates
   * 				has variable framerate which can be set
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
class GlWidget :public QGLWidget, public OpenGLRenderModule{
   Q_OBJECT
private:
	QtInputHandler & _inputHandler;
	PairMap<Qt::Key, nspace::Keys> _keyMap;
	PairMap<Qt::MouseButton, nspace::MouseButtons> _mouseButtonMap;
public:

	QtInputHandler  & inputHandler();
  /**
   * \brief Constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param [in,out] parent   If non-null, the parent.
   */
  GlWidget(QWidget * parent);

  /**
   * \brief Gets the capture interval.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return The capture interval.
   */
  Time getDesiredCaptureInterval();

  /**
   * \brief Gets the render interval.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return The render interval.
   */
  Time getDesiredRenderInterval();  

  /**
   * \brief Query if this object is capturing.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return true if capturing, false if not.
   */
  bool isCapturing();

  /**
   * \brief Gets the desired framerate.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return The desired framerate.
   */
  Real getDesiredFramerate();

  /**
   * \brief Query if this object is rendering.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return true if rendering, false if not.
   */
  bool isRendering();
public slots:

  /**
   * \brief Toggles image capturing.
   * 				images are stored in a vector.
   * 				Memory Consumption is proportionally high
   * 				
   * 				Sequence can be stored with storeSequece or cleared with clearSequence.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void toggleCapture();

  /**
   * \brief Starts capturing.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void startCapture();

  /**
   * \brief Stops capturing.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void stopCapture();

  /**
   * \brief Sets capturing to on or off.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param capture true to capture.
   */
  void setCapturing(bool capture);

  /**
   * \brief Sets the capture interval.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void setCaptureInterval();

  /**
   * \brief Stores the sequence.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void storeSequence();

  /**
   * \brief Clears the captured sequence.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void clearSequence();

  /**
   * \brief Captures the next frame.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void captureOnce();

  /**
   * \brief Sets the capture interval.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param timeout The timeout.
   */
  void setCaptureInterval(Time timeout);

  /**
   * \brief Sets the desired framerate via an input dialog.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void setFramerate();

  /**
   * \brief Sets the desired framerate.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param desiredFramerate The desired framerate.
   */
  void setFramerate(double desiredFramerate);

  /**
   * \brief Sets the render interval causing rendering to be called when the interval has passed. 
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param timeout The timeout.
   */
  void setRenderInterval(Time timeout);

  /**
   * \brief Sets rendering to on or off.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param flag true to flag.
   */
  void setRendering(bool flag);

  /**
   * \brief Starts rendering.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void startRendering();

  /**
   * \brief Stops rendering.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void stopRendering();

  /**
   * \brief Toggles rendering.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void toggleRendering();

protected:
	//members of RenderEngine
  virtual bool initializeGlRenderEngine();
  virtual void cleanupGlRenderEngine();
  
	// input event interceptors
  virtual void keyPressEvent(QKeyEvent* ke);
  virtual void keyReleaseEvent(QKeyEvent* ke);
  virtual void mouseMoveEvent(QMouseEvent* me);
  virtual void mousePressEvent(QMouseEvent* me);
  virtual void mouseReleaseEvent(QMouseEvent* me);

  /**
   * \brief Initializes the opengl framework.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  virtual void initializeGL();

  /**
   * \brief Resizes opengl viewport
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param w The width.
   * \param h The height.
   */
  virtual void resizeGL(int w, int h);

  /**
   * \brief renders the scene.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  virtual void paintGL();



private:
  /**
   * \brief Stores the current frame in the sequence vector
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void storeCurrentFrame();

	void initMappings(PairMap<Qt::Key, nspace::Keys> & keymap, PairMap<Qt::MouseButton, nspace::MouseButtons> & mousebuttonMap);

  ///< The captured sequence
  std::vector<QImage> * sequence;
  ///< The capture timeout
  Time captureTimeout;
  ///< The capture timer
  QTimer * captureTimer;
  ///< The render timer
  QTimer * renderTimer;
  ///< true if rendering
  bool rendering;
  ///< true to next grab frame
  bool grabFrame;
  ///< true if capturing
  bool capturing;
  ///< The elapsed timer used for measuring (the framerate)
  QElapsedTimer * timer;
	
};//namespace GlWidget
};//namespace mbslib
