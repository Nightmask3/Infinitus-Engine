/* Start Header
*****************************************************************/
/*!
Copyright (C) 2015 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.

\file Math2D.cpp
\author Sai Narayan, sainarayan.n, 60000215
\par sainarayan@digipen.edu
\date October 9th, 2015
\brief The implementation file for the Math/Collision checking operations.


History:
Modifications :  October 5th, Added the Static Circle to Static Rectangle collision function

Language: C, Visual Studio 2013
Project: CS529_Math2D.c_1

/* End Header
*******************************************************************/

#include "Math2D.h"
#include "stdio.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if (Vector2DSquareDistance(pP, pCenter) <= powf(Radius, 2))
		return 1;
	else
		return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	int HalfWidth = Width/2, HalfHeight = Height/2;
	float left, right, bottom, top;

	left = pRect->x - HalfWidth; // Gets the x values of the left midpoint of the Rectangle 
	top = pRect->y + HalfHeight; // Gets the x values of the top midpoint of the Rectangle 
	right = pRect->x + HalfWidth; // Gets the y values of the right midpoint of the Rectangle 
	bottom = pRect->y - HalfHeight; // Gets the y values of the bottom midpoint of the Rectangle 

	// left = pRect->y; Not used but can be in the future
	// top = pRect->x; Not used but can be in the future
	// right = pRect->y; Not used but can be in the future
	// bottom = pRect->x; Not used but can be in the future

	if (pPos->x < left || pPos->x >right || pPos->y < bottom || pPos->y > top) 
		return 0;
	else 
		return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if ((Vector2DSquareDistance(pCenter0, pCenter1)) <= powf(Radius0 + Radius1, 2))
		return 1;
	else
		return 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float left0, right0, bottom0, top0;  // Holds the midpoint values of Rectangle 1
	float left1, right1, bottom1, top1;  // Holds the midpoint values of Rectangle 2
	// Calculations for the 1st rectangle.
	left0 = pRect0->x - Width0 / 2;
	top0 = pRect0->y + Height0 / 2;
	right0 = pRect0->x + Width0 / 2;
	bottom0 = pRect0->y - Height0 / 2;
	// Calculations for the 2nd rectangle.
	left1 = pRect1->x - Width1 / 2;
	top1 = pRect1->y + Height1 / 2;
	right1 = pRect1->x + Width1 / 2;
	bottom1 = pRect1->y - Height1 / 2;

	if (left0 > right1 || left1 > right0 || top0 < bottom1 || top1 < bottom0)
		return 0;
	else
		return 1;
}


/*
This function checks if a static circle is intersecting with a static rectangle

Circle:		Center is "Center", radius is "Radius"
Rectangle:	Center is "Rect", width is "Width" and height is "Height"
Function returns true is the circle and rectangle are intersecting, otherwise it returns false
*/

int StaticCircleToStaticRectangle(Vector2D *pCenter, float Radius, Vector2D *pRect, float Width, float Height)
{
	Vector2D Snap;
	Vector2DZero(&Snap);
	float left = pRect->x;
	float right = pRect->x; 
	float top = pRect->y;
	float bottom = pRect->y;
	if (pCenter->x < left)
		Snap.x = left;
	else if (pCenter->x > right)
			Snap.x = right;
	else
		Snap.x = pCenter->x;
	if (pCenter->y < bottom)
		Snap.y = bottom;
	
	else if (pCenter->y > top)
		Snap.y = top;
	else
		Snap.y = pCenter->y;
	if (StaticPointToStaticCircle(&Snap, pCenter, 1))
		return 1;

	return 0;
}