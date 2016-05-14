#pragma once

#include <GUI/Generic/GUIElement.h>
#include <unordered_map>

struct GUIIndexRange
{
	uchar myBegin;
	uchar myEnd;
};

class GUIFactory
{
public:
	~GUIFactory();

	static GUIFactory* const GetInstance()
	{
		return myInstance;
	}

	static void Create()
	{
		if (myInstance == nullptr)
		{
			myInstance = new GUIFactory();
		}
	}

	void Load();
	void Reload();

	//GUIElement* GetGUIElement(std::string aName);

	CU::GrowingArray<GUIElement*, uchar>& GetLoadedGUI(const char* aStateName);
private:
	GUIFactory();

	static GUIFactory* myInstance;

	//void LoadGUI();
	//void ReloadGUI();

	CU::GrowingArray<GUIElement*, uchar> myGUIElements;

	std::unordered_map<std::string, GUIIndexRange> myGUILookup;
};
