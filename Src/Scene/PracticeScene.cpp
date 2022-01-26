#include "PracticeScene.h"

PracticeScene::PracticeScene(ISceneManager* pChanger, IResourceManager* pResource) : BaseScene(pChanger, pResource){
	m_pIndexSet = new StructIndex();
	m_pFlagSet = new StructFlag();
	m_pStageSet = new StructStage();
	m_pBlockSet = new StructBlock();
	m_pPlayerSet = new StructPlayer();
}

PracticeScene::~PracticeScene(){
	DeletePtr(m_pIndexSet);
	DeletePtr(m_pFlagSet);
	DeletePtr(m_pStageSet);
	DeletePtr(m_pBlockSet);
	DeletePtr(m_pPlayerSet);
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void PracticeScene::Initialize(){
	InitializeSceneStatus();
	InitializeBlocks();
	InitializePlayer();
}

/// <summary>
/// �Q�[������ݒ肵�܂��B
/// </summary>
void PracticeScene::InitializeSceneStatus(){
	const int& nLevel = GetLevel();
	m_pStageSet->m_nGameHiScore = GetGameDataScore(nLevel);
	m_pStageSet->m_sGameHiRank = GetGameDataRank(nLevel);
	m_nSoundHandle = GetSoundsHandle(SOUND_BGM_STAGE);
}

/// <summary>
/// �u���b�N���������������܂��B
/// </summary>
void PracticeScene::InitializeBlocks(){
	m_pIndexSet->m_nAnimeIndex = m_pAnime->SetAnimationDelayCount(m_pStageSet->m_nGameMaxCount, m_pStageSet->m_nStandMaxCount);
	m_apBlock.resize(m_pBlockSet->m_nBlockCount);
}

/// <summary>
/// �v���C���[���������������܂��B
/// </summary>
void PracticeScene::InitializePlayer(){
	const int& nWidth = m_pPlayerSet->m_nWidth;
	const int& nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_GREEN);
	const int& nMaxIndex = m_pPlayerSet->m_nBarCount;
	const int& nWhiteHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_WHITE);
	const int nDiffIndex = nMaxIndex / 2;

	m_apPlayer.clear();
	m_apPlayer.resize(nMaxIndex);
	for(int i = (-1) * nDiffIndex; i < nMaxIndex - nDiffIndex; i++){
		const int nX = WindowCenX + i * nWidth;
		const int& nY = m_pPlayerSet->m_nFieldY;
		const int nIndex = i + nDiffIndex;
		const int& nAnimeIndex = m_pIndexSet->m_nAnimeIndex;
		m_apPlayer.at(nIndex) = new Player(nX, nY, nHandle, nWhiteHandle, nIndex, m_pAnime, nAnimeIndex);
	}

	//�ړ��s�G���A�𐶐�
	int anForbidIndex[2] = { GetLevel(), nMaxIndex - 1 - GetLevel() };
	for(int i = 0; i < 2; i++) m_apPlayer.at(anForbidIndex[i])->SetCollision();
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns>TRUE</returns>
void PracticeScene::Update(){
	UpdatePlayers();
	if(!m_pAnime->IsFinishedAnimationDelayCount(m_pIndexSet->m_nAnimeIndex)) return;

	if(m_pFlagSet->m_bStageClear) UpdateStageClearProcess();
	else if(m_pFlagSet->m_bGameOver) UpdateGameOverProcess();
	else UpdateGamePlayProcess();
}

