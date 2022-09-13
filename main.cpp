#include "DxLib.h"
#include "screen.h"
#include "car.h"


// ウィンドウのタイトルに表示する文字列
const char TITLE_[] = "交通整理";



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
	SetBackgroundColor(0x00, 0x00, 0xff);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int titleBGM = LoadSoundMem("Resource/sound/titleBGM.mp3");
	ChangeVolumeSoundMem(100, titleBGM);
	int gameBGM = LoadSoundMem("Resource/sound/gameBGM.mp3");
	ChangeVolumeSoundMem(100, gameBGM);
	int endBGM = LoadSoundMem("Resource/sound/endBGM.mp3");
	ChangeVolumeSoundMem(100, endBGM);
	int selectSE = LoadSoundMem("Resource/sound/selectSE.mp3");
	ChangeVolumeSoundMem(150, selectSE);
	int decisionSE = LoadSoundMem("Resource/sound/decisionSE.mp3");
	ChangeVolumeSoundMem(150, decisionSE);

	//ゲーム説明
	int optionGH = LoadGraph("Resource/pict/operation.png");

	//タイトル
	int title1GH = LoadGraph("Resource/pict/title1.png");
	int title2GH = LoadGraph("Resource/pict/title2.png");
	int title3GH = LoadGraph("Resource/pict/title3.png");

	// ゲームループで使う変数の宣言
	Screen* screen = new Screen;
	Car* car = new Car;

	int scene = TITLE;
	int stage = EXPLANATION;


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

		
		switch (scene) {
		case TITLE:
			StopSoundMem(gameBGM);
			StopSoundMem(endBGM);

			//BGM
			if (!CheckSoundMem(titleBGM)) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, true);
			}

			//ステージ選択
			//上
			if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]) {
				stage--;
				if (stage < EXPLANATION) stage = STAGE2;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			}

			//下
			if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN]) {
				stage++;
				if (stage > STAGE2) stage = EXPLANATION;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			}

			//決定
			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) {
				PlaySoundMem(decisionSE, DX_PLAYTYPE_BACK, true);
				scene = stage;
				car->Reset(stage);
			}

			//DrawFormatString(0, 0, 0xffffff, "title");

			if (stage == EXPLANATION) {
				DrawGraph(0, 0, title1GH, true);
				//DrawFormatString(0, 15, 0xffffff, "stage1");
			}
			else if (stage == STAGE1) {
				//DrawFormatString(0, 15, 0xffffff, "stage2");
				DrawGraph(0, 0, title2GH, true);
			}
			else if (stage == STAGE2) {
				//DrawFormatString(0, 15, 0xffffff, "exp");
				DrawGraph(0, 0, title3GH, true);
			}

			break;
		case EXPLANATION:

			//決定
			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) {
				PlaySoundMem(decisionSE, DX_PLAYTYPE_BACK, true);
				scene = TITLE;
			}

			//背景
			DrawGraph(0, 0, optionGH, true);

			DrawFormatString(0, 0, 0xffffff, "exp");

			break;
		case STAGE1:
		case STAGE2:
			StopSoundMem(titleBGM);

			//BGM
			if (!CheckSoundMem(gameBGM)) {
				PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP, true);
			}

			// 更新処理
			screen->Update();

			car->Update(mouseX, mouseY, mouse, scene);

			// 描画処理
			screen->Draw(scene, car->HpGet(), car->TimerGet());

			car->Draw();
			break;
		case END:
			StopSoundMem(gameBGM);

			//BGM
			if (!CheckSoundMem(endBGM)) {
				PlaySoundMem(endBGM, DX_PLAYTYPE_LOOP, true);
			}

			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) {
				PlaySoundMem(decisionSE, DX_PLAYTYPE_BACK, true);
				scene = TITLE;
			}

			//DrawFormatString(0, 0, 0xffffff, "end");

			screen->Score(stage, car->ScoreGet());
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
