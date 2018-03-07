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
  String description, uint8_t pin, uint32_t interval, int16_t offset, uint8_t count )
  : MySensors_Node_Sensor( temperature_id, S_TEMP, V_TEMP, description ) {
  _pin = pin;
  _interval = interval;
  _offset = offset;
  _count = count;

  _next_read = random( 0, _interval );
}

MySensors_Node_Sensor_DS18X::~MySensors_Node_Sensor_DS18X() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_DS18X::clone() const {
  return new MySensors_Node_Sensor_DS18X( *this );
}

void MySensors_Node_Sensor_DS18X::node_sensor_present( ) {
  for ( int i = 0; i < _count; i++ ) {
    present( get_sensor_id() + i, S_TEMP, ( get_description() + " Temperature " + i).c_str());
  }
}

void MySensors_Node_Sensor_DS18X::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_DS18X] Setup.\n"));
  _waiting = false;
  _read_delay = 1000;

  _ow = new OneWire( _pin );
  _dt = new DallasTemperature( _ow );
  _dt->begin();
}

void MySensors_Node_Sensor_DS18X::node_sensor_loop( ) {
  float t;
  if ( _waiting && millis() > _next_read + _read_delay ) {
    for ( int i = 0; i < _count; i++ ) {
      t = getControllerConfig().isMetric ? _dt->getTempCByIndex(i) : _dt->getTempFByIndex(i);
      t += _offset;
      DEBUG_MSG(F("[MySensors_Node_Sensor_DS18X] Sending Temperature for device "));
      DEBUG_MSG(i);
      DEBUG_MSG(" : ");
      DEBUG_MSG(t);
      DEBUG_MSG("\n");
      send( MyMessage(get_sensor_id() + i, V_TEMP).set( round(t) ));
    }
    _next_read += _interval;
    _waiting = false;

  } else if ( ( ! _waiting ) && millis() > _next_read ) {
    _dt->requestTemperatures();
    _waiting = true;

  } else {

  }
}
