#pragma once
// GLEW and OpenGL header files
#include "..\..\Dependencies\GLEW\glew.h"
#include "..\..\Dependencies\GLEW\wglew.h"
#include "..\Component Library\Component.h"
class OpenGLRenderer
{
private:
	/*------------------------------- SHADERS ----------------------------------*/
	int Lengths[2];	// Holds the length of the vertex shader and the fragment shader
	/*--------------------------- VERTEX ARRAY OBJECT --------------------------------*/
	GLuint VAO;
	/*--------------------------- VERTEX BUFFER OBJECT --------------------------------*/
	GLuint VBO;
	/*--------------------------- ELEMENT BUFFER OBJECT --------------------------------*/
	GLuint EAB;

public:
	// Returns the VAO
	GLuint & GetVertexArrayObject() { return VAO; }
	// Returns the VBO
	GLuint & GetVertexBufferObject() { return VBO; }
	// Returns the EBO
	GLuint & GetElementArrayBuffer() { return EAB; }

	OpenGLRenderer(){};
	~OpenGLRenderer(){};
};