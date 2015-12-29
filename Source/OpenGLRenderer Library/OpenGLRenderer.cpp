
#include "OpenGLRenderer.h"
#include "..\Component Library\PhysicsComponent.h"

void check_gl_error_render()
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
bool OpenGLRenderer::CreateVertexShader()
{
	/*--------------------------- VERTEX SHADER --------------------------------*/
	std::ifstream in("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\GLSL Library\\VertexShader.c");
	std::string vertexSource((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());	// Reads the content of vertex shader code into a string
	vertexShader = glCreateShader(GL_VERTEX_SHADER);	// Creates Shader Object of type vertex shader
	vertexFile[0] = { vertexSource.c_str() };
	glShaderSource(vertexShader, 1, vertexFile, NULL);			// files is a pointer to an array of character pointers
	glCompileShader(vertexShader);
	/*--------------------------- VERTEX SHADER DEBUG --------------------------------*/
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "\nVertex shader compiled successfully.";
		return true;
	}
	else
	{
		std::cout << "\nVertex shader failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer;
		return false;
	}
}

bool OpenGLRenderer::CreateFragmentShader()
{
	/*--------------------------- FRAGMENT SHADER --------------------------------*/
	std::ifstream in2("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\GLSL Library\\FragmentShader.c");
	std::string fragmentSource((std::istreambuf_iterator<char>(in2)), std::istreambuf_iterator<char>());	// Reads the content of vertex shader code into a string
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	// Creates Shader Object of type vertex shader
	fragmentFile[0] = { fragmentSource.c_str() };		// glShaderSource requires character pointers
	glShaderSource(fragmentShader, 1, fragmentFile, NULL);			// files is a pointer to an array of character pointers
	glCompileShader(fragmentShader);  
	/*--------------------------- FRAGMENT SHADER DEBUG --------------------------------*/
	GLint status;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "\nFragment shader compiled successfully.";
		return true;
	}
	else
	{
		std::cout << "\nFragment shader failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer;
		return false;
	}
}
bool OpenGLRenderer::CreateShaderProgram()
{
	/*--------------------------- SHADER CREATION --------------------------------*/
	CreateVertexShader();
	CreateFragmentShader();
	shaderProgram = glCreateProgram();
	// SHADER ATTACHMENT
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//glBindFragDataLocation(shaderProgram, 0, "outColor"); // Not necessary, but when using multiple buffers, binds the fragment data output to the right buffer
	
	// LINKAGE
	glLinkProgram(shaderProgram);						  // Links the shader objects (vertex, fragment) into the shader program
	// VALIDATION
	glValidateProgram(shaderProgram);
	/*--------------------------- SHADER PROGRAM DEBUG --------------------------------*/
	GLint linked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked == GL_TRUE)
	{
		std::cout << "\nShader program compiled successfully." << std::endl;
		return true;
	}
	else
	{
		std::cout << "\nShader program failed to compile.";
		char buffer[512];
		glGetShaderInfoLog(shaderProgram, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		return false;
	}
}

bool OpenGLRenderer::CreateViewMatrix(Vector3D & eye, Vector3D & target, Vector3D & up)
{
	Vector3D temp;
	Vector3DZero(&temp);

	Vector3DAdd(temp, eye, target);
	View = LookAt(eye, temp, up);
	return true;
}

