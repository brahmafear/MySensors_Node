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

#ifndef __MYSENSORS_NODE_SENSOR_RELAY_H
#define __MYSENSORS_NODE_SENSOR_RELAY_H

#include <Arduino.h>
#include "MySensors_Node_Sensor.h"
#include "debug.h"


class MySensors_Node_Sensor_Relay : public MySensors_Node_Sensor {
  public:

    MySensors_Node_Sensor_Relay(    uint8_t  sensor_id     = 25,
                                    uint8_t  sensor_type   = S_COVER,
                                    uint8_t  message_type  = V_STATUS,
                                    String   description   = "Relay",
                                    uint8_t  r_pin         = 3,          // Pin used by the relay
                                    uint8_t  s_pin         = 4,          // Pin used by position sensor
                                    bool     r_active      = LOW,        // The 'active' state of the relay
                                    uint16_t pulse         = 1000,       // The length of relay pulse
                                    uint8_t  input_type    = INPUT,      // INPUT, INPUT_PULLUP
                                    bool     s_open        = HIGH        // The gpio state for 'open'
                                  );
    ~MySensors_Node_Sensor_Relay();

    //void node_sensor_present();
    void node_sensor_receive( const MyMessage &msg );
    void node_sensor_setup();
    void node_sensor_loop();
    MySensors_Node_Sensor* clone() const;

  private:
    uint8_t  _r_pin;
    uint8_t  _s_pin;
    bool     _r_active;
    uint16_t _pulse;
    uint8_t  _input_type;
    bool     _s_open;
    
    bool     _msg_received;

    uint32_t _next_read;
    bool     _status; // T == open, F == closed
    uint32_t _next_send;
    uint8_t  _state;  // V_UP, V_DOWN, V_STOP
    
    uint32_t _sensor_check_interval;
    uint32_t _sensor_send_interval;
    uint32_t _pulse_trigger;
};

#endif
