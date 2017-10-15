#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>
#include "physics.h"
#include <helper/bullethelper.h>
using namespace irr;
;
Physics::Physics(const core::aabbox3df irrBox){

    this->collisionConfiguration = new btDefaultCollisionConfiguration();
	this->broadPhase = new btAxisSweep3(
        toBulletVector(core::vector3df(irrBox.MinEdge)), toBulletVector(core::vector3df(irrBox.MaxEdge))
    );
	this->dispatcher = new btCollisionDispatcher(collisionConfiguration);
	this->solver = new btSequentialImpulseConstraintSolver();

	this->initWorld();
}
void Physics::initWorld(){

    this->World = new btDiscreteDynamicsWorld(this->dispatcher, this->broadPhase, this->solver, this->collisionConfiguration);
    this->World->setGravity(btVector3(0,-10,0));

    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI = btRigidBody::btRigidBodyConstructionInfo(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    groundRigidBodyCI.m_restitution = 0.8f;
    groundRigidBodyCI.m_friction = 1.5f;
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

    World->addRigidBody(groundRigidBody);
}

void Physics::UpdatePhysics(u32 TDeltaTime) {

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(std::list<btRigidBody *>::iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {

		this->UpdateRender(*Iterator);
	}

}
void Physics::UpdateRender(btRigidBody *TObject) {
	scene::ISceneNode *Node = static_cast<scene::ISceneNode *>(TObject->getUserPointer());

	// Set position
	btVector3 Point = TObject->getCenterOfMassPosition();
	Node->setPosition(core::vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

	// Set rotation --- deprecated - non needed for now
//	vector3df Euler;
//	const btQuaternion& TQuat = TObject->getOrientation();
//	quaternion q(TQuat.getX(), TQuat.getY(), TQuat.getZ(), TQuat.getW());
//	q.toEuler(Euler);
//	Euler *= RADTODEG;
//	Node->setRotation(Euler);
}
btRigidBody* Physics::createCannonBall(scene::ISceneNode* node){
    core::vector3df position = node->getPosition();
    btTransform transformer;
    transformer.setIdentity();
    transformer.setOrigin(toBulletVector(position));

    btDefaultMotionState *motion = new btDefaultMotionState(transformer);
    btCollisionShape *sphere = new btSphereShape(1);

    btVector3 localInertia;
    sphere->calculateLocalInertia(2.f, localInertia);
    btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(10,motion,sphere,localInertia);
    ballRigidBodyCI.m_friction = 100.f;
    ballRigidBodyCI.m_restitution = 0.1f;

    btRigidBody *rigidBody = new btRigidBody(ballRigidBodyCI);
    rigidBody->setUserPointer((void*)(node));
        this->Objects.push_back(rigidBody);

    this->World->addRigidBody(rigidBody);
    return rigidBody;
}
