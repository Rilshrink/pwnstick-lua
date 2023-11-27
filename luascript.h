#pragma once

#include "LuaWrapper.h"

#include "filemanager.h"

#define SHOULD_AUTO_RUN true
#define AUTO_RUN_FILE "/autorun.lua"

namespace LuaScript {
    void start();
    bool isRunning();
    void runCode(String code);
    void stopCode();
};
