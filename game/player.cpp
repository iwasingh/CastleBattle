#include "player.h"
#include <iostream>
using namespace irr;

Player::Player(scene::ISceneManager* smgr, video::IVideoDriver* driver, core::vector3df position, PLAYER_TYPE type){
    this->cannon = smgr->addAnimatedMeshSceneNode(
    smgr->getMesh("media/cannon/cannon.obj"),
    0,
    type,
    position
    );
    this->cannon->setMaterialFlag(video::EMF_LIGHTING, false);
    this->cannon->setMaterialTexture(0,driver->getTexture("media/cannon/cannon_tex.png"));
    this->cannon->setMaterialTexture(1,driver->getTexture("media/cannon/cannonwagon_tex.png"));
    if(type == HUMAN){
        this->camera = smgr->addCameraSceneNode(0,
            core::vector3df(
                this->cannon->getPosition().X,
                this->cannon->getPosition().Y+this->cannon->getBoundingBox().MaxEdge.Y+0.6f,
                this->cannon->getPosition().Z-2.f));
        this->camera->setTarget(this->cannon->getAbsolutePosition());
        this->camera->bindTargetAndRotation(true);
        this->camera->setRotation(core::vector3df(0,0,0));
        this->camera->setFarValue(3000.f);
    }


    scene::IMeshBuffer* cannonUpper = this->cannon->getMesh()->getMeshBuffer(0);
    scene::IMeshBuffer* cannonLower = this->cannon->getMesh()->getMeshBuffer(1);

    for(unsigned int i = 0; i < cannonUpper->getVertexCount(); i++){
//        cannonUpper->getPosition(i).rotateYZBy(-15.f,core::vector3df(0,0,0));// up and down
//        cannonUpper->getPosition(i).rotateXZBy(-5.f,core::vector3df(0,0,0)); //left right, should be minimal
    }
            cannonUpper->recalculateBoundingBox();


}
scene::IAnimatedMeshSceneNode* Player::getNode() {
    return this->cannon;
}
