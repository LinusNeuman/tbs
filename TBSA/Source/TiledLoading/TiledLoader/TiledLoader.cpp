#include "stdafx.h"
#include "TiledLoader.h"
#include "JsonHelp/JsonHelp.h"

#include <GameObjects/Room/IsometricTile.h>
#include "SpriteSheet/SpriteSheet.h"

#include "TiledData/TiledData.h"
#include <Rend/StaticSprite.h>
#include "PathAndName.h"
#include "Objective.h"



namespace
{
	const std::string fileEnding = ".dds";
}


CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType);

void GetPathNodes(const int aINdex, PathAndName & aPath, const picojson::array & someData, const int aMapWidth, const int aLastTile);


void TiledLoader::Load(std::string aFilePath, TiledData* aTilePointer)
{
	TiledData& someTiles = *aTilePointer;
	std::map<std::string, unsigned short> enemyIndexes;
	CommonUtilities::GrowingArray<PathAndName> paths;
	paths.Init(1);

	picojson::object rootObject = JsonHelp::LoadJson(aFilePath);

	CommonUtilities::GrowingArray<SpriteSheet> SpriteSheets = LoadSpriteSheets(JsonHelp::GetArray(rootObject["tilesets"]), fileEnding);
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

	unsigned int height = static_cast<unsigned int>(JsonHelp::GetNumber(rootObject["height"]));
	unsigned int width = static_cast<unsigned int>(JsonHelp::GetNumber(rootObject["width"]));

	someTiles.myMapSize = CommonUtilities::Point2ui(width, height);
	
	picojson::array layers = JsonHelp::GetArray(rootObject["layers"]);
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
		picojson::object currentLayer = JsonHelp::GetPicoJsonObject(layers[i]);
		std::string name = JsonHelp::GetString(currentLayer["name"]);
		std::string type = JsonHelp::GetString(currentLayer["type"]);

		if (type == "tilelayer")
		{
			picojson::array data = JsonHelp::GetArray(currentLayer["data"]);

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
						DL_ASSERT(SIZE_TTCAST(startNodeIndex) < data.size(), "ERROR: Path is missing start");
						const int explainingIndex = JsonHelp::GetNumberInt(data[startNodeIndex]);
						startNodeType = explainingIndex - dataSheet.GetFirstIndex() + 1;
					} while (startNodeType != 1);

					PathAndName tempPath;
					tempPath.myName = name.substr(lastUnderscore + 1, name.size() - lastUnderscore);
					tempPath.myPath.Add(CommonUtilities::Vector2ui(startNodeIndex % width, startNodeIndex / width));

					GetPathNodes(startNodeIndex, tempPath, data, width,5);

					paths.Add(tempPath);
				}
				else if (dataType == "covers" || dataType == "Covers")
				{
					for (size_t j = 0; j < data.size(); j++)
					{
						if (JsonHelp::GetNumberInt(data[j]) != 0)
						{
							someTiles.myTiles[j].SetTileType(eTileType::COVER);
						}
					}
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
						const int explainingInt = static_cast<int>(JsonHelp::GetNumber(data[j]));

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
					unsigned int tileId = static_cast<int>(JsonHelp::GetNumber(data[j]));
					if (tileId == 0)
					{
						continue;
					}

					for (size_t l = 0; l < SpriteSheets.Size(); ++l)
					{
						if (tileId >= SpriteSheets[l].GetFirstIndex() && (l == SpriteSheets.Size()- 1 || tileId < SpriteSheets[l + 1].GetFirstIndex()))
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
				picojson::array objects = JsonHelp::GetArray(currentLayer["objects"]);
				for (size_t k = 0; k < objects.size(); k++)
				{
						
					picojson::object player = JsonHelp::GetPicoJsonObject(objects[k]);
					eActorType playerType = eActorType::ePlayerOne;
					const std::string typeString = JsonHelp::GetString(player["type"]);
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

					const float posX = static_cast<float>(JsonHelp::GetNumber(player["x"])) / 64;
					const float posY = static_cast<float>(JsonHelp::GetNumber(player["y"])) / 64;

					playerActor->SetPosition(CommonUtilities::Vector2f(posX, posY));
					someTiles.myPlayers[playerIndex] = playerActor;
				}
			}
			else if (name == "Enemy" || name == "Enemies")
			{
				picojson::array objects = JsonHelp::GetArray(currentLayer["objects"]);
				for (size_t k = 0; k < objects.size(); k++)
				{
					picojson::object enemy = JsonHelp::GetPicoJsonObject(objects[k]);
					eActorType enemyType = eActorType::eEnemyOne;
					const std::string typeString = JsonHelp::GetString(enemy["type"]);
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

					const float posX = static_cast<float>(JsonHelp::GetNumber(enemy["x"])) / 64;
					const float posY = static_cast<float>(JsonHelp::GetNumber(enemy["y"])) / 64;

					enemyActor->SetPosition(CommonUtilities::Vector2f(posX, posY));
					enemyActor->SetName(JsonHelp::GetString(enemy["name"]));

					if (enemy.count("properties") > 0)
					{
						picojson::object properties = JsonHelp::GetPicoJsonObject(enemy["properties"]);

						if (properties.count("direction") > 0)
						{
							const std::string direction = JsonHelp::GetString(properties["direction"]);
							if (direction == "N")
							{
								enemyActor->SetDirection(eDirection::NORTH);
							}
							else if(direction == "NE")
							{
								enemyActor->SetDirection(eDirection::NORTH_EAST);
							}
							else if (direction == "E")
							{
								enemyActor->SetDirection(eDirection::EAST);
							}
							else if (direction == "SE")
							{
								enemyActor->SetDirection(eDirection::SOUTH_EAST);
							}
							else if (direction == "S")
							{
								enemyActor->SetDirection(eDirection::SOUTH);
							}
							else if (direction == "SW")
							{
								enemyActor->SetDirection(eDirection::SOUTH_WEST);
							}
							else if (direction == "W")
							{
								enemyActor->SetDirection(eDirection::WEST);
							}
							else if (direction == "NW")
							{
								enemyActor->SetDirection(eDirection::NORTH_WEST);
							}
						}
					}

					someTiles.myEnemies.Add(enemyActor);

					enemyIndexes[JsonHelp::GetString(enemy["name"])] = someTiles.myEnemies.Size() - 1;
				}
			}
			else if (name == "Objective" || name == "Objectives")
			{
				picojson::array objects = JsonHelp::GetArray(currentLayer["objects"]);
				for (size_t k = 0; k < objects.size(); k++)
				{
					picojson::object goal = JsonHelp::GetPicoJsonObject(objects[k]);
					eObjectiveType objectiveType = eObjectiveType::eLevelEnd;
					const std::string typeString = JsonHelp::GetString(goal["type"]);

					const float posX = static_cast<float>(JsonHelp::GetNumber(goal["x"])) / 64;
					const float posY = static_cast<float>(JsonHelp::GetNumber(goal["y"])) / 64;

					if (typeString == "LevelEnd")
					{
						objectiveType = eObjectiveType::eLevelEnd;
					}
					else if (typeString == "Sweet" || typeString == "Candy")
					{
						objectiveType = eObjectiveType::eLevelEnd;
						const SIZE_T index = someTiles.myMapSize.x * static_cast<int>(posY) + static_cast<int>(posX);
						someTiles.myTiles[index].SetHasCandy();
					}
					else 
					{
						DL_ASSERT(false, "ERROR:  Objective type does not exist");
					}

					Objective* const objectiveObject = someTiles.myObjectiveFactory->CreateObjective(objectiveType);



					objectiveObject->SetPosition(CommonUtilities::Vector2f(posX, posY));
					someTiles.myObjectives.Add(objectiveObject);

					someTiles.myObjectiveManager->AddObjective(1000 * static_cast<int>(posY)+static_cast<int>(posX), JsonHelp::GetString(goal["name"]));
				}
			}
		}
	}

	for (size_t i = 0; i < paths.Size(); i++)
	{
		const int enemyIndex = enemyIndexes[paths[i].myName];
		someTiles.myEnemies[enemyIndex]->SetEnemyPath(paths[i].myPath);
	}
	someTiles.myIsLoaded = true;
}


