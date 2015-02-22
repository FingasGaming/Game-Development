function eventType()
local M = {}

M.SDL_QUIT           = 0x100 -- < User-requested quit */
M.SDL_APP_TERMINATING = 0x101
M.SDL_APP_LOWMEMORY = 0x102
M.SDL_APP_WILLENTERBACKGROUND = 0x103
M.SDL_APP_DIDENTERBACKGROUND = 0x104
M.SDL_APP_WILLENTERFOREGROUND = 0x105
M.SDL_APP_DIDENTERFOREGROUND = 0x106

-- Window Events
M.SDL_WINDOWEVENT    = 0x200
M.SDL_SYSWMEVENT = 0x201
-- KeyBoard events
M.SDL_KEYDOWN        = 0x300         -- Key pressed */
M.SDL_KEYUP = 0x301                  -- Key released */
M.SDL_TEXTEDITING = 0x302            -- Keyboard text editing (composition) */
M.SDL_TEXTINPUT = 0x303              -- Keyboard text input */
-- Mouse events
M.SDL_MOUSEMOTION    = 0x400         -- Mouse moved */
M.SDL_MOUSEBUTTONDOWN = 0x401        -- Mouse button pressed */
M.SDL_MOUSEBUTTONUP = 0x402          -- Mouse button released */
M.SDL_MOUSEWHEEL = 0x403             -- Mouse wheel motion */
--Joystick events
M.SDL_JOYAXISMOTION  = 0x600          --< Joystick axis motion */
M.SDL_JOYBALLMOTION  = 0x601          --< Joystick trackball motion */
M.SDL_JOYHATMOTION  = 0x602           --< Joystick hat position change */
M.SDL_JOYBUTTONDOWN  = 0x603          --< Joystick button pressed */
M.SDL_JOYBUTTONUP  = 0x604            --< Joystick button released */
M.SDL_JOYDEVICEADDED  = 0x605         --< A new joystick has been inserted into the system */
M.SDL_JOYDEVICEREMOVED  = 0x606       --< An opened joystick has been removed */
--Game Controller events
M.SDL_CONTROLLERAXISMOTION  = 0x650          --< Game controller axis motion */
M.SDL_CONTROLLERBUTTONDOWN  = 0x651          --< Game controller button pressed */
M.SDL_CONTROLLERBUTTONUP  = 0x652            --< Game controller button released */
M.SDL_CONTROLLERDEVICEADDED  = 0x653         --< A new Game controller has been inserted into the system */
M.SDL_CONTROLLERDEVICEREMOVED  = 0x654       --< An opened Game controller has been removed */
M.SDL_CONTROLLERDEVICEREMAPPED  = 0x655      --< The controller mapping was updated */
--Clipboard Events
M.SDL_CLIPBOARDUPDATE = 0x900
--Drag and Drop Events
M.SDL_DROPFILE        = 0x1000
-- Render events
M.SDL_RENDER_TARGETS_RESET = 0x2000

M.SDL_USEREVENT    = 0x8000

M.SDL_LASTEVENT    = 0xFFFF
return M
end

function keyCode()
local M = {}

M.SDLK_UNKNOWN = 0

M.SDLK_RETURN = 13
M.SDLK_ESCAPE = 27
M.SDLK_BACKSPACE = 8
M.SDLK_TAB = 9
M.SDLK_SPACE = 32
M.SDLK_EXCLAIM = 33
M.SDLK_QUOTEDBL = 34
M.SDLK_HASH = 35
M.SDLK_PERCENT = 37
M.SDLK_DOLLAR = 36
M.SDLK_AMPERSAND = 38
M.SDLK_QUOTE = 39
M.SDLK_LEFTPAREN = 40
M.SDLK_RIGHTPAREN = 41
M.SDLK_ASTERISK = 42
M.SDLK_PLUS = 43
M.SDLK_COMMA = 44
M.SDLK_MINUS = 45
M.SDLK_PERIOD = 46
M.SDLK_SLASH = 47

M.SDLK_0 = 48
M.SDLK_1 = 49
M.SDLK_2 = 50
M.SDLK_3 = 51
M.SDLK_4 = 52
M.SDLK_5 = 53
M.SDLK_6 = 54
M.SDLK_7 = 55
M.SDLK_8 = 56
M.SDLK_9 = 57

M.SDLK_COLON = 58
M.SDLK_SEMICOLON = 59
M.SDLK_LESS = 60
M.SDLK_EQUALS = 61
M.SDLK_GREATER = 62
M.SDLK_QUESTION = 63
M.SDLK_AT = 64

--skip uppercase letters

M.SDLK_LEFTBRACKET = 91
M.SDLK_BACKSLASH = 92
M.SDLK_RIGHTBRACKET = 93
M.SDLK_CARET = 94
M.SDLK_UNDERSCORE = 95
M.SDLK_BACKQUOTE = 96
M.SDLK_a = 97
M.SDLK_b = 98
M.SDLK_c = 99
M.SDLK_d = 100
M.SDLK_e = 101
M.SDLK_f = 102
M.SDLK_g = 103
M.SDLK_h = 104
M.SDLK_i = 105
M.SDLK_j = 106
M.SDLK_k = 107
M.SDLK_l = 108
M.SDLK_m = 109
M.SDLK_n = 110
M.SDLK_o = 111
M.SDLK_p = 112
M.SDLK_q = 113
M.SDLK_r = 114
M.SDLK_s = 115
M.SDLK_t = 116
M.SDLK_u = 117
M.SDLK_v = 118
M.SDLK_w = 119
M.SDLK_x = 120
M.SDLK_y = 121
M.SDLK_z = 122

M.SDLK_CAPSLOCK = 0x40000039

