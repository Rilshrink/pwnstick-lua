#include "luascript.h"

#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDMouse.h"

USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;

const char* KEYS[61] = {
  "KEY_A",
  "KEY_B",
  "KEY_C",
  "KEY_D",
  "KEY_E",
  "KEY_F",
  "KEY_G",
  "KEY_H",
  "KEY_I",
  "KEY_J",
  "KEY_K",
  "KEY_L",
  "KEY_M",
  "KEY_N",
  "KEY_O",
  "KEY_P",
  "KEY_Q",
  "KEY_R",
  "KEY_S",
  "KEY_T",
  "KEY_U",
  "KEY_V",
  "KEY_W",
  "KEY_X",
  "KEY_Y",
  "KEY_Z",
  "KEY_0",
  "KEY_1",
  "KEY_2",
  "KEY_3",
  "KEY_4",
  "KEY_5",
  "KEY_6",
  "KEY_7",
  "KEY_8",
  "KEY_9",
  "KEY_SPACE",
  "KEY_BACKSPACE",
  "KEY_TAB",
  "KEY_RETURN",
  "KEY_LCTRL",
  "KEY_LALT",
  "KEY_LSHIFT",
  "KEY_LGUI",
  "KEY_DEL",
  "KEY_F1",
  "KEY_F2",
  "KEY_F3",
  "KEY_F4",
  "KEY_F5",
  "KEY_F6",
  "KEY_F7",
  "KEY_F8",
  "KEY_F9",
  "KEY_F10",
  "KEY_F11",
  "KEY_F12",
  "KEY_RIGHT",
  "KEY_LEFT",
  "KEY_DOWN",
  "KEY_UP"
};

const uint8_t KEY_CODES[61]{
  0x04,          // a
  0x05,          // b
  0x06,          // c
  0x07,          // d
  0x08,          // e
  0x09,          // f
  0x0a,          // g
  0x0b,          // h
  0x0c,          // i
  0x0d,          // j
  0x0e,          // k
  0x0f,          // l
  0x10,          // m
  0x11,          // n
  0x12,          // o
  0x13,          // p
  0x14,          // q
  0x15,          // r
  0x16,          // s
  0x17,          // t
  0x18,          // u
  0x19,          // v
  0x1a,          // w
  0x1b,          // x
  0x1c,          // y
  0x1d,          // z
  0x27,          // 0
  0x1e,          // 1
  0x1f,          // 2
  0x20,          // 3
  0x21,          // 4
  0x22,          // 5
  0x23,          // 6
  0x24,          // 7
  0x25,          // 8
  0x26,          // 9
  0x2c,          // SPACE
  0x2a,          // BACKSPACE
  0x2b,          // TAB
  0x28,          // ENTER
  0xe0,          // LCTRL (just here to keep lists the same size)
  0xe2,          // LALT (just here to keep lists the same size)
  0xe1,          // LSHIFT (just here to keep lists the same size)
  0xe3,          // LGUI
  0x4c,          // DEL
  0x3a,          // F1
  0x3b,          // F2
  0x3c,          // F3
  0x3d,          // F4
  0x3e,          // F5
  0x3f,          // F6
  0x40,          // F7
  0x41,          // F8
  0x42,          // F9
  0x43,          // F10
  0x44,          // F11
  0x45,          // F12
  0x4e,          // RIGHT
  0x4f,          // LEFT
  0x50,          // DOWN
  0x51,          // UP
};

static int LUA_keyboard_write(lua_State* L) {
    
  Keyboard.print(luaL_checkstring(L, 1));

  return 0;
}

static int LUA_keyboard_writeln(lua_State* L) {
    
  Keyboard.print(luaL_checkstring(L, 1));
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  return 0;
}

static int LUA_delay(lua_State* L) {
  delay(luaL_checkinteger(L, 1));
  return 0;
}

static int LUA_random_seed(lua_State* L) {
  randomSeed(random(luaL_checkinteger(L, 1)));
  return 0;
}

static int LUA_random(lua_State* L) {
  int r = random(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2));
  lua_pushnumber(L, (lua_Number)r);
  return 1;
}

static int LUA_millis(lua_State* L) {
  lua_pushnumber(L, (lua_Number)millis());
  return 1;
}

static int LUA_print(lua_State* L) {
  String str = luaL_checkstring(L, 1);
  return 0;
}

static int LUA_keyboard_tap(lua_State* L) {

  int key = luaL_checkinteger(L, 1);
  Keyboard.pressRaw(key);
  Keyboard.releaseRaw(key);
  
  return 0;
}

