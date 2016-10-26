/*
 * RegionsPainter.h
 *
 *  Created on: 26 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSPAINTER_H_
#define SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSPAINTER_H_

#include <opencv2/opencv.hpp>
#include <vector>

class Region;

void paintByHeight(std::vector<Region*> &regions, cv::Mat &dstImg);

#endif /* SRC_IMAGEPROCESSING_REGIONGROWTHLUMORDERED_REGIONSPAINTER_H_ */
