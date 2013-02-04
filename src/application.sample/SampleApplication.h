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
  /*class SkyboxRenderer;
  class ViewportController;
  class SimulationTimeProvider;*/

  class SampleApplication : public virtual NamedObject, public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(SampleApplication);
  public:
    PROPERTY(SkyboxRenderer * ,Skybox);
    PROPERTY(ViewportController * ,Camera);
    PROPERTY(std::string  ,ResourceDirectory);
    PROPERTY(SimulationTimeProvider * ,SimulationTimeProvider);
    PROPERTY(ObjectViewPlugin * ,ObjectViewPlugin);
    PROPERTY(QtPropertyView * ,QtPropertyView);
    PROPERTY(ViewportPlugin * ,ViewportPlugin);
    PROPERTY(InitializationModule * ,Initializer);
    PROPERTY(Hub * ,Hub);
    PROPERTY(PluginApplication * ,Application);
    PROPERTY(GlViewport * ,Viewport);
    PROPERTY(RenderSet * ,RenderSet);
    PROPERTY(QtTaskRunner * ,QtTaskRunner);
    PROPERTY(QtTimeControlPlugin * ,QtTimeControlPlugin);
    PROPERTY(DefaultLightSetup * ,DefaultLightSetup);
    PROPERTY(SimulationTimeController * ,SimulationTimeController);
    PROPERTY(Simulation * ,Simulation);
    PROPERTY(StepIntegrator * ,Integrator);
    PROPERTY(GridRenderer * ,Grid);

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
