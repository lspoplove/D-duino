pin = 5 -- The pin you connected the DHTXX
status, temp, humi, temp_dec, humi_dec = dht.read11(pin)
bimb = 1


function init_OLED(sda,scl,sla) --Set up the u8glib lib
 i2c.setup(0, sda, scl, i2c.SLOW)
 disp = u8g.ssd1306_128x64_i2c(sla)
 disp:setFont(u8g.font_6x10)
 disp:setFontRefHeightExtendedText()
 disp:setDefaultForegroundColor()
 disp:setFontPosTop()
end
function display() 
 disp:firstPage()
 repeat
 if wifi.sta.getip()== nil then
 disp:drawStr(0,0,"Wait")
 else
 disp:drawStr(0,0,wifi.sta.getip())
 disp:drawStr(0,12,"WiFi Connected")
 disp:drawStr(0,24,"Temperature")
 disp:drawStr(0,36,"Humidity")
 disp:drawStr(70,24,temp)
 disp:drawStr(70,36,humi)
 end
 until disp:nextPage() == false 
 end
 
 
 init_OLED(1,2,0x3c)
 display()

function sendData()
dht.read11(pin)
srv=net.createServer(net.TCP) 
srv:listen(80,function(conn) 
conn:on("receive", function(client,request)
 local buf = ""; 
 local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP"); 
 if(method == nil)then 
 _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP"); 
 end 
 local _GET = {} 
 if (vars ~= nil)then 
 for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do 
 _GET[k] = v 
 end 
 end 
 buf = buf.."<h1 align=\"center\"> Hello Dongsen Technology </h1>"; 
 buf = buf.."<hr />"; 
 buf = buf.."<h1>Tempurature</h1>"..temp;
 buf = buf.."<h1>Humidity</h1>"..humi.."%";
 client:send(buf);
 client:close(); 
 collectgarbage(); 
 conn:close()
 end) 
end)
end

tmr.alarm(2, 6000, 1, function() sendData() end )
