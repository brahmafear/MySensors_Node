/*
 * MySensors Node is a companion software to work with the MySensors library (http://www.mysensors.org)
 * for wireless sensor/actuator connection to a home automation / monitoring system.  This software is
 * designed to be used on the sensor / actuator device running on a Arduino microcontroller.  The base
 * software can be extended to include additional functionality by extending the abstract
 * MySensor_Node_Sensor class.
 *
 * Created by Dave Myers <brahmafear@gmail.com>
 * Copyright (c) 2018
 *
 * http://github.com/brahmafear/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#include "MySensors_Node_Sensor_DS18X.h"

MySensors_Node_Sensor_DS18X::MySensors_Node_Sensor_DS18X( uint8_t temperature_id,
  String description, uint8_t pin, uint32_t interval, int16_t offset )
  : MySensors_Node_Sensor( temperature_id, S_TEMP, V_TEMP, description ) {
  _pin = pin;
  _interval = interval;
  _offset = offset;

  _next_read = random( 0, _interval );
}

MySensors_Node_Sensor_DS18X::~MySensors_Node_Sensor_DS18X() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_DS18X::clone() const {
  return new MySensors_Node_Sensor_DS18X( *this );
}

void MySensors_Node_Sensor_DS18X::node_sensor_present( ) {
  present( get_sensor_id(), S_TEMP, ( get_description() + " Temperature" ).c_str());
}

void MySensors_Node_Sensor_DS18X::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_DS18X] Setup.\n"));
  _waiting = false;
  _read_delay = 1000;
}

void MySensors_Node_Sensor_DS18X::node_sensor_loop( ) {
  static OneWire ow(_pin);
  static DallasTemperature dt( &ow );
  float t;
  if ( _waiting && millis() > _next_read + _read_delay ) {
    t = getControllerConfig().isMetric ? dt.getTempCByIndex(0) : dt.getTempFByIndex(0);
    t += _offset;
    DEBUG_MSG(F("[MySensors_Node_Sensor_DS18X] Sending Temperature: "));
    DEBUG_MSG(t);
    DEBUG_MSG("\n");
    send( MyMessage(get_sensor_id(), V_TEMP).set( round(t) ));
    _next_read += _interval;
    _waiting = false;
    
  } else if ( ( ! _waiting ) && millis() > _next_read ) {
    dt.requestTemperatures();
    _waiting = true;
  
  } else {
  
  }
}
