#include "../CommonUtilities/CU/Vectors/vector2.h"
#include "../CommonUtilities/CU/Vectors/vector4.h"
#include "../CommonUtilities/CU/Timer/Time.h"
#include "WrappedSprite.h"
#include "Renderer.h"

struct ParticleEmitterData
{
	bool IsActive = false;
	bool RotateSpritesOverTime = true;
	bool CanRotateCW = false;
	bool CanRotateCCW = true;
	bool PulseEmission = false;
	bool FadeIn = false;
	bool FadeOut = false;
	bool DieOnMagnetImpact = true;
	int	PulseEmissionAmount = 0;
	float PulseTimer = 0.f;
	float PulseRate = 0.f;
	float KillTimeLimit = 0.2f;
	float TimeSinceLastEmission = 0.f;
	float EmissionRate = 0.01f;
	float CurrentLifetime = 0.f;
	float LifetimeGoal = 0.1f;
	float MinParLifetime = 2.0f;
	float MaxParLifetime = 5.0f;
	float MinParFadeoutTime = 0.5f;
	float MaxParFadeoutTime = 1.0f;
	float MinParFadeinTime = 0.5f;
	float MaxParFadeinTime = 1.0f;
	float MinParRed = 1.f;
	float MaxParRed = 1.;
	float MinParGreen = 1.f;
	float MaxParGreen = 1.f;
	float MinParBlue = 1.f;
	float MaxParBlue = 1.f;
	float MinParSize = 1.f;
	float MaxParSize = 1.f;
	float MinParRotationSpeed = 10.f;
	float MaxParRotationSpeed = 25.f;
	GameObject* myMagnetTarget = nullptr;
	CommonUtilities::Vector2f Position;
	CommonUtilities::Vector2f Dimensions;
	CommonUtilities::Vector2f MinParEmissionVel = { -150.f, -150.f };
	CommonUtilities::Vector2f MaxParEmissionVel = { 150.f, 150.f };
};

template<unsigned int COUNT>
struct ParticleData
{
	bool IsActive[COUNT];
	bool RotateCCW[COUNT];
	float FadeInTime[COUNT];
	float FadeOutTime[COUNT];
	float Lifetime[COUNT];
	float LifetimeGoal[COUNT];
	float RotationSpeed[COUNT];
	Vector2f Position[COUNT];
	Vector2f Velocity[COUNT];
	DX2D::CColor Color[COUNT];
	WrappedSprite Sprite[COUNT];
};

template<unsigned int COUNT>
class ParticleEmitter
{
	public:

		ParticleEmitter();
		~ParticleEmitter();

		void Update(CU::Time aTime);
		void Activate(Vector2f aPosition);
		void LoadEmitterSettings(const std::string& aFileName);
		void SetPosition(const Vector2f aPos);
		void ResetEmitter();
		void SetMagnetTarget(GameObject* aTarget);
		void SetEmitterSize(Vector2f aSize);
		void SetDieOnMagnetImpact(bool aBool);
		bool IsActive();

	private:

		void KillParticle(unsigned int aIndex);
		void ResetParticle(unsigned int aIndex);
		void UpdateParticle(unsigned int aIndex, CU::Time aTime);
		Vector2f GenerateNewParticlePos();

		ParticleEmitterData myData;
		ParticleData<COUNT> myParticleData;
};

template<unsigned int COUNT>
ParticleEmitter<COUNT>::ParticleEmitter()
{
}

