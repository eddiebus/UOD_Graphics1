#pragma once
#include "MyVertex.h"
#include <iostream>
#include <string>

namespace math
{
	float ToRadians(float input);
}

class Matrix3x3
{
public:
	//Default Constructor
	//Creates Identity Matrix.
	Matrix3x3();

	Matrix3x3(std::initializer_list<float> input);

	//Copy Constructor
	Matrix3x3(const Matrix3x3& other);

	//Get a value from a single cell
	float Get(int row, int col);

	//Set a value in a single cell
	void Set(int row, int col, float newValue);

	void DescribeSelf();

	//Set this matrix equal to another
	Matrix3x3& operator= (const Matrix3x3& other);

	Matrix3x3& operator*(const Matrix3x3& other);

	Vertex operator* (Vertex otherVertex) const;

	bool operator== (const Matrix3x3& other);
private:
	const int Width = 4;
	float Value[4][4] = { 0 };
};

Matrix3x3 ScaleMatrix(float x, float y, float z);

Matrix3x3 TranslateMatrix(float x, float y,float z);

Matrix3x3 XRotationMatrix(float angle);

Matrix3x3 YRotatationMatrix(float angle);

Matrix3x3 ZRotationMatrix(float angle);

Matrix3x3 PerspectiveProjectionMatrix(float depth, float aspectRatio);

Matrix3x3 ScreenTransformMatrix(float width, float height, float depth);


