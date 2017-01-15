# MySensors_Node Library


MySensors Node is a companion software to work with the [MySensors library](http://www.mysensors.org)
for wireless sensor/actuator connection to a home automation / monitoring
system.  This software is designed to be used on the sensor / actuator device
running on a Arduino microcontroller.  The base software can be extended to
include additional functionality by extending the abstract MySensor_Node_Sensor
class.  

Created by Dave Myers <brahmafear@gmail.com>
Copyright (c) 2017

http://github.com/brahmafear/

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.


See the example sketch for how to use.  Built in sensor types are listed below.
Note: No checks are made for sane values!  So don't set gpio pin to 999 or input
type to a non-constant-defined value!

This setup relies upon polling and offers no sleep functionality.  As such, it is
*highly unsuited* for battery-powered operation.  

**GPIO Output**
MySensors_Node_Sensor_Gpio_Out takes either 6 or 4 initialization parameters.  
  * Sensor ID -- the child id of this sensor / actuator
  * Sensor type -- the type from MySensors library, defaults to S_BINARY
  * Message type -- the message type associated with above type, defaults to V_STATUS
  * Description -- a description to pass to controller
  * GPIO pin -- the microcontroller gpio pin to manipulate
  * GPIO "on" state -- true for active high, false for active low

  Sensor type and message type may be omitted which will default to S_BINARY
  and V_STATUS.  

**GPIO Input**
MySensors_Node_Sensor_Gpio_In takes either 8 or 6 initialization parameters.  
  * Sensor ID -- the child id of this sensor / actuator
  * Sensor type -- the type from MySensors library, defaults to S_MOTION
  * Message type -- the message type associated with above type, defaults to V_TRIPPED
  * Description -- a description to pass to controller
  * GPIO pin -- the microcontroller gpio pin to read
  * GPIO "on" state -- true for active high, false for active low
  * Input type -- INPUT, INPUT_PULLUP, or INPUT_PULLDOWN - note: microcontroller dependent
  * Interval -- frequency in ms to read and post to controller

**PWM Output**
MySensors_Node_Sensor_Pwm takes either 8 or 6 initialization parameters.  
  * Sensor ID -- the child id of this sensor / actuator
  * Sensor type -- the type from MySensors library, defaults to S_DIMMER
  * Message type -- the message type associated with above type, defaults to V_PERCENTAGE
  * Description -- a description to pass to controller  
  * GPIO pin -- the microcontroller gpio pin to manipulate
  * GPIO "on" state -- true for active high, false for active low
  * Percentage -- true if message from controller is a 0-100 representing a percentage
  * Max Value -- the value which represents a 100% pwm duty cycle, usually 255

**Analog Input**
MySensors_Node_Sensor_Analog_In takes either 8 or 6 initialization parameters.  
  * Sensor ID -- the child id of this sensor / actuator
  * Sensor type -- the type from MySensors library, defaults to S_MOTION
  * Message type -- the message type associated with above type, defaults to V_TRIPPED
  * Description -- a description to pass to controller
  * GPIO pin -- the microcontroller gpio pin to read
  * Percentage -- true if message to controller is a 0-100 representing a percentage
  * Max Value -- the value which represents a 100% reading, usually 1023
  * Interval -- frequency in ms to read and post to controller
