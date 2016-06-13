#include "DialogManager.h"
#include <JsonWrapper\JsonWrapper.h>

std::map<std::string, std::queue<std::string>>
LoadDialogs()
{
	std::map<std::string, std::queue<std::string>> data;

	JsonWrapper json;

	picojson::value root = json.LoadPicoValue("Data/Dialogs/dialogs.json");
	picojson::array dialogs = root.get("dialogs").get<picojson::array>();

	for (unsigned int i = 0; i < dialogs.size(); ++i)
	{
		std::string name = dialogs[i].get("name").to_str();
		std::string file("Data/Dialogs/");
		file.append(dialogs[i].get("file").to_str());

		std::queue<std::string> newDialog;

		picojson::value dialogFile = json.LoadPicoValue(file);
		picojson::array messages = dialogFile.get("dialog").get<picojson::array>();

		for (unsigned int j = 0; j < messages.size(); ++j)
		{
			newDialog.emplace(messages[j].get("text").to_str());
		}

		data[name] = newDialog;
	}

	return data;
}