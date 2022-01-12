#include "Character.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
void SkinnedCharacter::SetRagdolls()
{
	
}

void StaticCharacter::SetRigidbody()
{
	btVector3 pos = btVector3(-1, 0.5, 0);    //!< ���S���W
	btScalar mass = 0.03;                    //!< ����
	btScalar restitution = 0.8;                //!< �����W��

	// �Փˌ��o���@�̑I��(�f�t�H���g��I��)
	btDefaultCollisionConfiguration* config = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(config);

	// �u���[�h�t�F�[�Y�@�̐ݒ�(Dynamic AABB tree method)
	btDbvtBroadphase* broadphase = new btDbvtBroadphase();

	// �S��(���̊ԃ����N)�̃\���o�ݒ�
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	// Bullet�̃��[���h�쐬
	auto g_pDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
	g_pDynamicsWorld->setGravity(btVector3(0, -9.8, 0));
	float g_frad = 1.0f;
	// ���̌`���ݒ�
	btCollisionShape* sphere_shape = new btSphereShape(g_frad);

	// ���̂̏����ʒu�E�p��
	btQuaternion qrot(0, 0, 0, 1);
	btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

	// �������[�����g�̌v�Z
	btVector3 inertia(0, 0, 0);
	sphere_shape->calculateLocalInertia(mass, inertia);

	// ���̃I�u�W�F�N�g����(���ʁC�ʒu�p���C�`��C�������[�����g��ݒ�)
	auto g_pSphereBody = new btRigidBody(mass, motion_state, sphere_shape, inertia);

	// ���[���h�ɍ��̃I�u�W�F�N�g��ǉ�
	g_pDynamicsWorld->addRigidBody(g_pSphereBody);


	btVector3 forward = btVector3(1, 0, 0);
	g_pSphereBody->applyCentralForce(inertia);
}
