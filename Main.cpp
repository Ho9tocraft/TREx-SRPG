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
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (!game_main->stage_loaded) {
			json11::Json stageData = game_loader->parseResource(game_loader->loadPath(LoaderHandlerType::DATA_STAGES, "stage_001.json"));
			game_main->setStageMap(stageData);
			game_main->stage_loaded = true;
		}
		ClearDrawScreen();
		game_main->eventOnTurn();
		game_main->DrawStageGraph(windowWidth, windowHeight);
		ScreenFlip();
	}
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
	json11::Json area_properties = raw_data["stage_data"]["area_properties"];
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
	json11::Json path_data = raw_data["stage_data"]["path_data"];
	for (auto& terrainY : terrain_data_index) {
		std::vector<std::pair<bool, GameMapPath>> prefetch_terrain;
		for (auto& terrainX : terrainY) {
			prefetch_terrain.push_back(std::make_pair(false, GameMapPath(path_data[terrainX])));
		}
		this->stageMap.push_back(prefetch_terrain);
	}
	json11::Json stageInfo = raw_data["stage_data"]["stage_info"];
	{
		auto& eventCreateLaunch = stageInfo["create_launch"].array_items();
		for (auto& evData : eventCreateLaunch) {
			uint64_t eventTurn = stoull(evData["event_turn"].string_value());
			this->eventTurns.insert_or_assign(eventTurn, evData);
			this->isInitialized.insert_or_assign(eventTurn, std::map<GameFaction, bool>{
				{ GameFaction::NOT_CREATED, false },
				{ GameFaction::PLAYER, false },
				{ GameFaction::ENEMY_1, false },
				{ GameFaction::ENEMY_2, false },
				{ GameFaction::ALLY, false }
			});
		}
		this->operation_condition = stageInfo["operation_condition"];
		json11::Json bgm = stageInfo["background_music"];
		if (bgm["common"].is_string()) this->map_soundhandler = LoadSoundMem(
			game_loader->loadPath(LoaderHandlerType::AUDIO, sjis_to_utf8(bgm["common"].string_value())).c_str());
		ChangeVolumeSoundMem(255 * 40 / 100, this->map_soundhandler);
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

void GameMain::eventOnTurn()
{
	if (this->isInitialized.contains(this->map_round) && !this->isInitialized.at(this->map_round).at(this->map_phase)) {
		json11::Json& incStRound = this->eventTurns.at(this->map_round);
		GameFaction tgtPhase = static_cast<GameFaction>(incStRound["event_phase"].int_value());
		if (this->map_phase == tgtPhase || this->map_round == 0ULL) {
			json11::Json::array popEntity = incStRound["event_pop"].array_items();
			for (auto& entity : popEntity) {
				std::string tMainUnit = sjis_to_utf8(entity["main_unit_unit_name"].string_value());
				std::string tMainPilot = sjis_to_utf8(entity["main_unit_main_pilot_name"].string_value());
				std::string tSubUnit = sjis_to_utf8(entity["sub_unit_unit_name"].string_value());
				std::string tSubPilot = sjis_to_utf8(entity["sub_unit_main_pilot_name"].string_value());
				int64_t tMainLevel = static_cast<int64_t>(entity["main_unit_main_pilot_level"].int_value());
				int64_t tSubLevel = static_cast<int64_t>(entity["sub_unit_main_pilot_level"].int_value());
				int64_t posX = static_cast<int64_t>(entity["troop_posX"].int_value());
				int64_t posY = static_cast<int64_t>(entity["troop_posY"].int_value());
				std::string faction = entity["troop_faction"].string_value();
				if (this->savedUnit.contains(tMainPilot)) {
					using std::regex;
					using std::regex_match;
					using namespace std::regex_constants;
					regex FAC_PLAYER(R"(^味方|プレイヤー|PC)", ECMAScript, icase);
					regex FAC_ENEMY_1(R"(^敵|ENM1)", ECMAScript, icase);
					regex FAC_ENEMY_2(R"(^中立|ENM2)", ECMAScript, icase);
					regex FAC_NPC(R"(^NPC|ノンプレイヤー)", ECMAScript, icase);
					int tmpFact_index = regex_match(faction, FAC_PLAYER) ? 1 : regex_match(faction, FAC_ENEMY_1) ? 2 :
						regex_match(faction, FAC_ENEMY_2) ? 3 : regex_match(faction, FAC_NPC) ? 4 : 4;
					if (!tSubPilot.empty() && this->savedUnit.contains(tSubPilot)) {
						this->LaunchUnitFromSaveData(tMainPilot, posX, posY, 
							tSubPilot, static_cast<GameFaction>(tmpFact_index));
					}
					else if (tSubPilot.empty()) {
						this->LaunchUnitFromSaveData(tMainPilot, posX, posY, 
							"", static_cast<GameFaction>(tmpFact_index));
					}
				}
				else {
					int64_t rankMainAll = entity["main_unit_unit_rank"].is_number() ?
						static_cast<int64_t>(entity["main_unit_unit_rank"].int_value()) : 0LL;
					int64_t rankMainHP = rankMainAll,
						rankMainEN = rankMainAll,
						rankMainArmor = rankMainAll,
						rankMainSight = rankMainAll,
						rankMainEvade = rankMainAll;
					json11::Json column_modify;
					if (entity["main_unit_unit_rank"].is_object()) {
						column_modify = entity["main_unit_unit_rank"];
						rankMainHP = static_cast<int64_t>(column_modify["HP"].int_value());
						rankMainEN = static_cast<int64_t>(column_modify["EN"].int_value());
						rankMainArmor = static_cast<int64_t>(column_modify["AMR"].int_value());
						rankMainSight = static_cast<int64_t>(column_modify["SIG"].int_value());
						rankMainEvade = static_cast<int64_t>(column_modify["EVA"].int_value());
					}
					if (!tSubPilot.empty() && !this->savedUnit.contains(tSubPilot)) {
						int64_t rankSubAll = entity["sub_unit_unit_rank"].is_number() ?
							static_cast<int64_t>(entity["sub_unit_unit_rank"].int_value()) : 0LL;
						int64_t rankSubHP = rankSubAll,
							rankSubEN = rankSubAll,
							rankSubArmor = rankSubAll,
							rankSubSight = rankSubAll,
							rankSubEvade = rankSubAll;
						if (entity["sub_unit_unit_rank"].is_object()) {
							column_modify = entity["sub_unit_unit_rank"];
							rankSubHP = static_cast<int64_t>(column_modify["HP"].int_value());
							rankSubEN = static_cast<int64_t>(column_modify["EN"].int_value());
							rankSubArmor = static_cast<int64_t>(column_modify["AMR"].int_value());
							rankSubSight = static_cast<int64_t>(column_modify["SIG"].int_value());
							rankSubEvade = static_cast<int64_t>(column_modify["EVA"].int_value());
						}
						this->CreateUnitByFaction(tMainUnit, rankMainHP, rankMainEN,
							rankMainArmor, rankMainSight, rankMainEvade, tMainPilot,
							tMainLevel, faction, posX, posY, tSubUnit, rankSubHP,
							rankSubEN, rankSubArmor, rankSubSight, rankSubEvade,
							tSubPilot, tSubLevel);
					}
					else if (tSubPilot.empty()) {
						this->CreateUnitByFaction(tMainUnit, rankMainHP, rankMainEN,
							rankMainArmor, rankMainSight, rankMainEvade,
							tMainPilot, tMainLevel, faction, posX, posY);
					}
				}
			}
			this->isInitialized.at(this->map_round).insert_or_assign(this->map_phase, true);
			if (this->map_round == 0ULL) {
				this->isInitialized.at(this->map_round).insert_or_assign(GameFaction::PLAYER, true);
				this->isInitialized.at(this->map_round).insert_or_assign(GameFaction::ENEMY_1, true);
				this->isInitialized.at(this->map_round).insert_or_assign(GameFaction::ENEMY_2, true);
				this->isInitialized.at(this->map_round).insert_or_assign(GameFaction::ALLY, true);
				this->SequenceIncreaseTurn();
			}
			if (CheckSoundMem(this->map_soundhandler) == 0) PlaySoundMem(this->map_soundhandler, DX_PLAYTYPE_LOOP);
		}
	}
}

void GameMain::LaunchUnitFromSaveData(std::string pKeyPilotMain, int64_t pPosX, int64_t pPosY, std::string pKeyPilotSub, GameFaction pFaction)
{
	//既出チェック(セーブデータにない場合は除外)
	if (!this->savedUnit.contains(pKeyPilotMain) || (!pKeyPilotSub.empty() && !this->savedUnit.contains(pKeyPilotSub))) return;
	std::shared_ptr<GameUnit> tmpUnitMain = this->savedUnit.at(pKeyPilotMain);
	std::shared_ptr<GameTroop> tmpTroop;
	if (!pKeyPilotSub.empty()) {
		std::shared_ptr<GameUnit> tmpUnitSub = this->savedUnit.at(pKeyPilotSub);
		tmpTroop = std::make_shared<GameTroop>(tmpUnitMain, tmpUnitSub);
	}
	else tmpTroop = std::make_shared<GameTroop>(tmpUnitMain);
	tmpTroop->launchUnit(pPosX, pPosY, pFaction);
}

void GameMain::CreateUnitByFaction(std::string pKeyUnitMain, int64_t pUnitMainRankHP, int64_t pUnitMainRankEN, int64_t pUnitMainRankArmor,
	int64_t pUnitMainRankSight, int64_t pUnitMainRankEvade, std::string pKeyPilotMain, int64_t pPilotMainLevel, std::string pFaction,
	int64_t pPosX, int64_t pPosY, std::string pKeyUnitSub, int64_t pUnitSubRankHP, int64_t pUnitSubRankEN, int64_t pUnitSubRankArmor,
	int64_t pUnitSubRankSight, int64_t pUnitSubRankEvade, std::string pKeyPilotSub, int64_t pPilotSubLevel)
{
	//既出チェック
	//雑魚はもれなくfalseとなるので無視される
	if (this->generatedPilot[pKeyPilotMain] || this->generatedPilot[pKeyPilotSub]) return;
	//また、セーブファイルにある場合も無視
	if (this->savedUnit.contains(pKeyPilotMain) || this->savedUnit.contains(pKeyPilotSub)) return;
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

void GameMain::SequenceIncreaseTurn()
{
	if (this->map_round == 0ULL) {
		this->map_phase = GameFaction::PLAYER;
		this->map_round++;
	}
	else {
		int stackCheck = 0;
		int current_phase = static_cast<int>(this->map_phase);
		GameFaction moved_to_phase = this->map_phase;
		do {
			if (stackCheck == 8) break; //スタックオーバーフロー対策
			if (moved_to_phase != GameFaction::ALLY) {
				current_phase++;
				moved_to_phase = static_cast<GameFaction>(current_phase);
			}
			else {
				moved_to_phase = GameFaction::PLAYER;
			}
			stackCheck++;
		}
		while (!this->foundFaction(moved_to_phase));
	}
}

bool GameMain::foundFaction(GameFaction faction)
{
	uint64_t countTroop = 0ULL;
	for (auto& tmpTroop : this->troopList) {
		if (tmpTroop->getFaction() == faction) countTroop++;
	}
	return countTroop > 0ULL;
}

GameMain::GameMain()
{
	this->stage_loaded = false;
	this->map_width = 0LL;
	this->map_height = 0LL;
	this->map_round = 0ULL;
	this->map_phase = GameFaction::NOT_CREATED;
	this->map_soundhandler = 0;
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
