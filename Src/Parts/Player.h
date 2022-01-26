#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Player : public Task
{
public:
	Player(int nX, int nY, const int& nHandle, const int& nWhiteHandle, const int& nIndex, Animation*& pAnime, const int& nAnimeIndex);
	~Player();

	void Update() override;
	void DrawLoop() override;

	/// <summary>
	/// ���SX���W���擾���܂��B
	/// </summary>
	/// <returns>���SX���W</returns>
	int GetPlayerPositionX() const { return m_pStatusSet->m_nPlayerX; }

	/// <summary>
	/// ���SY���W���擾���܂��B
	/// </summary>
	/// <returns>���SY���W</returns>
	int GetPlayerPositionY() const { return m_pStatusSet->m_nPlayerY; }

	/// <summary>
	/// �Փˍςݏ���ݒ肵�܂��B
	/// </summary>
	void SetCollision() { m_pStatusSet->m_bCollision = TRUE; }

	/// <summary>
	/// �Փˏ����擾���܂��B
	/// </summary>
	/// <returns>�Փ˂������ǂ���</returns>
	int GetCollision() const { return m_pStatusSet->m_bCollision; }

	/// <summary>
	/// �Փˏ��𔽓]���܂��B
	/// </summary>
	void ReverseCollision(){ ReverseFlag(m_pStatusSet->m_bCollision); }

	/// <summary>
	/// ���쒆�̐���_�ł����܂��B
	/// </summary>
	/// <param name="nIndex">���쒆�̗v�f�ԍ�</param>
	void SetFlash(const int& nIndex){ 
		if(m_pStatusSet->m_bCollision) return;
		if(nIndex == m_pStatusSet->m_nIndex) m_pStatusSet->m_bFlash = TRUE;
		else m_pStatusSet->m_bFlash = FALSE;
	}

	/// <summary>
	/// �_�ŏ����擾���܂��B
	/// </summary>
	/// <returns>�_�ł��Ă��邩�ǂ���</returns>
	int IsFlash() const { return m_pStatusSet->m_bFlash; }
private:
	struct StructStatus{
		int m_nPlayerX;					//�v���C���[X���W
		int m_nPlayerY;					//�v���C���[Y���W
		int m_nAlphaCount = 0;			//�v���C���[���ߓx�J�E���^
		int m_nFlashCount = 0;			//�v���C���[�_�ŃJ�E���^
		int m_nFlashCycleCount = 8;	//1�t���b�V���ɕK�v�ȃJ�E���g
		int m_bCollision =  FALSE;		//�v���C���[�o�[�̂����蔻��
		int m_nFlashHandle;				//�v���C���[�摜
		int m_nStopHandle;				//�v���C���[�摜2
		int m_nIndex;						//�v���C���[�ԍ�
		int m_bFlash = FALSE;			//�v���C���[�o�[�_��
		int m_nAnimeIndex;				//�A�j���[�V�����v�f�ԍ�
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

