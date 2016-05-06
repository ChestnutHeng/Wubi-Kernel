#!/usr/bin/env python3

import segment as sg

inputSylla = ""
output = ""



#print(sg.seg("ektygcmqcqlg"))
#print(sg.seg("wygdgdrndhqa"))

inputSylla = input()
while inputSylla != "#":
	print(sg.seg(inputSylla))
	inputSylla = input()
	


