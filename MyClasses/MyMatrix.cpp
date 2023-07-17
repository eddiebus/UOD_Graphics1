#include "MyMatrix.h"

float math::ToRadians(float input)
{
	return input * (3.14f / 180);
}


/*
* Matrix Class for 3D (4x4) transformation
*/
Matrix3x3::Matrix3x3()
{
	for (int i = 0; i < Width; i++)
	{
		Value[i][i] = 1;
	}
}

Matrix3x3::Matrix3x3(std::initializer_list<float> input)
{
	const float* input_begin = input.begin();

	for (int row = 0, col = 0; row < Width;)
	{
		int index = (row * Width) + col;

		if (index < input.size())
		{
			Value[row][col] = input_begin[index];
		}

		col += 1;
		if (col >= Width)
		{
			col = 0;
			row += 1;
		}
	}

}
Matrix3x3::Matrix3x3(const Matrix3x3& other)
{
	this->operator=(other);
}

float Matrix3x3::Get(int row, int col)
{
	if (row > Width) { row = Width; }
	else if (row < 0) { row = 0; }

	if (col > Width) { col = Width; }
	else if (col < 0) { col = 0; }

	return Value[row][col];
}

void Matrix3x3::Set(int row, int col, float newValue)
{
	if (row > Width) { row = Width; }
	else if (row < 0) { row = 0; }

	if (col > Width) { col = Width; }
	else if (col < 0) { col = 0; }

	Value[row][col] = newValue;
}

void Matrix3x3::DescribeSelf()
{
	std::cout << "We have a Matrix class here.Its values are: \n";
	for (int row = 0, col = 0; row < Width;)
	{
		std::cout << std::to_string(Value[row][col]) + " || ";

		if (col == Width - 1)
		{
			std::cout << "\n";
			row += 1;
			col = 0;
		}
		else
		{
			col += 1;
		}
	}
}

Matrix3x3& Matrix3x3::operator= (const Matrix3x3& other)
{

	for (int row = 0, col = 0; row < Width;)
	{
		Value[row][col] = other.Value[row][col];
		col += 1;
		if (col >= Width)
		{
			col = 0;
			row += 1;
		}
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator* (const Matrix3x3& other)
{
	Matrix3x3 NewMatrix;
	for (int row = 0; row < Width; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			float newValue = 0;
			newValue += Value[row][0] * other.Value[0][col];
			newValue += Value[row][1] * other.Value[1][col];
			newValue += Value[row][2] * other.Value[2][col];
			newValue += Value[row][3] * other.Value[3][col];
			NewMatrix.Value[row][col] = newValue;
		}
	}
	*this = NewMatrix;

	return *this;
}

Vertex Matrix3x3::operator*(Vertex otherVertex) const
	{
		Vertex returnV;
		returnV.SetX(Value[0][0] * otherVertex.GetX() + Value[0][1] * otherVertex.GetY() + Value[0][2] * otherVertex.GetZ() + Value[0][3] * otherVertex.GetW());
		returnV.SetY(Value[1][0] * otherVertex.GetX() + Value[1][1] * otherVertex.GetY() + Value[1][2] * otherVertex.GetZ() + Value[1][3] * otherVertex.GetW());
		returnV.SetZ(Value[2][0] * otherVertex.GetX() + Value[2][1] * otherVertex.GetY() + Value[2][2] * otherVertex.GetZ() + Value[2][3] * otherVertex.GetW());
		returnV.SetW(Value[3][0] * otherVertex.GetX() + Value[3][1] * otherVertex.GetY() + Value[3][2] * otherVertex.GetZ() + Value[3][3] * otherVertex.GetW());

		return returnV;
	}

bool Matrix3x3::operator== (const Matrix3x3& other)
	{
		int CellCount = Width * Width;
		int EqualCount = 0;
		for (int row = 0, column = 0; row < Width;)
		{
			if (Value[row][column] == other.Value[row][column])
			{
				EqualCount += 1;
			}

			column += 1;
			if (column >= Width)
			{
				column = 0;
				row += 1;
			}
		}

		if (EqualCount == CellCount)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

Matrix3x3 ScaleMatrix(float x, float y, float z)
{
	return Matrix3x3({
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
		});
}

Matrix3x3 TranslateMatrix(float x, float y,float z)
{
	return Matrix3x3({
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1 }
	);
}

Matrix3x3 XRotationMatrix(float angle)
{
	float rA = math::ToRadians(angle);

	return Matrix3x3({
		1,0,0,0,
		0,cos(rA),sin(rA),0,
		0,-sin(rA),cos(rA),0,
		0,0,0,1
		});

}

Matrix3x3 YRotatationMatrix(float angle)
{
	float rA = math::ToRadians(angle);

	return Matrix3x3({
		cos(rA),0,-sin(rA),0,
		0,1,0,0,
		sin(rA),0,cos(rA),0,
		0,0,0,1
		});
}

Matrix3x3 ZRotationMatrix(float angle)
{
	float rA = math::ToRadians(angle);

	return Matrix3x3({
		cos(rA),sin(rA),0,0,
		-sin(rA),cos(rA),0,0,
		0,0,1,0,
		0,0,0,1
		});
}

Matrix3x3 PerspectiveProjectionMatrix(float d, float aspectRatio)
{
	return Matrix3x3({
	d/aspectRatio,0,0,0,
	0,d,0,0,
	0,0,d,0,
	0,0,1,0
		});
}

Matrix3x3 ScreenTransformMatrix(float width, float height, float d)
{
	Matrix3x3 rMatrix = Matrix3x3({
		width/2,0,0,width/2,
		0,height/2,0,height/2,
		0,0,d/2,d/2,
		0,0,0,1
		});

	return rMatrix;
}