Matrix3D OpenGLRenderer::LookAt(Vector3D & eye, Vector3D & target, Vector3D & up) // Returns a view matrix
{
	Vector3D zaxis(0, 0, 0, 0); // The "forward" vector.
	Vector3D xaxis(0, 0, 0, 0);// The "right" vector.
	// Find the direction vector to look towards, Z plane vector
	Vector3DSub(zaxis, eye, target);
	Vector3DNormalize(zaxis, zaxis);
	// Find X plane vector
	Vector3D crossproduct = Vector3DCrossProduct(&up, &zaxis);
	Vector3DNormalize(xaxis, crossproduct);
	// Find Y plane vector
	Vector3D yaxis = Vector3DCrossProduct(&zaxis, &xaxis);   // The "up" vector.

	// Create a 4x4 orientation matrix from the right, up, and forward vectors
	// This is transposed which is equivalent to performing an inverse 
	// if the matrix is orthonormalized (in this case, it is).
	Matrix3D orientation;
	Matrix3DIdentity(&orientation);
	orientation.m[0][0] = xaxis.x;
	orientation.m[0][1] = xaxis.y;
	orientation.m[0][2] = xaxis.z;

	orientation.m[1][0] = yaxis.x;
	orientation.m[1][1] = yaxis.y;
	orientation.m[1][2] = yaxis.z;

	orientation.m[2][0] = zaxis.x;
	orientation.m[2][1] = zaxis.y;
	orientation.m[2][2] = zaxis.z;


	// Create a 4x4 translation matrix.
	// The eye position is negated which is equivalent
	// to the inverse of the translation matrix. 
	// T(v)^-1 == T(-v)
	Matrix3D translation;
	Matrix3DIdentity(&translation);

	translation.m[0][3] = -eye.x;
	translation.m[1][3] = -eye.y;
	translation.m[2][3] = -eye.z;
	
	// Combine the orientation and translation to compute 
	// the final view matrix
	Matrix3D result;
	Matrix3DConcat(&result, &orientation, &translation);
	return result;
}
/*
This function creates the Perspective Matrix and returns it
*/
Matrix3D OpenGLRenderer::CreateProjectionMatrix(
	float fovy,					// Angle between top plane and bottom plane of viewing cone
	float aspect_ratio,			// Ratio between width and height of the view port
	float near_plane,			// Distance between eye and near plane
	float far_plane				// Distance between eye and far plane
	)
{
	Matrix3D output;
	Matrix3DIdentity(&output);
	const float
		y_scale = Cotangent(DegreesToRadians(fovy / 2)),
		x_scale = y_scale / aspect_ratio,
		frustum_length = far_plane - near_plane;
	output.m[0][0] = x_scale;
	output.m[1][1] = y_scale;
	output.m[2][2] = -((near_plane + far_plane) / frustum_length);
	output.m[2][3] = -((2 * near_plane*far_plane) / frustum_length);
	output.m[3][2] = -1;
	output.m[3][3] = 0;

	return output;
}

bool OpenGLRenderer::BindTexture(sf::Image image)
{
	GLsizei width = 0, height = 0;
	width = image.getSize().x;
	height = image.getSize().y;
	SpriteComponent * s = static_cast<SpriteComponent*>(SpriteList.back());
	s->SetTextureHandle(TextureCount);
	// Sets the active texture unit using the enum values
	glActiveTexture(GL_TEXTURE0 + TextureCount);
	// Sets what type of texture it is and the texture buffer it is bound to
	glBindTexture(GL_TEXTURE_2D, *TBO[TextureCount]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), s->GetTextureHandle());
	// Sets the texture uniform in the shader
	check_gl_error_render();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Binds the texture to the image data
	TextureCount++;
	return true;
}

