#pragma once

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;

class Screen {
public:
	Screen();
	~Screen();

	void Update();

	void Draw();
private:
	int backX;
	int backY;
	int stageGH1;
};