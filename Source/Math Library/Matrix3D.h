/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Matrix3D.h
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date October 9th, 2015 
\brief The headerfile for the Matrix operations.

Language: C, Visual Studio 2013
Project: CS529_Matrix3D.h_1

/* End Header
*******************************************************************/

#ifndef Matrix3D_H
#define Matrix3D_H


#include "Vector3D.h"

struct Matrix3D
{
	float m[4][4]; // 4x4 to hold the homogeneous coordinate system form (i.e. with weight 'w')
};


/*
This function sets the matrix Result to the identity matrix
*/
void Matrix3DIdentity(Matrix3D *pResult);

/*
This functions calculated the transpose matrix of pMtx and saves it in Result
*/
void Matrix3DTranspose(Matrix3D *pResult, Matrix3D *pMtx);

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix3DConcat(Matrix3D *pResult, Matrix3D *pMtx0, Matrix3D *pMtx1);

/*
This function creates a translation matrix from x, y, z and saves it in Result
*/
void Matrix3DTranslate(Matrix3D *pResult, float x, float y, float z);

/*
This function creates a scaling matrix from x, y, z and saves it in Result
*/
void Matrix3DScale(Matrix3D *pResult, float x, float y, float z);

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix3DRotDeg(Matrix3D *pResult, float Angle);

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian, (for rotation about X axis)
Save the resultant matrix in Result
*/
void Matrix3DRotRadX(Matrix3D *pResult, float Angle);


/*
This matrix creates a rotation matrix from "Angle" whose value is in radian, (for rotation about Y axis)
Save the resultant matrix in Result
*/
void Matrix3DRotRadY(Matrix3D *pResult, float Angle);

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian, (for rotation about Z axis)
Save the resultant matrix in Result
*/
void Matrix3DRotRadZ(Matrix3D *pResult, float Angle);

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix3DMultVec(Vector3D *pResult,const Matrix3D *pMtx, const Vector3D *pVec);
/*
This function calculates the cotangent of the input angle and returns it
*/
float Cotangent(float angle);

float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);
#endif