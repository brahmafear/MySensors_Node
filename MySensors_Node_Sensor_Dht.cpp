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

#include "MySensors_Node_Sensor_Dht.h"

MySensors_Node_Sensor_Dht::MySensors_Node_Sensor_Dht( uint8_t temperature_id,
  uint8_t humidity_id, String description, uint8_t pin, uint32_t interval,
  int16_t offset, uint8_t type )
  : MySensors_Node_Sensor( temperature_id, S_TEMP, V_TEMP, description ) {
  _humidity_id = humidity_id;
  _pin = pin;
  _interval = interval;
  _offset = offset;

  _next_read = random( 0, _interval );

  if ( type == DHT11 ) {
    _dht = new SimpleDHT11( );
  } else if ( type == DHT22 ) {
    _dht = new SimpleDHT22( );
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Dht] Error: bad sensor type.\n"));
  }
}

MySensors_Node_Sensor_Dht::~MySensors_Node_Sensor_Dht() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Dht::clone() const {
  return new MySensors_Node_Sensor_Dht( *this );
}

void MySensors_Node_Sensor_Dht::node_sensor_present( ) {
  present( get_sensor_id(), S_TEMP, ( get_description() + " Temperature" ).c_str());
  present( _humidity_id, S_HUM, ( get_description() + " Humidity" ).c_str());
}

void MySensors_Node_Sensor_Dht::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Dht] Setup.\n"));

}

void MySensors_Node_Sensor_Dht::node_sensor_loop( ) {
  if ( millis() > _next_read ) { // time to check
    float temp = 0, hum = 0;

    if( ! _dht->read2( _pin, &temp, &hum, NULL )) {
        temp = getControllerConfig().isMetric ? temp :  1.8 * temp + 32 ;
        temp += _offset;
        DEBUG_MSG(F("[MySensors_Node_Sensor_Dht] Sending Temperature: "));
        DEBUG_MSG(temp);
        DEBUG_MSG(F(", Humidity: "));
        DEBUG_MSG(hum);
        DEBUG_MSG("\n");
        send( MyMessage(get_sensor_id(), V_TEMP).set( temp, 1 ));
        send( MyMessage(_humidity_id, V_HUM).set( hum, 1 ));
    } else {
      DEBUG_MSG(F("[MySensors_Node_Sensor_Dht] Bad read from device.\n"));
    }
    _next_read += _interval;
  }
}
