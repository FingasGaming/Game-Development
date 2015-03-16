
function new(entity)
	local object = {}
	object.entity = entity -- the object/entity to manipulate
	object.states = {} -- states stored by the state machine
	object.transitions = {} -- transtions stored by the state machine
	object.currState = nil -- points to the current state
	object.prevState = nil -- points to the previous state
	object.trans = nil -- points to the current transition
	--Function: addStates to the FSM
	function object:addState(stateName, state)
		if object.states[stateName] == nil then
			object.states[stateName] = state
			print("State: " .. stateName .. " was added..")
		else			
			print("State: " .. transName .. " was not added..")
		end
	end
	--Function: addTransition to the FSM
	function object:addTransition( transName, trans)
		if object.transitions[transName] == nil then
			object.transitions[transName] = trans
			print("Transtion: " .. transName .. " was added..")
		else			
			print("Transtion: " .. transName .. " was not added..")
		end
	end
	--Function: Transition to another state
	function object:toTransition( toTrans)
		if object.transitions[toTrans] then 
			object.trans = object.transitions[toTrans]
		end
	end
	function exeOnTransition(toTrans)	
		this.toTransition(toTrans)
		this.onExecute()
	end
	--Function: setState of the FSM
	function object:setState( stateName)
		object.prevState = currState
		object.currState = states[stateName]
	end
	--Function: setDefaultState of the FSM
	function object:setDefaultState( stateName)
		object.currState = states[stateName]
		object.prevState = currState	
	end
	--Function: onExecute the FSM
	function object:onExecute()
		if (object.trans) then
			object.currState:onExit()
			object.trans:onEnter()
			object.trans:onExecute()
			tmp = object.trans:getInfo()
			object:setState(tmp)
			object.trans:onExit()
			object.currState:onEnter()
			object.trans = nil
		end
		if object.prevState == nil then
			object.currState:onExecute()
		else
			object.currState:onExecute()
		end
	end
	return object
end

return { new = new}