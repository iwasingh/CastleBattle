#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"
#include "ball.h"
#include "target.h"
#include "camera.h"
#include <hud.h>
#include <castle.h>
#include "cannon.h"
using namespace irr;
using namespace KEYBOARD;

 enum PLAYER_TYPE{
    HUMAN=0,
    AI
 };
 enum PLAYER_POSITION{
    STRAIGHT,
    OPPOSITE
 };

class Player{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        irr::IrrlichtDevice* device;
        Camera* camera;
        Physics* physics;
        Castle* castle;
        Cannon* cannon;
        Keyboard *keyboard;
        PLAYER_POSITION side;
    public:
        core::stringw name;
        PLAYER_TYPE type;
        Player(IrrlichtDevice* device,scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, Keyboard* keyboard, PLAYER_TYPE type, PLAYER_POSITION side = STRAIGHT);
        scene::IMeshSceneNode* getNode();
        core::vector3df getCannonRange();
        void focusCamera();
        void setCannon();
        bool loop(HUD::HUD* hud);
        void reset();
        bool checkTarget();




};
#endif
