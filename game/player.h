#ifndef PLAYER_H
#define PLAYER_H
#include <irrlicht.h>
#include "keyboard.h"

using namespace irr;
using namespace KEYBOARD;
class Player{
    private:
        scene::ISceneManager* smgr;
        scene::IAnimatedMeshSceneNode* cannon;
        scene::ICameraSceneNode* camera;
        Keyboard keyboard;
    public:
        enum PLAYER_TYPE{
        HUMAN=0,
        AI
        };
        Player(IrrlichtDevice* device,scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, PLAYER_TYPE type);
        scene::IAnimatedMeshSceneNode* getNode();
        void initKeyboard(IrrlichtDevice* device);
        void loop();
};
#endif
