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

#ifndef __MYSENSORS_NODE_SENSOR_H
#define __MYSENSORS_NODE_SENSOR_H

#include <Arduino.h>
#include "debug.h"
#include "core/MyMessage.h"
#include "core/MySensorsCore.h"

// abstract for other node features
class MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor( uint8_t sensor_id,         // ID of this sensor
                           uint8_t sensor_type,       // The sensor type from the MySensors library
                           uint8_t message_type,      // The message type from the MySensors library
                           String description         // A description of this sensor to send to controller
                         );
    ~MySensors_Node_Sensor();

    virtual void node_sensor_present();                           // These are defaults that
    virtual void node_sensor_request();                           // can be used by children
    virtual void node_sensor_setup();
    virtual void node_sensor_loop();
    virtual void node_sensor_receive( const MyMessage &msg );
    virtual MySensors_Node_Sensor* clone() const = 0;             // This must be overridden by all children


    uint8_t get_sensor_id();
    uint8_t get_sensor_type();
    uint8_t get_message_type();
    String  get_description();

  protected:


  private:
    uint8_t  _sensor_id;
    uint8_t  _sensor_type;
    uint8_t  _message_type;
    String   _description;


};


#endif
