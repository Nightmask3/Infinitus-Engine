#pragma once
// GLEW and OpenGL header files
#include "..\..\Dependencies\GLEW\glew.h"	// glew.h needs to be included before GL.h
#include "..\..\Dependencies\GLEW\wglew.h"
#include "Component.h"
#include <vector>
#pragma pack(push, 1)
struct Vertex
{
	GLfloat X, Y, Z;	// Position
	GLfloat R, G, B, A;	// Color
};
#pragma pack(pop)
class SpriteComponent : public Component
{
public:
	std::vector<Vertex> VertexList;
	std::vector<GLuint> IndexList;
	std::vector<GLfloat> VertexColorList;
public:
	SpriteComponent() : Component(Component::SPRITE){};
	std::vector<Vertex> & GetVertexList() { return VertexList; }
	std::vector<GLuint> & GetIndexList() { return IndexList; }
	std::vector<GLfloat> & GetVertexColorList() { return VertexColorList; }
	void SetVertexList(GLfloat list[], GLuint number);
	void SetIndexList(GLuint list[], GLuint number);
	void SetVertexColorList(GLfloat list[]);
	void Update(); 
	void Serialize(FILE **pFile);
	virtual ~SpriteComponent();
};