M.SDLK_F1 = 0x4000003A
M.SDLK_F2 = 0x4000003B
M.SDLK_F3 = 0x4000003C
M.SDLK_F4 = 0x4000003D
M.SDLK_F5 = 0x4000003E
M.SDLK_F6 = 0x4000003F
M.SDLK_F7 = 0x40000040
M.SDLK_F8 = 0x40000041
M.SDLK_F9 = 0x40000042
M.SDLK_F10 = 0x40000043
M.SDLK_F11 = 0x40000044
M.SDLK_F12 = 0x40000045

M.SDLK_PRINTSCREEN = 0x40000046
M.SDLK_SCROLLLOCK = 0x40000047
M.SDLK_PAUSE = 0x40000048
M.SDLK_INSERT = 0x40000049
M.SDLK_HOME = 0x4000004A
M.SDLK_PAGEUP = 0x4000004B
M.SDLK_DELETE = 127
M.SDLK_END = 0x4000004D
M.SDLK_PAGEDOWN = 0x4000004E
M.SDLK_RIGHT = 0x4000004F
M.SDLK_LEFT = 0x40000050
M.SDLK_DOWN = 0x40000051
M.SDLK_UP = 0x40000052

M.SDLK_LCTRL = 0x400000E0
M.SDLK_LSHIFT = 0x400000E1
M.SDLK_LALT = 0x400000E2
M.SDLK_LGUI = 0x400000E3
M.SDLK_RCTRL = 0x400000E4
M.SDLK_RSHIFT = 0x400000E5
M.SDLK_RALT = 0x400000E6
M.SDLK_RGUI = 0x400000E7

M.SDLK_MODE = 0x40000101
return M
end

function keyMod()
local M = {}
M.KMOD_NONE = 0x0000
M.KMOD_LSHIFT = 0x0001
M.KMOD_RSHIFT = 0x0002
M.KMOD_LCTRL = 0x0040
M.KMOD_RCTRL = 0x0080
M.KMOD_LALT = 0x0100
M.KMOD_RALT = 0x0200
M.KMOD_LGUI = 0x0400
M.KMOD_RGUI = 0x0800
M.KMOD_NUM = 0x1000
M.KMOD_CAPS = 0x2000
M.KMOD_MODE = 0x4000
M.KMOD_RESERVED = 0x8000
return M
end

function mouseButton()
local M = {}
M.SDL_BUTTON_LEFT     = 1
M.SDL_BUTTON_MIDDLE   = 2
M.SDL_BUTTON_RIGHT    = 3
M.SDL_BUTTON_X1       = 4
M.SDL_BUTTON_X2       = 5
return M
end

function scanCode()
local M = {}

	M.Key_UNKNOWN = 0

	M.Key_A = 4
    M.Key_B = 5
    M.Key_C = 6
    M.Key_D = 7
    M.Key_E = 8
    M.Key_F = 9
    M.Key_G = 10
    M.Key_H = 11
    M.Key_I = 12
    M.Key_J = 13
    M.Key_K = 14
    M.Key_L = 15
    M.Key_M = 16
    M.Key_N = 17
    M.Key_O = 18
    M.Key_P = 19
    M.Key_Q = 20
    M.Key_R = 21
    M.Key_S = 22
    M.Key_T = 23
    M.Key_U = 24
    M.Key_V = 25
    M.Key_W = 26
    M.Key_X = 27
    M.Key_Y = 28
    M.Key_Z = 29
	
    M.Key_1 = 30
    M.Key_2 = 31
    M.Key_3 = 32
    M.Key_4 = 33
    M.Key_5 = 34
    M.Key_6 = 35
    M.Key_7 = 36
    M.Key_8 = 37
    M.Key_9 = 38
    M.Key_0 = 39

    M.Key_RETURN = 40
    M.Key_ESCAPE = 41
    M.Key_BACKSPACE = 42
    M.Key_TAB = 43
    M.Key_SPACE = 44

    M.Key_MINUS = 45
    M.Key_EQUALS = 46
    M.Key_LEFTBRACKET = 47
    M.Key_RIGHTBRACKET = 48
    M.Key_BACKSLASH = 49
	
	M.Key_NONUSHASH = 50
	
	M.Key_SEMICOLON = 51
    M.Key_APOSTROPHE = 52
    M.Key_GRAVE = 53
	
	M.Key_COMMA = 54
    M.Key_PERIOD = 55
    M.Key_SLASH = 56
	
	M.Key_CAPSLOCK = 57

    M.Key_F1 = 58
    M.Key_F2 = 59
    M.Key_F3 = 60
    M.Key_F4 = 61
    M.Key_F5 = 62
    M.Key_F6 = 63
    M.Key_F7 = 64
    M.Key_F8 = 65
    M.Key_F9 = 66
    M.Key_F10 = 67
    M.Key_F11 = 68
    M.Key_F12 = 69

    M.Key_PRINTSCREEN = 70
    M.Key_SCROLLLOCK = 71
    M.Key_PAUSE = 72
    M.Key_INSERT = 73
	
	M.Key_HOME = 74
    M.Key_PAGEUP = 75
    M.Key_DELETE = 76
    M.Key_END = 77
    M.Key_PAGEDOWN = 78
    M.Key_RIGHT = 79
    M.Key_LEFT = 80
    M.Key_DOWN = 81
    M.Key_UP = 82

    M.Key_NUMLOCKCLEAR = 83
	
	
	M.Key_LCTRL = 224
    M.Key_LSHIFT = 225
    M.Key_LALT = 226
    M.Key_LGUI = 227
    M.Key_RCTRL = 228
    M.Key_RSHIFT = 229
    M.Key_RALT = 230
    M.Key_RGUI = 231

    M.Key_MODE = 257
return M
end