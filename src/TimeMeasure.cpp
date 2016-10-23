/*
 * TimeMeasure.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: gstiebler
 */

#include "TimeMeasure.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

TimeMeasure::TimeMeasure()
{
    gettimeofday(&_start, NULL);
}

TimeMeasure::~TimeMeasure()
{
}

string TimeMeasure::getTime()
{
    timeval end;

    long mtime, seconds, useconds;
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - _start.tv_sec;
    useconds = end.tv_usec - _start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    char result[100] = {0};
    sprintf(result, "Elapsed time: %ld milliseconds\n", mtime);
    return result;
}
