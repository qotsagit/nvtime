#include <stdio.h>
#include <string>
#include <iostream>
#include "stdint.h"
#include "nvtime.h"

void main()
{	
	//DDMMYYYY //HHMMSS

	uint8_t *date=(uint8_t*)"31,10,2150";
	uint8_t *time=(uint8_t*)"000000";

#ifdef WITH_TIME
	uint32_t t = nvtimestamp(date,time);
#else	
	uint32_t t = nvtimestamp(date);
#endif

	fprintf(stderr,"%s\n",date);
	fprintf(stderr,"%u\n",t);
	
	nvtime_t a;
	nvdatetime(t, &a);
	
	uint32_t b = nvtimestamp(2150,10,31);

	fprintf(stderr,"%u\n%u\n",b,b+1420070400);
	
	fprintf(stderr,"%02d-%02d-%02d\n",a.Y,a.M,a.D);


	
	//	a & 1
	system("pause");
	
}
