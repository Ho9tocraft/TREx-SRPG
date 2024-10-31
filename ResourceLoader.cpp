#include "trex_wrapper.h"

DataSkillPilot* ResourceLoader::getPilotSkill(std::string skillKey)
{
	return this->pilotSkillDatabase.at(skillKey);
}

ResourceLoader::ResourceLoader()
{
	namespace fs = std::filesystem;
	fs::path data_path = fs::current_path();
	data_path += "/Resources/datas";
	fs::path datapack_path = data_path;
	datapack_path += "/datapacks";
	fs::path locale_path = data_path;
	locale_path += "/localization";
	AppLogAdd("Initialize Resource Loader");
	ErrorLogTabAdd();
	for (const fs::directory_entry &entry : fs::directory_iterator(locale_path)) {
		if (entry.path().extension() == ".json") {
			AppLogAdd(std::string("Target JSON File: " + fs::absolute(entry.path()).string() + "\n").c_str());
			std::wifstream ifs(fs::absolute(entry.path()));
			if (!ifs.bad()) {
				ifs.imbue(std::locale("", LC_CTYPE));
				std::wostringstream woss;
				woss << ifs.rdbuf();
				std::string str = wide_to_utf8(woss.str());
				std::string raw_json;
				if (str.size() >= 3 && str[0] == -17 && str[1] == -69 && str[2] == -65) raw_json = str.substr(3);
				else raw_json = str;
				AppLogAdd(string(raw_json + "\n").c_str());
				std::string err;
				json11::Json JsonData = json11::Json::parse(raw_json, err, json11::JsonParse::COMMENTS);
				if (!err.empty()) {
					ErrorLogAdd(string(err + "\n").c_str());
				}
			}
		}
	}
	ErrorLogTabSub();
}
