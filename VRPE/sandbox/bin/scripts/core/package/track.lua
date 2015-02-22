function new()
	local O = baseClass("object").new()
	O.name = "anim Track"
	O.duration = 0
	O.frames = {}
	function O:addKeyframe( key )
		for _,e in pairs(self.frames) do
			if e == key then -- check if entity was already added
				return
			end
		end
	    self.frames[#self.frames + 1] = key
	    self:calDur()
	end
	function O:play(start, endt, dur, time )
		local seek = nEase(start, endt, dur, time)
		for k,v in pairs(self.frames) do
			if seek <= start + self.frames[v]:getDuration() then
				--to do: show keyframe here
				--self.frames[v]:show()
			end
		end
	end

	function O:calDur( )
		self.duration = 0
		for k,v in pairs(self.frames) do
			self.duration = self.duration + self.frames[v]:getDuration()
		end
	end
	return O
end

return { new = new}