#include <irrlicht.h>
#include "physics.h"
#include "helper/bullethelper.h"
using namespace irr;

class Ball{

    private:

    public:
        btRigidBody* btBall;
        scene::ISceneNode* irrBall;
        f32 radius = 0.3f;
        Ball(scene::ISceneManager* smgr, video::IVideoDriver* driver, Physics* physics, core::vector3df position);



};
