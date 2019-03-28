//Include the header, and all nessary other files from arduino
#include <GjosseEncoders.h>
#include <FastGPIO.h>
#include <avr/interrupt.h>
#include <Arduino.h>

//Define the pins for the encoders A and B channels
#define LEFT_XOR   8
#define LEFT_B     IO_E2
#define RIGHT_XOR  7
#define RIGHT_B    23

//Set up the varibles used to remeber the last pulse
static volatile bool lastLeftA;
static volatile bool lastLeftB;
static volatile bool lastRightA;
static volatile bool lastRightB;

static volatile uint32_t countLeft;
static volatile uint32_t countRight;


int32_t GjosseEncoders::getCountsLeft() {
    //check if the interupts are set up, etc
    init();
    
    //disable any interupt for now to prevent the value from changing
    cli();
    //set a int16 value for the arduino, fast method to extract the pulse
    int32_t counts = countLeft;
    
    //enable the interupts agian
    sei();
    
    //return value
    return counts;
}

int32_t GjosseEncoders::getCountsRight() {
    //check if interupts are set up.
    init();
    
    //disable the interupts to prevent value from changing
    cli();
    
    //extract the count value, fast
    int32_t counts = countRight;
    
    //turn on interupts again.
    sei();
    
    //return value
    return counts;
}

void GjosseEncoders::resetCounts() {
    countRight = 0;
    countLeft = 0;
}

ISR(PCINT0_vect) {
    //Read the values of the B channel
    bool leftB = FastGPIO::Pin<LEFT_B>::isInputHigh();
    
    //Read the balue of the A channel and XOR it with the B channel
    bool leftA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ leftB;
    
    //check if there was a change between the last value and the current one. On both channels
    countLeft += (lastLeftA ^ leftB) - (leftA ^ lastLeftB);
    
    //reset the last values
    lastLeftA = leftA;
    lastLeftB = leftB;
}

static void rightISR() {
    //Read the values of the A channel
    bool rightB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
    
    //Read the values of the B channel and XOR with the B channel
    bool rightA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ rightB;
    
    //CHeck if there was chnage between the last value and current one, on both channels
    countRight += (lastRightA ^ rightB) - (rightA ^ lastRightB);
    
    //reset the last values
    lastRightA = rightA;
    lastRightB = rightB;
}



//Init the object
void GjosseEncoders::init2() {
    //Set the the pins to a input and pull it up.
    FastGPIO::Pin<LEFT_XOR>::setInputPulledUp();
    FastGPIO::Pin<LEFT_B>::setInputPulledUp();
    FastGPIO::Pin<RIGHT_XOR>::setInputPulledUp();
    FastGPIO::Pin<RIGHT_B>::setInputPulledUp();
    
    //Turn on pin chnage interupt and disable pin change interrupts
    PCICR = (1 << PCIE0);
    PCMSK0 = (1 << PCINT4);
    //Clear the interupt flag
    PCIFR = (1 << PCIF0);
    
    //Attach the interupt to the right encoder on change
    attachInterrupt(4, rightISR, CHANGE);
    
    //init the varibles of last pulses and counts back to 0
    lastLeftB = FastGPIO::Pin<LEFT_B>::isInputHigh();
    lastLeftA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ lastLeftB;
    countLeft = 0;
    
    lastRightB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
    lastRightA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ lastRightB;
    countRight = 0;
}





