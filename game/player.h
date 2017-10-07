#include <irrlicht.h>
using namespace irr;

class Player{
    private:
        scene::ISceneManager* smgr;
        scene::IAnimatedMeshSceneNode* cannon;
        scene::ICameraSceneNode* camera;

    public:
        enum PLAYER_TYPE{
        HUMAN=0,
        AI
        };
        Player(scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, PLAYER_TYPE type);
        scene::IAnimatedMeshSceneNode* getNode();
};
