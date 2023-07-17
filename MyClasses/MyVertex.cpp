#include "MyVertex.h"
#include <iostream>
#include <string>

Vertex::Vertex()
{
	x = 0;
	y = 0;
	z = 0;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vertex::GetX() const
{
	return x;
}

float Vertex::GetY() const
{
	return y;
}

float Vertex::GetZ() const
{
	return z;
}

float Vertex::GetW() const 
{
	return w;
}

void Vertex::SetX(float value)
{
	x = value;
}

void Vertex::SetY(float value)
{
	y = value;
}

void Vertex::SetZ(float value)
{
	z = value;
}

void Vertex::SetW(float value)
{
	w = value;
}

Vertex& Vertex::operator+(const Vertex& otherV)
{
	this->x += otherV.GetX();
	this->y += otherV.GetY();
	this->z += otherV.GetZ();
	this->w += otherV.GetW();

	return *this;
}

Vertex& Vertex::operator=(const Vertex& otherV)
{
	this->x = otherV.x;
	this->y = otherV.y;
	this->z = otherV.z;
	this->w = otherV.w;

	return *this;
}

bool Vertex::operator==(const Vertex& otherV)
{
	int checkCount = 0;
	checkCount += x == otherV.x;
	checkCount += y == otherV.y;
	checkCount += z == otherV.z;
	checkCount += w == otherV.w;

	return checkCount == 4;
}

void Vertex::DescribeSelf()
{
	std::cout << "This is a vertex class with values:\n";
	std::cout << x << "\n";
	std::cout << y << "\n";
	std::cout << w << "\n";
}