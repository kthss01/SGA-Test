#pragma once

struct Particle_Vertex {
	Vector2 position;
	DWORD color;
	Vector2 uv;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
};

typedef vector<D3DXCOLOR> VEC_COLOR;
typedef vector<float> VEC_SCALE;

// 입자 하나
class Particle
{
public:
	class Transform* transform;
private:
	bool bLive; // 활성화 여부
	float fTotalLiveTime; // 최종 시간
	float fDeltaLiveTime; // 몇초까지 진행되었는지
	// 색깔값이나 크기값 변경할 때 사용할꺼
	float fNormalizeLiveTime; // 활성화 비율 시간 (0 ~ 1) 1이면 사라지게

	Vector2 velocity; // 방향 및 속도값
	Vector2 accelation; // 가속도
	float rotate; // 처음 축 + 회전값 degree 값으로 들어갈꺼
	float rotateAccel; // 회전 가속도

	float fScale; // 기본 스케일 값
public:
	Particle();
	~Particle();

	// 입자 하나를 생성
	void Start(
		float liveTime, // 얼마만큼 화면에 띄울 것인지
		const Vector2* pos, // 시작 위치, 항상 시작 위치가 이미터가 아닐 수도 있음
		const Vector2* velo, // 시작 속도
		const Vector2* accel, // 가속도
		float rotate, // 시작할때 회전값
		float rotateAccel, // 회전 증감값
		float scale // 기본 스케일 값
	);

	void Update();

	// 렌더는 이미터에서 해줄꺼
	// 버퍼 사용하지 않고 렌더할꺼
	void GetParticleVertex(
		Particle_Vertex* pOut, // vertex buffer 배열
		DWORD* pIndex, // index buffer 배열
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		DWORD particleNum // 현재 파티클이 몇개 발생되었는지 
		);

	bool IsLive() { return bLive; }
};

