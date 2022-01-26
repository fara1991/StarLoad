#pragma once

enum ResourceImage{
	//���[�h���
	IMAGE_LOAD_TITLE,
	IMAGE_LOAD_LOADING,
	IMAGE_LOAD_GAUGE_EMPTY,
	IMAGE_LOAD_GAUGE_FILL,
	IMAGE_LOAD_START,

	//���C�����
	IMAGE_TITLE_DISPLAY,
	IMAGE_TITLE_CURSOR,
	IMAGE_TITLE_PRACTICE,
	IMAGE_TITLE_PRACTICE_DESCRIPTION,
	IMAGE_TITLE_RESULT,
	IMAGE_TITLE_RESULT_DESCRIPTION,
	IMAGE_TITLE_CONFIG,
	IMAGE_TITLE_CONFIG_DESCRIPTION,
	IMAGE_TITLE_MANUAL,
	IMAGE_TITLE_MANUAL_DESCRIPTION,
	IMAGE_TITLE_CREDIT,
	IMAGE_TITLE_CREDIT_DESCRIPTION,
	IMAGE_TITLE_EXIT,
	IMAGE_TITLE_EXIT_DESCRIPTION,

	//���x���I�����
	IMAGE_TITLE_PRACTICE_LEVEL_BEGINNER,
	IMAGE_TITLE_PRACTICE_LEVEL_STANDARD,
	IMAGE_TITLE_PRACTICE_LEVEL_HARD,
	IMAGE_TITLE_PRACTICE_LEVEL_BEGINNER_DESCRIPTION,
	IMAGE_TITLE_PRACTICE_LEVEL_STANDARD_DESCRIPTION,
	IMAGE_TITLE_PRACTICE_LEVEL_HARD_DESCRIPTION,
	IMAGE_TITLE_PRACTICE_LEVEL_DESCRIPTION,

	//���U���g���
	IMAGE_TITLE_RESULT_DISPLAY_DESCRIPTION,

	//�R���t�B�O���
	IMAGE_TITLE_CONFIG_BGM,
	IMAGE_TITLE_CONFIG_SE,
	IMAGE_TITLE_CONFIG_BACK,
	IMAGE_TITLE_CONFIG_DISPLAY_DESCRIPTION,

	//�}�j���A�����
	IMAGE_TITLE_MANUAL_PAGE1,
	IMAGE_TITLE_MANUAL_PAGE2,
	IMAGE_TITLE_MANUAL_PAGE3,
	IMAGE_TITLE_MANUAL_PAGE4,
	IMAGE_TITLE_MANUAL_DESPLAY_DESCRIPTION,

	//�N���W�b�g�\�L���
	IMAGE_TITLE_CREDIT_PAGE,
	IMAGE_TITLE_CREDIT_DISPLAY_DESCRIPTION,
	//�Q�[���J�n���
	IMAGE_PRACTICE_BACKGROUND,
	IMAGE_PRACTICE_STAR_RED,
	IMAGE_PRACTICE_STAR_GREEN,
	IMAGE_PRACTICE_STAR_YELLOW,
	IMAGE_PRACTICE_STAR_WHITE,

	//�Q�[���I�����
	IMAGE_PRACTICE_GAME_RESTART,
	IMAGE_PRACTICE_GAME_CLEAR,
	IMAGE_PRACTICE_GAME_OVER,
	IMAGE_PRACTICE_SELECT_YES,
	IMAGE_PRACTICE_SELECT_NO,

	IMAGE_COUNT
};

enum ResourceSound{
	SOUND_BGM_TITLE,
	SOUND_BGM_STAGE,

	SOUND_SE_LOAD_OK,
	SOUND_SE_TITLE_OK,
	SOUND_SE_CANCEL,
	SOUND_SE_CURSOR_MOVE,
	SOUND_SE_BLOCK_MOVE,
	SOUND_SE_PLAYER_BLOCK_COLLISION,
	SOUND_SE_WHITE_BLOCK_COLLISION,
	SOUND_SE_CLEAR,
	SOUND_COUNT
};

class IResourceManager
{
public:
	virtual ~IResourceManager() = 0;
	virtual int GetGraphicsHandle(ResourceImage eImage) = 0;
	virtual int GetSoundsHandle(ResourceSound eSound) = 0;
	virtual int GetGraphicsLoadingCount() = 0;
	virtual int GetSoundsLoadingCount() = 0;
	virtual int IsLoadGraphics() = 0;
	virtual int IsLoadSounds() = 0;
	virtual void SetSoundsBGMVolume(int nPercent) = 0;
	virtual void SetSoundsSEVolume(int nPercent) = 0;
	virtual void AllSoundsStopBGMVolume() = 0;
	virtual void AllSoundsStopSEVolume() = 0;
};
