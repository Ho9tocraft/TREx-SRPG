#include "stdafx.h"
#include "DataPilot.h"

DPilotGenderType ConvertToGenderType(int from)
{
	return static_cast<DPilotGenderType>(from);
}

DPilotGenderType ConvertToGenderType(std::string from)
{
	using std::regex;
	using std::regex_match;
	using namespace std::regex_constants;
	regex rgxMan(R"(^(Man|Gentleman|Male|Guy|Boy))", ECMAScript, icase);
	regex rgxJpMan(R"(^((性別)?：?男性?))", ECMAScript);
	regex rgxWoman(R"(^(Woman|Lady|Girl|Female))", ECMAScript, icase);
	regex rgxJpWoman(R"(^((性別)?：?女性?))", ECMAScript);
	regex rgxNomale(R"(^(Nomale|Asexual|Insexual))", ECMAScript, icase);
	regex rgxJpNomale(R"(^((性別)?：?(なし|無性)))", ECMAScript);
	regex rgxMachine(R"(^(Machine|Unfeel))", ECMAScript, icase);
	regex rgxJpMachine(R"(^((性別)?：?機械))", ECMAScript);
	//エラー対策のため、デフォルト値に無性を設定
	int convert_sample_value = regex_match(from, rgxMan) || regex_match(from, rgxJpMan) ? 0 :
		regex_match(from, rgxWoman) || regex_match(from, rgxJpWoman) ? 1 :
		regex_match(from, rgxNomale) || regex_match(from, rgxJpNomale) ? 2 :
		regex_match(from, rgxMachine) || regex_match(from, rgxJpMachine) ? 3 : 2; 
	return ConvertToGenderType(convert_sample_value);
}

DPilotPersonalityType ConvertToPersonalityType(int from)
{
	return static_cast<DPilotPersonalityType>(from);
}

DPilotPersonalityType ConvertToPersonalityType(std::string from)
{
	using std::regex;
	using std::regex_match;
	using namespace std::regex_constants;
	regex rgxBullish(R"(^(Bullish|強気))", ECMAScript, icase);
	regex rgxVeryBullish(R"(^(VeryBullish|VBullish|超強気))", ECMAScript, icase);
	regex rgxSerenity(R"(^(Serenity|冷静))", ECMAScript, icase);
	regex rgxPrudent(R"(^(Prudent|慎重))", ECMAScript, icase);
	regex rgxOptimist(R"(^(Optimist|楽天家))", ECMAScript, icase);
	regex rgxHardworker(R"(^(Hardworker|努力家))", ECMAScript, icase);
	regex rgxImpatient(R"(^(Impatient|短気))", ECMAScript, icase);
	regex rgxSuperfluous(R"(^(Superfluous|Bigwig|大物)", ECMAScript, icase);
	regex rgxVerySuperfluous(R"(VerySuperfluous|VeryBigwig|VSuperfluous|VBigwig|超大物)", ECMAScript, icase);
	regex rgxGuileful(R"(Guileful|狡猾)", ECMAScript, icase);
	regex rgxViolence(R"(Violence|残虐)", ECMAScript, icase);
	regex rgxRemnantFire(R"(Remnant(Fire)?|Ember|残影)", ECMAScript, icase);
	regex rgxRefulgence(R"(Refulgence|光輝)", ECMAScript, icase);
	int convert_sample_value = regex_match(from, rgxBullish) ? 1 : regex_match(from, rgxVeryBullish) ? 2 :
		regex_match(from, rgxSerenity) ? 3 : regex_match(from, rgxPrudent) ? 4 :
		regex_match(from, rgxOptimist) ? 5 : regex_match(from, rgxHardworker) ? 6 :
		regex_match(from, rgxImpatient) ? 7 : regex_match(from, rgxSuperfluous) ? 8 :
		regex_match(from, rgxVerySuperfluous) ? 9 : regex_match(from, rgxGuileful) ? 10 :
		regex_match(from, rgxViolence) ? 11 : regex_match(from, rgxRemnantFire) ? 12 :
		regex_match(from, rgxRefulgence) ? 13 : 0;
	return ConvertToPersonalityType(convert_sample_value);
}

DPilotGrowthType ConvertToGrowthType(int from)
{
	return static_cast<DPilotGrowthType>(from);
}

