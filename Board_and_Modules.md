- Storing data into the ESP memory.
  - https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#eeprom
- Low power modes for sensors
- Use color sensor for Green color only (hardwire certain pins)
- Verify voltages required by each pins
- Battery-powering the NodeMCU

- Duty Cycling
  - Implementing a manual watchdog : https://www.youtube.com/watch?v=D_7ciW_TCac

- Deep Sleep mode
- Work with Arduino [[Board Characteristics]]
- Interesting Sources
  - [Source 1](https://lastminuteengineers.com/tcs230-tcs3200-color-sensor-arduino-tutorial/)
- Designing for Arduino
  - Verify that [[DHT]] works
  - Verify that [[LDR]] works
  - Verify that [[Moisture Sensor]] works
  - Verify that [[Color Sensor]] works
  - Verify that a message can be displayed on the [[LCD Module]]
- Not a good idea :
  - Verify that a picture can be taken using the [[Camera]]
- Pin labels for ESP8266
- Reference [here](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)

## Pins Requirements
![ESP8622](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?w=817&quality=100&strip=all&ssl=1)

![image](https://www.esp8266.com/wiki/lib/exe/fetch.php?cache=&w=856&h=346&tok=f2e9fd&media=pin_functions.png)

## Module Requirements

| Module / Component           | Requirements |
| ---------------------------- | ------------ |
| DHT11 (Temperature/Humidity) | Signal Pin (Digital Input), VDD, VCC :heavy_check_mark:      |
| LDR                          | (Analog Input) :heavy_check_mark: |
| Moisture Sensor              | D0 (Digital Input), VDD, VCC :heavy_check_mark: |
| Color Sensor GY-31TCS230     | Control Pin S0 (Digital Output), Control Pin S1 (Digital Output), Control Pin S2 (Digital Output), Control Pin S3 (Digital Output), Out (Digital Input), VDD, VCC :heavy_check_mark: |
| LCD Module                   | SDA (I2C SDA); SCL (I2C SCL), VDD, VCC :heavy_check_mark: |
| LED (Watering Pump Signal) | (Digital Output):heavy_check_mark: |
| LED Indicator | (Digital Output) :heavy_check_mark: |
| Button for LCD | (Digital Input):heavy_check_mark: |

## ESP8622 Pins / Module Usage

- I2C Pins : **GPIO5** : SCL; **GPIO4** : SDA
- SPI Pins : **GPIO12**: MISO; **GPIO13**: MOSI; **GPIO14**: SCLK; **GPIO15**: CS
- Software PWM : **GPIO0 to GPIO15**
- Interrupts : **All GPIO pins**, with the exception of **GPIO16**, support interrupts
- **GPIO6 to GPIO11** are connected to the flash chip, so they are not recommended for use.
- If 2% frequency scaling doesn't work on the Color sensor, then we just forego one of the LEDs (UPDATE : Fixed by setting some control pins in the color sensor to always be connected to VDD).

| Pin Label | GPIO       | Input                              | Output                             | Notes                                                        | Associated Module Pin                         |
| --------- | ---------- | ---------------------------------- | ---------------------------------- | ------------------------------------------------------------ | --------------------------------------------- |
| D0        | **GPIO16** | No Interrupt Support               | no PWM or I2C support              | HIGH at boot; used to wake up from deep sleep by connecting pin to RST pin | (USED FOR DEEP SLEEP WAKEUP/CONNECTED TO RST) |
| D1        | **GPIO5**  | OK                                 | OK                                 | often used as SCL (I2C)                                      | LCD Module SCL                                |
| D2        | **GPIO4**  | OK                                 | OK                                 | often used as SDA (I2C)                                      | LCD Module SDA                                |
| D3        | **GPIO0**  | pulled up                          | OK                                 | connected to FLASH button, boot fails if pulled LOW (Board goes into bootloader mode instead) | Moisture Sensor D0                            |
| D4        | **GPIO2**  | pulled up                          | OK                                 | HIGH at boot; connected to on-board LED, boot fails if pulled LOW | Color Sensor Control Pin S0                    |
| D5        | **GPIO14** | OK                                 | OK                                 | SPI (SCLK)                                                   | Color Sensor Control Pin S1                 |
| D6        | **GPIO12** | OK                                 | OK                                 | SPI (MISO)                                                   | LED Indicator                 |
| D7        | **GPIO13** | OK                                 | OK                                 | SPI (MOSI)                                                   | Color Sensor Out                              |
| D8        | **GPIO15** | pulled to GND                      | OK (unexpected behaviour possible) | SPI (CS); Boot fails if pulled HIGH                          | DHT11 Signal Pin                              |
| RX        | **GPIO3**  | OK (unexpected behaviour possible) | RX PIN (AVOID USING)               | HIGH at boot                                                 | Button for LCD                                |
| TX        | **GPIO1**  | TX PIN (AVOID USING)               | OK (unexpected behaviour possible) | HIGH at boot; debug output at boot, boot fails if pulled LOW | LED (Watering Pump Signal)                    |
| A0        | **ADC0**   | OK (Analog Input)                  | DOES NOT WORK                      |                                                              | LDR Analog Read                               |
| GND       |            |                                    |                                    |                                                              |                  |
| VDD       |            |                                    |                                    |                                                              | Color Sensor Control Pin S2  & Color Sensor Control Pin S3                                                |
| RST       |            |                                    |                                    | Pulling the RST pin LOW resets the ESP8266 (similar to pressing the reset button on the board) |                                               |
