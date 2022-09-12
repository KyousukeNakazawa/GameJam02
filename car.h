#pragma once
#include <stdlib.h>
#include "trafficLight.h"
#include "DxLib.h"
#include "screen.h"
#include"math.h"

class Car
{
public:
	Car();
	~Car();

	//���Z�b�g����
	void Reset(int stage);

	//�X�V����
	void Update(int mouseX_, int mouseY_, int mouse_, int& scene);

	//�`��
	void Draw();

	//�Q�b�^�[
	//HP
	int HpGet() { return hp; }

	//�^�C�}�[
	int TimerGet() { return gameTimer; }

private:
	//�G���
	int carGH[6];

	//�T�E���h���
	//�Ԃ̏Փ�SE
	int carCrashSE;

	//���
	//��
	static const int carNum = 20;
	const float spdNum = 2.0f;
	//�E���炭��Ԃ̏��
	bool rightIsDead[carNum];
	bool rightIsStop[carNum];
	float rightCarSpd[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	int rightGH[carNum];

	//������Ԃ̏��
	bool leftIsDead[carNum];
	bool leftIsStop[carNum];
	float leftCarSpd[carNum];
	float leftPosX[carNum];
	float leftPosY[carNum];
	int leftGH[carNum];

	//�������Ɉړ�����Ԃ̏��
	float horizRX;
	float horizRY;

	//�ォ�炭��Ԃ̏��
	bool topIsDead[carNum];
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	int topGH[carNum];

	//������Ԃ̏��
	bool bottomIsDead[carNum];
	bool bottomIsStop[carNum];
	float bottomCarSpd[carNum];
	float bottomPosX[carNum];
	float bottomPosY[carNum];
	int bottomGH[carNum];

	//�c�����Ɉړ������
	float verticalRX;
	float verticalRY;

	//�Ԑ����
	int rightlane;
	int toplane;
	int bottomlane;

	//�M�����
	TrafficLight* trafficLight;

	//�X�|�[���^�C�}�[
	//2�`6�b�Ń����_��
	const int spawnTime = 60 * (GetRand(4) + 2);
	int	rightSpawnTimer;
	int topSpawnTimer;
	int leftSpawnTimer;
	int bottomSpawnTimer;

	//�Q�[���^�C�}�[
	const int gameTime = 60 * 60;
	int gameTimer;

	//HP
	const int hpNum = 3;
	int hp;

	int scene;

	//�֐�
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

	bool LeftCarStop(int i);

	bool BottomCarStop(int i);

	//�ʎԐ��̓����蔻��
	void CarCollision();

	void Collision(const float posX1[], const float posY1[], const float posX2[], const float posY2[], bool isDead1[], bool isDead2[]);
};

