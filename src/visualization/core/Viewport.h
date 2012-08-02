#pragma once
#include <simulation/core/ISimulationObject.h>
#include <simulation/kinematics/CoordinateSystem.h>
namespace nspace{
class Viewport : virtual public ISimulationObject{
private:
	int _width;
	int _height;
public:
	Real aspectRatio()const {
		return (Real)_width / (Real)_height;
	}
	Viewport():_width(1),_height(1){
    setName("Viewport");
	}
	void resize(int width, int height){
		if(width <=0)width = 1;
		if(height <= 0)height=1;
		
		if(_width==width && _height == height){
			return;
		}
		_width = width;
		_height = height;
		onResize(width,height);
	}
	const int & width(){return _width;}
	const int & height(){return _height;}
  virtual void viewport()=0;
protected:
	virtual void onResize(int newWidth, int newHeight){}
};

class ViewportBase : public virtual Viewport{
private:
	CoordinateSystem _coordinates;
	Real _fieldOfViewAngle;
	Real _nearCutOffPlane;
	Real _farCutOffPlane;
	Real _zoomFactor;
public:
	ViewportBase():_fieldOfViewAngle(M_PI/ 4), _nearCutOffPlane(0.1),_farCutOffPlane(100.0), _zoomFactor(1.0){}
	inline CoordinateSystem & coordinates(){return _coordinates;}
	inline Real & fieldOfViewAngle(){return _fieldOfViewAngle;}
	inline Real & nearCutOffPlane(){return _nearCutOffPlane;}
	inline Real & farCutOffPlane(){return _farCutOffPlane;}
	inline Real & zoomFactor(){return _zoomFactor;}

};
}