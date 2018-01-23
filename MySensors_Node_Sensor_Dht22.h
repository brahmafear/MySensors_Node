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

#ifndef __MYSENSORS_NODE_SENSOR_DHT22_H
#define __MYSENSORS_NODE_SENSOR_DHT22_H

#include <Arduino.h>
#include "core/MySensorsCore.h"
#include "MySensors_Node_Sensor.h"
#include "debug.h"
#include "SimpleDHT.h"

class MySensors_Node_Sensor_Dht22 : public MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor_Dht22( uint8_t  temperature_id  = 10,
                                 uint8_t  humidity_id     = 11,
                                 String   description     = "DHT",
                                 uint8_t  pin             = 4,      // Pin for dht22 device
                                 uint32_t interval        = 120000, // How often to read and send in ms
                                 int16_t  offset          = 0       // Fixed offset of temperature
                               );
    ~MySensors_Node_Sensor_Dht22();

    void node_sensor_present();
    //void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    MySensors_Node_Sensor* clone() const;

  private:
    uint8_t  _humidity_id;
    uint8_t  _pin;
    uint32_t _interval;
    int16_t  _offset;

    uint32_t _next_read;
};


#endif
