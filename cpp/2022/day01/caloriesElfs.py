def fixMax(maximum, pos, val):
	if pos <= 2:
		tmp = maximum[pos]
		maximum[pos] = val
	if pos < 2:
		tmp2 = maximum[pos+1]
		maximum[pos+1] = tmp
	if pos == 0:
		maximum[pos+2] = tmp2
		
def lstMax(maximum, val):
	for i in range(0, len(maximum)):
		if val > maximum[i]:
			return i
	
	return -1
	
	
f = open('input.txt', 'r')
tmax = [0,0,0]
tsum = 0
for line in f:
	if line == '\n':
		pos = lstMax(tmax, tsum)
		if pos >= 0:
			fixMax(tmax, pos, tsum)
		tsum = 0
	else:
		tsum += int(line)

pos = lstMax(tmax, tsum)
if pos >= 0:
	fixMax(tmax, pos, tsum)		
print(sum(tmax))

f.close()
