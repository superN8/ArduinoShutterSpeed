/* == Shutter Speed Sensor ==
    based on original code by Ethan Moses
    Link:
    https://github.com/cameradactyl/Shutter-Timer/blob/master/Shutter_Timer_v1.2.ino
    created by Nathaniel DeLano
*/
long timeActive,
     timeStop;
float shutterSpeed; //Variables are declared outside of the loop so the computer doesnt reallocate memory on every iteration

void setup() //This part of the program is run exactly once on boot 
{ 
    Serial.begin(9600); //opens a serial connection.
    attachInterrupt(digitalPinToInterrupt(2), record, CHANGE); //run the method 'record', every time the voltage on pin 2 changes. 
}
void loop() // this part of the program is run over and over again,  unless INTERRUPTED by our interrupt 
{
    //The body of this loop is intentionally left blank
    // Arduinos always need a loop function to run, but all the work is performed in the interrupt, which occurs when the sensor is activated rather than when the loop is iterated
}

void record() //this is the interrupt function, which is called everytime the voltage on pin 2 changes, regardless of the clock cycle
{ 
    if(digitalRead(2) == HIGH)
    {
        
        timeActive = micros(); //set the variable timeActive to current microseconds 
        
    } 
    else // If the voltage on pin 2 is low this will set the stop time and display the speed info
    { 
        timeStop = micros();
        Serial.print("Start: ");
        Serial.println(timeActive); //display the time the sensor was activated, before timeActive is changed
        Serial.print("Stop: ");
        Serial.println(timeStop);
        timeActive = timeStop - timeActive; // calculate active time by subtracting the start time from the current time
        Serial.print("Microseconds: ");
        Serial.println(timeActive); //display total microseconds in shutter interval
        shutterSpeed = 1000000/(float)timeActive; // declare shutter speed, which is the inverse of the timeActive in seconds
        Serial.print("shutter speed: 1/"); Serial.println(shutterSpeed); //display the shutter speed
        Serial.println();
    } 
} 

    