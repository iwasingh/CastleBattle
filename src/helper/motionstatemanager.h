#ifndef MOTION_MANAGER_H
#include <irrlicht.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "bullethelper.h"
using namespace irr;

class MotionStateManager : public btMotionState {

    private:
        scene::ISceneNode* node;
        btTransform initialPosition;

    public:
        MotionStateManager(btTransform &pos, scene::ISceneNode* node);
        virtual ~MotionStateManager(){}

        virtual void getWorldTransform(btTransform &wordTrans) const;

        virtual void setWorldTransform(const btTransform &worldTrans);
};
#endif
