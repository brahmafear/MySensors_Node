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

#include "MySensors_Node_Sensor_Pwm.h"

MySensors_Node_Sensor_Pwm::MySensors_Node_Sensor_Pwm( uint8_t sensor_id,
  uint8_t sensor_type, uint8_t message_type, String description, uint8_t pin,
  bool active, bool percentage, uint16_t max_value )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _pin = pin;
  _active = active;
  _percentage = percentage;
  _max_value = max_value;
  _msg_received = false;
}

MySensors_Node_Sensor_Pwm::MySensors_Node_Sensor_Pwm( uint8_t sensor_id,
  String description, uint8_t pin, bool active, bool percentage, uint16_t max_value )
  : MySensors_Node_Sensor_Pwm( sensor_id, S_DIMMER, V_PERCENTAGE, description,
    pin, active, percentage, max_value ) { }


MySensors_Node_Sensor_Pwm::~MySensors_Node_Sensor_Pwm() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Pwm::clone() const {
  return new MySensors_Node_Sensor_Pwm( *this );
}

void MySensors_Node_Sensor_Pwm::node_sensor_receive( const MyMessage &msg ) {
  static uint16_t prev_data = _max_value;
  if ( msg.type == get_message_type() ) {
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Pwm] Dimmer message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");
    set_pwm( data );
    send( MyMessage(get_sensor_id(), get_message_type()).set(data) );
    send( MyMessage(get_sensor_id(), V_STATUS ).set( data > 0 ? 1 : 0 ) );
    if ( data != 0 ) prev_data = data; // don't save if we are turning off
    _msg_received = true;
  } else if ( msg.type == V_STATUS ) { //Also need to respond to this type
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Pwm] Status message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");
    if ( data == 0 ) {
      set_pwm( 0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ) );
    } else {
      set_pwm( prev_data );
      send( MyMessage(get_sensor_id(), get_message_type()).set(prev_data) );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 1 ) );
    }
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Pwm] Incorrect message type received.\n"));
  }
}

void MySensors_Node_Sensor_Pwm::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Pwm] Setup.\n"));
  pinMode( _pin, OUTPUT );
  node_sensor_request();
}

void MySensors_Node_Sensor_Pwm::node_sensor_loop( ) {
  static uint32_t delay5s = millis() + 5000;  // Give controller 5s to send previous state
  if ( _msg_received == false && millis() > delay5s ) {  // set to default, inactive state
    DEBUG_MSG(F("[MySensors_Node_Sensor_Pwm] Setting default state.\n"));
    //analogWrite( _pin, 0 );
    set_pwm( 0 );
    send( MyMessage(get_sensor_id(), get_message_type()).set( 0 ));
    send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ) );
    _msg_received = true;
  }
}

void MySensors_Node_Sensor_Pwm::set_pwm(uint16_t data) {
  if ( _percentage ) data = round( constrain(data, 0, 100) / 100.0 * _max_value );
  if ( ! _active ) data = _max_value - data;
  analogWrite( _pin, data );
}
