#include <irrlicht.h>
using namespace irr;
/*
A skydome is a large (half-) sphere with a panoramic texture on the inside and is drawn around the camera position.
We will use a simple skydome with a blue-sky texture
*/
class Sky{
    private:
        scene::ISceneNode* sky;
    public:
        Sky(scene::ISceneManager* smgr, video::IVideoDriver* driver, core::stringw texture, f32 radius);
};
