#pragma once

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;

enum Scene {
	TITLE,
	STAGE1,
	STAGE2,
	END,
	LOAD,
};

//�A�j���[�V�����p
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
	//�w�i���
	int backX;
	int backY;
	int stageGH1;

	//HP UI���
	int hpGHX;
	int hpGHY;
	AniGHTimer hpEffect{ 8, 40, 0 };
	int hpGH[8];

	void HpUI(int hp);
};