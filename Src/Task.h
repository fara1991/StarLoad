#pragma once
#include "DxLib.h"
#include <algorithm>
#include <assert.h>

const static int Success = 0;							//�������萔
const static int Invalid = -1;						//���s���萔
const static int WindowMinX = 0;						//�E�B���h�E���[X���W
const static int WindowMaxX = 640;					//�E�B���h�E�E�[X���W
const static int WindowCenX = WindowMaxX / 2;	//�E�B���h�E����X���W
const static int WindowMinY = 0;						//�E�B���h�E��[Y���W
const static int WindowMaxY = 480;					//�E�B���h�E���[Y���W
const static int WindowCenY = WindowMaxY / 2;	//�E�B���h�E����Y���W

//���N���X
class Task
{
public:
	virtual ~Task(){};

	//=0�ƂȂ��Ă�����̂͌p����Ŏ������Ȃ���΂����Ȃ�
	//{}�ƂȂ��Ă�����̂͌p����Ŏ������Ȃ��Ă��悢
	virtual void Initialize(){}
	virtual void Update() = 0;
	virtual void DrawLoop() = 0;
	virtual void Finalize(){}

	/// <summary>
	/// �t���O���]���������܂��B
	/// </summary>
	/// <param name="bFlag">���݂̃t���O</param>
	void ReverseFlag(int& bFlag){ bFlag = !bFlag; }
};

/// <summary>
/// �|�C���^���f���[�g��Ƀk���|�C���^�ɂ��܂��B
/// </summary>
template <class T>
inline void DeletePtr(T*& ptr) {
	delete ptr;
	ptr = nullptr;
}