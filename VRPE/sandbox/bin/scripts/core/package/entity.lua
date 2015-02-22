package("fsm")
Entity = {}

function Entity:Create()
	local fsm = kpFSM:Create(Entity)
	Entity.fsm = fsm 
	function Entity:onInit()
	end
	function Entity:onEvent(event)
	end
	function Entity:onUpdate(delta)
	end
	function Entity:onDraw(render)
	end
	function Entity:onDestroy()
	end
	return Entity
end