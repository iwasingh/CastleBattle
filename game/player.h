#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"
#include "ball.h"
#include "camera.h"
#include <hud/hud.h>
using namespace irr;
using namespace KEYBOARD;

const f32 INCLINATE_FACTOR = 0.5f;
const f32 MAX_ANGLE_BOTTOM = 5.f;
const f32 MAX_ANGLE_TOP = 45.f;
const f32 MAX_ANGLE_LEFT = -20.f;
const f32 MAX_ANGLE_RIGHT = 20.f;
const f32 MAX_CANNON_FORCE = 50.f;
const f32 CANNON_POWER = 50.f;
//const f32 MAX_RANGE_Y = 10.f;
const f32 BARREL_RADIUS = 0.6f;

class Player{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        scene::IAnimatedMeshSceneNode* cannon;
        Camera* camera;
        Keyboard keyboard;
        scene::IMeshBuffer* barrel;
        scene::IMeshBuffer* wagon;
        f32 angle;
        Ball* btBall;
        Physics* physics;
        core::vector3df rotation = core::vector3df(0,0,0);
        core::vector3df initBarrelVector;
        core::vector3df plane;
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
        void moveCannon(ACTION_KEYBOARD action);
        void shoot(f32 power);
        f32 refreshAngle();
        void initAngles();
        core::matrix4 getInclinateValues(ACTION_KEYBOARD key);
};
#endif
