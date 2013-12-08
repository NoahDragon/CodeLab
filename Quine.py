def f(s):
	l=s.find("f(",28)
	print s[:l+2]+repr(s)+s[-1]

if __name__ == '__main__':
	f('def f(s):\n\tl=s.find("f(",28)\n\tprint s[:l+2]+repr(s)+s[-1]\n\nif __name__ == \'__main__\':\n\tf()')
