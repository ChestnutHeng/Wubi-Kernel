wd_map = {}
f = open("../Dict/wubi98.les")
lines = f.readlines()
for line in lines:
	line = line.strip()
	line = line.split()
	wd_map[line[1]] = line[0]
	
	

inp = input()
while inp != "#":

	while inp != "":
		false_flag = 1
	#foud max len word
		while false_flag <= 4:
			wd = inp[0:false_flag]
			if wd not in wd_map:
				break
			false_flag += 1
	#print code of this word	
		prefix = inp[0:false_flag-1]
		if len(prefix) == 1 and len(inp) == 1 and len(wd_map[prefix]) != 3:
			print(wd_map[prefix],end='')
		elif len(prefix) == 1:
			print(wd_map[prefix][0:2],end='')
		else:
			print(wd_map[prefix],end="")
		inp = inp[false_flag - 1:]
		
	print("")
	inp = input()
		
	
print("#")
#inp = input()
#while inp != "#":
#	for ch in inp:
#		print(wd_map[ch][0:2],end="")
#	print("")
#	inp = input()
	
