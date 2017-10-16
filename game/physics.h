#ifndef PHYSICS_H
#define PHYSICS_H
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>
#include <list>
using namespace irr;
class Physics{
    private:
        btDiscreteDynamicsWorld *World;
        std::list<btRigidBody *> Objects;
         btDefaultCollisionConfiguration *collisionConfiguration;
        btBroadphaseInterface *broadPhase;
        btCollisionDispatcher *dispatcher;
        btSequentialImpulseConstraintSolver *solver;
    public:
        Physics(const core::aabbox3df irrBox);
        void initWorld();
        void UpdatePhysics(u32 delta);
        void UpdateRender(btRigidBody* btbody);
        btRigidBody* createCannonBall(scene::ISceneNode* node, core::vector3df position, f32 radius);
};
#endif
