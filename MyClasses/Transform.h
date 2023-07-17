#pragma once
#include "MyVertex.h"
#include "MyMatrix.h"


class Transform
{
public:
	Transform();
	Vertex Scale = Vertex(1.0f, 1.0f, 1.0f);
	Vertex Rotation = Vertex(0.0f, 0.0f, 0.0f);
	Vertex Position = Vertex(0.0f, 0.0f, 0.0f);
	Matrix3x3 GetTransformMatrix();
};


