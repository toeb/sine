#pragma once
#include <application.sample.h>
#include <core.hub.h>
#include <application.qt.h>
#include <core.initialization.h>
#include <visualization.opengl.qt.h>
#include <visualization.h>
#include <visualization.opengl.renderer.h>
#include <simulation.runner.qt/QtTaskRunner.h>
#include <visualization/Material.h>
#include <simulation.runner.qt/QtTimeControlPlugin.h>
#include <simulation.time.h>
#include <simulation.integration/IntegratingSystem.h>
#include <simulation.integration/implementations/RungeKutta4.h>
#include <simulation.runner.qt/QtPropertyView.h>
#include <application.qt.objectview.h>

namespace nspace{
  class SampleApplication : public virtual NamedObject, public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(SampleApplication);
  public:
    PROPERTY(SkyboxRenderer * ,Skybox){cancel = true;}
    PROPERTY(ViewportController * ,Camera){cancel = true;}
    PROPERTY(std::string  ,ResourceDirectory){}
    PROPERTY(SimulationTimeProvider * ,SimulationTimeProvider){cancel = true;}
    PROPERTY(ObjectViewPlugin * ,ObjectViewPlugin){cancel = true;}
    PROPERTY(QtPropertyView * ,QtPropertyView){cancel = true;}
    PROPERTY(ViewportPlugin * ,ViewportPlugin){cancel = true;}
    PROPERTY(InitializationModule * ,Initializer){cancel = true;}
    PROPERTY(Hub * ,Hub){cancel = true;}
    PROPERTY(PluginApplication * ,Application){cancel = true;}
    PROPERTY(GlViewport * ,Viewport){cancel = true;}
    PROPERTY(RenderSet * ,RenderSet){cancel = true;}
    PROPERTY(QtTaskRunner * ,QtTaskRunner){cancel = true;}
    PROPERTY(QtTimeControlPlugin * ,QtTimeControlPlugin){cancel = true;}
    PROPERTY(DefaultLightSetup * ,DefaultLightSetup){cancel = true;}
    PROPERTY(SimulationTimeController * ,SimulationTimeController){cancel = true;}
    PROPERTY(Simulation * ,Simulation){cancel = true;}
    PROPERTY(StepIntegrator * ,Integrator){cancel = true;}
    PROPERTY(GridRenderer * ,Grid){cancel = true;}

  public:
    SampleApplication(int argc, char ** argv, Sample & sample, const std::string & resourceDirectory = ".");
    Hub & hub();
    void setup();
    int run();
    void printSetup();
    void printHierarchy();
  private:
    Sample & _sample;
  };
}
