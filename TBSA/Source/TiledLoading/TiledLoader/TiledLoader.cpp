#include "stdafx.h"
#include "TiledLoader.h"
#include <JSON/JSONWrapper.h>
#include <CU/Utility/FileHandling.h>

#include <GameObjects/Room/IsometricTile.h>
#include "SpriteSheet/SpriteSheet.h"
#include <JsonWrapper/JsonWrapper.h>

#include "TiledData/TiledData.h"
#include <Rend/StaticSprite.h>
#include "PathAndName.h"

namespace
{
	const std::string fileEnding = ".png";
}


picojson::object GetObject(picojson::value aValue);
double& GetNumber( picojson::value aValue);
picojson::array GetArray( picojson::value aValue);
std::string GetString( picojson::value aValue);
CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue);

CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType);

void GetPathNodes(const int aINdex, PathAndName & aPath, const picojson::array & someData, const int aMapWidth, const int aLastTile);


void TiledLoader::Load(std::string aFilePath, TiledData& someTiles)
{
	std::map<std::string, unsigned short> enemyIndexes;
	CommonUtilities::GrowingArray<PathAndName> paths;
	paths.Init(1);

	picojson::value root;
	
	std::string JsonData = CommonUtilities::GetFileAsString(aFilePath);
	std::string err = picojson::parse(root , JsonData);
	
	DL_ASSERT(err.empty(), (std::string("ERROR from Json: ") + err).c_str());


	picojson::object rootObject = JsonWrapper::GetPicoObject(root);

	CommonUtilities::GrowingArray<SpriteSheet> SpriteSheets = LoadSpriteSheets(GetArray(rootObject["tilesets"]), fileEnding);
	SpriteSheet dataSheet;
	size_t dataSheetIndex = INT_MAX;

	for (size_t i = 0; i < SpriteSheets.Size(); i++)
	{
		std::string name = SpriteSheets[i].GetName();
		if (name[0] == '_')
		{
			dataSheet = SpriteSheets[i];
			dataSheetIndex = i;
			break;
		}
	}

	unsigned int height = static_cast<unsigned int>(GetNumber(rootObject["height"]));
	unsigned int width = static_cast<unsigned int>(GetNumber(rootObject["width"]));

	someTiles.myMapSize = CommonUtilities::Point2ui(width, height);
	
	picojson::array layers = GetArray(rootObject["layers"]);
	bool loadedObjects = false;
	for (size_t i = 0; i < height * width; i++)
	{
		IsometricTile newTile = IsometricTile(CommonUtilities::Vector2f(static_cast<float>(i % width), static_cast<float>(static_cast<int>(i / width))));
		newTile.Init();
		someTiles.myTiles.Add(newTile);
	}

	bool isOverFloor = false;
	for (size_t i = 0; i < layers.size(); ++i)
	{
		picojson::object currentLayer = GetObject(layers[i]);
		std::string name = GetString(currentLayer["name"]);
		std::string type = GetString(currentLayer["type"]);

		if (type == "tilelayer")
		{
			picojson::array data = GetArray(currentLayer["data"]);

			if (name[0] == '_')
			{
				
				isOverFloor = true;
				unsigned int lastUnderscore = name.find_last_of('_');


				const std::string dataType = name.substr(1, lastUnderscore - 1);
				if (dataType == "path" || dataType == "Path")
				{
					int startNodeIndex = -1;
					int startNodeType = 0;
					do
					{
						++startNodeIndex;
						DL_ASSERT(startNodeIndex < data.size(), "ERROR: Path is missing start");
						const int explainingIndex = GetNumber(data[startNodeIndex]);
						startNodeType = explainingIndex - dataSheet.GetFirstIndex() + 1;
					} while (startNodeType != 1);

					PathAndName tempPath;
					tempPath.myName = name.substr(lastUnderscore + 1, name.size() - lastUnderscore);
					tempPath.myPath.Add(CommonUtilities::Vector2ui(startNodeIndex % width, startNodeIndex / width));

					GetPathNodes(startNodeIndex, tempPath, data, width,5);

					paths.Add(tempPath);
				}
				else
				{
					
					unsigned int roomId;
					try
					{
						roomId = std::stoi(name.substr(lastUnderscore + 1, name.size() - lastUnderscore));
					}
					catch (std::invalid_argument)
					{
						roomId = 0;
						DL_ASSERT(false, "ERROR! layers with a name starting with underscore is data layer and needs a number in the en preceeded by another underscore")
					}

					for (size_t j = 0; j < data.size(); j++)
					{
						const int explainingInt = static_cast<int>(GetNumber(data[j]));

						IsometricTile& newTile = someTiles.myTiles[j];

						newTile.SetRoomId(roomId);

						int tileId = static_cast<int>(explainingInt - dataSheet.GetFirstIndex() + 1);
						if (tileId < 0 || tileId >= static_cast<int>(eTileType::Size))
						{
							tileId = 0;
						}

						eTileType tileType = static_cast<eTileType>(tileId);

						newTile.SetTileType(tileType);
						if (tileType == eTileType::DOOR || tileType == eTileType::DOOR_2)
						{
							newTile.SetDoor(Door(roomId));
						}
					}
				}
			}
			else
			{
				for (size_t j = 0; j < data.size(); ++j)
				{
					unsigned int tileId = static_cast<int>(GetNumber(data[j]));
					if (tileId == 0)
					{
						continue;
					}

					for (size_t l = 0; l < SpriteSheets.Size(); ++l)
					{
						if (tileId >= SpriteSheets[l].GetFirstIndex() && dataSheetIndex != l)
						{
							SpriteSheet explainingSpriteSheet = SpriteSheets[l];
							StaticSprite* explaingSprite = explainingSpriteSheet.CreateSprite(tileId);

							if (isOverFloor == true)
							{
								explaingSprite->SetLayer(enumRenderLayer::eGameObjects);
							}
							else
							{
								explaingSprite->SetLayer(enumRenderLayer::eFloor);
							}

							someTiles.myTiles[j].AddSpriteLayer(explaingSprite);
						}
					}
				}
			}
		}
		else if (type == "objectgroup")
		{
			if (name == "Players" || name == "Player")
			{
				picojson::array objects = GetArray(currentLayer["objects"]);
				for (size_t k = 0; k < objects.size(); k++)
				{
						
					picojson::object player = GetObject(objects[k]);
					eActorType playerType = eActorType::ePlayerOne;
					const std::string typeString =  GetString(player["type"]);
					int playerIndex;
					if (typeString == "Player1")
					{
						playerType = eActorType::ePlayerOne;
						playerIndex = 0;
					}
					else if (typeString == "Player2")
					{
						playerType = eActorType::ePlayerTwo;
						playerIndex = 1;
					}
					else
					{
						DL_ASSERT(false, "ERROR:  Player type does not exist");
						playerIndex = 0;
					}

					Player *const playerActor = someTiles.myPlayerFactory->CreatePlayer(playerType);

					const float posX = static_cast<float>(GetNumber(player["x"])) / 64;
					const float posY = static_cast<float>(GetNumber(player["y"])) / 64;

					playerActor->SetPosition(CommonUtilities::Vector2f(posX, posY));
					someTiles.myPlayers[playerIndex] = playerActor;
				}
			}
			else if (name == "Enemy" || name == "Enemies")
			{
				picojson::array objects = GetArray(currentLayer["objects"]);
				for (size_t k = 0; k < objects.size(); k++)
				{
					picojson::object enemy = GetObject(objects[k]);
					eActorType enemyType = eActorType::eEnemyOne;
					const std::string typeString = GetString(enemy["type"]);
					if (typeString == "Enemy1")
					{
						enemyType = eActorType::eEnemyOne;
					}
					else if (typeString == "Enemy2")
					{
						enemyType = eActorType::eEnemyTwo;
					}
					else if (typeString == "Enemy3")
					{
						enemyType = eActorType::eEnemyThree;
					}
					else if (typeString == "Enemy4")
					{
						enemyType = eActorType::eEnemyFour;
					}
					else if (typeString == "Enemy5")
					{
						enemyType = eActorType::eEnemyFive;
					}
					else
					{
						DL_ASSERT(false, "ERROR:  Player type does not exist");
					}

					Enemy *const enemyActor = someTiles.myEnemyFactory->CreateEnemy(enemyType);

					const float posX = static_cast<float>(GetNumber(enemy["x"])) / 64;
					const float posY = static_cast<float>(GetNumber(enemy["y"])) / 64;

					enemyActor->SetPosition(CommonUtilities::Vector2f(posX, posY));
					someTiles.myEnemies.Add(enemyActor);

					enemyIndexes[GetString(enemy["name"])] = someTiles.myEnemies.Size() - 1;
				}
			}
		}
	}

	for (size_t i = 0; i < paths.Size(); i++)
	{
		const int enemyIndex = enemyIndexes[paths[i].myName];
		someTiles.myEnemies[enemyIndex]->SetEnemyPath(paths[i].myPath);
	}
}