/// <summary>
/// �X�e�[�W�N���A���̏��������܂��B
/// </summary>
void PracticeScene::UpdateStageClearProcess(){
	if(!m_pAnime->IsFinishedAnimationCount(m_pIndexSet->m_nFinishStageIndex)){
		//BGM�t�F�[�h�A�E�g
		const int nVolume = m_pAnime->GetAnimationSmooth(m_pIndexSet->m_nFinishStageIndex, GetGameDataVolumeBGM(), 0);
		m_pResource->SetSoundsBGMVolume(nVolume);

		UpdateBlocks();
		return;
	}
	else if(m_pFlagSet->m_bClearMusic){
		m_pFlagSet->m_bClearMusic = FALSE;
		const int& nHandle = GetSoundsHandle(SOUND_SE_CLEAR);
		int nVolume = static_cast<int>((255.0f / 100.0f) * GetGameDataVolumeSE());
		ChangeVolumeSoundMem(nVolume, nHandle);
		PlaySoundMem(nHandle, DX_PLAYTYPE_BACK);
	}
	if(m_pFlagSet->m_bFadeout) UpdateFadeOutProcess();

	if(CheckSoundMem(m_nSoundHandle)) StopSoundMem(m_nSoundHandle);
	if(IsFixedProcess(KEY_INPUT_LEFT) || IsFixedProcess(KEY_INPUT_RIGHT)){
		ReverseFlag(m_pFlagSet->m_bContinue);
		PlaySoundMem(GetSoundsHandle(SOUND_SE_CURSOR_MOVE), DX_PLAYTYPE_BACK);
	}
	if(IsPushProcess(KEY_INPUT_Z)){
		m_pIndexSet->m_nAnimeIndex = m_pAnime->SetAnimationCount(m_pStageSet->m_nFadeoutMaxCount);
		m_pFlagSet->m_bFadeout = TRUE;
		PlaySoundMem(GetSoundsHandle(SOUND_SE_TITLE_OK), DX_PLAYTYPE_BACK);
	}
}

/// <summary>
/// �Q�[���I�[�o�[���̏��������܂��B
/// </summary>
void PracticeScene::UpdateGameOverProcess(){
	if(!m_pAnime->IsFinishedAnimationCount(m_pIndexSet->m_nFinishStageIndex)){
		//BGM�t�F�[�h�A�E�g
		const int nVolume = m_pAnime->GetAnimationSmooth(m_pIndexSet->m_nFinishStageIndex, GetGameDataVolumeBGM(), 0);
		m_pResource->SetSoundsBGMVolume(nVolume);

		UpdateBlocks();
		return;
	}
	if(m_pFlagSet->m_bFadeout) UpdateFadeOutProcess();

	if(CheckSoundMem(m_nSoundHandle)) StopSoundMem(m_nSoundHandle);
	if(IsFixedProcess(KEY_INPUT_LEFT) || IsFixedProcess(KEY_INPUT_RIGHT)){
		ReverseFlag(m_pFlagSet->m_bContinue);
		PlaySoundMem(GetSoundsHandle(SOUND_SE_CURSOR_MOVE), DX_PLAYTYPE_BACK);
	}
	if(IsPushProcess(KEY_INPUT_Z)){
		m_pIndexSet->m_nAnimeIndex = m_pAnime->SetAnimationCount(m_pStageSet->m_nFadeoutMaxCount);
		m_pFlagSet->m_bFadeout = TRUE;
		PlaySoundMem(GetSoundsHandle(SOUND_SE_TITLE_OK), DX_PLAYTYPE_BACK);
	}
}

/// <summary>
/// �t�F�[�h�A�E�g���������܂��B
/// </summary>
void PracticeScene::UpdateFadeOutProcess(){
	if(!m_pAnime->IsFinishedAnimationCount(m_pIndexSet->m_nAnimeIndex)) return;

	m_pResource->AllSoundsStopBGMVolume();
	m_pResource->AllSoundsStopSEVolume();
	//�n�C�X�R�A
	if(m_pStageSet->m_nGameScore > m_pStageSet->m_nGameHiScore){
		SetGameDataDateTime(GetLevel(), GetNowDateTime());
		SetGameDataScore(GetLevel(), m_pStageSet->m_nGameScore);
		SetGameDataRank(GetLevel(), m_pStageSet->m_sGameRank);
		FinalizeLoadResultStream();
	}
	m_pAnime->RestartAllAnimation();
	if(m_pFlagSet->m_bContinue) m_pSceneChanger->ChangeScene(SCENE_PRACTICE);
	else{
		m_pSceneChanger->ChangeScene(SCENE_MENU);
		SetPhase(PHASE_TITLE);
	}
}

