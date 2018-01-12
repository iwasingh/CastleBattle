#ifndef BULLET_HELPER_H
#define BULLET_HELPER_H
#include <irrlicht.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
using namespace irr;
//namespace BulletWrap{

    btVector3 toBulletVector(core::vector3df vec);
    btQuaternion EulerToQuaternion(const core::vector3df &euler);
    core::vector3df QuaternionToEuler(const btQuaternion &TQuat);
    core::vector3df toIrrlichtVector(btVector3 vec);
    f32 getRand(const f32 maxValue, const f32 offset = 0.f);
    f32* getMeshSize(scene::ISceneNode* mesh);
    video::SColor randomColor();
    int sign(int x);
    core::stringc vectorToString(core::vector3df vector);

#endif
