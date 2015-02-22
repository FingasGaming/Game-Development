
function new()
	local O = package("sprite").new()
	O.colums = 0
	O.rows = 0
	O.curr = 0
	O.delay = 0
	O.rate = 0
	O.start = 0
	O.seek = 0
	O.superInit = O.onInit
	O.superDraw = O.onDraw
	O.superDestroy = O.onDestroy
	O.name = "flipbook"
	function O:onInit(render, filename)
		self:superInit(render, filename)
	end
	function O:play()
		if (self.delay + self.rate) <= SDL_GetTicks() then 
			if self.curr >= self.colums - 1 then
				self.curr = self.start
			else
				self.curr = self.curr + 1
			end
			self.frameX = self.curr * (self.imageW / self.colums)
			self.frameY = self.seek * (self.imageH / self.rows)
			self.frameW = self.imageW / self.colums
			self.frameH = self.imageH / self.rows

			self.delay = SDL_GetTicks()	
		end

	end
	function O:onDraw(render)
		--self:superDraw(render)
		renderCopyCrop(render, self.image, self.frameX, self.frameY, self.frameW, self.frameH, self.x, self.y, self.w, self.h)
	end
	function O:onDestroy()
		self:superDestroy()
	end
	function O:setColoums( c )
		self.colums = c
	end
	function O:setRows( r )
		self.rows = r
	end
	function O:setDelay( d )
		self.delay = d
	end
	function O:setPlayRate( r )
		self.rate = r
	end
	function O:setStartFrame( s )
		self.start = s
	end
	function O:setup( col, row, rate )
		self:setColoums(col)
		self:setRows(row)
		self:setPlayRate(rate)
	end
	return O
end

return { new = new}