/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Matrix3D.c
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date October 9th, 2015
\brief The implementation file for the Matrix operations.

Language: C, Visual Studio 2013
Project: CS529_Matrix3D.c_1

/* End Header
*******************************************************************/

#include "Matrix3D.h"

#define PI      3.1415926535897932384626433832795
/*---------------------------HELPER FUNCTIONS-----------------------------*/
float DegreesToRadians(float degrees)
{
	return degrees * (float)(PI / 180);
}

float RadiansToDegrees(float radians)
{
	return radians * (float)(180 / PI);
}
/*
This function sets the matrix Result to the identity matrix
*/
void Matrix3DIdentity(Matrix3D *pResult)
{	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (j == i)
				pResult->m[i][j] = 1;
			else
				pResult->m[i][j] = 0;
		}
	}

	/*for (int i = 0; i < 3; i++)           Function for printing out matrix to check results
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%f\t", pResult->m[i][j]);
		}
		printf("\n");
	} */ 

}

// ---------------------------------------------------------------------------
/*
This functions calculates the cotangent of the input angle and returns it
*/
float Cotangent(float angle)
{
	return (float)(1.0 / tan(angle));
}
// ---------------------------------------------------------------------------
/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix3DTranspose(Matrix3D *pResult, Matrix3D *pMtx)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			pResult->m[i][j] = pMtx->m[j][i];
		}
	}
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix3DConcat(Matrix3D *pResult, Matrix3D *pMtx0, Matrix3D *pMtx1)
{
	Matrix3D temp; 
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp.m[i][j] = 0; // Zero out values
		}
	}
	// Multiply matrices
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			for (int k = 0; k < 4; k++)
			{
				temp.m[row][column] += pMtx0->m[row][k] * pMtx1->m[k][column];
			}
		}
	}
	*pResult = temp;
}


// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x, y, z and saves it in Result
*/
void Matrix3DTranslate(Matrix3D *pResult, float x, float y, float z)
{
	Matrix3DIdentity(pResult);
	pResult->m[0][3] = x;
	pResult->m[1][3] = y;
	pResult->m[2][3] = z;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x, y, z and saves it in Result
*/
void Matrix3DScale(Matrix3D *pResult, float x, float y, float z)
{
	Matrix3DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
	pResult->m[2][2] = z;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix3DRotDeg(Matrix3D *pResult, float Angle)
{
	float radianvalue; 
	radianvalue = (Angle * PI) / 180;
	// For X rotation
	Matrix3DRotRadX(pResult, radianvalue);
	// For Y rotation
	Matrix3DRotRadY(pResult, radianvalue);
	// For Z rotation
	Matrix3DRotRadZ(pResult, radianvalue);
}

// ---------------------------------------------------------------------------

/*
This matrix rotates by 'Angle' radians around the X axis
*/
void Matrix3DRotRadX(Matrix3D *pResult, float Angle)
{
	float sine = sinf(Angle);
	float cosine = cosf(Angle);
	Matrix3DIdentity(pResult);
	pResult->m[1][1] = cosine;
	pResult->m[1][2] = -sine;
	pResult->m[2][1] = sine;
	pResult->m[2][2] = cosine;
}
// ---------------------------------------------------------------------------

/*
This matrix rotates by 'Angle' radians around the Y axis
*/
void Matrix3DRotRadY(Matrix3D *pResult, float Angle)
{
	float sine = sinf(Angle);
	float cosine = cosf(Angle);
	Matrix3DIdentity(pResult);
	pResult->m[0][0] = cosine;
	pResult->m[0][2] = sine;
	pResult->m[2][0] = -sine;
	pResult->m[2][2] = cosine;
}
// ---------------------------------------------------------------------------

/*
This matrix rotates by 'Angle' radians around the Z axis
*/
void Matrix3DRotRadZ(Matrix3D *pResult, float Angle)
{
	float sine = sinf(Angle);
	float cosine = cosf(Angle);
	Matrix3DIdentity(pResult);
	pResult->m[0][0] = cosine;
	pResult->m[0][1] = -sine;
	pResult->m[1][0] = sine;
	pResult->m[1][1] = cosine;
}
// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix3DMultVec(Vector3D *pResult, Matrix3D *pMtx, Vector3D *pVec)
{
	Vector3D temp(0, 0, 0, 1);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float mult = 0.0f;
			if (j == 0)
				mult = pVec->x;
			else if (j == 1)
				mult = pVec->y;
			else if (j == 2)
				mult = pVec->z;
			else if (j == 3)
				mult = pVec->w;
			if (i == 0)
				temp.x += pMtx->m[i][j] * mult;
			else if (i == 1)
				temp.y += pMtx->m[i][j] * mult;
			else if (i == 2)
				temp.z += pMtx->m[i][j] * mult;
			else if (i == 3)
				temp.w += pMtx->m[i][j] * mult;
		}
	}
	Vector3DSet(pResult, temp.x, temp.y, temp.z, temp.w);
}

// ---------------------------------------------------------------------------
