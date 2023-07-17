#pragma once
#include "MyVertex.h"
#include "Vector3D.h"
#include "MyMatrix.h"
class Camera
{
public:
	Camera(float xRotation, float yRotation, float zRotation, const Vertex & position);

	Vector3D GetPosition() const;
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	Matrix3x3 GetViewingMatrix();
private:
	float xRotation = 0;
	float yRotation = 0;
	float zRotation = 0;

	Vector3D position = Vector3D(0,0,-50);

	Matrix3x3 ViewMatrix;

};