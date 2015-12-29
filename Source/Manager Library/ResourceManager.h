#pragma once
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
// SFML Texture header file 
#include <SFML\Graphics\Texture.hpp>
class ResourceManager
{
private:
	int **MapData;
	int BINARY_MAP_WIDTH;
	int BINARY_MAP_HEIGHT;
	sf::Image Image;
	std::string ImagePath;
public:
	int GetMapHeight() { return BINARY_MAP_HEIGHT; }
	int GetMapWidth() { return BINARY_MAP_WIDTH; }
	int ** GetMapData() { return MapData; }
	inline sf::Image const & GetImage() { return Image; }
	inline std::string const & GetImagePath() { return ImagePath; }
	bool SetImage(std::string imagePath)
	{
		ImagePath = imagePath;
		return Image.loadFromFile(imagePath);
	}
	ResourceManager();
	virtual ~ResourceManager();
	int ImportMapDataFromFile(char *pFileName);
};

