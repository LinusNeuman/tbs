#include "stdafx.h"
#include "LayerInputReciever.h"
#include <Message/MouseButtonDownMessage.h>
#include <Message/MouseButtonPressedMessage.h>
#include <Message/MouseButtonReleasedMessage.h>
#include <PostMaster/SingletonPostMaster.h>

LayerInputReciever::LayerInputReciever()
{
	myDownInput.Init(USHORTCAST(CU::enumMouseButtons::enumLength));
	myDownInput.Resize(USHORTCAST(CU::enumMouseButtons::enumLength));
	
	myPressedInput.Init(USHORTCAST(CU::enumMouseButtons::enumLength));
	myPressedInput.Resize(USHORTCAST(CU::enumMouseButtons::enumLength));

	myReleasedInput.Init(USHORTCAST(CU::enumMouseButtons::enumLength));
	myReleasedInput.Resize(USHORTCAST(CU::enumMouseButtons::enumLength));

	ResetInput();
	EnableReciever();
}


LayerInputReciever::~LayerInputReciever()
{
	DisableReceiver();
}

void LayerInputReciever::EnableReciever()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eMouseInput, *this);
}

void LayerInputReciever::DisableReceiver()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eMouseInput, *this);
}

bool LayerInputReciever::RecieveMessage(const MouseButtonDownMessage& aMessage)
{
	myDownInput[aMessage.myKey] = aMessage.myKeyValue;
	return true;
}

bool LayerInputReciever::RecieveMessage(const MouseButtonPressedMessage& aMessage)
{
	myPressedInput[aMessage.myKey] = aMessage.myKeyValue;
	return true;
}

bool LayerInputReciever::RecieveMessage(const MouseButtonReleasedMessage&aMessage)
{
	myReleasedInput[aMessage.myKey] = aMessage.myKeyValue;
	return true;
}

bool LayerInputReciever::RecieveMessage(const MouseInputClearMessage & aMessage)
{
	ResetInput();
	return true;
}







void LayerInputReciever::ResetInput()
{
	for (unsigned short iButton = 0; iButton < USHORTCAST(CU::enumMouseButtons::enumLength); ++iButton)
	{
		myDownInput[iButton] = false;
		myPressedInput[iButton] = false;
		myReleasedInput[iButton] = false;
	}
}