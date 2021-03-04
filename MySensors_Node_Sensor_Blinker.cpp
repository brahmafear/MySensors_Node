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

#include "MySensors_Node_Sensor_Blinker.h"

MySensors_Node_Sensor_Blinker::MySensors_Node_Sensor_Blinker( uint8_t sensor_id, uint8_t sensor_type,
  uint8_t message_type, String description, uint32_t interval )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _interval = interval;
 
  _next_read = random( 0, _interval );
  _last_state = false;

}


MySensors_Node_Sensor_Blinker::~MySensors_Node_Sensor_Blinker() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Blinker::clone() const {
  return new MySensors_Node_Sensor_Blinker( *this );
}

/* void MySensors_Node_Sensor_Blinker::node_sensor_receive( const MyMessage &msg ) {

} */

void MySensors_Node_Sensor_Blinker::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Blinker] Setup.\n"));
}

void MySensors_Node_Sensor_Blinker::node_sensor_loop( ) {
  if ( millis() > _next_read ) { // time to check
    _last_state = ! _last_state;
    DEBUG_MSG(F("[MySensors_Node_Sensor_Blinker] Sending state "));
    DEBUG_MSG( _last_state ? F("active.\n") : F("inactive.\n"));
    send( MyMessage(get_sensor_id(), get_message_type()).set( _last_state ? 1 : 0 ));
    _next_read += _interval;
  }
}
