#pragma once
// Ư�� �ִϸ��̼� �ൿ�� ���������� �����ؼ� animation clip�̶�� ��

// AnimationClip���� �� ������
struct AnimationData {
	float frameRate;	// ���� �ʴ� ��� �ִϸ��̼��� ������ ������
	Vector2 frame;
	Vector2 MaxFrame;

	wstring textureName;
	AnimationData* pNextFrame;
};

// ���� �ϳ� ������ ���� �̷��� �� �ִ°�
class AnimationClip
{
private:
	std::map<wstring, AnimationData*> aniClip;
public:
	AnimationClip();
	~AnimationClip();

	void PushAnimationData(wstring keyName, 
		AnimationData* data);
	AnimationData* GetCurrentData(wstring keyName);
};

