#include "car.h"


Car::Car() {
	trafficLight = new TrafficLight;
	carGH = LoadGraph("Resource/car1GH.png");

	horizRX = 32;
	horizRY = 16;
	verticalRX = 16;
	verticalRY = 32;
	rightSpawnTimer = spawnTime;
	topSpawnTimer = spawnTime;
	for (int i = 0; i < carNum; i++) {
		rightIsDead[i] = true;
		rightIsStop[i] = false;
		rightPosX[i] = -50;
		rightPosY[i] = -50;
		rightCarSpd[i] = spdNum;
		topIsDead[i] = true;
		topIsStop[i] = false;
		topPosX[i] = -50;
		topPosY[i] = -50;
		topCarSpd[i] = spdNum;
	}
}

Car::~Car() {
	if (trafficLight != nullptr) delete trafficLight;
}

void Car::Update(int mouseX_, int mouseY_, int mouse_) {

	//�X�|�[������
	Spawn();

	//�M������
	trafficLight->Update(mouseX_, mouseY_, mouse_);

	//�ԂȂ��~����
	Stop();

	//�ړ�����
	Move();

	//�͈͏���
	Range();
}

void Car::Draw() {
	//��
	for (int i = 0; i < carNum; i++) {
		//�E���炭���
		if (!rightIsDead[i]) {
			DrawRotaGraph(rightPosX[i], rightPosY[i], 1.0, Radian(-90), carGH, true, false);
		}
		//�ォ�炭���
		if (!topIsDead[i]) {
			DrawRotaGraph(topPosX[i], topPosY[i], 1.0, Radian(180), carGH, true, false);
		}
	}

	//�M��
	trafficLight->Draw();

	DrawFormatString(0, 0, 0x00ffff, "%lf", trafficLight->GetRightX() + 26);
	DrawFormatString(0, 15, 0x00ffff, "%lf", rightPosX[0]);
}

void Car::Spawn() {
	if (--rightSpawnTimer < 0) {
		//�J�E���g��0�ɂȂ�����t���O�������Ă���̂�T������
		//�E���炭���
		for (int i = 0; i < carNum; i++) {
			if (rightIsDead[i]) {
				rightPosX[i] = WIN_WIDTH + horizRX;
				rightPosY[i] = WIN_HEIGHT / 2 + 40;
				rightIsDead[i] = false;
				break;
			}
		}

		//�ォ�炭���
		for (int i = 0; i < carNum; i++) {
			if (topIsDead[i]) {
				topPosX[i] = WIN_WIDTH / 2 + 40;
				topPosY[i] = -verticalRY;
				topIsDead[i] = false;
				break;
			}
		}
		rightSpawnTimer = spawnTime;
	}
}

void Car::Stop() {
	for (int i = 0; i < carNum; i++) {
		//�E���炭��Ԃ̐M��
		//�M�����̏ꍇ
		if (!trafficLight->GetRightStop()) {
			rightCarSpd[i] = spdNum;
		}
		//�M�����ԂőO�ɎԂ����邪�ʂ�߂��Ă���ꍇ
		else if (rightPosX[i] < trafficLight->GetRightX() + 14 && trafficLight->GetRightStop()
			&& RightCarStop(i)) {
			rightCarSpd[i] = spdNum;
		}
		//�M�����ԂőO�ɎԂ�����ꍇ
		else if (trafficLight->GetRightStop() && RightCarStop(i)) {
			rightCarSpd[i] = 0;
		}
		//�M�����ԂőO�ɎԂ����Ȃ��ꍇ
		else if (rightPosX[i] >= trafficLight->GetRightX() + 14 && rightPosX[i] <= trafficLight->GetRightX() + 28
			&& trafficLight->GetRightStop() && !RightCarStop(i)) {
			rightCarSpd[i] = 0;
		}
		else {
			rightCarSpd[i] = spdNum;
		}

		//�ォ�炭��Ԃ̐M��
		//�M�����̏ꍇ
		if (!trafficLight->GetTopStop()) {
			topCarSpd[i] = spdNum;
		}
		//�M�����ԂőO�ɎԂ����邪�ʂ�߂��Ă���ꍇ
		else if (topPosY[i] > trafficLight->GetTopY() - 14 && trafficLight->GetTopStop()
			&& TopCarStop(i)) {
			topCarSpd[i] = spdNum;
		}
		//�M�����ԂőO�ɎԂ�����ꍇ
		else if (trafficLight->GetRightStop() && TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		//�M�����ԂőO�ɎԂ����Ȃ��ꍇ
		else if (topPosY[i] <= trafficLight->GetTopY() - 14 && topPosY[i] >= trafficLight->GetTopY() - 28
			&& trafficLight->GetTopStop() && !TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		else {
			topCarSpd[i] = spdNum;
		}
	}
}

void Car::Move() {
	//
	for (int i = 0; i < carNum; i++) {
		if (!rightIsDead[i]) {
			rightPosX[i] -= rightCarSpd[i];
		}

		if (!topIsDead[i]) {
			topPosY[i] += topCarSpd[i];
		}
	}
}

void Car::Range() {
	for (int i = 0; i < carNum; i++) {
		if (!rightIsDead[i] && rightPosX[i] < -horizRX) {
			rightIsDead[i] = true;
		}
		if (!topIsDead[i] && topPosY[i] > WIN_HEIGHT + verticalRY) {
			topIsDead[i] = true;
		}
	}
}

bool Car::RightCarStop(int i) {
	//�f�X�t���O�������Ă��Ȃ��ꍇ�����蔻������
	if (!rightIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!rightIsDead[j]) {
				//���S�_�̋��������
				float distanceX = rightPosX[i] - rightPosX[j];
				float distanceY = rightPosY[i] - rightPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//��Βl�Ƃ���
				if (distanceX < 0.0f) distanceX *= -1.0f;
				if (distanceY < 0.0f) distanceY *= -1.0f;

				if (distanceX < horizRX * 2 + 10 && distanceY < horizRY * 2) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Car::TopCarStop(int i) {
	//�f�X�t���O�������Ă��Ȃ��ꍇ�����蔻������
	if (!topIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!topIsDead[j]) {
				//���S�_�̋��������
				float distanceX = topPosX[i] - topPosX[j];
				float distanceY = topPosY[i] - topPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//��Βl�Ƃ���
				if (distanceX < 0.0f) distanceX *= -1.0f;
				if (distanceY < 0.0f) distanceY *= -1.0f;

				if (distanceX < verticalRX * 2 && distanceY < verticalRY * 2 + 10) {
					return true;
				}
			}
		}
	}

	return false;
}