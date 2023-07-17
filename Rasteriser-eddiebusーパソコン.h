#pragma once
#include "Framework.h"
#include "MyClasses/MD2Loader.h"
#include "MyClasses/Model.h"
#include "MyClasses//Camera.h"
#include "MyClasses//Transform.h"

class Rasteriser : public Framework
{
public:
	Rasteriser();
	
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void DrawWireFrame(const Bitmap& bitmap);
	void DrawSolidFlat(const Bitmap& bitmap, COLORREF colour = RGB(0,255,0));
	void DrawTri(Vertex input[3], const Bitmap& bitmap);
	void DrawFlatTri(Vertex input[3], const Bitmap& bitmap, COLORREF colour = RGB(0,255,0));
private:
	
	Model _Model;
	Transform ModelTransform;
	Camera mainCamera = Camera(0.0f, 0.0f, 0.0f,Vertex(0,0,-50));
	Matrix3x3 perspectiveMatrix;
	Matrix3x3 screenviewMatrix;


};

