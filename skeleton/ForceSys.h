#pragma once
#include <vector>
#include <unordered_map>
class Particle;
class ForceGen;

class ForceSys
{
public:
	std::unordered_map<Particle*,std::vector<ForceGen*>> fuerzasGen;
	std::unordered_map<physx::PxRigidDynamic*, std::vector<ForceGen*>> fuerzasGenSolids;

	~ForceSys();
	void addForce(Particle* p, ForceGen* fg);
	void addForce(physx::PxRigidDynamic* s, ForceGen* fg);

	void removeForces(Particle* p);
	void removeForces(physx::PxRigidDynamic* s);

	void update(float dt);
};

