#pragma once

enum Scene{
	SCENE_LOAD,
	SCENE_MENU,
	SCENE_PRACTICE,

	SCENE_UNKNOWN
};

enum Phase{
	PHASE_LOAD = -1,	//���[�h��
	PHASE_TITLE,		//���j���[�I��
	PHASE_LEVEL,		//���x���I��
	PHASE_RESULT,		//���U���g
	PHASE_CONFIG,		//�R���t�B�O�I��
	PHASE_MANUAL,		//�}�j���A��
	PHASE_CREDIT,		//�N���W�b�g
	PHASE_EXIT,			//�Q�[���I��
	PHASE_GAMEPLAY,	//�Q�[���J�n

	PHASE_COUNT
};

enum Level{
	LEVEL_BEGINNER,	//��Փx��
	LEVEL_STANDARD,	//��Փx��
	LEVEL_HARD,			//��Փx��

	LEVEL_COUNT
};

class ISceneManager
{
public:
	virtual ~ISceneManager() = 0;
	virtual void ChangeScene(Scene eScene) = 0;	//�w��V�[���ɕύX����
	virtual void SetPhase(Phase ePhase) = 0;	//�w��t�F�[�Y�ɕύX����
	virtual int GetPhase() = 0;
	virtual void SetLevel(Level eLevel) = 0;
	virtual int GetLevel() = 0;
};

