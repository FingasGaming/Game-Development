package("entity")

function new()
	local BackGround = baseClass("object").new()
	BackGround.x = 0
	BackGround.y = 0
	BackGround.w = 0
	BackGround.h = 0
	BackGround.back = nil
	BackGround.superInit = BackGround.onInit
	function BackGround:onInit(render, a, b, c, d)
		self:superInit()
		BackGround.back = package("sprite").new()
		BackGround.back:onInit(render, "bin/resources/bg_0.gif")
		BackGround.back:setDemensions(a, b, c, d)
		--BackGround.mid = nil
		--BackGround.fur = nil
		BackGround.x = a
		BackGround.y = b
		BackGround.w = c
		BackGround.h = d
		return BackGround
	end
	function BackGround:onEvent(event)
	end
	function BackGround:onUpdate(delta)
	end
	function BackGround:onDraw(render)
		BackGround.back:onDraw(render)
		--renderCopyCrop(render, BackGround.back, BackGround.x, BackGround.y, BackGround.w, BackGround.h+100, BackGround.x, BackGround.y, BackGround.w, BackGround.h)
	end
	function BackGround:drawBack(render)
	end
	function BackGround:drawMid(render)
	end	
	function BackGround:drawfur(render)
	end
	function BackGround:onDestroy()
	BackGround.back:onDestroy()
	end
	return BackGround
end

return { new = new}