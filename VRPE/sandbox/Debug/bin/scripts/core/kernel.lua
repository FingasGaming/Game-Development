
package("fsm")
package("window")
package("SDLEvent")
local eKey = keyCode()
Kernel = {}
Engine = {}
function Kernel:Create()
	local fsm = kpFSM:Create(Kernel)
	Kernel.fsm = fsm 
	Kernel.engine = Engine:Create()
	function Kernel:onInit()
	Kernel.engine:onInit()
	end
	function Kernel:onExecute(run)
		while run == true and QSDL(Kernel.engine.win.event) == false do
		--handle events here
		self.engine:onEvent()
		--update here
		self.engine:onUpdate(1)		
		--render here
		self.engine:onDraw()
		end
	end
	function Kernel:onDestroy()
		self.engine:onDestroy()
	end
	
	return Kernel
end

function Engine:Create()
	local fsm = kpFSM:Create(Engine)
	local debugIMG = nil
	Engine.fsm = fsm
	--Engine.fsm =  baseClass("statemachine").new()
	Engine.win = nil
	Engine.renEng = nil
	Engine.physics = nil
	Engine.game = nil
	Engine.timer = nil
	showGame = true
	showPhys = false
	--initialize engine
	function Engine:onInit()
	Engine.timer = kpTimer:new()
	Engine.win = loadWindowSettings()
	Engine.win:onInit()
	Engine.renEng = baseClass("renderEngine").new(Engine.win)
	--Engine.physics = loadPhysicsSettings()
	Engine.game = loadGame(Engine)
	Engine.game:onInit()
	-- Engine.physics:addBox(800/2, 600-50, 800, 170, 0)
	
	-- Engine.physics:addBox(-30, 0, 30, 600*2, 0)
	-- Engine.physics:addBox((800 + 30), 0, 30, 600*2, 0)
	local state = baseClass("state").new(self.fsm, "default")
	self.fsm:addState("default", state)
	self.fsm:setState("default")
	return Engine
	end
	--handle events
	function Engine:onEvent()
	pollEvent(self.win.event)
	self.game:onEvent(self.win.event)
	
		if checkKeyDown(self.win.event, eKey.SDLK_e) == true then
			if showGame == true then
				showGame = false
			elseif showGame == false then
				showGame = true
			end
		end
		if checkKeyDown(self.win.event, eKey.SDLK_r) == true then
			if showPhys == true then
				showPhys = false
			elseif showPhys == false then
				showPhys = true
			end
		end
		self.fsm:onExecute()
	end
	--update engine
	function Engine:onUpdate(delta)
		if not self.timer:started() then
			self.timer:start()
		end		
		local prv = self.timer:ticks()
		local dt = (self.timer:ticks() - prv) / 1000
		--if self.physics then 
		--self.physics:step(1/Engine.win.refreshRate, self.physics.stepVal, self.physics.stepPos)
		--end

		self.game:onUpdate(dt)
	end
	--engine draw
	function Engine:onDraw()
		if showGame then
			self.renEng:onRender(self.game, Engine.timer:ticks())	
		end
	-- if showPhys and self.physics then

	-- 	Engine.win.win:clearRect()
	-- 	Engine.physics:debugPhysics(Engine.win.win, Engine.win.render)
	-- 	Engine.win.win:updateWindow()
	-- end
	-- --renderCrop(Engine.win.render, 0, 0, Engine.width, Engine.height)
	-- regulateFPS(Engine.win.refreshRate, Engine.timer:ticks())
	-- Engine.win:flip()
	end
	--kill engine
	function Engine:onDestroy()
		if self.game then
			self.game:onDestroy()
		end
	end
return Engine
end