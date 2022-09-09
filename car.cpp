#include "car.h"


Car::Car() {
	trafficLight = new TrafficLight;
	LoadDivGraph("Resource/carGH.png", 6, 3, 2, 32, 64, carGH);

	hp = hpNum;
	gameTimer = gameTime;

	horizRX = 32;
	horizRY = 16;
	verticalRX = 16;
	verticalRY = 32;

	rightSpawnTimer = 60 * (GetRand(15) % 3 + 2);
	topSpawnTimer = 60 * (GetRand(10) % 3 + 2);
	leftSpawnTimer = 60 * (GetRand(25) % 3 + 2);
	bottomSpawnTimer = 60 * (GetRand(20) % 3 + 2);

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

		leftIsDead[i] = true;
		leftIsStop[i] = false;
		leftPosX[i] = -50;
		leftPosY[i] = -50;
		leftCarSpd[i] = spdNum;

		bottomIsDead[i] = true;
		bottomIsStop[i] = false;
		bottomPosX[i] = -50;
		bottomPosY[i] = -50;
		bottomCarSpd[i] = spdNum;
	}
}

Car::~Car() {
	if (trafficLight != nullptr) delete trafficLight;
}

void Car::Reset(int stage) {
	trafficLight->Reset(stage);
	hp = hpNum;
	gameTimer = gameTime;

	rightSpawnTimer = 60 * (GetRand(15) % 3 + 2);
	topSpawnTimer = 60 * (GetRand(10) % 3 + 2);
	leftSpawnTimer = 60 * (GetRand(25) % 3 + 2);
	bottomSpawnTimer = 60 * (GetRand(20) % 3 + 2);

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

		leftIsDead[i] = true;
		leftIsStop[i] = false;
		leftPosX[i] = -50;
		leftPosY[i] = -50;
		leftCarSpd[i] = spdNum;

		bottomIsDead[i] = true;
		bottomIsStop[i] = false;
		bottomPosX[i] = -50;
		bottomPosY[i] = -50;
		bottomCarSpd[i] = spdNum;
	}
}

void Car::Update(int mouseX_, int mouseY_, int mouse_, int& scene_) {
	scene = scene_;
	//�X�|�[������
	Spawn();

	//�M������
	trafficLight->Update(mouseX_, mouseY_, mouse_, scene);

	//�ԂȂ��~����
	Stop();

	//�ړ�����
	Move();

	//�͈͏���
	Range();

	//�Ԃ̏Փ˔���
	CarCollision();

	//�Q�[���I�[�o�[����
	if (hp <= 0) scene_ = END;
	if (--gameTimer <= 0) scene_ = END;
}

void Car::Draw() {
	//��
	for (int i = 0; i < carNum; i++) {
		//�E���炭���
		if (!rightIsDead[i]) {
			DrawRotaGraph(rightPosX[i], rightPosY[i], 1.0, Radian(-90), rightGH[i], true, false);
		}
		//�����炭���
		if (!leftIsDead[i]) {
			DrawRotaGraph(leftPosX[i], leftPosY[i], 1.0, Radian(90), leftGH[i], true, true);
		}
		//�ォ�炭���
		if (!topIsDead[i]) {
			DrawRotaGraph(topPosX[i], topPosY[i], 1.0, Radian(180), topGH[i], true, false);
		}
		//�����炭���
		if (!bottomIsDead[i]) {
			DrawRotaGraph(bottomPosX[i], bottomPosY[i], 1.0, Radian(0), bottomGH[i], true, true);
		}
	}

	//�M��
	trafficLight->Draw();

	DrawFormatString(0, 0, 0x00ffff, "%d", rightSpawnTimer);
	DrawFormatString(0, 15, 0x00ffff, "%d", topSpawnTimer);
}

