require("./bin/scripts/core/scene")
function new(engine)
	local M = require("bin/scripts/core/baseClass/baseGame").new(engine)
	M.name = "example1"

	M.superInit = M.onInit
	function M:onInit()
		self:superInit()
		if self.engine.physics then 
		self.engine.physics:addBox(800/2, 600-50, 800, 170, 0)
		
		self.engine.physics:addBox(-30, 0, 30, 600*2, 0)
		self.engine.physics:addBox((800 + 30), 0, 30, 600*2, 0)
		end
	end
	M.superEvent = M.onEvent
	function M:onEvent(event)
		self:superEvent(event)
	end
	M.superUpdate = M.onUpdate
	function M:onUpdate(delta)
		self:superUpdate(delta)
		--print(self.name .. " update: " .. delta)
	end
	M.superDraw = M.onDraw
	function M:onDraw(render)
		self:superDraw(redner)
		--print(self.name .. " render")
	end
	function M:onDestroy()
	end

	return M
end

return { new = new}