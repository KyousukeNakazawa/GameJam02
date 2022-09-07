#pragma once
class TrafficLight
{
public:
	TrafficLight();
	~TrafficLight();

	void Update(int mouseX_, int mouseY_, int mouse_);

	void Draw();

	//信号情報のゲッター
	float GetRightX() { return rightPosX; }
	bool GetRightStop() { return rightStop; }
private:
	//絵情報
	int trafficLightGH[2];

	//情報
	//右からくる車の信号
	bool rightStop;
	float rightPosX;
	float rightPosY;
	float horizRX;	//横向きに移動する車の信号
	float horizRY;

	//マウス情報
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	//信号が変わる処理
	void Change();
};

