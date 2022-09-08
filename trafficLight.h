#pragma once
#include "DxLib.h"
#include "screen.h"
#include "math.h"

class TrafficLight
{
public:
	TrafficLight();
	~TrafficLight();

	void Reset();

	void Update(int mouseX_, int mouseY_, int mouse_);

	void Draw();

	//�M�����̃Q�b�^�[
	float GetRightX() { return rightPosX; }
	bool GetRightStop() { return rightStop; }

	float GetTopY() { return topPosY; }
	bool GetTopStop() { return topStop; }
private:
	//�G���
	int trafficLightGH[2];

	//���
	//�E���炭��Ԃ̐M��
	bool rightStop;
	float rightPosX;
	float rightPosY;
	float horizRX;	//�������Ɉړ�����Ԃ̐M��
	float horizRY;

	//�ォ�炭��Ԃ̐M��
	bool topStop;
	float topPosX;
	float topPosY;
	float verticalRX;	//�c�����Ɉړ�����Ԃ̐M��
	float verticalRY;

	//�}�E�X���
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	//�M�����ς�鏈��
	void Change();
};

