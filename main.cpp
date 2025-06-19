#define USER_BUTTON PC_13

#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"

#define TIME_PERIOD     10              // Constant compiler Values here 10 equates to 10ms or 100Hz base Frequency
#define D11x            PA_7_ALT0       // PWMOut class with argument D11 uses same timer as buzzer, so use ALT0 as a fix
                                        // Info regarding tim channels mbed-os/targets/TARGET_STM/STAGET_STM32F4/TARGET_STM32F439xI/PeripheralPins.c


DigitalIn microswitch1(D4);         //Instance of the DigitalIn class called 'microswitch1'
DigitalIn microswitch2(D3);         //Instance of the DigitalIn class called 'microswitch2'
DigitalIn myButton(USER_BUTTON);    //Instance of the DigitalIn class called 'myButton'   
DigitalOut greenLED(LED1);          //Instance of the DigitalOut class called 'greenLED'


Motor Wheel(D13,D11x,D9,D10);        //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

UnbufferedSerial ser(USBTX,USBRX,115200);   // Serial object for printing info

int main ()
{
    // Clear the terminal and print an intro
    printf("\033[2J\033[1;1H\r\n");
    printf("Plymouth University PROJ100 2024/25 Optical Encoder Demonstration\n\r");

    // Set the PWM frequency
    Wheel.Period_in_ms(TIME_PERIOD);                

    // Ensure our motors are stopped at the beginning
    Wheel.Stop();

    // Wait for the blue button to be pressed
    printf("Press Blue Button To Begin\n\r");
    while (myButton == 0){
        greenLED = !greenLED; ThisThread::sleep_for(100ms);
    }
 
    while(true){

        // The following lines demostrate the use of the microswitches.
        // You should remove these from your final solution 
        // You could maybe find a better use for the switches(collision detection?)
        if(microswitch1.read()==1){
            // If the first switch is pressed print Hello
            printf("Hello\n");
        }
        if(microswitch2.read()==1){
            // If the second switch is pressed print Goodbye
            printf("Goodbye\n");
        }

        //*****The following is an example of how to use the Wheel class object*****//

        // Set both motors to full speed in the same direction (drive forward at full speed)
        // (Duty cycle range 0.0-1.0)
        Wheel.Fwd(1.0);
        // When Wheel.fwd() or Wheel.Speed is called, the motors are set to rotate
        // We wish to maintain this until it is time for our next command, so we just wait for some time
        wait_us(5000000);

        // Set both motors going full speed in different directions (turn on the spot)
        // (Duty cycle range 0.0-1.0, negative numbers rotate in the opposite direction)
        Wheel.Speed(1.0,-1.0);
        wait_us(2000000);

        // Then spin the other direction
        Wheel.Speed(-1.0,1.0);
        wait_us(2000000);

        // If we set both motors in the same direction but with different
        // speeds we can trace an arc
        Wheel.Speed(0.8,0.2);
        wait_us(2000000);

        // Finally, to stop both motors we can call Wheel.Stop()
        Wheel.Stop();
        // We can also stop the motors by setting the speeds to 0
        Wheel.Speed(0.0,0.0);

        //*******Demostration of the pwm_tune library***********//
        jingle_bells(2);
        //close_encounter(2);


        // Write the parts of your code which should run in a loop between here..
        


        // ..and here

        
    };
}