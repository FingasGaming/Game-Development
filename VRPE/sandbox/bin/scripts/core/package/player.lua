package("SDLEvent")
local eKey = scanCode()

function new()
	local Player = baseClass("object").new()
	Player.x = 10
	Player.y = 50
	Player.w = 90
	Player.h = 220
	Player.img = nil
	Player.body = nil
	Player.superInit = Player.onInit
	Player.name = "Player"
	Player.walkSpeed = 260
	Player.legStrenght = 720
	function Player:onInit(render, phys)
		self:superInit()
		Player.img = package("flipbook").new()
		Player.img:onInit(render, "bin/resources/image.png")
		Player.img:setup(3, 4, 200)
		Player.img:setFrame(0, 0, Player.w, Player.h)
		Player.img:setOrigin(Player.w/2, Player.h/2)
		--Player.body = phys:addBox(Player.w/2, Player.h/2, Player.w, Player.h, 1)
		--Player.body:isFixedRotation(1)
		Player.img.seek = 2
	end
	function Player:onEvent(event)
		if checkKeyState(eKey.Key_RIGHT) == true then
			self.img.seek = 2
			Player.x = Player.x + 1		
			--Player.body:applyImpulse(Player.walkSpeed, 0)
		end
		if checkKeyState(eKey.Key_LEFT) == true then
			self.img.seek = 1		
			Player.x = Player.x - 1	
			--Player.body:applyImpulse(-Player.walkSpeed, 0)	
		end
		if checkKeyState(eKey.Key_UP) == true then
			self.img.seek = 3
			Player.y = Player.y - 1	
			--Player.body:applyImpulse(0, -Player.legStrenght)
		end
		if checkKeyState(eKey.Key_DOWN) == true then
			self.img.seek = 0
			Player.y = Player.y + 1		
			
			--Player.body:applyImpulse(0, 100)
		end--[[]]
	end
	function Player:onUpdate(delta)
		Player.img:play()
		--tmp = Player.body:getWorldCenter()
		--Player.img:setXY(tmp)
	end
	function Player:onDraw(render)
		--renderCopy(render, Player.img, Player.x, Player.y, 50, 50)--[[]]
		Player.img:onDraw(render)
	end
	function Player:onDestroy()
		Player.img:onDestroy()
	end
	return Player
end

return {new = new}