template<unsigned int COUNT>
ParticleEmitter<COUNT>::~ParticleEmitter()
{
	for (unsigned int i = 0; i < COUNT; ++i)
	{
		SpriteManager::GetInstance()->DestroySprite(myParticleData.Sprite[i]);
	}
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::ResetParticle(unsigned int aIndex)
{
	float sizeScale = myData.MinParSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParSize - myData.MinParSize)));

	myParticleData.Position[aIndex] = myData.Position;
	myParticleData.Lifetime[aIndex] = 0;
	myParticleData.IsActive[aIndex] = false;
	myParticleData.FadeInTime[aIndex] = myData.MinParFadeinTime + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParFadeinTime - myData.MinParFadeinTime)));
	myParticleData.FadeOutTime[aIndex] = myData.MinParFadeoutTime + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParFadeoutTime - myData.MinParFadeoutTime)));
	myParticleData.LifetimeGoal[aIndex] = myData.MinParLifetime + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParLifetime - myData.MinParLifetime)));
	myParticleData.Color[aIndex].myR = myData.MinParRed + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParRed - myData.MinParRed)));
	myParticleData.Color[aIndex].myG = myData.MinParGreen + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParGreen - myData.MinParGreen)));
	myParticleData.Color[aIndex].myB = myData.MinParBlue + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParBlue - myData.MinParBlue)));
	myParticleData.Color[aIndex].myA = 0.f;
	myParticleData.Sprite[aIndex]->SetSize({1.f, 1.f});
	myParticleData.Sprite[aIndex]->SetSize(myParticleData.Sprite[aIndex]->GetSize() * sizeScale);
	myParticleData.Sprite[aIndex]->SetColor(myParticleData.Color[aIndex]);
	myParticleData.Velocity[aIndex].x = myData.MinParEmissionVel.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParEmissionVel.x - myData.MinParEmissionVel.x)));
	myParticleData.Velocity[aIndex].y = myData.MinParEmissionVel.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParEmissionVel.y - myData.MinParEmissionVel.y)));
	myParticleData.RotationSpeed[aIndex] = myData.MinParRotationSpeed + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.MaxParRotationSpeed - myData.MinParRotationSpeed)));

	if (myData.CanRotateCW == true && myData.CanRotateCCW == true)
	{
		if (rand() % 2 == 0)
		{
			myParticleData.RotateCCW[aIndex] = false;
		}
		else
		{
			myParticleData.RotateCCW[aIndex] = true;
		}
	}
	else
	{
		if (myData.CanRotateCW == true)
		{
			myParticleData.RotateCCW[aIndex] = false;
		}
		else if (myData.CanRotateCCW == true)
		{
			myParticleData.RotateCCW[aIndex] = true;
		}
	}
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::Update(CU::Time aTime)
{
	if (myData.IsActive == true)
	{
		myData.TimeSinceLastEmission += aTime.GetSeconds();

		while(myData.TimeSinceLastEmission >= myData.EmissionRate && myData.CurrentLifetime < myData.LifetimeGoal)
		{
			bool emitted = false;

			for (int i = 0; i < COUNT; ++i)
			{
				if (myParticleData.IsActive[i] == false)
				{
					myParticleData.IsActive[i] = true;
					myParticleData.Position[i] = GenerateNewParticlePos();
					emitted = true;
					break;
				}
			}

			if (emitted == true)
			{
				myData.TimeSinceLastEmission -= myData.EmissionRate;
			}
			else
			{
				break;
			}
		}

		myData.CurrentLifetime += aTime.GetSeconds();

		if (myData.CurrentLifetime >= myData.LifetimeGoal && myData.LifetimeGoal > 0.f)
		{
			bool readyToDie = true;

			for (int i = 0; i < COUNT; ++i)
			{
				if (myParticleData.IsActive[i] == true)
				{
					readyToDie = false;
					break;
				}
			}

			if (readyToDie == true)
			{
				myData.IsActive = false;
			}
		}
	}

	if (myData.PulseEmission == true)
	{
		myData.PulseTimer += aTime.GetSeconds();
	}

	for (int i = 0; i < COUNT; ++i)
	{
		if (myParticleData.IsActive[i] == true)
		{
			UpdateParticle(i, aTime);
		}
	}
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::Activate(Vector2f aPosition)
{
	myData.Position = aPosition;

	if (myData.PulseEmission == true && myData.PulseTimer >= myData.PulseRate)
	{
		myData.PulseTimer = 0.f;

		for (int i = 0; i < myData.PulseEmissionAmount; ++i)
		{
			for (int j = 0; j < COUNT; ++j)
			{
				if (myParticleData.IsActive[j] == false)
				{
					myParticleData.IsActive[j] = true;
					myParticleData.Position[j] = GenerateNewParticlePos();
					break;
				}
			}
		}
	}
	else if (myData.IsActive == false)
	{
		myData.IsActive = true;
		myData.CurrentLifetime = 0.f;
	}
}

template<unsigned int COUNT>
bool ParticleEmitter<COUNT>::IsActive()
{
	return myData.IsActive;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::UpdateParticle(unsigned int aIndex, CU::Time aTime)
{
	static unsigned int counter = 0;

	if (myData.myMagnetTarget != nullptr)
	{
		Vector2f targetPos = myData.myMagnetTarget->GetCenterPosition() - myParticleData.Position[aIndex];

		myParticleData.Velocity[aIndex] = myParticleData.Velocity[aIndex] + (targetPos * 0.18);
	}

	myParticleData.Position[aIndex].x += myParticleData.Velocity[aIndex].x * aTime.GetSeconds();
	myParticleData.Position[aIndex].y += myParticleData.Velocity[aIndex].y * aTime.GetSeconds();

	myParticleData.Lifetime[aIndex] += aTime.GetSeconds();

	if (myData.RotateSpritesOverTime == true)
	{
		float newRotation = myParticleData.Sprite[aIndex]->GetRotation();

		switch (myParticleData.RotateCCW[aIndex])
		{
			case false:
					newRotation += myParticleData.RotationSpeed[aIndex] * aTime.GetSeconds();
				break;

			case true:
					newRotation -= myParticleData.RotationSpeed[aIndex] * aTime.GetSeconds();
				break;
		}

		myParticleData.Sprite[aIndex]->SetRotation(newRotation);
	}

	++counter;

	float newAlpha = 1.f;

	if (myData.FadeIn == true && (myParticleData.Lifetime[aIndex] <= myParticleData.FadeInTime[aIndex]))
	{
		newAlpha = myParticleData.Lifetime[aIndex] / myParticleData.FadeInTime[aIndex];
	}
	else if (myData.FadeOut == true && (myParticleData.Lifetime[aIndex] >= myParticleData.LifetimeGoal[aIndex] - myParticleData.FadeInTime[aIndex]))
	{
		newAlpha = ((myParticleData.LifetimeGoal[aIndex] - myParticleData.Lifetime[aIndex]) / myParticleData.FadeOutTime[aIndex]);
	}

	if (newAlpha > 1.f)
	{
		newAlpha = 1.f;
	}
	else if (newAlpha < 0.f)
	{
		newAlpha = 0.f;
	}

	myParticleData.Color[aIndex].myA = newAlpha;
	myParticleData.Sprite[aIndex]->SetColor(myParticleData.Color[aIndex]);

	Renderer::ConvertPixelToScreen(myParticleData.Sprite[aIndex], myParticleData.Position[aIndex]);

	if (myParticleData.Lifetime[aIndex] >= myParticleData.LifetimeGoal[aIndex])
	{
		KillParticle(aIndex);
	}
	else if (myData.myMagnetTarget != nullptr)
	{
		Vector2f par = myParticleData.Position[aIndex];
		Vector2f tar = myData.myMagnetTarget->GetCenterPosition();

		if (myData.DieOnMagnetImpact == true &&
			(par.x > (tar.x - 40)) &&
			(par.x < (tar.x + 40)) &&
			(par.y > (tar.y - 40)) &&
			(par.y < (tar.y + 40)) &&
			myParticleData.Lifetime[aIndex] >= myData.KillTimeLimit)
		{
			KillParticle(aIndex);
		}
	}
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::KillParticle(unsigned int aIndex)
{
	myParticleData.IsActive[aIndex] = false;
	ResetParticle(aIndex);
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::LoadEmitterSettings(const std::string& aFileName)
{
	std::string fileName = aFileName;
	fileName.insert(0, "Data/ParticleEffects/");
	fileName.append(".json");

	picojson::object settingsObject = JW::GetPicoObject(JW::LoadPicoValue(fileName));
	picojson::object ParticleLifeObject = settingsObject.find("ParticleLife")->second.get<picojson::object>();
	picojson::object ParticleSpeedObject = settingsObject.find("ParticleSpeed")->second.get<picojson::object>();
	picojson::object RotationObject = settingsObject.find("Rotation")->second.get<picojson::object>();
	picojson::object ColorObject = settingsObject.find("Color")->second.get<picojson::object>();
	picojson::object ScaleObject = settingsObject.find("Scale")->second.get<picojson::object>();
	picojson::object FadeObject = settingsObject.find("Fade")->second.get<picojson::object>();
	picojson::object AreaObject = settingsObject.find("EmissionArea")->second.get<picojson::object>();

	std::string spritePath = "Sprites/Particles/sprParticle";
	spritePath.append(JW::GetString("Sprite", settingsObject));
	spritePath.append(".dds");

	myData.Dimensions.x = JW::GetFloat("Width", AreaObject);
	myData.Dimensions.y = JW::GetFloat("Height", AreaObject);

	myData.PulseRate = JW::GetFloat("PulseRate", settingsObject);
	myData.PulseEmission = JW::GetBool("PulseEmission", settingsObject);
	myData.PulseEmissionAmount = JW::GetInt("PulseEmissionAmount", settingsObject);

	myData.EmissionRate = JW::GetFloat("EmissionRate", settingsObject);
	myData.LifetimeGoal = JW::GetFloat("Lifetime", settingsObject);

	myData.MinParLifetime = JW::GetFloat("Min", ParticleLifeObject);
	myData.MaxParLifetime = JW::GetFloat("Max", ParticleLifeObject);

	myData.MinParEmissionVel = { JW::GetFloat("X-Min", ParticleSpeedObject), JW::GetFloat("Y-Min", ParticleSpeedObject) };
	myData.MaxParEmissionVel = { JW::GetFloat("X-Max", ParticleSpeedObject), JW::GetFloat("Y-Max", ParticleSpeedObject) };

	myData.RotateSpritesOverTime = JW::GetBool("RotateOverTime", RotationObject);
	myData.CanRotateCW = JW::GetBool("RotateCW", RotationObject);
	myData.CanRotateCCW = JW::GetBool("RotateCCW", RotationObject);
	myData.MinParRotationSpeed = JW::GetFloat("MinRotationSpeed", RotationObject);
	myData.MaxParRotationSpeed = JW::GetFloat("MaxRotationSpeed", RotationObject);

	myData.MinParRed = JW::GetFloat("MinRed", ColorObject);
	myData.MaxParRed = JW::GetFloat("MaxRed", ColorObject);
	myData.MinParGreen = JW::GetFloat("MinGreen", ColorObject);
	myData.MaxParGreen = JW::GetFloat("MaxGreen", ColorObject);
	myData.MinParBlue = JW::GetFloat("MinBlue", ColorObject);
	myData.MaxParBlue = JW::GetFloat("MaxBlue", ColorObject);

	myData.MinParSize = JW::GetFloat("Min", ScaleObject);
	myData.MaxParSize = JW::GetFloat("Max", ScaleObject);

	myData.FadeIn = JW::GetBool("FadeIn", settingsObject);
	myData.FadeOut = JW::GetBool("FadeOut", settingsObject);
	myData.MinParFadeinTime = JW::GetFloat("MinTimeIn", FadeObject);
	myData.MaxParFadeinTime = JW::GetFloat("MaxTimeIn", FadeObject);
	myData.MinParFadeoutTime = JW::GetFloat("MinTimeOut", FadeObject);
	myData.MaxParFadeoutTime = JW::GetFloat("MaxTimeOut", FadeObject);

	for (unsigned int i = 0; i < COUNT; ++i)
	{
		myParticleData.Sprite[i] = SpriteManager::GetInstance()->CreateSprite(spritePath, SpriteManager::RenderLayer::Foreground);
		ResetParticle(i);
		myParticleData.Sprite[i]->SetPivot({0.5f, 0.5f});
	}

	myData.IsActive = false;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::SetPosition(const Vector2f aPos)
{
	myData.Position = aPos;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::ResetEmitter()
{
	for (unsigned int i = 0; i < COUNT; ++i)
	{
		ResetParticle(i);
	}

	myData.IsActive = false;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::SetMagnetTarget(GameObject* aTarget)
{
	myData.myMagnetTarget = aTarget;
}

template<unsigned int COUNT>
Vector2f ParticleEmitter<COUNT>::GenerateNewParticlePos()
{
	Vector2f returnVec;

	returnVec.x = myData.Position.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.Dimensions.x)));
	returnVec.y = myData.Position.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (myData.Dimensions.y)));

	return returnVec;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::SetEmitterSize(Vector2f aSize)
{
	myData.Dimensions = aSize;
}

template<unsigned int COUNT>
void ParticleEmitter<COUNT>::SetDieOnMagnetImpact(bool aBool)
{
	myData.DieOnMagnetImpact = aBool;
}