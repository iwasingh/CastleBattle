#ifndef MAIN
#define MAIN
#include <irrlicht.h>
#include "enviroment/Terrain.h"
#include "enviroment/Sky.h"
#include "hud/hud.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <cstdlib>
#include <time.h>
#include <list>
#include "game/physics.h"
#include "game/gamemanager.h"
using namespace irr;

int main() {

    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(800,600),16, false,false,false,0);
    device->getCursorControl()->setVisible(false);
    video::IVideoDriver* driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
    scene::ISceneManager* smgr = device->getSceneManager();
    srand (time(NULL));

    core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
    Terrain* terrain = new Terrain(smgr,driver,pathTexture,core::vector3df(250.f,0.0001f, 250.f));
    Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);

    /********************BULLET INIT***************************/

    Physics* physics = new Physics(terrain->getTerrainBox());

    /********************END BULLET INIT**********************/

    //Player* player = new Player(device,smgr,driver,terrain->getCenter(), physics, Player::AI);
//    Castle* castle = new Castle(smgr,physics,device,driver,terrain->getCenter() + core::vector3df(-15,0,175));
    GameManager* gameManager = new GameManager(smgr,driver,device,terrain->getCenter(), physics);
    smgr->addCameraSceneNodeFPS(0,100.f,0.04f)->setPosition(terrain->getCenter());
    smgr->setAmbientLight(video::SColor(0,255,255,204));
    int lastFPS = -1;
    u32 TimeStamp = device->getTimer()->getTime(), DeltaTime = 0;
    while(device->run() && device) {

//        if(device->isWindowActive()){
            u32 fps = driver->getFPS();
            DeltaTime = device->getTimer()->getTime() - TimeStamp;
            physics->UpdatePhysics(DeltaTime,fps);
            driver->beginScene(true, true, video::SColor(255,200,200,200));

            smgr->drawAll();
            //hud staff goes here
            gameManager->loop();
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
//
//        } else
//            device->yield();
    }
}

//    IAnimatedMesh* map_mesh = smgr->getMesh("./media/Second.obj");
//    ISceneNode* map_node = 0;
//
//    if(map_mesh) map_node = smgr->addOctreeSceneNode(map_mesh->getMesh(0), 0, -1, 1024);
//    if(map_node) map_node->setPosition(core::vector3df(0,-5,0));
//
//    map_node->setMaterialTexture(0,driver->getTexture("./media/FirstMap.png"));
//    //ILightSceneNode* light = smgr->addLightSceneNode(0, core::vector3df(400,800,-1400),video::SColor(0,255,255,204),2000.0f);
//    smgr->setAmbientLight(video::SColor(0,255,255,204));
#endif
