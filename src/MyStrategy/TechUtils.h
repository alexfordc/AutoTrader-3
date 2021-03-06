#ifndef TECH_UTILS_H
#define TECH_UTILS_H

#include "stdafx.h"
#include <list>
#include <vector>

class TickWrapper;
class KData;

class TechUtils
{
public:
	TechUtils();
	~TechUtils();

	static double CalulateMA(const std::vector<TickWrapper>& data, const TickWrapper& current, size_t seconds);
	static double CalulateEMA(const std::vector<TickWrapper>& data, const TickWrapper& current, size_t seconds);
	static double CalulateWMA(const std::vector<TickWrapper>& data, const TickWrapper& current, size_t seconds);
	static double CalulateAMA(const std::vector<TickWrapper>& data, const TickWrapper& current, size_t seconds);

	static double CalulateMA(const std::vector<KData>& data, const KData& current, size_t mins);
	static double CalulateEMA(const std::vector<KData>& data, const KData& current, size_t mins);
	static double CalulateWMA(const std::vector<KData>& data, const KData& current, size_t mins);
	static double CalulateAMA(const std::vector<KData>& data, const KData& current, size_t mins);
};

#endif