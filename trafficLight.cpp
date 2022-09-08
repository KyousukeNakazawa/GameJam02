#include "trafficLight.h"

enum trafficLight {
	Red_,
	blue_,
};

TrafficLight::TrafficLight() {
	LoadDivGraph("Resource/trafficLightGH.png", 2, 1, 2, 32, 64, trafficLightGH);

	rightStop = true;
	rightPosX = WIN_WIDTH / 2 + 100;
	rightPosY = WIN_HEIGHT / 2 + 115;
	horizRX = 12;
	horizRY = 32;

	topStop = true;
	topPosX = WIN_WIDTH / 2 + 115;
	topPosY = WIN_HEIGHT / 2 - 100;
	verticalRX = 32;
	verticalRY = 12;
}

TrafficLight::~TrafficLight() {

}

void TrafficLight::Update(int mouseX_, int mouseY_, int mouse_) {
	oldMouse = mouse;
	mouse = mouse_;
	mouseX = mouseX_;
	mouseY = mouseY_;

	Change();
}

void TrafficLight::Draw() {
	//右からくる車の信号
	if (rightStop) DrawRotaGraph(rightPosX, rightPosY, 1.0, 0,  trafficLightGH[Red_], true, false);
	else DrawRotaGraph(rightPosX, rightPosY, 1.0, 0, trafficLightGH[blue_], true, false);

	//上からくる車の信号
	if(topStop) DrawRotaGraph(topPosX, topPosY, 1.0, Radian(-90), trafficLightGH[Red_], true, false);
	else DrawRotaGraph(topPosX, topPosY, 1.0, Radian(-90), trafficLightGH[blue_], true, false);
}

void TrafficLight::Change() {
	float right1 = rightPosX + horizRX;
	float left1 = rightPosX - horizRX;
	float top1 = rightPosY - horizRY;
	float bottom1 = rightPosY + horizRY;
	//クリックで信号が変わる
	//右からくる車の信号
	if (oldMouse == 0 && mouse == 1 && mouseX < right1 && mouseX > left1 && mouseY >top1 && mouseY < bottom1) {
		rightStop = !rightStop;
	}

	float right2 = topPosX + verticalRX;
	float left2 = topPosX - verticalRX;
	float top2 = topPosY - verticalRY;
	float bottom2 = topPosY + verticalRY;
	//上からくる車の信号
	if (oldMouse == 0 && mouse == 1 && mouseX < right2 && mouseX > left2 && mouseY > top2 && mouseY < bottom2) {
		topStop = !topStop;
	}
}