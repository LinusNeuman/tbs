#pragma once
#include <PostMaster/MessageReceiver.h>
#include <CU/InputWrapper/MouseButtonsEnum.h>

class LayerInputReciever : public MessageReciever
{
public:
	LayerInputReciever();
	~LayerInputReciever();

	void EnableReciever();
	void DisableReceiver();

	virtual bool RecieveMessage(const MouseButtonDownMessage& aMessage) override;
	virtual bool RecieveMessage(const MouseButtonPressedMessage& aMessage) override;
	virtual bool RecieveMessage(const MouseButtonReleasedMessage&aMessage) override;
	virtual bool RecieveMessage(const MouseInputClearMessage & aMessage) override;

	bool GetMouseButtonDown(const CU::enumMouseButtons aMouseButtonID);
	bool GetMouseButtonPressed(const CU::enumMouseButtons aMouseButtonID);
	bool GetMouseButtonReleased(const CU::enumMouseButtons aMouseButtonID);

	void SetMessageLetThrough(const bool aLetThroughFlag);

private:
	void ResetInput();

	bool myLetTroughMessagesFlag;

	CU::GrowingArray<bool> myDownInput;
	CU::GrowingArray<bool> myPressedInput;
	CU::GrowingArray<bool> myReleasedInput;
};

inline bool LayerInputReciever::GetMouseButtonDown(const CU::enumMouseButtons aMouseButtonID)
{
	return myDownInput[USHORTCAST(aMouseButtonID)];
}

inline bool LayerInputReciever::GetMouseButtonPressed(const CU::enumMouseButtons aMouseButtonID)
{
	return myPressedInput[USHORTCAST(aMouseButtonID)];
}

inline bool LayerInputReciever::GetMouseButtonReleased(const CU::enumMouseButtons aMouseButtonID)
{
	return myReleasedInput[USHORTCAST(aMouseButtonID)];
}

inline void LayerInputReciever::SetMessageLetThrough(const bool aLetThroughFlag)
{
	myLetTroughMessagesFlag = aLetThroughFlag;
}