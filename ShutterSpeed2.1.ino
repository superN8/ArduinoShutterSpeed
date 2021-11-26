/* == Shutter Speed Sensor ==

    based on original code by Ethan Moses
    Link:
    https://github.com/cameradactyl/Shutter-Timer/blob/master/Shutter_Timer_v1.2.ino
    
    Created by Nathaniel DeLano
    
    Changelog:
    -2.1
     -added "inPin" variable to improve ease of editing code for different pinouts
     -added "flip" variable to allow different pinouts with the sensor
*/

const int inPin = 2; //number of the pin that is connected to sensor data
const bool flip = false; //Change this value to true if your results are being recorded at the wrong times
long timeActive,
     timeStop;
float shutterSpeed;

void setup()  
{ 
    Serial.begin(9600); //Serial is the window that pops up on the computer that is connected to the arduino
    Serial.println("==Begin Shutter Test==");
    attachInterrupt(digitalPinToInterrupt(2), record, CHANGE); 
}
void loop()  
{
    //The body of this loop is intentionally left blank
}

void record() 
{ 
    if((digitalRead(inPin) == LOW) == flip) //This is the equivalent of an XNOR operation between inPin state and flip
    {
        timeActive = micros();
    } 
    else 
    { 
        timeStop = micros();
        
        Serial.print("Start: ");
        Serial.println(timeActive);
        Serial.print("Stop: ");
        Serial.println(timeStop);
        
        timeActive = timeStop - timeActive;
        shutterSpeed = 1000000/(float)timeActive; // declare shutter speed, which is the inverse of the timeActive in seconds
        
        Serial.print("Microseconds: ");
        Serial.println(timeActive);
        Serial.print("shutter speed: 1/");
        Serial.println(shutterSpeed); 
        Serial.println();
    } 
} 
