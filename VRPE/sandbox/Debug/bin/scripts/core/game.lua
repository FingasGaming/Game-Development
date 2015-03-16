package("scene")
local Player = require("./bin/scripts/core/player")
local BG = require("./bin/scripts/core/background")
Game = {}
function cam2d()
local M = {}
M.x = 0
M.y = 0
M.w = 0
M.h = 0
return M
end

function Game:Create(engine)
	local O = require("./bin/scripts/core/baseClass/object").new()
	local player = Player.new()
	local player2 = BG.new()
	O.scene = nil
	O.engine = engine
	function O:onInit(render)
	O.scene = Scene:Create()
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
