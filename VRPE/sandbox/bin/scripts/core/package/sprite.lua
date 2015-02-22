
function new()
	local M = baseClass("object").new()
	M.image = nil
	M.x = 0
	M.y = 0
	M.w = 0
	M.h = 0
	M.imageW = 0
	M.imageH = 0
	M.frameX = 0
	M.frameY = 0
	M.frameW = 0
	M.frameH = 0
	M.name = "sprite"
	function M:onInit(render, filename)
		--self:superInit(self)
		self.x = 0
		self.y = 0
		self.imageW = 0
		self.imageH = 0
		self.frameX = 0
		self.frameY = 0
		self.frameW = 0
		self.frameH = 0
		self.originX = 0
		self.originY = 0
		self.image = loadTexture(render, filename)
		vec = queryTexture(self.image)
		self.imageW = vec:x()
		self.imageH = vec:y()
	end
	function M:setX(x)
		self.x = x - self.originX
	end
	function M:setY(y)
		self.y = y - self.originY
	end
	function M:getX()
		return self.x - self.originX
	end
	function M:getY()
		return self.y - self.originY
	end
	function M:setXY(x, y)
		self:setX(x)
		self:setY(y)
	end
	function M:setXY(vec)
		self:setX(vec:x())
		self:setY(vec:y())
	end
	function M:setFrameXY(x, y)
		self.frameX = x - self.originX
		self.frameY = y - self.originY
	end
	function M:setFrame(x, y, w, h)
		self.frameX = x - self.originX
		self.frameY = y - self.originY
		self.w = w + self.originX
		self.frameW = w + self.originX
		self.h = h + self.originY
		self.frameH = h + self.originY

	end
	function M:setDemensions(x, y, w, h)
		self.x = x
		self.y = y
		self.w = w
		self.h = h
		self.imageW = w
		self.frameW = w
		self.imageH = h
		self.frameH = h
	end
	function M:onDraw(render)
		renderCopyCrop(render, self.image, self.frameX, self.frameY, self.frameW, self.frameH, self.x, self.y, self.w, self.h)
	end
	function M:onDestroy()
		if self.image == nil then
		else
			self.image:kill()
		end
	end
	function M:setOrigin(x, y)
		self.originX = x
		self.originY = y
	end
	return M
end

return { new = new}