#pragma once
#include "../Generic/GUIElement.h"

class GUIButton : public GUIElement
{
public:
	GUIButton();
	virtual ~GUIButton();

	void Create(const char* aName, const std::string& aSpritePath, CU::Vector2f aParentSpace, CU::Vector2f anOffset, CU::Vector2f aImageSize, bool aIsIsometric = false, bool aIsEnabled = true) override;

	void Update(const CU::Time &aDelta) override;

	void Render() override;

	void WhenHovered() override;
protected:
	StaticSprite* mySpritePressed;
	StaticSprite* mySpriteHovered;
	StaticSprite* mySpriteUnpressed;
};
