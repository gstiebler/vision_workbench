/*
 * RegionsAnalyzer.cpp
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#include "RegionsAnalyzer.h"
#include "RegionsManager.h"
#include "Region.h"

using namespace std;

RegionsAnalyzer::RegionsAnalyzer(int height) :
		heightHistogram(height)
{
	std::fill(heightHistogram.begin(), heightHistogram.end(), 0);
}

RegionsAnalyzer::~RegionsAnalyzer()
{
}

void RegionsAnalyzer::analyze(RegionsManager &regionsManager)
{
	for(auto &region : regionsManager.regions)
	{
		if(!region->isFinal() || region->id == 0) continue;
		heightHistogram[region->height()]++;
	}
}
