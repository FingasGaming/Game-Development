
function package(src)
	return require("./bin/scripts/core/package/" .. src)
end

function baseClass(src)
	return require("./bin/scripts/core/baseClass/" .. src)
end

function writeToFile( path, filename, value)
	io.output(path .. filename)
	io.write(value)
	io.read()
end

function readFile(file, option)
	return io.open(file, option)
end

function printFile(file)
	local f = readFile(file, "r")
	for line in io.lines() do
		print(line)
	end
end
-----------------------------------------------------------------------
--System load functions
-----------------------------------------------------------------------
function loadWindowSettings()
	local win = nil
	local tmp = INIReader:new("game/config/manifest.ini") 
	local title  = tmp:getString("WINDOW", "title", "noTitle")
	local width = tmp:getInteger("WINDOW", "width", 300)
	local height = tmp:getInteger("WINDOW", "height", 200)	
	local rate = tmp:getInteger("WINDOW", "refreshRate", 60)
	tmp:kill()
	win = Window:Create(title, 100, 100, width, height)
	win.refreshRate = rate
	return win
end
function loadPhysicsSettings()
	local phys = nil
	local tmp = INIReader:new("game/config/manifest.ini")
	local enable = tmp:getBool("PHYSICS", "Enable", 0)
	local phys_type = tmp:getString("PHYSICS", "Type", "2D")
	local gravity = tmp:getFloat("PHYSICS", "Gravity", 9.81)	
	local gravityAngle = tmp:getFloat("PHYSICS", "GravityAngle", 0.0)
	local stepVal = tmp:getInteger("PHYSICS", "stepVal", 5)
	local stepPos = tmp:getInteger("PHYSICS", "stepPos", 5)
	tmp:kill()
	if enable == true then
		if phys_type == "Box2D" then
			phys = b2World:new(gravityAngle,gravity)
			phys.stepVal = stepVal
			phys.stepPos = stepPos
		elseif phys_type == "Bullet" then 
			phys.stepVal = stepVal
			phys.stepPos = stepPos
		end
	end
	return phys
end
function loadGame(engine)
	local game = nil
	local tmp = INIReader:new("game/config/manifest.ini") 
	local path = tmp:getString("GAME SETTINGS", "gamePath", "game/assets/scripts/")
	local src = tmp:getString("GAME SETTINGS", "gameSrc", "game")
	tmp:kill()
	game = require("." .. path .. src).new(engine)
	return game
end

------------------------------------------------------------------------------------
-- Animation functions -------------------------------------------------------------
------------------------------------------------------------------------------------
function nEase(start, endt, duration, time)
	return ((endt - start) * (time / duration) + start)
end
function pEaseIn( time, duration, power)
	return (math.pow((time/duration), power))
end
function pEaseOut( time, duration, power)
	return (1 - math.pow(1 - (time/duration), power))
end
function eEase( time, duration, rate)
	k = (time/duration)
	return (k * k * ((rate + 1) * k - rate))
end
function sEase( time, duration)
	return  (math.sin((time/duration) *(math.pi / 2)))
end
function pdot( time, duration)
	return math.cos(time * duration)
end
function fEase( time, duration)
	f = (2 * pdot(time, duration) * (time - duration))
	finish = ((f + (1 - f))*(math.pow(math.max(0, pdot(f, duration)), 5)))
	return finish
end
function plength( time, duration)
	f = math.sqrt((time * time * duration * duration))
	return f
end