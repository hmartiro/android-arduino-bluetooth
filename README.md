android-arduino-bluetooth
=========================

Demo of a clean and robust way to interface Android and Arduino devices over a Bluetooth connection.

**Features:**

 * Bluetooth using SoftwareSerial on Arduino
 * Separate thread for Bluetooth RX/TX in Android
 * Basic UI for connecting, disconnecting, reading, and writing
 * Exception handling for failed connections
 * Parsing of complete messages using a delimiter character
 * Forwarding of messages from USB serial to bluetooth on Arduino
 * Lots of comments

**Requirements:**

 * Android device with Bluetooth enabled.
 * Arduino with a Bluetooth module (BlueSMiRF Silver tested), wired to digital input pins.
 * Android Studio and an Arduino IDE.

**Usage:**

 * For Android, set the MAC address of your Bluetooth module in `BluetoothActivity.java`.
 * For Arduino, set the RX and TX pin numbers you wired up.
 * Load the Android app, the Arduino sketch, and hit Connect.

**Issues:**

 * Bluetooth socket still fails to connect once in a while (my hardware?)
 * Can't seem to get higher than 19200 bps with SoftwareSerial
 * Connected/disconnected events in Android should have their own message types
 * Handle arbitrary data (delimiter) by implementing escape character (possibly overkill)