picojson::object GetObject(picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::object>(), "ERROR: Json value is not an object");
	return aValue.get<picojson::object>();
}

double& GetNumber(picojson::value aValue)
{
	DL_ASSERT(aValue.is<double>(), "ERROR: Json value is not a number");
	return aValue.get<double>();
}

picojson::array GetArray( picojson::value aValue)
{
	DL_ASSERT(aValue.is<picojson::array>(), "ERROR: Json value is not an array");
	return aValue.get<picojson::array>();
}

std::string GetString( picojson::value aValue)
{
	DL_ASSERT(aValue.is<std::string>(), "ERROR: Json value is not a string");
	return aValue.get<std::string>();
}

CommonUtilities::Vector2f GetVector2f(const picojson::value& aXValue, const picojson::value& aYValue)
{
	const float x = static_cast<float>(GetNumber(aXValue));
	const float y = static_cast<float>(GetNumber(aYValue));

	return CommonUtilities::Vector2f(x, y);
}

CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType)
{
	CommonUtilities::GrowingArray<SpriteSheet> returnArray;
	returnArray.Init(2);

	for (size_t i = 0; i < aSpriteSheetArray.size(); ++i)
	{
		picojson::object  currentObject = GetObject(aSpriteSheetArray[i]);

		std::string name = GetString(currentObject["name"]);
		unsigned int firstId = static_cast<unsigned int>(GetNumber(currentObject["firstgid"]));
		CommonUtilities::Vector2f size = GetVector2f(currentObject["tilewidth"], currentObject["tileheight"]);
		CommonUtilities::Vector2f sheetSize = GetVector2f(currentObject["imageheight"], currentObject["imagewidth"]);

		returnArray.Add(SpriteSheet(name, size, sheetSize, aFileType, firstId));
	}

	return returnArray;
}

void GetPathNodes(const int aIndex, PathAndName& aPath, const picojson::array& someData, const int aMapWidth, const int aLastTile)
{

	
	if (aLastTile != 3 && aIndex + 1 < someData.size() && GetNumber(someData[aIndex + 1]) >= 1)
	{
		int index = aIndex + 1;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 0);
		return;
	}
	if (aLastTile != 2 && aIndex + aMapWidth < someData.size() && GetNumber(someData[aIndex + aMapWidth]) >= 1)
	{
		int index = aIndex + aMapWidth;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 1);
		return;
	}
	if (aLastTile != 1 && aIndex - aMapWidth >= 0 && GetNumber(someData[aIndex - aMapWidth]) >= 1)
	{
		int index = aIndex - aMapWidth;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 2);
		return;
	}
	if (aLastTile != 0 && aIndex - 1 >= 0 && GetNumber(someData[aIndex - 1]) >= 1)
	{
		int index = aIndex - 1;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 3);
		return;
	}
}
