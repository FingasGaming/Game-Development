kpFSM = {}
kpState = {}
kpTransition = {}

function kpState:Create(fsm, sname)
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

function kpTransition:Create(state)
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

function kpFSM:Create(entity)
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
		object.prevState = object.currState
		object.currState = object.states[stateName]
	end
	--Function: setDefaultState of the FSM
	function object:setDefaultState( stateName)
		object.currState = object.states[stateName]
		object.prevState = object.currState	
	end
	--Function: onExecute the FSM
	function object:onExecute()
		--print(object.trans)
		if (object.trans) then
			--print("exit currState")
			object.currState:onExit()
			--print("enter trans")
			object.trans:onEnter()
			--print("execute trans")
			object.trans:onExecute()
			tmp = object.trans:getInfo()
			--print("set currState to trans state: " .. tmp)
			object:setState(tmp)
			--print("exit trans")
			object.trans:onExit()
			--print("enter newState")
			object.currState:onEnter()
			--print(object.trans)
			object.trans = nil
			--print(object.trans)
		end
		if object.prevState == nil then
			--print("execute first State")
			--print(object.trans)
			object.currState:onExecute()
		else
			--print("execute currState")
			--print(object.trans)
			object.currState:onExecute()
		end
	end
	return object
end
