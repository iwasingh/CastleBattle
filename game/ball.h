#ifndef BALL_H
#define BALL_H
#include <irrlicht.h>
#include <vector>
#include "physics.h"
#include "helper/bullethelper.h"
#include "camera.h"
using namespace irr;
/* Public class */
const core::vector3df CAMERA_OFFSET_BALL = core::vector3df(0,1.f,-2.5f);
const core::vector3df CAMERA_OFFSET_BALL_OPPOSITE = core::vector3df(0,1.f,+2.5f);

class Ball{

    public:
        scene::ISceneManager* smgr;
        btRigidBody* btBall;
        scene::ISceneNode* irrBall;
        f32 radius = 0.3f;
        core::vector3df cameraStartPosition;
        Camera* camera;
        IrrlichtDevice* device;
        scene::ICameraSceneNode* parentCamera;
        Ball(IrrlichtDevice* device, scene::ISceneManager* smgr, video::IVideoDriver* driver, Physics* physics, core::vector3df position);
        core::array<core::vector3df> points;
        ~Ball();
        void setCamera(scene::ICameraSceneNode* camera, core::vector3df rotation = core::vector3df(0,0,0));
        bool moveCamera();
        void deleteCamera();


};
#endif
