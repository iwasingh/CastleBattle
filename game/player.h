#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"
#include "ball.h"
#include <hud/hud.h>
using namespace irr;
using namespace KEYBOARD;

const f32 INCLINATE_FACTOR = 0.5f;
const f32 MAX_ANGLE_BOTTOM = 125.f;
const f32 MAX_ANGLE_TOP = 148.f;
const f32 MAX_CANNON_FORCE = 50.f;
const f32 MAX_RANGE_X = 50.f;
const f32 MAX_RANGE_Y = 25.f;

class Player{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        scene::IAnimatedMeshSceneNode* cannon;
        scene::ICameraSceneNode* camera;
        Keyboard keyboard;
        scene::IMeshBuffer* barrel;
        scene::IMeshBuffer* wagon;
        f32 angle;
        Ball* btBall;
        Physics* physics;
        core::vector3df rotation;
    public:
        enum PLAYER_TYPE{
        HUMAN=0,
        AI
        };
        Player(IrrlichtDevice* device,scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics, PLAYER_TYPE type);
        scene::IAnimatedMeshSceneNode* getNode();
        void initKeyboard(IrrlichtDevice* device);
        void loop(HUD::HUD* hud);
        void inclinate(ACTION_KEYBOARD action);
        void shoot(f32 power);
        f32 refreshAngle();
        core::matrix4 getInclinateValues(ACTION_KEYBOARD key);
};
#endif
