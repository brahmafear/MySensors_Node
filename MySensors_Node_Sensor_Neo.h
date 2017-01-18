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

#ifndef __MYSENSORS_NODE_SENSOR_NEO_H
#define __MYSENSORS_NODE_SENSOR_NEO_H

#include <Arduino.h>
#include "MySensors_Node_Sensor.h"
#include "debug.h"
#include <Adafruit_NeoPixel.h>

class MySensors_Node_Sensor_Neo : public MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor_Neo( uint8_t sensor_id,
                                    uint8_t sensor_type,
                                    uint8_t message_type,
                                    String description,
                                    uint8_t pin,          // Pin used by this device
                                    uint16_t count,
                                    uint16_t neo_type = NEO_GRB + NEO_KHZ800
                              );
    MySensors_Node_Sensor_Neo( uint8_t sensor_id, String description, uint8_t pin, uint16_t count );
    ~MySensors_Node_Sensor_Neo();

    //void node_sensor_present();
    void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    //void node_sensor_request();
    MySensors_Node_Sensor* clone() const;

  private:
    bool _msg_received;
    Adafruit_NeoPixel _strip;
    void set_neo( long color );

};


#endif
