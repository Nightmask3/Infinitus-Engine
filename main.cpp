#define GLEW_STATIC // Preprocesser directive to specify static linkage

// Windows header files
#include <windows.h>
// C++ header files
#include <iostream>
#include <fstream>
#include <string>
// SFML header files
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
// GLEW and OpenGL header files
#include "Dependencies\GLEW\glew.h"	// glew.h needs to be included before GL.h
#include "Dependencies\GLEW\wglew.h"
// SOIL header file
#include "SOIL.h"
// Game Engine Managers header files
#include "Source\Manager Library\GameObjectFactory.h"
#include "Source\SFML Library\SFMLWindowManager.h"
#include "Source\SFML Library\SFMLEventManager.h"
#include "Source\SFML Library\SFMLInputManager.h"
// Graphics module
#include "Source\OpenGLRenderer Library\OpenGLRenderer.h"

GameObject *LoadObject(const char *pFileName)
{
	GameObject *pNewObject = NULL;

	FILE *fp;
	fopen_s(&fp, pFileName, "r");
	if (fp)
	{
		pNewObject = new GameObject();
		while (!feof(fp))
		{
			char componentName[256];
			memset(componentName, 0, 256 * sizeof(char));

			if (strcmp(componentName, "Transform") == 0)	// Evaluates to 0 when it is true
			{
				TransformComponent *pT = new TransformComponent();
				// SET THE TRANSFORM COMPONENT VALUES HERE FROM THE FILE
				// pT->posX = bla bla bla
			}
			if (strcmp(componentName, "Sprite") == 0)	// Evaluates to 0 when it is true
			{
				//Sprite *pS = new Sprite();
				// SET THE COMPONENT VALUES HERE FROM THE FILE
			}
			if (strcmp(componentName, "") == 0)	// Evaluates to 0 when it is true
			{
				//ComponentX *pT = new ComponentX();
				// SET THE COMPONENT VALUES HERE FROM THE FILE
			}
		}
	}
	fclose(fp);
	return pNewObject;
}