static int LUA_keyboard_press(lua_State* L) {
  Keyboard.pressRaw(luaL_checkinteger(L, 1));
  return 0;
}

static int LUA_keyboard_release(lua_State* L) {
  Keyboard.releaseRaw(luaL_checkinteger(L, 1));
  return 0;  
}

static int LUA_mouse_click(lua_State* L) {
  Mouse.click(luaL_checkinteger(L, 1));
  return 0;  
}

static int LUA_mouse_move(lua_State* L) {
  Mouse.move(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
  return 0;  
}

static int LUA_mouse_press(lua_State* L) {
  Mouse.press(luaL_checkinteger(L, 1));
  return 0;  
}

static int LUA_mouse_release(lua_State* L) {
  Mouse.release(luaL_checkinteger(L, 1));
  return 0;
}

void LUA_init_keyboard_globals(lua_State* L) {
  for(int i = 0; i < 61; i++) {
    lua_pushnumber(L, (lua_Number)KEY_CODES[i]);
    lua_setglobal(L, KEYS[i]); 
  }

  lua_pushnumber(L, (lua_Number)MOUSE_LEFT);
  lua_setglobal(L, "MOUSE_LEFT");
  lua_pushnumber(L, (lua_Number)MOUSE_RIGHT);
  lua_setglobal(L, "MOUSE_RIGHT");
  lua_pushnumber(L, (lua_Number)MOUSE_MIDDLE);
  lua_setglobal(L, "MOUSE_MIDDLE");
}

void LUA_init_mouse(lua_State* L) {
  lua_newtable(L);

  lua_pushcfunction(L, LUA_mouse_click);
  lua_setfield(L, -2, "click");
  lua_pushcfunction(L, LUA_mouse_move);
  lua_setfield(L, -2, "move");
  lua_pushcfunction(L, LUA_mouse_press);
  lua_setfield(L, -2, "press");
  lua_pushcfunction(L, LUA_mouse_release);
  lua_setfield(L, -2, "release");

  lua_setglobal(L, "mouse");
}

void LUA_init_keyboard(lua_State* L) {
  // Functions
  lua_newtable(L);

  lua_pushcfunction(L, LUA_keyboard_write);
  lua_setfield(L, -2, "write");

  lua_pushcfunction(L, LUA_keyboard_writeln);
  lua_setfield(L, -2, "writeln");

  lua_pushcfunction(L, LUA_keyboard_tap);
  lua_setfield(L, -2, "tap");

  lua_pushcfunction(L, LUA_keyboard_press);
  lua_setfield(L, -2, "press");

  lua_pushcfunction(L, LUA_keyboard_release);
  lua_setfield(L, -2, "release");

  lua_setglobal(L, "keyboard");
}

void LUA_init_globals(lua_State* L) {
  luaopen_base(L);
  luaopen_table(L);
  luaopen_string(L);
  luaopen_math(L);
  lua_register(L, "print", LUA_print);
  lua_register(L, "millis", LUA_millis);
  lua_register(L, "delay", LUA_delay);
  lua_register(L, "random", LUA_random);
  lua_register(L, "randomSeed", LUA_random_seed);
}

namespace LuaScript {
  String currentCode;
  TaskHandle_t currentThread = NULL;
  
  void start() {
    Mouse.begin();
    Keyboard.begin();
    USB.begin();

#ifdef SHOULD_AUTO_RUN
    if(FileManager::fileExists(AUTO_RUN_FILE)) { 
      String autoRunCode = FileManager::readFile(AUTO_RUN_FILE);  
      runCode(autoRunCode);
    }
#endif
  }

  bool isRunning() {
    return currentThread != NULL;  
  }

  void _start_thread(void* params) {
    String code = *((String*)params);

    lua_State* L = luaL_newstate();
  
    LUA_init_globals(L);
    LUA_init_keyboard_globals(L);
    LUA_init_keyboard(L);
    LUA_init_mouse(L);
    
    if(luaL_dostring(L, code.c_str())) {
      //String error = "Lua Error: " + String(lua_tostring(L, -1));
      lua_pop(L, 1);
    }
    
    lua_close(L);

    currentThread = NULL;
    vTaskDelete(NULL);
  }

  void runCode(String code) {
    if(isRunning())
      return;

    currentCode = code;

    xTaskCreate( _start_thread , "lua", 16384, (void*)&currentCode, 2, &currentThread );
  }

  void stopCode() {
    if(currentThread)
      vTaskDelete(currentThread);
    currentThread = NULL;  
  }
  
};
