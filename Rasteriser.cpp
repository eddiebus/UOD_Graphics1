#include "Rasteriser.h"
#include "MyClasses/Model.h"
#include "MyClasses/MyVertex.h"

#include <algorithm>

Rasteriser::Rasteriser()
{
}

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("chef.md2", _Model, &Model::AddPolygon, &Model::AddVertex))
	{
		OutputDebugString(L"Failed to load model.Check the file path.\n");
	}
	else
	{
		OutputDebugString(L"MD2 model load success.\n");
	}

	


	SceneName.push_back(L"Translation");
	SceneName.push_back(L"Scaling");
	SceneName.push_back(L"Rotation X-Axis");
	SceneName.push_back(L"Rotation Y-Axis");
	SceneName.push_back(L"Rotation Z-Axis");
	SceneName.push_back(L"BackFace-Culling");
	SceneName.push_back(L"Solid Shading");
	SceneName.push_back(L"Directional Lighting");

	previousTickTime = std::chrono::high_resolution_clock::now();

	return true;


}

void Rasteriser::Update(const Bitmap& bitmap)
{
	currentTickTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = currentTickTime  - previousTickTime;
	deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();
	previousTickTime = currentTickTime;

	Speed = deltaTime / 100;


	ScenceTime += deltaTime;
	//Change Scene after set amount of time
	if (ScenceTime > MaxSceneTime)
	{
		ScenceTime = 0;
		CurrentScene += 1;
		//Reset the transform
		ModelTransform = Transform();
		if (CurrentScene >= SceneName.size())
		{
			CurrentScene = 0;
			
		}
	}
	 
	DrLight.clear();
	//Scene Effects
	switch (CurrentScene)
	{
	case 0:
	{
		ModelTransform.Position.SetX(ModelTransform.Position.GetX() + Speed/10);
		ModelTransform.Position.SetY(ModelTransform.Position.GetY() + Speed/10);
		ModelTransform.Position.SetZ(ModelTransform.Position.GetZ() - Speed/10);
	}
	break;
	case 1:
	{
		ModelTransform.Scale.SetX(ModelTransform.Scale.GetX() - Speed/200);
		ModelTransform.Scale.SetY(ModelTransform.Scale.GetX());
		ModelTransform.Scale.SetZ(ModelTransform.Scale.GetX());
	}
	break;
	case 2:
	{
		ModelTransform.Rotation.SetX(ModelTransform.Rotation.GetX() + Speed * 5);
	}
	break;
	case 3:
	{
		ModelTransform.Rotation.SetY(ModelTransform.Rotation.GetY() + Speed * 5);
	}
	break;
	case 4:
	{
		ModelTransform.Rotation.SetZ(ModelTransform.Rotation.GetZ() + Speed * 5);
	}
	break;
	case 5:
	{
		ModelTransform.Rotation.SetY(ModelTransform.Rotation.GetY() + Speed * 5);
	}
	case 6:
	{
		ModelTransform.Rotation.SetY(ModelTransform.Rotation.GetY() + Speed * 5);

		DrLight.push_back(DirectionalLight(
			Vector3D(0, 0, -1),
			Vector3D(150, 0, 0)
		));
	}
	break;
	case 7:
	{
		ModelTransform.Rotation.SetY(ModelTransform.Rotation.GetY() + Speed * 5);

		DrLight.push_back(DirectionalLight(
			Vector3D(0, 0, -1),
			Vector3D(150, 0, 0)
		));

		DrLight.push_back(DirectionalLight(
			Vector3D(0.5f, 0, -1),
			Vector3D(0, 50, 0)
		));
	}
	break;
	default:
		break;
	}

	perspectiveMatrix = PerspectiveProjectionMatrix(1, (float)bitmap.GetWidth()/(float)bitmap.GetHeight() );
	screenviewMatrix = ScreenTransformMatrix((float)bitmap.GetWidth(),(float)bitmap.GetHeight(), 1);
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	HBRUSH bgBrush = CreateSolidBrush(RGB(200, 200, 200));
	bitmap.Clear(bgBrush);
	mainCamera.SetPosition(0, 0, 50);
	HFONT textFont = CreateFont(
		30, 20,
		0, 0,
		0,
		FW_DONTCARE,
		false,
		false,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		NULL
	);
	SelectObject(bitmap.GetDC(), textFont);
	RECT textRect = { 0 };
	textRect.right = bitmap.GetWidth();
	textRect.bottom = 100;
	DrawText(bitmap.GetDC(), SceneName.at(CurrentScene).c_str(), -1, &textRect, (DT_LEFT));

	switch (CurrentScene)
	{
	case 0:
	{
		DrawWireFrame(bitmap,false);
	}
	case 1:
	{
		DrawWireFrame(bitmap, false);

	}
	case 2:
	{
		DrawWireFrame(bitmap, false);

	}
	case 3:
	{
		DrawWireFrame(bitmap, false);

	}
	break;
	case 4:
	{
		DrawWireFrame(bitmap, false);

	}
	break;
	case 5:
	{
		DrawWireFrame(bitmap);
	}
	break;
	default:
	{
		DrawSolidFlat(bitmap);
	}
		break;
	}
	DeleteObject(bgBrush);
	DeleteObject(textFont);
}

