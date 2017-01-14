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

#include "MySensors_Node_Sensor.h"

MySensors_Node_Sensor::MySensors_Node_Sensor( uint8_t sensor_id, uint8_t sensor_type, uint8_t message_type, String description ) {
  _sensor_id = sensor_id;
  _sensor_type = sensor_type;
  _message_type = message_type;
  _description = description;

}

MySensors_Node_Sensor::~MySensors_Node_Sensor() {

}

void MySensors_Node_Sensor::node_sensor_present( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor] Presenting "));
  DEBUG_MSG( get_sensor_id() );
  DEBUG_MSG(" ");
  DEBUG_MSG( get_sensor_type() );
  DEBUG_MSG(" ");
  DEBUG_MSG( get_description() );
  DEBUG_MSG(" ");
  present( get_sensor_id(), get_sensor_type(), get_description().c_str() );
}

void MySensors_Node_Sensor::node_sensor_request( ) {
  request( get_sensor_id(), get_message_type() );
}

void MySensors_Node_Sensor::node_sensor_setup() {
  DEBUG_MSG(F("[MySensors_Node_Sensor] Setup.\n"));
}

void MySensors_Node_Sensor::node_sensor_loop() { }

uint8_t MySensors_Node_Sensor::get_sensor_id()  {
  return _sensor_id;
}

uint8_t MySensors_Node_Sensor::get_sensor_type() {
  return _sensor_type;
}

uint8_t MySensors_Node_Sensor::get_message_type() {
  return _message_type;
}

String MySensors_Node_Sensor::get_description() {
  return _description;
}
