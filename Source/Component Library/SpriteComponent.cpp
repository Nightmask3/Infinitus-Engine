#include "SpriteComponent.h"

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Serialize(FILE **pFile)
{
	char imageName[256];

	memset(imageName, 0, 246 * sizeof(char));

	fscanf_s(*pFile, "%255s\n", imageName, sizeof(imageName));

	std::string fullPath = "..\\Resources\\";
	fullPath += imageName; // Concatenates the string Full path with image Name
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
	for (auto i = VertexList.begin(); i != VertexList.end(); i++)
	{
		temp = &*i;
		temp->R = list[count++];
		temp->G = list[count++];
		temp->B = list[count++];
	}
}
void SpriteComponent::Update(){}