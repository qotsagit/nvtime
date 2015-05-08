#include "nvtime.h"
#include "stdlib.h"
#include <stdio.h>

uint8_t month_days_count[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

bool is_leap(uint16_t v)
{
	return ((v%4 == 0 && v%100 != 0) || v%400 == 0);
}

uint32_t days_y(uint8_t v, uint16_t year)
{
	uint32_t days = 0;
	
	while(v)
	{
		if(is_leap(year - v))
			days+=LEAP_YEAR_DAYS;
		else
			days+=YEAR_DAYS;
		v--;
	}
	
	return days;
}

uint16_t days_m(uint8_t v, uint8_t leap_offset)
{
	uint16_t days = leap_offset;
	while(v--) 
		days+=month_days_count[v];
	
	return days;
}

uint32_t year(uint32_t *v)
{
	uint32_t year = START_YEAR;
	
	while(*v >= YEAR_DAYS)
	{
		if(is_leap(year))
			*v-=LEAP_YEAR_DAYS;
		else
			*v-=YEAR_DAYS;
		year++;
	}
	
	return year;
}

uint8_t month(uint32_t *v)
{
	uint8_t month = 0;
	while(*v >= month_days_count[month])
	{
		*v-= month_days_count[month];
		month++;
	}

	return month + 1;
}

uint32_t nvtimestampoffset()
{
	return START_OFFSET;
}

//DD,MM,YYYY //hhmmss
#ifdef WITH_TIME
uint32_t nvtimestamp(uint8_t *date, uint8_t *time)
#else
uint32_t nvtimestamp(uint8_t *date)
#endif
{
	uint8_t cDD[2];	cDD[0] = date[0];	cDD[1] = date[1];
	uint8_t cMM[2];	cMM[0] = date[3];	cMM[1] = date[4];
	uint8_t cYY[4];	cYY[0] = date[6];	cYY[1] = date[7];	cYY[2] = date[8];	cYY[3] = date[9];
#ifdef WITH_TIME	
	uint8_t chh[2];	chh[0] = time[0];	chh[1] = time[1];
	uint8_t cmm[2];	cmm[0] = time[2];	cmm[1] = time[3];
	uint8_t css[2];	css[0] = time[4];	css[1] = time[5];
#endif		
	uint16_t cY = atoi((const char*)cYY);
	uint8_t Y = cY - START_YEAR;
	uint8_t M = atoi((const char*)cMM) - 1;
	uint8_t D = atoi((const char*)cDD) - 1;

#ifdef WITH_TIME
	uint8_t h = atoi((const char*)chh);
	uint8_t m = atoi((const char*)cmm);
	uint8_t s = atoi((const char*)css);
#endif
	uint32_t ydays = days_y(Y,cY);

	uint8_t leap_offset = 0;
	if(is_leap(cY) && M > 1) //is current year leap ?
		leap_offset = 1;

	uint16_t mdays = days_m(M,leap_offset);
	ydays = ydays + mdays + D;

#ifdef WITH_TIME
	return (ydays * SECONDS_IN_DAY) + (h * SECONDS_IN_HOUR) + (m * SECONDS_IN_MINUTE) + s;
#else
	return (ydays * SECONDS_IN_DAY);
#endif

}

void nvdatetime(uint32_t timestamp, nvtime_t *v)
{
	uint32_t days	 = timestamp / SECONDS_IN_DAY;
	uint32_t seconds = timestamp % SECONDS_IN_DAY;
	v->Y = year(&days);
	
	if(is_leap(v->Y))
		days+=1;
		
	v->M = month(&days);
	v->D = days + 1;
	
	v->h = seconds / SECONDS_IN_HOUR;
	seconds = seconds % SECONDS_IN_HOUR;
	v->m = seconds / SECONDS_IN_MINUTE;
	seconds = seconds % SECONDS_IN_MINUTE;
	v->s  = seconds;
	
}