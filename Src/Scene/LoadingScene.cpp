#include "LoadingScene.h"

LoadingScene::LoadingScene(ISceneManager* pChanger, IResourceManager* pResource) : BaseScene(pChanger, pResource){
}

/// <summary>
/// �X�V����
/// </summary>
void LoadingScene::Update(){
	if(m_pResource->IsLoadGraphics()) m_nLoadCount++;
	else if(m_pResource->IsLoadSounds()) m_nLoadCount++;
	else{
		if(!m_bFinishScene){
			if(!m_pKey->IsKeyPush(KEY_INPUT_Z)) return;
			m_bFinishScene = TRUE;
			PlaySoundMem(GetSoundsHandle(SOUND_SE_LOAD_OK), DX_PLAYTYPE_BACK);
		}
		//�Q�[�W100������1�b���Ă��玟�̃V�[����
		if(m_nWaitCount >= m_nWaitMaxCount){
			m_pSceneChanger->ChangeScene(SCENE_MENU);
			SetPhase(PHASE_TITLE);
		}
		m_nWaitCount++;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void LoadingScene::DrawLoop(){
	int nAlpha = 255 - (255 / m_nWaitMaxCount) * m_nWaitCount;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	DrawDescription();
	DrawLoadGauge();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - nAlpha);
	//�t�F�[�h�A�E�g
	DrawGraph(0, 0, m_pResource->GetGraphicsHandle(IMAGE_PRACTICE_BACKGROUND), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// ����������\�����܂��B
/// </summary>
void LoadingScene::DrawDescription(){
	DrawRotaGraph(WindowCenX, WindowCenY / 2, 1, 0, m_pResource->GetGraphicsHandle(IMAGE_LOAD_TITLE), TRUE);

	if(m_nLoadCount != m_nResourceCount || m_nWaitCount % 4 / 2 != 0) return;
	DrawRotaGraph(WindowCenX, WindowCenY + 30, 1, 0, m_pResource->GetGraphicsHandle(IMAGE_LOAD_START), TRUE);
}

/// <summary>
/// �f�ޓǂݍ��݊��������Q�[�W��\�����܂��B
/// </summary>
void LoadingScene::DrawLoadGauge(){
	float fPi = static_cast<float>(M_PI);
	float fRadian = (2 * fPi / 360) * (GetNowCount() / 2);
	int nAlpha = static_cast<int>(255 - 127 * sinf(fRadian));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	DrawRotaGraph(WindowCenX / 2, 360, 1, 0, m_pResource->GetGraphicsHandle(IMAGE_LOAD_LOADING), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	int nLength = 50 + static_cast<int>((500.0f / m_nResourceCount) * m_nLoadCount);
	DrawExtendGraph(50, 376, 550, 400, m_pResource->GetGraphicsHandle(IMAGE_LOAD_GAUGE_EMPTY), TRUE);
	DrawExtendGraph(50, 376, nLength, 400, m_pResource->GetGraphicsHandle(IMAGE_LOAD_GAUGE_FILL), TRUE);

	float fRatio = static_cast<float>(m_nLoadCount) / static_cast<float>(m_nResourceCount);
	DrawFormatString(480, 350, GetColor(255, 255, 255), "%.2f%%", fRatio * 100);
}
