/**
 * Bluetooth communication using the BlueSMiRF module.
 * 
 * Author: Hayk Martirosyan
 */

#include <SoftwareSerial.h>

// Set to match your hardware
int RX_PIN = 4;
int TX_PIN = 5;

// Serial interface for the BlueSMiRF
SoftwareSerial bluetooth(RX_PIN, TX_PIN);

// Send and receive buffers
String bluetooth_rx_buffer = "";
String bluetooth_tx_buffer = "";

// Delimiter used to separate messages
char DELIMITER = '\n';

void setup() {
  
  // Start USB communication
  Serial.begin(19200);
  
  // Uncomment this only once, when configuring a new BlueSMiRF
  //set_bluetooth_baudrate();
  
  // Start bluetooth communication
  bluetooth.begin(19200);
  
  Serial.println("Initialized.");
}

void set_bluetooth_baudrate() {
  
  // Open BlueSMiRF at default baudrate
  bluetooth.begin(115200);
  
  // Enter command mode
  bluetooth.print("$$$");  
  
  // Short delay, wait for the Mate to send back CMD
  delay(100);
  
  // Change the baudrate to 19200 bps
  // 115200 is usually too fast for SoftwareSerial to read data properly
  bluetooth.println("SU,19");
}

/**
 * Called when a complete message is received.
 */
void gotMessage(String message) {
  
  Serial.println("[RECV] " + message);
  
  // Do something!
}

/**
 * Finds complete messages from the rx buffer.
 */
void parseReadBuffer() {
  
  // Find the first delimiter in the buffer
  int inx = bluetooth_rx_buffer.indexOf(DELIMITER);
  
  // If there is none, exit
  if (inx == -1) return;
  
  // Get the complete message, minus the delimiter
  String s = bluetooth_rx_buffer.substring(0, inx);
  
  // Remove the message from the buffer
  bluetooth_rx_buffer = bluetooth_rx_buffer.substring(inx + 1);
  
  // Process the message
  gotMessage(s);
  
  // Look for more complete messages
  parseReadBuffer();
}

void parseWriteBuffer() {
  
  // Find the first delimiter in the buffer
  int inx = bluetooth_tx_buffer.indexOf(DELIMITER);
  
  // If there is none, exit
  if (inx == -1) return;
  
  // Get the complete message, including the delimiter
  String message = bluetooth_tx_buffer.substring(0, inx + 1);
  
  // Remove the message from the buffer
  bluetooth_tx_buffer = bluetooth_tx_buffer.substring(inx + 1);
  
  // Send off the message
  bluetooth.print(message);
  Serial.print("[SENT] " + message);
  
  // Look for more
  parseWriteBuffer();
}

/**
 * Continuously sends messages sent from USB and reads in messages from
 * the Bluetooth connection.
 */
void loop() {
  
  // Forward anything received via USB to bluetooth
  if(Serial.available()) {
    
    while(Serial.available()) {
      bluetooth_tx_buffer += (char)Serial.read();
    }
    
    // Look for complete messages
    parseWriteBuffer();
  }
  
  // Add bytes received over bluetooth to the buffer
  if(bluetooth.available()) {
    
    while(bluetooth.available()) {
      bluetooth_rx_buffer += (char)bluetooth.read();
    }
    // Look for complete messages
    parseReadBuffer();
  }
}

