#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "gpio.h"

/*
 * In order to perform non-blocking debounce
 * we need to handle the state over different reading cycle
 * so we have to wrap the state-less read function
 * with a proper function to keep the state
 */
#define DEBOUNCE_COUNT_LIMIT (10)

typedef GPIO_PinState button_state_t;
struct button_s
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	button_state_t last_state;
	button_state_t last_stable_state;
	int8_t count;
};

typedef struct button_s button_t;

/*
 * Init does not allocate the button structure
 * Always allocate resources outside the functions
 */
void button_init(button_t* button, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, button_state_t init_state);
/*
 * Read the value with debounce
 */
button_state_t button_read(button_t* button);

/*
 * Return the port number of GPIO PORT used by the button
 */
GPIO_TypeDef* button_get_port(const button_t* button);

/*
 * Return the port number of GPIO PIN NUMBER used by the button
 */
uint16_t button_get_pin_number(const button_t* button);

/*
 * Return the last read state of the button. No debounce
 */
button_state_t button_get_actual_state(const button_t* button);


#endif /* INC_BUTTON_H_ */
