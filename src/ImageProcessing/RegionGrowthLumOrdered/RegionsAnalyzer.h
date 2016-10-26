/*
 * RegionsAnalyzer.h
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSANALYZER_H_
#define SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSANALYZER_H_

#include <vector>

class RegionsManager;

class RegionsAnalyzer
{
public:
	RegionsAnalyzer(int height);
	virtual ~RegionsAnalyzer();

	void analyze(RegionsManager &regions);

	std::vector<int> heightHistogram;

private:
};

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSANALYZER_H_ */
