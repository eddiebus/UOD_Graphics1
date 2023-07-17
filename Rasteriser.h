#pragma once
#include "Framework.h"
#include "MyClasses/MD2Loader.h"
#include "MyClasses/Model.h"
#include "MyClasses/Camera.h"
#include "MyClasses/Transform.h"
#include "MyClasses/DirectionalLight.h"

#include <chrono>

class Rasteriser : public Framework
{
public:
	Rasteriser();
	
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void DrawWireFrame(const Bitmap& bitmap, bool Culling = true);
	void DrawSolidFlat(const Bitmap& bitmap, COLORREF colour = RGB(100,100,100));
	void DrawTri(Vertex input[3], const Bitmap& bitmap);
	void DrawFlatTri(Vertex input[3], const Bitmap& bitmap, COLORREF colour = RGB(0,255,0));

	void FillPolygonFlat(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour);
private:
	
	Model _Model;
	Transform ModelTransform;
	Camera mainCamera = Camera(0.0f, 0.0f, 0.0f,Vertex(0,0,-50));
	std::vector<DirectionalLight> DrLight;

	Matrix3x3 perspectiveMatrix;
	Matrix3x3 screenviewMatrix;

	void _FillBottomFlatTri(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour);
	void _FillTopFlatTri(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour);


	//Values to count which scene/feature is being shown
	std::vector<std::wstring> SceneName;
	int CurrentScene = 0;
	float ScenceTime = 0;
	int MaxSceneTime = 5000;
	float Speed = 2.0f;

	//DeltaTime
	std::chrono::steady_clock::time_point previousTickTime;
	std::chrono::steady_clock::time_point currentTickTime;
	float deltaTime = 0.0f;
};

