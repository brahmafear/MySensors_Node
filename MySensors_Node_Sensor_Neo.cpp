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

#include "MySensors_Node_Sensor_Neo.h"

MySensors_Node_Sensor_Neo::MySensors_Node_Sensor_Neo( uint8_t sensor_id,
  uint8_t sensor_type, uint8_t message_type, String description, uint8_t pin, uint16_t count )
  : MySensors_Node_Sensor( sensor_id, sensor_type, message_type, description ) {

  _strip = Adafruit_NeoPixel(count, pin, NEO_RGB + NEO_KHZ800);
  _strip.begin();
  _strip.clear();
  _msg_received = false;
}

MySensors_Node_Sensor_Neo::MySensors_Node_Sensor_Neo( uint8_t sensor_id, String description, uint8_t pin, uint16_t count )
  : MySensors_Node_Sensor_Neo( sensor_id, S_RGB_LIGHT, V_RGB, description, pin, count ) { }


MySensors_Node_Sensor_Neo::~MySensors_Node_Sensor_Neo() {

}

MySensors_Node_Sensor* MySensors_Node_Sensor_Neo::clone() const {
  return new MySensors_Node_Sensor_Neo( *this );
}

void MySensors_Node_Sensor_Neo::node_sensor_receive( const MyMessage &msg ) {
  static long color = 0;
  static uint8_t brightness = 100;
  if ( msg.type == V_RGB ) {
    String data = msg.getString();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] RGB message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");

    color = (long) strtol( &data[0], NULL, 16);
    if ( color == 0 ) {
      set_neo( 0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ));
    } else {
      set_neo( color );
      char buff[10];
      sprintf( buff, "%06X", _strip.getPixelColor(0) );
      send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
    }
    _msg_received = true;

  } else if ( msg.type == V_PERCENTAGE ) {
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] Dimmer message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");

    if ( data == 0 ) {
      set_neo( 0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ));
    } else {
      brightness = constrain( data, 0, 100 );
      _strip.setBrightness( round( 2.55 * brightness ) );
      _strip.show();
      char buff[10];
      sprintf( buff, "%06X", _strip.getPixelColor(0) );
      send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
      send( MyMessage(get_sensor_id(), V_PERCENTAGE ).set( brightness ) );

    }
    _msg_received = true;

  } else if ( msg.type == V_STATUS ) { //Also need to respond to this type
    int data = msg.getInt();
    DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] Status message received for "));
    DEBUG_MSG( get_description() );
    DEBUG_MSG(F(" of value "));
    DEBUG_MSG( data );
    DEBUG_MSG(".\n");
    if ( data == 0 ) {

      set_neo( 0 );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ));

    } else {
      if ( color == 0 ) color = 4210752;

      _strip.setBrightness( 255 );
      for ( uint16_t i = 0; i < _strip.numPixels(); i++ ) {
        _strip.setPixelColor( i, color );
      }
      _strip.setBrightness(brightness);
      _strip.show();

      char buff[10];
      sprintf( buff, "%06X", _strip.getPixelColor(0) );
      send( MyMessage(get_sensor_id(), V_RGB ).set( buff ) );
      send( MyMessage(get_sensor_id(), V_PERCENTAGE ).set( brightness ) );
      send( MyMessage(get_sensor_id(), V_STATUS ).set( 1 ) );
    }
  } else {
    DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] Incorrect message type received.\n"));
  }
}

void MySensors_Node_Sensor_Neo::node_sensor_setup( ) {
  DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] Setup.\n"));
  node_sensor_request();
}

void MySensors_Node_Sensor_Neo::node_sensor_loop( ) {
  static uint32_t delay5s = millis() + 5000;  // Give controller 5s to send previous state
  if ( _msg_received == false && millis() > delay5s ) {  // set to default, inactive state
    DEBUG_MSG(F("[MySensors_Node_Sensor_Neo] Setting default state.\n"));
    set_neo(0);
    send( MyMessage(get_sensor_id(), V_RGB ).set( "000000" ) );
    send( MyMessage(get_sensor_id(), V_PERCENTAGE ).set( 100 ) );
    send( MyMessage(get_sensor_id(), V_STATUS ).set( 0 ) );
    _msg_received = true;
  }
}

void MySensors_Node_Sensor_Neo::set_neo( long color ) {
  for ( uint16_t i = 0; i < _strip.numPixels(); i++ ) {
    _strip.setPixelColor( i, color );
  }
  _strip.show();
}
