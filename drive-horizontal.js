#!/usr/bin/env node


// Drive horizontal...
// This example uses an H-bridge to drive a DC motor in two directions
// From here: https://www.safaribooksonline.com/library/view/beaglebone-cookbook/9781491915660/ch04.html


var b = require('bonescript');

var enable = 'P8_19';    // Pin to use for PWM speed control
var in1    = 'P8_13';
var in2    = 'P8_15';

var min    = 0.1;       // Min duty cycle
var max    = 1.0;       // Max duty cycle
var speed  = max*0.75;  // Current speed;
var interval    = 500;// Run time in milliseconds
var isClockwise = false;  // Rotation direction
var timer       = 0;

b.pinMode(enable, b.ANALOG_OUTPUT, 6, 0, 0, runMotor); 
b.pinMode(in1, b.OUTPUT);
b.pinMode(in2, b.OUTPUT);


// runMotor() does what it sounds like.
// Check to see if speed setting is rational, set to safe values.
// Check direction boolean and then...
// run for interval miliseconds
function runMotor(foo) {
        if(foo.err) {
        console.log('foo.err = ' + foo.err);
        return;
    }
    console.log('runMotor');
    
    if(speed > max ) {
            speed = max;
        } else if (speed < min) {
            stopMotor();
            console.log('speed hosed... getting out of here.');
            return;
        }
    
    // Talk to the hardware
    b.analogWrite(enable, speed);
    console.log('speed = ' + speed);
    var i=0;
    
    for (i = 0; i < interval; i++) {
        if(isClockwise) {
            timer = setInterval(clockwise(), 1);
        } else {
            timer = setInterval(counterClockwise(), 1);
        }
    }

    stopMotor;
}

function stopMotor() {
    console.log('stopMotorping');
    clearInterval(timer);
    b.digitalWrite(in1, b.LOW);
    b.digitalWrite(in2, b.LOW);
}

function clockwise() {
    console.log('Clockwise');
    b.digitalWrite(in1, b.HIGH);
    b.digitalWrite(in2, b.LOW);
}

function counterClockwise() {
    console.log('Counter Clockwise');
    b.digitalWrite(in1, b.LOW);
    b.digitalWrite(in2, b.HIGH);
}

process.on('SIGINT', function() {
    console.log('Got SIGINT, turning motor off');
    clearInterval(timer);         // stopMotor the timer
    b.analogWrite(enable, 0);     // Turn motor off
});
