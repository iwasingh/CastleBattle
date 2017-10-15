#include <irrlicht.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
using namespace irr;
//namespace BulletWrap{

    btVector3 toBulletVector(core::vector3df vec);

    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);
