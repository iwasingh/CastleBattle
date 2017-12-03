#include <irrlicht.h>
#include "ball.h"
#include "keyboard.h"
#include "camera.h"

using namespace irr;
using namespace KEYBOARD;
const f32 INCLINATE_FACTOR = 0.5f;
const f32 MAX_ANGLE_BOTTOM = 5.f;
const f32 MAX_ANGLE_TOP = 45.f;
const f32 MAX_ANGLE_LEFT = -20.f;
const f32 MAX_ANGLE_RIGHT = 20.f;
const f32 MAX_CANNON_FORCE = 50.f;
const f32 CANNON_POWER = 50.f;
const f32 BARREL_RADIUS = 0.6f;
class Cannon{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        scene::IAnimatedMeshSceneNode* cannon;
        scene::IMeshBuffer* barrel;
        scene::IMeshBuffer* wagon;
        f32 angle;
        Camera* camera;
        Ball* btBall;
        Physics* physics;
        core::vector3df rotation = core::vector3df(0,0,0);
        core::vector3df initBarrelVector;
        core::vector3df plane;
    public:
        Cannon(scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics);
        void shoot(f32 power);
        f32 refreshAngle();
        void initAngles();
        core::aabbox3df getBoundingBox();
        scene::IAnimatedMeshSceneNode* getCannon();
        void moveCannon(ACTION_KEYBOARD action);
        void moveCamera();
        core::matrix4 getInclinateValues(ACTION_KEYBOARD key);
        void setCamera(core::vector3df offset, core::vector3df rotation, scene::ISceneManager* smgr,scene::ISceneNode* node);
        void setPosition(core::vector3df position);
        core::vector3df getRange();

};
