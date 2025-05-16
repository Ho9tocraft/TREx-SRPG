#include "stdafx.h"
#include "Main.h"
#include "Loader.h"
#include "DataPilot.h"
#include "DataPilotSkills.h"
#include "DataUnit.h"
#include "DataUnitSkills.h"
#include "GamePilot.h"
#include "GameUnit.h"

std::shared_ptr<Loader> game_loader;

int WINAPI WinMain(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPrevIns, _In_ LPSTR lpC, _In_ int nC) {
	ChangeWindowMode(TRUE);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	if (DxLib_Init() == -1) return -1;
	game_loader = std::make_shared<Loader>();
	json11::Json parsedJson = game_loader->parseResource("./Resources/datas/datapacks/pilots.json");
	json11::Json::array pilotList = parsedJson["pilot_list"].array_items();
	for (const json11::Json& pilot : pilotList) {
		game_loader->registeringPilot(pilot["regKey"].string_value(), pilot);
	}
	DrawString(0, 0, sjis_to_utf8(game_loader->register_pilots.at("ExelliaCCSAware")->profile.getFullname()).c_str(), 0xffff00);
	WaitKey();
	DxLib_End();
	return 0;
}
