#pragma once

// SingletonBase.h

// �̱��� ���� - ������ ���� �� �ϳ�
// ���� ���� : ��ü�� �ϳ��� ����� ������ �־ ( new�� �ѹ��� �Ѵ� )
// �����ؼ� ����� �� singleton �ٿ��� ����ϴ� ��찡 ���� �̹��� ������

// ���ø� �̿��ؼ� ����� ���ø� �̱���
// �׳� ����� ���̳��� �̱��� �̷��� �Ǵµ� �ϴ� ������ �Ȱ��� -> ��ü �ϳ� ����

template <typename T>
class SingletonBase
{
protected:
	// �̱��� �ν��Ͻ�
	static T* instance;
	SingletonBase() {};
	~SingletonBase() {};

public:
	// �̱��� ��ü ��������
	static T* GetSingleton();
	void ReleaseSingleton();
};

// �̱��� �ν��Ͻ� ����
template<typename T>
T* SingletonBase<T>::instance = NULL;

template<typename T>
T * SingletonBase<T>::GetSingleton()
{
	// �̱��� ��ü�� ������ ���� ����
	if (!instance) instance = new T;
	// �����ϸ� ��ȯ
	return instance;
}

// �̱��� �޸� ������ ������ ����ɶ� �ϰ� �ǹǷ� �ʹ� ������ ������
template<typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance) {
		delete instance;
		instance = 0;
	}
}

// �Ϲ��� ���̳��� �̱�����
// ������ �Ҹ��� private protected �� ��� �ϰԵ� 
// �ܺο��� ����(new �Ҵ�) ���ϰ� �ϰ