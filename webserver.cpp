#include "webserver.h"

#include "luascript.h"
#include "webfiles.h"

IPAddress AP_LOCAL_IP(192,168,1,1);
IPAddress AP_GATEWAY(192,168,1,1);
IPAddress AP_SUBNET(255,255,255,0);

namespace HTTPServer {
  AsyncWebServer webServer(80);
  DNSServer dnsServer;

  void update() {
    dnsServer.processNextRequest();  
  }
  
  void start() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PSK, AP_CHANNEL);
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY, AP_SUBNET);

    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
        return request->requestAuthentication();
      request->send_P(200, "text/html", (char*)index_html.c_str());
    });

    webServer.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
        return request->requestAuthentication();
      request->send_P(200, "application/javascript", (char*)script_js.c_str());
    });

    webServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
        return request->requestAuthentication();
      request->send_P(200, "text/css", (char*)style_css.c_str());
    });

    webServer.on("/files", HTTP_GET, [] (AsyncWebServerRequest *request) {
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
  
      request->send_P(200, "text/txt", FileManager::listDir("/").c_str());
    });
  
    webServer.on("/remove", HTTP_GET, [] (AsyncWebServerRequest *request) {
        
        if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
  
        if(!request->hasParam("file"))
          return;
  
        String filePath = request->getParam("file")->value();

        if(!filePath.startsWith("/"))
          return;
  
        // LOAD_FILE
        FileManager::deleteFile(filePath.c_str());
    });
  
    webServer.on("/load", HTTP_GET, [] (AsyncWebServerRequest *request) {
  
        if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
  
        if(!request->hasParam("file"))
          return;
  
        String filePath = request->getParam("file")->value();

        if(!filePath.startsWith("/"))
          return;
  
        // LOAD_FILE
        request->send_P(200, "text/lua", FileManager::readFile(filePath.c_str()).c_str());
    });

    webServer.on("/status", HTTP_GET, [] (AsyncWebServerRequest *request) {
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
      String ramUsage;
      String sdcardUsage;
      String luacodeUsage;
    });

    webServer.on("/stop", HTTP_POST, [] (AsyncWebServerRequest *request) {
      if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
      LuaScript::stopCode();
    });

    webServer.on("/run", HTTP_POST, [](AsyncWebServerRequest* request) {}, NULL,
    [](AsyncWebServerRequest *request, uint8_t* _data, size_t len, size_t index, size_t total) {
        if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
        String code = String(_data, len);
        LuaScript::runCode(code);
    });

    webServer.on("/save", HTTP_POST, [](AsyncWebServerRequest* request) {}, NULL,
    [](AsyncWebServerRequest *request, uint8_t* _data, size_t len, size_t index, size_t total) {
        if(!request->authenticate(WEBUI_USER, WEBUI_PSK))
          return request->requestAuthentication();
        
        String code = String(_data, len);
        
        String filePath;
        if(!request->hasParam("file"))
          return;
        
        filePath = request->getParam("file")->value();

        if(!filePath.startsWith("/"))
          return;
        
        FileManager::writeFile(filePath.c_str(), code.c_str());
    });

    webServer.onNotFound([] (AsyncWebServerRequest *request) {
      request->redirect("/");
    });

    dnsServer.setTTL(300);
    dnsServer.start(DNS_PORT, "*", AP_LOCAL_IP);

    webServer.begin();
  }
  
};
