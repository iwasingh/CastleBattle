#ifndef APPLICATION_H
#define APPLICATION_H
#include <irrlicht.h>
#include <physics.h>
#include <gamemanager.h>
#include <Terrain.h>

using namespace irr;

class Application{
  private:
    IrrlichtDevice* device;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
    Physics* physics;
    GameManager* gameManager;
    gui::IGUIEnvironment* gui;
    Terrain* terrain;

  public:
    Application();
    bool loop();
    void createWorldEnviroment();
    void createInitWindow();
    bool init();
};
#endif
