#pragma once

enum class eObjectiveType
{
	eLevelEnd,
	eDialogMessage
};

class Objective
{
public:
	Objective();
	Objective(std::string aDialogName);
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

	std::string myDialogMessageName;
	CU::Vector2f myPosition;
};

