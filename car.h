#pragma once
#include "trafficLight.h"

class Car
{
public:
	Car();
	~Car();

	//�X�V����
	void Update(int mouseX_, int mouseY_, int mouse_);

	//�`��
	void Draw();

private:
	//�G���
	int carGH;

	//���
	//��
	static const int carNum = 10;
	const float spdNum = 2.0f;
	float rightCarSpd[carNum];
	bool rightIsDead[carNum];	//�E���炭��Ԃ̏��
	bool isStop[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	bool leftIsDead[carNum];	//�����炭��Ԃ̏��
	float leftPosX[carNum];
	float leftPosY[carNum];
	float horizRX;	//�������Ɉړ�����Ԃ̏��
	float horizRY;

	//�X�|�[���^�C�}�[
	const int spawnTime = 60 * 5;
	int	spawnTimer;

	//�M�����
	TrafficLight* trafficLight;

	//�}�E�X���
	/*int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;*/

	//�ړ�����
	void Move();

	//��ʊO�ɍs�����������
	void Range();

	//�����Ԑ��̓����蔻��
	bool StopCollision();
};

