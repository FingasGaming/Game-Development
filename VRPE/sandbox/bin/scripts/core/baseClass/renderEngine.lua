function new(window)
	local O = baseClass("object").new()
	O.win = window
	O.mainCamera = nil
	O.activeLight = nil
	O.defaultShader = nil

	function O:onRender(obj, dt)
		self.win:begin()
		obj:onDraw(self.win.render)

		regulateFPS(self.win.refreshRate, dt)
		self.win:flip()
	end
	function O:setCamera(cam)
		self.mainCamera = cam
	end
	function O:getActiveLight()
		return self.activeLight
	end
	function O:onDraw(render)
	end
	function O:onDestroy()
	end
	return O
end

return { new = new}