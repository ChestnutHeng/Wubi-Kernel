raw_f = open("data.les")

raw = raw_f.readlines()

out_f = open("stdout.les")

out = out_f.readlines()


wr = 0.
co = 0.

for i in range(0,len(out)):
	if out[i].strip() != raw[i].strip():
		wr += 1
		print("Wrong:" + out[i].strip() + "\tAct:" + raw[i].strip())
	co += 1
	
	
print('Accuracy: %.2f'%(1 - wr/co))
