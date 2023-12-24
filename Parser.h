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
	enum class EnumMagicalElement : uint64_t;
	enum class EnumTerrainAdaptionType : uint64_t;
	enum class EnumTerrainAdaptionRank : uint64_t;
	class JSONParser;

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
		Json parsedJaJPLangJSON;
		Json parsedEnUSLangJSON;
		Json parsedPilotDatJSON;
		Json parsedUnitDatJSON;
	public:
		Json ParseJson(string langUrl) const {
			ifstream ifs(langUrl);
			string err, ifsstr((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
			Json TempJson = Json::parse(ifsstr, err, COMMENTS);
			if (!err.empty()) throw exception("Illegal JSON");
			return TempJson;
		}
		JSONParser();
	};

	JSONParser::JSONParser() {
		this->jaJPLangUrl = R"(.\Resources\datas\localization\ja_jp.json)";
		this->enUSLangUrl = R"(.\Resources\datas\localization\en_us.json)";
	}
	/* -- end class: JSONParser -- */
}

using namespace TREx;
