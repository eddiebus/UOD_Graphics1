#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indecies[0] = 0;
	_indecies[1] = 0;
	_indecies[2] = 0;

	zAverage = 0.0f;
	_toCull = false;
	colour = Vector3D(0, 0, 0);
	normal = Vector3D(0, 0, 0);
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& otherPoly)
{
	operator=(otherPoly);
}


Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indecies[0] = index0;
	_indecies[1] = index1;
	_indecies[2] = index2;

	zAverage = 0.0f;
	_toCull = false;
	colour = Vector3D(0, 0, 0);
	normal = Vector3D(0, 0, 0);
}

int Polygon3D::GetIndex(int index) const
{
	if (index > 2) { index = 2; }
	else if (index < 0) { index = 0; }
	return _indecies[index];
}

void Polygon3D::SetNormal(Vector3D normal)
{
	this->normal = normal;
}

Vector3D Polygon3D::GetNormal() const
{
	return normal;
}

void Polygon3D::SetDepthAverage(std::vector<Vertex>& ModelVertecies)
{
	//No vertecies in the model. Return
	if (ModelVertecies.size() < 1)
	{
		return;
	}
	
	float zTotal = ModelVertecies.at(_indecies[0]).GetZ() +
		ModelVertecies.at(_indecies[1]).GetZ() +
		ModelVertecies.at(_indecies[2]).GetZ();

	zAverage = zTotal / 3;

}

float Polygon3D::GetDepthAverage() const
{
	return zAverage;
}

void Polygon3D::SetCull(bool input)
{
	_toCull = input;
}

bool Polygon3D::GetCull() const
{
	return _toCull;
}

void Polygon3D::SetColour(Vector3D colour)
{
	this->colour = colour;
}

Vector3D Polygon3D::GetColour() const
{
	return colour;
}

Polygon3D& Polygon3D::operator=(const Polygon3D& otherPoly)
{
	for (int i = 0; i < 3; i++)
	{
		_indecies[i] = otherPoly._indecies[i];
	}

	zAverage = otherPoly.zAverage;
	_toCull = otherPoly._toCull;
	colour = otherPoly.colour;
	normal = otherPoly.normal;

	return *this;
}

bool DepthCompare(const Polygon3D& input1, const Polygon3D& input2)
{
	return input1.GetDepthAverage() < input2.GetDepthAverage();
}
