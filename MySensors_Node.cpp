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

#include "MySensors_Node.h"

MySensors_Node::MySensors_Node( String description, String ver ) {
  _description = description;
  _version = ver;
}

MySensors_Node::~MySensors_Node() {

}

bool MySensors_Node::add_sensor( MySensors_Node_Sensor *sensor ) {
  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    if ( _node_sensors[i]->get_sensor_id() == sensor->get_sensor_id() ) return false;
  }

  // _node_sensors.push_back(sensor->clone());
  _node_sensors.push_back( sensor );

  DEBUG_MSG(F("[MySensors_Node] Added: "));
  DEBUG_MSG( sensor->get_description() );
  DEBUG_MSG("\n");
  return true;
}

void MySensors_Node::present() {
  sendSketchInfo( _description.c_str(), _version.c_str() );

  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    _node_sensors[i]->node_sensor_present();
  }

}

void MySensors_Node::receive( const MyMessage &msg ) {

  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    if ( msg.sensor == _node_sensors[i]->get_sensor_id() ) {
      _node_sensors[i]->node_sensor_receive( msg );
      break; // exit loop early since no sensor should have same id as another
    }
  }

}

void MySensors_Node::setup() {

  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    _node_sensors[i]->node_sensor_setup();
  }

  DEBUG_MSG(F("[MySensors_Node] "));
  DEBUG_MSG( __MYSENSORS_NODE_VERSION );
  DEBUG_MSG(F(" with sketch "));
  DEBUG_MSG( _description );
  DEBUG_MSG(F(" version "));
  DEBUG_MSG( _version );
  DEBUG_MSG(F(" node ID: "));
  DEBUG_MSG( getNodeId() );
  DEBUG_MSG(F(" and parent ID: "));
  DEBUG_MSG( getParentNodeId() );
  DEBUG_MSG(F(" with features:\n"));
  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    DEBUG_MSG(" * ");
    DEBUG_MSG( _node_sensors[i]->get_sensor_id() );
    DEBUG_MSG(" ");
    DEBUG_MSG( _node_sensors[i]->get_sensor_type() );
    DEBUG_MSG(" ");
    DEBUG_MSG( _node_sensors[i]->get_description() );
    DEBUG_MSG("\n");
  }
}

void MySensors_Node::loop() {

  for ( uint8_t i = 0; i < _node_sensors.size(); i++ ) {
    _node_sensors[i]->node_sensor_loop();
  }
}
