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

	//リセット処理
	void Reset(int stage);

	//更新処理
	void Update(int mouseX_, int mouseY_, int mouse_, int& scene);

	//描画
	void Draw();

	//ゲッター
	//HP
	int HpGet() { return hp; }

	//タイマー
	int TimerGet() { return gameTimer; }

private:
	//絵情報
	int carGH[6];

	//サウンド情報
	//車の衝突SE
	int carCrashSE;

	//情報
	//車
	static const int carNum = 20;
	const float spdNum = 2.0f;
	//右からくる車の情報
	bool rightIsDead[carNum];
	bool rightIsStop[carNum];
	float rightCarSpd[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	int rightGH[carNum];

	//左から車の情報
	bool leftIsDead[carNum];
	bool leftIsStop[carNum];
	float leftCarSpd[carNum];
	float leftPosX[carNum];
	float leftPosY[carNum];
	int leftGH[carNum];

	//横向きに移動する車の情報
	float horizRX;
	float horizRY;

	//上からくる車の情報
	bool topIsDead[carNum];
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	int topGH[carNum];

	//下から車の情報
	bool bottomIsDead[carNum];
	bool bottomIsStop[carNum];
	float bottomCarSpd[carNum];
	float bottomPosX[carNum];
	float bottomPosY[carNum];
	int bottomGH[carNum];

	//縦向きに移動する車
	float verticalRX;
	float verticalRY;

	//車線情報
	int rightlane;
	int toplane;
	int bottomlane;

	//信号情報
	TrafficLight* trafficLight;

	//スポーンタイマー
	//2～6秒でランダム
	const int spawnTime = 60 * (GetRand(4) + 2);
	int	rightSpawnTimer;
	int topSpawnTimer;
	int leftSpawnTimer;
	int bottomSpawnTimer;

	//ゲームタイマー
	const int gameTime = 60 * 60;
	int gameTimer;

	//HP
	const int hpNum = 3;
	int hp;

	int scene;

	//関数
	//スポーン処理
	void Spawn();

	//信号での停止処理
	void Stop();

	//移動処理
	void Move();

	//画面外に行ったら消える
	void Range();

	//同じ車線の当たり判定
	bool RightCarStop(int i);

	bool TopCarStop(int i);

	bool LeftCarStop(int i);

	bool BottomCarStop(int i);

	//別車線の当たり判定
	void CarCollision();

	void Collision(const float posX1[], const float posY1[], const float posX2[], const float posY2[], bool isDead1[], bool isDead2[]);
};

