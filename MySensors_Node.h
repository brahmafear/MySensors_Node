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

#ifndef __MYSENSORS_NODE_H
#define __MYSENSORS_NODE_H

#define __MYSENSORS_NODE_VERSION    "0.97"

#include <Arduino.h>
#include "core/MyMessage.h"
#include "core/MySensorsCore.h"

#include "debug.h"
#include "vector.h"
#include "MySensors_Node_Sensor.h"

#include "MySensors_Node_Sensor_Gpio_Out.h"                         // List all types of sensors here to prevent
#include "MySensors_Node_Sensor_Gpio_In.h"                          // need to import from main sketch
#include "MySensors_Node_Sensor_Analog_In.h"
#include "MySensors_Node_Sensor_Pwm.h"
#include "MySensors_Node_Sensor_Dht.h"
#include "MySensors_Node_Sensor_Dht11.h"
#include "MySensors_Node_Sensor_Dht22.h"
#include "MySensors_Node_Sensor_DS18X.h"
#include "MySensors_Node_Sensor_Rgb.h"
#include "MySensors_Node_Sensor_Neo.h"
#include "MySensors_Node_Sensor_Relay.h"


class MySensors_Node {

  public:

    MySensors_Node( String description, String ver );
    ~MySensors_Node();
    bool add_sensor( MySensors_Node_Sensor *sensor );
    void present( void );
    void receive( const MyMessage &msg );
    void setup();
    void loop();

  private:

    String _description;
    String _version;
    Vector< MySensors_Node_Sensor* > _node_sensors;
};

#endif
