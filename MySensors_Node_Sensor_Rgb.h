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

#ifndef __MYSENSORS_NODE_SENSOR_RGB_H
#define __MYSENSORS_NODE_SENSOR_RGB_H

#include <Arduino.h>
#include "MySensors_Node_Sensor.h"
#include "debug.h"

class MySensors_Node_Sensor_Rgb : public MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor_Rgb(  uint8_t sensor_id       = 33,
                                uint8_t sensor_type     = S_RGB_LIGHT,
                                uint8_t message_type    = V_RGB,
                                String description      = "RGB",
                                uint8_t red_pin         = 3,          // Pins used by this device
                                uint8_t grn_pin         = 5,
                                uint8_t blu_pin         = 6,
                                bool active             = true        // The 'active' state of the device
                              );
    // MySensors_Node_Sensor_Rgb( uint8_t sensor_id, String description, uint8_t red_pin, uint8_t grn_pin, uint8_t blu_pin, bool active );
    ~MySensors_Node_Sensor_Rgb();

    //void node_sensor_present();
    void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    //void node_sensor_request();
    MySensors_Node_Sensor* clone() const;

  private:
    uint8_t  _red_pin;
    uint8_t  _grn_pin;
    uint8_t  _blu_pin;
    bool     _active;
    bool     _msg_received;

    uint8_t _r_ideal, _r_actual, _b_ideal, _b_actual, _g_ideal, _g_actual;
    uint8_t _brightness = 100;
    uint32_t _delay5s;

    void set_rgb( uint8_t r, uint8_t g, uint8_t b );

};


#endif
