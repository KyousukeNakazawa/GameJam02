#include "DxLib.h"
#include "screen.h"

Screen::Screen() {
	backX = 0;
	backY = 0;
	stageGH1 = LoadGraph("Resource/stage1.png");
}

Screen::~Screen() {

}

void Screen::Update() {

}

void Screen::Draw() {
	DrawGraph(backX, backY, stageGH1, true);
}