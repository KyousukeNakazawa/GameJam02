#pragma once
#include "trafficLight.h"
#include "DxLib.h"
#include "screen.h"
#include"math.h"

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
	bool rightIsDead[carNum];	//�E���炭��Ԃ̏��
	bool rightIsStop[carNum];
	float rightCarSpd[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	float horizRX;	//�������Ɉړ�����Ԃ̏��
	float horizRY;
	bool topIsDead[carNum];	//�ォ�炭��Ԃ̏��
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	float verticalRX;
	float verticalRY;

	//�X�|�[���^�C�}�[
	const int spawnTime = 60 * 5;
	int	rightSpawnTimer;
	int topSpawnTimer;

	//�M�����
	TrafficLight* trafficLight;

	//�}�E�X���
	/*int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;*/

	//�X�|�[������
	void Spawn();

	//�M���ł̒�~����
	void Stop();

	//�ړ�����
	void Move();

	//��ʊO�ɍs�����������
	void Range();

	//�����Ԑ��̓����蔻��
	bool RightCarStop(int i);

	bool TopCarStop(int i);
};