/// <summary>
/// �Q�[�����̏��������܂��B
/// </summary>
void PracticeScene::UpdateGamePlayProcess(){
	//�Q�[���I�[�o�[��
	if(!m_pFlagSet->m_bStageClear && m_pPlayerSet->m_nBarIndex == Invalid){
		if(m_pFlagSet->m_bGameOver) return;
		m_pFlagSet->m_bGameOver = TRUE;
		m_pIndexSet->m_nFinishStageIndex = m_pAnime->SetAnimationCount(m_pStageSet->m_nFinishStageCount);
		PlaySoundMem(GetSoundsHandle(SOUND_SE_PLAYER_BLOCK_COLLISION), DX_PLAYTYPE_BACK);
	}
	//�Q�[���N���A��
	else if(!m_pFlagSet->m_bGameOver && m_pAnime->IsFinishedAnimationCount(m_pIndexSet->m_nAnimeIndex)){
		if(m_pFlagSet->m_bStageClear) return;
		m_pFlagSet->m_bStageClear = TRUE;
		m_pPlayerSet->m_nBarIndex = Invalid;
		m_pIndexSet->m_nFinishStageIndex = m_pAnime->SetAnimationCount(m_pStageSet->m_nFinishStageCount);
	}
	if(!CheckSoundMem(m_nSoundHandle)) PlaySoundMem(m_nSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
	UpdateBlocks();

	//�X�R�A
	int& nScore = m_pStageSet->m_nGameScore;
	int& nIndex = m_pStageSet->m_nRateIndex;
	const int& nMaxIndex = m_pStageSet->m_nRateMaxIndex;
	int& nAddRate = m_pStageSet->m_nAddRate;
	nScore += nAddRate;

	if(nIndex >= nMaxIndex) return;
	const int& nRate = m_pStageSet->m_anRankingRate[nIndex];
	if(nScore >= nRate){
		nIndex++;
		nAddRate *= 2;
		UpdateRank(m_pStageSet->m_sGameRank);
		UpdateRank(m_pStageSet->m_sGameHiRank);
	}
}

/// <summary>
/// �����N���グ�鏈�������܂��B
/// </summary>
/// <param name="sRank">���݂̃����N</param>
void PracticeScene::UpdateRank(std::string& sRank){
	if(sRank == "D") sRank = "C";
	else if(sRank == "C") sRank = "B";
	else if(sRank == "B") sRank = "A";
	else if(sRank == "A") sRank = "S";
}

/// <summary>
/// �u���b�N�X�V���������܂��B
/// </summary>
void PracticeScene::UpdateBlocks(){
	DeleteBlocks();
	CreateBlocks();
	for(int i = 0; i < m_pBlockSet->m_nBlockCount; i++){
		if(m_apBlock.at(i) == nullptr) continue;
		m_apBlock.at(i)->Update();
		int nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_GREEN);
		if(m_apBlock.at(i)->GetBlockPositionY() < WindowCenY) continue;
		if(m_apBlock.at(i)->GetBlockHandle() != nHandle) continue;
		//�΁��� or ��
		nHandle = GetGraphicsHandle((GetRand(TRUE) ? IMAGE_PRACTICE_STAR_YELLOW : IMAGE_PRACTICE_STAR_RED));
		m_apBlock.at(i)->SetBlockHandle(nHandle);
	}
}

