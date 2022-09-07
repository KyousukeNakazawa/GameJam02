#include "DxLib.h"
#include "car.h"
#include "screen.h"

float Radian(float n) {
	return n * 3.14f / 180;
}

Car::Car() {
	trafficLight = new TrafficLight;
	carGH = LoadGraph("Resource/carGH.png");

	horizRX = 32;
	horizRY = 16;
	spawnTimer = spawnTime;
	for (int i = 0; i < carNum; i++) {
		rightIsDead[i] = true;
		isStop[i] = false;
		rightPosX[i] = -50;
		rightPosY[i] = -50;
		rightCarSpd[i] = spdNum;
		leftIsDead[i] = true;
		leftPosX[i] = -50;
		leftPosY[i] = -50;
	}
}

Car::~Car() {
	if(trafficLight != nullptr) delete trafficLight;
}

void Car::Update(int mouseX_, int mouseY_, int mouse_) {
	//マウス情報を更新
	/*oldMouse = mouse;
	mouse = mouse_;
	mouseX = mouseX_;
	mouseY = mouseY_;*/

	//スポーン処理
	if (--spawnTimer < 0) {
		//カウントが0になったらフラグが立ってるものを探し生成
		for (int i = 0; i < carNum; i++) {
			if (rightIsDead[i]) {
				rightPosX[i] = WIN_WIDTH - horizRX;
				rightPosY[i] = WIN_HEIGHT / 2 + 12;
				rightIsDead[i] = false;
				break;
			}
		}
		spawnTimer = spawnTime;
	}

	//信号処理
	trafficLight->Update(mouseX_, mouseY_, mouse_);

	//赤なら停止する
	for (int i = 0; i < carNum; i++) {
		//信号が赤で前に車がいない場合
		if (rightPosX[i] >= trafficLight->GetRightX() + 15 && rightPosX[i] <= trafficLight->GetRightX() + 25
			&& trafficLight->GetRightStop() && !StopCollision()) {
			rightCarSpd[i] = 0;
			
		}
		//信号が赤で前に車がいる場合
		else if(trafficLight->GetRightStop() && StopCollision()) {
			rightCarSpd[i] = 0;
		}
		//信号が青の場合
		else {
			rightCarSpd[i] = spdNum;
		}
	}


	//移動処理
	Move();

	//範囲処理
	Range();
}

void Car::Draw() {
	//車
	for (int i = 0; i < carNum; i++) {
		if (!rightIsDead[i]) {
			DrawRotaGraph(rightPosX[i], rightPosY[i], 1.0, Radian(-90),  carGH, true, false);
		}
	}

	//信号
	trafficLight->Draw();

	DrawFormatString(0, 0, 0x00ffff, "%d", rightIsDead[0]);
}

void Car::Move() {
	//
	for (int i = 0; i < carNum; i++) {
		if (!rightIsDead[i]) {
			rightPosX[i] -= rightCarSpd[i];
		}
	}
}

void Car::Range() {
	for (int i = 0; i < carNum; i++) {
		if (!rightIsDead[i] && rightPosX[i] < -horizRX) {
			rightIsDead[i] = true;
		}
	}
}

bool Car::StopCollision() {
	for (int i = 0; i < carNum; i++) {
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
						rightCarSpd[i] = 0;
						return true;
					}
				}
			}
		}
	}
	return false;
}