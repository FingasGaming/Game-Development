--base entity
local fsm = require("./bin/scripts/core/baseClass/statemachine")

function new()
	local object = {}
	object.name = "untitled"
	object.fsm = fsm.new(object)
	object.superInit = nil
	object.superDraw = nil
	object.superDestroy = nil
	object.superEvent = nil
	object.superUpdate = nil
	function object:onInit(context)
	--print(self.name .. " init")
	end
	function object:onEvent(event)
		self.fsm:onExecute()
	end
	function object:onUpdate(delta)
	--print(self.name .. " update: " .. delta)
	end
	function object:onDraw(render)
	--print(self.name .. " render")
	end
	function object:onDestroy()
	end
	return object
end

return { new = new}