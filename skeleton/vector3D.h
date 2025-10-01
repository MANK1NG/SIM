#pragma once

#include <cmath>
class Vector3D
{
private:
	float x;
	float y;
	float z;

public:

	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	
	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline float getZ() const { return z; }



	inline Vector3D normalice(const Vector3D& _vec) const {
		int modulo = module(_vec);
		if (modulo == 0) {
			return Vector3D(0, 0, 0);
		}else{
			return Vector3D(_vec.x / modulo, _vec.y / modulo, _vec.z / modulo);
		}
	}
	inline int module(const Vector3D& _vec) const {
		return sqrt(_vec.x* _vec.x + _vec.y*_vec.y + _vec.z*_vec.z);
	}

	inline double escalar(const Vector3D& _vec) const {
		return x * _vec.x + y * _vec.y + z * _vec.z;
	}

	inline Vector3D multEscalar(const double& _esc) const {
		return Vector3D(x * _esc, y * _esc, z * _esc);
	}


	inline Vector3D& operator=(const Vector3D& otro) {
		if (this != &otro) {
			x = otro.x;
			y = otro.y;
			z = otro.z;

		}
		return *this;
	}

	inline Vector3D& operator+(const Vector3D& otro) {
		return Vector3D(x + otro.x, y + otro.y, z + otro.z);
	}
	inline Vector3D& operator-(const Vector3D& otro) {
		return Vector3D(x - otro.x, y - otro.y, z - otro.z);

	}
	inline Vector3D& operator*( const Vector3D& otro) const{
		return Vector3D(x * otro.x, y * otro.y, z * otro.z);

	}

};

