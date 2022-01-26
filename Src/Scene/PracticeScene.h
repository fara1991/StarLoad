#pragma once
#include "BaseScene.h"
#include "../Parts/Block.h"
#include "../Parts/Player.h"

class PracticeScene : public BaseScene
{
public:
	//�R���X�g���N�^
	PracticeScene(ISceneManager* pChanger, IResourceManager* pResource);
	virtual ~PracticeScene();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void DrawLoop() override;
	virtual void Finalize() override;

private:
	enum BlockPosition{
		BLOCK_POSITION_C,
		BLOCK_POSITION_D,
		BLOCK_POSITION_E,
		BLOCK_POSITION_F,
		BLOCK_POSITION_G,
		BLOCK_POSITION_A,
		BLOCK_POSITION_B
	};

	struct StructIndex{
		int m_nAnimeIndex = Invalid;		//�X�e�[�W�̌����Ԃ��J�E���g
		int m_nFinishStageIndex = Invalid;	//�Q�[���i�s���~�܂�܂ł̃J�E���g
		int m_nMoveSceneIndex = Invalid;	//��ʈړ������܂ł̎��Ԃ��J�E���g
		int m_nFadeoutIndex = Invalid;	//�t�F�[�h�A�E�g�����܂ł��J�E���g
	};

	struct StructFlag{
		int m_bStageClear = FALSE;	//�X�e�[�W�I���t���O
		int m_bGameOver = FALSE;	//�Q�[���I�[�o�[�t���O
		int m_bContinue = FALSE;	//�R���e�B�j���[�t���O
		int m_bFadeout = FALSE;		//�t�F�[�h�A�E�g�t���O
		int m_bClearMusic = TRUE;	//�N���A��SE�t���O
	};

	struct StructStage{
		const int m_nStandMaxCount = 300;												//�Q�[���ҋ@����
		const int m_nFinishStageCount = 60;												//�Q�[���I���܂ł̎���
		const int m_nFadeoutMaxCount = 20;												//�t�F�[�h�A�E�g����
		int m_nGameScore = 0;																//�Q�[���X�R�A
		int m_nGameHiScore = 0;																//�Q�[���n�C�X�R�A
		const int m_nGameMaxCount = 114 * 60;											//�X�e�[�W�I���܂ł̎���
		std::string m_sGameRank = "D";													//�Q�[�������N
		std::string m_sGameHiRank = "";													//�Q�[���n�C�X�R�A���̃����N
		const int m_anRankingRate[4] = { 50000, 250000, 750000, 1500000 };	//�����N�グ���l�ꗗ
		int m_nAddRate = 57;																	//1F���ɑ�����X�R�A�l
		int m_nRateIndex = 0;																//�����N�グ�v�f�ԍ�
		const int m_nRateMaxIndex = 4;													//�����N�グ�v�f�ő�ԍ�
	};

	struct StructBlock{
		const int m_nBlockCount = 64;	//�΂�\�������
	};

	struct StructPlayer{
		const int m_nWidth = 40;									//�v���C���[���m�̕�
		int m_nBarIndex = 3;											//�v���C���[���ݒn
		const int m_nBarCount = 7;									//�v���C���[�̃o�[�̐�
		const int m_nFieldMinX = (WindowMaxX / 2) - 140;	//�ړ��\�̈捶�[X���W
		const int m_nFieldY = WindowMaxY - 50;					//�\��Y���W
	};

	StructIndex* m_pIndexSet;
	StructFlag* m_pFlagSet;
	StructStage* m_pStageSet;
	StructBlock* m_pBlockSet;
	StructPlayer* m_pPlayerSet;
	std::vector<Block*> m_apBlock;
	std::vector<Player*> m_apPlayer;

	int m_nSoundHandle;			//���y�n���h��

	void InitializeSceneStatus();
	void InitializeBlocks();
	void InitializePlayer();
	void UpdateStageClearProcess();
	void UpdateGameOverProcess();
	void UpdateFadeOutProcess();
	void UpdateGamePlayProcess();
	void UpdateRank(std::string& sRank);
	void UpdateBlocks();
	void CreateBlocks();
	void DeleteBlocks();
	void UpdatePlayers();
	void UpdateCollisionPlayers();
	void UpdateCollisionMovePlayers();
	void UpdateBarMovePlayers();
	void ReverseAllCollision();
	void DrawLoopBlocks();
	void DrawLoopPlayers();
	void FinalizeBlocks();
	void FinalizePlayers();

	/// <summary>
	/// �w��L�[�����������ǂ����`�F�b�N���܂��B
	/// </summary>
	/// <param name="nKey">�w��L�[</param>
	/// <returns>���������ǂ���</returns>
	int IsPushProcess(const int& nKey){ return m_pKey->IsKeyPush(nKey); }

	/// <summary>
	/// �w��L�[��15�t���[�������Ă��邩�`�F�b�N���܂��B
	/// </summary>
	/// <param name="nKey">�w��L�[</param>
	/// <returns>�w��t���[���o�߂������ǂ���</returns>
	int IsFixedProcess(const int& nKey){ return m_pKey->IsKeyFixedPush(nKey, 15); }
};