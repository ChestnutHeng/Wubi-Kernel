#!/usr/bin/env python3

import segment as sg

inputSylla = ""
screen = []
output = ""



#print(sg.seg("ektygcmqcqlg"))
#print(sg.seg("wygdgdrndhqa"))

while len(inputSylla) == 0 or inputSylla[-1] != "#":
	#read input
	inp_ch = input("Please input char:")
	if inp_ch != "" and inp_ch[0].isdigit():
		#if input is a number
		print("Choose :" + on_screen[int(inp_ch)][0] + str(on_screen[int(inp_ch)][1]))
		output += on_screen[int(inp_ch)][0]
		inputSylla = inputSylla[on_screen[int(inp_ch)][1]:]
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
		tp_list = []
		for wubi_line in sg.wubi:
			if wubi_line[0].startswith(inputSylla[0:it]):
				wubi_code = int(wubi_line[1])
				if wubi_code in sg.uni_map:
					tp_list.append([sg.wd_map[wubi_code],it,sg.uni_map[wubi_code]])
				counter += 1
			if counter >= 30:
				flag = False
				tp_list.sort(key=lambda info: info[2], reverse=True)
				screen.append(tp_list)
				break;
		tp_list.sort(key=lambda info: info[2], reverse=True)
		screen.append(tp_list)
		it = it - 1
	print("output: " + output + inputSylla)
	
	on_screen = []
	for lines in screen:
		on_screen += lines
	
	i = 0
	for line in on_screen:
		if i % 5 == 0:
			print("")
		print(line[0:2],end="")
		i += 1
	print("")
	
	#print screen

