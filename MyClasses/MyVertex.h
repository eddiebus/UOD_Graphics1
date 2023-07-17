#pragma once

#include <iostream>
#include <string>


class Vertex
{
public:
	Vertex();

	Vertex(float x, float y, float z, float w = 1);

	float GetX() const;

	float GetY() const;

	float GetZ() const;

	float GetW() const;

	void SetX(float value);

	void SetY(float value);

	void SetZ(float value);

	void SetW(float value);

	Vertex& operator+(const Vertex& otherV);

	Vertex& operator=(const Vertex& otherV);

	bool operator==(const Vertex& otherV);


	void DescribeSelf();

private:
	float x;
	float y;
	float z;
	float w = 1;
};