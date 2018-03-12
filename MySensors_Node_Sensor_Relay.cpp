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

#include "MySensors_Node_Sensor_Relay.h"

MySensors_Node_Sensor_Relay::MySensors_Node_Sensor_Relay( 
	uint8_t   	sensor_id, 
	uint8_t 	sensor_type, 
	uint8_t 	message_type, 
	String 		description, 
	uint8_t 	r_pin, 
	uint8_t 	s_pin, 
	bool 		r_active,
	uint16_t    pulse,
	uint8_t     input_type,
	bool        s_open )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _r_pin = r_pin;
  _s_pin = s_pin;
  _r_active = r_active;
  _pulse = pulse;
  _input_type = input_type;
  _s_open = s_open;
  
  _next_read = 0ul;
  _next_send = 0ul;
  _state = _s_open;
  _status = V_STOP;
  _sensor_check_interval = 100ul;
  _sensor_send_interval = 300000;
  _pulse_trigger = 0;
}

MySensors_Node_Sensor_Relay::~MySensors_Node_Sensor_Relay() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Relay::clone() const {
  return new MySensors_Node_Sensor_Relay( *this );
}

void MySensors_Node_Sensor_Relay::node_sensor_receive( const MyMessage &msg ) {

  if ( msg.type == V_UP || msg.type == V_DOWN || msg.type == V_STOP ) {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Message received for "));
    DEBUG_MSG( get_description() );
	if ( msg.type == V_UP ) DEBUG_MSG( F(" of type UP.\n"));
	else if ( msg.type == V_DOWN ) DEBUG_MSG( F(" of type DOWN.\n"));
	else if ( msg.type == V_STOP ) DEBUG_MSG( F(" of type STOP.\n"));
	
	_state = msg.type;
	
	digitalWrite( _r_pin, _r_active );
	_pulse_trigger = millis() + _pulse;

  	//send( MyMessage(get_sensorid(), V_UP    ).set( _state == V_UP ) );
  	//send( MyMessage(get_sensorid(), V_DOWN  ).set( _state == V_DOWN ) );
  	//send( MyMessage(get_sensorid(), V_STOP  ).set( _state == V_STOP ) );
  	//send( MyMessage(get_sensorid(), V_STATUS).set( _status ) );
  	_next_send = 0;
  
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Incorrect message type received.\n"));
  }  
  
}

void MySensors_Node_Sensor_Relay::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Setup.\n"));
  // Relay Pin
  digitalWrite( _r_pin, ! _r_active );
  pinMode( _r_pin, OUTPUT );
  
  // Sensor Pin
  pinMode( _s_pin, _input_type );
  
  //node_sensor_request();
}

void MySensors_Node_Sensor_Relay::node_sensor_loop( ) {

  uint32_t now = millis();
  
  // Relay update:
  if ( _pulse_trigger > 0 && (long)(now - _pulse_trigger) >= 0 ) {
    _pulse_trigger = 0;
    digitalWrite( _r_pin, ! _r_active );
    DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Deactivating relay."));
  } else if ( _pulse_trigger > 0 ) {
    // Waiting with relay active
  } else {
    // waiting with relay not active
  }
  
  // Sensor read
  if ( (long)(now - _next_read ) >= 0 ) {
	if ( (digitalRead( _s_pin ) == _s_open) != _status ) {
  	  _status = ! _status;
  	  DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Status change detected."));
  	  
  	  // send update
  	  _next_send = 0; // this will trigger send in next block
  	}
  	_next_read += _sensor_check_interval;
  }
  
  // Sensor force update
  if ( (long)(now - _next_send) >= 0 ) {
  	// send update
	DEBUG_MSG(F("[MySensors_Node_Sensor_Relay] Sending state "));
	if ( _state == V_UP ) DEBUG_MSG(F("UP"));
	else if ( _state == V_DOWN ) DEBUG_MSG(F("DOWN"));
	else if ( _state == V_STOP ) DEBUG_MSG(F("STOP"));
	DEBUG_MSG( _status ? F(" and status open.\n") : F(" and status closed.\n"));

  	
  	send( MyMessage(get_sensor_id(), V_UP    ).set( _state == V_UP ) );
  	send( MyMessage(get_sensor_id(), V_DOWN  ).set( _state == V_DOWN ) );
  	send( MyMessage(get_sensor_id(), V_STOP  ).set( _state == V_STOP ) );
  	send( MyMessage(get_sensor_id(), V_STATUS).set( _status ) );
  	
  	_next_send = now + _sensor_send_interval;
  }
}
