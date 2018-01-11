#ifndef MAIN
#define MAIN
#include <irrlicht.h>
#include <cstdlib>
#include <time.h>
#include <list>
#include "src/game/Application.h"
using namespace irr;

int main() {
  Application* app = new Application();
  srand (time(NULL));
  if(app->init()) return app->loop();
  return 1;
}

#endif
//
//     IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(800,600),16, false,false,false,0);
//     device->getCursorControl()->setVisible(false);
//     video::IVideoDriver* driver = device->getVideoDriver();
//     driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
//     scene::ISceneManager* smgr = device->getSceneManager();
//     srand (time(NULL));
//
//     // core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
//     // Terrain* terrain = new Terrain(smgr,driver,pathTexture,core::vector3df(250.f,0.0001f, 250.f));
//     // Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);
//
//     /********************BULLET INIT***************************/
//
//     Physics* physics = new Physics(terrain->getTerrainBox());
//
//     /********************END BULLET INIT**********************/
//
//     //Player* player = new Player(device,smgr,driver,terrain->getCenter(), physics, Player::AI);
//     GameManager* gameManager = new GameManager(smgr,driver,device,terrain->getCenter(), physics);
//     //smgr->addCameraSceneNodeFPS(0,100.f,0.04f)->setPosition(terrain->getCenter());
//     smgr->setAmbientLight(video::SColor(0,255,255,204));
//     int lastFPS = -1;
//     log(INFO,1,"CIAO");
//     log(INFO,2,"CIAO hard");
//
//     u32 TimeStamp = device->getTimer()->getTime(), DeltaTime = 0;
//     while(device->run() && device) {
//
// //        if(device->isWindowActive()){
//             u32 fps = driver->getFPS();
//             DeltaTime = device->getTimer()->getTime() - TimeStamp;
//             physics->UpdatePhysics(DeltaTime,fps);
//             driver->beginScene(true, true, video::SColor(255,200,200,200));
//
//             smgr->drawAll();
//             if(gameManager->loop()){
//                 gameManager->winner();
//                 break;
//             }
//             driver->endScene();
//
//             TimeStamp = device->getTimer()->getTime();
//
//             if(lastFPS != fps)
//             {
//                 core::stringw str =L"Castle Battle [";
//                 str += driver->getName();
//                 str += "] FPS:";
//                 str += fps;
//                 device->setWindowCaption(str.c_str());
//                 lastFPS = fps;
//             }
// //
// //        } else
// //            device->yield();
//     }
