#!/usr/bin/env python3 

import viterbi as vt

dicts = vt.load_map()
uni_map = dicts[0]
big_map = dicts[1]


wd_map = {}
f = open("word.txt")
lines = f.readlines()
for line in lines:
	line = line.strip()
	line = line.split()
	wd_map[line[1]] = line[0]
	
wubi_map = {}
fc = open("wubi.txt")
lines = fc.readlines()
for line in lines:
	line = line.strip()
	line = line.split()
	wubi_map[line[1]] = line[0]

pref = input("0(code), 1(uni), 2(bi):")

while(pref != "#"):
	if pref == "0":
		inp = input("Input your word:")
		while(inp != "#"):
			inp = inp.strip()
			inp = inp.split()
			for ele in inp:
				try:
					print(wubi_map[wd_map[ele]])
				except:
					print("False!")
			inp = input("Input your word:")

	elif pref == "1":
		inp = input("Input your word:")
		while(inp != "#"):
			try:
				print("Frac:" + str(uni_map[int(wd_map[inp])]))
			except:
					print("False!")
			inp = input("Input your word:")

	elif pref == "2":
		inp = input("Input your word A,B:")
		while(inp != "#"):
			inp = inp.strip()
			inp = inp.split()
			try:
				print("Frac:"+ str(big_map[int(wd_map[inp[0]]),int(wd_map[inp[1]])]))
			except:
					print("False!")
			inp = input("Input your word A,B:")
	else:
		print("END!")
	pref = input("0(code), 1(uni), 2(bi):")

print("Bye!")