/// <summary>
/// �u���b�N�������������܂��B
/// </summary>
void PracticeScene::CreateBlocks(){
	const int bHard = (GetLevel() == static_cast<int>(LEVEL_HARD));
	const int bHalfCount = (m_pAnime->GetAnimationCount(m_pIndexSet->m_nAnimeIndex) >= m_pStageSet->m_nGameMaxCount / 2);
	const int nInterval = static_cast<int>((bHard ? 30 : 60) * (bHalfCount ? (2.0f / 3.0f) : 1));
	const int& nGameCount = m_pAnime->GetAnimationCount(m_pIndexSet->m_nAnimeIndex);
	if(nGameCount % nInterval != 0 || nGameCount > m_pStageSet->m_nGameMaxCount - 180) return;
	
	int nIndex = 0;
	while(nIndex < m_pBlockSet->m_nBlockCount){
		if(m_apBlock.at(nIndex) == nullptr) break;
		nIndex++;
	}

	//���x���f�U�C��
	const int nBlock = 7;
	const int nYellowMin = 2 + (1 - GetLevel() / 2);
	const int nRandom = nYellowMin + GetRand(3 - GetLevel());
	//nRandom�̐��������F���𐶐�
	std::vector<int> anTempNum = { 0, 1, 2, 3, 4, 5, 6 };
	std::vector<int> anYellowPos;
	anYellowPos.resize(nRandom);
	for(int i = nRandom - 1; i >= 0; i--){
		const int nSize = static_cast<int>(anTempNum.size());
		anYellowPos.at(i) = anTempNum.at(GetRand(nSize - 1));

		auto itrFactor = std::find(anTempNum.begin(), anTempNum.end(), anTempNum.at(i));
		const int nFindIndex = std::distance(anTempNum.begin(), itrFactor);
		anTempNum.erase(anTempNum.begin() + nFindIndex);
	}

	const int& nAnimeIndex = m_pIndexSet->m_nAnimeIndex;
	int bWhite = FALSE;
	const int nWhitePatternLine = 3;
	for(int i = nIndex; i < nIndex + nBlock; i++){
		if(m_apBlock.at(i) != nullptr) continue;
		const int nBlockIndex = i % nBlock;
		const int nX = m_pPlayerSet->m_nFieldMinX + static_cast<int>(m_pPlayerSet->m_nWidth * (nBlockIndex + 0.5f));
		const int nPattern = 99;
		int nChange = GetRand(nPattern - nWhitePatternLine * bWhite);
		//���F�w��̏ꏊ�͉��F��
		for(int j = 0; j < nRandom; j++){
			if(anYellowPos.at(j) != nBlockIndex) continue;
			nChange = nPattern - nWhitePatternLine;	//���F��
			break;
		}

		int nHandle = Invalid;
		//����2�ȏ�܂Ƃ߂ė����Ȃ�
		if(nChange > nPattern - nWhitePatternLine){
			nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_WHITE);
			bWhite = TRUE;
		}
		else if(nChange >= nPattern / 3 * 2) nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_YELLOW);
		else if(nChange >= nPattern / 3) nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_GREEN);
		else nHandle = GetGraphicsHandle(IMAGE_PRACTICE_STAR_RED);

		m_apBlock.at(i) = new Block(nX, -20, GetLevel() + 3, nBlockIndex, nHandle, m_pAnime, nAnimeIndex);
	}
}

/// <summary>
/// �u���b�N�폜���������܂��B
/// </summary>
void PracticeScene::DeleteBlocks(){
	//�폜�`�F�b�N
	for(int i = 0; i < m_pBlockSet->m_nBlockCount; i++){
		if(m_apBlock.at(i) == nullptr) continue;
		if(m_apBlock.at(i)->GetBlockPositionY() < WindowMaxY + 20) continue;
		DeletePtr(m_apBlock.at(i));
	}
}

