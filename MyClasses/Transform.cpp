#include "MyMatrix.h"
#include "Transform.h"

Transform::Transform()
{
	Scale = Vertex(1.0f, 1.0f, 1.0f);
	Rotation = Vertex(0.0f, 0.0f, 0.0f);
	Position = Vertex(0.0f, 0.0f, 0.0f);
}

Matrix3x3 Transform::GetTransformMatrix()
{
	Matrix3x3 scaleMatrix = ScaleMatrix(Scale.GetX(), Scale.GetY(), Scale.GetZ());

	Matrix3x3 xRMatrix = XRotationMatrix(Rotation.GetX());
	Matrix3x3 yRMatrix = YRotatationMatrix(Rotation.GetY());
	Matrix3x3 zRMatrix = ZRotationMatrix(Rotation.GetZ());
	Matrix3x3 rotationMatrix = xRMatrix * yRMatrix * zRMatrix;

	Matrix3x3 translateMatrix = TranslateMatrix(Position.GetX(), Position.GetY(), Position.GetZ());
	
	Matrix3x3 rMatrix = scaleMatrix * rotationMatrix * translateMatrix;
	return rMatrix;
}






