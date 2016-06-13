#pragma once
#include <Audio/Instances/SoundEffect.h>
#include "GUIButton.h"

class GUIChangePlayerButton : public GUIButton
{
public:
	GUIChangePlayerButton();
	virtual ~GUIChangePlayerButton();

	void Update(const CU::Time &aDelta) override;

	void WhenClicked() override;

	void Render() override;

	virtual bool RecieveMessage(const PlayerIDMessage & aMessage);
protected:
	int myPlayerID;
};