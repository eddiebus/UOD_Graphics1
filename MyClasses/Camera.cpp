#include "Camera.h"
#include <math.h>




Camera::Camera(
	float xRot, float yRot, float zRot, 
	const Vertex& position
)
{
	xRotation = xRot;
	yRotation = yRot;
	zRotation = zRot;

	this->position = position;
}

Vector3D Camera::GetPosition() const
{
	return position;
}

void Camera::SetPosition(float x, float y, float z)
{
	position =  Vertex(x, y, z);
}

void Camera::SetRotation(float x, float y, float z)
{
	xRotation = x;
	yRotation = y;
	zRotation = z;
}

Matrix3x3 Camera::GetViewingMatrix()
{
	Matrix3x3 rMatrix = 
		XRotationMatrix(xRotation) * 
		YRotatationMatrix(yRotation) * 
		ZRotationMatrix(zRotation) *
		TranslateMatrix(-position.GetX(), -position.GetY(), -position.GetZ());
	return rMatrix;
}

