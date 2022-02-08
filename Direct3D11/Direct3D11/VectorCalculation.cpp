#include "VectorCalculation.h"

FLOAT VectorCalculation::Cal_DotProduct(XMFLOAT3 _vectorLeft, XMFLOAT3 _vectorRight)
{
	FLOAT dotProduct;

	dotProduct = (_vectorLeft.x * _vectorRight.x) + (_vectorLeft.y * _vectorRight.y) + (_vectorLeft.z * _vectorRight.z);

	return dotProduct;
}

FLOAT VectorCalculation::Cal_SqrMagnitute(XMFLOAT3 _vector)
{
	FLOAT sqrMagnitude = (_vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z);

	sqrMagnitude = sqrt(sqrMagnitude);

	return sqrMagnitude;
}

XMFLOAT3 VectorCalculation::Cal_Scale(XMFLOAT3 _vector)
{
	XMFLOAT3 scaledVector = _vector;

	scaledVector.x *= _vector.x;
	scaledVector.y *= _vector.y;
	scaledVector.z *= _vector.z;

	return scaledVector;
}

XMFLOAT3 VectorCalculation::Cal_CrossPorduct(XMFLOAT3 _vectorA, XMFLOAT3 _vectorB)
{
	XMFLOAT3 crossVec;

	crossVec = XMFLOAT3(_vectorA.y * _vectorB.z - _vectorA.z * _vectorB.y,
						_vectorA.z * _vectorB.x - _vectorA.x * _vectorB.z,
						_vectorA.x * _vectorB.y - _vectorA.y * _vectorB.x);

	return crossVec;
}

FLOAT VectorCalculation::Cal_Angle(FLOAT _dotProduct, FLOAT _lenghtA, FLOAT _lenghtB)
{
	FLOAT angle;

	angle = (_dotProduct / (_lenghtA * _lenghtB));

	angle = acos(angle);

	return angle;
}
