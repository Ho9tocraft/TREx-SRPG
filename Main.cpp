#include "trex_wrapper.h"

DINPUT_JOYSTATE input;
ResourceLoader* resLoader;

int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	if (DxLib_Init() == -1) return -1;
	SetAlwaysRunFlag(TRUE);
	resLoader = new ResourceLoader();
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && (CheckHitKey(KEY_INPUT_RSHIFT) == 0 || CheckHitKey(KEY_INPUT_LSHIFT) == 0) && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

std::vector<std::string> split(std::string str, char del)
{
	size_t first = 0;
	size_t last = str.find_first_of(del);
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
