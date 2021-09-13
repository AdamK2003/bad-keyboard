#include <HID-Project.h>
#include <HID-Settings.h>


void setup() {
  Serial1.begin(38400);
  Keyboard.begin();
}

void loop() {
  if(Serial1.available()) {
  
    int read = Serial1.read();

    if(read == 30) {
      Keyboard.write(KEY_BACKSPACE);
    } else if (read == 31) {
      Keyboard.write(KEY_RETURN);
    } else {
      Keyboard.write(read);
    }
  }
}
