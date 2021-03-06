#include "SceneMgr.h"

SceneMgr::SceneMgr() : m_eNextScene(SCENE_UNKNOWN), m_ePhase(PHASE_LOAD)
{
	m_pResource = new Resource();
	m_pScene = dynamic_cast<BaseScene*>(new LoadingScene(this, this));
}

SceneMgr::~SceneMgr()
{
	DeletePtr(m_pResource);
	DeletePtr(m_pScene);
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneMgr::Initialize(){
	m_pScene->BaseScene::Initialize();
	m_pScene->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void SceneMgr::Update(){
	if(m_eNextScene != SCENE_UNKNOWN){
		Finalize();
		DeletePtr(m_pScene);

		switch(m_eNextScene){
		case SCENE_LOAD:
			m_pScene = dynamic_cast<BaseScene*>(new LoadingScene(this, this));
			break;
		case SCENE_MENU:
			m_pScene = dynamic_cast<BaseScene*>(new MenuScene(this, this));
			break;
		case SCENE_PRACTICE:
			m_pScene = dynamic_cast<BaseScene*>(new PracticeScene(this, this));
			break;
		}
		m_eNextScene = SCENE_UNKNOWN;
		Initialize();
	}

	m_pScene->BaseScene::Update();
	m_pScene->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void SceneMgr::DrawLoop(){
	m_pScene->BaseScene::DrawLoop();
	m_pScene->DrawLoop();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneMgr::Finalize(){
	m_pScene->BaseScene::Finalize();
	m_pScene->Finalize();
}
