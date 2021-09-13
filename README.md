# bad-keyboard

 Arduino keyboard thingy inspired by [this Twitter thread](https://twitter.com/Foone/status/1207892434706825216)

## Hardware requirements

- Arduino with HoodLoader2
- rotary encoder
- 8x8 dotmatrix display
- 8 bit shift register
- pushbutton

## Required libraries

- [HID-Project](https://github.com/NicoHood/HID)
- [RotaryEncoder](https://github.com/mathertel/RotaryEncoder)

## Circuit

- shift register pins:
  - data pin (SER) connected to Arduino pin 4
  - latch pin (SRCLK) connected to Arduino pin 5
  - clock pin (RCLK) connected to Arduino pin 6
  - output pins connected to dotmatrix column pins (lowest pin to leftmost column)
- rotary encoder pins connected to Arduino pin 2 and 3
- button connected between 5V and Arduino analog pin 5, connect 10K resistor between pin 5 and GND
- pins 7 through 12 and A0, A1 connected to dotmatrix row pins (pin 7 to highest row, pin A1 to lowest row)
