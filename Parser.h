#pragma once
#include <exception>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <numeric>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <ios>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include <openssl/evp.h>
#include <openssl/aes.h>

#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4996)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

#include <DxLib.h>

#include "all_loaders.h"
#include "ResourceLoader.h"
#include "strconv2.h"
#include "main.h"
#include "Pilots.h"
#include "Units.h"
#include "UtilGameContents.h"
#include "json11.hpp"

using namespace std;
/* DROPBOX/JSON11 LIBRARIES */
using namespace json11;

namespace TREx {
	struct DictDataEnviroment;
	enum class EnumMagicalElement : uint64_t;
	enum class EnumTerrainAdaptionType : uint64_t;
	enum class EnumTerrainAdaptionRank : uint64_t;
	class JSONParser;

	enum class EnumGender : uint64_t;
	enum class EnumPilotPersonality : uint64_t;
	enum class EnumSpecies : uint64_t;
	enum class EnumPilotStatusInitials : uint64_t;
	enum class EnumSpecificSkills : int64_t;

	class DataSpecies;
	class SpecificSkill;
	class SpiritualPower;
	class SpiritualPowerEffect;
	class ActiveConditionSS;
	class DataSpiritualEffect;
	class DataPilot;
	class GamePilot;

	class DataUnit;
	class GameUnit;

	/* -- begin class: JSONParser -- */

	/// <summary>
	/// JSONをパーシングするためのクラスです。
	/// </summary>
	class JSONParser {
	protected:
		string jaJPLangUrl;
		string enUSLangUrl;
		string pilotDatUrl;
		string unitDatUrl;
		string speciesDatUrl;
		Json parsedJaJPLangJSON;
		Json parsedEnUSLangJSON;
		Json parsedPilotDatJSON;
		Json parsedUnitDatJSON;
		Json parsedSpeciesDatJSON;
	public:
		Json ParseJson(string fileUrl) const {
			ifstream ifs(fileUrl);
			if (!ifs) throw exception("File not exist.");
			string err, ifsstr((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
			Json TempJson = Json::parse(ifsstr, err, COMMENTS);
			if (!err.empty()) throw exception("Illegal JSON");
			return TempJson;
		}
		JSONParser();
	};

	inline JSONParser::JSONParser() {
		this->jaJPLangUrl = R"(.\Resources\datas\localization\ja_jp.json)";
		this->enUSLangUrl = R"(.\Resources\datas\localization\en_us.json)";
		this->pilotDatUrl = R"(.\Resources\datas\datapacks\pilot.json)";
		this->unitDatUrl = R"(.\Resources\datas\datapacks\unit.json)";
		this->speciesDatUrl = R"(.\Resources\datas\datapacks\species.json)";
		this->parsedJaJPLangJSON = this->ParseJson(this->jaJPLangUrl);
		this->parsedPilotDatJSON = this->ParseJson(this->pilotDatUrl);
		this->parsedSpeciesDatJSON = this->ParseJson(this->speciesDatUrl);
	}
	/* -- end class: JSONParser -- */
}

using namespace TREx;
