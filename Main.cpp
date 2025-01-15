#include "All_Header_Wrapper.h"

int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	WaitKey();
	DxLib_End();
	return 0;
}
