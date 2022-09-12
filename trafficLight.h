#pragma once
#include "DxLib.h"
#include "screen.h"
#include "math.h"

class TrafficLight
{
public:
	TrafficLight();
	~TrafficLight();

	void Reset(int stage_);

	void Update(int mouseX_, int mouseY_, int mouse_, int scene);

	void Draw();

	//�M�����̃Q�b�^�[
	float GetRightX() { return rightPosX; }
	bool GetRightStop() { return rightStop; }

	float GetTopY() { return topPosY; }
	bool GetTopStop() { return topStop; }

	float GetLeftX() { return leftPosX; }
	bool GetLeftStop() { return leftStop; }

	float GetBottomY() { return bottomPosY; }
	bool GetBottomStop() { return bottomStop; }
private:
	//�G���
	int trafficLightGH[2];

	//�T�E���h���
	//�M�����N���b�N�����Ƃ��̉�
	int changeSE;

	//���
	//�E���炭��Ԃ̐M��
	bool rightStop;
	float rightPosX;
	float rightPosY;

	//������Ԃ̐M��
	bool leftStop;
	float leftPosX;
	float leftPosY;

	//�������Ɉړ�����Ԃ̐M��
	float horizRX;
	float horizRY;

	//�ォ�炭��Ԃ̐M��
	bool topStop;
	float topPosX;
	float topPosY;

	//������Ԃ̐M��
	bool bottomStop;
	float bottomPosX;
	float bottomPosY;

	//�c�����Ɉړ�����Ԃ̐M��
	float verticalRX;
	float verticalRY;

	//�}�E�X���
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	int scene;

	//�M�����ς�鏈��
	void Change();
};

