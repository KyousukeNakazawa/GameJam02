#include "DxLib.h"
#include "screen.h"
#include "car.h"


// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE_[] = "��ʐ���";



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	bool winChange = true;
	ChangeWindowMode(winChange);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE_);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xff);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
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

	//�Q�[������
	int optionGH = LoadGraph("Resource/pict/operation.png");

	//�^�C�g��
	int title1GH = LoadGraph("Resource/pict/title1.png");
	int title2GH = LoadGraph("Resource/pict/title2.png");
	int title3GH = LoadGraph("Resource/pict/title3.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	Screen* screen = new Screen;
	Car* car = new Car;

	int scene = TITLE;
	int stage = EXPLANATION;


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	//�}�E�X���
	int mouseX;
	int mouseY;
	int mouse = 0;
	int oldMouse;

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		oldMouse = mouse;

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		GetMousePoint(&mouseX, &mouseY);

		int mouse = GetMouseInput();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		
		switch (scene) {
		case TITLE:
			StopSoundMem(gameBGM);
			StopSoundMem(endBGM);

			//BGM
			if (!CheckSoundMem(titleBGM)) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, true);
			}

			//�X�e�[�W�I��
			//��
			if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]) {
				stage--;
				if (stage < EXPLANATION) stage = STAGE2;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			}

			//��
			if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN]) {
				stage++;
				if (stage > STAGE2) stage = EXPLANATION;
				PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			}

			//����
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

			//����
			if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) {
				PlaySoundMem(decisionSE, DX_PLAYTYPE_BACK, true);
				scene = TITLE;
			}

			//�w�i
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

			// �X�V����
			screen->Update();

			car->Update(mouseX, mouseY, mouse, scene);

			// �`�揈��
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

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	if (screen != nullptr) delete screen;
	if (car != nullptr) delete car;
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
