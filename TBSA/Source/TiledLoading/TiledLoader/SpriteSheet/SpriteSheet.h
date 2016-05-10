// Author:   Hampus Huledal
// CreationDate: 10/05/2016
#pragma once
#include <CU/Vectors/vector2.h>
#include <string>

class WrappedSprite;

class SpriteSheet
{
public:
	SpriteSheet();
	SpriteSheet(const std::string& aName, const CommonUtilities::Vector2f& aSubImageSize, const std::string& aFileType, unsigned aFirstId);
	~SpriteSheet();

	static void SetFolder(const std::string & aPathToAFolder);

	std::string GetPath() const;
	
	WrappedSprite* CreateSprite(unsigned int aImageId, bool aUniqueId = true);
	unsigned int GetFirstIndex();
	std::string GetName();

private:
	static std::string ourFolder;

	std::string myFileFormat;
	std::string myName;

	unsigned int myFirstId;
	CommonUtilities::Vector2f mySize;
	
};
