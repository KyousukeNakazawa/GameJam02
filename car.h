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
	void Reset();

	//更新処理
	void Update(int mouseX_, int mouseY_, int mouse_, int& scene);

	//描画
	void Draw();

	//HPのゲッター
	int HpGet() { return hp; }

private:
	//絵情報
	int carGH;

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
	//横向きに移動する車の情報
	float horizRX;
	float horizRY;
	//上からくる車の情報
	bool topIsDead[carNum];
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	//縦向きに移動する車
	float verticalRX;
	float verticalRY;

	//車線
	int rightlane;
	int toplane;

	//スポーンタイマー
	//2～6秒でランダム
	const int spawnTime = 60 * (GetRand(4) + 2);
	int	rightSpawnTimer;
	int topSpawnTimer;

	//信号情報
	TrafficLight* trafficLight;

	//HP
	const int hpNum = 3;
	int hp;

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

	//別車線の当たり判定
	void CarCollision();
};

