if __name__ == '__main__':
	hanoi = []
	for i in range(3):
		hanoi.append([])
	hanoi[0] = [0,1,2]
	hanoi[1] = [3,3,3]
	hanoi[2] = [3,3,3]

	def check(a,b,c):
		flag = False
		for i in range(3):
			if hanoi[b][i]<a:
				return False
			if hanoi[b][i] == a:
				flag = True
		if flag == False:
			return False 
		for j in range(3):
			if hanoi[c][j]<a:
				return False
		return True
	def find(a):
		if a<0:
			a=2
		if a<-1:
			a=1
		for i in range(3):
			for j in range(3):
				if hanoi[i][j] == a:
					return i
	def able(a):
		if a<0:
			a=2
		if a<-1:
			a=1
		b=0
		flag = True
		for i in range(3):
			for j in range(3):
				if hanoi[i][j]<a:
					flag = False
			if flag:
				b = i
			flag = True
		return b
	def ablenext(a,d):
		if a<0:
			a=2
		if a<-1:
			a=1
		flag = True
		b=0
		for i in range(3):
			for j in range(3):
				if hanoi[i][j]<a:
					flag = False
			if flag and d!=i:
				b=i
			flag = True
		return b		
	def reset(a,b,c):
		hanoi[b][a] = 3
		hanoi[c][a] = a
	def many(b):
		count = 0
		for i in range(3):
			if hanoi[b] < 3:
				count+=1
		return count
	def move(a,b,c):
		if b>2:
			b=0
		if a<0:
			a=2
		if c<0:
			c=2
		if c<-1:
			c=1
		if c>2:
			c=0
		if a>2:
			a=0
		if b==c:
			#move(a,b,c+1)
			return
		if hanoi[2][0]==0 and hanoi[2][1]==1 and hanoi[2][2]==2:
			return
		#if b==c:
		#	if many(b)>=2:
		#		move(a,b,c+1)
		#	else:
		#		move(a-1,find(a-1),c)
		if check(a,b,c):
			reset(a,b,c)
			print "IF:", a,b,c,hanoi
			d = able(a-1)
			if find(a-1) == d:
				d = ablenext(a-1,d)
			move(a-1,find(a-1),d)
			#return
		else:
			#move(a-1,b,c)
			print "ELSE:",a,b,c
			d = able(a-1)
			if find(a-1) == d:
				d = ablenext(a-1,d)
			move(a-1,find(a-1),d)
			#move(a-1,1,2)
		return
		#if b==c:
		#	move(a,b,c+1)
		#if check(a,b,c):
		#	reset(a,b,c)
		#	move(a,find(a),c)
		#else:
		#	move(a-1,find(a-1),c)

	move(2,0,2)
