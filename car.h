#pragma once
#include "trafficLight.h"

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
	float rightCarSpd[carNum];
	bool rightIsDead[carNum];	//右からくる車の情報
	bool isStop[carNum];
	float rightPosX[carNum];
	float rightPosY[carNum];
	bool leftIsDead[carNum];	//左からくる車の情報
	float leftPosX[carNum];
	float leftPosY[carNum];
	float horizRX;	//横向きに移動する車の情報
	float horizRY;

	//スポーンタイマー
	const int spawnTime = 60 * 5;
	int	spawnTimer;

	//信号情報
	TrafficLight* trafficLight;

	//マウス情報
	/*int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;*/

	//移動処理
	void Move();

	//画面外に行ったら消える
	void Range();

	//同じ車線の当たり判定
	bool StopCollision();
};

