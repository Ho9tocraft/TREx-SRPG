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
std::shared_ptr<GameMain> game_main;

int WINAPI WinMain(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPrevIns, _In_ LPSTR lpC, _In_ int nC) {
	game_loader = std::make_shared<Loader>();
	game_main = std::make_shared<GameMain>();
	json11::Json parsedConfig = game_loader->parseResource("./config.json");
	json11::Json stageData = game_loader->parseResource(game_loader->loadPath(LoaderHandlerType::DATA_STAGES, "stage_001.json"));
	int windowWidth = parsedConfig["window"]["width"].int_value();
	int windowHeight = parsedConfig["window"]["height"].int_value();
	game_loader->unitGraphResolution = windowWidth / 32;
	SetMainWindowText("The Reminiscence of Exellia NG+X");
	ChangeWindowMode(TRUE);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	SetGraphMode(windowWidth, windowHeight, 32);
	if (DxLib_Init() == -1) return -1;
	json11::Json parsedJsonPilot = game_loader->parseResource(game_loader->loadPath(LoaderHandlerType::DATA_PILOT));
	json11::Json parsedJsonUnit  = game_loader->parseResource(game_loader->loadPath(LoaderHandlerType::DATA_UNIT));
	json11::Json::array pilotList = parsedJsonPilot["pilot_list"].array_items();
	json11::Json::array unitList = parsedJsonUnit["unit_list"].array_items();
	for (const json11::Json& pilot : pilotList) {
		game_loader->registeringPilot(pilot);
	}
	for (const json11::Json& unit : unitList) {
		game_loader->registeringUnit(unit);
	}
	game_main->setStageMap(stageData);
	/*
	DrawString(0, 0, sjis_to_utf8(game_loader->registry_pilots.at("エクセリア・シャルロッテ・クレア・ゼーゲブレヒト・アウェア")
		->profile.getFullname()).c_str(), 0xffff00);
	DrawString(0, 24, sjis_to_utf8(game_loader->registry_units.at("エクセリア・シャルロッテ・クレア・ゼーゲブレヒト・アウェア")
		->profile.getUFullname()).c_str(), 0xff9900);
	*/
	game_main->CreateUnitByFaction("エクセリア・シャルロッテ・クレア・ゼーゲブレヒト・アウェア", 0, 
		"エクセリア・シャルロッテ・クレア・ゼーゲブレヒト・アウェア", 1, 0, 0, "味方");
	game_main->DrawStageGraph(windowWidth, windowHeight);
	WaitKey();
	DxLib_End();
	return 0;
}

/* --- GameMain --- */

std::shared_ptr<GamePilot> GameMain::definationPilot(std::shared_ptr<GamePilot> unit)
{
	std::string pilotFullName = sjis_to_utf8(unit->getReferData()->profile.getFullname());
	bool isUnique = unit->getReferData()->profile.isWeed() == false;
	if (isUnique) this->generatedPilot.insert_or_assign(pilotFullName, isUnique);
	else if (this->generatedPilot.contains(pilotFullName)) this->generatedPilot.erase(pilotFullName);
	return unit;
}

void GameMain::DrawStageGraph(int windowWidth, int windowHeight)
{
	int lineHorizontal = windowHeight / game_loader->unitGraphResolution;
	int lineVertical = windowWidth / game_loader->unitGraphResolution;
	for (int i = 0; i < lineHorizontal; i++) {
		int horzLinePosY = game_loader->unitGraphResolution * (i + 1);
		DrawLine(0, horzLinePosY, windowWidth, horzLinePosY, 0xDCDCDC);
	}
	for (int i = 0; i < lineVertical; i++) {
		int vertLinePosX = game_loader->unitGraphResolution * (i + 1);
		DrawLine(vertLinePosX, 0, vertLinePosX, windowHeight, 0xDCDCDC);
	}
	for (auto& troop : this->troopList) {
		int drawX = static_cast<int>(troop->getPosX() * game_loader->unitGraphResolution);
		int drawY = static_cast<int>(troop->getPosY() * game_loader->unitGraphResolution);
		troop->DrawUnitGraph(drawX, drawY);
	}
}

void GameMain::setStageMap(json11::Json raw_data)
{
	json11::Json area_properties = raw_data["area_properties"];
	std::vector<std::vector<uint64_t>> terrain_data_index;
	auto& arrItemAll = area_properties.array_items();
	for (auto& arrayY : arrItemAll) {
		std::vector<uint64_t> prefetch_index;
		auto& arrItemY = arrayY.array_items();
		for (auto& arrayX : arrItemY) {
			int64_t tmpArrItemY = static_cast<int64_t>(arrItemY.size());
			if (tmpArrItemY > this->map_width) this->map_width = tmpArrItemY;
			prefetch_index.push_back(arrayX.int_value());
		}
		int64_t tmpArrItemAll = static_cast<int64_t>(arrItemAll.size());
		if (tmpArrItemAll > this->map_height) this->map_height = tmpArrItemAll;
		terrain_data_index.push_back(prefetch_index);
	}
	json11::Json path_data = raw_data["path_data"];
	for (auto& terrainY : terrain_data_index) {
		std::vector<std::pair<bool, GameMapPath>> prefetch_terrain;
		for (auto& terrainX : terrainY) {
			prefetch_terrain.push_back(std::make_pair(false, GameMapPath(path_data[terrainX])));
		}
		this->stageMap.push_back(prefetch_terrain);
	}
}

