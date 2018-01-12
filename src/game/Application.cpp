#include "Application.h"
#include <Sky.h>
#include <stdlib.h>
#include <Logger.h>
#include <driverChoice.h>
#include <launcher.h>
#include <iostream>
#include <bullethelper.h>
#include <cassert>
using namespace irr;
Application::Application(){
  // ask user for driver
   video::E_DRIVER_TYPE driverType = driverChoiceConsole();
   if (driverType==video::EDT_COUNT)
       exit (EXIT_FAILURE);

  this->device = createDevice(driverType, core::dimension2d<u32>(800,600), 16, false, false, false, 0);
  this->device->getLogger()->setLogLevel(ELL_NONE);
  #if (DEBUG_OUTPUT_MASK & 2)
      // this->device->getLogger()->setLogLevel(ELL_DEBUG);
  #endif
  this->driver = this->device->getVideoDriver();
  this->driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
  this->smgr = this->device->getSceneManager();
  this->smgr->setAmbientLight(video::SColor(0,255,255,204));
  log(INFO,1,"Turn on lights");
  this->gui = this->device->getGUIEnvironment();
  this->createInitWindow();
  this->createWorldEnviroment();


}
void Application::createInitWindow(){
}
void Application::createWorldEnviroment(){
  core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
  this->terrain = new Terrain(smgr,driver,pathTexture,core::vector3df(250.f,0.0001f, 250.f));
  Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);
  log1("World created");
  this->physics = new Physics(terrain->getTerrainBox());
  log(INFO,1,"Law of physics successfully created");
}
bool Application::init(){
  Launcher* screen = new Launcher(this->gui, this->device);
  assert(screen != 0);
  while(device->run() && driver){
   if (device->isWindowActive()){
      driver->beginScene(true, true, video::SColor(255,200,200,200));
       this->gui->drawAll();
       assert(screen->listener != 0);
       if(screen->listener->stateElement[GUI_ID_START_BUTTON]){
         break;
         screen->listener->stateElement[GUI_ID_START_BUTTON] = false;
       }
       driver->endScene();
   }
 }
 if(!driver) return false;
  core::stringw names[2];
  names[0] = (screen->players[0]->getText());
  names[1] = (screen->players[1]->getText());
  screen->clear();
  this->gameManager = new GameManager(smgr,driver,device,terrain->getCenter(), physics, names);
  #if (DEBUG_OUTPUT_MASK & 2)
      this->smgr->addCameraSceneNodeFPS(0,100.f,0.04f)->setPosition(terrain->getCenter());
  #endif

  this->device->getCursorControl()->setVisible(false);
  log1("Gameplay initialized.");
  return true;
}
bool Application::loop(){
  u32 TimeStamp = device->getTimer()->getTime(), DeltaTime = 0;
  int lastFPS = -1;
  bool flagWin = false;
  while(device->run() && device) {

    //        if(device->isWindowActive()){
                u32 fps = driver->getFPS();
                DeltaTime = device->getTimer()->getTime() - TimeStamp;
                physics->UpdatePhysics(DeltaTime,fps);
                driver->beginScene(true, true, video::SColor(255,200,200,200));

                smgr->drawAll();
                if(gameManager->loop()){
                    flagWin = true;
                    break;
                }
                driver->endScene();

                TimeStamp = device->getTimer()->getTime();

                if(lastFPS != fps)
                {
                    core::stringw str =L"Castle Battle [";
                    str += driver->getName();
                    str += "] FPS:";
                    str += fps;
                    device->setWindowCaption(str.c_str());
                    lastFPS = fps;
                }
  }
  if(flagWin) { log(1,INFO,"Thanks for playing. Goodbye!"); return 0; }

}
