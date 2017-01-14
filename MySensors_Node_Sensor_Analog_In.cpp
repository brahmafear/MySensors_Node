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

#include "MySensors_Node_Sensor_Analog_In.h"

MySensors_Node_Sensor_Analog_In::MySensors_Node_Sensor_Analog_In( uint8_t sensor_id,
  uint8_t sensor_type, uint8_t message_type, String description, uint8_t pin, bool percentage,
  uint16_t max_value, uint16_t interval )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _pin = pin;
  _percentage = percentage;
  _max_value = max_value;
  _interval = interval;
}

MySensors_Node_Sensor_Analog_In::MySensors_Node_Sensor_Analog_In( uint8_t sensor_id,
  String description, uint8_t pin, bool percentage, uint16_t max_value, uint16_t interval )
  : MySensors_Node_Sensor_Analog_In( sensor_id, S_LIGHT_LEVEL, V_LIGHT_LEVEL, description,
    pin, percentage, max_value, interval ) { }


MySensors_Node_Sensor_Analog_In::~MySensors_Node_Sensor_Analog_In() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Analog_In::clone() const {
  return new MySensors_Node_Sensor_Analog_In( *this );
}

void MySensors_Node_Sensor_Analog_In::node_sensor_receive( const MyMessage &msg ) {

}

void MySensors_Node_Sensor_Analog_In::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Analog_Input] Setup.\n"));
}

void MySensors_Node_Sensor_Analog_In::node_sensor_loop( ) {
  static uint32_t next_read = 0;
  if ( millis() > next_read ) { // time to check
    uint16_t value = analogRead( _pin );
    value = _percentage ? map( value, 0, _max_value, 0, 100 ) : value;
    DEBUG_MSG(F("[MySensors_Node_Sensor_Analog_Input] Sending value "));
    DEBUG_MSG( value );
    DEBUG_MSG(".\n");
    send( MyMessage(get_sensor_id(), get_message_type()).set( value ));
    next_read += _interval;
  }
}
