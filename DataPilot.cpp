#include "DataPilot.h"

float TerrainAdaptCompare::CalculateTerrainAdaptUnitAndPilot(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot)
{
    /*
        E = 0 / D = 1 / C = 2 / B = 3 / A = 4 / S = 5
        計算式: (地形適応ランク指数)×0.25+追加補正
        Sのみ、追加補正あり(-0.05)
        よって、計算上の補正値は以下の通り
        E = 0.00 / D = 0.25 / C = 0.50 / B = 0.75 / A = 1.00 / S = 1.20
    */
    float adaptValUnit = static_cast<float>(static_cast<int>(adaptUnit)) * 0.25f + (adaptUnit == TerrainAdaptValue::S ? -0.05f : 0);
    float adaptValPilot = static_cast<float>(static_cast<int>(adaptPilot)) * 0.25f + (adaptPilot == TerrainAdaptValue::S ? -0.05f : 0);
    /*
        それぞれの平均値を取る。
    */
    return std::round((adaptValUnit + adaptValPilot) * 100.0f / 2.0f) / 100.0f;
}

TerrainAdaptValue TerrainAdaptCompare::GetTerrainAdaptAverage(TerrainAdaptValue adaptUnit, TerrainAdaptValue adaptPilot)
{
    float adaptValAverageFloat = TerrainAdaptCompare::CalculateTerrainAdaptUnitAndPilot(adaptUnit, adaptPilot);
    TerrainAdaptValue adaptValAverageResult = TerrainAdaptValue::E;
    if (adaptValAverageFloat > 0.125f) adaptValAverageResult = TerrainAdaptValue::D;
    if (adaptValAverageFloat > 0.375f) adaptValAverageResult = TerrainAdaptValue::C;
    if (adaptValAverageFloat > 0.625f) adaptValAverageResult = TerrainAdaptValue::B;
    if (adaptValAverageFloat > 0.875f) adaptValAverageResult = TerrainAdaptValue::A;
    if (adaptValAverageFloat > 1.0f) adaptValAverageResult = TerrainAdaptValue::S;
    return adaptValAverageResult;
}
