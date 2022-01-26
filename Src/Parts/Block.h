#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Block : public Task
{
public:
	Block(int nX, int nY, int nSpeed, int nPos, int nHandle, Animation*& pAnime, const int& nIndex);
	~Block();

	void Update() override;
	void DrawLoop() override;
	
	/// <summary>
	/// ���SX���W���擾���܂��B
	/// </summary>
	/// <returns>���SX���W</returns>
	int GetBlockPositionX() const { return m_pStatusSet->m_nBlockX; }

	/// <summary>
	/// ���SY���W���擾���܂��B
	/// </summary>
	/// <returns>���SY���W</returns>
	int GetBlockPositionY() const { return m_pStatusSet->m_nBlockY; }

	/// <summary>
	/// �摜�n���h����ݒ肵�܂��B
	/// </summary>
	/// <param name="nHandle">�摜�n���h��</param>
	void SetBlockHandle(const int& nHandle) { m_pStatusSet->m_nHandle = nHandle; }

	/// <summary>
	/// �摜�n���h�����擾���܂��B
	/// </summary>
	/// <returns>�摜���n���h��</returns>
	int GetBlockHandle() const { return m_pStatusSet->m_nHandle; }

	/// <summary>
	/// �v���C���[�Ƃ̏ՓˍϏ�Ԃɂ��܂��B
	/// </summary>
	void SetCollision() { m_pStatusSet->m_bCollision = TRUE; }

	/// <summary>
	/// �v���C���[�Ƃ̏Փˏ�Ԃ��擾���܂��B
	/// </summary>
	/// <returns>�Փˍς݂��ǂ���</returns>
	int GetCollision() const { return m_pStatusSet->m_bCollision; }

	/// <summary>
	/// �v�f�ԍ����擾���܂��B
	/// </summary>
	/// <returns>�v�f�ԍ�(0�`6)</returns>
	int GetBlockIndex() const { return m_pStatusSet->m_nPos; }
private:
	struct StructStatus{
		int m_nBlockX;			//�u���b�NX���W
		int m_nBlockY;			//�u���b�NY���W
		int m_nPos;				//�u���b�N�v�f�ԍ�
		int m_nSpeed;			//�u���b�N����
		int m_nAlphaCount;	//�u���b�N���ߓx�J�E���^
		int m_bCollision;		//�u���b�N�����蔻��
		int m_nHandle;			//�u���b�N�摜
		int m_nIndex;			//�u���b�N�A�j���[�V��������v�f
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

