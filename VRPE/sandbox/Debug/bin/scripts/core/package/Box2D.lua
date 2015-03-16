function b2FixtureDef()
local M = {}

M.friction = 0.2f
M.restitution = 0.0f
M.density = 0.0f
M.isSensor = false

return M
end

function b2BodyDef()
local M = {}

M.posX = 0.0f
M.posY = 0.0f
M.angle = 0.0f
M.linearVelocityX = 0.0f
M.linearVelocityY = 0.0f
M.angularVelocity = 0.0f
M.linearDamping = 0.0f
M.angularDamping = 0.0f
M.allowSleep = true
M.awake = true
M.fixedRotation = false
M.bullet = false
M.active = true
M.gravityScale = 1.0f

return M
end