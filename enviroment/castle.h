#ifndef CASTLE_H
#define CASTLE_H
#include <irrlicht.h>
#include <vector>
#include <game/physics.h>
#include <helper/bullethelper.h>
using namespace irr;
const f32 BLOCKS_OFFSET = 0.05f;

class Castle{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        core::vector3df position;
        scene::IMeshSceneNode* node;
        IrrlichtDevice* device;
        std::vector<scene::IMeshSceneNode*> nodes;
        Physics* physics;
        void createBlock(core::vector3df position, core::vector3df scale, core::vector3df rotation);
        void addToPhysicsWorld();

    public:
        video::SColor COLOR_LIGHT;
        video::SColor COLOR_DARK;
        Castle(scene::ISceneManager* smgr, Physics* physics, IrrlichtDevice* device, video::IVideoDriver* driver, core::vector3df center);
        bool buildCastle(core::vector3df center);


};
#endif