void Car::Spawn() {
	//�E���炭���
	if (--rightSpawnTimer < 0) {
		rightlane = GetRand(38) % 2;
		//�J�E���g��0�ɂȂ�����t���O�������Ă���̂�T������
		for (int i = 0; i < carNum; i++) {
			if (rightIsDead[i]) {
				rightPosX[i] = WIN_WIDTH + horizRX;
				//�X�e�[�W1�ł̃X�|�[���ʒu
				if (scene == STAGE1) {
					if (rightlane == 0) rightPosY[i] = WIN_HEIGHT / 2 + 40;
					else rightPosY[i] = WIN_HEIGHT / 2 - 40;
				}
				//�X�e�[�W2�ł̃X�|�[���ʒu
				else if (scene == STAGE2) {
					rightPosY[i] = WIN_HEIGHT / 2 + 40;
				}
				rightIsDead[i] = false;
				//�`�悷��ԗ��������_���Ō���
				rightGH[i] = carGH[GetRand(5)];
				break;
			}
		}
		rightSpawnTimer = 60 * (GetRand(50) % 5 + 1);
	}

	//�ォ�炭���
	if (--topSpawnTimer < 0) {
		toplane = GetRand(53) % 2;
		//�J�E���g��0�ɂȂ�����t���O�������Ă���̂�T������
		for (int i = 0; i < carNum; i++) {
			if (topIsDead[i]) {
				//�X�e�[�W1�ł̃X�|�[���ʒu
				if (scene == STAGE1) {
					if (toplane == 0) topPosX[i] = WIN_WIDTH / 2 + 40;
					else topPosX[i] = WIN_WIDTH / 2 - 40;
				}
				//�X�e�[�W2�ł̃X�|�[���ʒu
				else if (scene == STAGE2) {
					if (toplane == 0) topPosX[i] = WIN_WIDTH / 2.5 * 2 - 25;
					else topPosX[i] = WIN_WIDTH / 2.5 * 2 - 105;
				}
				topPosY[i] = -verticalRY;
				topIsDead[i] = false;
				//�`�悷��ԗ��������_���Ō���
				topGH[i] = carGH[GetRand(5)];
				break;
			}
		}
		topSpawnTimer = 60 * (GetRand(35) % 5 + 2);
	}

	if (scene == STAGE2) {
		//�����炭���
		if (--leftSpawnTimer < 0) {
			//�J�E���g��0�ɂȂ�����t���O�������Ă���̂�T������
			for (int i = 0; i < carNum; i++) {
				if (leftIsDead[i]) {
					leftPosX[i] = -horizRX;
					leftPosY[i] = WIN_HEIGHT / 2 - 40;
					leftIsDead[i] = false;
					//�`�悷��ԗ��������_���Ō���
					leftGH[i] = carGH[GetRand(5)];
					break;
				}
			}
			leftSpawnTimer = 60 * (GetRand(43) % 5 + 2);
		}

		//�����炭���
		if (--bottomSpawnTimer < 0) {
			bottomlane = GetRand(46) % 2;
			//�J�E���g��0�ɂȂ�����t���O�������Ă���̂�T������
			for (int i = 0; i < carNum; i++) {
				if (bottomIsDead[i]) {
					if (bottomlane == 0) bottomPosX[i] = WIN_WIDTH / 3 - 60;
					else bottomPosX[i] = WIN_WIDTH / 3 - 140;
					bottomPosY[i] = WIN_HEIGHT + verticalRY;
					bottomIsDead[i] = false;
					//�`�悷��ԗ��������_���Ō���
					bottomGH[i] = carGH[GetRand(5)];
					break;
				}
			}
			bottomSpawnTimer = 60 * (GetRand(35) % 5 + 2);
		}
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
		else if (rightPosX[i] >= trafficLight->GetRightX() + 14 && rightPosX[i] <= trafficLight->GetRightX() + 30
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
		else if (trafficLight->GetTopStop() && TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		//�M�����ԂőO�ɎԂ����Ȃ��ꍇ
		else if (topPosY[i] <= trafficLight->GetTopY() - 14 && topPosY[i] >= trafficLight->GetTopY() - 30
			&& trafficLight->GetTopStop() && !TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		else {
			topCarSpd[i] = spdNum;
		}

		if (scene == STAGE2) {
			//�����炭��Ԃ̐M��
			//�M�����̏ꍇ
			if (!trafficLight->GetLeftStop()) {
				leftCarSpd[i] = spdNum;
			}
			//�M�����ԂőO�ɎԂ����邪�ʂ�߂��Ă���ꍇ
			else if (leftPosX[i] > trafficLight->GetLeftX() - 14 && trafficLight->GetLeftStop()
				&& LeftCarStop(i)) {
				leftCarSpd[i] = spdNum;
			}
			//�M�����ԂőO�ɎԂ�����ꍇ
			else if (trafficLight->GetLeftStop() && LeftCarStop(i)) {
				leftCarSpd[i] = 0;
			}
			//�M�����ԂőO�ɎԂ����Ȃ��ꍇ
			else if (leftPosX[i] <= trafficLight->GetLeftX() - 14 && leftPosX[i] >= trafficLight->GetLeftX() - 30
				&& trafficLight->GetLeftStop() && !LeftCarStop(i)) {
				leftCarSpd[i] = 0;
			}
			else {
				leftCarSpd[i] = spdNum;
			}

			//�����炭��Ԃ̐M��
			//�M�����̏ꍇ
			if (!trafficLight->GetBottomStop()) {
				bottomCarSpd[i] = spdNum;
			}
			//�M�����ԂőO�ɎԂ����邪�ʂ�߂��Ă���ꍇ
			else if (bottomPosY[i] < trafficLight->GetBottomY() + 14 && trafficLight->GetBottomStop()
				&& BottomCarStop(i)) {
				bottomCarSpd[i] = spdNum;
			}
			//�M�����ԂőO�ɎԂ�����ꍇ
			else if (trafficLight->GetBottomStop() && BottomCarStop(i)) {
				bottomCarSpd[i] = 0;
			}
			//�M�����ԂőO�ɎԂ����Ȃ��ꍇ
			else if (bottomPosY[i] >= trafficLight->GetBottomY() + 14 && bottomPosY[i] <= trafficLight->GetBottomY() + 30
				&& trafficLight->GetBottomStop() && !BottomCarStop(i)) {
				bottomCarSpd[i] = 0;
			}
			else {
				bottomCarSpd[i] = spdNum;
			}
		}
	}
}

void Car::Move() {
	//
	for (int i = 0; i < carNum; i++) {
		//�E���炭���
		if (!rightIsDead[i]) {
			rightPosX[i] -= rightCarSpd[i];
		}
		//�ォ�炭���
		if (!topIsDead[i]) {
			topPosY[i] += topCarSpd[i];
		}

		if (scene == STAGE2) {
			//�����炭���
			if (!leftIsDead[i]) {
				leftPosX[i] += leftCarSpd[i];
			}
			//�����炭���
			if (!bottomIsDead[i]) {
				bottomPosY[i] -= bottomCarSpd[i];
			}
		}
	}
}

void Car::Range() {
	for (int i = 0; i < carNum; i++) {
		//�E���炭���
		if (!rightIsDead[i] && rightPosX[i] < -horizRX) {
			rightIsDead[i] = true;
		}
		//�ォ�炭���
		if (!topIsDead[i] && topPosY[i] > WIN_HEIGHT + verticalRY) {
			topIsDead[i] = true;
		}

		if (scene == STAGE2) {
			//�����炭���
			if (!leftIsDead[i] && leftPosX[i] > WIN_WIDTH + verticalRX) {
				leftIsDead[i] = true;
			}
			//�����炭���
			if (!bottomIsDead[i] && bottomPosY[i] < -verticalRY) {
				bottomIsDead[i] = true;
			}
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

bool Car::LeftCarStop(int i) {
	//�f�X�t���O�������Ă��Ȃ��ꍇ�����蔻������
	if (!leftIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!leftIsDead[j]) {
				//���S�_�̋��������
				float distanceX = leftPosX[i] - leftPosX[j];
				float distanceY = leftPosY[i] - leftPosY[j];
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

bool Car::BottomCarStop(int i) {
	//�f�X�t���O�������Ă��Ȃ��ꍇ�����蔻������
	if (!bottomIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!bottomIsDead[j]) {
				//���S�_�̋��������
				float distanceX = bottomPosX[i] - bottomPosX[j];
				float distanceY = bottomPosY[i] - bottomPosY[j];
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

void Car::CarCollision() {

	//���ׂĂ̎Ԃ̓����蔻��
	//�E�Ə�
	Collision(rightPosX, rightPosY, topPosX, topPosY, rightIsDead, topIsDead);

	if (scene == STAGE2) {
		//�E�Ɖ�
		Collision(rightPosX, rightPosY, bottomPosX, bottomPosY, rightIsDead, bottomIsDead);

		//���Ə�
		Collision(leftPosX, leftPosY, topPosX, topPosY, leftIsDead, topIsDead);

		//���Ɖ�
		Collision(leftPosX, leftPosY, bottomPosX, bottomPosY, leftIsDead, bottomIsDead);
	}
	
}

void Car::Collision(const float posX1[], const float posY1[], const float posX2[], const float posY2[], bool isDead1[], bool isDead2[]) {
	//�f�X�t���O�������Ă��Ȃ��ꍇ�����蔻������
	for (int i = 0; i < carNum; i++) {
		if (!isDead1[i]) {
			for (int j = 0; j < carNum; j++) {
				if (!isDead2[j]) {
					//���S�_�̋��������
					float distanceX = posX1[i] - posX2[j];
					float distanceY = posY1[i] - posY2[j];
					//��Βl�Ƃ���
					if (distanceX < 0.0f) distanceX *= -1.0f;
					if (distanceY < 0.0f) distanceY *= -1.0f;
					//�Q�̒Z�`�T�C�Y�����
					float sizeX = horizRX + verticalRX;
					float sizeY = horizRY + verticalRY;
					//�������Ă�����HP��1����Ԃ�����������
					if (distanceX < sizeX && distanceY < sizeY) {
						isDead1[i] = true;
						isDead2[j] = true;
						hp--;
					}
				}
			}
		}
	}
}