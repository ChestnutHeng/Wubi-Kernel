f = open("data.std")

lines = f.readlines()

t = open("data.les","w")

for line in lines:
	if len(line) <= 6:
		t.write(line)

t.write("#")

