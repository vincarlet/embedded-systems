#include <stdint.h>
#include "gpio.h"
#include "button.h"

void button_init(button_t* button, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, button_state_t init_state)
{
	button->GPIO_Pin = GPIO_Pin;
	button->GPIOx = GPIOx;
	button->last_state = init_state;
	button->last_stable_state = init_state;
	button->count = 0;
}

button_state_t button_read(button_t* button)
{
	button_state_t current_state = HAL_GPIO_ReadPin(button->GPIOx, button->GPIO_Pin);
	if(current_state == button->last_state)
	{
		if(++(button->count) >= DEBOUNCE_COUNT_LIMIT)
		{
			button->last_stable_state = current_state;
		}
	}
	/*Unstable read*/
	else
	{
		button->last_state = current_state;
		button->count = 0;
	}

	return button->last_stable_state;
}

inline GPIO_TypeDef* button_get_port(const button_t* button)
{
	if(button)
	{
		return button->GPIOx;
	}
	return NULL;
}

inline uint16_t button_get_pin_number(const button_t* button)
{
	if(button)
	{
		return button->GPIO_Pin;
	}
	return -1;
}

/*
 * Here we have a conflict between the return value and the error value
 * How can we manage this situation?
 */
inline button_state_t button_get_actual_state(const button_t* button)
{
	if(button)
	{
		return button->last_state;
	}
	return 0;
}

/*
 * New function interface
 * typedef int8_t button_result_t
 * #define BUTTON_OK  (0)
 * #define BUTTON_ERR (-1) <-- POSIX Convention
 * inline int16_t button_get_actual_state(const button_t* button, button_state_t* state)
 * {
 *    state = 0;
 *    button_result_t res = BUTTON_ERR; <-- Defensive programming
 * 	  if(button)
 *	  {
 *		state = button->last_state;
 *		res = BUTTON_OK;
 *	  }
 *	  return res;
 * }
 */

