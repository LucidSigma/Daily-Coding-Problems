function get_product_array_without_division(array)
	local SIZE = #array
	local product_counter = 1
	local increasing_products = { }

	for i = 1, SIZE
	do
		increasing_products[i] = product_counter
		product_counter = product_counter * array[i]
	end

	product_counter = 1
	local decreasing_products = { }

	for i = SIZE, 1, -1
	do
		decreasing_products[i] = product_counter
		product_counter = product_counter * array[i]
	end

	local combined_products = { }

	for i = 1, SIZE
	do
		combined_products[i] = increasing_products[i] * decreasing_products[i]
	end

	return combined_products
end

function print_array(array)
	for i = 1, #array
	do
		io.write(array[i])

		if i ~= #array
		then
			io.write(", ")
		end
	end

	io.write("\n")
end

print_array(get_product_array_without_division({ 1, 2, 3, 4, 5 }))
print_array(get_product_array_without_division({ 3, 2, 1 }))