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
        btTransform ground;
    public:
        Physics(const core::aabbox3df irrBox);
        void initWorld();
        btTransform getGround();
        void UpdatePhysics(u32 delta, u32 fps);
        void UpdateRender(btRigidBody* btbody);
        btRigidBody* createCannonBall(scene::ISceneNode* node, core::vector3df position, f32 radius);
        btRigidBody* createTreasure(scene::ISceneNode* node, core::vector3df scale, core::vector3df position);

};
#endif
