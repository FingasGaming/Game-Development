package("scene")
local Player = package("player")
local BG = package("background")

function new(engine)
	local O = baseClass("object").new()
	local player = Player.new()
	local player2 = BG.new()
	O.scene = nil
	O.engine = engine
	function O:onInit()
		local render = engine.win.render
		O.scene = Scene:Create()
		if self.engine.physics then 
			--self.engine.physics:addBox(800/2, 600-50, 800, 170, 0)
			
			--self.engine.physics:addBox(-30, 0, 30, 600*2, 0)
			--self.engine.physics:addBox((800 + 30), 0, 30, 600*2, 0)
		end
		player.name = "player"
		player:onInit(render, engine.physics)
		player2.name = "player2"
		player2:onInit(render, 0, 0, 800, 500)
		O.scene:addToScene(player2)
		O.scene:addToScene(player)
		return O
	end
	function O:onEvent(event)
		O.scene:onEvent(event)
	end
	function O:onUpdate(delta)
		O.scene:onUpdate(delta)
	end
	function O:onDraw(render)
		O.scene:onDraw(render)
	end
	function O:onDestroy()
		O.scene:onDestroy()
	end
	return O
end


return { new = new}