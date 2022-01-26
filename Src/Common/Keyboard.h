#pragma once
#include "../Task.h"

static const int m_nKeyType = 256;

class Keyboard : public Task
{
public:
	Keyboard(){}
	~Keyboard(){}

	void Initialize(){}
	void Update() override;
	void DrawLoop(){}
	void Finalize(){}

	int IsKeyPush(int nKey);
	int IsKeyPull(int nKey);
	int IsKeyPushHold(int nKey);
	int IsKeyPullHold(int nKey);
	int IsKeyFixedPush(int nKey, int nFixedCount);
private:
	char m_asKey[m_nKeyType];
	int m_anPushKeyCount[m_nKeyType];
	int m_anPullKeyCount[m_nKeyType];
};

