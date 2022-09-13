#pragma once

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

enum Scene {
	TITLE,
	STAGE1,
	STAGE2,
	END,
	LOAD,
};

//アニメーション用
struct AniGHTimer {
	const int GHNum;
	const int GHTime;
	int GHTimer;
};

class Screen {
public:
	Screen();
	~Screen();

	void Update();

	void Draw(int scene, int hp, int timer);

	void Score(int stage, int score);

private:
	//背景情報
	int backX;
	int backY;
	int stageGH1;
	int stageGH2;

	int stageEndGH1;
	int stageEndGH2;

	//UI情報
	//HP
	int hpGHX;
	int hpGHY;
	AniGHTimer hpEffect{ 8, 40, 0 };
	int hpGH[8];

	//タイマー 
	int timerGHX;
	int timerGHY;
	int timerGH[10];
	const int timerDigits = 2;
	char timerStrNum[3];
	int timerEachNum[3];

	//スコア
	//タイマー 
	int scoreGHX;
	int scoreGHY;
	int scoreGH[10];
	const int scoreDigits = 2;
	char scoreStrNum[3];
	int scoreEachNum[3];

	void HpUI(int hp);

	void TimerUI(int timer);
};