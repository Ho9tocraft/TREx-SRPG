#include "trex_wrapper.h"

DINPUT_JOYSTATE input;

int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_RSHIFT) == 0 || CheckHitKey(KEY_INPUT_LSHIFT) == 0) && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		ScreenFlip();
	}
	WaitKey();
	DxLib_End();
	return 0;
}
