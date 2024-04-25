#include <stdio.h>
#include <time.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_BTN 14
#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21
#define PIN_SERVO 12

// NEVER change SERVO_POS_MIN and SERVO_POS_MAX.
// Changing the two values may break your servo motor.
#define SERVO_POS_MIN 500
#define SERVO_POS_MAX 2500

#define LOOP_PERIOD_MS 1000

/* [P1] Write your function FROM here, if needed */


// LED 색 바꾸는 코드. 
void change_led_color(int led_state) {
    
    switch (led_state) {
    case 1:
        gpioWrite(PIN_LEDR, PI_HIGH);
        gpioWrite(PIN_LEDG, PI_LOW);
        gpioWrite(PIN_LEDB, PI_LOW);
        break;
    case 2:
        gpioWrite(PIN_LEDR, PI_LOW);
        gpioWrite(PIN_LEDG, PI_HIGH);
        gpioWrite(PIN_LEDB, PI_LOW);
        break;
    case 3:
        gpioWrite(PIN_LEDR, PI_HIGH);
        gpioWrite(PIN_LEDG, PI_HIGH);
        gpioWrite(PIN_LEDB, PI_LOW);
        break;
    case 4:
        gpioWrite(PIN_LEDR, PI_LOW);
        gpioWrite(PIN_LEDG, PI_LOW);
        gpioWrite(PIN_LEDB, PI_HIGH);
        break;
    case 5:
        gpioWrite(PIN_LEDR, PI_HIGH);
        gpioWrite(PIN_LEDG, PI_LOW);
        gpioWrite(PIN_LEDB, PI_HIGH);
        break;
    case 6:
        gpioWrite(PIN_LEDR, PI_LOW);
        gpioWrite(PIN_LEDG, PI_HIGH);
        gpioWrite(PIN_LEDB, PI_HIGH);
        break;
    case 7:
        gpioWrite(PIN_LEDR, PI_HIGH);
        gpioWrite(PIN_LEDG, PI_HIGH);
        gpioWrite(PIN_LEDB, PI_HIGH);
        break;
    default:
        gpioWrite(PIN_LEDR, PI_LOW);
        gpioWrite(PIN_LEDG, PI_LOW);
        gpioWrite(PIN_LEDB, PI_LOW);
        break;
    }
}



/* [P1] Write your function UP TO here, if needed */


int change_servo_angle(int servo_state) {
    int servo_angle;
    /* [P1] Write your function for servo*/
    // Convert servo state to servo angle
    int servo_angle = SERVO_POS_MIN + (servo_state * 500);
    // Ensure servo_angle does not exceed limits
    if (servo_angle > SERVO_POS_MAX) {
        servo_angle = SERVO_POS_MAX - (servo_angle - SERVO_POS_MAX);
    }
    /* [P1] Write your function FROM here*/
    return servo_angle;
}



int main()
{
    unsigned long t_start_ms, t_elapsed_ms;

    /* [P1] Write your variables FROM here */
    int servo_state = 0;
    int led_state = 0;
    int servo_angle = 0;
    /* [P1] Write your variables UP TO here */

    srand((unsigned int)time(NULL));

    // GPIO settings
    if (gpioInitialise() < 0) {
        printf("Cannot initialize GPIOs\r\n");
        return 1;
    }

    gpioSetMode(PIN_LEDR, PI_OUTPUT);
    gpioSetMode(PIN_LEDG, PI_OUTPUT);
    gpioSetMode(PIN_LEDB, PI_OUTPUT);
    gpioSetMode(PIN_BTN, PI_INPUT);

    gpioSetPullUpDown(PIN_BTN, PI_PUD_UP); // PIN_BTN은 버튼이 눌리면 0, 아니면 1
    gpioWrite(PIN_LEDR, PI_LOW);
    gpioWrite(PIN_LEDG, PI_LOW);
    gpioWrite(PIN_LEDB, PI_LOW);

    // Infinite loop
    while (1) {
        t_start_ms = millis();

        // Update servo position
        servo_angle = change_servo_angle(servo_state);
        gpioServo(PIN_SERVO, servo_angle);
        servo_state = (servo_state + 1) % 5;

        // Read the button state
        int button_pressed = !gpioRead(PIN_BTN);
        if (button_pressed) {

            led_state = (led_state + 1) % 7 + 1;
            change_led_color(led_state);   
            printf("Button is pushed!! \n");
            printf("Button state: %d, Servo position: %d, LED state: %d\n", button_pressed, servo_angle, led_state);
        }

        else {
            printf("Button is not pushed.... \n");
            printf("Button state: %d, Servo position: %d, LED state: %d\n", button_pressed, servo_angle, led_state);
        }
        /* [P1] Write your codes UP TO here */

        t_elapsed_ms = millis() - t_start_ms;
        sleep_ms(LOOP_PERIOD_MS - t_elapsed_ms);
    }

    return 1;
}
