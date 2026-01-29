/*
 *  It should not be necessary to change anything else than in this file to suit
 * your needs. If you need to change other things, consider adding to this file
 * and submit a pull request :) Remember that all password, SSID´s and so on are
 * CASE SENSITIVE !
 */

// Change config to verify that project has been configured
#ifndef CONFIGURED
#define CONFIGURED                                                             \
  1 // Change this to "1" when you completed your config and begin upload
#endif

// WIFI settings
#ifndef WIFI_SSID                // If already defined skip defining it again
#define WIFI_SSID "SECRET_SSID"      //"SECRET_SSID"  // Put in your SSID
#define WIFI_PASSWORD "SECRET_PASSWORD" //"SECRET_PASSWORD" // Put in your SSID Password
#endif

// LED settings
#define WIFI_LED LED_BUILTIN // Blue led on NodeMCU
#define USE_WIFI_LED                                                           \
  true // if 'true', the blue led in a NodeMCU will blink during connection,
       // and glow solid once connected
// MQTT settings
#ifndef MQTT_SERVER             // If already defined skip defining it again
#define MQTT_SERVER "SECRET_MQTT_IP" // Put in the IP addresses of your MQTT broker
#endif
#ifndef MQTT_USERNAME // If already defined skip defining it again
#define MQTT_USERNAME                                                          \
  "SECRET_MQTT_CRED" // Username for the MQTT broker (NULL if no username is required)
#define MQTT_PASSWORD                                                          \
  "SECRET_MQTT_CRED" // Password for the MQTT broker (NULL if no password is required)
#endif
#define MQTT_SEND_INTERVAL                                                     \
  600000 // normally set to 180000 milliseconds = 3 minutes. Define as you like

// Serial port
#define SERIAL_CHOICE SERIAL_HARDWARE // SERIAL_SOFTWARE or SERIAL_HARDWARE
#define SERIAL_SOFTWARE_RX 16 // only needed if SERIAL is SERIAL_SOFTWARE
#define SERIAL_SOFTWARE_TX 17 // only needed if SERIAL is SERIAL_SOFTWARE

// Modbus address of the unit (possible to be changed via config)
#define MODBUS_SLAVE_ADDRESS 2 // Default is 30

// Modbus Serial Configuration
#ifndef MODBUS_BAUD
#define MODBUS_BAUD 19200
#endif
#ifndef MODBUS_CONFIG
#define MODBUS_CONFIG SERIAL_8E1
#endif

#if CONFIGURED == 0
#error "Default configuration used - won't upload to avoid loosing connection."
#endif
