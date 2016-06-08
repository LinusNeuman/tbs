#include "stdafx.h"
#include "Camera2D.h"
#include "CU/Macros/Macros.h"

Camera2D::Camera2D()
{
	myShaking = false;
	myShakeDuration = 0;
	myShakeForce = 1.f;

	myMaxConstrains = TilePositionf(45.f, 45.f);
}

Camera2D::~Camera2D()
{
}

void Camera2D::StopShaking()
{
	myShaking = false;
	myShakeDuration = 0;
}

void Camera2D::Init(const CU::Vector2f & aResolution, const CU::Vector2<float>& aPosition)
{
	myResolution = aResolution;
	myProjection.myMatrix[0] = 2.f / aResolution.x;
	myProjection.myMatrix[4] = 2.f / aResolution.y;
	myOrientation.myMatrix[6] = aPosition.x;
	myOrientation.myMatrix[7] = aPosition.y;
	myResolutionScale = aResolution.y / 720.f;
	myTargetPos = aPosition;

	myRandomizer.SetMinMax(-0.1f, 0.1f);
}

void Camera2D::Update(float aDelta)
{
	CU::Vector2<float> pos = myOrientation.GetPosition();
	pos += (myTargetPos - pos) * aDelta * 5.f;

	if (myShaking == true)
	{
		myShakeDuration -= aDelta;
		if (myShakeDuration < 0)
		{
			myShaking = false;
		}

		pos.x += myRandomizer.GetRandomValue(-myShakeForce, myShakeForce);
		pos.y += myRandomizer.GetRandomValue(-myShakeForce, myShakeForce);
	}

	myOrientation.SetPosition(pos);
}

void Camera2D::Shake(const float aDuration, const float aForce)
{
	myShakeDuration = aDuration;
	myShakeForce = aForce;
	myShaking = true;
}

const CU::Matrix33<float> Camera2D::GetInverse() const
{
	
	CU::Vector3<float> translation(-myOrientation.myMatrix[6], -myOrientation.myMatrix[7], 1);
	CU::Matrix33<float> inverse(myOrientation);
	inverse.myMatrix[6] = 0;
	inverse.myMatrix[7] = 0;
	inverse = inverse.Transpose();
	translation *= inverse;
	inverse.myMatrix[6] = translation.x;
	inverse.myMatrix[7] = translation.y;
	return inverse;
}

const CU::Vector2f Camera2D::GetScreenOffset() const
{
	return (GetPosition() - (myResolution / 2.f)) * myResolutionScale;
}

void Camera2D::Zoom(float aFraction)
{
	myProjection.myMatrix[0] *= aFraction;
	myProjection.myMatrix[4] *= aFraction;
}

void Camera2D::MoveCamera(const CU::Vector2f & aPosition)
{
	TilePositionf tempPosition = myOrientation.GetPosition() + aPosition;

	if (tempPosition.x > 0.f && tempPosition.y > 0.f
		&& tempPosition.x < myMaxConstrains.x && tempPosition.y < myMaxConstrains.y)
	{
		myOrientation.SetPosition(myOrientation.GetPosition() + aPosition);
	}
}

void Camera2D::MoveCameraIsomertic(const CU::Vector2f & aPosition)
{
	MoveCamera(aPosition * CU::Matrix33f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(-45.f)));
}

void Camera2D::SetProjection()
{
	myProjection.myMatrix[0] = 2.f / myResolution.x;
	myProjection.myMatrix[4] = 2.f / myResolution.y;
}