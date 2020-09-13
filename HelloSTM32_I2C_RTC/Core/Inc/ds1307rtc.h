
#ifndef INC_DS1307RTC_H_
#define INC_DS1307RTC_H_

#include <stdint.h>


#define DS1307_OK 		(0)
#define DS1307_ERR		(-1)
#define DS1307_IC2_ERR	(-2)


struct date_time_s
{
	uint8_t     seconds;
	uint8_t     minutes;
	uint8_t     hours;
	uint8_t     day;
	uint8_t     date;
	uint8_t     month;
	uint16_t    year;
};

typedef struct date_time_s date_time_t;

int8_t ds1307rtc_init();

int8_t ds1307rtc_get_date_time(date_time_t* datetime);

int8_t ds1307rtc_set_date_time(const date_time_t* datetime);

int8_t ds1307rtc_dispose();



#endif /* INC_DS1307RTC_H_ */
