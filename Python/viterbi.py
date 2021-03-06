#!/usr/bin/env python3

import os
import json
import copy

def rd_fl(px):
	fp = open(px, "r")
	lns = fp.readlines()
	for i in range(0, len(lns)):
		lns[i] = lns[i].strip().split()
	fp.close()
	return lns

def rm_dup(lst):
	assert isinstance(lst, list)
	rv = []
	mp = {}
	for item in lst:
		if item not in mp:
			mp[item] = None
			rv.append(item)
	return rv

	
def load_map():
	"LOAD maps"
	bigram = rd_fl("../Dict/bigram.txt")
	unigram = rd_fl("../Dict/unigram.txt")
	wubi = rd_fl("../Dict/wubi.txt")
	word = rd_fl("../Dict/word.txt")

	#  Fuck the UNIGRAM.
	uni_map = {}
	for uni_line in unigram:
		uni_map[int(uni_line[0])] = float(uni_line[1])

	#  Fuck the BIGRAM
	big_map = {}
	for big_line in bigram:
		big_map[(int(big_line[0]), int(big_line[1]))] = float(big_line[2])


	#  Fuck the WD map.
	wd_map = {}
	for wd_line in word:
		wd_map[int(wd_line[0])] = wd_line[1]
	return uni_map, big_map, wd_map, wubi

def viterbi(test,uni_map, big_map, wd_map, wubi):	
	"main viterbi function"
	if(len(test) == 0):
		test = [" ", " ", " "]
	test += ["zzzz"]
	candidate = []

	for can_item in test:
		candidate.append([])
		for wubi_line in wubi:
			if (wubi_line[0].startswith(can_item) and len(wd_map[int(wubi_line[1])]) == 1)\
					or wubi_line[0] == can_item:
				candidate[-1].append(int(wubi_line[1]))
		if len(candidate[-1]) == 0:
			#No items
			return

		candidate[-1] = rm_dup(candidate[-1])
		candidate[-1].sort()

	left_mp = copy.deepcopy(candidate)
	coeff_mp = copy.deepcopy(candidate)
	bptr_mp = copy.deepcopy(candidate)

	for col in range(0, len(candidate)):
		for row in range(0, len(candidate[col])):
			if col == 0:
				coeff_mp[col][row] = uni_map[candidate[col][row]]
			else:
				coeff_mp[col][row] = None
			left_mp[col][row] = uni_map[candidate[col][row]]
			bptr_mp[col][row] = -1
	INF = -13.8
	#print(coeff_mp)
	for col in range(1, len(candidate)):
		for row in range(0, len(candidate[col])):
			for row_prev in range(0, len(candidate[col - 1])):
				link = (candidate[col - 1][row_prev], candidate[col][row])
				link_coeff = INF
				if link in big_map:
					link_coeff = big_map[link]
				ncoeff = coeff_mp[col - 1][row_prev] + link_coeff + left_mp[col][row]
				if coeff_mp[col][row] is None:
					coeff_mp[col][row] = ncoeff
					bptr_mp[col][row] = row_prev
				else:
					if ncoeff > coeff_mp[col][row]:
						coeff_mp[col][row] = ncoeff
						bptr_mp[col][row] = row_prev

	mx_id = 0
	mx_val = candidate[-1][0]
	for row in range(1, len(candidate[-1])):
		if candidate[-1][row] > mx_val:
			mx_id = row
			mx_val = candidate[-1][row]

	fin = []
	col = len(candidate) - 1
	while mx_id >= 0:
		fin.append(wd_map[candidate[col][mx_id]])
		mx_id = bptr_mp[col][mx_id]
		col -= 1

	fin.reverse()
	return [fin, coeff_mp[-1][mx_id]]
	#print(fin)

