#pragma once
#include <random>

class Randomizer
{
public:
	Randomizer(float aMinValue = 0.f, float aMaxValue = 1.f);
	~Randomizer();

	void SetMinMax(float aMinValue, float aMaxValue);

	float GetRandomValue();
	float GetRandomValue(float aMinValue, float aMaxValue);

private:
	std::default_random_engine myRandomGenerator;
	std::uniform_real_distribution<float> myDistribution;
};

