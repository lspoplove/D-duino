wifi.setmode(wifi.STATION) 
wifi.sta.config("Your WiFi name","Your WiFi password")
wifi.sta.connect() 
function init_OLED(sda,scl,sla) --Set up the u8glib lib
 i2c.setup(0, sda, scl, i2c.SLOW)
 disp = u8g.ssd1306_128x64_i2c(sla)
 disp:setFont(u8g.font_6x10)
 disp:setFontRefHeightExtendedText()
 disp:setDefaultForegroundColor()
 disp:setFontPosTop()
end
init_OLED(1,2,0x3c)
print("Setting up WIFI...")

tmr.alarm(1, 1000, 1, function() 
if wifi.sta.getip()== nil then 
print("IP unavaiable, Waiting...") 
else 
tmr.stop(1)
print("Config done, IP is "..wifi.sta.getip())
dofile("wifiled.lua")
end 
end)
