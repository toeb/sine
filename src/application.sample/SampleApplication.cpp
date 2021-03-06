#include "SampleApplication.h"
#include <iostream>
using namespace std;
using namespace nspace;


void SampleApplication::propertyChanging(std::string  ,ResourceDirectory){}
void SampleApplication::propertyChanging(SkyboxRenderer * ,Skybox){cancel = true;}
void SampleApplication::propertyChanging(ViewportController * ,Camera){cancel = true;}
void SampleApplication::propertyChanging(SimulationTimeProvider * ,SimulationTimeProvider){cancel = true;}
void SampleApplication::propertyChanging(ObjectViewPlugin * ,ObjectViewPlugin){cancel = true;}
void SampleApplication::propertyChanging(QtPropertyView * ,QtPropertyView){cancel = true;}
void SampleApplication::propertyChanging(ViewportPlugin * ,ViewportPlugin){cancel = true;}
void SampleApplication::propertyChanging(InitializationModule * ,Initializer){cancel = true;}
void SampleApplication::propertyChanging(Hub * ,Hub){cancel = true;}
void SampleApplication::propertyChanging(PluginApplication * ,Application){cancel = true;}
void SampleApplication::propertyChanging(GlViewport * ,Viewport){cancel = true;}
void SampleApplication::propertyChanging(RenderSet * ,RenderSet){cancel = true;}
void SampleApplication::propertyChanging(QtTaskRunner * ,QtTaskRunner){cancel = true;}
void SampleApplication::propertyChanging(QtTimeControlPlugin * ,QtTimeControlPlugin){cancel = true;}
void SampleApplication::propertyChanging(DefaultLightSetup * ,DefaultLightSetup){cancel = true;}
void SampleApplication::propertyChanging(SimulationTimeController * ,SimulationTimeController){cancel = true;}
void SampleApplication::propertyChanging(Simulation * ,Simulation){cancel = true;}
void SampleApplication::propertyChanging(StepIntegrator * ,Integrator){cancel = true;}
void SampleApplication::propertyChanging(GridRenderer * ,Grid){cancel = true;}

SampleApplication::SampleApplication(int argc, char ** argv, Sample & sample, const std::string & resourceDirectory):
  _Skybox(0),
  _Camera(0),
  _ResourceDirectory(resourceDirectory),
  _SimulationTimeProvider(0),
  _ObjectViewPlugin(0),
  _QtPropertyView(0),
  _ViewportPlugin(0),
  _Initializer(0),
  _Hub(0),
  _Application(0),
  _Viewport(0),
  _RenderSet(0),
  _QtTaskRunner(0),
  _QtTimeControlPlugin(0),
  _DefaultLightSetup(0),
  _SimulationTimeController(0),
  _Simulation(0),
  _Integrator(0),
  _Grid(0),
  _sample(sample)
{
  Color::loadColors(resourceDirectory+"/colors/palette.txt");
  Material::loadMaterials(resourceDirectory+"/materials/palette.txt");

  _Application = new PluginApplication(argc,argv);
  _sample.setApplication(*this);
  setName("SampleApplication");

  getApplication()->setName("Sample Application");

  _Integrator=new RungeKutta4(0.05);
  _SimulationTimeProvider = new SimulationTimeProvider();
  _SimulationTimeController=new SimulationTimeController(*getSimulationTimeProvider(),false);

  _Skybox = new SkyboxRenderer();
  _Camera = new FpsViewportController();
  _ObjectViewPlugin = new ObjectViewPlugin();
  _QtPropertyView = new QtPropertyView();
  _ViewportPlugin = new ViewportPlugin();
  _Initializer = new InitializationModule();
  _Hub = new Hub();
  _Viewport = new GlViewport();
  _RenderSet = new RenderSet();
  _QtTaskRunner = new QtTaskRunner();
  _QtTimeControlPlugin = new QtTimeControlPlugin();
  _Grid = new GridRenderer();
  _DefaultLightSetup = new DefaultLightSetup();
  _Simulation =  new Simulation();
}

void SampleApplication::printSetup(){
  hub().foreachElement([](Object* o){
    cout << o << endl;
  });
}
void SampleApplication::printHierarchy(){
  hub().successorsToStream(cout);
}

void SampleApplication::setup(){
  getViewport()->setName("Default View");

  getViewportPlugin()->setName("Visualization Window");

  getGrid()->GridMaterial() = Color("LightGrey");
  getGrid()->setSections(50);
  getGrid()->Coordinates().position().y()=-5;
  getGrid()->setWidth(100);
  getGrid()->setHeight(100);

  getSkybox()->setFileBase(getResourceDirectory()+"/images/sky");

  getQtTimeControlPlugin()->setTimeController(getSimulationTimeController());

  hub()|=getSimulation();
  hub()|=getIntegrator();
  hub()|=getSimulationTimeProvider();
  hub()|=getSimulationTimeController();
  hub()|=getQtTimeControlPlugin();
  hub()|=getGrid();
  hub()|=getSkybox();
  hub()|=getApplication();
  hub()|=getInitializer();
  hub()|=getViewportPlugin();
  hub()|=getCamera();
  hub()|=getDefaultLightSetup();
  hub()|=getViewport();
  hub()|=getQtTaskRunner();
  hub()|=getRenderSet();
  hub()|=&_sample;
  hub()|=getObjectViewPlugin();
  hub()|=getQtPropertyView();

  getViewport()->setViewportRenderer(getRenderSet());
  getViewport()->Coordinates().position()=Vector3D(0,0,-10);
  getViewportPlugin()->glWidget()->setViewportController(getCamera());
}
Hub & SampleApplication::hub(){return *getHub();}

int SampleApplication::run(){
  setup();
  _sample.setup();
  getInitializer()->initialize();
  return getApplication()->run();
}