#include "stdafx.h"
#include "Particle.h"

#include "Common\Transform.h"

Particle::Particle()
{
	transform = new Transform;
}


Particle::~Particle()
{
	SAFE_DELETE(transform);
}

void Particle::Start(float liveTime, const Vector2 * pos, const Vector2 * velo,
	const Vector2 * accel, float rotate, float rotateAccel, float scale)
{
	this->bLive = true;

	this->fTotalLiveTime = liveTime;
	this->fDeltaLiveTime = 0.0f;

	this->transform->SetWorldPosition(*pos);

	this->velocity = *velo;
	this->accelation = *accel;
	this->rotate = rotate;
	this->rotateAccel = rotateAccel;
	this->fScale = scale;
}

void Particle::Update()
{
	if (bLive == false) return;

	if (fDeltaLiveTime > fTotalLiveTime)
		bLive = false;

	float deltaTime = (float)Frame::Get()->GetFrameDeltaSec();

	fDeltaLiveTime += deltaTime;

	fNormalizeLiveTime = fDeltaLiveTime / fTotalLiveTime;

	if (fNormalizeLiveTime > 1.0f)
		fNormalizeLiveTime = 1.0f;

	// 이동 및 회전
	transform->MovePositionWorld(velocity * deltaTime);
	transform->RotateSelf(rotate * deltaTime);

	this->velocity = velocity + accelation * deltaTime;
	this->rotate = rotate + rotateAccel * deltaTime;
}

// 컬러값 크기값은 여기서 변경
void Particle::GetParticleVertex(Particle_Vertex * pOut, DWORD * pIndex, const VEC_COLOR & colors, const VEC_SCALE & scales, DWORD particleNum)
{
	// 현재의 파티클 위치값
	Vector2 center = transform->GetWorldPosition();
	DWORD dwColor = 0;
	float scale;

	// 스케일 보간
	float s = 0.0f;
	int lastIndex = scales.size() - 1;

	// 마지막번째 녀석임
	if (fNormalizeLiveTime == 1.0f) {
		dwColor = colors[colors.size() - 1];
		scale = fScale * scales[scales.size() - 1];
	}
	else if (fNormalizeLiveTime == 0.0f) {
		dwColor = colors[0];
		scale = fScale * scales[0];
	}
	else {
		// 이거 맞는지 잘 확인하자 lastIndex가 아니라 사이즈 일지도 모름
		float interval = 1.0f / lastIndex;

		// liveTime에서 어느 위치에 있는지
		float position = fNormalizeLiveTime / interval;

		int startIndex = (int)position;
		int endIndex = startIndex + 1;
		// 보간값 (0 ~ 1 사이값)
		float fN = position - startIndex;

		// 컬러는 보정하는 함수 존재 스케일은 없어서 계산해야함
		s = (scales[endIndex] - scales[startIndex]) * fN + scales[startIndex];

		scale = fScale * s;

		// 컬러 보간
		lastIndex = colors.size() - 1;

		interval = 1.0f / lastIndex;

		position = fNormalizeLiveTime / interval;
		
		startIndex = (int)position;
		endIndex = startIndex + 1;
		fN = position - startIndex;

		D3DXCOLOR color;
		D3DXColorLerp(&color, &colors[startIndex], &colors[lastIndex], fN);

		dwColor = (DWORD)color;
	}

	// vertex info
	float halfSize = scale * 0.5f;
	Vector2 x = transform->GetRight();
	Vector2 y = transform->GetUp();

	(pOut + 0)->position = center + (x * -halfSize) + (y * -halfSize); // 왼상
	(pOut + 1)->position = center + (x *  halfSize) + (y * -halfSize); // 오른상
	(pOut + 2)->position = center + (x * -halfSize) + (y *  halfSize); // 왼하
	(pOut + 3)->position = center + (x *  halfSize) + (y *  halfSize); // 오른하

	(pOut + 0)->uv = Vector2(0, 0);
	(pOut + 1)->uv = Vector2(1, 0);
	(pOut + 2)->uv = Vector2(0, 1);
	(pOut + 3)->uv = Vector2(1, 1);

	(pOut + 0)->color = dwColor;
	(pOut + 1)->color = dwColor;
	(pOut + 2)->color = dwColor;
	(pOut + 3)->color = dwColor;

	*(pIndex + 0) = (particleNum * 4) + 0;
	*(pIndex + 1) = (particleNum * 4) + 1;
	*(pIndex + 2) = (particleNum * 4) + 2;
	*(pIndex + 3) = (particleNum * 4) + 2;
	*(pIndex + 4) = (particleNum * 4) + 1;
	*(pIndex + 5) = (particleNum * 4) + 3;
}
