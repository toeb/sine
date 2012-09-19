#pragma once
#include <vector>
#include <algorithm>
#include <simulation/ISimulationModule.h>

#define MAX_KEYS 256
#define MAX_MOUSE_BUTTONS 3

namespace nspace{
	
  enum MouseButtons{
    BUTTON_UNKNOWN=99,
    BUTTON_LEFT=0,
    BUTTON_RIGHT=1,
    BUTTON_MIDDLE=2
  };
  enum Keys{
    KEY_UNKNOWN,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SPACE,
    KEY_TAB,
    KEY_ENTER,
    KEY_F1       ,
    KEY_F2       ,
    KEY_F3       ,
    KEY_F4       ,
    KEY_F5       ,
    KEY_F6       ,
    KEY_F7       ,
    KEY_F8       ,
    KEY_F9       ,
    KEY_F10      ,
    KEY_F11      ,
    KEY_F12      ,
    KEY_LEFT     ,
    KEY_UP       ,
    KEY_RIGHT    ,
    KEY_DOWN     ,
    KEY_PAGE_UP  ,
    KEY_PAGE_DOWN,
    KEY_HOME     ,
    KEY_END      ,
    KEY_INSERT   ,
    KEY_NUM_LOCK ,
    KEY_BEGIN    ,
    KEY_DELETE   ,
    KEY_CTRL,
    KEY_ALT,
    KEY_SHIFT,
    KEY_PERIOD,
    KEY_BACKSPACE
  };


}
