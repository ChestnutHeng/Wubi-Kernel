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

def all_seg(inp,seg,level,tail):
	"OUTPUT all segments"
	global ans
	if level >= len(inp):
		seg.append(copy.deepcopy(ans))
		seg[-1][-1] += tail
		return
	else:
		if level + 2 <= len(inp):
			ans.append(inp[level:level + 2])
			all_seg(inp,seg,level + 2,tail)
			ans.pop()
		if level + 4 <= len(inp):
			ans.append(inp[level:level + 4])
			all_seg(inp,seg,level + 4,tail)
			ans.pop()
	

def seg(inp):
	"segmenter main function"
	tail = ""
	if len(inp) % 2 != 0:
		tail = inp[-1]
		inp = inp[:-1]
		
	#load wubimap
	for line in wubi:
		wubi_map[line[0]] = int(line[1])
	
	#all segments here
	seg = []
	all_seg(inp,seg,0,tail)
	
	#find viterbi path every segment
	vit = []
	for segline in seg:
		ans = vt.viterbi(segline,uni_map, big_map, wd_map, wubi)
		if not ans == None:
			#ans[1] = ans[1] - 20*len(ans[0])
			vit.append(ans)
	
	vit.sort(key=lambda path: path[1], reverse=False)
	
	for v in vit:
		#print(v)
		pass
	
	#return max viterbi path
	if len(vit) > 0:
		return vit[-1][0]
	else:
		return False
	
