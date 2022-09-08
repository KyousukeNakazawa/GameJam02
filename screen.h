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

	void Draw(int hp);

private:
	//背景情報
	int backX;
	int backY;
	int stageGH1;

	//HP UI情報
	int hpGHX;
	int hpGHY;
	AniGHTimer hpEffect{ 8, 40, 0 };
	int hpGH[8];

	void HpUI(int hp);
};