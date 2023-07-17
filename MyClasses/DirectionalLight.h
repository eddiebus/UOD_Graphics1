#pragma once

#include "Vector3D.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(Vector3D direction, Vector3D colour);

	void SetColour(Vector3D colour);
	void SetDirection(Vector3D direction);

	Vector3D GetColour() const;
	Vector3D GetDirection() const;

	DirectionalLight& operator=(const DirectionalLight& otherLight);
private:
	Vector3D colour;
	Vector3D direction;
};

