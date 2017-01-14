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

#ifndef __MYSENSORS_NODE_SENSOR_GPIO_OUT_H
#define __MYSENSORS_NODE_SENSOR_GPIO_OUT_H

#include <Arduino.h>
#include "MySensors_Node_Sensor.h"
#include "debug.h"

class MySensors_Node_Sensor_Gpio_Out : public MySensors_Node_Sensor {
  public:
    MySensors_Node_Sensor_Gpio_Out( uint8_t sensor_id, 
                                    uint8_t sensor_type,
                                    uint8_t message_type,
                                    String description,
                                    uint8_t pin,          // Pin used by this device
                                    bool active );        // The 'active' state of the device
    MySensors_Node_Sensor_Gpio_Out( uint8_t sensor_id, String description, uint8_t pin, bool active );
    ~MySensors_Node_Sensor_Gpio_Out();

    //void node_sensor_present();
    void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    MySensors_Node_Sensor* clone() const;

  private:
    uint8_t  _pin;
    bool     _active;
    bool     _msg_received;

};


#endif