bool OpenGLRenderer::Render()
{
	GameObject temp;
	GLuint counter = 0;
	// Get the Model Matrix
	GLint glModel = glGetUniformLocation(GetShaderProgram(), "model");
	// Get the View Matrix
	GLint glView = glGetUniformLocation(GetShaderProgram(), "view");
	// Get the Projection Matrix
	GLint glProjection = glGetUniformLocation(GetShaderProgram(), "projection");
	/*-------------------------------- PROJECTION MATRIX -------------------------------*/
	// Creates the projection matrix
	Matrix3D Projection;
	float FoV = 90.0f;
	Projection = CreateProjectionMatrix(
		FoV,         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f       // Far clipping plane. Keep as little as possible.
		);
	glUniformMatrix4fv(glView, 1, GL_TRUE, &(View.m[0][0]));
	glUniformMatrix4fv(glProjection, 1, GL_TRUE, &(Projection.m[0][0]));
	
	// Sets background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Wireframe drawing
	if (inputManager.isKeyPressed(sf::Keyboard::P))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Because SFML is buggy with windows and contexts =/
	windowManager.GetWin().setActive();
	// If M is pressed, draw the Menu
	if (inputManager.isKeyPressed(sf::Keyboard::M) || mLoseScreen == true || mWinScreen == true)
	{
		GLfloat vertices[] = {
			//  Position      Color         Texcoords
			-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
			0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top-right
			0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// Bottom-right

			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// Bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
			-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top-left
		};
		/*--------------------------- VERTEX ARRAY OBJECT --------------------------------*/
		glBindVertexArray(VAMenu);
		/*--------------------------- VERTEX BUFFER OBJECT --------------------------------*/
		glBindBuffer(GL_ARRAY_BUFFER, VBMenu);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		/*--------------------------- TEXTURE BINDING --------------------------------*/
		if (mLoseScreen == true)
			glBindTexture(GL_TEXTURE_2D, 3);
		else if (mWinScreen == true)
			glBindTexture(GL_TEXTURE_2D, 4);
		else
			glBindTexture(GL_TEXTURE_2D, 2);
		
		/*--------------------------- VERTEX ATTRIBUTE POINTERS --------------------------------*/
		// Position
		glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			7 * sizeof(GLfloat),
			(GLvoid*)0
		);
		glEnableVertexAttribArray(0);
		// Color
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			7 * sizeof(GLfloat),
			(GLvoid*)(2 * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(1);
		// Texture Coordinates
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			7 * sizeof(GLfloat),
			(GLvoid*)(5 * sizeof(GLfloat))
			);
		glEnableVertexAttribArray(2);
		/*-------------------------------- MODEL MATRIX -------------------------------*/
		// Create the transformation / Model matrix
		Matrix3D Model;
		Matrix3D Scale;
		Matrix3D Rotation;
		// Scales using the original values of the mesh
		Matrix3DIdentity(&Scale);
		Matrix3DIdentity(&Model);
		Scale.m[0][0] = 25;
		Scale.m[1][1] = 25;
		Scale.m[2][2] = 25;

		Matrix3DConcat(&Model, &Model, &(Scale));
		windowManager.GetWin().setActive();
		// Uniform matrices ARE supplied in Row Major order hence set to GL_TRUE
		glUniformMatrix4fv(glModel, 1, GL_TRUE, &Model.m[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
		return true;
	}
	for (auto iterator = SpriteList.begin(); iterator != SpriteList.end(); iterator++)
	{
		SpriteComponent * s = static_cast<SpriteComponent *>(*iterator); // Gets a reference to the Sprite Component of a Game Object to render
		PhysicsComponent * p = static_cast<PhysicsComponent *>(s->mOwner->GetComponent(Component::PHYSICS));
		/*--------------------------- VERTEX ARRAY OBJECT --------------------------------*/
		glBindVertexArray(*VAO[counter]);
		/*--------------------------- VERTEX BUFFER OBJECT --------------------------------*/
		glBindBuffer(GL_ARRAY_BUFFER, *VBO[counter]);
		glBufferData(GL_ARRAY_BUFFER, s->GetVertexList().size() * sizeof(Vertex), &(s->GetVertexList()[0]), GL_STATIC_DRAW);
		/*--------------------------- ELEMENT ARRAY BUFFER --------------------------------*/
		if (s->GetIndexList().size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EAB[counter]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, s->GetIndexList().size() * sizeof(GLuint), &(s->GetIndexList()[0]), GL_STATIC_DRAW);
		}
		/*--------------------------- TEXTURE BINDING --------------------------------*/
		// If its not an AABB
		if (p != nullptr)
		{
			if (!p->mpShape->mType == Bounding::AABB)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 1);
			}
		}
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
		// Texture Coordinates
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(GLvoid*)(7 * sizeof(GLfloat))
			);
		glEnableVertexAttribArray(2);
		counter++;
	}
	counter = 0;
	for (auto iterator = SpriteList.begin(); iterator != SpriteList.end(); iterator++)
	{
		Matrix3D Model;
		TransformComponent * t = nullptr;
		SpriteComponent * s = nullptr;
		// Iterator is a pointer to a pointer, so it must be dereferenced twice
		temp = (*(*iterator)->mOwner); // Gets a copy of the Gameobject owner of this Sprite Component to use for Transform calculations
		
		t = static_cast<TransformComponent *>(temp.GetComponent(Component::TRANSFORM));
		s = static_cast<SpriteComponent *>(*iterator);
		// Create the transformation / Model matrix
		Matrix3DConcat(&Model, &(t->mTranslation), &(t->mRotation));
		Matrix3DConcat(&Model, &Model, &(t->mScale));
		
		windowManager.GetWin().setActive();
		// Uniform matrices ARE supplied in Row Major order hence set to GL_TRUE
		glUniformMatrix4fv(glModel, 1, GL_TRUE, &Model.m[0][0]);
		// Binds the Vertex array to the currently supplied VAO
		glBindVertexArray(*VAO[counter++]);

		check_gl_error_render();
		// If index list is specified, use Indexed Drawing
		if (s->GetIndexList().size() > 0 )
			glDrawElements(GL_QUADS, s->GetIndexList().size(), GL_UNSIGNED_INT, 0);
		// Otherwise, use normal drawing
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, s->GetVertexList().size());
		}
		check_gl_error_render();
	}
	counter = 0;
	// DEBUG DRAWING FOR COLLIDERS
	if (inputManager.isKeyPressed(sf::Keyboard::C))
	{
		for (auto iterator = SpriteList.begin(); iterator != SpriteList.end(); iterator++)
		{
			SpriteComponent * s = static_cast<SpriteComponent *>(*iterator); // Gets a reference to the Sprite Component of a Game Object to render
			PhysicsComponent * p = nullptr;
			p = static_cast<PhysicsComponent *>((*iterator)->mOwner->GetComponent(Component::PHYSICS));
			// Sprites without physics components are not drawn
			if (p == nullptr)
				continue;

			/*--------------------------- VERTEX ARRAY OBJECT --------------------------------*/
			glBindVertexArray(*VAO[counter]);
			/*--------------------------- VERTEX BUFFER OBJECT --------------------------------*/
			glBindBuffer(GL_ARRAY_BUFFER, *VBO[counter]);
			glBufferData(GL_ARRAY_BUFFER, p->GetVertexListCollider().size() * sizeof(VertexCollider), &(p->GetVertexListCollider()[0]), GL_STATIC_DRAW);
			/*--------------------------- ELEMENT ARRAY BUFFER --------------------------------*/
			if (p->GetIndexListCollider().size() > 0)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EAB[counter]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, p->GetIndexListCollider().size() * sizeof(GLuint), &(p->GetIndexListCollider()[0]), GL_STATIC_DRAW);
			}
			/*--------------------------- VERTEX ATTRIBUTE POINTERS --------------------------------*/
			// Position
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(VertexCollider),
				(GLvoid*)0
				);
			glEnableVertexAttribArray(0);
			// Color
			glVertexAttribPointer(
				1,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(VertexCollider),
				(GLvoid*)(3 * sizeof(GLfloat))
				);
			glEnableVertexAttribArray(1);
			// Texture Coordinates
			glVertexAttribPointer(
				2,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(VertexCollider),
				(GLvoid*)(7 * sizeof(GLfloat))
				);
			glEnableVertexAttribArray(2);
			counter++;
		}
		counter = 0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (auto iterator = SpriteList.begin(); iterator != SpriteList.end(); iterator++)
		{
			temp = (*(*iterator)->mOwner); // Gets a copy of the Gameobject owner of this Sprite Component to use for Transform calculations
			// Iterator is a pointer to a pointer, so it must be dereferenced twice
			SpriteComponent * s = static_cast<SpriteComponent *>(*iterator);
			TransformComponent * t = static_cast<TransformComponent *>(temp.GetComponent(Component::TRANSFORM));
			PhysicsComponent * p = static_cast<PhysicsComponent *>(temp.GetComponent(Component::PHYSICS));
			// Sprites without physics components are not drawn
			if (p == nullptr)
				continue;
			/*-------------------------------- MODEL MATRIX -------------------------------*/
			// Create the transformation / Model matrix
			Matrix3D Model;
			Matrix3D Scale;
			// Scales using the original values of the mesh
			Matrix3DIdentity(&Scale);
			
			Scale.m[0][0] = t->mOriginalScale.x;
			Scale.m[1][1] = t->mOriginalScale.y;
			Scale.m[2][2] = t->mOriginalScale.z;

			Matrix3DConcat(&Model, &(t->mTranslation), &(t->mRotation));
			Matrix3DConcat(&Model, &Model, &(Scale));
			windowManager.GetWin().setActive();
			// Uniform matrices ARE supplied in Row Major order hence set to GL_TRUE
			glUniformMatrix4fv(glModel, 1, GL_TRUE, &Model.m[0][0]);
			glBindVertexArray(*VAO[counter++]);
			check_gl_error_render();
			// If index list is specified, use Indexed Drawing
			if (p->GetIndexListCollider().size() > 0)
				glDrawElements(GL_QUADS, p->GetIndexListCollider().size(), GL_UNSIGNED_INT, 0);
			// Otherwise, use normal drawing
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, p->GetVertexListCollider().size());
			}
			check_gl_error_render();
		}
	}
	return true;
}
