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

#ifndef __MYSENSORS_NODE_SENSOR_ANALOG_IN_H
#define __MYSENSORS_NODE_SENSOR_ANALOG_IN_H

#include <Arduino.h>
#include "MySensors_Node_Sensor.h"
#include "debug.h"

class MySensors_Node_Sensor_Analog_In : public MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor_Analog_In( uint8_t  sensor_id       = 15,
                                     uint8_t  sensor_type     = S_LIGHT_LEVEL,
                                     uint8_t  message_type    = V_LIGHT_LEVEL,
                                     String   description     = "Light Level",
                                     uint8_t  pin             = A3,             // Pin for analog device
                                     bool     pullup          = true,           // True if pullup resistor should be activated
                                     bool     active          = false,          // If false, value will be reversed
                                     bool     percentage      = true,           // If true, value will be sent as 0-100 % of max value
                                     uint16_t max_value       = 1024,           // Max value of device - normally 1024
                                     uint32_t interval        = 60000           // How often to read and send in ms
                                   );
    /* MySensors_Node_Sensor_Analog_In( uint8_t sensor_id, String description, uint8_t pin, bool pullup, bool active,
                                     bool percentage, uint16_t max_value, uint16_t interval );
    */
    ~MySensors_Node_Sensor_Analog_In();

    //void node_sensor_present();
    //void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    MySensors_Node_Sensor* clone() const;

  private:
    uint8_t  _pin;
    bool     _pullup;
    bool     _active;
    bool     _percentage;
    uint16_t _max_value;
    uint32_t _interval;

    uint32_t _next_read;
};


#endif