void Rasteriser::DrawWireFrame(const Bitmap& bitmap, bool Culling)
{
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(bitmap.GetDC(),Pen);
	_Model.ApplyTransformToLocalVertecies(ModelTransform.GetTransformMatrix());
	_Model.CalculateBackfacesAndNormals(mainCamera);
	_Model.ApplyTransformToTransformedVertecies(mainCamera.GetViewingMatrix());
	_Model.Sort();
	_Model.ApplyTransformToTransformedVertecies(perspectiveMatrix);
	_Model.DehomTransformedVertecies();
	_Model.ApplyTransformToTransformedVertecies(screenviewMatrix);

	std::vector<Polygon3D> polys = _Model.GetPolygons();
	for (int i = 0; i < polys.size(); i++)
	{
		bool toDraw = true;
		if (Culling && (polys.at(i).GetCull() == true))
		{
			toDraw = false;
		}

		if (toDraw)
		{
			Polygon3D currentPoly = polys.at(i);
			Vertex Tri[3] = { Vertex() };
			Tri[0] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(0));
			Tri[1] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(1));
			Tri[2] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(2));
			DrawTri(Tri, bitmap);
		}
	}

	DeleteObject(Pen);
}

void Rasteriser::DrawSolidFlat(const Bitmap& bitmap,COLORREF colour)
{
	_Model.ApplyTransformToLocalVertecies(ModelTransform.GetTransformMatrix());
	_Model.CalculateBackfacesAndNormals(mainCamera);
	_Model.CalculateDirectionalLighting(DrLight);
	_Model.ApplyTransformToTransformedVertecies(mainCamera.GetViewingMatrix());

	_Model.Sort();
	_Model.ApplyTransformToTransformedVertecies(perspectiveMatrix);


	_Model.DehomTransformedVertecies();
	_Model.ApplyTransformToTransformedVertecies(screenviewMatrix);

	std::vector<Polygon3D> polys = _Model.GetPolygons();
	for (int i = 0; i < polys.size(); i++)
	{
		if (polys.at(i).GetCull() == false)
		{
			Polygon3D currentPoly = polys.at(i);
			Vertex Tri[3] = { Vertex() };
			Tri[0] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(0));
			Tri[1] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(1));
			Tri[2] = _Model.GetTransformedVertecies().at(currentPoly.GetIndex(2));
			Vector3D vColour = Vector3D(
				currentPoly.GetColour()
			);


			FillPolygonFlat(bitmap,Tri[0],Tri[1],Tri[2],RGB(vColour.GetX(),vColour.GetY(),vColour.GetZ()));
		}
	}
}

