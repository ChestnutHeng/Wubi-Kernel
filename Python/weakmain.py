#!/usr/bin/env python3

import segment as sg

inputSylla = ""
output = ""



#print(sg.seg("ektygcmqcqlg"))
#print(sg.seg("wygdgdrndhqa"))

inputSylla = input()
while inputSylla != "#":
	ans = sg.seg(inputSylla)
	for i in range(0,len(ans)-1):
		print(ans[i],end="")
	print("")
	inputSylla = input()
	


