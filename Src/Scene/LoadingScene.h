#pragma once
#include "BaseScene.h"

//���C�������N���X
class LoadingScene : public BaseScene{
public:
	//�R���X�g���N�^
	LoadingScene(ISceneManager* changer, IResourceManager* pResource);
	virtual ~LoadingScene(){}

	void Update() override;
	void DrawLoop() override;

private:
	int m_nLoadCount = 0;
	int m_nWaitCount = 0;
	const int m_nWaitMaxCount = 60;
	const int m_nResourceCount = static_cast<int>(IMAGE_COUNT) + static_cast<int>(SOUND_COUNT);
	int m_bFinishScene = FALSE;

	void DrawDescription();
	void DrawLoadGauge();
};

