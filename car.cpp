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
	//スポーン処理
	Spawn();

	//信号処理
	trafficLight->Update(mouseX_, mouseY_, mouse_, scene);

	//赤なら停止する
	Stop();

	//移動処理
	Move();

	//範囲処理
	Range();

	//車の衝突判定
	CarCollision();

	//ゲームオーバー処理
	if (hp <= 0) scene_ = END;
	if (--gameTimer <= 0) scene_ = END;
}

void Car::Draw() {
	//車
	for (int i = 0; i < carNum; i++) {
		//右からくる車
		if (!rightIsDead[i]) {
			DrawRotaGraph(rightPosX[i], rightPosY[i], 1.0, Radian(-90), rightGH[i], true, false);
		}
		//左からくる車
		if (!leftIsDead[i]) {
			DrawRotaGraph(leftPosX[i], leftPosY[i], 1.0, Radian(90), leftGH[i], true, true);
		}
		//上からくる車
		if (!topIsDead[i]) {
			DrawRotaGraph(topPosX[i], topPosY[i], 1.0, Radian(180), topGH[i], true, false);
		}
		//下からくる車
		if (!bottomIsDead[i]) {
			DrawRotaGraph(bottomPosX[i], bottomPosY[i], 1.0, Radian(0), bottomGH[i], true, true);
		}
	}

	//信号
	trafficLight->Draw();

	DrawFormatString(0, 0, 0x00ffff, "%d", rightSpawnTimer);
	DrawFormatString(0, 15, 0x00ffff, "%d", topSpawnTimer);
}

