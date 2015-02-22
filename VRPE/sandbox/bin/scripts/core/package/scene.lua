
Scene = {}

function Scene:Create()
	local sceneEntities = {}

	function Scene:addToScene(ent)
		for _,e in pairs(sceneEntities) do
			if e == ent then -- check if entity was already added
				return
			end
		end
	    sceneEntities[#sceneEntities + 1] = ent
	end

	function Scene:onEvent(event)
		for _,e in pairs(sceneEntities) do
			e:onEvent(event)
	    end
	end
	function Scene:onUpdate(delta)
		for _,e in pairs(sceneEntities) do
			e:onUpdate(delta)
	    end
	end

	function Scene:onDraw(render)
		for _,e in pairs(sceneEntities) do
			e:onDraw(render)
	    end
	end
	function Scene:onDestroy()
		for _,e in pairs(sceneEntities) do
			e:onDestroy()
	    end
	end
	function Scene:getEntities()
		return sceneEntities
	end
	-- return
	return Scene
end