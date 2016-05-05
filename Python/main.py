#!/usr/bin/env python3

import segment as sg

inputSylla = ""
screen = []
output = ""

numbers = list("0123456789")

#print(sg.seg("ektygcmqcqlg"))
#print(sg.seg("wygdgdrndhqa"))
#
while len(inputSylla) == 0 or inputSylla[-1] != "#":
	inp_ch = input("Please input char:")
	if inp_ch != "" and inp_ch[0].isdigit():
		print("Choose :" + screen[int(inp_ch)][0] + str(screen[int(inp_ch)][1]))
		output += screen[int(inp_ch)][0]
		inputSylla = inputSylla[screen[int(inp_ch)][1]:]
		continue
	else:	
		#update input Sylla
		inputSylla += inp_ch
	print(sg.seg(inputSylla))
	
	#max incorrection pattern
	screen = []
	it = 4
	counter = 0
	flag = True
	while it >= 0 and flag:
		for wubi_line in sg.wubi:
			if wubi_line[0].startswith(inputSylla[0:it]):
				screen.append([sg.wd_map[int(wubi_line[1])],it])
				counter += 1
			if counter >= 30:
				flag = False
				break;
		it = it - 1
	print("output: " + output + inputSylla)
	
	#print screen
	co = 0
	for lists in screen:
		if co % 5 == 0:
			print("")
		print(lists,end=" ")
		co += 1
	print("")
	
