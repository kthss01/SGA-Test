#pragma once

#include "GameObject/GameObject.h"

// 방사 타입, 어떤 도형으로 만들 것인지
enum PARTICLE_EMISSION_TYPE {
	PZERO,	// 정점
	CIRCLE, // 구 내부의 랜덤하게
	CIRCLE_OUTLINE, // 원 외부에서만 (원 라인만)
	RECT,
};

class Particle : public GameObject
{
private:
	struct Particle_Vertex {
		Vector2 position;
		Vector2 uv;
		DWORD color;

		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE };
	};
	typedef vector<D3DXCOLOR> VEC_COLOR;
	typedef vector<float> VEC_SCALE;

private:
	DWORD particleNum; // 파티클의 총 입자 수
	Particle_Vertex* particleVertex; // 파티클 정점 정보

	float emissionPerSec; // 초당 입자 몇개를 발사한 건지

	DWORD particleCount; // 총 몇개가 화면에 렌더가 되는지

	// 변할 색깔 및 크기 값 일정 시간에 따라 해당 값으로 변하게 끔 하기 위해서
	VEC_COLOR color;
	VEC_SCALE scale;
public:
	Particle();
	~Particle();

	void Init(
		DWORD particleNum,
		float emission,
		float liveTimeMin,	// 화면에 보여주는 시간
		float liveTimeMax,
		const Vector2& velocityMin,
		const Vector2& velocityMax,
		const Vector2& accelMin, // 가속도
		const Vector2& accelMan, // 가속도
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		float scaleMin,	// 맨 처음 생성되는 입자의 크기
		float scaleMax,
		LPDIRECT3DTEXTURE9 pParticleTexture,
		bool bLocal = false // 독립해서 움직일 것이냐 (완전하게 랜덤하게 
		// 처음 녀석에 영향을 받아서 움직일 것이냐
	);
};