void Rasteriser::DrawTri(Vertex input[3], const Bitmap& bitmap)
{
	for (int i = 0; i < 3; i++)
	{
		int nextI = i + 1;
		if (nextI > 2) {
			nextI = 0;
		}
		HDC TargetDC = bitmap.GetDC();
		MoveToEx(TargetDC, (int)input[i].GetX(), (int)input[i].GetY(), NULL);
		LineTo(TargetDC, (int)input[nextI].GetX(),(int)input[nextI].GetY());
	}
}

void Rasteriser::DrawFlatTri(Vertex input[3], const Bitmap& bitmap, COLORREF colour)
{
	HDC hdc = bitmap.GetDC();
	HPEN pen = CreatePen(PS_SOLID, 2, colour);
	HBRUSH brush = CreateSolidBrush(colour);

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	POINT points[3];
	for (int i = 0; i < 3; i++)
	{
		points[i].x = (LONG)input[i].GetX();
		points[i].y = (LONG)input[i].GetY();
	}

	Polygon(hdc, points, 3);
	DeleteObject(pen);
	DeleteObject(brush);
}

void Rasteriser::FillPolygonFlat(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	Vertex input[3] = { v1,v2,v3 };
	//Sorting Vertecies order so first == highest
	for (int i = 0; i < 2;)
	{
		if (input[i].GetY() > input[i + 1].GetY())
		{
			Vertex tempV = input[i];
			input[i] = input[i + 1];
			input[i + 1] = tempV;
			
			i = 0;
		}
		else
		{
			i++;
		}
	}

	v1 = input[0];
	v2 = input[1];
	v3 = input[2];

	//Check if triangle is top flat or bottom flat
	if (v2.GetY() == v3.GetY())
	{
		_FillBottomFlatTri(bitmap, v1, v2, v3, colour);
	}
	else if (v1.GetY() == v2.GetY())
	{
		_FillTopFlatTri(bitmap, v1, v2, v3, colour);
	}
	//Triangle is neither. Cut it into two 
	else
	{
		Vertex tempV = Vertex(
			(v1.GetX() + ((v2.GetY() - v1.GetY()) / (v3.GetY() - v1.GetY())) * (v3.GetX() - v1.GetX())),
			v2.GetY(),
			1.0f,
			0.0f
		);

		_FillBottomFlatTri(bitmap, v1, v2, tempV, colour);
		_FillTopFlatTri(bitmap, v2, tempV, v3,colour);
	}
}

void Rasteriser::_FillBottomFlatTri(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	HDC targetDC = bitmap.GetDC();

	HPEN Pen = CreatePen(PS_SOLID, 3, colour);
	SelectObject(targetDC, Pen);

	float slope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float x1 = v1.GetX();
	float x2 = v1.GetX() + 0.5f;

	for (int scanLineY = (int)v1.GetY(); scanLineY < (int)v2.GetY(); scanLineY++)
	{
		MoveToEx(targetDC, (int)x1, scanLineY,NULL);
		LineTo(targetDC, (int)x2, scanLineY);
		x1 += slope1;
		x2 += slope2;
	}

	DeleteObject(Pen);
}

void Rasteriser::_FillTopFlatTri(const Bitmap& bitmap, Vertex v1, Vertex v2, Vertex v3, COLORREF colour)
{
	HDC targetDC = bitmap.GetDC();

	HPEN Pen = CreatePen(PS_SOLID, 3, colour);
	SelectObject(targetDC, Pen);

	float slope1 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v2.GetX()) / (v3.GetY() - v2.GetY());

	float x1 = v3.GetX();
	float x2 = v3.GetX() + 0.5f;

	for (int scanLineY = (int)v3.GetY(); scanLineY > (int)v1.GetY(); scanLineY--)
	{
		MoveToEx(targetDC, (int)x1, scanLineY, NULL);
		LineTo(targetDC, (int)x2, scanLineY);
		x1 -= slope1;
		x2 -= slope2;
	}
	DeleteObject(Pen);
}




Rasteriser app; 

