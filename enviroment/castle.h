#ifndef CASTLE_H
#define CASTLE_H
#include <irrlicht.h>
#include <vector>
#include <game/physics.h>
using namespace irr;
const f32 BLOCKS_OFFSET = 0.05f;
class Castle{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        core::vector3df position;
        scene::ISceneNode* node;
        IrrlichtDevice* device;
        std::vector<scene::ISceneNode*> nodes;
        Physics* physics;

    public:
        Castle(scene::ISceneManager* smgr, Physics* physics, IrrlichtDevice* device, video::IVideoDriver* driver, core::vector3df center);
        bool buildCastle(core::vector3df center);
        void addToPhysicsWorld();


};
#endif
