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

std::vector<std::string> split(std::string str, char del)
{
	int first = 0;
	int last = str.find_first_of(del);
	std::vector<std::string> result;
	while (first < str.size()) {
		std::string subStr(str, first, last - first);
		result.push_back(subStr);
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos) {
			last = str.size();
		}
	}
	return result;
}
