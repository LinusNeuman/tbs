#pragma once


class RenderConverter;
class WrappedSprite;

class Player
{
public:
	Player(const CU::Vector2f &aStartPosition, const unsigned aId);
	~Player();
	void Update(const CU::Time aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2f aTargetPosition, const CU::Time  aDeltaTime);
	unsigned GetSizeX() const;
	unsigned GetSizeY() const;
	void SetSelected(const bool aValue);

	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}
	unsigned GetPlayerId() const
	{
		return myId;
	}
	bool GetIsSelected() const
	{
		return myIsSelected;
	}
private:
	WrappedSprite *mySprite;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myTargetPosition;
	unsigned myId;
	bool myIsSelected;
};

