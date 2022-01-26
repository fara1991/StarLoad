#pragma once
#define _USE_MATH_DEFINES	//�~�����΂��g�p����̂ɕK�v

#include "../Task.h"
#include "../Common/IResourceManager.h"
#include "../Common/Animation.h"
#include "../Common/Keyboard.h"
#include "../Common/Json/json11.hpp"
#include "ISceneManager.h"
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//�V�[���̊��N���X
class BaseScene : public Task
{
public:
	BaseScene(ISceneManager* pChanger, IResourceManager* pResource);
	virtual ~BaseScene();

	virtual void Initialize();
	virtual void Update();
	virtual void DrawLoop();
	virtual void Finalize();

	/// <summary>
	/// �t�F�[�Y��ݒ肵�܂��B
	/// </summary>
	/// <param name="ePhase">�w��t�F�[�Y</param>
	void SetPhase(Phase ePhase)	{ m_pSceneChanger->SetPhase(ePhase); }

	/// <summary>
	/// �t�F�[�Y���擾���܂��B
	/// </summary>
	/// <returns>�t�F�[�Y</returns>
	int GetPhase()						{ return m_pSceneChanger->GetPhase(); }

	/// <summary>
	/// ���x����ݒ肵�܂��B
	/// </summary>
	/// <param name="eLevel">�w�背�x��</param>
	void SetLevel(Level eLevel)	{ m_pSceneChanger->SetLevel(eLevel); }

	/// <summary>
	/// ���x�����擾���܂��B
	/// </summary>
	/// <returns>���x��</returns>
	int GetLevel()						{ return m_pSceneChanger->GetLevel(); }

	/// <summary>
	/// �摜�n���h�����擾���܂��B
	/// </summary>
	/// <returns>�摜�n���h��</returns>
	int GetGraphicsHandle(ResourceImage eImage)	{ return m_pResource->GetGraphicsHandle(eImage); };

	/// <summary>
	/// BGM,SE�n���h�����擾���܂��B
	/// </summary>
	/// <returns>BGM,SE�n���h��</returns>
	int GetSoundsHandle(ResourceSound eSound)		{ return m_pResource->GetSoundsHandle(eSound); };

	/// <summary>
	/// �摜�ǂݍ��݃J�E���^���擾���܂��B
	/// </summary>
	/// <returns>�J�E���^</returns>
	int GetGraphicsLoadingCount()						{ return m_pResource->GetGraphicsLoadingCount(); };

	/// <summary>
	/// BGM,SE�ǂݍ��݃J�E���^���擾���܂��B
	/// </summary>
	/// <returns>�J�E���^</returns>
	int GetSoundsLoadingCount()						{ return m_pResource->GetSoundsLoadingCount(); };

	/// <summary>
	/// �J�E���^�ɑΉ������摜���������ɓǂݍ��݂܂��B
	/// �S�Ẳ摜���ǂݍ��݊������Ă����FALSE��Ԃ��܂��B
	/// </summary>
	/// <returns>�摜�ǂݍ��ݒ����ǂ���</returns>
	int IsLoadGraphics()									{ return m_pResource->IsLoadGraphics(); };

	/// <summary>
	/// �J�E���^�ɑΉ�����BGM,SE���������ɓǂݍ��݂܂��B
	/// �S�Ă�BGM,SE���ǂݍ��݊������Ă����FALSE��Ԃ��܂��B
	/// </summary>
	/// <returns>BGM,SE�ǂݍ��ݒ����ǂ���</returns>
	int IsLoadSounds()									{ return m_pResource->IsLoadSounds(); };
protected:
	ISceneManager * m_pSceneChanger;
	IResourceManager* m_pResource;
	Animation* m_pAnime;
	Keyboard* m_pKey;
	std::fstream m_fStream;

	json11::Json JsonConfigData = json11::Json::object{
		{ "BGM", 60 },
		{ "SE", 60 }
	};

	json11::Json JsonResultData = json11::Json::object{
		{
			"Begginer", json11::Json::object{
				{ "DateTime", "2018/05/01 00:00:00" },
				{ "Score", 50000 },
				{ "Rank", "D" }
			}
		},
		{
			"Standard", json11::Json::object{
				{ "DateTime", "2018/05/01 00:00:00" },
				{ "Score", 50000 },
				{ "Rank", "D" }
			}
		},
		{
			"Hard", json11::Json::object{
				{ "DateTime", "2018/05/01 00:00:00" },
				{ "Score", 50000 },
				{ "Rank", "D" }
			}
		}
	};

	const char* m_sResultFileName = "Resource/SaveData/Result.json";
	const char* m_sConfigFileName = "Resource/SaveData/Config.json";

	void InitializeLoadConfigStream();
	void InitializeLoadResultStream();
	void FinalizeLoadConfigStream();
	void FinalizeLoadResultStream();
	int EnableConvertDateTime(std::string sDatetime);
	std::string GetNowDateTime();

	/// <summary>
	/// BGM�̉��ʂ�ݒ肵�܂��B
	/// </summary>
	/// <param name="nVolume">���ʁ�</param>
	void SetGameDataVolumeBGM(int nVolume)	{ m_nVolumeBGM = nVolume; }

	/// <summary>
	/// SE�̉��ʂ�ݒ肵�܂��B
	/// </summary>
	/// <param name="nVolume">���ʁ�</param>
	void SetGameDataVolumeSE(int nVolume)	{ m_nVolumeSE = nVolume; }

	/// <summary>
	/// BGM�̉��ʂ��擾���܂��B
	/// </summary>
	/// <returns>���ʁ�</returns>
	int GetGameDataVolumeBGM()	const			{ return m_nVolumeBGM; }

	/// <summary>
	/// SE�̉��ʂ��擾���܂��B
	/// </summary>
	/// <returns>���ʁ�</returns>
	int GetGameDataVolumeSE()	const			{ return m_nVolumeSE; }

	/// <summary>
	/// ���t��ݒ肵�܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <param name="sTime">���t������</param>
	void SetGameDataDateTime(int nLevel, std::string sTime){
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return;
		m_asDatetime[nLevel] = sTime;
	}

	/// <summary>
	/// �X�R�A��ݒ肵�܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <param name="nScore">�X�R�A</param>
	void SetGameDataScore(int nLevel, int nScore){
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return;
		m_anScore[nLevel] = nScore;
	}

	/// <summary>
	/// �����N��ݒ肵�܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <param name="sRank">�����N</param>
	void SetGameDataRank(int nLevel, std::string sRank){
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return;
		m_asRank[nLevel] = sRank;
	}

	/// <summary>
	/// ���t���擾���܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <returns>���t������</returns>
	std::string GetGameDataDateTime(int nLevel) const {
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return "2018/05/01 00:00:00";
		return m_asDatetime[nLevel];
	}

	/// <summary>
	/// �X�R�A���擾���܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <returns>�X�R�A</returns>
	int GetGameDataScore(int nLevel) const {
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return Invalid;
		return m_anScore[nLevel];
	}

	/// <summary>
	/// �����N���擾���܂��B
	/// </summary>
	/// <param name="nLevel">���x��</param>
	/// <returns>�����N</returns>
	std::string GetGameDataRank(int nLevel) const {
		if(nLevel < 0 || nLevel > static_cast<int>(LEVEL_HARD)) return std::to_string(Invalid);
		return m_asRank[nLevel];
	}
private:
	int m_nVolumeBGM = 0;
	int m_nVolumeSE = 0;
	std::string m_asDatetime[3] = { "","","" };
	int m_anScore[3] = { 0,0,0 };
	std::string m_asRank[3] = { "","","" };
};

