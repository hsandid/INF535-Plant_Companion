## Sketches List

- `01_DHT11_Humidty_Temperature`
  - **Purpose :** Configure DHT11 sensor (connected to Pin 3) and read Humidity/Temperature values
- `02_ESP8266_Connecting_to_Wi-Fi`
  - **Purpose :** Connecting the ESP8266 to wifi "IoT" with password "Polytechnique"
  - Code mostly taken from example sketch in Arduino IDE
- `03_Hardware_Interrupts_0_and_1`
  - **Purpose :** Show how to invoke interrupt functions for both HW interrupts 0 and 1 on pins 2 and 3 of the Arduino UNO respectively
  - Used in conjunction with Sleep to wake the device
  - (What about the ESP ?)
- `04_LCD_Message`
  - **Purpose :** Using LCD, we want to display a message
- `05_LDR_DetectingLightLevel`
  - **Purpose :** Sample analog value of an LDR connected to A0.
- `06_Timer1_Interrupts`
  - **Purpose :** Shows how to use Timer1 with Interrupts
- `07_WATCHDOG_Duty_Cycling_and_SLEEPMODE`
  - **Purpose :** Configure Watchdog Duty Cycling (4 sec default)

## Programming Advice

- Using a `switch` statement saves memory compared to iterative `if/else` statements.
- Using `volatile` for variables is important if they are used in both interrupt routines and the main loop.
- Avoid creating functions if they are not called more than once.
- Some functions like `millis()` and `delay()` do not function inside of interrupt routines (i.e. all calls will return the same result).
- Use `#define` with Arduino ports for simplicity and portability.