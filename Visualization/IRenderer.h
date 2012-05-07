#pragma once
namespace IBDS{
class IRenderer{
public:
  
  virtual void render()=0;
  virtual void initializeRenderer()=0;
  virtual void cleanupRenderer()=0;
};
}
