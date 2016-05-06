#pragma once


class RenderConverter;
class WrappedSprite;

class Player
{
public:
	Player(RenderConverter* aRenderConverter);
	~Player();
	void Update(const CU::Time aDeltaTime);
	void Draw() const;
	void Move(CU::Vector2f aTargetPosition, const CU::Time  aDeltaTime);
	unsigned GetSizeX() const;
	unsigned GetSizeY() const;

	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}
private:
	WrappedSprite *mySprite;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myTargetPosition;
};

