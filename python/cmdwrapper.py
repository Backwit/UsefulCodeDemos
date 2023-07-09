#!/usr/bin/python3
import os
import sys
import getopt

debug = True
shortopts = "hl:k:v:n:"
longopts = ["help", "log=", "key="]

def Debug(msg):
	#if debug: print(sys._getframe().f_code.co_name, sys._getframe().f_lineno,msg)
	if debug: print(msg)	

def ClearLog():
	Debug("ClearLog")

def GetLog():
	Debug("GetLog")

def GetAllLog():
	Debug("GetAllLog")

def Log(level):
	loglevel = {'0':ClearLog, '1':GetLog, '2':GetAllLog}
	Debug(level)
	loglevel[level]()

def main():
	print("main")
	try:
		opts, args = getopt.getopt(sys.argv[1:], shortopts, longopts)
	except getopt.error as msg:
		print(msg)
	for o,a in opts:
		if o in ['-h', '--help']:
			Debug([o,a])
		elif o in ['-l', '--log']:
			Debug([o,a])
			Log(a)
		elif o in ['-k', '--key']:
			Debug([o,a])
			key()

if __name__ == '__main__':
	main()