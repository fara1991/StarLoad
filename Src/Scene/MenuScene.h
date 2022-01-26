#pragma once
#include "BaseScene.h"

class MenuScene : public BaseScene
{
public:
	//�R���X�g���N�^
	MenuScene(ISceneManager* pChanger, IResourceManager* pResource);
	virtual ~MenuScene();

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;

private:
	enum MenuCursor{
		CURSOR_MENU_PRACTICE,
		CURSOR_MENU_RESULT,
		CURSOR_MENU_CONFIG,
		CURSOR_MENU_MANUAL,
		CURSOR_MENU_CREDIT,
		CURSOR_MENU_EXIT,
		CURSOR_MENU_COUNT
	};

	enum LevelCursor{
		CURSOR_LEVEL_BEGINNER,
		CURSOR_LEVEL_STANDARD,
		CURSOR_LEVEL_HARD,
		CURSOR_LEVEL_COUNT
	};

	enum ConfigCursor{
		CURSOR_CONFIG_VOLUME_BGM,
		CURSOR_CONFIG_VOLUME_SE,
		CURSOR_CONFIG_EXIT,
		CURSOR_CONFIG_COUNT,
		CURSOR_CONFIG_BGM_COUNT = 20,
		CURSOR_CONFIG_SE_COUNT = 20,
	};

	enum ManualCursor{
		CURSOR_MANUAL_PAGE1,
		CURSOR_MANUAL_PAGE2,
		CURSOR_MANUAL_PAGE3,
		CURSOR_MANUAL_PAGE4,
		CURSOR_MANUAL_COUNT
	};

	struct StructReplayData{
		std::string m_sDateTime;
		int m_nScore;
		std::string m_sRank;
	};

	struct StructCursor{
		int m_nMainCursorPos = 0;
		int m_nLevelCursorPos = 0;
		int m_nConfigCursorPos = 0;
		int m_nConfigBGMCursorPos = 12;		//�R���t�B�O�t�@�C������ǂݎ���Ēl�ύX����
		int m_nConfigSECursorPos = 8;
		int m_nManualCursorPos = 0;
		const int m_nMainCursorMaxPos = static_cast<int>(CURSOR_MENU_COUNT);
		const int m_nLevelCursorMaxPos = static_cast<int>(CURSOR_LEVEL_COUNT);
		const int m_nConfigCursorMaxPos = static_cast<int>(CURSOR_CONFIG_COUNT);
		const int m_nConfigBGMCursorMaxPos = static_cast<int>(CURSOR_CONFIG_BGM_COUNT);
		const int m_nConfigSECursorMaxPos = static_cast<int>(CURSOR_CONFIG_SE_COUNT);
		const int m_nManualCursorMaxPos = static_cast<int>(CURSOR_MANUAL_COUNT);
	};

	struct StructPushKey{
		int m_bLeftKeyPush = FALSE;
		int m_bRightKeyPush = FALSE;
		int m_bUpKeyPush = FALSE;
		int m_bDownKeyPush = FALSE;
		int m_bOKKeyPush = FALSE;
		int m_bCancelKeyPush = FALSE;
	};

	struct StructIndex{
		int m_nAnimeIndex = Invalid;
		int m_nAnimeLoopIndex = Invalid;
	};

	struct StructCount{
		const int m_nMoveCursorCount = 15;		//�J�[�\���ړ�����
		const int m_nMovePhaseCount = 30;		//�t�F�[�Y�ړ�����
		const int m_nLoopAlphaMaxCount = 30;	//���l���[�v�ɕK�v�Ȏ���
		int m_nLoopAlphaNowCount = 0;				//���l���[�v���ݎ���
	};

	StructReplayData* m_apDataSet[static_cast<int>(CURSOR_LEVEL_COUNT)];
	StructCursor* m_pCursorSet;
	StructPushKey* m_pPushSet;
	StructIndex* m_pIndexSet;
	StructCount* m_pCountSet;

	int m_nBackGroundHandle = GetGraphicsHandle(IMAGE_PRACTICE_BACKGROUND);
	float m_nDrawMenuNowAngle = 0.0f;

	/// <summary>
	/// ���[�v�J�E���^���������܂��B
	/// </summary>
	void UpdateAlphaCount(){
		if(m_pCountSet->m_nLoopAlphaNowCount == 0) m_pIndexSet->m_nAnimeLoopIndex = m_pAnime->SetAnimationCount(m_pCountSet->m_nLoopAlphaMaxCount);
		m_pCountSet->m_nLoopAlphaNowCount = (m_pCountSet->m_nLoopAlphaNowCount + 1) % m_pCountSet->m_nLoopAlphaMaxCount;
	}

	void UpdateMoveCursorAction();
	void UpdateGoKeyAction();
	void UpdateCancelKeyAction();

	void MoveCursorKeyPushCheck();
	void MoveCursorProcess();
	int& GetCursorPos();
	const int& GetCursorMaxPos();
	int& GetVolumeCursorPos();
	const int& GetVolumeCursorMaxPos();

	void DrawPhaseTitle();
	int GetDrawMenuHandle(const int& nIndex);
	int GetDrawMenuDescriptionHandle(const int& nIndex);
	void DrawPhaseLevel();
	int GetDrawLevelHandle(const int& nIndex);
	int GetDrawLevelDescriptionHandle(const int& nIndex);
	void DrawPhaseResult();
	void DrawPhaseConfig();
	void DrawPhaseManual();
	void DrawPhaseCredit();
};
