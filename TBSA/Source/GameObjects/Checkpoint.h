#pragma once

class Checkpoint
{
public:
	Checkpoint()
	{

	}
	~Checkpoint()
	{

	}

	void SetPosition(const CommonUtilities::Vector2f & aPos)
	{
		myPosition = aPos;
	}

	CU::Vector2f GetPosition() const
	{
		return myPosition;
	}

private:

	CU::Vector2f myPosition;
	bool myIsActivated;
};
