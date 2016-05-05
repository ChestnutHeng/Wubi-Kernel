#!/usr/bin/env python3

import viterbi as vt
import copy

dicts = vt.load_map()
uni_map = dicts[0]
big_map = dicts[1]
wd_map = dicts[2]
wubi = dicts[3]
wubi_map = {}
ans = []

def all_seg(inp,seg,level):
	"OUTPUT all segments"
	global ans
	if level >= len(inp):
		seg.append(copy.deepcopy(ans))
		return
	else:
		if level + 2 <= len(inp):
			ans.append(inp[level:level + 2])
			all_seg(inp,seg,level + 2)
			ans.pop()
		if level + 4 <= len(inp):
			ans.append(inp[level:level + 4])
			all_seg(inp,seg,level + 4)
			ans.pop()
	

def seg(inp):
	"segmenter main function"
	#load wubimap
	for line in wubi:
		wubi_map[line[0]] = int(line[1])
	
	#all segments here
	seg = []
	all_seg(inp,seg,0)
	
	#find viterbi path every segment
	vit = []
	for segline in seg:
		ans = vt.viterbi(segline,uni_map, big_map, wd_map, wubi)
		if not ans == None:
			vit.append(ans)
	
	vit.sort(key=lambda path: path[1], reverse=False)

	#return max viterbi path
	if len(vit) > 0:
		return vit[-1][0]
	else:
		return False
	
