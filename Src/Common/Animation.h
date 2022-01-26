#pragma once
#include "../Task.h"
#include <vector>
#include <math.h>

class Animation : public Task
{
public:
	Animation();
	~Animation();

	void Update() override;
	void DrawLoop() override{}

	/// <summary>
	/// �A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="count">�A�j���[�V�������鎞��</param>
	/// <returns>�ݒ肵���z��v�f�ԍ�</returns>
	int SetAnimationCount(const int& nCount){
		if(nCount < 0) return Invalid;

		auto itrBegin = m_anAnimationMaxCount.begin();
		auto itrEnd = m_anAnimationMaxCount.end();
		auto itrFactor = std::find(itrBegin, itrEnd, Invalid);
		//�v�f�ԍ����擾
		const int nIndex = std::distance(itrBegin, itrFactor);

		if(nIndex == m_nMaxIndex) return Invalid;

		m_anAnimationNowCount.at(nIndex) = 0;
		m_anAnimationMaxCount.at(nIndex) = nCount;
		m_abAnimation.at(nIndex) = TRUE;
		m_anIndexList.push_back(nIndex);
		return nIndex;
	}

	/// <summary>
	/// �w��̎��ԕ��x����A�A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="nCount">�A�j���[�V�������鎞��</param>
	/// <param name="nDelayCount">�A�j���[�V�����O�̒x�����鎞��</param>
	/// <returns>�ݒ肵���z��v�f�ԍ�</returns>
	int SetAnimationDelayCount(const int& nCount, const int& nDelayCount){
		if(nDelayCount < 0 || nDelayCount >= INT_MAX) return Invalid;

		const int nIndex = SetAnimationCount(nCount);
		if(nIndex == Invalid) return Invalid;

		m_anAnimationDelayNowCount.at(nIndex) = 0;
		m_anAnimationDelayMaxCount.at(nIndex) = nDelayCount;
		return nIndex;
	}

	/// <summary>
	/// �A�j���[�V�����̑��x�����A�A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="nCount">�A�j���[�V�������鎞��</param>
	/// <param name="nSpeedCount">�A�j���[�V�������鑬�x</param>
	/// <returns></returns>
	int SetAnimationSpeed(const int& nCount, const int& nSpeedCount){
		if(nSpeedCount < 0 || nSpeedCount >= INT_MAX) return Invalid;

		const int nIndex = SetAnimationCount(nCount);
		if(nIndex == Invalid) return Invalid;

		m_anAnimationSpeed.at(nIndex) = nSpeedCount;
		return nIndex;
	}

