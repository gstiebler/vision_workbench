/*
 * TimeMeasure.h
 *
 *  Created on: 23 de out de 2016
 *      Author: gstiebler
 */

#ifndef SRC_TIMEMEASURE_H_
#define SRC_TIMEMEASURE_H_

#include <sys/time.h>
#include <string>

class TimeMeasure
{
public:
	TimeMeasure();
	virtual ~TimeMeasure();
	std::string getTime();

private:
	timeval _start;
};

#endif /* SRC_TIMEMEASURE_H_ */
