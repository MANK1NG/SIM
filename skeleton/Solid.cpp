#include "Solid.h"



Solid::Solid(physx::PxTransform t, physx::PxGeometry& geo, Vector3 linear_v, Vector3 ang_v, float masa, Vector4 color, physx::PxPhysics* phys, physx::PxScene* scene, physx::PxVec3 inertia, float lifeTime_)
{
	gScene = scene;
	lifeTime = lifeTime_;

	physx::PxReal staticFriction = 0.5f;
	physx::PxReal dynamicFriction = 0.3f;
	physx::PxReal restitution = 0.7f;

	physx::PxMaterial* material = phys->createMaterial(staticFriction, dynamicFriction, restitution);
	body = phys->createRigidDynamic(t);
	body->setLinearVelocity(linear_v);
	body->setAngularVelocity(ang_v);
	shape = CreateShape(geo, material);
	body->attachShape(*shape);
	physx::PxReal mass = masa;

	body->setMass(mass);
	body->setMassSpaceInertiaTensor(inertia);
	scene->addActor(*body);

	renderItem = new RenderItem(shape, body, color);
}

Solid::~Solid()
{
	DeregisterRenderItem(renderItem);
	gScene->removeActor(*body);
	body->release();
	shape->release();

}

void Solid::update(double dt) {
	if (!alive) return;

	timeAlive += dt;
	physx::PxTransform pose = body->getGlobalPose();
	if (timeAlive >= lifeTime || pose.p.y < -3.0f || pose.p.y > 60.0f|| pose.p.z > 120 || pose.p.z< -120) {
		alive = false;
	}
}
