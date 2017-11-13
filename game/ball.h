#include <irrlicht.h>
#include "physics.h"
#include "helper/bullethelper.h"
#include "camera.h"
using namespace irr;
/* Public class */
class Ball{


    public:
        scene::ISceneManager* smgr;
        btRigidBody* btBall;
        scene::ISceneNode* irrBall;
        f32 radius = 0.3f;
        core::vector3df cameraStartPosition;
        Camera* camera;
        Ball(scene::ISceneManager* smgr, video::IVideoDriver* driver, Physics* physics, core::vector3df position);
        void setCamera(scene::ICameraSceneNode* camera);
        void moveCamera();


};