/// <summary>
/// �v���C���[�X�V���������܂��B
/// </summary>
void PracticeScene::UpdatePlayers(){
	const int& nIndex = m_pPlayerSet->m_nBarIndex;
	for(int i = 0; i < m_pPlayerSet->m_nBarCount; i++){
		int j = (i <= nIndex ? nIndex - i : i);
		if(m_apPlayer.at(j) == nullptr) continue;
		m_apPlayer.at(j)->Update();

		const int& nRefIndex = m_pPlayerSet->m_nBarIndex;
		if(nRefIndex == Invalid) continue;

		if(m_apPlayer.at(j)->GetCollision()) continue;
		m_apPlayer.at(j)->SetFlash(nRefIndex);
		UpdateCollisionPlayers();
	}
	UpdateBarMovePlayers();
}

/// <summary>
/// �v���C���[�ƃu���b�N�̏Փ˃`�F�b�N�����܂��B
/// </summary>
void PracticeScene::UpdateCollisionPlayers(){
	const int& nIndex = m_pPlayerSet->m_nBarIndex;
	for(int i = 0; i < m_pBlockSet->m_nBlockCount; i++){
		//�u���b�N�J���[�ɂ���ď����ύX
		if(m_apBlock.at(i) == nullptr || m_apBlock.at(i)->GetCollision()) continue;
		const int& nPlayerX = m_apPlayer.at(nIndex)->GetPlayerPositionX();
		const int& nPlayerY = m_apPlayer.at(nIndex)->GetPlayerPositionY();
		const int& nBlockX = m_apBlock.at(i)->GetBlockPositionX();
		const int& nBlockY = m_apBlock.at(i)->GetBlockPositionY();
		if(nBlockY < nPlayerY) continue;

		const int& nBlockHandle = m_apBlock.at(i)->GetBlockHandle();
		const int& nSoundHandle = GetSoundsHandle(SOUND_SE_PLAYER_BLOCK_COLLISION);
		if(nBlockHandle == GetGraphicsHandle(IMAGE_PRACTICE_STAR_RED)){
			//��
			if(nPlayerX == nBlockX){
				m_apPlayer.at(nIndex)->SetCollision();
				UpdateCollisionMovePlayers();
				PlaySoundMem(nSoundHandle, DX_PLAYTYPE_BACK);
			}
		}
		//��
		else if(nBlockHandle == GetGraphicsHandle(IMAGE_PRACTICE_STAR_WHITE)) ReverseAllCollision();
		//���A�΂͓��ɂȂ�

		//�ʉ߂����΂͒ʉߌ�Փ˔��肵�Ȃ�
		m_apBlock.at(i)->SetCollision();
		return;
	}
}

/// <summary>
/// �v���C���[�ƃu���b�N�̏Փˌ�̏��������܂��B
/// </summary>
void PracticeScene::UpdateCollisionMovePlayers(){
	//���ݒn�����ԋ߂��ړ����������
	int& nIndex = m_pPlayerSet->m_nBarIndex;
	if(nIndex == Invalid) return;

	const int& nCount = m_pPlayerSet->m_nBarCount;
	for(int i = 2; i < nCount * 2; i++){
		//���ݒn�̍��A�E�̏��Ń`�F�b�N
		const int nCheckIndex = nIndex + (i / 2) * (i % 2 == 0 ? -1 : 1);
		if(nCheckIndex < 0 || nCheckIndex >= nCount) continue;
		if(m_apPlayer.at(nCheckIndex) == nullptr || m_apPlayer.at(nCheckIndex)->GetCollision()) continue;

		const int& nPlayerY = m_apPlayer.at(nCheckIndex)->GetPlayerPositionY();
		for(int j = 0; j < m_pBlockSet->m_nBlockCount; j++){
			if(m_apBlock.at(j) == nullptr) continue;
			const int& nBlockY = m_apBlock.at(j)->GetBlockPositionY();
			const int& nBlockIndex = m_apBlock.at(j)->GetBlockIndex();
			if(nBlockY < nPlayerY || nBlockIndex != nCheckIndex) continue;

			//�ړ��悪�ԂȂ疳��
			const int& nBlockHandle = m_apBlock.at(j)->GetBlockHandle();
			if(nBlockHandle == GetGraphicsHandle(IMAGE_PRACTICE_STAR_RED)) break;
			nIndex = nBlockIndex;
			return;
		}
	}

	//�ړ��悪�Ȃ���΃v���C���[�΂�S�ĐԂ�
	nIndex = Invalid;
	for(int i = 0; i < m_pPlayerSet->m_nBarCount; i++) m_apPlayer.at(i)->SetCollision();
}

