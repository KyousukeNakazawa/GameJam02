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

	//更新処理
	void Update(int mouseX_, int mouseY_, int mouse_);

	//描画
	void Draw();

private:
	//絵情報
	int carGH;

	//情報
	//車
	static const int carNum = 10;
	const float spdNum = 2.0f;
	bool rightIsDead[carNum];	//右からくる車の情報
	bool rightIsStop[carNum];
	float rightCarSpd[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	float horizRX;	//横向きに移動する車の情報
	float horizRY;
	bool topIsDead[carNum];	//上からくる車の情報
	bool topIsStop[carNum];
	float topCarSpd[carNum];
	float topPosX[carNum];
	float topPosY[carNum];
	float verticalRX;
	float verticalRY;

	//スポーンタイマー
	const int spawnTime = 60 * 5;
	int	rightSpawnTimer;
	int topSpawnTimer;

	//信号情報
	TrafficLight* trafficLight;

	//マウス情報
	/*int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;*/

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
};

