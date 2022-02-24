#include <FS.h>

void setup() {
   if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  Serial.begin(9600);
  writeFile(SPIFFS, "/activate.txt", "False");
  writeFile(SPIFFS, "/ssid.txt", "Testing123");
  writeFile(SPIFFS, "/pwd.txt", "123");
  // put your setup code here, to run once:

}

void loop() {
Serial.println(readFile(SPIFFS, "/activate.txt"));
Serial.println(readFile(SPIFFS, "/ssid.txt"));
Serial.println(readFile(SPIFFS, "/pwd.txt"));
delay(2000);
}




String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if (!file) {
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while (file.available()) {
    fileContent += String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}
