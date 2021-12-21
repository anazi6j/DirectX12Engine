#include "BULLET3TEST.h"


btDynamicsWorld* g_pDynamicsWorld = 0;	//!< Bullet���[���h
btRigidBody* g_pSphereBody = 0;		//!< ����
void BULLET3TEST::InitBullet(void)
{
	btVector3 pos = btVector3(-1,0.5,0);
	btScalar mass =0.03;
	btScalar restitution = 0.0f;

	//�Փˌ��o���@�̑I���i�f�t�H���g��I���j
	btDefaultCollisionConfiguration* config = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(config);

	//�u���[�h�t�F�[�Y�@�̐ݒ�(Dynamic AABB�@tree method)
	btDbvtBroadphase* broadphase = new btDbvtBroadphase();

	//�S��(���̊ԃ����N�j�̃\���o�ݒ�
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	// Bullet�̃��[���h�쐬
    g_pDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
    g_pDynamicsWorld->setGravity(btVector3(0, -9.8, 0));
	btSphereShape g_fRad = btSphereShape(1.0f);
    // ���̌`���ݒ�
    btCollisionShape *sphere_shape = new btSphereShape(g_fRad);

    // ���̂̏����ʒu�E�p��
    btQuaternion qrot(0, 0, 0, 1);
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

    // �������[�����g�̌v�Z
    btVector3 inertia(0, 0, 0);
    sphere_shape->calculateLocalInertia(mass, inertia);

    // ���̃I�u�W�F�N�g����(���ʁC�ʒu�p���C�`��C�������[�����g��ݒ�)
    g_pSphereBody = new btRigidBody(mass, motion_state, sphere_shape, inertia);

    // ���[���h�ɍ��̃I�u�W�F�N�g��ǉ�
    g_pDynamicsWorld->addRigidBody(g_pSphereBody);
}


void BULLET3TEST::CleanBullet(void)
{
	// �I�u�W�F�N�g�j��
	delete g_pSphereBody->getMotionState();
	g_pDynamicsWorld->removeRigidBody(g_pSphereBody);
	delete g_pSphereBody;

	// ���[���h�j��
	delete g_pDynamicsWorld->getBroadphase();
	delete g_pDynamicsWorld;
}


void BULLET3TEST::Timer(int value)
{
	// ���̂̕������^�����v�Z
	if (g_bIdle) {
		if (g_iStep == 0) {
			g_pSphereBody->applyCentralImpulse(g_v3Frc * DT);
		}

		// bullet�̃X�e�b�v��i�߂�
		if (g_pDynamicsWorld) {
			g_pDynamicsWorld->stepSimulation(DT, 1);
		}

		g_iStep++;
		
	}

}