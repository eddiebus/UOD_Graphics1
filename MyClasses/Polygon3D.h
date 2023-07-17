#pragma once
#include <vector>
#include "MyVertex.h"
#include "Vector3D.h"

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& otherPoly);

	int GetIndex(int) const;
	
	void SetColour(Vector3D colour);
	Vector3D GetColour() const;

	void SetNormal(Vector3D normal);
	Vector3D GetNormal() const;

	// Set the depth average of poly based on model vertecies
	void SetDepthAverage(std::vector<Vertex>& ModelVertecies);
	float GetDepthAverage() const;

	void SetCull(bool);
	bool GetCull() const;


	Polygon3D& operator= (const Polygon3D& otherPoly);
private:
	int _indecies[3];
	float zAverage = 0;
	bool _toCull = false;
	Vector3D normal; 
	Vector3D colour = Vector3D(0, 0, 0);
};

bool DepthCompare(const Polygon3D& input1, const Polygon3D& input2);