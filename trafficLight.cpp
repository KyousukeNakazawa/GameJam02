#include "trafficLight.h"

enum trafficLight {
	Red_,
	blue_,
};

TrafficLight::TrafficLight() {
	LoadDivGraph("Resource/pict/trafficLightGH.png", 2, 1, 2, 32, 64, trafficLightGH);

	changeSE = LoadSoundMem("Resource/sound/changeSE.mp3");
	ChangeVolumeSoundMem(150, changeSE);

	rightStop = true;
	rightPosX = WIN_WIDTH / 2 + 100;
	rightPosY = WIN_HEIGHT / 2 + 115;

	leftPosX = -100;
	leftPosY = -100;

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

void TrafficLight::Reset(int stage) {
	rightStop = true;
	topStop = true;
	leftStop = true;
	bottomStop = true;

	if (stage == STAGE1) {
		rightPosX = WIN_WIDTH / 2 + 100;
		rightPosY = WIN_HEIGHT / 2 + 115;

		topPosX = WIN_WIDTH / 2 + 115;
		topPosY = WIN_HEIGHT / 2 - 100;
	}
	else if (stage == STAGE2) {
		rightPosX = WIN_WIDTH / 2.5 * 2 + 36;
		rightPosY = WIN_HEIGHT / 2 + 115;

		leftPosX = WIN_WIDTH / 6 + 10;
		leftPosY = WIN_HEIGHT / 2 - 115;

		topPosX = WIN_WIDTH / 2.5 * 2 + 51;
		topPosY = WIN_HEIGHT / 2 - 100;

		bottomPosX = WIN_WIDTH / 3 + 10;
		bottomPosY = WIN_HEIGHT / 2 + 100;
	}
}

void TrafficLight::Update(int mouseX_, int mouseY_, int mouse_, int scene_) {
	scene = scene_;
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

	if (scene == STAGE2) {
		//左から車の信号
		if (leftStop) DrawRotaGraph(leftPosX, leftPosY, 1.0, 0, trafficLightGH[Red_], true, true);
		else DrawRotaGraph(leftPosX, leftPosY, 1.0, 0, trafficLightGH[blue_], true, true);

		//下から車の信号
		if (bottomStop) DrawRotaGraph(bottomPosX, bottomPosY, 1.0, Radian(-90), trafficLightGH[Red_], true, false);
		else DrawRotaGraph(bottomPosX, bottomPosY, 1.0, Radian(-90), trafficLightGH[blue_], true, false);

	}
}

void TrafficLight::Change() {
	//クリックで信号が変わる
	//右からくる車の信号
	float right1 = rightPosX + horizRX;
	float left1 = rightPosX - horizRX;
	float top1 = rightPosY - horizRY;
	float bottom1 = rightPosY + horizRY;
	
	if (oldMouse == 0 && mouse == 1 && mouseX < right1 && mouseX > left1 && mouseY >top1 && mouseY < bottom1) {
		rightStop = !rightStop;
		PlaySoundMem(changeSE, DX_PLAYTYPE_BACK, true);
	}

	//上からくる車の信号
	float right2 = topPosX + verticalRX;
	float left2 = topPosX - verticalRX;
	float top2 = topPosY - verticalRY;
	float bottom2 = topPosY + verticalRY;
	
	if (oldMouse == 0 && mouse == 1 && mouseX < right2 && mouseX > left2 && mouseY > top2 && mouseY < bottom2) {
		topStop = !topStop;
		PlaySoundMem(changeSE, DX_PLAYTYPE_BACK, true);
	}

	//左からくる車の信号
	float right3 = leftPosX + horizRX;
	float left3 = leftPosX - horizRX;
	float top3 = leftPosY - horizRY;
	float bottom3 = leftPosY + horizRY;

	if (oldMouse == 0 && mouse == 1 && mouseX < right3 && mouseX > left3 && mouseY > top3 && mouseY < bottom3) {
		leftStop = !leftStop;
		PlaySoundMem(changeSE, DX_PLAYTYPE_BACK, true);
	}

	//下からくる車の信号
	float right4 = bottomPosX + verticalRX;
	float left4 = bottomPosX - verticalRX;
	float top4 = bottomPosY - verticalRY;
	float bottom4 = bottomPosY + verticalRY;

	if (oldMouse == 0 && mouse == 1 && mouseX < right4 && mouseX > left4 && mouseY > top4 && mouseY < bottom4) {
		bottomStop = !bottomStop;
		PlaySoundMem(changeSE, DX_PLAYTYPE_BACK, true);
	}
}