#pragma once

#define PI 3.14159
// C++ header files
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>

// GLEW and OpenGL header files
#include "..\..\Dependencies\GLEW\glew.h"	// glew.h needs to be included before GL.h
#include "..\..\Dependencies\GLEW\wglew.h"
#include "Component.h"

#include "..\Math Library\Vector3D.h"
struct Vertex
{
	GLfloat X, Y, Z;	// Position
	GLfloat R, G, B, A;	// Color
	GLfloat U, V;		// Texture Coordinates
};
class SpriteComponent : public Component
{
public: 
	enum SHAPE_PRIMITIVE
	{
		SPHERE,
		CUBE,
		RECTANGLE,
		TRIANGLE,
		COUNT
	};
	std::vector<Vertex> VertexList;
	std::vector<GLuint> IndexList;
	SHAPE_PRIMITIVE shapeType;
	GLuint mTextureHandle;
public:
	
	SpriteComponent() : Component(Component::SPRITE){ shapeType = COUNT; };
	inline std::vector<Vertex> const & GetVertexList() { return VertexList; }
	inline std::vector<GLuint> const & GetIndexList() { return IndexList; }

	void SetVertexList(GLfloat list[], GLuint number);
	void SetIndexList(GLuint list[], GLuint number);
	void SetVertexColorList(GLfloat list[]);
	void SetTextureCoordList(GLfloat list[]);
	void Update(); 
	void Serialize(std::string &, unsigned int &);
	void CreatePrimitive(SHAPE_PRIMITIVE);
	void SetTextureHandle(GLuint handle);
	GLuint GetTextureHandle() { return mTextureHandle; }
	virtual ~SpriteComponent();
};

