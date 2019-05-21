function contains_two_number_sum(array, total)
	local number_hash = { }

	for i = 1, #array
	do
		if number_hash[total - array[i]] ~= nil
		then
			return true
		end

		number_hash[array[i]] = true
	end

	return false
end

io.write(tostring(contains_two_number_sum({ 10, 15, 3, 7 }, 17)), "\n")