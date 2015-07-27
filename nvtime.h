#ifndef __NVTIME_H
#define __NVTIME_H

#include "stdint.h"
#define START_YEAR			2015
#define LEAP_YEAR_DAYS		366
#define YEAR_DAYS			365
#define SECONDS_IN_DAY		86400
#define SECONDS_IN_HOUR		3600
#define SECONDS_IN_MINUTE	60

#define START_OFFSET		1420070400 //2015-01-01 00:00:00

typedef struct nvtime
{
	uint16_t Y;	//year
	uint8_t	M;	//month
	uint8_t D;	//day
	uint8_t h;	//hour
	uint8_t m;	//minute
	uint8_t s;	//second

}nvtime_t;

#if 1
#define WITH_TIME
#endif

#ifdef WITH_TIME
uint32_t nvtimestamp(uint8_t *date, uint8_t *time);	//encode with time
#else
uint32_t nvtimestamp(uint8_t *date);				//encode only date
#endif
uint32_t nvtimestamp(int Y,int M,int D);			//datestamp form Y,M,D

void nvdatetime(uint32_t timestamp, nvtime_t *v);	//decode from timestamp
uint32_t nvtimestampoffset();						//start offset
uint32_t nvtimestamp(uint8_t *time);				// from GPS string only time

#endif