#include "DxLib.h"
#include "screen.h"

Screen::Screen() {
	//�w�i���
	backX = 0;
	backY = 0;
	stageGH1 = LoadGraph("Resource/pict/stage1.png");
	stageGH2 = LoadGraph("Resource/pict/stage2.png");

	stageEndGH1 = LoadGraph("Resource/pict/stage1End.png");
	stageEndGH2 = LoadGraph("Resource/pict/stage2End.png");

	//UI���
	//HP
	hpGHX = 10;
	hpGHY = 10;
	LoadDivGraph("Resource/pict/hp.png", 8, 8, 1, 32, 32, hpGH);

	//�^�C�}�[
	timerGHX = WIN_WIDTH - 106;
	timerGHY = 10;
	LoadDivGraph("resource/pict/timenum.png", 10, 10, 1, 48, 48, timerGH);

	//�X�R�A
	scoreGHX = 640 - 48;
	scoreGHY = 382 - 24;
	LoadDivGraph("resource/pict/scorenum.png", 10, 10, 1, 48, 48, scoreGH);
}

Screen::~Screen() {

}

void Screen::Update() {

}

void Screen::Draw(int scene, int hp, int timer) {
	//�w�i
	if (scene == STAGE1) DrawGraph(backX, backY, stageGH1, true);
	else if (scene == STAGE2)DrawGraph(backX, backY, stageGH2, true);

	//UI
	//HP
	HpUI(hp);

	//�^�C�}�[
	TimerUI(timer);
}

void Screen::Score(int stage, int score) {
	if (stage == STAGE1) {
		DrawGraph(backX, backY, stageEndGH1, true);
	}
	else if (stage == STAGE2) {
		DrawGraph(backX, backY, stageEndGH2, true);
	}

	//�z��Ɋi�[
	sprintf_s(scoreStrNum, sizeof(scoreStrNum), "%d", score);

	//�I�t�Z�b�g�l�ɍ��킹��
	for (int i = 0; i < scoreDigits; i++) {
		scoreEachNum[i] = scoreStrNum[i] - 48;
	}
	for (int i = 0; i < scoreDigits; i++) {
		if (score <= 9) {
			DrawGraph(scoreGHX + 24, scoreGHY, scoreGH[scoreEachNum[i]], true);
		}
		else if (score >= 10) {
			DrawGraph(scoreGHX + i * 48, scoreGHY, scoreGH[scoreEachNum[i]], true);
		}
	}
	//DrawFormatString(0, 15, 0xffffff, "%d", score);
}


void Screen::HpUI(int hp) {
	int j = hpEffect.GHTimer / (hpEffect.GHTime / hpEffect.GHNum);

	if (++hpEffect.GHTimer >= hpEffect.GHTime) hpEffect.GHTimer = 0;

	for (int i = 0; i < hp; i++) {
		DrawGraph(hpGHX + (i * 32), hpGHY, hpGH[j], true);
	}
}

void Screen::TimerUI(int timer) {
	//�z��Ɋi�[
	sprintf_s(timerStrNum, sizeof(timerStrNum), "%02d", timer / 60);

	//�I�t�Z�b�g�l�ɍ��킹��
	for (int i = 0; i < timerDigits; i++) {
		timerEachNum[i] = timerStrNum[i] - 48;
	}
	for (int i = 0; i < timerDigits; i++) DrawGraph(timerGHX + i * 48, timerGHY, timerGH[timerEachNum[i]], true);
}