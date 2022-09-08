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
	void Reset();

	//�X�V����
	void Update(int mouseX_, int mouseY_, int mouse_, int& scene);

	//�`��
	void Draw();

	//HP�̃Q�b�^�[
	int HpGet() { return hp; }

private:
	//�G���
	int carGH;

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
	//�������Ɉړ�����Ԃ̏��
	float horizRX;
	float horizRY;
	//�ォ�炭��Ԃ̏��
	bool topIsDead[carNum];
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	//�c�����Ɉړ������
	float verticalRX;
	float verticalRY;

	//�Ԑ�
	int rightlane;
	int toplane;

	//�X�|�[���^�C�}�[
	//2�`6�b�Ń����_��
	const int spawnTime = 60 * (GetRand(4) + 2);
	int	rightSpawnTimer;
	int topSpawnTimer;

	//�M�����
	TrafficLight* trafficLight;

	//HP
	const int hpNum = 3;
	int hp;

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

	//�ʎԐ��̓����蔻��
	void CarCollision();
};

