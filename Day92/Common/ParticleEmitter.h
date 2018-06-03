#pragma once

#include "GameObject/GameObject.h"
#include "Particle.h"

class ParticleEmitter : public GameObject
{
private: 
	DWORD particleNum; // 파티클에 대한 총 입자량
	Particle* particles; // 파티클 정보 입력으로로 쓸꺼고 이 정보를 particleVertex에 넣을꺼

	Particle_Vertex* particleVertex;
	DWORD* particleIndex;

	float fEmissionPerSec; // 1초에 몇개 생성할껀지
	DWORD dwParticleCount; // 활성화 순서

	VEC_COLOR colors;
	VEC_SCALE scales;

	float fStartLiveTimeMin;
	float fStartLiveTimeMax;

	Vector2 startVelocityMin;
	Vector2 startVelocityMax;

	Vector2 startAccelateMin;
	Vector2 startAccelateMax;

	float startSetRotateMin;
	float startSetRotateMax;

	float startRotateMin;
	float startRotateMax;

	float startRotateAccelateMin;
	float startRotateAccelateMax;

	float fStartScaleMin;
	float fStartScaleMax;

	bool bEmission; // 현재 생성중
	float fEmissionIntervalTime; // 생성 간격
	float fEmissionDeltaTime; // 지나간 시간

	LPDIRECT3DTEXTURE9 pTex;

	bool bLocal;
public:
	ParticleEmitter();
	~ParticleEmitter();

	void Init(
		DWORD particleNum, float emission, 
		float liveTimeMin, float liveTimeMax,
		const Vector2& velocityMin, const Vector2& velocityMax, 
		const Vector2& accelMin, const Vector2& accelMax,
		float startRotateMin, float startRotateMax,
		float rotateMin, float rotateMax,
		float rotateAccelMin, float rotateAccelMax,
		const VEC_COLOR& colors, const VEC_SCALE& scales,
		float scaleMin, float scaleMax,
		LPDIRECT3DTEXTURE9 pTex, bool bLocal = false
		);

	void Update();
	void Render();

	void StartEmission();
	void StopEmission();

	void SetRenderLocal(bool bLocal) { this->bLocal = bLocal; }

private:
	void StartOneParticle(); // 파티클 입자 하나 생성
};

