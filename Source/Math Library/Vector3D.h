/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Vector3D.h
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date Sep 23, 2015
\brief The headerfile for all the Vector operations.

Language: C, Visual Studio 2013
Project: CS529_Vector3D.h_1

/* End Header
*******************************************************************/
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "math.h"

struct Vector3D
{
	float x, y, z, w;
	Vector3D(float X = 0, float Y = 0, float Z = 0, float W = 0) : x(X), y(Y), z(Z), w(W) {}
};


/*
This function sets the coordinates of the 3D vector (pResult) to 0
*/
void Vector3DZero(Vector3D *pResult);

/*
This function sets the coordinates of the 3D vector (pResult) to x &y
*/
void Vector3DSet(Vector3D *pResult, float x, float y, float z, float w);

/*
In this function, pResult will be set to the opposite of pVec0
*/
void Vector3DNeg(Vector3D *pResult, Vector3D *pVec0);

/*
In this function, pResult will be the sum of pVec0 and pVec1
*/
void Vector3DAdd(Vector3D & pResult, const Vector3D  & pVec0, const Vector3D & pVec1);

/*
In this function, pResult will be the difference between pVec0 and pVec1 I.E: pVec0 - pVec1
*/
void Vector3DSub(Vector3D & pResult, Vector3D const & pVec0, Vector3D const & pVec1);

/*
In this function, pResult will be the unit vector of pVec0
*/
void Vector3DNormalize(Vector3D  & pResult, Vector3D const & pVec0);

/*
In this function, pResult will be the vector pVec0 scaled by the value c
*/
void Vector3DScale(Vector3D *pResult, Vector3D *pVec0, float c);

/*
In this function, pResult will be the vector pVec0 scaled by c and added to pVec1 
*/
void Vector3DScaleAdd(Vector3D *pResult, Vector3D *pVec0, Vector3D *pVec1, float c);

/*
In this function, pResult will be the vector pVec0 scaled by c and pVec1 will be subtracted from it 
*/
void Vector3DScaleSub(Vector3D *pResult, Vector3D *pVec0, Vector3D *pVec1, float c);

/*
This function returns the length of the vector pVec0
*/
float Vector3DLength(Vector3D const & pVec0);

/*
This function returns the square of pVec0's length. Avoid the square root
*/
float Vector3DSquareLength(Vector3D *pVec0);

/*
In this function, pVec0 and pVec1 are considered as 3D points.
The distance between these 2 3D points is returned
*/
float Vector3DDistance(Vector3D const & pVec0, Vector3D const & pVec1);

/*
In this function, pVec0 and pVec1 are considered as 3D points.
The squared distance between these 2 3D points is returned. Avoid the square root
*/
float Vector3DSquareDistance(const Vector3D & pVec0, const Vector3D & pVec1);

/*
This function returns the dot product between pVec0 and pVec1
*/
float Vector3DDotProduct(Vector3D const & pVec0, Vector3D const & pVec1);

/*
This function returns the cross product between pVec0 and pVec1
*/
Vector3D Vector3DCrossProduct(Vector3D *pVec0, Vector3D *pVec1);
/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Degrees
*/
void Vector3DFromAngleDeg(Vector3D *pResult, float angle);

/*
This function computes the coordinates of the vector represented by the angle "angle", which is in Radian
*/
void Vector3DFromAngleRad(Vector3D *pResult, float angle);
/*
This function finds the largest value in a vector and returns it
*/
float Vector3DMax(Vector3D const & vec);
/*
This function finds the largest of two vectors and returns it
*/
Vector3D const & Vector3DMaxBetween(Vector3D const & vec1, Vector3D const & vec2);
#endif