#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
	XMFLOAT4 color;

	Vertex() {};

	/// <summary>
	/// Vertex with Position
	/// </summary>
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = 0;
		uv.x = 0;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 0;
	}

	/// <summary>
	/// Vertex with Position and RGB Colour
	/// </summary>
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, UINT _r, UINT _g, UINT _b)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = 0;
		uv.x = 0;
		color.x = _r / 255.0f;
		color.y = _g / 255.0f;
		color.z = _b / 255.0f;
		color.w = 0;
	}

	/// <summary>
	/// Vertex with Position and UV
	/// </summary>
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _u, FLOAT _v)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		uv.x = _u;
		uv.x = _v;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 0;
	}

	/// <summary>
	/// Vertex with Position, normal and UV
	/// </summary>
	Vertex(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _nx, FLOAT _ny, FLOAT _nz, FLOAT _u, FLOAT _v)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
		normal.x = _nx;
		normal.y = _ny;
		normal.z = _nz;
		uv.x = _u;
		uv.x = _v;
		color.x = 1;
		color.y = 1;
		color.z = 1;
		color.w = 0;
	}
};