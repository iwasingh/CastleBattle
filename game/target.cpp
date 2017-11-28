#include "target.h"
#include <iostream>
using namespace std;
using namespace irr;

Target::Target( core::vector3df power, core::vector3df offset, scene::ISceneManager* smgr, video::IVideoDriver* driver, Physics* physics){
    this->smgr = smgr;
    this->physics = physics;
    scene::IMesh* mesh = smgr->getMesh("media/chest/chest.obj");
    core::vector3df pos = power + offset;
    btVector3 ground = physics->getGround().getOrigin();
    core::vector3df scale = core::vector3df(1,1,1);
    this->irrTarget = smgr->addCubeSceneNode(1,0,-1,pos);
    //this->irrTarget = smgr->addMeshSceneNode(mesh,0,-1);
        //pos += core::vector3df(0,this->irrTarget->getBoundingBox().getCenter().Y,0);

    this->irrTarget->setScale(scale);
    this->irrTarget->setPosition(pos);
    this->irrTarget->setMaterialFlag(video::EMF_LIGHTING, false);
    this->irrTarget->setMaterialTexture(0, driver->getTexture("media/chest/chest_rare.jpg"));

    this->irrTarget->setDebugDataVisible(scene::EDS_BBOX);
    this->btTarget = physics->createTreasure(this->irrTarget,scale, pos);
}
