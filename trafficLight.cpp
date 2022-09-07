#include "DxLib.h"
#include "screen.h"
#include "trafficLight.h"

enum trafficLight {
	Red_,
	blue_,
};

TrafficLight::TrafficLight() {
	LoadDivGraph("Resource/trafficLightGH.png", 2, 1, 2, 32, 64, trafficLightGH);

	rightStop = true;
	rightPosX = WIN_WIDTH / 2 + 150;
	rightPosY = WIN_HEIGHT / 2 + 100;
	horizRX = 12;
	horizRY = 32;
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
	if (rightStop) DrawRotaGraph(rightPosX, rightPosY, 1.0, 0,  trafficLightGH[Red_], true, false);
	else DrawRotaGraph(rightPosX, rightPosY, 1.0, 0, trafficLightGH[blue_], true, false);
}

void TrafficLight::Change() {
	float right = rightPosX + horizRX;
	float left = rightPosX - horizRX;
	float top = rightPosY - horizRY;
	float bottom = rightPosY + horizRY;
	//クリックで信号が変わる
	if (oldMouse == 0 && mouse == 1 && mouseX < right && mouseX > left && mouseY >top && mouseY < bottom) {
		rightStop = !rightStop;
	}
}