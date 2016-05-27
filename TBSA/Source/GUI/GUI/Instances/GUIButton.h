#pragma once
#include "../Generic/GUIElement.h"

class GUIButton : public GUIElement
{
public:
	GUIButton();
	virtual ~GUIButton();

	virtual void Update(CommonUtilities::Time &aDelta) override;
protected:

};
