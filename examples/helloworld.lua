delay(1000) -- Add delay for computer to recognise usb.

local t = millis()

keyboard.write("Hello World")
keyboard.writeln("Next Line Please")

local rand = random(0, 100)

keyboard.writeln("Got random number: " .. rand)

delay(500)

keyboard.tap(KEY_A)

keyboard.press(KEY_LGUI)
keyboard.tap(KEY_R)
keyboard.release(KEY_LGUI)

local final_time = millis() - t
keyboard.writeln("Script took " .. final_time .. " millis to run!")