void Car::Spawn() {
	//右からくる車
	if (--rightSpawnTimer < 0) {
		rightlane = GetRand(38) % 2;
		//カウントが0になったらフラグが立ってるものを探し生成
		for (int i = 0; i < carNum; i++) {
			if (rightIsDead[i]) {
				rightPosX[i] = WIN_WIDTH + horizRX;
				//ステージ1でのスポーン位置
				if (scene == STAGE1) {
					if (rightlane == 0) rightPosY[i] = WIN_HEIGHT / 2 + 40;
					else rightPosY[i] = WIN_HEIGHT / 2 - 40;
				}
				//ステージ2でのスポーン位置
				else if (scene == STAGE2) {
					rightPosY[i] = WIN_HEIGHT / 2 + 40;
				}
				rightIsDead[i] = false;
				//描画する車両をランダムで決定
				rightGH[i] = carGH[GetRand(5)];
				break;
			}
		}
		rightSpawnTimer = 60 * (GetRand(50) % 5 + 1);
	}

	//上からくる車
	if (--topSpawnTimer < 0) {
		toplane = GetRand(53) % 2;
		//カウントが0になったらフラグが立ってるものを探し生成
		for (int i = 0; i < carNum; i++) {
			if (topIsDead[i]) {
				//ステージ1でのスポーン位置
				if (scene == STAGE1) {
					if (toplane == 0) topPosX[i] = WIN_WIDTH / 2 + 40;
					else topPosX[i] = WIN_WIDTH / 2 - 40;
				}
				//ステージ2でのスポーン位置
				else if (scene == STAGE2) {
					if (toplane == 0) topPosX[i] = WIN_WIDTH / 2.5 * 2 - 25;
					else topPosX[i] = WIN_WIDTH / 2.5 * 2 - 105;
				}
				topPosY[i] = -verticalRY;
				topIsDead[i] = false;
				//描画する車両をランダムで決定
				topGH[i] = carGH[GetRand(5)];
				break;
			}
		}
		topSpawnTimer = 60 * (GetRand(35) % 5 + 2);
	}

	if (scene == STAGE2) {
		//左からくる車
		if (--leftSpawnTimer < 0) {
			//カウントが0になったらフラグが立ってるものを探し生成
			for (int i = 0; i < carNum; i++) {
				if (leftIsDead[i]) {
					leftPosX[i] = -horizRX;
					leftPosY[i] = WIN_HEIGHT / 2 - 40;
					leftIsDead[i] = false;
					//描画する車両をランダムで決定
					leftGH[i] = carGH[GetRand(5)];
					break;
				}
			}
			leftSpawnTimer = 60 * (GetRand(43) % 5 + 2);
		}

		//下からくる車
		if (--bottomSpawnTimer < 0) {
			bottomlane = GetRand(46) % 2;
			//カウントが0になったらフラグが立ってるものを探し生成
			for (int i = 0; i < carNum; i++) {
				if (bottomIsDead[i]) {
					if (bottomlane == 0) bottomPosX[i] = WIN_WIDTH / 3 - 60;
					else bottomPosX[i] = WIN_WIDTH / 3 - 140;
					bottomPosY[i] = WIN_HEIGHT + verticalRY;
					bottomIsDead[i] = false;
					//描画する車両をランダムで決定
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
		//右からくる車の信号
		//信号が青の場合
		if (!trafficLight->GetRightStop()) {
			rightCarSpd[i] = spdNum;
		}
		//信号が赤で前に車がいるが通り過ぎている場合
		else if (rightPosX[i] < trafficLight->GetRightX() + 14 && trafficLight->GetRightStop()
			&& RightCarStop(i)) {
			rightCarSpd[i] = spdNum;
		}
		//信号が赤で前に車がいる場合
		else if (trafficLight->GetRightStop() && RightCarStop(i)) {
			rightCarSpd[i] = 0;
		}
		//信号が赤で前に車がいない場合
		else if (rightPosX[i] >= trafficLight->GetRightX() + 14 && rightPosX[i] <= trafficLight->GetRightX() + 30
			&& trafficLight->GetRightStop() && !RightCarStop(i)) {
			rightCarSpd[i] = 0;
		}
		else {
			rightCarSpd[i] = spdNum;
		}

		//上からくる車の信号
		//信号が青の場合
		if (!trafficLight->GetTopStop()) {
			topCarSpd[i] = spdNum;
		}
		//信号が赤で前に車がいるが通り過ぎている場合
		else if (topPosY[i] > trafficLight->GetTopY() - 14 && trafficLight->GetTopStop()
			&& TopCarStop(i)) {
			topCarSpd[i] = spdNum;
		}
		//信号が赤で前に車がいる場合
		else if (trafficLight->GetTopStop() && TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		//信号が赤で前に車がいない場合
		else if (topPosY[i] <= trafficLight->GetTopY() - 14 && topPosY[i] >= trafficLight->GetTopY() - 30
			&& trafficLight->GetTopStop() && !TopCarStop(i)) {
			topCarSpd[i] = 0;
		}
		else {
			topCarSpd[i] = spdNum;
		}

		if (scene == STAGE2) {
			//左からくる車の信号
			//信号が青の場合
			if (!trafficLight->GetLeftStop()) {
				leftCarSpd[i] = spdNum;
			}
			//信号が赤で前に車がいるが通り過ぎている場合
			else if (leftPosX[i] > trafficLight->GetLeftX() - 14 && trafficLight->GetLeftStop()
				&& LeftCarStop(i)) {
				leftCarSpd[i] = spdNum;
			}
			//信号が赤で前に車がいる場合
			else if (trafficLight->GetLeftStop() && LeftCarStop(i)) {
				leftCarSpd[i] = 0;
			}
			//信号が赤で前に車がいない場合
			else if (leftPosX[i] <= trafficLight->GetLeftX() - 14 && leftPosX[i] >= trafficLight->GetLeftX() - 30
				&& trafficLight->GetLeftStop() && !LeftCarStop(i)) {
				leftCarSpd[i] = 0;
			}
			else {
				leftCarSpd[i] = spdNum;
			}

			//下からくる車の信号
			//信号が青の場合
			if (!trafficLight->GetBottomStop()) {
				bottomCarSpd[i] = spdNum;
			}
			//信号が赤で前に車がいるが通り過ぎている場合
			else if (bottomPosY[i] < trafficLight->GetBottomY() + 14 && trafficLight->GetBottomStop()
				&& BottomCarStop(i)) {
				bottomCarSpd[i] = spdNum;
			}
			//信号が赤で前に車がいる場合
			else if (trafficLight->GetBottomStop() && BottomCarStop(i)) {
				bottomCarSpd[i] = 0;
			}
			//信号が赤で前に車がいない場合
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
		//右からくる車
		if (!rightIsDead[i]) {
			rightPosX[i] -= rightCarSpd[i];
		}
		//上からくる車
		if (!topIsDead[i]) {
			topPosY[i] += topCarSpd[i];
		}

		if (scene == STAGE2) {
			//左からくる車
			if (!leftIsDead[i]) {
				leftPosX[i] += leftCarSpd[i];
			}
			//下からくる車
			if (!bottomIsDead[i]) {
				bottomPosY[i] -= bottomCarSpd[i];
			}
		}
	}
}

void Car::Range() {
	for (int i = 0; i < carNum; i++) {
		//右からくる車
		if (!rightIsDead[i] && rightPosX[i] < -horizRX) {
			rightIsDead[i] = true;
		}
		//上からくる車
		if (!topIsDead[i] && topPosY[i] > WIN_HEIGHT + verticalRY) {
			topIsDead[i] = true;
		}

		if (scene == STAGE2) {
			//左からくる車
			if (!leftIsDead[i] && leftPosX[i] > WIN_WIDTH + verticalRX) {
				leftIsDead[i] = true;
			}
			//下からくる車
			if (!bottomIsDead[i] && bottomPosY[i] < -verticalRY) {
				bottomIsDead[i] = true;
			}
		}
	}
}

bool Car::RightCarStop(int i) {
	//デスフラグが立っていない場合当たり判定を取る
	if (!rightIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!rightIsDead[j]) {
				//中心点の距離を取る
				float distanceX = rightPosX[i] - rightPosX[j];
				float distanceY = rightPosY[i] - rightPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//絶対値とする
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
	//デスフラグが立っていない場合当たり判定を取る
	if (!topIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!topIsDead[j]) {
				//中心点の距離を取る
				float distanceX = topPosX[i] - topPosX[j];
				float distanceY = topPosY[i] - topPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//絶対値とする
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
	//デスフラグが立っていない場合当たり判定を取る
	if (!leftIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!leftIsDead[j]) {
				//中心点の距離を取る
				float distanceX = leftPosX[i] - leftPosX[j];
				float distanceY = leftPosY[i] - leftPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//絶対値とする
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
	//デスフラグが立っていない場合当たり判定を取る
	if (!bottomIsDead[i]) {
		for (int j = 0; j < carNum; j++) {
			if (!bottomIsDead[j]) {
				//中心点の距離を取る
				float distanceX = bottomPosX[i] - bottomPosX[j];
				float distanceY = bottomPosY[i] - bottomPosY[j];
				if (distanceX == 0 && distanceY == 0) continue;
				//絶対値とする
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

	//すべての車の当たり判定
	//右と上
	Collision(rightPosX, rightPosY, topPosX, topPosY, rightIsDead, topIsDead);

	if (scene == STAGE2) {
		//右と下
		Collision(rightPosX, rightPosY, bottomPosX, bottomPosY, rightIsDead, bottomIsDead);

		//左と上
		Collision(leftPosX, leftPosY, topPosX, topPosY, leftIsDead, topIsDead);

		//左と下
		Collision(leftPosX, leftPosY, bottomPosX, bottomPosY, leftIsDead, bottomIsDead);
	}
	
}

void Car::Collision(const float posX1[], const float posY1[], const float posX2[], const float posY2[], bool isDead1[], bool isDead2[]) {
	//デスフラグが立っていない場合当たり判定を取る
	for (int i = 0; i < carNum; i++) {
		if (!isDead1[i]) {
			for (int j = 0; j < carNum; j++) {
				if (!isDead2[j]) {
					//中心点の距離を取る
					float distanceX = posX1[i] - posX2[j];
					float distanceY = posY1[i] - posY2[j];
					//絶対値とする
					if (distanceX < 0.0f) distanceX *= -1.0f;
					if (distanceY < 0.0f) distanceY *= -1.0f;
					//２つの短形サイズを取る
					float sizeX = horizRX + verticalRX;
					float sizeY = horizRY + verticalRY;
					//当たっていたらHPが1減り車が両方消える
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