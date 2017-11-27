#ifndef CASTLE_H
#define CASTLE_H
#include <irrlicht.h>
#include <vector>
using namespace irr;
const f32 BLOCKS_OFFSET = 0.05f;
class Castle{
    private:
        scene::ISceneManager* smgr;
        video::IVideoDriver* driver;
        core::vector3df position;
        scene::IMeshSceneNode* node;
        IrrlichtDevice* device;
        std::vector<scene::IMeshSceneNode*> nodes;

    public:
        Castle(scene::ISceneManager* smgr, IrrlichtDevice* device, video::IVideoDriver* driver, core::vector3df center);
        bool buildCastle(core::vector3df center);


};
#endif
