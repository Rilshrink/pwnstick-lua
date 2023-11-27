#pragma once

#include <WiFi.h>
#include "DNSServer.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"

#include "filemanager.h"

#define AP_SSID "PwnStick"
#define AP_PSK  "pwnedpwned"
#define AP_CHANNEL 6

#define WEBUI_USER "root"
#define WEBUI_PSK  "toor"

#define DNS_PORT 53

namespace HTTPServer {
  void start();
  void update();
};
