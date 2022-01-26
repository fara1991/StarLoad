#pragma once
#include "../Task.h"
#include "IResourceManager.h"

const int m_nGraphicsCount = static_cast<int>(IMAGE_COUNT);
const int m_nSoundsCount = static_cast<int>(SOUND_COUNT);
const int m_nBGMCount = static_cast<int>(SOUND_BGM_STAGE) + 1;
const int m_nSECount = m_nSoundsCount - m_nBGMCount;

class Resource : public IResourceManager{
public:
	Resource(){}
	~Resource();

	/// <summary>
	/// �摜�ǂݍ��݃J�E���^���擾���܂��B
	/// </summary>
	/// <returns>�J�E���^</returns>
	int GetGraphicsLoadingCount() override { return m_nGraphicLoadingCount; }

	/// <summary>
	/// BGM,SE�ǂݍ��݃J�E���^���擾���܂��B
	/// </summary>
	/// <returns>�J�E���^</returns>
	int GetSoundsLoadingCount() override { return m_nSoundsLoadingCount; }

	/// <summary>
	/// �J�E���^�ɑΉ������摜���������ɓǂݍ��݂܂��B
	/// �S�Ẳ摜���ǂݍ��݊������Ă����FALSE��Ԃ��܂��B
	/// </summary>
	/// <returns>�摜�ǂݍ��ݒ����ǂ���</returns>
	int IsLoadGraphics() override{
		if(m_nGraphicLoadingCount >= static_cast<int>(IMAGE_COUNT)) return FALSE;

		m_anGraphicsHandleList[m_nGraphicLoadingCount] = LoadGraph(m_asGraphicsList[m_nGraphicLoadingCount]);
		m_nGraphicLoadingCount++;
		return TRUE;
	}

	/// <summary>
	/// �J�E���^�ɑΉ�����BGM,SE���������ɓǂݍ��݂܂��B
	/// �S�Ă�BGM,SE���ǂݍ��݊������Ă����FALSE��Ԃ��܂��B
	/// </summary>
	/// <returns>BGM,SE�ǂݍ��ݒ����ǂ���</returns>
	int IsLoadSounds() override{
		if(m_nSoundsLoadingCount >= static_cast<int>(SOUND_COUNT)) return FALSE;

		m_anSoundsHandleList[m_nSoundsLoadingCount] = LoadSoundMem(m_asSoundsList[m_nSoundsLoadingCount]);
		m_nSoundsLoadingCount++;
		return TRUE;
	}

	/// <summary>
	/// �w��̉摜�n���h�����擾���܂��B
	/// </summary>
	/// <param name="eImage">�w��摜�v�f</param>
	/// <returns>�摜�n���h��</returns>
	int GetGraphicsHandle(ResourceImage eImage){
		int nIndex = static_cast<int>(eImage);
		if(nIndex < 0 || nIndex >= static_cast<int>(IMAGE_COUNT)) return Invalid;
		return m_anGraphicsHandleList[nIndex];
	}

	/// <summary>
	/// �w���BGM,SE�n���h�����擾���܂��B
	/// </summary>
	/// <param name="eSound">�w��BGM,SE�v�f</param>
	/// <returns>BGM,SE�n���h��</returns>
	int GetSoundsHandle(ResourceSound eSound){
		int nIndex = static_cast<int>(eSound);
		if(nIndex < 0 || nIndex >= static_cast<int>(SOUND_COUNT)) return Invalid;
		return m_anSoundsHandleList[nIndex];
	}

	/// <summary>
	/// BGM�̉��ʂ��w�聓�ɂ��܂��B
	/// </summary>
	/// <param name="nPercent">���ʁ�(0�`100)</param>
	void SetSoundsBGMVolume(int nPercent){
		if(nPercent < 0) nPercent = 0;
		else if(nPercent > 100) nPercent = 100;
		int nVolume = static_cast<int>((255.0f / 100.0f) * nPercent);
		for(int i = 0; i < m_nBGMCount; i++) ChangeVolumeSoundMem(nVolume, m_anSoundsHandleList[i]);
	}

