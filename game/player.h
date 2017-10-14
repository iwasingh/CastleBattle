#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"

using namespace irr;
using namespace KEYBOARD;

const f32 INCLINATE_FACTOR = 0.5f;
const f32 MAX_ANGLE_BOTTOM = 115.f;
const f32 MAX_ANGLE_TOP = 148.f;

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
    public:
        enum PLAYER_TYPE{
        HUMAN=0,
        AI
        };
        Player(IrrlichtDevice* device,scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, PLAYER_TYPE type);
        scene::IAnimatedMeshSceneNode* getNode();
        void initKeyboard(IrrlichtDevice* device);
        void loop();
        void inclinate(ACTION_KEYBOARD action);
        f32 refreshAngle();
        core::matrix4 getInclinateValues(ACTION_KEYBOARD key);
};
#endif
