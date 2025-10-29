#pragma once
#include <vector>
#include <unordered_map>
class Particle;
class ForceGen;

class ForceSys
{
public:
	std::unordered_map<Particle*,std::vector<ForceGen*>> fuerzasGen;
	~ForceSys();
	void addForce(Particle* p, ForceGen* fg);
	void update(float dt);
};

