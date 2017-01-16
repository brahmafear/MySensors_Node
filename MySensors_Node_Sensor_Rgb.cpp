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

#include "MySensors_Node_Sensor_Rgb.h"

MySensors_Node_Sensor_Rgb::MySensors_Node_Sensor_Rgb( uint8_t sensor_id,
  uint8_t sensor_type, uint8_t message_type, String description, uint8_t red_pin, uint8_t grn_pin, uint8_t blu_pin,
  bool active )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {
  _red_pin = red_pin;
  _grn_pin = grn_pin;
  _blu_pin = blu_pin;
  _active = active;
  _msg_received = false;
}

MySensors_Node_Sensor_Rgb::MySensors_Node_Sensor_Rgb( uint8_t sensor_id,
  String description, uint8_t red_pin, uint8_t grn_pin, uint8_t blu_pin, bool active )
  : MySensors_Node_Sensor_Rgb( sensor_id, S_RGB_LIGHT, V_RGB, description,
    red_pin, grn_pin, blu_pin, active ) { }


MySensors_Node_Sensor_Rgb::~MySensors_Node_Sensor_Rgb() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Rgb::clone() const {
  return new MySensors_Node_Sensor_Rgb( *this );
}

void MySensors_Node_Sensor_Rgb::node_sensor_receive( const MyMessage &msg ) {
  static uint8_t r_ideal = 0, r_actual = 0, b_ideal = 0, b_actual = 0, g_ideal = 0, g_actual = 0;
  static uint8_t brightness = 100;
  if ( msg.type == V_RGB ) {
    String data = msg.getString();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] RGB message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");

    long number = (long) strtol( &data[0], NULL, 16);
    r_ideal = ( number >> 16 );
    g_ideal = ( number >> 8 & 0xFF );
    b_ideal = ( number & 0xFF );
    r_actual = round(( brightness / 100.0 ) * r_ideal );
    g_actual = round(( brightness / 100.0 ) * g_ideal );
    b_actual = round(( brightness / 100.0 ) * b_ideal );
    set_rgb( r_actual, g_actual, b_actual );
    char buff[10];
    sprintf( buff, "%02X%02X%02X", r_actual, g_actual, b_actual );
    send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
    _msg_received = true;


  } else if ( msg.type == V_PERCENTAGE ) {
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] Dimmer message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");

    if ( data == 0 ) {
      set_rgb( 0,0,0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ));
    } else {
      brightness = constrain( data, 0, 100 );
      r_actual = round(( brightness / 100.0 ) * r_ideal );
      g_actual = round(( brightness / 100.0 ) * g_ideal );
      b_actual = round(( brightness / 100.0 ) * b_ideal );
      set_rgb( r_actual, g_actual, b_actual );
      char buff[10];
      sprintf( buff, "%02X%02X%02X", r_actual, g_actual, b_actual );
      send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
      send( MyMessage(get_sensor_id(), V_PERCENTAGE ).set( brightness ) );

    }
    _msg_received = true;

  } else if ( msg.type == V_STATUS ) { //Also need to respond to this type
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] Status message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");
    if ( data == 0 ) {
      set_rgb( 0,0,0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ));
    } else {
      if ( r_actual + g_actual + b_actual == 0 ) {
        r_ideal = 255; g_ideal = 255; b_ideal = 255;
        r_actual = 255; g_actual = 255; b_actual = 255;
      }

      set_rgb( r_actual, g_actual, b_actual );
      char buff[10];
      sprintf( buff, "%02X%02X%02X", r_actual, g_actual, b_actual );
      send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 1 ) );
    }
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] Incorrect message type received.\n"));
  }
}

void MySensors_Node_Sensor_Rgb::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] Setup.\n"));
  pinMode( _red_pin, OUTPUT );
  pinMode( _grn_pin, OUTPUT );
  pinMode( _blu_pin, OUTPUT );
  node_sensor_request();
}

void MySensors_Node_Sensor_Rgb::node_sensor_loop( ) {
  static uint32_t delay5s = millis() + 5000;  // Give controller 5s to send previous state
  if ( _msg_received == false && millis() > delay5s ) {  // set to default, inactive state
    DEBUG_MSG(F("[MySensors_Node_Sensor_Rgb] Setting default state.\n"));
    set_rgb(0,0,0);
    send( MyMessage(get_sensor_id(), V_RGB ).set( "000000" ) );
    send( MyMessage(get_sensor_id(), V_PERCENTAGE ).set( 100 ) );
    send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ) );
    _msg_received = true;
  }
}

void MySensors_Node_Sensor_Rgb::set_rgb( uint8_t r, uint8_t g, uint8_t b ) {
  r = constrain( r, 0, 255 );
  g = constrain( g, 0, 255 );
  b = constrain( b, 0, 255 );
  analogWrite( _red_pin, _active ? r : 255 - r );
  analogWrite( _grn_pin, _active ? g : 255 - g );
  analogWrite( _blu_pin, _active ? b : 255 - b );
}
