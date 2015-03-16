function new(engine)
	local M = require(".bin/scripts/core/baseClass/object").new()
	M.engine = engine
	M.name = "gameClass"
	function M:onInit()
	print(self.name .. " init")
	end
	function M:onEvent(event)
	print(self.name .. " event")
	end
	function M:onUpdate(delta)
	print(self.name .. " update: " .. delta)
	end
	function M:onDraw(render)
	print(self.name .. " render")
	end
	function M:onDestroy()
	end

	return M
end

return { new = new}