	/// <summary>
	/// �w��J�E���^���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationNowCount.at(nIndex);
	}

	/// <summary>
	/// �w��J�E���^�I���l���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationMaxCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationMaxCount.at(nIndex);
	}

	/// <summary>
	/// �w��x���J�E���^���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationDelayCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationDelayNowCount.at(nIndex);
	}

	/// <summary>
	/// �w��x���J�E���^�I���l���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationDelayMaxCount(const int& nIndex) const {
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationDelayMaxCount.at(nIndex);
	}

	/// <summary>
	/// �w��J�E���^�̑��x���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationSpeed(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationSpeed.at(nIndex);
	}

	/// <summary>
	/// �w��J�E���g�ɓ��B�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <param name="nMatchCount">�w��J�E���g</param>
	/// <returns>TRUE�F�w��J�E���^�ɂȂ����@�AFALSE�F�w��J�E���^�ɂȂ��Ă��Ȃ�</returns>
	int IsMatchedAnimationCount(const int& nIndex, const int& nMatchCount) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		if(nMatchCount < 0 || nMatchCount > m_anAnimationMaxCount.at(nIndex)) return Invalid;

		int bMatch = FALSE;
		if(m_anAnimationNowCount.at(nIndex) == nMatchCount) bMatch = TRUE;
		return bMatch;
	}

	/// <summary>
	/// �w��J�E���^���J�E���g���I�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>TRUE: �J�E���g���I�����A FALSE�F �J�E���g���I���Ă��Ȃ�</returns>
	int IsFinishedAnimationCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationNowCount.at(nIndex) == Invalid) return Invalid;

		int bFinish = FALSE;
		if(m_anAnimationNowCount.at(nIndex) == m_anAnimationMaxCount.at(nIndex)) bFinish = TRUE;
		return bFinish;
	}

	/// <summary>
	/// �w��J�E���g�ɓ��B�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <param name="nMatchCount">�w��J�E���g</param>
	/// <returns>TRUE�F�w��J�E���^�ɂȂ����@�AFALSE�F�w��J�E���^�ɂȂ��Ă��Ȃ�</returns>
	int IsMatchedAnimationDelayCount(const int& nIndex, const int& nMatchCount) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		if(nMatchCount < 0 || nMatchCount > m_anAnimationDelayMaxCount.at(nIndex)) return Invalid;

		int bMatch = FALSE;
		if(m_anAnimationDelayNowCount.at(nIndex) == nMatchCount) bMatch = TRUE;
		return bMatch;
	}

	/// <summary>
	/// �w��x���J�E���^���J�E���g���I�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>TRUE: �J�E���g���I�����A FALSE�F �J�E���g���I���Ă��Ȃ�</returns>
	int IsFinishedAnimationDelayCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayNowCount.at(nIndex) == Invalid) return Invalid;

		int bFinish = FALSE;
		if(m_anAnimationDelayNowCount.at(nIndex) == m_anAnimationDelayMaxCount.at(nIndex)) bFinish = TRUE;
		return bFinish;
	}

	/// <summary>
	/// �w��J�E���^���~���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int StopAnimation(const int& nIndex){
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;

		m_abAnimation.at(nIndex) = FALSE;
		return TRUE;
	}

	/// <summary>
	/// �w��J�E���^���ăJ�E���g���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int RestartAnimation(const int& nIndex){
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;

		m_abAnimation.at(nIndex) = TRUE;
		return TRUE;
	}

	/// /// <summary>
	/// �o�^�ς݂̃J�E���^��S�Ē�~���܂��B
	/// </summary>
	/// <returns></returns>
	int StopAllAnimation(){
		const int nSize = static_cast<int>(m_anIndexList.size());
		for(int i = 0; i < nSize; i++){
			const int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex) != Invalid) m_abAnimation.at(nIndex) = FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// �o�^�ς݂̃J�E���^��S�čăJ�E���g���܂��B
	/// </summary>
	/// <returns></returns>
	int RestartAllAnimation(){
		const int nSize = static_cast<int>(m_anIndexList.size());
		for(int i = 0; i < nSize; i++){
			const int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex) != Invalid) m_abAnimation.at(nIndex) = TRUE;
		}
		return TRUE;
	}

	/// <summary>
	/// �w��J�E���^����~���Ă��邩�`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int IsStoppedAnimation(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_abAnimation.at(nIndex);
	}

	/// <summary>
	/// �o�^�ς݂̃J�E���^���S�Ē�~���Ă��邩�`�F�b�N���܂��B
	/// </summary>
	/// <returns></returns>
	int IsAllStoppedAnimation() const{
		const int nSize = static_cast<int>(m_anIndexList.size());
		int nCount = 0;
		for(int i = 0; i < nSize; i++){
			const int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex)) break;
			nCount++;
		}
		const int bAllStop = (nCount == nSize);
		return bAllStop;
	}

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetAnimationSmooth(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		else if(tStart == tEnd) return tEnd;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tMax = static_cast<T>(m_anAnimationMaxCount.at(nIndex));

		const float fRatio = static_cast<float>(tNow) / static_cast<float>(tMax);
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetAnimationAccelerate(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		else if(tStart == tEnd) return tEnd;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tMax = static_cast<T>(m_anAnimationMaxCount.at(nIndex));
		const float fDiv = static_cast<float>(tNow) / static_cast<float>(tMax);
		const float fRatio = fDiv * fDiv;
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetAnimationSlowDown(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		else if(tStart == tEnd) return tEnd;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tMax = static_cast<T>(m_anAnimationMaxCount.at(nIndex));
		const float fDiv = static_cast<float>(tNow) / static_cast<float>(tMax);
		const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// ���������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationSmoothLaps(const int& nIndex, const T& tStart, const T& tMiddle, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tCenter = static_cast<T>(m_anAnimationMaxCount.at(nIndex) / static_cast<T>(2));
		T tValue;
		if(tNow < tCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fRatio = static_cast<float>(tNow) / static_cast<float>(tCenter);
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			tNow -= tCenter;
			const float fRatio = static_cast<float>(tNow) / static_cast<float>(tCenter);
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ����������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationAccelerateLaps(const int& nIndex, const T& tStart, const T& tMiddle, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tCenter = static_cast<T>(m_anAnimationMaxCount.at(nIndex) / static_cast<T>(2));
		T tValue;
		if(tNow < tCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fDiv = static_cast<float>(tNow) / static_cast<float>(tCenter);
			const float fRatio = fDiv * fDiv;
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			tNow -= tCenter;
			const float fDiv = static_cast<float>(tNow) / static_cast<float>(tCenter);
			const float fRatio = fDiv * fDiv;
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ�ꌸ�������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationSlowDownLaps(const int& nIndex, const T& tStart, const T& tMiddle, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tCenter = static_cast<T>(m_anAnimationMaxCount.at(nIndex) / static_cast<T>(2));

		T tValue;
		if(tNow < tCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fDiv = static_cast<float>(tNow) / static_cast<float>(tCenter);
			const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			tNow -= tCenter;
			const float fDiv = static_cast<float>(tNow) / static_cast<float>(tCenter);
			const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�܂Ō����A���Ԓl���I���l�܂ŉ����̉����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationGravityLaps(const int& nIndex, const T& tStart, const T& tMiddle, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return static_cast<T>(Invalid);
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;

		T tNow = static_cast<T>(m_anAnimationNowCount.at(nIndex));
		T tCenter = m_anAnimationMaxCount.at(nIndex) / static_cast<T>(2);
		if(tNow < tCenter) return GetAnimationSlowDownLaps(nIndex, tStart, tMiddle, tEnd);
		else return GetAnimationAccelerateLaps(nIndex, tStart, tMiddle, tEnd);
	}
	//��nIndex�̃A�j���[�V����������l���擾����p

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetMomentSmooth(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(nNow <= 0) return tStart;
		if(tStart == tEnd || nNow >= nMax || nMax <= 0) return tEnd;

		const float fRatio = static_cast<float>(nNow) / static_cast<float>(nMax);
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetMomentAccelerate(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(nNow <= 0) return tStart;
		if(tStart == tEnd || nNow >= nMax || nMax <= 0) return tEnd;

		const float fDiv = static_cast<float>(nNow) / static_cast<float>(nMax);
		const float fRatio = fDiv * fDiv;
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template<typename T> T GetMomentSlowDown(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(nNow <= 0) return tStart;
		if(tStart == tEnd || nNow >= nMax || nMax <= 0) return tEnd;

		const float fDiv = static_cast<float>(nNow) / static_cast<float>(nMax);
		const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
		T tValue = tStart + static_cast<T>((tEnd - tStart) * fRatio);
		return tValue;
	}

	/// <summary>
	/// ���������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nCenter">nNow�̒��Ԓl</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns></returns>
	template<typename T> T GetMomentSmoothLaps(const T& tStart, const T& tMiddle, const T& tEnd, int nNow, const int nCenter, const int nMax) const{
		if(nNow <= 0) return tStart;
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;
		if(nNow >= nMax) return tEnd;

		T tValue;
		if(nNow < nCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fRatio = static_cast<float>(nNow) / static_cast<float>(nCenter);
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			nNow -= nCenter;
			const float fRatio = static_cast<float>(nNow) / static_cast<float>(nCenter);
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ����������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nCenter">nNow�̒��Ԓl</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns></returns>
	template<typename T> T GetMomentAccelerateLaps(const T& tStart, const T& tMiddle, const T& tEnd, int nNow, const int nCenter, const int nMax) const{
		if(nNow <= 0) return tStart;
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;
		if(nNow >= nMax) return tEnd;

		T tValue;
		if(nNow < nCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fDiv = static_cast<float>(nNow) / static_cast<float>(nCenter);
			const float fRatio = fDiv * fDiv;
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			nNow -= nCenter;
			const float fDiv = static_cast<float>(nNow) / static_cast<float>(nCenter);
			const float fRatio = fDiv * fDiv;
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ�ꌸ�������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nCenter">nNow�̒��Ԓl</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationSlowDownLaps(const T& tStart, const T& tMiddle, const T& tEnd, int nNow, const int nCenter, const int nMax) const{
		if(nNow <= 0) return tStart;
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;
		if(nNow >= nMax) return tEnd;

		T tValue;
		if(nNow < nCenter){
			if(tStart == tMiddle) return tMiddle;
			const float fDiv = static_cast<float>(nNow) / static_cast<float>(nCenter);
			const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
			tValue = tStart + static_cast<T>((tMiddle - tStart) * fRatio);
		}
		else{
			if(tMiddle == tEnd) return tEnd;
			nNow -= nCenter;
			const float fDiv = static_cast<float>(nNow) / static_cast<float>(nCenter);
			const float fRatio = 1 - (1 - fDiv) * (1 - fDiv);
			tValue = tMiddle + static_cast<T>((tEnd - tMiddle) * fRatio);
		}
		return tValue;
	}

	/// <summary>
	/// �J�n�l�`���Ԓl�܂Ō����A���Ԓl���I���l�܂ŉ����̉����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tMiddle">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nCenter">nNow�̒��Ԓl</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns></returns>
	template<typename T> T GetAnimationGravityLaps(const T& tStart, const T& tMiddle, const T& tEnd, int nNow, const int nCenter, const int nMax) const{
		if(nNow <= 0) return tStart;
		if(tStart == tMiddle && tMiddle == tEnd) return tStart;
		if(nNow >= nMax) return tEnd;

		if(nNow < nCenter) return GetAnimationSlowDownLaps(tStart, tMiddle, tEnd, nNow, nCenter, nMax);
		else return GetAnimationAccelerateLaps(tStart, tMiddle, tEnd, nNow, nCenter, nMax);
	}
private:
	const int m_nMaxIndex = 128;

	std::vector<int> m_anAnimationMaxCount;
	std::vector<int> m_anAnimationNowCount;
	std::vector<int> m_anAnimationDelayNowCount;
	std::vector<int> m_anAnimationDelayMaxCount;
	std::vector<int> m_anAnimationSpeed;
	std::vector<int> m_abAnimation;
	std::vector<int> m_anIndexList;

	void UpdateCount(const int& nIndexSize, std::vector<int>& anAnimeDeleteList);
};
 