#pragma once
#include "Window.h"
#include <vector>
#include <iostream>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

class VectorCalculation
{
public:

	FLOAT Cal_DotProduct(XMFLOAT3 _vectorLeft, XMFLOAT3 _vectorRight);
	FLOAT Cal_SqrMagnitute(XMFLOAT3 _vector);
	XMFLOAT3 Cal_Scale(XMFLOAT3 _vector);
	XMFLOAT3 Cal_CrossPorduct(XMFLOAT3 _vectorA, XMFLOAT3 _vectorB);
	FLOAT Cal_Angle(FLOAT _dotProduct, FLOAT _lenghtA, FLOAT _lenghtB);
};

