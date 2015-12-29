#pragma once
#define  MAXIMUM_SPRITES 512
// C++ header files
#include <iostream>
#include <fstream>
#include <vector>
// GLEW and OpenGL header files
#include "..\..\Dependencies\GLEW\glew.h"
#include "..\..\Dependencies\GLEW\wglew.h"
// Manager header file
#include "..\SFML Library\SFMLWindowManager.h"
#include "..\SFML Library\SFMLInputManager.h"
// Matrix Math Library
#include "..\Math Library\Matrix3D.h"
// Sprite Component Files
#include "..\Entity Library\GameObject.h"
#include "..\Component Library\Component.h"
#include "..\Component Library\SpriteComponent.h"
#include "..\Component Library\TransformComponent.h"
// SFML Texture header file 
#include <SFML\Graphics\Texture.hpp>
class OpenGLRenderer
{
private:
	/*--------------------------- VERTEX SHADER --------------------------------*/
	GLuint vertexShader;
	std::string vertexSource;
	/*--------------------------- FRAGMENT SHADER --------------------------------*/
	GLuint fragmentShader;
	std::string fragmentSource;
	/*--------------------------- SHADER PROGRAM --------------------------------*/
	GLuint shaderProgram;
	/*--------------------------- VERTEX ARRAY OBJECTS --------------------------------*/
	GLuint * VAO[MAXIMUM_SPRITES];
	/*--------------------------- VERTEX BUFFER OBJECTS --------------------------------*/
	GLuint * VBO[MAXIMUM_SPRITES];
	/*--------------------------- ELEMENT BUFFER OBJECTS --------------------------------*/
	GLuint * EAB[MAXIMUM_SPRITES];
	/*--------------------------- TEXTURE BUFFER OBJECTS --------------------------------*/
	GLuint * TBO[MAXIMUM_SPRITES];
	/*-------------------------------- MENU BUFFER OBJECTS -------------------------------*/
	GLuint VAMenu;
	GLuint VBMenu;
	/*--------------------------- SHADER FILE NAME LIST --------------------------------*/
	const char * vertexFile[1];
	const char * fragmentFile[1];
	/*-------------------------------- VIEW MATRIX -------------------------------*/
	Matrix3D View;
	/*-------------------------------- PROJECTION MATRIX -------------------------------*/
	Matrix3D Projection;
	/*-------------------------------- WINDOW MANAGER REFERENCE -------------------------------*/
	SFMLWindowManager & windowManager;
	/*-------------------------------- INPUT MANAGER REFERENCE -------------------------------*/
	SFMLInputManager & inputManager;
public:
	bool mLoseScreen;
	bool mWinScreen;
	// List of sprite components
	std::vector<Component *> SpriteList;
	// Returns the Shader Program
	GLuint const & GetShaderProgram() { return shaderProgram; }
	// Returns the Vertex Shader
	GLuint const & GetVertexShader() { return vertexShader; }
	// Returns the Fragment Shader
	GLuint const & GetFragmentShader() { return fragmentShader; }
	// Returns the View Matrix
	Matrix3D GetViewMatrix() { return View; }
	// Returns the Projection Matrix
	Matrix3D GetProjectionMatrix() { return Projection; }
	// Creates the Vertex Shader Program (VSP)
	bool CreateVertexShader();
	// Creates the Fragment Shader Program (FSP)
	bool CreateFragmentShader();
	// Creates, links and validates the Final Shader Program (FISP)
	bool CreateShaderProgram();
	// Creates a view matrix
	bool CreateViewMatrix(Vector3D & eye, Vector3D & target, Vector3D & up);
	// This function creates the Perspective Matrix and returns it
	Matrix3D CreateProjectionMatrix(
		float fovy,					// Angle between top plane and bottom plane of viewing cone
		float aspect_ratio,			// Ratio between width and height of the view port
		float near_plane,			// Distance between eye and near plane
		float far_plane				// Distance between eye and far plane
	);
	// This function creates a view matrix and returns it
	Matrix3D LookAt(
		Vector3D & eye,				// given eye position (camera),
		Vector3D & target,			// target position to look at
		Vector3D & up				// up vector (in most cases [0, 1, 0])
	);
	// Updates the scene values for all sprites
	bool Render();
	// Binds a texture unit to a supplied image
	bool BindTexture(sf::Image);
	// Holds the number of currently active/bound textures
	GLuint TextureCount;
	OpenGLRenderer(SFMLWindowManager &win, SFMLInputManager & in) : windowManager(win), inputManager(in)
	{
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		/*--------------------------- DEBUG CODE -------------------------------*/
		if (err != GLEW_OK)
		{
			int x;
			std::cout << "GLEW failed to initialize!\n";
			std::cin >> x;
			exit(1); // or handle the error in a nicer way, TODO : print to log or something
		}
		if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
		{
			int x;
			std::cout << "GLEW version 2.1 not supported by system.\n";
			std::cin >> x; 
			exit(1); // or handle the error in a nicer way, TODO : print to log or something
		}
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		std::cout << "Renderer: " << renderer << std::endl;
		std::cout << "OpenGL version:" << version << std::endl;
		TextureCount = 0;
		for (int i = 0; i < MAXIMUM_SPRITES; i++)
		{
			// Allocates the vertex data objects
			VAO[i] = new GLuint;
			glGenVertexArrays(1, VAO[i]);
			VBO[i] = new GLuint;
			glGenBuffers(1, VBO[i]);
			EAB[i] = new GLuint;
			glGenBuffers(1, EAB[i]);
			TBO[i] = new GLuint;
			glGenTextures(1, TBO[i]);
		}
		glGenVertexArrays(1, &VAMenu);
		glGenBuffers(1, &VBMenu);
		/*---------------------------------------- OPEN GL SETTINGS --------------------------------------------*/
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST); // Depth test
		glEnable(GL_BLEND);		 // Alpha Blending
		//glEnable(GL_CULLING);	 // Backface Culling
		mLoseScreen = false;
		mWinScreen = false;
	}
	~OpenGLRenderer()
	{
		// SHADER DELETION
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
		for (int i = 0; i < MAXIMUM_SPRITES; i++)
		{
			// BUFFER DELETION
			glDeleteBuffers(1, VBO[i]);
			glDeleteBuffers(1, EAB[i]);
			// TEXTURE DELETION
			glDeleteTextures(1, TBO[i]);
			// VERTEX ARRAY DELETION
			glDeleteVertexArrays(1, VAO[i]);
		}
	}
};