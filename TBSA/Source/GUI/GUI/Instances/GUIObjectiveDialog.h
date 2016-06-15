#include "GUI/Generic/GUIElement.h"
#include <TextBox.h>
#include <queue>

class GUIObjectiveDialog : public GUIElement
{
public:
	GUIObjectiveDialog(const CommonUtilities::Vector2f aPosition, const CommonUtilities::Vector2f aDimensions, const std::string aFontPath, const eLinewrappingMode aMode = eLinewrappingMode::Char);
	~GUIObjectiveDialog();
	void Render() override;
	void Update(const CU::Time& aTimeDelta) override;
	void SetLines(const unsigned int aLines);
	void Clear();
	void Toggle();
	bool RecieveMessage(const TextMessage& aMessage) override;
	bool RecieveMessage(const BaseMessage& aMessage) override;
private:
	TextBox myTextBox;
	StaticSprite* myTextBackground;

	//bool RecieveMessage(const ObjectiveTextMessage& aMessage) override;
};