DPilotGrowthType ConvertToGrowthType(std::string from)
{
	using std::regex;
	using std::regex_match;
	using namespace std::regex_constants;
	regex rgxNormal(R"(^(Normal|標準))", ECMAScript, icase);
	regex rgxMelNormal(R"(Mele?Normal|格闘・?標準)", ECMAScript, icase);
	regex rgxMelAlmighty(R"(Mele?Almighty?|格闘・?万能)", ECMAScript, icase);
	regex rgxMelRangeFoc(R"(Mele?(Foc)?Ra?ng(ed)?|格闘・?射撃(重視)?)", ECMAScript, icase);
	regex rgxMelMagicFoc(R"(Mele?(Foc)?Mag(ic|e)|格闘・?魔力(重視)?)", ECMAScript, icase);
	regex rgxMelDefensive(R"(Mele?Def(ensive)?|格闘・?防御)", ECMAScript, icase);
	regex rgxMelLateBloom(R"(Mele?L(ate)?Bloom|格闘・?晩成)", ECMAScript, icase);
	regex rgxRngNormal(R"(Ra?ng(ed)?Normal|射撃・?標準)", ECMAScript, icase);
	regex rgxRngAlmighty(R"(Ra?ng(ed)?Almighty?|射撃・?万能)", ECMAScript, icase);
	regex rgxRngMeleeFoc(R"(Ra?ng(ed)?(Foc)?Mele?|射撃・?格闘(重視)?)", ECMAScript, icase);
	regex rgxRngMagicFoc(R"(Ra?ng(ed)?(Foc)?Mag(ic|e)|射撃・?魔力(重視)?)", ECMAScript, icase);
	regex rgxRngDefensive(R"(Ra?ng(ed)?(Foc)?Def(ensive)|射撃・?防御)", ECMAScript, icase);
	regex rgxRngLateBloom(R"(Ra?ng(ed)?(Foc)?L(ate)?Bloom|射撃・?晩成)", ECMAScript, icase);
	regex rgxMgcNormal(R"(Mag(ic|e)Normal|魔力・?標準)", ECMAScript, icase);
	regex rgxMgcAlmighty(R"(Mag(ic|e)Almighty?|魔力・?万能)", ECMAScript, icase);
	regex rgxMgcMeleeFoc(R"(Mag(ic|e)(Foc)?Mele?|魔力・?格闘(重視)?)", ECMAScript, icase);
	regex rgxMgcRangeFoc(R"(Mag(ic|e)(Foc)?Ra?ng(ed)?|魔力・?射撃(重視)?)", ECMAScript, icase);
	regex rgxMgcDefensive(R"(Mag(ic|e)(Foc)?Def(ensive)?|魔力・?防御)", ECMAScript, icase);
	regex rgxMgcLateBloom(R"(Mag(ic|e)(Foc)?L(ate)?Bloom|魔力・?晩成)", ECMAScript, icase);
	regex rgxAlmNormal(R"(Almighty?Normal|万能・?標準)", ECMAScript, icase);
	regex rgxAlmLateBloom(R"(Almighty?L(ate)?Bloom|万能・?晩成)", ECMAScript, icase);
	regex rgxSPFocus(R"(SPFoc(us)?|(SP|精神(ポイント)?)重視)", ECMAScript, icase);
	regex rgxSubPilot(R"(Sub(Pilot)?|サブ(パイロット)?)", ECMAScript, icase);
	int convert_sample_value = regex_match(from, rgxNormal) ? 0 : regex_match(from, rgxMelNormal) ? 1 :
		regex_match(from, rgxMelAlmighty)  ?  2 : regex_match(from, rgxMelRangeFoc)  ?  3 :
		regex_match(from, rgxMelMagicFoc)  ?  4 : regex_match(from, rgxMelDefensive) ?  5 :
		regex_match(from, rgxMelLateBloom) ?  6 : regex_match(from, rgxRngNormal)    ?  7 :
		regex_match(from, rgxRngAlmighty)  ?  8 : regex_match(from, rgxRngMeleeFoc)  ?  9 :
		regex_match(from, rgxRngMagicFoc)  ? 10 : regex_match(from, rgxRngDefensive) ? 11 :
		regex_match(from, rgxRngLateBloom) ? 12 : regex_match(from, rgxMgcNormal)    ? 13 :
		regex_match(from, rgxMgcAlmighty)  ? 14 : regex_match(from, rgxMgcMeleeFoc)  ? 15 :
		regex_match(from, rgxMgcRangeFoc)  ? 16 : regex_match(from, rgxMgcDefensive) ? 17 :
		regex_match(from, rgxMgcLateBloom) ? 18 : regex_match(from, rgxAlmNormal)    ? 19 :
		regex_match(from, rgxAlmLateBloom) ? 20 : regex_match(from, rgxSPFocus)      ? 21 :
		regex_match(from, rgxSubPilot)     ? 22 : 0;
	return ConvertToGrowthType(convert_sample_value);
}

