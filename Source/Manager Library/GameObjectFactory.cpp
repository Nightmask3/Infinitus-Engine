#include "GameObjectFactory.h"

void GameObjectFactory::CreateGameObject()
{
	GameObject gObject;
	ObjectLibrary.push_back(gObject);	// Pushes the game object into the object list
}
void GameObjectFactory::LoadObject(const char *pFileName)
{
	// Using C method of reading, as it has a significant speed advantage over C++ streams
	FILE *fp;
	unsigned int counter = 0;
	unsigned char tempC = '\0'; // Used to hold temporary character values for component names
	fp = fopen(pFileName, "rb");
	if (fp)
	{
		std::string componentName;
		componentName.reserve(256);
		std::string contents;
		//contents.reserve(2048);			 // To prevent reallocations
		std::fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp)); // Finds the size of the file and resizes the string 'contents' to match that size
		std::rewind(fp);				 // Resets the file pointer
		std::fread(&contents[0], 1, contents.size(), fp);
		std::fclose(fp);
		CreateGameObject();
		while (contents.at(counter) != '\0')		// While not end of the string
		{
			componentName = "";
			while ((contents.at(counter) != '\r')) // Reads character by character until new line
			{
				tempC = contents.at(counter++);
				componentName += tempC;			 // Gets type of component to create
			}
			if (strcmp(componentName.c_str(), "Sprite Component") == 0)	// Evaluates to 0 if it is true
			{	
				// SET THE COMPONENT VALUES HERE FROM THE FILE
				SpriteComponent * s = nullptr;
				CreateComponent<SpriteComponent>();
				s = static_cast<SpriteComponent *>(ObjectLibrary.back().GetComponent(Component::ComponentType::SPRITE));
				s->Serialize(contents, counter);
			}
			else if (strcmp(componentName.c_str(), "Transform Component") == 0)
			{
				// SET THE TRANSFORM COMPONENT VALUES HERE FROM THE FILE
				TransformComponent * t = nullptr;
				CreateComponent<TransformComponent>();
				t = static_cast<TransformComponent *>(ObjectLibrary.back().GetComponent(Component::ComponentType::TRANSFORM));
				t->Serialize(contents, counter);
			}
			else if (strcmp(componentName.c_str(), "Physics Component") == 0)
			{
				// SET THE COMPONENT VALUES HERE FROM THE FILE
				PhysicsComponent * p = nullptr;
				CreateComponent<PhysicsComponent>();
				p = static_cast<PhysicsComponent *>(ObjectLibrary.back().GetComponent(Component::ComponentType::PHYSICS));
				p->Serialize(contents, counter);
			}
			else if (strcmp(componentName.c_str(), "Keyboard Controller Component") == 0)
			{
				// SET THE COMPONENT VALUES HERE FROM THE FILE
				KeyboardControllerComponent * k = nullptr;
				CreateComponent<KeyboardControllerComponent>();
				k = static_cast<KeyboardControllerComponent *>(ObjectLibrary.back().GetComponent(Component::ComponentType::KBCONTROLLER));
			}
			counter += 3; // To skip newline and carriage return characters
			if (counter > contents.size())
				return;
		}
	}
}