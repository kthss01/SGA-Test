#pragma once

#include "GameObject/GameObject.h"

// ��� Ÿ��, � �������� ���� ������
enum PARTICLE_EMISSION_TYPE {
	PZERO,	// ����
	CIRCLE, // �� ������ �����ϰ�
	CIRCLE_OUTLINE, // �� �ܺο����� (�� ���θ�)
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
	DWORD particleNum; // ��ƼŬ�� �� ���� ��
	Particle_Vertex* particleVertex; // ��ƼŬ ���� ����

	float emissionPerSec; // �ʴ� ���� ��� �߻��� ����

	DWORD particleCount; // �� ��� ȭ�鿡 ������ �Ǵ���

	// ���� ���� �� ũ�� �� ���� �ð��� ���� �ش� ������ ���ϰ� �� �ϱ� ���ؼ�
	VEC_COLOR color;
	VEC_SCALE scale;
public:
	Particle();
	~Particle();

	void Init(
		DWORD particleNum,
		float emission,
		float liveTimeMin,	// ȭ�鿡 �����ִ� �ð�
		float liveTimeMax,
		const Vector2& velocityMin,
		const Vector2& velocityMax,
		const Vector2& accelMin, // ���ӵ�
		const Vector2& accelMan, // ���ӵ�
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		float scaleMin,	// �� ó�� �����Ǵ� ������ ũ��
		float scaleMax,
		LPDIRECT3DTEXTURE9 pParticleTexture,
		bool bLocal = false // �����ؼ� ������ ���̳� (�����ϰ� �����ϰ� 
		// ó�� �༮�� ������ �޾Ƽ� ������ ���̳�
	);
};

