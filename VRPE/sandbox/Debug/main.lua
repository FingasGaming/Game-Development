function onInit()
	print("hello from lua")
end
function onStart()
	-- body
	--print("onStart start")	
	--print("onStart end")
end
function onEvent()

end
-- runtime function call every frame in main loop
function onUpdate()
	--updateEngine()
	--local timing = getEngineTime()
	--local nim = timing:ticks()
	
	--update scene here
	
end
-- runtime function call every frame in main loop
function onRender()
	--local rwin = getMainWindow()
	
	--only 2d compatible at the moment, To Do: 3d rendering	
	--rwin:clear()
	--glClearColor(0.50,0.50,0.50,1.0)

	--render scene here
	--print (gameClass)
	

	--Differed Rendering Phase
	--(PBS)Physical Based Shading - Geometry Phase
	--(IBL)Image Based Lighting - Light Phase
	--render differed screen to window
	
	--render UI elements here
	

	--render debug view
	

	--refresh the screen using engine function
	
end
-- function call once when window close
function onDestroy()

end