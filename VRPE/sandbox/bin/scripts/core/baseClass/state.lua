
function new(fsm, sname)
	local object = {}
	object.fsm = fsm
	object.name = sname
	object.timer = 0 -- int timer value
	object.startTime = 0 -- int startTime value
	function object:onEnter(self)
	end
	function object:onExecute(self)
	end
	function object:onExit(self)
	end
	function object:getInfo()
		return object.name
	end
	function object:setInfo(n)
		object.name = n
	end
	return object
end

return { new = new}