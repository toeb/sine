#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <simulation/core/SimulationModuleBase.h>
#include <simulation/interaction/Keys.h>
#include <math/definitions.h>
#include <simulation/interaction/IInputListener.h>
namespace nspace{

class InputHandler:public SimulationModuleBase<IInputListener>{
private:
    bool _keysDown[MAX_KEYS];
    bool _mouseButtonsDown[MAX_MOUSE_BUTTONS];
		int _mouseX;
    int _mouseY;
    Real _mouseWheel;
public:    
	InputHandler();

    bool isAnyKeyDown(){
      for(int i=0; i <MAX_KEYS;i++ ){
        if(_keysDown[i])return true;
      }
      return false;
    }
		bool operator ()(MouseButtons button){
			return isMouseButtonDown(button);
		}
		bool operator()(Keys key){
			return isKeyDown(key);
		}

    virtual bool isMouseButtonDown(MouseButtons b){
			return _mouseButtonsDown[b];
		};
    virtual bool isKeyDown(Keys key){
			return _keysDown[key];
		};
		
		virtual int mouseX(){return _mouseX;}
		virtual int mouseY(){return _mouseY;}
		virtual Real mouseWheel(){return _mouseWheel;}

		void onMouseMove(int x, int y);
		void onMouseButtonDown(MouseButtons b);
		void onKeyDown(Keys key);
		void onKeyUp(Keys key);
		void onMouseButtonUp(MouseButtons b);
		void onMouseWheelMove(Real p);
protected:
	void onObjectAdded(IInputListener * obj){
		obj->setInputHandler(this);
	}
  };

template< typename K1, typename K2 >
class PairMap{
private:
	std::map<K1,K2> m12;
	std::map<K2,K1> m21;
public:
	bool mappingExists(K1 k){
		auto it = m12.find(k);
		if(it == m12.end())return false;
		return true;
	}
	bool mappingExists(K2 k){
		auto it = m21.find(k);
		if(it == m21.end())return false;
		return true;
	}
	K1 operator()(K2 k){
		return m21[k];
	}
	
	K2 operator()(K1 k){
		return m12[k];
	}
	void addMapping(K1 k1,K2 k2){
		m12[k1] = k2;
		m21[k2] = k1;
	}
};
}