# INF535 - Plant Companion

- Group Members : Chinonso Stanislaus Ngwu, Hadi Rayan Al-Sandid

- The code for the Plant Companion is in the "Controller/" folder; the code fo the web-server is under the "server files/" folder.

## Description:
- The Plant Companion is an Arduino-based system that uses sensors to collect data relevant to maintaining a plant & irrigates the plant when necessary to do so. Data about soil humidity, soil temperature, and light intensity is collected by the sensors.
- This data will be used to (1) automatically water the plant if needed, with a local water pump; (2) warn users of any abnormality in environment which could affect the plant

## Activation Process for the Plant Companion

- When the device is powered on for the first time, the ESP sends a HTTP request to the server to retrieve configuration information.

- The server replies with a json file containing all the configuration parameters such as Activation status, Moisture Level Threshold and Manual Pump Status and Wi-Fi Credentials.

- This JSON file is decoded by the ESP and saved inside a file locally on the ESP after which it restarts with the newly saved configuration parameters.

- The ESP keeps checks for this configuration periodically and updates the files accordinly. (This can be likened to software updates where the system is usually restarted after the new updates to pick up the new configuration)

## Sending Data
- When readings are taken from the sensors, it is encoded in a request string and sent to the server via a HTTP POST request, the server processes this request and saves them to the DB.

## Loading Configuration Data
- The configuration data includes;
1. Wi-Fi SSID
2. Wi-Fi Password
3. Device Status: 1(Activated), 0(Not Activated)
4. Minimum Soil Mositure
- The configurations from the server are saved to a files permanently on the ESP file system and is loaded during the setup process of the controller.

## How to run the server

- Download the server files

- Install XAMP

- Start Apache and MySQL from the XAMP control panel

- Copy project documents and paste inside the htdocs folder in your XAMP directory <C:\xampp\htdocs> 

- Open your browser and navigate to http://localhost/phpmyadmin
- Create a database plant_companion, click on import and select the DB.sql file from the downloaded server files  to import your DB files

- Open your browser and navigate to http://localhost/ or http://localhost/the_folder_pasted_the_server_files

- Your website should be running with no issues
