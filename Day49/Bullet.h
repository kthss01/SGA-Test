#pragma once

#include "GameNode.h"

// 스킬이나 폭탄 쏴서 이미지 다 날라가는거
// 총알들 다 false로 하는거

// 총알을 담당해주는 클래스
// 총알을 발사해주면 특정 위치에서 날라가고 충돌하는 녀석

// 총알이 가지고 있는 속성 설정
// 총알 구조체
// 구조체에 이미지 넣어두기 (초기화 하는거) 보다는 
// 클래스에 넣어서 하나만 (초기화해서) 그리면 되기는 함
// 2D에서는 속도 차이가 별로 안나서 그냥 이렇게 하는거 
// 3D에서는 오래걸리니 하나만 두거나 memcpy 이용하는게 좋음
struct tagBullet {
	Image* bulletImage;
	RECT rc;
	float x, y;				// 움직이는 위치
	float fireX, fireY;		// 발사 될때 위치
	float radius;
	float speed;
	float angle;
	bool fire;
};

// 공용 총알 (각도를 가지고 움직이는 녀석)
class Bullet
{
private:

public:
	Bullet();
	~Bullet();
};

class Missile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	// 일정 사거리 넘어가면 총알 리셋되는거
public:
	Missile();
	~Missile();

	HRESULT Init(int bulletMax, float range);
	void Release() override;
	void Update() override;
	void Render() override;

	void Fire(float x, float  y);
	void Move();
	void Bomb();
};

// 생성자 소멸자 안쓰면 자동으로 만들어짐
// 복사 생성자라는 것도 있음
// 생성을 하면서 값을 넣어주는 거 
// 자동으로 생성되는거
// 기본생성자
// 복사생성자
// 복사하고 반환하는 생성자
// 소멸 생성자