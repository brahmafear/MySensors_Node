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

#include "MySensors_Node_Sensor_Gpio_Out.h"

MySensors_Node_Sensor_Gpio_Out::MySensors_Node_Sensor_Gpio_Out( uint8_t sensor_id, uint8_t sensor_type, uint8_t message_type, String description, uint8_t pin, bool active )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _pin = pin;
  _active = active;
  _msg_received = false;
}

/* MySensors_Node_Sensor_Gpio_Out::MySensors_Node_Sensor_Gpio_Out( uint8_t sensor_id, String description, uint8_t pin, bool active )
  : MySensors_Node_Sensor_Gpio_Out( sensor_id, S_BINARY, V_STATUS, description, pin, active ) { }
*/

MySensors_Node_Sensor_Gpio_Out::~MySensors_Node_Sensor_Gpio_Out() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Gpio_Out::clone() const {
  return new MySensors_Node_Sensor_Gpio_Out( *this );
}

void MySensors_Node_Sensor_Gpio_Out::node_sensor_receive( const MyMessage &msg ) {
  if ( msg.type == get_message_type() ) {
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_Output] Message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG( data != 0 ? F(" with value true.\n") : F(" with value false.\n"));
    digitalWrite( _pin, data != 0 ? _active : ! _active );
    send( MyMessage(get_sensor_id(), get_message_type()).set(data) );
    _msg_received = true;
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_Output] Incorrect message type received.\n"));
  }
}

void MySensors_Node_Sensor_Gpio_Out::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_Output] Setup.\n"));
  digitalWrite( _pin, ! _active );
  pinMode( _pin, OUTPUT );
  node_sensor_request();
  _delay5s = millis() + 5000;
}

void MySensors_Node_Sensor_Gpio_Out::node_sensor_loop( ) {
  if ( _msg_received == false && millis() > _delay5s ) {  // set to default, inactive state
    DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_Output] Setting default state.\n"));
    digitalWrite( _pin, ! _active );
    send( MyMessage(get_sensor_id(), get_message_type()).set( 0 ));
    _msg_received = true;
  }
}
