local function action(loves_coffee)
	if loves_coffee then
		print("Check out 'something' ...!")
	else
		print("Check out 'something else'!!!")
	end
end

-- "falsey" values: nil, false // Everything else is true by default
action() -- same as action(nil)
action(false)

-- everything else is truthy
action(true)
action(0)
action({})
