gpio.mode(3, gpio.OUTPUT) 
gpio.mode(4, gpio.OUTPUT) 
gpio.mode(5, gpio.OUTPUT) 
gpio.mode(6, gpio.OUTPUT)
gpio.mode(7, gpio.OUTPUT)
gpio.mode(8, gpio.OUTPUT)
gpio.mode(9, gpio.OUTPUT)
gpio.mode(10, gpio.OUTPUT)


local IP = wifi.sta.getip();
function Display()
 disp:firstPage()
 repeat
 if wifi.sta.getip()== nil then
 disp:drawStr(0,0,"Setting up WIFI...")
 else
 disp:drawStr(0,0,IP)
 disp:drawStr(0,12,"WiFi Connected") 
 end
 until disp:nextPage() == false 
end

Display()

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
 buf = buf.."<h2>Conrol your Led</h2>";
 buf = buf.."<p>GPIO3<a href=\"?pin=ON1\"><button>ON</button></a> <a href=\"?pin=OFF1\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO4<a href=\"?pin=ON2\"><button>ON</button></a> <a href=\"?pin=OFF2\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO5<a href=\"?pin=ON3\"><button>ON</button></a> <a href=\"?pin=OFF3\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO6<a href=\"?pin=ON4\"><button>ON</button></a> <a href=\"?pin=OFF4\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO7<a href=\"?pin=ON5\"><button>ON</button></a> <a href=\"?pin=OFF5\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO8<a href=\"?pin=ON6\"><button>ON</button></a> <a href=\"?pin=OFF6\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO9<a href=\"?pin=ON7\"><button>ON</button></a> <a href=\"?pin=OFF7\"><button>OFF</button></a></p>"; 
 buf = buf.."<p>GPIO10<a href=\"?pin=ON8\"><button>ON</button></a> <a href=\"?pin=OFF8\"><button>OFF</button></a></p>"; 
 buf = buf.."<hr />";
 buf = buf.."<h2 align=\"center\">Make something amazing with you</h2>";
 local _on,_off = "","" 
 if(_GET.pin == "ON1")then 
 gpio.write(3, gpio.HIGH); 
 elseif(_GET.pin == "OFF1")then 
 gpio.write(3, gpio.LOW); 
 elseif(_GET.pin == "ON2")then 
 gpio.write(4, gpio.HIGH); 
 elseif(_GET.pin == "OFF2")then 
 gpio.write(4, gpio.LOW); 
 elseif(_GET.pin == "ON3")then 
 gpio.write(5, gpio.HIGH); 
 elseif(_GET.pin == "OFF3")then 
 gpio.write(5, gpio.LOW);
 elseif(_GET.pin == "ON4")then 
 gpio.write(6, gpio.HIGH); 
 elseif(_GET.pin == "OFF4")then 
 gpio.write(6, gpio.LOW);
 elseif(_GET.pin == "ON5")then 
 gpio.write(7, gpio.HIGH); 
 elseif(_GET.pin == "OFF5")then 
 gpio.write(7, gpio.LOW);
 elseif(_GET.pin == "ON6")then 
 gpio.write(8, gpio.HIGH); 
 elseif(_GET.pin == "OFF6")then 
 gpio.write(8, gpio.LOW); 
 elseif(_GET.pin == "ON7")then 
 gpio.write(9, gpio.HIGH); 
 elseif(_GET.pin == "OFF7")then 
 gpio.write(9, gpio.LOW); 
 elseif(_GET.pin == "ON8")then 
 gpio.write(10, gpio.HIGH); 
 elseif(_GET.pin == "OFF8")then 
 gpio.write(10, gpio.LOW); 
 end 
 client:send(buf); 
 client:close(); 
 collectgarbage(); 
 conn:close()
 end) 
end)