/// <summary>
/// �v���C���[�ړ����������܂��B
/// </summary>
void PracticeScene::UpdateBarMovePlayers(){
	int& nIndex = m_pPlayerSet->m_nBarIndex;
	if(nIndex == Invalid) return;
	const int& nMaxIndex = m_pPlayerSet->m_nBarCount;
	const int anKey[7] = { KEY_INPUT_S, KEY_INPUT_D, KEY_INPUT_F, KEY_INPUT_SPACE, KEY_INPUT_J, KEY_INPUT_K, KEY_INPUT_L };
	const int nDefIndex = nIndex;
	//�Ή��L�[���������Ƃ�
	for(int i = 0; i < nMaxIndex; i++){
		if(IsPushProcess(anKey[i]) && !m_apPlayer.at(i)->GetCollision()){
			nIndex = i;
			PlaySoundMem(GetSoundsHandle(SOUND_SE_BLOCK_MOVE), DX_PLAYTYPE_BACK);
		}
	}
	//���E�L�[���������Ƃ�
	if(IsFixedProcess(KEY_INPUT_LEFT) && nIndex > 0){
		while(nIndex >= 0){
			nIndex--;
			if(nIndex < 0){
				nIndex = nDefIndex;
				break;
			}

			const int& bNotCollision = !m_apPlayer.at(nIndex)->GetCollision();
			if(!bNotCollision) continue;
			PlaySoundMem(GetSoundsHandle(SOUND_SE_BLOCK_MOVE), DX_PLAYTYPE_BACK);
			break;
		}
	}
	else if(IsFixedProcess(KEY_INPUT_RIGHT) && nIndex < nMaxIndex - 1){
		while(nIndex <= nMaxIndex - 1){
			nIndex++;
			if(nIndex >= nMaxIndex){
				nIndex = nDefIndex;
				break;
			}

			const int& bNotCollision = !m_apPlayer.at(nIndex)->GetCollision();
			if(!bNotCollision) continue;
			PlaySoundMem(GetSoundsHandle(SOUND_SE_BLOCK_MOVE), DX_PLAYTYPE_BACK);
			break;
		}
	}
}

