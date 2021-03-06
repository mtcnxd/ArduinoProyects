[ZoneTransfer]
ZoneId=3
ReferrerUrl=about:blank
HostUrl=https://mail-attachment.googleusercontent.com/attachment/u/0/?ui=2&ik=2ba6f84cd1&attid=0.1&permmsgid=msg-f:1704326347039772545&th=17a6fbc860a50f81&view=att&disp=safe&saddbat=ANGjdJ-IbUzmXEjb8Gvad6IpkVU_N79Yr2hw_IqCfAD5bfjDlIA02T455k5_7d9MclZC1TMVyFFOhFz_oxEV0l0uhtUY62A6wYeS_O1fvt_fr95rS2BuvYVXPtg69fhHE7F2d4H9X-GLi0GLYn3fGNHZh54swNXjBM1rgejoxUo3OKu_reHjsM1mLgYrdS1EcvhnRqB4uZT9uT3blaYfHLg5Rp-l92tj5pJ0xIOlnzzGZKlwuNxU1pBUPGl6bpTTaE1LYy5JxHnp0t6JmY9wANSGG1AgAbp17eEr3dYFtX4FbsOii8tqE4CiQ7geNxxS0PPna92m9DHc3HNkiFkzjZ4E_dq_88BOXgrK2j2rge_FGKBsjGgOBdYvgocjOFm2-KBjxA-woea8UMY702Z8FxxRoSSdfunjnlcaDeUem3PMy33vNzWejiG2gUdVXHzimpeihfUoh0VgMnoxkfZ_Gxnlt81iTXJ-BTuQE70kduQOWr2evNUM8k_PFemKfTfln5e-3NCYy4kCmFyNj0nc_BzybFgLbFBvtgDf2xoF1f9-FNEsNjlhk2D7fxlRcgp4HnmBu52hQyIZm27y8ka0weQG70qg4WH7awnpmMmDUlljEJkl7j0dK1ykSJ01wQQJ1PHIoTxVzTZo7zpTttwlKUt_wx99AJokBAcgGDQRS30kV1UE0s_oq7Pcr_DxNdM
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      /************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME "your_username"
#define IO_KEY "your_key"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056
//   - Adafruit PyPortal -> https://www.adafruit.com/product/4116
//   - Adafruit Metro M4 Express AirLift Lite ->
//   https://www.adafruit.com/product/4000
//   - Adafruit AirLift Breakout -> https://www.adafruit.com/product/4201
//   - Adafruit AirLift Shield -> https://www.adafruit.com/product/4285
//   - Adafruit AirLift FeatherWing -> https://www.adafruit.com/product/4264

#define WIFI_SSID "your_ssid"
#define WIFI_PASS "your_pass"

// uncomment the following line if you are using airlift
// #define USE_AIRLIFT

// uncomment the following line if you are using winc1500
// #define USE_WINC1500

// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
/******************************* FONA **************************************/

// the AdafruitIO_FONA client will work with the following boards:
//   - Feather 32u4 FONA -> https://www.adafruit.com/product/3027

// uncomment the following two lines for 32u4 FONA,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_FONA.h"
// AdafruitIO_FONA io(IO_USERNAME, IO_KEY);

/**************************** ETHERNET ************************************/

// the AdafruitIO_Ethernet client will work with the following boards:
//   - Ethernet FeatherWing -> https://www.adafruit.com/products/3201

// uncomment the following two lines for ethernet,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_Ethernet.h"
// AdafruitIO_Ethernet io(IO_USERNAME, IO_KEY);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        // Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 5
#define LED_PIN 5

// set up the 'digital' fee