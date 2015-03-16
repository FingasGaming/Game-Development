function new(state)
	local object = {}
	object.toState = state --string stateName
	function object:onEnter(self)
	end
	function object:onExecute(self)
		print("Transitioning...")
	end
	function object:onExit(self)
	end
	function object:getInfo()
		return object.toState
	end
	return object
end

return { new = new}