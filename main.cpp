#include "all_loaders.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	//ウィンドウモードにする
	ChangeWindowMode(TRUE);
	//DXライブラリ初期化
	if (DxLib_Init() == -1) return -1;
	//(テストコード)
	WaitKey();
	//DXLibの終了
	DxLib_End();
	return 0;
}