CommonUtilities::GrowingArray<SpriteSheet> LoadSpriteSheets(const picojson::array& aSpriteSheetArray, std::string aFileType)
{
	CommonUtilities::GrowingArray<SpriteSheet> returnArray;
	returnArray.Init(2);

	for (size_t i = 0; i < aSpriteSheetArray.size(); ++i)
	{
		picojson::object  currentObject = JsonHelp::GetPicoJsonObject(aSpriteSheetArray[i]);

		std::string name = JsonHelp::GetString(currentObject["name"]);
		unsigned int firstId = static_cast<unsigned int>(JsonHelp::GetNumber(currentObject["firstgid"]));
		CommonUtilities::Vector2f size = JsonHelp::GetVector2f(currentObject["tilewidth"], currentObject["tileheight"]);
		CommonUtilities::Vector2f sheetSize = JsonHelp::GetVector2f(currentObject["imagewidth"], currentObject["imageheight"]);

		returnArray.Add(SpriteSheet(name, size, sheetSize, aFileType, firstId));
	}

	return returnArray;
}

void GetPathNodes(const int aIndex, PathAndName& aPath, const picojson::array& someData, const int aMapWidth, const int aLastTile)
{

	
	if (aLastTile != 3 && aIndex + 1 < INTCAST(someData.size()) && JsonHelp::GetNumberInt(someData[aIndex + 1]) >= 1)
	{
		int index = aIndex + 1;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 0);
		return;
	}
	if (aLastTile != 2 && aIndex + aMapWidth < INTCAST(someData.size()) && JsonHelp::GetNumberInt(someData[aIndex + aMapWidth]) >= 1)
	{
		int index = aIndex + aMapWidth;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 1);
		return;
	}
	if (aLastTile != 1 && aIndex - aMapWidth >= 0 && JsonHelp::GetNumberInt(someData[aIndex - aMapWidth]) >= 1)
	{
		int index = aIndex - aMapWidth;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 2);
		return;
	}
	if (aLastTile != 0 && aIndex - 1 >= 0 && JsonHelp::GetNumberInt(someData[aIndex - 1]) >= 1)
	{
		int index = aIndex - 1;
		aPath.myPath.Add(CommonUtilities::Vector2ui(index % aMapWidth, index / aMapWidth));
		GetPathNodes(index, aPath, someData, aMapWidth, 3);
		return;
	}
}
