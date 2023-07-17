#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vertex& vertex)
{
	x = vertex.GetX();
	y = vertex.GetY();
	z = vertex.GetZ();
}

float Vector3D::GetMagnitude() const
{
	float result = 0.0f;
	float sum = (float)pow(x, 2) + (float)pow(y, 2) + (float)pow(z, 2);
	result = (float)sqrt(sum);
	return result;
}

float Vector3D::GetX() const
{
	return x;
}

float Vector3D::GetY() const
{
	return y;
}

float Vector3D::GetZ() const
{
	return z;
}

void Vector3D::SetX(float value)
{
	x = value;
}

void Vector3D::SetY(float value)
{
	y = value;
}

void Vector3D::SetZ(float value)
{
	z = value;
}

bool Vector3D::operator==(const Vector3D& otherV)
{
	return GetX() == otherV.GetX() 
		&& GetY() == otherV.GetY() 
		&& GetZ() == otherV.GetZ();
}

Vector3D& Vector3D::operator+(const Vector3D& otherV)
{
	x = x + otherV.GetX();
	y = y + otherV.GetY();
	z = z + otherV.GetZ();

	return *this;
}

Vector3D& Vector3D::operator-(const Vector3D& otherV)
{
	x = x - otherV.GetX();
	y = y - otherV.GetY();
	z = z - otherV.GetZ();

	return *this;
}


float DotProductVector(const Vector3D v1, const Vector3D v2)
{
	float rX = v1.GetX() * v2.GetX();
	float rY = v1.GetY() * v2.GetY();
	float rZ = v1.GetZ() * v2.GetZ();
	return rX + rY + rZ;
}

Vector3D CrossProductVector(const Vector3D v1, const Vector3D v2)
{
	float cX = (v1.GetY() * v2.GetZ()) - (v1.GetZ() * v2.GetY());
	float cY = (v1.GetZ() * v2.GetX()) - (v1.GetX() * v2.GetZ());
	float cZ = (v1.GetX() * v2.GetY()) - (v1.GetY() * v2.GetX());

	return Vector3D(cX,cY,cZ);
}