double ConvertTerrainAdaptToAdjustValue(TerrainAdaptValue val)
{
	return val == TerrainAdaptValue::E ? 0.0 : val == TerrainAdaptValue::D ? 0.5 : val == TerrainAdaptValue::C ? 0.6 :
		val == TerrainAdaptValue::B ? 0.8 : val == TerrainAdaptValue::S ? 1.2 : 1.0;
}

std::string DPilotProfile::decideGenderDisplayStr(std::string from_value)
{
	std::string result_value = "なし";
	switch (gender_type)
	{
	case DPilotGenderType::MALE:
		result_value = "男";
		break;
	case DPilotGenderType::FEMALE:
		result_value = "女";
		break;
	case DPilotGenderType::NO_MALE:
		result_value = "なし";
		break;
	case DPilotGenderType::MACHINE:
		result_value = "機械";
		break;
	default:
		break;
	}
	return from_value.empty() ? result_value : from_value;
}

std::string DPilotProfile::getFullname() const
{
	return full_name;
}

std::string DPilotProfile::getNickname() const
{
	return nick_name;
}

std::string DPilotProfile::getReadname() const
{
	return read_name;
}

std::string DPilotProfile::getCodename() const
{
	return code_name;
}

DPilotGenderType DPilotProfile::getGenderType() const
{
	return gender_type;
}

std::string DPilotProfile::getGenderDisplayStr() const
{
	return gender_custom_display;
}

DPilotPersonalityType DPilotProfile::getPersonality() const
{
	return personality_type;
}

int DPilotProfile::getDropExp() const
{
	return drop_experience;
}

std::string DPilotProfile::getBgmFile() const
{
	return bgmFile;
}

std::string DPilotProfile::getGraphFile() const
{
	return graphFile;
}

DPilotProfile::DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename,
	DPilotGenderType pGenderType, std::string pGenderDispStr, DPilotPersonalityType pPersonalityType, int pDropExp,
	std::string pBgmFile, std::string pGraphPath)
{
	full_name = pFullname;
	nick_name = pNickname;
	read_name = pReadname;
	code_name = pCodename;
	gender_type = pGenderType;
	gender_custom_display = decideGenderDisplayStr(pGenderDispStr);
	personality_type = pPersonalityType;
	drop_experience = pDropExp;
	bgmFile = pBgmFile;
	graphFile = pGraphPath;
	BgmHandler = -1;
	GraphHandler = -1;
}

DPilotProfile::DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename,
	std::string pGenderType, std::string pGenderDispStr, std::string pPersonalityType, int pDropExp,
	std::string pBgmFile, std::string pGraphPath) :
		DPilotProfile(pFullname, pNickname, pReadname, pCodename, ConvertToGenderType(pGenderType), pGenderDispStr,
			ConvertToPersonalityType(pPersonalityType), pDropExp, pBgmFile, pGraphPath)
{
}

DPilotProfile::DPilotProfile(std::string pFullname, std::string pNickname, std::string pReadname, std::string pCodename,
	int pGenderType, std::string pGenderDispStr, int pPersonalityType, int pDropExp, std::string pBgmFile, std::string pGraphPath) :
		DPilotProfile(pFullname, pNickname, pReadname, pCodename, ConvertToGenderType(pGenderType), pGenderDispStr,
			ConvertToPersonalityType(pPersonalityType), pDropExp, pBgmFile, pGraphPath)
{
}

DPilotProfile::DPilotProfile() : DPilotProfile("", "", "", "", "無性", "", "普通", 0, "", "")
{
	//なんも引数を設定していないときの初期化。なにもしない
}
