wifi.setmode(wifi.STATION) 
wifi.sta.config("Your wifi name","Your wifi password")
wifi.sta.connect() 
print("Setting up WIFI...")
tmr.alarm(1, 1000, 1, function() 
if wifi.sta.getip()== nil then 
print("IP unavaiable, Waiting...") 
else 
tmr.stop(1)
print("Config done, IP is "..wifi.sta.getip())
dofile("wifidht.lua")
end 
end)
