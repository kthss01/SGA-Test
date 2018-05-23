#pragma once

// MainGame대신 돌아갈꺼

class Program
{
private:
	// 기본적으로 도형 만들려면 vertex 필요
	struct Vertex {
		Vector2 position;
		DWORD color;
	};

	Vertex* vertices;
	Matrix matView;
	Matrix matProjection;
	// viewPort 필요없음 
	// 윈도우 쓰겠다고 선언된 순간부터 window 기준으로 되어있음
	Vector2 vEye;
	Vector2 outPos;

	Ray ray;

	float color[4];

	class Rect* head;
	class Rect* body;
	class Rect* lArm;
	class Rect* rArm;
	class Rect* lLeg;
	class Rect* rLeg;

	// 텍스에 대한 정보를 저장할 곳
	LPDIRECT3DTEXTURE9 pRenderTexture;
	// 텍스에 대한 표면 (색상값 설정)
	LPDIRECT3DSURFACE9 pRenderSurface;

	vector< pair<LPDIRECT3DTEXTURE9, D3DXIMAGE_INFO> > vecImage;

	class Camera* mainCamera;
public:
	Program();
	~Program();

	void Update();
	void Render();

	void CreateRenderTargetTexture();
};

/*
	과제1 애니메이션
	1. 캐릭터 만들어 두고 마우스 클릭시 부위만 움직이게
	2. ctrl + s시 모든 정보를 vector< vector<transform> > (2번째 벡터)
		현재 trasform 정보 모두를 vector에 다 넣고 
		그 vector를 2번째 vector에 넣어두는거
		이거를 하고싶은만큼 해두고 (5개 정도 이상)
	3. 이 vector 순으로 움직이게 (일정 시간에 따라) 
		보간 활용해서
	4. 애니메이션 만들면 콜라이더 추가해서 상호작용 원 충돌하게
	
	과제2 지렁이 게임 추가
	5. 지렁이 게임 만들었는데 아이템 먹으면 지렁이 늘어나게끔

	과제3
	5.5 IsOverlap 채우기 (RectCollider로 하는)
	6. 콜라이더 이용해서 중력값 받앗을때 바닥 처리
	  일정 거리 넘어가면 화면 밖으로 안나가게 (왼쪽)
	  오른쪽은 점프 맵 만들어서 점프할 수 있게
	  점프맵 생긴 때 부터는 바닥 사라지게
	  
	  * 바닥은 AABBMinMax이용해서 사각형 충돌 해주면 됨

	7. 조사숙제 xml 사용법 및 데이터를 올려주신거 어떻게 사용할지 고민하기
		(5.18(금) 새벽쯤이나 다음날 아침 쯤에 카페에 올려주실꺼)
*/