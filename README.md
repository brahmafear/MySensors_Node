# MySensors_Node Library


MySensors Node is a companion software to work with the [MySensors library](http://www.mysensors.org)
for wireless sensor/actuator connection to a home automation / monitoring
system.  This software is designed to be used on the sensor / actuator device
running on a Arduino microcontroller.  The base software can be expanded to
include additional functionality by extending the abstract MySensor_Node_Sensor
class.  See the example sketch for usage details.

Created by Dave Myers <brahmafear@gmail.com>
Copyright (c) 2017

http://github.com/brahmafear/

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

**Library notes:**

  * No checks are made for sane values!  So don't set gpio pin to 999 or input
type to a non-constant-defined value!

  * This setup relies upon polling and offers no sleep functionality.  As such, it is
*highly unsuited* for battery-powered operation.  

  * Designed and tested for use with [HomeAssistant](https://home-assistant.io/).  
  No other controllers have been test.




Built in sensor/actuator types are listed below.  Other types can be created by extending the
MySensors_Node_Sensor class.  

**GPIO Output**

MySensors_Node_Sensor_Gpio_Out is suitable for any binary indicator or output.
  * Sensor ID -- the child id of this sensor / actuator, default 5
  * Sensor type -- the type from MySensors library, default S_BINARY
  * Message type -- the message type associated with above type, default V_STATUS
  * Description -- a description to pass to controller, default "Output"
  * GPIO pin -- the microcontroller gpio pin to manipulate, default 2
  * GPIO "on" state -- true for active high, false for active low, default true

**GPIO Input**

MySensors_Node_Sensor_Gpio_In is suitable for PIR motion sensors, door/window sensors, ....
  * Sensor ID -- the child id of this sensor / actuator, default 20
  * Sensor type -- the type from MySensors library, default S_MOTION
  * Message type -- the message type associated with above type, default V_TRIPPED
  * Description -- a description to pass to controller, default "Motion"
  * GPIO pin -- the microcontroller gpio pin to read, default A2
  * GPIO "on" state -- true for active high, false for active low, default true
  * Input type -- INPUT, INPUT_PULLUP, or INPUT_PULLDOWN, default INPUT_PULLUP
      - note: dependent on microcontroller supporting that feature on that pin
  * Interval -- frequency in ms to read and post to controller, default 500

**PWM Output**

MySensors_Node_Sensor_Pwm primarily intended for use as a dimmable light but could
possibly be used for servo control or other pulse width modulation needs.
  * Sensor ID -- the child id of this sensor / actuator, default 30
  * Sensor type -- the type from MySensors library, default S_DIMMER
  * Message type -- the message type associated with above type, default V_PERCENTAGE
  * Description -- a description to pass to controller, default "Dimmer"
  * GPIO pin -- the microcontroller gpio pin to manipulate, default 6
  * GPIO "on" state -- true for active high, false for active low, default true
  * Percentage -- true if message is 0-100 representing a percentage, default true
  * Max Value -- the value which represents a 100% pwm duty cycle, default 255

**Analog Input**

MySensors_Node_Sensor_Analog_In is intended for use with CdS light-dependent resistors
but can be used to measure and report any analog value.
  * Sensor ID -- the child id of this sensor / actuator, default 15
  * Sensor type -- the type from MySensors library, default S_LIGHT_LEVEL
  * Message type -- the message type associated with above type, default V_LIGHT_LEVEL
  * Description -- a description to pass to controller, default "Light Level"
  * GPIO pin -- the microcontroller gpio pin to read, default A3
  * Pullup -- true to activate pullup resistor, default true
  * Active -- set to false to reverse value, default false
  * Percentage -- true if message is 0-100 representing a percentage, default true
  * Max Value -- the value which represents a 100% reading, default 1023
  * Interval -- frequency in ms to read and post to controller, default 60000

**DHT Temperature/Humidity Sensor**  

MySensors_Node_Sensor_Dht is intended for use with DHT11/DHT22 sensor.
  * Temperature ID -- the child id for temperature, default 10
  * Humidity ID -- the child id for humidity, default 11
  * Description -- a description to pass to controller, default "DHT"
  * GPIO pin -- the microcontroller gpio pin connected to DHT11, default 4
  * Interval -- frequency in ms to read and post to controller, default 120000
  * Offset -- negative or positive value that temperature reading should be adjusted by, default 0
  * Type -- "DHT11" or "DHT22" depending on sensor type

**DS18X Temperature Sensor**

MySensors_Node_Sensor_DS18X is intended for use with DS18X temperature sensor.
  * Temperature ID -- the first child id for temperature, default 10
  * Description -- a description to pass to controller, default "DS18X"
  * GPIO pin -- the microcontroller gpio pin connected to the OneWire bus, default 2
  * Interval -- frequency in ms to read and post to controller, default 120000
  * Offset -- negative or positive value that temperature reading should be adjusted by, default 0
  * Count -- the number of devices on this bus, each device will use child id incremented by one

**RGB LED**

MySensors_Node_Sensor_Rgb is intended for use as a dimmable, multicolor light.
  * Sensor ID -- the child id of this sensor / actuator, default 33
  * Sensor type -- the type from MySensors library, default S_RGB_LIGHT
  * Message type -- the message type associated with above type, default V_RGB
  * Description -- a description to pass to controller  , default "RGB"
  * Red pin -- the rgb red pin, default 3
  * Green pin -- the rgb green pin, default 5
  * Blue pin -- the rgb blue pin, default 6
  * GPIO "on" state -- true for active high, false for active low, default true

**NeoPixel**

MySensors_Node_Sensor_Neo is intended for use as with WS2812 'NeoPixel' LEDs.
  * Sensor ID -- the child id of this sensor / actuator, default 36
  * Sensor type -- the type from MySensors library, default S_RGB_LIGHT
  * Message type -- the message type associated with above type, default V_RGB
  * Description -- a description to pass to controller  , default "NeoPixel"
  * Pin -- the pin connected to NeoPixel In, default 8
  * Count -- the number of LEDs in NeoPixel array, default 24
  * NeoPixel Type -- Specific to certain models of LED, default NEO_GRB + NEO_KHZ800

**Relay**

MySensors_Node_Sensor_Relay is a specific use for using a relay to control a 'dumb' garage door.
  * Sensor ID -- the child id of this sensor / actuator, default 25
  * Sensor type -- the type from MySensors library, default S_COVER
  * Message type -- the message type associated with above type, default V_STATUS
  * Description -- a description to pass to controller  , default "Relay"
  * Relay Pin -- the pin connected to the relay control, default 3
  * Sensor Pin -- the pin connected to the sensor determining door position, default 4
  * Relay active -- the gpio state that will cause the relay to be active, default LOW
  * Pulse length -- the length in ms for how long the relay should be active when triggered, default 1000
  * Input type -- the type for pinMode for the sensor pin, default INPUT_PULLUP
  * Sensor active -- The gpio state that represents the door open, default HIGH
