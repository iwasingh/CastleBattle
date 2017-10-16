#include <irrlicht.h>

using namespace irr;

class Terrain{
    private:
        scene::ITerrainSceneNode* terrain;

    public:
        Terrain(scene::ISceneManager* smgr, video::IVideoDriver* driver, const core::stringw* pathTexture, const core::vector3df &scale);
        ~Terrain();
        core::vector3df getCenter();
    void collisionResponseAnimator(scene::ISceneManager* smgr,scene::ISceneNode* obj);
    void addCollisionNode(scene::ISceneManager* smgr,scene::IAnimatedMeshSceneNode* obj);
    core::aabbox3df getTerrainBox();
    scene::ITerrainSceneNode* getTerrain();

};
