#include "AnchoredSpringForceGen.h"

AnchoredSpringForceGen::AnchoredSpringForceGen(double k, double resting, const Vector3D& anchor_pos) :
	SpringForceGenerator(k, resting, nullptr) {
	_other = new Particle(anchor_pos, Vector3D(0, 0, 0), 1.0f, 1e9, Vector4(1, 1, 1, 1), 1.0f, 1e9);


}

AnchoredSpringForceGen::~AnchoredSpringForceGen()
{
	delete _other;
}
