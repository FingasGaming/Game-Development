function winFlags()
local windowflags = {}

windowflags.SDL_WINDOW_FULLSCREEN = 0x00000001         -- fullscreen window */
windowflags.SDL_WINDOW_OPENGL = 0x00000002             -- window usable with OpenGL context */
windowflags.SDL_WINDOW_SHOWN = 0x00000004              -- window is visible */
windowflags.SDL_WINDOW_HIDDEN = 0x00000008             -- window is not visible */
windowflags.SDL_WINDOW_BORDERLESS = 0x00000010         -- no window decoration */
windowflags.SDL_WINDOW_RESIZABLE = 0x00000020          -- window can be resized */
windowflags.SDL_WINDOW_MINIMIZED = 0x00000040          -- window is minimized */
windowflags.SDL_WINDOW_MAXIMIZED = 0x00000080          -- window is maximized */
windowflags.SDL_WINDOW_INPUT_GRABBED = 0x00000100      -- window has grabbed input focus */
windowflags.SDL_WINDOW_INPUT_FOCUS = 0x00000200        -- window has input focus */
windowflags.SDL_WINDOW_MOUSE_FOCUS = 0x00000400        -- window has mouse focus */


return windowflags
end

function contextFlags()
local contextflags = {}

contextflags.SDL_GL_CONTEXT_DEBUG_FLAG              = 0x0001
contextflags.SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG = 0x0002
contextflags.SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG      = 0x0004
contextflags.SDL_GL_CONTEXT_RESET_ISOLATION_FLAG    = 0x0008

return contextflags
end

function glProfile()
local profile = {}

profile.SDL_GL_CONTEXT_PROFILE_CORE           = 0x0001
profile.SDL_GL_CONTEXT_PROFILE_COMPATIBILITY  = 0x0002
profile.SDL_GL_CONTEXT_PROFILE_ES             = 0x0004 -- GLX_CONTEXT_ES2_PROFILE_BIT_EXT */

return profile
end

