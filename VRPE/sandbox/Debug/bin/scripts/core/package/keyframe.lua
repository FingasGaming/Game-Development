function new()
	local O = baseClass("object").new()
	O.name = "anim Keyframe"
	O.duration = 0
	function O:getDuration( )
		return self.duration
	end
	function O:setDuration(d)
		self.duration = d
	end
	return O
end

return { new = new}