void GameMain::eventOnDestroy()
{
	for (size_t i = 0; i < this->troopList.size(); i++) {
		auto& value = this->troopList[i];
		if (value->getUnitMain()->getUnitCond() == UnitCondition::BEING_BEATEN_DOWN &&
			value->getUnitSub()->getUnitCond() == UnitCondition::BEING_BEATEN_DOWN && value->getFaction() != GameFaction::PLAYER) {
			value->getUnitMain().reset();
			value->getUnitSub().reset();
			this->troopList.erase(this->troopList.begin() + i);
		}
	}
}

void GameMain::LaunchUnitFromSaveData(std::string pKeyPilotMain, std::string pKeyPilotSub)
{
}

void GameMain::CreateUnitByFaction(std::string pKeyUnitMain, int64_t pUnitMainRankHP, int64_t pUnitMainRankEN, int64_t pUnitMainRankArmor,
	int64_t pUnitMainRankSight, int64_t pUnitMainRankEvade, std::string pKeyPilotMain, int64_t pPilotMainLevel, std::string pFaction,
	int64_t pPosX, int64_t pPosY, std::string pKeyUnitSub, int64_t pUnitSubRankHP, int64_t pUnitSubRankEN, int64_t pUnitSubRankArmor,
	int64_t pUnitSubRankSight, int64_t pUnitSubRankEvade, std::string pKeyPilotSub, int64_t pPilotSubLevel)
{
	//既出チェック
	//雑魚はもれなくfalseとなるので無視される
	if (this->generatedPilot[pKeyPilotMain] || this->generatedPilot[pKeyPilotSub]) return;
	std::shared_ptr<GameUnit> tmpUnitMain = std::make_shared<GameUnit>(game_loader->registry_units.at(pKeyUnitMain),
		pUnitMainRankHP, pUnitMainRankEN, pUnitMainRankArmor, pUnitMainRankSight, pUnitMainRankSight);
	std::shared_ptr<GameUnit> tmpUnitSub;
	std::shared_ptr<GameTroop> tmpTroop;
	tmpUnitMain->ridePilot(this->definationPilot(
		std::make_shared<GamePilot>(game_loader->registry_pilots.at(pKeyPilotMain), pPilotMainLevel)));
	if (!pKeyPilotSub.empty()) {
		tmpUnitSub = std::make_shared<GameUnit>(game_loader->registry_units.at(pKeyUnitSub),
			pUnitSubRankHP, pUnitSubRankEN, pUnitSubRankArmor, pUnitSubRankSight, pUnitSubRankEvade);
		tmpUnitSub->ridePilot(this->definationPilot(
			std::make_shared<GamePilot>(game_loader->registry_pilots.at(pKeyPilotSub), pPilotSubLevel)));
	}
	if (!tmpUnitSub) tmpTroop = std::make_shared<GameTroop>(tmpUnitMain, tmpUnitSub);
	else tmpTroop = std::make_shared<GameTroop>(tmpUnitMain);
	GameFaction tmpFaction = GameFaction::NOT_CREATED;
	{
		using std::regex;
		using std::regex_match;
		using namespace std::regex_constants;
		regex FAC_PLAYER(R"(^味方|プレイヤー|PC)", ECMAScript, icase);
		regex FAC_ENEMY_1(R"(^敵|ENM1)", ECMAScript, icase);
		regex FAC_ENEMY_2(R"(^中立|ENM2)", ECMAScript, icase);
		regex FAC_NPC(R"(^NPC|ノンプレイヤー)", ECMAScript, icase);
		int rgx_index = regex_match(pFaction, FAC_PLAYER) ? 1 : regex_match(pFaction, FAC_ENEMY_1) ? 2 :
			regex_match(pFaction, FAC_ENEMY_2) ? 3 : regex_match(pFaction, FAC_NPC) ? 4 : 4;
		tmpFaction = static_cast<GameFaction>(rgx_index);
	}
	tmpTroop->launchUnit(pPosX, pPosY, tmpFaction);
	this->troopList.push_back(std::move(tmpTroop));
}

void GameMain::CreateUnitByFaction(std::string pKeyUnitMain, int64_t pUnitMainRank, std::string pKeyPilotMain, int64_t pPilotMainLevel, int64_t pPosX, int64_t pPosY, std::string pFaction, std::string pKeyUnitSub, int64_t pUnitRankSub, std::string pKeyPilotSub, int64_t pPilotSubLevel)
{
	this->CreateUnitByFaction(pKeyUnitMain, pUnitMainRank, pUnitMainRank, pUnitMainRank,
		pUnitMainRank, pUnitMainRank, pKeyPilotMain, pPilotMainLevel, pFaction, pPosX, pPosY, pKeyUnitSub,
		pUnitRankSub, pUnitRankSub, pUnitRankSub, pUnitRankSub, pUnitRankSub,
		pKeyPilotSub, pPilotSubLevel);
}

GameMain::GameMain()
{
	this->map_width = 0LL;
	this->map_height = 0LL;
}

std::string GameMapPath::getPathName() const
{
	return this->path_name;
}

int64_t GameMapPath::getMoveCost() const
{
	return this->move_cost;
}

TerrainAdaptType GameMapPath::getTerrain() const
{
	return this->terrain_adapt;
}

GameMapPath::GameMapPath()
{
	this->move_cost = 1;
	this->terrain_adapt = TerrainAdaptType::GROUND;
}

GameMapPath::GameMapPath(json11::Json raw_data)
{
	this->path_name = raw_data["path_name"].string_value();
	this->move_cost = raw_data["move_cost"].int_value();
	this->terrain_adapt = static_cast<TerrainAdaptType>(raw_data["terrain_type"].int_value());
}
