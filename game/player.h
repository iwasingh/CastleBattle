#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"
#include "ball.h"
#include "target.h"
#include "camera.h"
#include <hud/hud.h>
#include <enviroment/castle.h>
#include "cannon.h"
using namespace irr;
using namespace KEYBOARD;



class Player{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        Camera* camera;
        Keyboard keyboard;
        Physics* physics;
        Castle* castle;
        Cannon* cannon;
    public:
        enum PLAYER_TYPE{
        HUMAN=0,
        AI
        };
        PLAYER_TYPE type;
        Player(IrrlichtDevice* device,scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, PLAYER_TYPE type);
        scene::IAnimatedMeshSceneNode* getNode();
        void initKeyboard(IrrlichtDevice* device);
        void loop(HUD::HUD* hud);
        core::vector3df getCannonRange();


};
#endif
