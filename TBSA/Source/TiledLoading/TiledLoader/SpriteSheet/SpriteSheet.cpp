#include "stdafx.h"
#include "SpriteSheet.h"
#include "../../../Renderer/Rend/StaticSprite.h"


std::string SpriteSheet::ourFolder = "Sprites/SpriteSheets/";

SpriteSheet::SpriteSheet() : SpriteSheet("", CommonUtilities::Vector2f(0, 0), CommonUtilities::Vector2f(0, 0), "", 0)
{

}

SpriteSheet::SpriteSheet(const std::string& aName, const CommonUtilities::Vector2f& aSubImageSize, const CommonUtilities::Vector2f& aSheetSize, const std::string& aFileType, unsigned aFirstId)
{
	myName = aName;
	mySize = aSubImageSize;
	myFileFormat = aFileType;
	myFirstId = aFirstId;
	mySheetSize = aSheetSize;
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

StaticSprite* SpriteSheet::CreateSprite(unsigned aImageId, bool aGlobalId)
{
	int id = aImageId;
	if (aGlobalId == true)
	{
		id = aImageId - myFirstId;
	}

	const int column = id % static_cast<int>(mySheetSize.x / mySize.x);
	const int row = id / static_cast<int>(mySheetSize.x / mySize.x);

	CommonUtilities::Vector2f originPoint(mySize.x * column, mySize.y * row);
	CommonUtilities::Point4f rect(originPoint.x, originPoint.y, mySize.x, mySize.y);

	StaticSprite* sprite = new StaticSprite();
	sprite->Init(GetPath(), true, rect, false);
	sprite->SetLayer(enumRenderLayer::eFloor);

	return  sprite;
}

unsigned SpriteSheet::GetFirstIndex()
{
	return myFirstId;
}

std::string SpriteSheet::GetName()
{
	return  myName;
}
