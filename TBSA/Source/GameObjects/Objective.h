#pragma once

enum class eObjectiveType
{
	eLevelEnd
};

class Objective
{
public:
	Objective();
	~Objective();

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
};