/// <summary>
/// �Փ˔���𔽓]���܂��B
/// </summary>
void PracticeScene::ReverseAllCollision(){
	for(int i = 0; i < m_pPlayerSet->m_nBarCount; i++){
		if(m_apPlayer.at(i) == nullptr || i == m_pPlayerSet->m_nBarIndex) continue;
		m_apPlayer.at(i)->ReverseCollision();
	}
	PlaySoundMem(GetSoundsHandle(SOUND_SE_WHITE_BLOCK_COLLISION), DX_PLAYTYPE_BACK);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <returns>TRUE</returns>
void PracticeScene::DrawLoop(){
	if(m_pFlagSet->m_bFadeout) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	int nHandle = GetGraphicsHandle(IMAGE_PRACTICE_BACKGROUND);
	DrawGraph(0, 0, nHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawLoopBlocks();
	DrawLoopPlayers();

	//�t�F�[�h�A�E�g
	int nAlpha = m_pAnime->GetAnimationSmooth(m_pIndexSet->m_nFinishStageIndex, 0, 255);
	if(m_pFlagSet->m_bFadeout) nAlpha = 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	DrawGraph(0, 0, nHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�X�R�A�\��
	int& nScore = m_pStageSet->m_nGameScore;
	const int& nHiScore = m_pStageSet->m_nGameHiScore;
	DrawString(WindowMaxX - 80, 50, "Score", GetColor(0, 255, 255));
	DrawFormatString(WindowMaxX - 80, 80, GetColor(255, 255, 255), "%d", nScore);

	//�n�C�X�R�A�\��
	DrawString(WindowMaxX - 115, 140, "HighScore", GetColor(255, 255, 0));
	DrawFormatString(WindowMaxX - 80, 170, GetColor(255, 255, 255), "%d", (nScore < nHiScore ? nHiScore : nScore));

	if(!m_pAnime->IsFinishedAnimationCount(m_pIndexSet->m_nFinishStageIndex)) return;
	if(!m_pFlagSet->m_bStageClear && !m_pFlagSet->m_bGameOver) return;

	//����or���s
	if(m_pFlagSet->m_bStageClear){
		nHandle = GetGraphicsHandle(IMAGE_PRACTICE_GAME_CLEAR);
		DrawRotaGraph(WindowCenX, WindowCenY, 0.8, 0, nHandle, TRUE);
	}
	else if(m_pFlagSet->m_bGameOver){
		nHandle = GetGraphicsHandle(IMAGE_PRACTICE_GAME_OVER);
		DrawRotaGraph(WindowCenX, WindowCenY, 0.8, 0, nHandle, TRUE);
	}
	//����
	nHandle = GetGraphicsHandle(IMAGE_PRACTICE_GAME_RESTART);
	DrawRotaGraph(WindowCenX, WindowCenY + 50, 0.8, 0, nHandle, TRUE);

	nAlpha = (m_pFlagSet->m_bContinue ? 255 : 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	nHandle = GetGraphicsHandle(IMAGE_PRACTICE_SELECT_YES);
	DrawRotaGraph(WindowCenX - 50, WindowCenY + 100, 0.8, 0, nHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - nAlpha);
	nHandle = GetGraphicsHandle(IMAGE_PRACTICE_SELECT_NO);
	DrawRotaGraph(WindowCenX + 50, WindowCenY + 100, 0.8, 0, nHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

/// <summary>
/// �u���b�N�`�揈�������܂��B
/// </summary>
void PracticeScene::DrawLoopBlocks(){
	for(int i = 0; i < m_pBlockSet->m_nBlockCount; i++){
		if(m_apBlock.at(i) == nullptr) continue;
		m_apBlock.at(i)->DrawLoop();
	}
}

/// <summary>
/// �v���C���[�`�揈�������܂��B
/// </summary>
void PracticeScene::DrawLoopPlayers(){
	for(int i = 0; i < m_pPlayerSet->m_nBarCount; i++){
		if(m_apPlayer.at(i) == nullptr) continue;
		m_apPlayer.at(i)->DrawLoop();
	}
}

/// <summary>
/// �I������
/// </summary>
/// <returns>TRUE</returns>
void PracticeScene::Finalize(){
	FinalizeBlocks();
	FinalizePlayers();
	StopSoundMem(m_nSoundHandle);
	m_pAnime->RestartAllAnimation();
}

/// <summary>
/// �u���b�N�I�����������܂��B
/// </summary>
void PracticeScene::FinalizeBlocks(){
	for(int i = 0; i < m_pBlockSet->m_nBlockCount; i++){
		if(m_apBlock.at(i) == nullptr) continue;
		m_apBlock.at(i)->Finalize();
		DeletePtr(m_apBlock.at(i));
	}

	m_apBlock.clear();
	m_apBlock.shrink_to_fit();//���������
}

/// <summary>
/// �v���C���[�I�����������܂��B
/// </summary>
void PracticeScene::FinalizePlayers(){
	for(int i = 0; i < m_pPlayerSet->m_nBarCount; i++){
		if(m_apPlayer.at(i) == nullptr) continue;
		m_apPlayer.at(i)->Finalize();
		DeletePtr(m_apPlayer.at(i));
	}

	m_apPlayer.clear();
	m_apPlayer.shrink_to_fit();
}
