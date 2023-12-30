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
#include "strconv2.h"
#include "main.h"
#include "Pilots.h"
#include "Parser.h"
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

	/// <summary>
	/// データ系の構造体です。
	/// </summary>
	struct DictDataEnviroment {
		JSONParser* jsonParser;
		map<string, DataPilot*> dictDataPilot;

		DictDataEnviroment();
	};

	inline DictDataEnviroment::DictDataEnviroment() {
		this->jsonParser = new JSONParser();
	}

	/// <summary>
	/// 言語分類(ローカライズ)の読み込み用クラスです。
	/// </summary>
	class LanguageHandler {
	protected:
	public:
	};

	/* -- End class: LanguageHandler -- */

	/// <summary>
	/// 画像(イメージ)の読み込み用クラスです。
	/// </summary>
	class ImageHandler {
	protected:
	public:
	};

	class SettingHandler {
	protected:
	public:
	};
}
