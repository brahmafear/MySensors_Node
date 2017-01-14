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

**GPIO Output**
MySensors_Node_Sensor_Gpio_Out takes either 6 or 4 initialization parameters.  
  * Sensor ID
  * Sensor type
  * Message type
  * Description
  * GPIO pin
  * GPIO "on" state

  Sensor type and message type may be omitted which will default to S_BINARY
  and V_STATUS.  
