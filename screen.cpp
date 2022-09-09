#include "DxLib.h"
#include "screen.h"

Screen::Screen() {
	//背景情報
	backX = 0;
	backY = 0;
	stageGH1 = LoadGraph("Resource/stage1.png");
	stageGH2 = LoadGraph("Resource/stage2.png");

	//UI情報
	//HP
	hpGHX = 10;
	hpGHY = 10;
	LoadDivGraph("Resource/hp.png", 8, 8, 1, 32, 32, hpGH);

	//タイマー
	timerGHX = WIN_WIDTH - 106;
	timerGHY = 10;
	LoadDivGraph("resource/timenum.png", 10, 10, 1, 48, 48, timerGH);
}

Screen::~Screen() {

}

void Screen::Update() {

}

void Screen::Draw(int scene, int hp, int timer) {
	//背景
	if (scene == STAGE1) DrawGraph(backX, backY, stageGH1, true);
	else if (scene == STAGE2)DrawGraph(backX, backY, stageGH2, true);

	//UI
	//HP
	HpUI(hp);

	//タイマー
	TimerUI(timer);
}


void Screen::HpUI(int hp) {
	int j = hpEffect.GHTimer / (hpEffect.GHTime / hpEffect.GHNum);

	if (++hpEffect.GHTimer >= hpEffect.GHTime) hpEffect.GHTimer = 0;

	for (int i = 0; i < hp; i++) {
		DrawGraph(hpGHX + (i * 32), hpGHY, hpGH[j], true);
	}
}

void Screen::TimerUI(int timer) {
	//配列に格納
	sprintf_s(timerStrNum, sizeof(timerStrNum), "%02d", timer / 60);

	//オフセット値に合わせる
	for (int i = 0; i < timerDigits; i++) {
		timerEachNum[i] = timerStrNum[i] - 48;
	}
	for (int i = 0; i < timerDigits; i++) DrawGraph(timerGHX + i * 48, timerGHY, timerGH[timerEachNum[i]], true);
}