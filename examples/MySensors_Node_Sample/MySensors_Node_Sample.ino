/*
 * MySensors Node is a companion software to work with the MySensors library (http://www.mysensors.org)
 * for wireless sensor/actuator connection to a home automation / monitoring system.  This software is
 * designed to be used on the sensor / actuator device running on a Arduino microcontroller.  The base
 * software can be extended to include additional functionality by extending the abstract
 * MySensor_Node_Sensor class.
 *
 * Created by Dave Myers <brahmafear@gmail.com>
 * Copyright (c) 2017
 *
 * http://github.com/brahmafear/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/*
 * Node config
 */
#define MY_NODE_DESCRIPTION                "Sample"     // Any string description of the node to send to controller.
#define MY_NODE_VERSION                    "0.01"       // Version to send to controller.
#define ENABLE_DEBUG                                    // Enables debug messages to serial console.

/*
 * MySensor config
 */
#define MY_DEBUG                                        // Displays *lots* of messages from MySensors library.
#define MY_NODE_ID                      247             // Forces node id.  Comment out for auto selection.
#define MY_RADIO_NRF24                                  // Sets library to use NRF24L01+ radio.
#define MY_RF24_SANITY_CHECK                            // Enables MySensors additional checks on radio.
// #define MY_RF24_CE_PIN               8               // Overrides the NRF24L01+ CE pin - default 9 on AVR.
// #define MY_RF24_CS_PIN               7               // Overrides the NRF24L01+ CS pin - default 10 on AVR.
// #define MY_REPEATER_FEATURE                          // Enables this node as a repeater.



// Includes
#include <SPI.h>
#include <MySensors.h>                                  // A bunch of code runs as soon as this is included -
                                                        // and before sketch setup().  Uncomment MY_DEBUG to see.
#include "MySensors_Node.h"                             // Must come *after* including MySensors.h.


// Global variables
MySensors_Node node(MY_NODE_DESCRIPTION, MY_NODE_VERSION);




void presentation() {

  // Add sensors here

  Serial.println("**** Adding Sensors.");
  // Create a sensor object to add
  MySensors_Node_Sensor_Gpio_Out nsgo( 11, "Simple LED 1", 5, true );
  Serial.println( node.add_sensor( &nsgo ) );

  // Or inline create
  Serial.println( node.add_sensor(  new MySensors_Node_Sensor_Gpio_In( 13, "Simple Motion", 2, true, INPUT_PULLUP, 500 ) ) );
  Serial.println( node.add_sensor(  new MySensors_Node_Sensor_Analog_In( 14, "Analog In", A0, false, true, true, 1024, 10000 ) ) );
  //Serial.println( node.add_sensor(  new MySensors_Node_Sensor_Pwm( 15, "PWM LED", 6, true, true, 255 ) ) );
  Serial.println( node.add_sensor(  new MySensors_Node_Sensor_Dht11( 20, 21, "DHT", 4, 10000 ) ) );
  Serial.println( node.add_sensor(  new MySensors_Node_Sensor_Rgb( 25, "RGB Light", 3, 5, 6, false ) ) );


  // Call present() of node sensors

  Serial.println("**** Presenting Sensors.");
  node.present();
}

void receive( const MyMessage &msg ) {
  Serial.println("**** Received Message.");
  node.receive( msg );
}


void setup() {
  Serial.begin(115200);
  Serial.println(F("\nNode begin."));

  // Add additional code here

  // This line must be included in setup()
  node.setup();
}

void loop() {

  // Add additional code here
  // Do not use delay() or other code with signifigant processing time

  // This line must be included in loop()
  node.loop();
}
