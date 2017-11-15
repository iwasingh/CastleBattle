#include <irrlicht.h>
#include "enviroment/Terrain.h"
#include "enviroment/Sky.h"
#include "hud/hud.h"
#include "game/player.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <cstdlib>
#include <list>
#include "game/physics.h"
using namespace irr;

int main() {

    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(800,600),16, false,false,false,0);
    device->getCursorControl()->setVisible(false);
    video::IVideoDriver* driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
    scene::ISceneManager* smgr = device->getSceneManager();

       core::stringw pathTexture[2] = {"media/terrain/grass_green_old.jpg","media/terrain/grass_green_thin.jpg"};
    Terrain* terrain = new Terrain(smgr,driver,pathTexture,core::vector3df(250.f,0.0001f, 250.f));
    Sky* sky = new Sky(smgr,driver,"media/terrain/sky.jpg",1000.0f);

    /********************BULLET INIT***************************/

    Physics* physics = new Physics(terrain->getTerrainBox());

    /********************END BULLET INIT**********************/

    HUD::HUD* hud = new HUD::HUD(device,driver);
    Player* player = new Player(device,smgr,driver,terrain->getCenter(), physics, Player::AI);

    smgr->addCameraSceneNodeFPS(0,100.f,0.009f)->setPosition(terrain->getCenter());
//    terrain->addCollisionNode(smgr,);
//    scene::ISceneCollisionManager* csmgr = smgr->getSceneCollisionManager();
    smgr->setAmbientLight(video::SColor(0,255,255,204));
    int lastFPS = -1;
    u32 TimeStamp = device->getTimer()->getTime(), DeltaTime = 0;

    while(device->run() && device) {

        if(device->isWindowActive()){
            u32 fps = driver->getFPS();
            DeltaTime = device->getTimer()->getTime() - TimeStamp;
            TimeStamp = device->getTimer()->getTime();
            physics->UpdatePhysics(DeltaTime,fps);
            driver->beginScene(true, true, video::SColor(255,200,200,200));

            smgr->drawAll();
            hud->env->drawAll();
            player->loop(hud);
            driver->endScene();
            if(lastFPS != fps)
            {
                core::stringw str =L"Castle Battle [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;
                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        } else
            device->yield();
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
