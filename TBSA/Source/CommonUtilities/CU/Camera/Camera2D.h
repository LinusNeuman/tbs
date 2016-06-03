#pragma once
#include <stdlib.h>
#include <crtdbg.h>



#include "CU/Vectors/Vector.h"
#include "CU/Matriser/matrix.h"
#include "CU/Utility/Randomizer/Randomizer.h"
#include "CU/NameSpaceAliases.h"
#include <CU/Utility/GameSpecificTypeDefs.h>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void Init(const CU::Vector2f & aResolution, const CU::Vector2<float>& aPosition);

	const CU::Matrix33f GetInverse() const;
	const CU::Matrix33f& GetProjection() const;
	const CU::Vector2f GetPosition() const;
	const CU::Vector2f GetScreenOffset() const;
	const CU::Vector2f& GetScreenResolution() const;
	const float GetResolutionScale() const;

	void Rotate(const float anAngle);

	void Zoom(float aFraction);
	void SetPos(const CU::Vector2f aPos);

	void MoveCamera(const CU::Vector2f & aPosition);
	void MoveCameraIsomertic(const CU::Vector2f & aPosition);

	void SetTargetPos(const CU::Vector2f aPos);
	void Update(float aDelta);
	bool IsShaking();
	void Shake(const float aDuration, const float aForce);
	void StopShaking();
private:
	void SetProjection();

	Randomizer myRandomizer;

	TilePositionf myMaxConstrains;
	CU::Matrix33f myOrientation;
	CU::Matrix33f myProjection;
	CU::Vector2f myResolution;
	CU::Vector2f myTargetPos;
	float myResolutionScale;
	float myShakeDuration;
	float myShakeForce;
	bool myShaking;
};

inline const CU::Vector2f Camera2D::GetPosition() const
{
	return myOrientation.GetPosition();
}

inline void Camera2D::SetPos(const CU::Vector2f aPos)
{
	myTargetPos = aPos;
	myOrientation.SetPosition(aPos);
}

inline void Camera2D::SetTargetPos(const CU::Vector2f aPos)
{
	myTargetPos = aPos;
}

inline const CU::Vector2f& Camera2D::GetScreenResolution() const
{
	return myResolution;
}

inline const float Camera2D::GetResolutionScale() const
{
	return myResolutionScale;
}

inline void Camera2D::Rotate(const float anAngle)
{
	myOrientation.Rotate2D(anAngle);
}

inline const CU::Matrix33f& Camera2D::GetProjection() const
{
	return myProjection;
}

inline bool Camera2D::IsShaking()
{
	return myShaking;
}