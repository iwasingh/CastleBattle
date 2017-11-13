#ifndef CAMERA_H
#define CAMERA_H
#include <irrlicht.h>
using namespace irr;

class Camera{
    private:
        scene::ISceneManager* smgr;

    public:
        scene::ICameraSceneNode* camera;
        Camera(scene::ICameraSceneNode* camera, scene::ISceneManager* smgr);
        Camera(scene::ICameraSceneNode* camera, scene::ISceneNode* parent, scene::ISceneManager* smgr);
        Camera(core::vector3df offset, core::vector3df rotation,scene::ISceneManager* smgr, scene::ISceneNode* parent);
        ~Camera();
        void activeCamera();
        scene::ICameraSceneNode* getCamera();

};
#endif // CAMERA_H
