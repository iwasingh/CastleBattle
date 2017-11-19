#include <irrlicht.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
using namespace irr;
//namespace BulletWrap{

    btVector3 toBulletVector(core::vector3df vec);

    core::vector3df QuaternionToEuler(const btQuaternion &TQuat);
    core::vector3df toIrrlichtVector(btVector3 vec);
