/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Matrix2D.c
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date October 9th, 2015
\brief The implementation file for the Matrix operations.

Language: C, Visual Studio 2013
Project: CS529_Matrix2D.c_1

/* End Header
*******************************************************************/

#include "Matrix2D.h"

#define PI      3.1415926535897932384626433832795
/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
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
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
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
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	float sum = 0;
	Matrix2D temp; // To be used with compatability for the reference variables
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sum = 0;
			for (int k = 0; k < 3; k++)
			{	
				sum += pMtx0->m[i][k] * pMtx1->m[k][j];
			}
			temp.m[i][j] = sum;
		}
	}
	*pResult = temp;
}


// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x *p y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;

}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x *p y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	float radianvalue; 
	radianvalue = (Angle * PI) / 180;
	Matrix2DRotRad(pResult, radianvalue);
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = cosf(Angle);
	pResult->m[0][1] = -(sinf(Angle));
	pResult->m[1][0] = sinf(Angle);
	pResult->m[1][1] = cosf(Angle);
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D temp;
	Vector2DZero(&temp);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0 && j == 0)
				temp.x += pMtx->m[i][j] * pVec->x;
			if (i == 0 && j == 1)
				temp.x += pMtx->m[i][j] * pVec->y;
			if (i == 0 && j == 2)
				temp.x += pMtx->m[i][j];
			if (i == 1 && j == 0)
				temp.y += pMtx->m[i][j] * pVec->x;
			if (i == 1 && j == 1)
				temp.y += pMtx->m[i][j] * pVec->y;
			if (i == 1 && j == 2)
				temp.y += pMtx->m[i][j];
		}
	}
	Vector2DSet(pResult, temp.x, temp.y);
}

// ---------------------------------------------------------------------------
