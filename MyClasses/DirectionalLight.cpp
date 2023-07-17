#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	colour = Vector3D(0, 0, 0);
	direction = Vector3D(0, 0, 0);
}

DirectionalLight::DirectionalLight(Vector3D direction, Vector3D colour)
{
	this->direction = direction;
	this->colour = colour;
}

void DirectionalLight::SetColour(Vector3D colour)
{
	this->colour = colour; 
}

void DirectionalLight::SetDirection(Vector3D direction)
{
	this->direction = direction;
}

Vector3D DirectionalLight::GetColour() const
{
	return colour;
}

Vector3D DirectionalLight::GetDirection() const
{
	return direction;
}

DirectionalLight& DirectionalLight::operator=(const DirectionalLight& otherLight)
{
	colour = otherLight.colour;
	direction = otherLight.direction;
	return *this;
}
