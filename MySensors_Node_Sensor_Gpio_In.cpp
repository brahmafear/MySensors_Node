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

#include "MySensors_Node_Sensor_Gpio_In.h"

MySensors_Node_Sensor_Gpio_In::MySensors_Node_Sensor_Gpio_In( uint8_t sensor_id, uint8_t sensor_type,
  uint8_t message_type, String description, uint8_t pin, bool active, uint8_t input_type, uint16_t interval )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _pin = pin;
  _active = active;
  _interval = interval;
  _input_type = input_type;

  _next_read = random( 0, _interval );
  _last_state = ! _active;

}

/* MySensors_Node_Sensor_Gpio_In::MySensors_Node_Sensor_Gpio_In( uint8_t sensor_id, String description, uint8_t pin, bool active, uint8_t input_type, uint16_t interval )
  : MySensors_Node_Sensor_Gpio_In( sensor_id, S_MOTION, V_TRIPPED, description, pin, active, input_type, interval ) { }
*/

MySensors_Node_Sensor_Gpio_In::~MySensors_Node_Sensor_Gpio_In() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Gpio_In::clone() const {
  return new MySensors_Node_Sensor_Gpio_In( *this );
}

/* void MySensors_Node_Sensor_Gpio_In::node_sensor_receive( const MyMessage &msg ) {

} */

void MySensors_Node_Sensor_Gpio_In::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_In] Setup.\n"));
  pinMode( _pin, _input_type );
}

void MySensors_Node_Sensor_Gpio_In::node_sensor_loop( ) {
  if ( millis() > _next_read ) { // time to check
    bool state;
    if ( _pin == A6 || _pin == A7 ) { // On some Arduino boards, these pins don't work with digitalRead()
      state = (_active == (analogRead( _pin ) > 200));
    } else {
      state = (_active == digitalRead( _pin ));
    }

    if ( state != _last_state || _next_read == 0 ) { // either something changed or first run
      DEBUG_MSG(F("[MySensors_Node_Sensor_Gpio_In] Sending state "));
      DEBUG_MSG( state ? F("active.\n") : F("inactive.\n"));
      send( MyMessage(get_sensor_id(), get_message_type()).set( state ? 1 : 0 ));
      _last_state = state;
    }
    _next_read += _interval;
  }
}
