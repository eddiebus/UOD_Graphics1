#pragma once
#include "Model.h"
#include "Vector3D.h"
#include "Camera.h"
#include <algorithm>
#include <Windows.h>

Model::Model()
{
	ReflectionCoef = Vector3D(1, 1, 1);
}

Model::~Model()
{
}

const std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const std::vector<bool>& Model::GetCullPolygons()
{
	return _cullPolygon;
}

const std::vector<Vertex>& Model::GetVerticies()
{
	return _verticies;
}

const std::vector<Vertex>& Model::GetTransformedVertecies()
{
	return _transformedV;
}

void Model::AddVertex(float x, float y, float z)
{
	_verticies.push_back(
		Vertex(x, y, z)
	);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(
		Polygon3D(i0, i1, i2)
	);

	_cullPolygon.push_back(false);
}



size_t Model::GetVertextCount() const
{
	return _verticies.size();
}

Vector3D Model::GetRelfectionCoefficients()
{
	return ReflectionCoef;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

void Model::ApplyTransformToLocalVertecies(const Matrix3x3& Transform)
{
	_transformedV.clear();
	for (int i = 0; i < _verticies.size(); i++)
	{
		_transformedV.push_back(_verticies[i]);
		_transformedV[i] = Transform * _transformedV[i];
	}
}

void Model::ApplyTransformToTransformedVertecies(const Matrix3x3& Transform)
{
	for (int i = 0; i < _transformedV.size(); i++)
	{
		_transformedV[i] = Transform * _transformedV.at(i);
	}
}

void Model::DehomTransformedVertecies()
{
	for (int i = 0; i < _transformedV.size(); i++)
	{
		Vertex v = _transformedV.at(i);
		v.SetX(v.GetX() / v.GetW());
		v.SetY(v.GetY() / v.GetW());
		v.SetZ(v.GetZ() / v.GetW());
		v.SetW(v.GetW() / v.GetW());
		_transformedV[i] = v;
	}
}

//Find backfacing model polygons
void Model::CalculateBackfacesAndNormals(Camera inputCamera)
{
	for (int p = 0; p < _polygons.size(); p++)
	{
		
		Vertex v0 = _transformedV.at(_polygons.at(p).GetIndex(0));
		Vertex v1 = _transformedV.at(_polygons.at(p).GetIndex(1));
		Vertex v2 = _transformedV.at(_polygons.at(p).GetIndex(2));
		
		Vector3D vA = Vector3D(v0) - Vector3D(v1);
		Vector3D vB = Vector3D(v0) - Vector3D(v2);
		Vector3D abNormal = CrossProductVector(vB, vA);
		_polygons[p].SetNormal(abNormal);
		
		Vector3D eyeVector = Vector3D(v0) - inputCamera.GetPosition();
		
		float DotProduct = DotProductVector(abNormal, eyeVector);

		if (DotProduct < 0)
		{
			_polygons[p].SetCull(true);
		}
		else
		{
			_polygons[p].SetCull(false);
		}
	}
}

void Model::CalculateDirectionalLighting(const std::vector<DirectionalLight> lights)
{
	for (int p = 0; p < _polygons.size(); p++)
	{
		Vector3D totalRGB;
		_polygons[p].SetColour(Vector3D(0, 0, 0));

		for (int l = 0; l < lights.size(); l++)
		{
			Vector3D tempRGB = lights[l].GetColour();
			Vector3D refCoef = ReflectionCoef;

			tempRGB = tempRGB * refCoef;

			Vector3D NormalLightV = lights[l].GetDirection().GetNormalisedVector();
			Vector3D NormalPolyNV = _polygons[p].GetNormal().GetNormalisedVector();

			float dotProduct = DotProductVector(NormalLightV, NormalPolyNV);

			tempRGB = tempRGB * dotProduct;
			totalRGB = totalRGB + tempRGB;
		}

		//vector clamping
		float vecValues[3] = { totalRGB.GetX(), totalRGB.GetY(), totalRGB.GetZ() };
		for (int i = 0; i < 3; i++)
		{
			if (vecValues[i] > 255)
			{
				vecValues[i] = 255;
			}
			else if (vecValues[i] < 0)
			{
				vecValues[i] = 0;
			}
		}

		totalRGB = Vector3D(vecValues[0], vecValues[1], vecValues[2]);

		_polygons[p].SetColour(totalRGB);
	}
}

void Model::Sort()
{
	for (int p = 0; p < _polygons.size(); p++)
	{
		_polygons[p].SetDepthAverage(_transformedV);
	}
	std::sort(_polygons.begin(), _polygons.end(),DepthCompare);


}


