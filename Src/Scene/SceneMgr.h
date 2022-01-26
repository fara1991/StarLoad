#pragma once
#include "ISceneManager.h"
#include "BaseScene.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "PracticeScene.h"
#include "../Common/IResourceManager.h"
#include "../Common/Resource.h"

class SceneMgr : public ISceneManager, IResourceManager, Task
{
private:
	//�V�[���Ǘ��ϐ�
	Resource* m_pResource;
	BaseScene* m_pScene;

	Scene m_eNextScene;
	Phase m_ePhase;
	Level m_eLevel;
public:
	SceneMgr();
	~SceneMgr();

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;

	void ChangeScene(Scene eScene)	override { m_eNextScene = eScene; }
	void SetPhase(Phase ePhase)		override { m_ePhase = ePhase; }
	int GetPhase()							override { return m_ePhase; }
	void SetLevel(Level eLevel)		override { m_eLevel = eLevel; }
	int GetLevel()							override { return m_eLevel; }

	int GetGraphicsHandle(ResourceImage eImage)	{ return m_pResource->GetGraphicsHandle(eImage); }
	int GetSoundsHandle(ResourceSound eSound)		{ return m_pResource->GetSoundsHandle(eSound); }
	int GetGraphicsLoadingCount()						{ return m_pResource->GetGraphicsLoadingCount(); }
	int GetSoundsLoadingCount()						{ return m_pResource->GetSoundsLoadingCount(); }
	int IsLoadGraphics()									{ return m_pResource->IsLoadGraphics(); }
	int IsLoadSounds()									{ return m_pResource->IsLoadSounds(); }
	void SetSoundsBGMVolume(int nPercent)			{ m_pResource->SetSoundsBGMVolume(nPercent); }
	void SetSoundsSEVolume(int nPercent)			{ m_pResource->SetSoundsSEVolume(nPercent); }
	void AllSoundsStopBGMVolume()						{ m_pResource->AllSoundsStopBGMVolume(); }
	void AllSoundsStopSEVolume()						{ m_pResource->AllSoundsStopSEVolume(); }
};
