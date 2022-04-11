# About

<p align="center">
  <img src="https://github.com/Gieneq/STM32L4_Button_Event_Structure/blob/main/img/stm32l4_board_1.png" alt="STM32L4 Board with LEDs" width="500">
</p>

Simple structure based C code used to detect button actions like:
- press,
- longpress,
- release,

and nonblocking time-based animation done on 10 LEDs array.

# Button events usage
Actions related to button are stored in structure:
```c
typedef struct {
	GPIO_PinState lastState;
	pin_t buttonPin;
	button_event_t onRelease;
	button_event_t onLongpress;
	uint32_t bounceStartTimeMillis;
	uint32_t longpressTimeMillis;
} button_t;
```

Type *pin_t* represents single IO of STM32:
```c
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} pin_t;
```

Type *button_event_t* is used to store function pointers:
```c
typedef void (*button_event_t)();
```

Adding events is done, by filling array. Size of array is automatically calculated:
```c
static button_t buttons[] = {
		{ GPIO_PIN_RESET, { BUTTON_BACKWARD_GPIO_Port, BUTTON_BACKWARD_Pin }, pressBackward, longpressBackward, 0, 0 },
		{ GPIO_PIN_RESET, { BUTTON_FORWARD_GPIO_Port, BUTTON_FORWARD_Pin }, pressForward, longpressForward, 0, 0 },
		{ GPIO_PIN_RESET, { BUTTON_MODE_GPIO_Port, BUTTON_MODE_Pin }, changeTransition, changeMode, 0, 0 }
};
static const int BUTTONS_COUNT = ARRLEN(buttons);
```

## Main loop

Events are the detected in following function. Previous button state is compared with currrent to detect edge:
```c
void checkAllButtonsEvents() {
	uint32_t millis = HAL_GetTick();

	for (int i = 0; i < BUTTONS_COUNT; ++i) {
		button_t *button = &buttons[i];

		if (millis - button->bounceStartTimeMillis > BOUNCE_TIME_MILLIS) {
			GPIO_TypeDef *port = button->buttonPin.port;
			int pin = button->buttonPin.pin;
			GPIO_PinState currentState = HAL_GPIO_ReadPin(port, pin);


			if (button->lastState == GPIO_PIN_RESET	&& currentState == GPIO_PIN_SET) {
				//on release event
				if (button->longpressTimeMillis > 0){
					button->bounceStartTimeMillis = millis;
					button->onRelease();
				}
			} else if (button->lastState == GPIO_PIN_SET && currentState == GPIO_PIN_RESET) {
				//on press event -> on longpress event
				button->longpressTimeMillis = millis;
			} else if (currentState == GPIO_PIN_RESET) {
				if (button->longpressTimeMillis > 0) {
					if(millis - button->longpressTimeMillis > LONGPRESS_TIME_MILLIS){
						button->longpressTimeMillis = 0;
						button->onLongpress();
					}
				}
			}

			button->lastState = currentState;
		}
	}
}
```

HALs millis is used to detect longpress which is set using define:
```c
#define LONGPRESS_TIME_MILLIS 500
```

Function *checkAllButtonsEvents()*should be used in main loop, e.g.:
```c
  /* USER CODE BEGIN WHILE */

	while (1) {
		checkAllButtonsEvents();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
```

<p align="center">
  <img src="https://github.com/Gieneq/STM32L4_Button_Event_Structure/blob/main/img/stm32l4_board_leds_array_1.png" alt="STM32L4 Board with LEDs" width="500">
</p>

# Animations

Animations are done in similar way. Animation function andlers are stored in array:
```c
typedef void (*transition_handler_t)();
static const transition_handler_t animations[TRANSITIONS_COUNT] = {simpleTransitionAnimation, bounceAnimation, toggleSimpleAnimation, bounceToggleAnimation, twocolorsAnimation, crossroadsAnimation, noiseAnimation, raindropsAnimation};
```

Handlers are void argument, but it would be usefull to not use global arguments.
Each animation function consists of 3 parts:
1. clear last animated LED,
2. evaluate new state,
3. update LEDs.

For examplefunction which randomise LED looks likethis:
```c
void noiseAnimation(){
	led_set(led, false);

	led = randLED();

	led_set(led, true);
}
```

## Main loop

Like before there is one time-based function which execues all handlers:
```c
void animate(bool force) {
	if(force || ((mode == MODE_ANIMATED) && (HAL_GetTick() - transitionTimer > interval))) {
		//execute selected transition
		animations[transition]();

		if(!force)
			transitionTimer += interval;
	}
}
```
Which can be placed inside main loop:
```c
  /* USER CODE BEGIN WHILE */

	led_set(led, true);
	while (1) {
		checkAllButtonsEvents();
		animate(false);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  ```

# Wiring

Use any of general purpose input or output pins (GPIO), i.e.:
<p align="center">
  <img src="https://github.com/Gieneq/STM32L4_Button_Event_Structure/blob/main/img/STM32_CUBEMX.PNG" width="500">
</p>

Which corresponds to Nucleos pin header:

<p align="center">
  <img src="https://github.com/Gieneq/STM32L4_Button_Event_Structure/blob/main/img/FORBOT_kurs_STM32L4_GPIO_10_linijka_mapowanie_v2.png" alt="STM32L4 Board with LEDs" width="500">
</p>

and can be then lead to breadboard with LEDs and resistors limiting current:

<p align="center">
  <img src="https://github.com/Gieneq/STM32L4_Button_Event_Structure/blob/main/img/FORBOT_kurs_STM32L4_GPIO_5_schemat_pasek_led.png" width="500">
</p>


# Further informations – STM32L4 course

CubeMX version: 1.6.0

Check out [free STM32L4 HAL CubeMX course](https://forbot.pl/blog/kurs-stm32l4-wejscia-wyjscia-czyli-gpio-stm32-id46571) (po polsku) or read topi on [Forbot forum](https://forbot.pl/forum/topic/19981-kurs-stm32l4---3---wejsciawyjscia-czyli-gpio-w-praktyce/?do=findComment&comment=163231).



