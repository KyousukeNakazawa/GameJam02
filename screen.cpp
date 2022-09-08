#include "DxLib.h"
#include "screen.h"

Screen::Screen() {
	//”wŒiî•ñ
	backX = 0;
	backY = 0;
	stageGH1 = LoadGraph("Resource/stage1.png");

	//HP UIî•ñ
	hpGHX = 10;
	hpGHY = 10;
	LoadDivGraph("Resource/hp.png", 8, 8, 1, 32, 32, hpGH);
}

Screen::~Screen() {

}

void Screen::Update() {

}

void Screen::Draw(int hp) {
	//”wŒi
	DrawGraph(backX, backY, stageGH1, true);

	//HP UI
	HpUI(hp);
}


void Screen::HpUI(int hp) {
	int j = hpEffect.GHTimer / (hpEffect.GHTime / hpEffect.GHNum);

	if (++hpEffect.GHTimer >= hpEffect.GHTime) hpEffect.GHTimer = 0;

	for (int i = 0; i < hp; i++) {
		DrawGraph(hpGHX + (i * 32), hpGHY, hpGH[j], true);
	}
}