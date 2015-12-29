#include "SpriteComponent.h"

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Serialize(std::string & Contents, unsigned int & Count)
{
	unsigned char tempC;
	unsigned int tempI;
	std::string::size_type end;			// size_type is a typedef-ed type that is used to guarantee that no matter how large the size of the input file, it can be contained (example : if larger than int)
	std::string DataType;				// Used to check the type of data being supplied before adding to corresponding list
	std::string TempData;				// Used to get the different vertex properties into their respective list
	std::vector<GLfloat> TempArray;
	GLfloat TempFloat = 0.0f;

	DataType.reserve(64);

	tempI = Count + 2;
	// SPHERE CREATION
	while ((Contents.at(tempI) != '\r')) // Reads character by character until new line
	{
		tempC = Contents.at(tempI++);
		DataType += tempC;				// Gets type of component to create
	}
	if (strcmp(DataType.c_str(), "Sphere") == 0)
	{
		// Get radius of sphere here
		CreatePrimitive(SPHERE);
		Count = tempI + 8;
		tempC = Contents.at(Count);
		return;
	}
	else
		DataType = "";
	Count += 2;							// To skip newline and '{'
	while (Contents.at(Count) != '\0')
	{
		while ((Contents.at(Count) != '\r')) // Reads character by character until new line
		{
			tempC = Contents.at(Count++);
			DataType += tempC;				// Gets type of component to create
		}
		Count += 4;							// To skip the newline character and the '{'
		end = Contents.find('}', Count);				// Finds the end of the current vertex property array
		TempData = Contents.substr(Count, end - Count); // Second parameter is the length of the string
		std::istringstream TempStream(TempData);		// Gets a string stream constructed from the temp data string
		std::string Token;
		while (std::getline(TempStream, Token, ','))
		{
			TempFloat = strtof(Token.c_str(), NULL);
			TempArray.push_back(TempFloat);
		}
		
		if (strcmp(DataType.c_str(), "Vertices") == 0)
		{
			SetVertexList(&TempArray[0], TempArray.size() / 3);
		}
		else if (strcmp(DataType.c_str(), "Colors") == 0)
		{
			SetVertexColorList(&TempArray[0]);
		}
		else if (strcmp(DataType.c_str(), "UVs") == 0)
		{
			SetTextureCoordList(&TempArray[0]);
		}
		/*if (strcmp(DataType.c_str(), "Indices") == 0) TODO : ADD SUPPORT FOR INDEX SERIALIZATION
		{
			SetIndexList(&TempArray[0], TempArray.size());
		}*/
		Count = end + 3; // To skip the \r and \n characters
		if (Count > Contents.size() || Contents.at(Count) == '-')// Serialization of this component complete
			return;
		DataType = "";
	}
}
void SpriteComponent::SetVertexList(GLfloat list[], GLuint number)
{
	GLuint i = 0;
	Vertex temp;
	while (i < 3 * number)
	{
		temp.X = list[i++];
		temp.Y = list[i++];
		temp.Z = list[i++];
		VertexList.push_back(temp);
	}
}
void SpriteComponent::SetIndexList(GLuint list[], GLuint number)
{
	for (GLuint i = 0; i < number; i++)
	{
		IndexList.push_back(list[i]);
	}
}
void SpriteComponent::SetVertexColorList(GLfloat list[])
{
	Vertex * temp;
	GLuint count = 0;
	for (auto i = VertexList.begin(); i != VertexList.end(); ++i)
	{
		temp = &*i;
		temp->R = list[count++];
		temp->G = list[count++];
		temp->B = list[count++];
		temp->A = 1;
	}
}

void SpriteComponent::SetTextureCoordList(GLfloat list[])
{
	Vertex * temp;
	GLuint count = 0;
	for (auto i = VertexList.begin(); i != VertexList.end(); i++)
	{
		temp = &*i;
		temp->U = list[count++];
		temp->V = list[count++];
	}
}

void SpriteComponent::CreatePrimitive(SHAPE_PRIMITIVE shape)
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLuint> indices;
	if (shape == SPHERE)
	{
		float radius = 1.0;
		unsigned int rings = 20, sectors = 30;
		float const R = 1. / (float)(rings - 1);
		float const S = 1. / (float)(sectors - 1);
		unsigned int r, s;

		shapeType = SPHERE;
		vertices.resize(rings * sectors * 3);
		normals.resize(rings * sectors * 3);
		texcoords.resize(rings * sectors * 2);
		std::vector<GLfloat>::iterator v = vertices.begin();
		std::vector<GLfloat>::iterator n = normals.begin();
		std::vector<GLfloat>::iterator t = texcoords.begin();
		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
			float const y = sin(-PI/2 + PI * r * R);
			float const x = cos(2 * PI * s * S) * sin(PI * r * R);
			float const z = sin(2 * PI * s * S) * sin(PI * r * R);

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = -x;
			*n++ = -y;
			*n++ = -z;
		}

		indices.resize(rings * sectors * 4);
		std::vector<GLuint>::iterator i = indices.begin();
		for (r = 0; r < rings - 1; r++)
			for (s = 0; s < sectors - 1; s++) {
				/*
				*i++ = r * sectors + s;
				*i++ = r * sectors + (s+1);
				*i++ = (r+1) * sectors + (s+1);
				*i++ = (r+1) * sectors + s;
				*/
				*i++ = (r + 1) * sectors + s;
				*i++ = (r + 1) * sectors + (s + 1);
				*i++ = r * sectors + (s + 1);
				*i++ = r * sectors + s;
			}
	}
	SetVertexList(&vertices[0], vertices.size()/3); // For reasons, to make it compatible with how the Set vertex list function is currently written
	SetIndexList(&indices[0], indices.size());
	std::vector<GLfloat> colors;
	colors.reserve(vertices.size());
	for (auto i = vertices.begin(); i != vertices.end(); ++i)
		colors.push_back(0.5f);
	SetVertexColorList(&colors[0]);
	SetTextureCoordList(&texcoords[0]);
}

void SpriteComponent::Update(){}

void SpriteComponent::SetTextureHandle(GLuint handle)
{
	mTextureHandle = handle;
}