/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Vector3D.cpp
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date Sep 23, 2015
\brief The implementation file for the Vector operations.

Language: C, Visual Studio 2013
Project: CS529_Vector3D.c_1

/* End Header
*******************************************************************/

#include "Vector3D.h"

#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795
// ---------------------------------------------------------------------------

void Vector3DZero(Vector3D *pResult)
{
	pResult->x = pResult->y = pResult->z = 0;
	// Assumes the vector is a point currently
	// TODO : Set w to 0 when a direction
	pResult->w = 1;
}

// ---------------------------------------------------------------------------

void Vector3DSet(Vector3D *pResult, float x, float y, float z, float w)
{
	pResult->x = x;
	pResult->y = y;
	pResult->z = z;
	pResult->w = w;
}

// ---------------------------------------------------------------------------

void Vector3DNeg(Vector3D *pResult, Vector3D *pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
	pResult->z = -pVec0->z;
}

// ---------------------------------------------------------------------------

void Vector3DAdd(Vector3D & pResult, const Vector3D & pVec0, const Vector3D & pVec1)
{
	pResult.x = pVec0.x + pVec1.x;
	pResult.y = pVec0.y + pVec1.y;
	pResult.z = pVec0.z + pVec1.z;
}

// ---------------------------------------------------------------------------

void Vector3DSub(Vector3D & pResult, Vector3D const & pVec0, Vector3D const & pVec1)
{
	pResult.x = pVec0.x - pVec1.x;
	pResult.y = pVec0.y - pVec1.y;
	pResult.z = pVec0.z - pVec1.z;
}

// ---------------------------------------------------------------------------

void Vector3DNormalize(Vector3D  & pResult, Vector3D const & pVec0)
{
	float length = sqrt(powf(pVec0.x, 2) + powf(pVec0.y, 2) + powf(pVec0.z, 2));
	pResult.x = pVec0.x / length;
	pResult.y = pVec0.y / length;
	pResult.z = pVec0.z / length;
}

// ---------------------------------------------------------------------------

void Vector3DScale(Vector3D *pResult, Vector3D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
	pResult->z = pVec0->z * c;
}

// ---------------------------------------------------------------------------

void Vector3DScaleAdd(Vector3D *pResult, Vector3D *pVec0, Vector3D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) + pVec1->x;
	pResult->y = (pVec0->y * c) + pVec1->y;
	pResult->z = (pVec0->z * c) + pVec1->z;
}

// ---------------------------------------------------------------------------

void Vector3DScaleSub(Vector3D *pResult, Vector3D *pVec0, Vector3D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) - pVec1->x;
	pResult->y = (pVec0->y * c) - pVec1->y;
	pResult->z = (pVec0->z * c) - pVec1->z;
}

// ---------------------------------------------------------------------------

float Vector3DLength(Vector3D const & pVec0)
{
	return sqrt(powf(pVec0.x, 2) + powf(pVec0.y, 2) + powf(pVec0.z, 2));	
}

// ---------------------------------------------------------------------------

float Vector3DSquareLength(Vector3D *pVec0)
{
	return powf(pVec0->x, 2) + powf(pVec0->y, 2) +  powf(pVec0->z, 2);
	
}

// ---------------------------------------------------------------------------

float Vector3DDistance(Vector3D const & pVec0, Vector3D const & pVec1)
{
	return sqrt(powf(pVec1.x - pVec0.x, 2) + powf(pVec1.y - pVec0.y, 2) + powf(pVec1.z - pVec0.z, 2));
	 
}

// ---------------------------------------------------------------------------

float Vector3DSquareDistance(const Vector3D & pVec0, const Vector3D & pVec1)
{
	return powf(pVec1.x - pVec0.x, 2) + powf(pVec1.y - pVec0.y, 2) + powf(pVec1.z - pVec0.z, 2);
}

// ---------------------------------------------------------------------------

float Vector3DDotProduct(Vector3D const & pVec0, Vector3D const & pVec1)
{
	return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y) + (pVec0.z * pVec1.z);
	
}

// ---------------------------------------------------------------------------

void Vector3DFromAngleDeg(Vector3D *pResult, float angle)
{
	pResult->y = sin((angle*PI) / 180);
	pResult->x = cos((angle*PI) / 180);
}

// ---------------------------------------------------------------------------

void Vector3DFromAngleRad(Vector3D *pResult, float angle)
{
	pResult->y = sin(angle);
	pResult->x = cos(angle);
}

// ---------------------------------------------------------------------------

Vector3D Vector3DCrossProduct(Vector3D *pVec0, Vector3D *pVec1)
{
	return Vector3D(pVec0->y*pVec1->z - pVec0->z*pVec1->y, pVec0->z* pVec1->x - pVec0->x*pVec1->z, pVec0->x*pVec1->y - pVec0->y*pVec1->x, 1.0f);
}

// ---------------------------------------------------------------------------

Vector3D const & Vector3DMaxBetween(Vector3D const & vec1, Vector3D const & vec2)
{
	bool vec2greater = false;
	// First establishes the condition if vec2 is greater with x coordinate check
	if (vec2.x > vec1.x)
		vec2greater = true;
	// Then checks for y coordinate if the condition remains true
	if (vec2.y > vec1.y)
		vec2greater = true;
	// If false, the bool is set to false again
	else if (vec1.y > vec2.y)
		vec2greater = false;
	// Repeat process for z coordinate
	if (vec2.z > vec1.z)
		vec2greater = true;
	else if (vec1.z > vec2.z)
		vec2greater = false;
	// Based on vec2greater, return vec1 or vec2 as result
	if (vec2greater)
		return vec2;
	else
		return vec1;
}
// ---------------------------------------------------------------------------
float Vector3DMax(Vector3D const & vec)
{
	float temp = 0.0f;
	temp = vec.x;
	if (vec.y > temp)
		temp = vec.y;
	if (vec.z > temp)
		temp = vec.z;
	return temp;
}