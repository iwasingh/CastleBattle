#include <irrlicht.h>
#include "ball.h"
#include "keyboard.h"
#include "camera.h"

using namespace irr;
using namespace KEYBOARD;
const f32 INCLINATE_FACTOR = 0.1f;
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
        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::IMeshSceneNode* cannon;
        scene::IMeshBuffer* barrel;
        scene::IMeshBuffer* wagon;
        f32 angle;
        Camera* camera;
        Ball* btBall;
        Physics* physics;
        core::vector3df initialBarrelVector;
        core::vector3df initBarrelVector;
        core::vector3df plane;
        ;
    public:
        core::vector3df rotation;
        Cannon(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, Physics* physics);
        ~Cannon();
        f32 refreshAngle();
        core::aabbox3df getBoundingBox();
        scene::IMeshSceneNode* getCannon();
        core::matrix4 getInclinateValues(ACTION_KEYBOARD key);
        core::vector3df getRange();
        Camera* getCamera();
        void setRotation(core::vector3df rotation);
        void shoot(f32 power);
        void setCamera(core::vector3df offset, core::vector3df rotation, scene::ISceneManager* smgr,scene::ISceneNode* node);
        void setPosition(core::vector3df position);
        bool moveCannon(ACTION_KEYBOARD action);
        bool moveCamera();
        void initAngles();
        void reset();
        void initCannon(core::vector3df position, core::vector3df rotation);

};
