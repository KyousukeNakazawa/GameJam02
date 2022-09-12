#pragma once
#include "DxLib.h"
#include "screen.h"
#include "math.h"

class TrafficLight
{
public:
	TrafficLight();
	~TrafficLight();

	void Reset(int stage_);

	void Update(int mouseX_, int mouseY_, int mouse_, int scene);

	void Draw();

	//信号情報のゲッター
	float GetRightX() { return rightPosX; }
	bool GetRightStop() { return rightStop; }

	float GetTopY() { return topPosY; }
	bool GetTopStop() { return topStop; }

	float GetLeftX() { return leftPosX; }
	bool GetLeftStop() { return leftStop; }

	float GetBottomY() { return bottomPosY; }
	bool GetBottomStop() { return bottomStop; }
private:
	//絵情報
	int trafficLightGH[2];

	//サウンド情報
	//信号をクリックしたときの音
	int changeSE;

	//情報
	//右からくる車の信号
	bool rightStop;
	float rightPosX;
	float rightPosY;

	//左から車の信号
	bool leftStop;
	float leftPosX;
	float leftPosY;

	//横向きに移動する車の信号
	float horizRX;
	float horizRY;

	//上からくる車の信号
	bool topStop;
	float topPosX;
	float topPosY;

	//下から車の信号
	bool bottomStop;
	float bottomPosX;
	float bottomPosY;

	//縦向きに移動する車の信号
	float verticalRX;
	float verticalRY;

	//マウス情報
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	int scene;

	//信号が変わる処理
	void Change();
};