GameObject * LoadLevel(const char *pFileName)
{
	FILE *pF;
	GameObject *pNewLevel = new GameObject();
	fopen_s(&pF, pFileName, "r"); // Reads the level file
	if (pF)
	{
		while (!feof(pF))
		{
			char objectName[256];
			memset(objectName, 0, 256 * sizeof(char));
		}
	}
	fclose(pF);
	return pNewLevel;
}
void check_gl_error()
{
	GLenum err(glGetError());
	using namespace std;
	while (err != GL_NO_ERROR) {
		string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		cerr << "GL_" << error.c_str() << endl;
		err = glGetError();
	}
}
int main(int argc, char* args[])
{
	//Main loop flag
	bool quit = false;

	SFMLWindowManager * window = new SFMLWindowManager();		 // Creates the window handler
	window->CreateWin(window->GetWin());						 // Creates the window

	SFMLInputManager * input = new SFMLInputManager(*window);	 // Creates the input handler

	SFMLEventManager * event = new SFMLEventManager(*input);	 // Creates the event handler

	GameObjectFactory *gObjectFactory = new GameObjectFactory(); // Creates the game object factory
	
	OpenGLRenderer * graphics = new OpenGLRenderer();
	
	// Create a clock for measuring the time elapsed
	sf::Clock clock;
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	/*--------------------------- DEBUG CODE -------------------------------*/
	if (err != GLEW_OK)
		exit(1); // or handle the error in a nicer way
	if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
		exit(1); // or handle the error in a nicer way
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	std::cout << "Renderer: " << renderer;
	std::cout << "\nOpenGL version:" << version;
	/*--------------------------- VERTEX SHADER --------------------------------*/
	std::ifstream in("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\GLSL Library\\VertexShader.c");
	std::string vertexSource((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());	// Reads the content of vertex shader code into a string
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	// Creates Shader Object of type vertex shader
	GLchar const* files[] = { vertexSource.c_str() };
	glShaderSource(vertexShader, 1, files, NULL);			// files is a pointer to an array of character pointers
	glCompileShader(vertexShader);
	/*--------------------------- VERTEX SHADER DEBUG --------------------------------*/
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "\nVertex shader compiled successfully.";
	}
	else
	{
		std::cout << "\nVertex shader failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer;
	}
	/*--------------------------- FRAGMENT SHADER --------------------------------*/
	std::ifstream in2("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\GLSL Library\\FragmentShader.c");
	std::string fragmentSource((std::istreambuf_iterator<char>(in2)), std::istreambuf_iterator<char>());	// Reads the content of vertex shader code into a string
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	// Creates Shader Object of type vertex shader
	GLchar const* files2[] = { fragmentSource.c_str() };		// glShaderSource requires character pointers
	glShaderSource(fragmentShader, 1, files2, NULL);			// files is a pointer to an array of character pointers
	glCompileShader(fragmentShader);
	/*--------------------------- FRAGMENT SHADER DEBUG --------------------------------*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "\nFragment shader compiled successfully.";
	}
	else
	{
		std::cout << "\nFragment shader failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer;
	}
	/*--------------------------- CREATES THE SHADER PROGRAM --------------------------------*/
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//glBindFragDataLocation(shaderProgram, 0, "outColor"); // Not necessary, but when using multiple buffers, binds the fragment data output to the right buffer
	glLinkProgram(shaderProgram);						  // Links the shader objects (vertex, fragment) into the shader program
	glValidateProgram(shaderProgram);
	GLint linked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked == GL_TRUE)
	{
		std::cout << "\nShader program compiled successfully.";
	}
	else
	{
		std::cout << "\nShader program failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer;
	}

	/*--------------------------- VERTEX DATA --------------------------------*/
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 
		-0.2f, 0.8f, 0.0f, 
		0.2f, 0.8f, 0.0f,
		0.0f, 0.8f, 0.0f, 
		0.0f, 1.0f, 0.0f,
		-0.2f, -0.8f, 0.0f,
		0.2f, -0.8f, 0.0f,
		0.0f, -0.8f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-0.8f, -0.2f, 0.0f,
		-0.8f, 0.2f, 0.0f,
		-0.8f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.8f, -0.2f, 0.0f,
		0.8f, 0.2f, 0.0f,
		0.8f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	/*--------------------------- INDEX DATA --------------------------------*/
	GLuint indices[] = { 
		// Top
		0, 1, 3,
		0, 3, 2,
		3, 1, 4,
		3, 4, 2,
		// Bottom
		0, 5, 7,
		0, 7, 6,
		7, 5, 8,
		7, 8, 6,
		// Left
		0, 9, 11,
		0, 11, 10,
		11, 9, 12,
		11, 12, 10,
		// Right
		0, 13, 15,
		0, 15, 14,
		15, 13, 16,
		15, 16, 14
	};
	/*--------------------------- COLOR DATA --------------------------------*/
	GLfloat colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};
	gObjectFactory->CreateGameObject();	// Creates a game object
	SpriteComponent * s;
	gObjectFactory->CreateComponent<SpriteComponent>();	// Attaches a sprite component to the game object
	s = static_cast<SpriteComponent *> (gObjectFactory->ObjectLibrary[0].GetComponent(Component::SPRITE));	// Gets sprite component of game object
	s->SetVertexList(vertices, 17);
	s->SetIndexList(indices, 48);
	s->SetVertexColorList(colors);

	window->GetWin().setActive();
	/*--------------------------- VERTEX ARRAY OBJECT --------------------------------*/
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	/*--------------------------- VERTEX BUFFER OBJECT --------------------------------*/
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, s->GetVertexList().size() * sizeof(Vertex), &(s->GetVertexList()[0]), GL_STATIC_DRAW);	// Copies the vertex array into the vertex buffer
	
	/*--------------------------- ELEMENT ARRAY BUFFER --------------------------------*/
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, s->GetIndexList().size() * sizeof(GLuint), &(s->GetIndexList()[0]), GL_STATIC_DRAW);

	/*--------------------------- VERTEX ATTRIBUTE POINTERS --------------------------------*/
	
	// Position
	glVertexAttribPointer(
		0, 
		3, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex), 
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	// Unbind the buffer for other uses
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Start the game loop
	while (window->GetWin().isOpen())
	{
		if (input->isKeyPressed(sf::Keyboard::P))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		window->GetWin().setActive();

		// Clear color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		check_gl_error();
		glDrawElements(GL_TRIANGLES, s->GetIndexList().size(), GL_UNSIGNED_INT, 0);
		check_gl_error();
		glBindVertexArray(0);
		window->GetWin().display(); // Swap buffers

		input->UpdateInputState();								// Handles the input for this frame TODO : Incorporate mouse and operators for combinations of keys
		// HANDLE THE EVENTS FOR THIS GAME LOOP
		while (window->GetWin().pollEvent(event->GetEvent()))	// Fills out the window events into the event variable
		{
			event->SetEventType();								// Finds out the event type
			event->HandleEvent();								// Handles the event based on its input type
		}
		
	}

	return EXIT_SUCCESS;
}