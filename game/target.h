#ifndef TARGET_H
#define TARGET_H
#include<irrlicht.h>
#include "physics.h"
using namespace irr;

class Target{
    private:
        scene::ISceneManager* smgr;
        Physics* physics;
        scene::IMeshSceneNode* irrTarget;
        btRigidBody* btTarget;
        core::vector3df position;
    public:
        // this wil figure out where to put the target based on the power of the cannon(or shoot power) and the offset
        Target(core::vector3df position, scene::ISceneManager* smgr, video::IVideoDriver* driver, Physics* physics);
};
#endif
