#include "stdafx.h"
#include "SpriteSheet.h"
#include "../../../Renderer/Rend/WrappedSprite.h"


std::string SpriteSheet::ourFolder = "Sprites/SpriteSheets";

SpriteSheet::SpriteSheet() : SpriteSheet("", CommonUtilities::Vector2f(0,0), "", 0)
{

}

SpriteSheet::SpriteSheet(const std::string& aName,const CommonUtilities::Vector2f& aSubImageSize,const std::string& aFileType, unsigned int aFirstId)
{
	myName = aName;
	mySize = aSubImageSize;
	myFileFormat = aFileType;
	myFirstId = aFirstId;
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::SetFolder(const std::string & aPathToAFolder)
{
	ourFolder = aPathToAFolder;
}

std::string SpriteSheet::GetPath() const
{
	return ourFolder + myName + myFileFormat;
}

WrappedSprite* SpriteSheet::CreateSprite(unsigned /*aImageId*/, bool /*aUniqueId*/)
{
	//TODO : Add code to extract Subimages

	return new WrappedSprite();
}

unsigned SpriteSheet::GetFirstIndex()
{
	return myFirstId;
}

std::string SpriteSheet::GetName()
{
	return  myName;
}
