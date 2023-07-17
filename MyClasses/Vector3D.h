#pragma once
#include "MyVertex.h"
#include "Vector3D.h"

class Vector3D
{
public:
	Vector3D(); 

	Vector3D(float x, float y, float z);
	Vector3D(const Vertex& vertex);

	float GetMagnitude() const;
	Vector3D GetNormalisedVector() const;

	float GetX() const;
	float GetY() const;
	float GetZ() const;
	
	void SetX(float value);
	void SetY(float value);
	void SetZ(float value);

	bool operator==(const Vector3D& otherV);
	Vector3D& operator+(const Vector3D& otherV);
	Vector3D& operator-(const Vector3D& otherV);
	Vector3D& operator*(const Vector3D& otherV);
	Vector3D& operator*(const float scale);
private:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

float DotProductVector(const Vector3D v1, const Vector3D v2);

Vector3D CrossProductVector(const Vector3D v1, const Vector3D v2);