	/// <summary>
	/// SE�̉��ʂ��w�聓�ɂ��܂��B
	/// </summary>
	/// <param name="nPercent">���ʁ�(0�`100)</param>
	void SetSoundsSEVolume(int nPercent){
		if(nPercent < 0) nPercent = 0;
		else if(nPercent > 100) nPercent = 100;
		int nVolume = static_cast<int>((255.0f / 100.0f) * nPercent);
		for(int i = m_nBGMCount; i < m_nSoundsCount; i++) ChangeVolumeSoundMem(nVolume, m_anSoundsHandleList[i]);
	}

	/// <summary>
	/// �S�Ă�BGM�Đ��𒆒f���܂��B
	/// </summary>
	void AllSoundsStopBGMVolume(){
		for(int i = 0; i < m_nBGMCount; i++) StopSoundMem(m_anSoundsHandleList[i]);
	}

	/// <summary>
	/// �S�Ă�SE�Đ��𒆒f���܂��B
	/// </summary>
	void AllSoundsStopSEVolume(){
		for(int i = m_nBGMCount; i < m_nSoundsCount; i++) StopSoundMem(m_anSoundsHandleList[i]);
	}
private:
	int m_anGraphicsHandleList[m_nGraphicsCount];
	int m_anSoundsHandleList[m_nSoundsCount];
	int m_nGraphicLoadingCount = 0;
	int m_nSoundsLoadingCount = 0;

	const char* m_asGraphicsList[m_nGraphicsCount] = {
		"Resource/Graphics/load_title.png",
		"Resource/Graphics/loading.png",
		"Resource/Graphics/gauge_empty.png",
		"Resource/Graphics/gauge_fill.png",
		"Resource/Graphics/gamestart.png",
		"Resource/Graphics/title_display.png",
		"Resource/Graphics/cursor.png",
		"Resource/Graphics/practice.png",
		"Resource/Graphics/practice_description.png",
		"Resource/Graphics/result.png",
		"Resource/Graphics/result_description.png",
		"Resource/Graphics/config.png",
		"Resource/Graphics/config_description.png",
		"Resource/Graphics/manual.png",
		"Resource/Graphics/manual_description.png",
		"Resource/Graphics/credit.png",
		"Resource/Graphics/credit_description.png",
		"Resource/Graphics/exit.png",
		"Resource/Graphics/exit_description.png",
		"Resource/Graphics/begginer.png",
		"Resource/Graphics/standard.png",
		"Resource/Graphics/hard.png",
		"Resource/Graphics/begginer_description.png",
		"Resource/Graphics/standard_description.png",
		"Resource/Graphics/hard_description.png",
		"Resource/Graphics/level_description.png",
		"Resource/Graphics/result_display_description.png",
		"Resource/Graphics/bgm.png",
		"Resource/Graphics/se.png",
		"Resource/Graphics/config_back.png",
		"Resource/Graphics/config_display_description.png",
		"Resource/Graphics/manual_page1.png",
		"Resource/Graphics/manual_page2.png",
		"Resource/Graphics/manual_page3.png",
		"Resource/Graphics/manual_page4.png",
		"Resource/Graphics/manual_display_description.png",
		"Resource/Graphics/credit_page.png",
		"Resource/Graphics/credit_display_description.png",
		"Resource/Graphics/background.png",
		"Resource/Graphics/star1.png",
		"Resource/Graphics/star2.png",
		"Resource/Graphics/star3.png",
		"Resource/Graphics/star4.png",
		"Resource/Graphics/restart.png",
		"Resource/Graphics/clear.png",
		"Resource/Graphics/gameover.png",
		"Resource/Graphics/yes.png",
		"Resource/Graphics/no.png"
	};
	const char* m_asSoundsList[m_nSoundsCount] = {
		"Resource/Sounds/BGM/title.ogg",
		"Resource/Sounds/BGM/stage.ogg",
		"Resource/Sounds/SE/load_ok.ogg",
		"Resource/Sounds/SE/title_ok.ogg",
		"Resource/Sounds/SE/cancel.ogg",
		"Resource/Sounds/SE/cursor_move.ogg",
		"Resource/Sounds/SE/block_move.ogg",
		"Resource/Sounds/SE/player_collision.ogg",
		"Resource/Sounds/SE/white_collision.ogg",
		"Resource/Sounds/SE/clear.ogg"
	};

};
