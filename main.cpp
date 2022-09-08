#include "DxLib.h"
#include "screen.h"
#include "car.h"


// ウィンドウのタイトルに表示する文字列
const char TITLE_[] = "";



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	bool winChange = true;
	ChangeWindowMode(winChange);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE_);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	Screen* screen = new Screen;
	Car* car = new Car;

	int scene = STAGE1;


	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	//マウス情報
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		oldMouse = mouse;

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		GetMousePoint(&mouseX, &mouseY);

		int mouse = GetMouseInput();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		switch (scene) {
		case TITLE:
			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) scene = STAGE1;

			DrawFormatString(0, 0, 0xffffff, "title");
			break;
		case STAGE1:
			screen->Update();

			car->Update(mouseX, mouseY, mouse, scene);

			// 描画処理
			screen->Draw(car->HpGet());

			car->Draw();
			break;
		case END:
			car->Reset();

			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) scene = TITLE;

			DrawFormatString(0, 0, 0xffffff, "end");
			break;
		case LOAD:

			break;
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	if (screen != nullptr) delete screen;
	if (car != nullptr) delete car;
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
