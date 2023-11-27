#include "filemanager.h"

namespace FileManager {
  
  bool start() {
    SD_MMC.setPins(SD_MMC_CLK_PIN, SD_MMC_CMD_PIN, SD_MMC_D0_PIN, SD_MMC_D1_PIN, SD_MMC_D2_PIN, SD_MMC_D3_PIN);
    
    if (!SD_MMC.begin()) {
      return true;
    }  

    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
      return true;
    }

    return false;
  }

  bool fileExists(const char* path) {
    File file = SD_MMC.open(path);
    if(!file)
      return false;
    return true;
  }
  
  String readFile(const char* path){
    File file = SD_MMC.open(path);
    if(!file)
        return "";
    String line = "";
    while(file.available())
        line = line + (char)file.read();
    return line;
  }
  
  bool writeFile(const char* path, const char* data){
      File file = SD_MMC.open(path, FILE_WRITE);
      if(!file){
          return false;
      }
      file.print(data);
      return true;
  }
  
  bool deleteFile(const char * path){
      if(!fileExists(path))
        return false;
      SD_MMC.remove(path);
      return true;
  }

  String listDir(const char * dirname){
    String all_files = "";
    File root = SD_MMC.open(dirname);
    if(!root){
        return "";
    }
    if(!root.isDirectory()){
        return "";
    }
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory())
          continue;
        all_files += "/" + String(file.name()) + ",";
        file = root.openNextFile();
    }
    return all_files;
  }

};
