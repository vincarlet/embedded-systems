#include <stdint.h>
#include "i2c.h"
#include "ds1307rtc.h"

#define DS1307_ADDRESS 				(0xD0)
#define MAX_RETRY					(3)

#define DS1307_SECONDS				(0x00)
#define DS1307_MINUTES				(0x01)
#define DS1307_HOURS				(0x02)
#define DS1307_DAY					(0x03)
#define DS1307_DATE					(0x04)
#define DS1307_MONTH				(0x05)
#define DS1307_YEAR					(0x06)
#define DS1307_CONTROL				(0x07)

/* Bits in control register */
#define DS1307_CONTROL_OUT			(7)
#define DS1307_CONTROL_SQWE			(4)
#define DS1307_CONTROL_RS1			(1)
#define DS1307_CONTROL_RS0			(0)

#define ADDRESS_SIZE				(1)
#define DATA_SIZE					(1)

uint8_t months[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

date_time_t recv_data;
date_time_t snd_data;

uint8_t out_buff;
uint8_t in_buff;



/*
* @fn          static uint8_t bcd2Dec ( uint8_t val )
* @brief       Convert BCD to Decimal
* @param[in]   val value to convert from BCD to Decimal
* @return      res Converted value
*/
uint8_t bcd2Dec ( uint8_t val )
{
    uint8_t res = ((val/16*10) + (val % 16));
    return res;
}

/*
* @fn           static uint8_t dec2Bcd ( uint8_t val )
* @brief        Convert Decimal to BCD
* @param[in]    val value to convert from Decimal to BCD
* @return       res Converted value
*/
uint8_t dec2Bcd ( uint8_t val )
{
    uint8_t res = ((val/10*16) + (val%10));
    return res;
}


int8_t ds1307rtc_init()
{
	HAL_StatusTypeDef returnValue;
	returnValue = HAL_I2C_IsDeviceReady(&hi2c1, DS1307_ADDRESS, MAX_RETRY, HAL_MAX_DELAY);
	if(returnValue != HAL_OK)
	{
		return DS1307_ERR;
	}
	return DS1307_OK;
}

int8_t ds1307rtc_update(date_time_t* datetime)
{
	HAL_StatusTypeDef returnValue;

	returnValue = HAL_I2C_Mem_Read_IT(&hi2c1, DS1307_ADDRESS, DS1307_SECONDS, ADDRESS_SIZE, &(datetime->seconds), DATA_SIZE);
	if(returnValue != HAL_OK)
	{
		return DS1307_IC2_ERR;
	}

	return DS1307_OK;
}

int8_t ds1307rtc_get_date_time(date_time_t* datetime)
{
	/*HAL_StatusTypeDef returnValue;

	returnValue = HAL_I2C_Mem_Read_IT(&hi2c1, DS1307_ADDRESS, DS1307_SECONDS, ADDRESS_SIZE, &(datetime->seconds), DATA_SIZE);
	if(returnValue != HAL_OK)
	{
		return DS1307_IC2_ERR;
	}

	return DS1307_OK;*/
}

int8_t ds1307rtc_set_date_time(const date_time_t* datetime)
{
	HAL_StatusTypeDef returnValue;
	uint8_t out[2];

	returnValue = HAL_I2C_Mem_Write_IT(&hi2c1, DS1307_ADDRESS, DS1307_SECONDS, ADDRESS_SIZE, &(datetime->seconds), DATA_SIZE);
	if(returnValue != HAL_OK)
	{
		return DS1307_IC2_ERR;
	}

	return DS1307_OK;

}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{

}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1)
	{
		recv_data.seconds = bcd2Dec(out_buff);
	}
}

uint8_t ds1307rtc_dispose();
