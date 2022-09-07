#pragma once
class TrafficLight
{
public:
	TrafficLight();
	~TrafficLight();

	void Update(int mouseX_, int mouseY_, int mouse_);

	void Draw();

	//�M�����̃Q�b�^�[
	float GetRightX() { return rightPosX; }
	bool GetRightStop() { return rightStop; }
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

	//�}�E�X���
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	//�M�����ς�鏈��
	void Change();
};

