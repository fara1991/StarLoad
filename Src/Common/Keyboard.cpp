#include "Keyboard.h"

/// <summary>
/// �X�V����
/// </summary>
void Keyboard::Update(){
	GetHitKeyStateAll(m_asKey);
	for(int i = 0; i < m_nKeyType; i++){
		if(m_asKey[i] == 0){
			m_anPushKeyCount[i] = 0;
			m_anPullKeyCount[i]++;
		}
		else{
			m_anPushKeyCount[i]++;
			m_anPullKeyCount[i] = 0;
		}

		//�J�E���^��int�^�ŏ����ł���͈͂ɂ���
		if(m_anPushKeyCount[i] < 0) m_anPullKeyCount[i] = 0;
		else if(m_anPullKeyCount[i] < 0) m_anPullKeyCount[i] = 0;
		else if(m_anPushKeyCount[i] >= INT_MAX - 1) m_anPushKeyCount[i] = 1;
		else if(m_anPullKeyCount[i] >= INT_MAX - 1) m_anPullKeyCount[i] = 1;
	}
}

/// <summary>
/// �w��L�[�����������`�F�b�N���܂��B�������u�Ԃ̂�TRUE��Ԃ��܂��B
/// </summary>
/// <param name="nKey">�������L�[�̎��</param>
/// <returns>���������ǂ���</returns>
int Keyboard::IsKeyPush(int nKey){
	if(nKey < 0 || nKey >= m_nKeyType) return FALSE;
	int bPush = FALSE;
	if(m_asKey[nKey] > 0 && m_anPushKeyCount[nKey] == 1) bPush = TRUE;
	return bPush;
}

/// <summary>
/// �w��L�[�������Ă��邩�`�F�b�N���܂��B�����Ă����TRUE��Ԃ��܂��B
/// </summary>
/// <param name="nKey">�����Ă���L�[�̎��</param>
/// <returns>�����Ă��邩�ǂ���</returns>
int Keyboard::IsKeyPushHold(int nKey){
	if(nKey < 0 || nKey >= m_nKeyType) return FALSE;
	int bPush = FALSE;
	if(m_asKey[nKey] > 0 && m_anPushKeyCount[nKey] >= 1) bPush = TRUE;
	return bPush;
}

/// <summary>
/// �w��L�[�𗣂������`�F�b�N���܂��B�������u��TRUE��Ԃ��܂��B
/// </summary>
/// <param name="nKey">�������L�[�̎��</param>
/// <returns>���������ǂ���</returns>
int Keyboard::IsKeyPull(int nKey){
	if(nKey < 0 || nKey >= m_nKeyType) return FALSE;
	int bPull = FALSE;
	if(m_asKey[nKey] == 0 && m_anPullKeyCount[nKey] == 1) bPull = TRUE;
	return bPull;
}

/// <summary>
/// �w��L�[��b���Ă��邩�`�F�b�N���܂��B�����Ă����TRUE��Ԃ��܂��B
/// </summary>
/// <param name="nKey">�����Ă���L�[�̎��</param>
/// <returns>�����Ă��邩�ǂ���</returns>
int Keyboard::IsKeyPullHold(int nKey){
	if(nKey < 0 || nKey >= m_nKeyType) return FALSE;
	int bPull = FALSE;
	if(m_asKey[nKey] == 0 && m_anPullKeyCount[nKey] >= 1) bPull = TRUE;
	return bPull;
}

/// <summary>
/// �����Ă���L�[���w�莞�Ԃ��Ƃ�TRUE��Ԃ��܂��B
/// </summary>
/// <param name="nKey">�����Ă���L�[�̎��</param>
/// <param name="nFixedCount">TRUE��Ԃ��Ԋu(�P�ʁF�t���[��)</param>
/// <returns>�w�莞�ԂɂȂ������ǂ���</returns>
int Keyboard::IsKeyFixedPush(int nKey, int nFixedCount){
	if(nKey < 0 || nKey >= m_nKeyType || nFixedCount <= 0 || nFixedCount >= INT_MAX - 1) return FALSE;
	int bFixedPush = FALSE;
	//�������u�Ԃ�TRUE�ɂ��邽�߂Ɋ������]���1�ɂ���
	if(m_asKey[nKey] > 0 && m_anPushKeyCount[nKey] % nFixedCount == 1) bFixedPush = TRUE;
	return bFixedPush;
}
