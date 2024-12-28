-- Modules are just files!


-- foo.lua  file
local M = {} -- M === Modules, {} === a table that'll be returned. for flexibility
M.cool_function = function() end
return M


-- bar.lua file
local foo = require('foo') -- basically importing other files like in java
foo.cool_function()
