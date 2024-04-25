#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_BTN 14
#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21
#define PIN_SERVO 12

#define SERVO_POS_MIN 1000
#define SERVO_POS_MAX 2000

#define LOOP_PERIOD_MS 0000  // Set the loop period properly


/* [P3] Write your global variables FROM here */
volatile bool g_toggle_led = false;
volatile bool g_change_color = false;
volatile bool g_servo_move = false;
volatile int g_led_color = 0;  // 0: red, 1: green, 2: blue


/* [P3] Write your global variables UP TO here */


/* [P3] Write your function FROM here, if needed */
// NO NEED 
/* [P3] Write your function UP TO here, if needed */

void myISR_ledToggle()
{
    /* [P3] Write your code FROM here */
    g_toggle_led = !g_toggle_led; // 단순 토글 
    /* [P3] Write your code UP TO here */
}

void myISR_ledColor()
{
    /* [P3] Write your code FROM here */
    g_change_color = true;
    /* [P3] Write your code UP TO here */
}

void myISR_servo()
{
    /* [P3] Write your code FROM here */
    g_servo_move = !g_servo_move;
    /* [P3] Write your code UP TO here */
}

int main()
{
    unsigned long t_start_ms, t_elapsed_ms;
    /* [P3] Write your variables FROM here*/
    int led_state = PI_LOW;  // Initial state of the LED

    srand((unsigned int)time(NULL))
    /* [P3] Write your variables UP TO here*/

    srand((unsigned int)time(NULL));

    // GPIO settings
    if(gpioInitialise()<0) {
        printf("Cannot initialize GPIOs\r\n");
        return 1;
    }

    gpioSetMode(PIN_LEDR, PI_OUTPUT);
    gpioSetMode(PIN_LEDG, PI_OUTPUT);
    gpioSetMode(PIN_LEDB, PI_OUTPUT);
    gpioSetMode(PIN_BTN, PI_INPUT);

    gpioSetPullUpDown(PIN_BTN, PI_PUD_UP);
    gpioWrite(PIN_LEDR, PI_LOW);
    gpioWrite(PIN_LEDG, PI_LOW);
    gpioWrite(PIN_LEDB, PI_LOW);

    // Interrupt settings
    /* [P3] Write your code FROM here */
    // Use gpioSetTimerFunc() properly.
    //gpioSetTimerFunc(0, *, *);
    //gpioSetTimerFunc(1, *, *);
    //gpioSetTimerFunc(2, *, *);

    /* [P3] Write your code UP TO here */
    gpioSetTimerFunc(0, 200, myISR_ledToggle);  // 200ms마다 LED 토글
    gpioSetTimerFunc(1, 2000, myISR_ledColor);  // 2000ms마다 색상 변경
    gpioSetTimerFunc(2, 5000, myISR_servo);     // 5000ms마다 서보 모터 작동
    // Infinite loop
    while(1) {
        t_start_ms = millis();
        
        /* [P3] Write your code FROM here */
        
            // While the LED is turned on, switch the LED color if
            // `g_led_color` is asserted in the ISR.
            
            // Setting LED color using bit-wise operators. Three LSBs of
            // `led_color` represents the state of BGR, respectively.
            
        if (g_toggle_led) {
            led_state = (led_state == PI_LOW) ? PI_HIGH : PI_LOW;  // LED 상태 토글
            gpioWrite(PIN_LEDR, led_state);
            gpioWrite(PIN_LEDG, led_state);
            gpioWrite(PIN_LEDB, led_state);
            g_toggle_led = false;
        }

        if (g_change_color) {
            g_led_color = (g_led_color + 1) % 3;  // 다음 색상으로 변경
            gpioWrite(PIN_LEDR, g_led_color == 0 ? PI_HIGH : PI_LOW);
            gpioWrite(PIN_LEDG, g_led_color == 1 ? PI_HIGH : PI_LOW);
            gpioWrite(PIN_LEDB, g_led_color == 2 ? PI_HIGH : PI_LOW);
            g_change_color = false;
        }
        /* [P3] Write your code UP TO here */

        t_elapsed_ms = millis() - t_start_ms;
        sleep_ms(LOOP_PERIOD_MS - t_elapsed_ms);
    }

    return 1;
}
