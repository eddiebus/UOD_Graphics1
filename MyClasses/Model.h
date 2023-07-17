#pragma once
#include <vector>
#include "Polygon3D.h"
#include "MyVertex.h"
#include "MyMatrix.h"
#include "Camera.h"
#include "DirectionalLight.h"

class Model
{
public:
	Model();
	~Model();

	//Accessors
	const std::vector<Polygon3D>& GetPolygons();
	const std::vector<bool>& GetCullPolygons();
	const std::vector<Vertex>& GetVerticies();
	const std::vector<Vertex>& GetTransformedVertecies();
	size_t GetPolygonCount() const;
	size_t GetVertextCount() const;
	Vector3D GetRelfectionCoefficients();

	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	//Transform Local(Stored) vertecies
	void ApplyTransformToLocalVertecies(const Matrix3x3& transform);
	//Transform Temporary transformed vertecies
	void ApplyTransformToTransformedVertecies(const Matrix3x3& transform);
	void DehomTransformedVertecies();

	void CalculateBackfacesAndNormals(Camera inputCamera);
	void CalculateDirectionalLighting(const std::vector<DirectionalLight> lights);

	void Sort();
private:
	//Function to be used by std::sort
	std::vector<Polygon3D> _polygons;
	std::vector<bool> _cullPolygon;
	std::vector<Vertex> _verticies;
	std::vector<Vertex> _transformedV;
	Vector3D ReflectionCoef;
};

