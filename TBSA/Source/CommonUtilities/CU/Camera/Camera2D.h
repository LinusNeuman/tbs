#pragma once
#include <stdlib.h>
#include <crtdbg.h>



#include "../Vectors/Vector.h"
#include "../Matriser/matrix.h"
#include "../Utility/Randomizer/Randomizer.h"
#include "../NameSpaceAliases.h"

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void Init(const CU::Vector2<float>* aResolutionPtr, const CU::Vector2<float>& aPosition);

	const CU::Matrix33<float> GetInverse() const;
	const CU::Matrix33<float>& GetProjection() const;
	const CU::Vector2<float> GetPosition() const;
	const CU::Vector2<float> GetScreenOffset() const;
	const CU::Vector2<float>& GetScreenResolution() const;
	const float GetResolutionScale() const;

	void Rotate(const float anAngle);
	void Move(CU::Vector3<float> aVector);
	void Zoom(float aFraction);
	void SetPos(const CU::Vector2<float> aPos);
	void SetTargetPos(const CU::Vector2<float> aPos);
	void Update(float aDelta);
	bool IsShaking();
	void Shake(const float aDuration, const float aForce);
	void StopShaking();
private:
	void SetProjection();

	Randomizer myRandomizer;

	CU::Matrix33<float> myOrientation;
	CU::Matrix33<float> myProjection;
	const CU::Vector2<float> *myResolutionPtr;
	CU::Vector2<float> myTargetPos;
	float myResolutionScale;
	float myShakeDuration;
	float myShakeForce;
	bool myShaking;


};

inline const CU::Vector2<float> Camera2D::GetPosition() const
{
	return myOrientation.GetPosition();
}

inline void Camera2D::SetPos(const CU::Vector2<float> aPos)
{
	myTargetPos = aPos;
	myOrientation.SetPosition(aPos);
}

inline void Camera2D::SetTargetPos(const CU::Vector2<float> aPos)
{
	myTargetPos = aPos;
}

inline const CU::Vector2<float>& Camera2D::GetScreenResolution() const
{
	return *myResolutionPtr;
}

inline const float Camera2D::GetResolutionScale() const
{
	return myResolutionScale;
}

inline void Camera2D::Rotate(const float anAngle)
{
	myOrientation.Rotate2D(anAngle);
}

inline const CU::Matrix33<float>& Camera2D::GetProjection() const
{
	return myProjection;
}

inline bool Camera2D::IsShaking()
{
	return myShaking;
}