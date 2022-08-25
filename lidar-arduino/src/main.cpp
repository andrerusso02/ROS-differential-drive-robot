#include <Arduino.h>

#include <SoftwareSerial.h>   //header file of software serial port

//SoftwareSerial Serial1(7, 8); //define software serial port name as Serial1 and define pin2 as RX & pin3 as TX

#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object


                                    
void setup()
{
    Serial.begin( 115200);   // Intialize terminal serial port
    delay(20);               // Give port time to initalize
    //printf("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // say 'hello'
    Serial.println("TFMPlus Library Example - 10SEP2021");  // say 'hello'

    Serial1.begin( 115200);  // Initialize TFMPLus device serial port.
    delay(20);               // Give port time to initalize
    tfmP.begin( &Serial1);   // Initialize device library object and...
                             // pass device serial port to the object.
    // Send some example commands to the TFMini-Plus
    // - - Perform a system reset - - - - - - - - - - -
    // printf( "Soft reset: ");
    // if( tfmP.sendCommand( SOFT_RESET, 0))
    // {
    //     printf( "passed.\r\n");
    // }
    // else tfmP.printReply();
  
    delay(500);  // added to allow the System Rest enough time to complete


    // Set baud rate
    // Serial.print( "Set baud rate : ");
    // if( tfmP.sendCommand( SET_BAUD_RATE, BAUD_115200))
    // {
    //   Serial.println( "succès.");
    // }
    // else
    // {
    //   Serial.println( "failed.\r\n");
    //   tfmP.printReply();
    // }

    // delay(500);
    // Serial1.flush();
    // Serial1.begin( 9600);
    // delay(500);


    // - - Set the data frame-rate to 20Hz - - - - - - - -
    //  Serial.print( "Data-Frame rate: ");
    // if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_1000))
    // {
    //   Serial.println( "20Hz");
    // }
    // else
    // {
    //   Serial.println( "failed");
    //   tfmP.printReply();
    // }
    // delay(500);
    // // save paramerters
    // Serial.print( "Save parameters: ");
    // if( tfmP.sendCommand( SAVE_SETTINGS, 0))
    // {
    //   Serial.println( "passed");
    // }
    // else
    // {
    //   Serial.println( "failed");
    //   tfmP.printReply();
    // }
    // delay(1000);
  
    // - - - - - - - - - - - - - - - - - - - - - - - -

/*  // - - - - - - - - - - - - - - - - - - - - - - - -  
    // The next two commands may be used to switch the device 
    // into I2C mode.  This sketch will no longer receive UART
    // (serial) data.  The 'TFMPI2C_example' sketch in the 
    // TFMPI2C Library can be used to switch the device back
    // to UART mode.
    // Don't forget to switch the cables, too.
    // - - - - - - - - - - - - - - - - - - - - - - - -
    printf( "Set I2C Mode: ");
    if( tfmP.sendCommand( SET_I2C_MODE, 0))
    {
        printf( "mode set.\r\n");
    }
    else tfmP.printReply();
    printf( "Save settings: ");
    if( tfmP.sendCommand( SAVE_SETTINGS, 0))
    {
        printf( "saved.\r\n");
    }
    else tfmP.printReply();
    // - - - - - - - - - - - - - - - - - - - - - - - -    
*/

  delay(1000);            // And wait for half a second.
}

// Initialize variables
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip

long cntSuccess = 0;
long cntEchec = 0;

long lastTime = 0;


// Use the 'getData' function to pass back device data.
void loop()
{
    //delay(50);   // Loop delay to match the 20Hz data frame rate

    if(lastTime==0){
      lastTime = millis();
    }

    if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      Serial.print("Dist =  ");
      Serial.print(tfDist);
      Serial.print(" cm, \tFlux = ");
      Serial.print(tfFlux);
      Serial.print(", \tTemp = ");
      Serial.print(tfTemp);
      Serial.println("C");
       cntSuccess++;
  
    }
    else                  // If the command fails...
    {
      //tfmP.printFrame();  // display the error and HEX dataa
      cntEchec++;
    }

    double freq = 1000.0/(double)(millis() - lastTime);
    lastTime = millis();

    // Serial.print("Success = ");
    // Serial.print(cntSuccess);
    // Serial.print(", \tEchec = ");
    // Serial.print(cntEchec);
    // Serial.print(", \tFreq = ");
    // Serial.print(freq);
    // Serial.println("");
}