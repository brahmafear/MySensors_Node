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

#include "MySensors_Node_Sensor_Dht11.h"

MySensors_Node_Sensor_Dht11::MySensors_Node_Sensor_Dht11( uint8_t temperature_id,
  uint8_t humidity_id, String description, uint8_t pin, uint32_t interval, int16_t offset )
  : MySensors_Node_Sensor( temperature_id, S_TEMP, V_TEMP, description ) {
  _humidity_id = humidity_id;
  _pin = pin;
  _interval = interval;
  _offset = offset;

  _next_read = random( 0, _interval );
}

MySensors_Node_Sensor_Dht11::~MySensors_Node_Sensor_Dht11() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Dht11::clone() const {
  return new MySensors_Node_Sensor_Dht11( *this );
}

void MySensors_Node_Sensor_Dht11::node_sensor_present( ) {
  present( get_sensor_id(), S_TEMP, ( get_description() + " Temperature" ).c_str());
  present( _humidity_id, S_HUM, ( get_description() + " Humidity" ).c_str());
}

void MySensors_Node_Sensor_Dht11::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Dht11] Setup.\n"));
}

void MySensors_Node_Sensor_Dht11::node_sensor_loop( ) {
  if ( millis() > _next_read ) { // time to check
    uint8_t temp, hum;
    SimpleDHT11 dht;
    if( ! dht.read( _pin, &temp, &hum, NULL )) {
        // Uncomment after fix of issue #736 in MySensors github
        temp = getControllerConfig().isMetric ? temp : round( 1.8 * temp + 32 );
        temp += _offset;
        DEBUG_MSG(F("[MySensors_Node_Sensor_Dht11] Sending Temperature: "));
        DEBUG_MSG(temp);
        DEBUG_MSG(F(", Humidity: "));
        DEBUG_MSG(hum);
        DEBUG_MSG("\n");
        send( MyMessage(get_sensor_id(), V_TEMP).set( temp ));
        send( MyMessage(_humidity_id, V_HUM).set( hum ));
    } else {
      DEBUG_MSG(F("[MySensors_Node_Sensor_Dht11] Bad read from device.\n"));
    }
    _next_read += _interval;
  }
}
