#include "stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h"

Rocket::Rocket()
{
}


Rocket::~Rocket()
{
}

HRESULT Rocket::Init()
{
	// release 안해줘도 됨
	m_player = IMAGE->AddImage(
		"rocket", "images/rocket.bmp", WINSIZEX / 2, WINSIZEY - 200,
		52, 64, true, RGB(255, 0, 255));
	// 내가 초당 100만큼 이동한다는거라 얼마 안이동함
	m_speed = 100.0f * FRAME->GetElapsedTime(); 

	m_missile = new Missile;
	m_missile->Init(100, 500);

	return S_OK;
}

void Rocket::Release()
{
	// 이거 귀찮으면 소멸자에 release() 넣으면 됨
	//m_missile->Release();
	SAFE_DELETE(m_missile);
}

void Rocket::Update()
{
	// 이동
	// 왼쪽
	if (INPUT->GetKey(VK_LEFT) && 
		m_player->GetX() > 0) {
		m_player->SetX(m_player->GetX() - m_speed);
	}
	// 오른쪽
	if (INPUT->GetKey(VK_RIGHT) && 
		(m_player->GetX() + m_player->GetWidth()) < WINSIZEX) {
		m_player->SetX(m_player->GetX() + m_speed);
	}
	// 위
	if (INPUT->GetKey(VK_UP) && 
		m_player->GetY() > 0) {
		m_player->SetY(m_player->GetY() - m_speed);
	}
	// 아래
	if (INPUT->GetKey(VK_DOWN) && 
		(m_player->GetY() + m_player->GetHeight()) < WINSIZEY) {
		m_player->SetY(m_player->GetY() + m_speed);
	}

	if (INPUT->GetKeyDown(VK_SPACE)) {
		m_missile->Fire(
			m_player->GetX() + m_player->GetWidth() / 2,
			m_player->GetY() - m_player->GetHeight() / 2);
	}

	if (INPUT->GetKey('B')) {
		m_speed = 10.0f * FRAME->GetElapsedTime();
	}
	else {
		m_speed = 100.0f * FRAME->GetElapsedTime();
	}
	m_missile->Update();
}

void Rocket::Update(float timeDelta) {
	if (INPUT->GetKeyDown(VK_SPACE)) {
		m_missile->Fire(
			m_player->GetX() + m_player->GetWidth() / 2,
			m_player->GetY() - m_player->GetHeight() / 2);
	}

	m_missile->Update(timeDelta);
}

void Rocket::Render()
{
	m_missile->Render();
	m_player->Render(GetMemDC(), m_player->GetX(), m_player->GetY());
}

void Rocket::RemoveMissile(int arrNum)
{
}

void Rocket::Collision()
{
	for (int i = 0; i < m_missile->GetVBullet().size(); i++) {
		for (int j = 0; j < m_em->GetVMinion().size(); j++) {
			RECT temp;
			if (IntersectRect(&temp,
				&m_missile->GetVBullet()[i].rc,
				&m_em->GetVMinion()[j]->GetRect())) {
				m_missile->GetVBullet()[i].fire = false;
				//m_em->GetVMinion()[j]->
				break;
			}
		}
	}
}

void Rocket::HitDamage(float damage)
{
}
