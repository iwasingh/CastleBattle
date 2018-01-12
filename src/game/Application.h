#ifndef APPLICATION_H
#define APPLICATION_H
#include <irrlicht.h>
#include <physics.h>
#include <gamemanager.h>
#include <Terrain.h>

using namespace irr;
/** Application will set up ::Launcher screen, and start the loop through ::GameManager.
* In particular this class will init Irrlicht world and will add physics provided by ::Physics.
* Also it will show and handle the first launcher screen.
*/
class Application{
  private:
    /** Irrlicht device instance */
    IrrlichtDevice* device;
    
    /** Irrlicht video instance */
    video::IVideoDriver* driver;

    /** Irrlicht scene manager instance */
    scene::ISceneManager* smgr;

    /** Physics instance */
    Physics* physics;

    /** GameManager instance */
    GameManager* gameManager;

    /** Gui enviroment to build gui objects */
    gui::IGUIEnvironment* gui;

    /** Terrain of the world */
    Terrain* terrain;

  public:

    /** Default constructor.
    * Given the video driver from command line, the constructor will start all instances, initialize logger, start launcher and create world
    */
    Application();

    /** Main loop of the application.
    * @return true if someone win with a printed message on command line, false if something went wrong
    */
    bool loop();

    /** Create physics and graphics scene */
    void createWorldEnviroment();

    /** Start the launcher screen, and will wait the start button click event */
    bool init();
};
#endif
