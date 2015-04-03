#include "stdint.h"
#define START_YEAR			2015
#define LEAP_YEAR_DAYS		366
#define YEAR_DAYS			365
#define SECONDS_IN_DAY		86400
#define SECONDS_IN_HOUR		3600
#define SECONDS_IN_MINUTE	60


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
uint32_t nvtimestamp(uint8_t *date, uint8_t *time);
#else
uint32_t nvtimestamp(uint8_t *date);
#endif
void nvdatetime(uint32_t timestamp, nvtime_t *v);