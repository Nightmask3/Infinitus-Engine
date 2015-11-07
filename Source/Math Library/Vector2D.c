/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Vector2D.cpp
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date Sep 23, 2015
\brief The implementation file for the Vector operations.

Language: C, Visual Studio 2013
Project: CS529_Vector2D.c_1

/* End Header
*******************************************************************/

#include "Vector2D.h"

#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795
// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float length = sqrt(powf(pVec0->x, 2) + powf(pVec0->y, 2));
	pResult->x = pVec0->x / length;
	pResult->y = pVec0->y / length;
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) + pVec1->x;
	pResult->y = (pVec0->y * c) + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) - pVec1->x;
	pResult->y = (pVec0->y * c) - pVec1->y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	return sqrt(powf(pVec0->x, 2) + powf(pVec0->y, 2));
	
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return powf(pVec0->x, 2) + powf(pVec0->y, 2);
	
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return sqrt(powf(pVec1->x - pVec0->x, 2) + powf(pVec1->y - pVec0->y, 2));
	 
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return powf(pVec1->x - pVec0->x, 2) + powf(pVec1->y - pVec0->y, 2);
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
	
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	pResult->y = sin((angle*PI) / 180);
	pResult->x = cos((angle*PI) / 180);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->y = sin(angle);
	pResult->x = cos(angle);
}

// ---------------------------------------------------------------------------
