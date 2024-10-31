#include "trex_wrapper.h"

json11::Json ResourceLoader::getLangFile(std::string langKey)
{
	return this->langFiles.at(langKey);
}

DataSkillPilot* ResourceLoader::getPilotSkill(std::string skillKey)
{
	return this->pilotSkillDatabase.at(skillKey);
}

ResourceLoader::ResourceLoader()
{
	this->pilotSkillKeybind = {
		//name
		{ "contents.specific-skills.id_00000000.name", "Attacker" },
		{ "contents.specific-skills.id_00000001.name", "InFight" },
		{ "contents.specific-skills.id_00000002.name", "GunFight" },
		{ "contents.specific-skills.id_00000003.name", "MagicBurst" },
		{ "contents.specific-skills.id_00000004.name", "StrongFortune" },
		{ "contents.specific-skills.id_00000005.name", "Commander" },
		{ "contents.specific-skills.id_00000006.name", "Genius" },
		{ "contents.specific-skills.id_00000007.name", "Psychokinesis" },
		{ "contents.specific-skills.id_00000008.name", "Prediction" },
		{ "contents.specific-skills.id_00000009.name", "Lucky" },
		{ "contents.specific-skills.id_0000000a.name", "SPRegeneration" },
		{ "contents.specific-skills.id_0000000b.name", "CoverAttack" },
		{ "contents.specific-skills.id_0000000c.name", "CoverDefence" },
		{ "contents.specific-skills.id_0000000d.name", "Counterattack" },
		{ "contents.specific-skills.id_0000000e.name", "Potentiality" },
		{ "contents.specific-skills.id_0000000f.name", "ContinuousAttack" },
		{ "contents.specific-skills.id_00000010.name", "SPUp" },
		{ "contents.specific-skills.id_00000011.name", "Guard" },
		{ "contents.specific-skills.id_00000012.name", "Forsake" },
		{ "contents.specific-skills.id_00000013.name", "MoraleLimitbreak" },
		{ "contents.specific-skills.id_00000014.name", "SecondAttack" },
		{ "contents.specific-skills.id_00000015.name", "FocusedAttack" },
		{ "contents.specific-skills.id_00000016.name", "HitAndAway" },
		{ "contents.specific-skills.id_00000017.name", "Revenge" },
		{ "contents.specific-skills.id_00000018.name", "CoordinatedAttack" },
		{ "contents.specific-skills.id_00000019.name", "SequentialAction" },
		{ "contents.specific-skills.id_0000001a.name", "ActivateMaximumBreak" },
		{ "contents.specific-skills.id_0000001b.name", "IncreaseMoraleDefence" },
		{ "contents.specific-skills.id_0000001c.name", "IncreaseMoraleAttack" },
		{ "contents.specific-skills.id_0000001d.name", "IncreaseMoraleALL" },
		{ "contents.specific-skills.id_0000001e.name", "HeightenedMorale" },
		{ "contents.specific-skills.id_0000001f.name", "Belligerence" },
		{ "contents.specific-skills.id_00000020.name", "RepairSkills" },
		{ "contents.specific-skills.id_00000021.name", "SupplySkills" },
		{ "contents.specific-skills.id_00000022.name", "BulletSave" },
		{ "contents.specific-skills.id_00000023.name", "EnergySave" },
		{ "contents.specific-skills.id_00000024.name", "QuickeningDynamis" },
		//desc
		{ "contents.specific-skills.id_00000000.desc", "Attacker" },
		{ "contents.specific-skills.id_00000001.desc", "InFight" },
		{ "contents.specific-skills.id_00000002.desc", "GunFight" },
		{ "contents.specific-skills.id_00000003.desc", "MagicBurst" },
		{ "contents.specific-skills.id_00000004.desc", "StrongFortune" },
		{ "contents.specific-skills.id_00000005.desc", "Commander" },
		{ "contents.specific-skills.id_00000006.desc", "Genius" },
		{ "contents.specific-skills.id_00000007.desc", "Psychokinesis" },
		{ "contents.specific-skills.id_00000008.desc", "Prediction" },
		{ "contents.specific-skills.id_00000009.desc", "Lucky" },
		{ "contents.specific-skills.id_0000000a.desc", "SPRegeneration" },
		{ "contents.specific-skills.id_0000000b.desc", "CoverAttack" },
		{ "contents.specific-skills.id_0000000c.desc", "CoverDefence" },
		{ "contents.specific-skills.id_0000000d.desc", "Counterattack" },
		{ "contents.specific-skills.id_0000000e.desc", "Potentiality" },
		{ "contents.specific-skills.id_0000000f.desc", "ContinuousAttack" },
		{ "contents.specific-skills.id_00000010.desc", "SPUp" },
		{ "contents.specific-skills.id_00000011.desc", "Guard" },
		{ "contents.specific-skills.id_00000012.desc", "Forsake" },
		{ "contents.specific-skills.id_00000013.desc", "MoraleLimitbreak" },
		{ "contents.specific-skills.id_00000014.desc", "SecondAttack" },
		{ "contents.specific-skills.id_00000015.desc", "FocusedAttack" },
		{ "contents.specific-skills.id_00000016.desc", "HitAndAway" },
		{ "contents.specific-skills.id_00000017.desc", "Revenge" },
		{ "contents.specific-skills.id_00000018.desc", "CoordinatedAttack" },
		{ "contents.specific-skills.id_00000019.desc", "SequentialAction" },
		{ "contents.specific-skills.id_0000001a.desc", "ActivateMaximumBreak" },
		{ "contents.specific-skills.id_0000001b.desc", "IncreaseMoraleDefence" },
		{ "contents.specific-skills.id_0000001c.desc", "IncreaseMoraleAttack" },
		{ "contents.specific-skills.id_0000001d.desc", "IncreaseMoraleALL" },
		{ "contents.specific-skills.id_0000001e.desc", "HeightenedMorale" },
		{ "contents.specific-skills.id_0000001f.desc", "Belligerence" },
		{ "contents.specific-skills.id_00000020.desc", "RepairSkills" },
		{ "contents.specific-skills.id_00000021.desc", "SupplySkills" },
		{ "contents.specific-skills.id_00000022.desc", "BulletSave" },
		{ "contents.specific-skills.id_00000023.desc", "EnergySave" },
		{ "contents.specific-skills.id_00000024.desc", "QuickeningDynamis" }
	};
	namespace fs = std::filesystem;
	fs::path data_path = fs::current_path();
	data_path += "/Resources/datas";
	fs::path datapack_path = data_path;
	datapack_path += "/datapacks";
	fs::path locale_path = data_path;
	locale_path += "/localization";
	AppLogAdd("Initialize Resource Loader:\n");
	ErrorLogTabAdd();
	for (const fs::directory_entry &entry : fs::directory_iterator(locale_path)) {
		if (entry.path().extension() == ".json") {
			AppLogAdd(std::string("Target JSON File: " + fs::absolute(entry.path()).string() + "\n").c_str());
			std::ifstream ifs(fs::absolute(entry.path()));
			if (!ifs) {
				ErrorLogAdd("Could not Open Files.\n");
				continue;
			}
			std::ostringstream oss;
			oss << ifs.rdbuf();
			std::string str = oss.str();
			std::string raw_json;
			if (str.size() >= 3 && str[0] == -17 && str[1] == -69 && str[2] == -65) raw_json = str.substr(3);
			else raw_json = str;
			std::string raw_sjis_json = utf8_to_sjis(raw_json);
			std::string err;
			json11::Json JsonData = json11::Json::parse(raw_sjis_json, err, json11::JsonParse::COMMENTS);
			if (!err.empty()) {
				ErrorLogAdd(string(err + "\n").c_str());
				continue;
			}
			std::string language_key = JsonData["lang_pack"]["language"].string_value();
			json11::Json language_value = JsonData["lang_pack"]["localize"];
			this->langFiles.insert_or_assign(language_key, language_value);
		}
	}
	AppLogAdd("Initialize Skill Database:\n");
	std::map<std::string, std::pair<std::string, std::string>> targetKey;
	for (std::pair<std::string, json11::Json> langJsonFile : this->langFiles) {
		for (json11::Json::object::const_iterator iterator = langJsonFile.second.object_items().begin();
				iterator != langJsonFile.second.object_items().end();) {
			std::pair<std::string, json11::Json> langData(iterator->first, iterator->second);
			std::string skillId;
			std::string skillUnlocalizedName;
			std::string skillUnlocalizedDesc;
			AppLogAdd(sjis_to_utf8("Finding key " + langData.first + "\n").c_str());
			if (this->pilotSkillKeybind.count(langData.first) == 0) {
				iterator++;
				continue;
			}
			if (langData.second.is_array()) {
				skillUnlocalizedDesc = langData.first;
				iterator++;
				langData = std::pair<std::string, json11::Json>(iterator->first, iterator->second);
			}
			if (langData.second.is_string()) {
				skillId = this->pilotSkillKeybind.at(langData.first);
				skillUnlocalizedName = langData.first;
				iterator++;
			}
			std::stringstream ss;
			ss << "SkillId: " << skillId << ", SkillName: " << skillUnlocalizedName
				<< ", SkillDesc: " << skillUnlocalizedDesc << std::endl;
			AppLogAdd(sjis_to_utf8(ss.str()).c_str());
			if (!skillId.empty() && !skillUnlocalizedName.empty() && !skillUnlocalizedDesc.empty()) {
				targetKey.insert_or_assign(skillId, 
					std::pair<std::string, std::string>(skillUnlocalizedName, skillUnlocalizedDesc));
			}
		}
	}
	for (std::pair<std::string, std::pair<std::string, std::string>> detected : targetKey) {
		if (detected.first.compare("Attacker")) {
			this->pilotSkillDatabase.insert_or_assign(detected.first,
				new DataSkillAttacker(detected.second.first, detected.second.second, this->langFiles));
		}
		else {
			//デバッグ時の一時保管用
			this->pilotSkillDatabase.insert_or_assign(detected.first,
				new DataSkillDummy(detected.second.first, detected.second.second, this->langFiles));
		}
	}
	ErrorLogTabSub();
}
