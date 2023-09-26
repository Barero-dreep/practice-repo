from enum import Enum
from decimal import Decimal, getcontext
import numpy as np
from numpy import *
from tkinter import *

# Set-up
getcontext().prec = 16
getcontext().rounding = 'ROUND_HALF_UP'


#Classes

class Operations(Enum):
	invalid  = -1
	equal    = 0
	add      = 1
	subtract = 2
	multiply = 3
	divide   = 4

class CalcNums:
	currNum : Decimal = 0
	buffer  : Decimal = 0
	lastCommand : Operations = Operations(-1)

	def __init__(self):
		pass

	def clear(self):
		self.currNum = 0
		self.buffer = 0
		self.lastCommand = 0

	def exectueLastComm(self, num: Decimal) -> int | Decimal:
		self.buffer = num

		match self.lastCommand:
			case Operations.equal:
				self.currNum = self.currNum + self.buffer
			case Operations.add:
				self.currNum = self.currNum + num
			case Operations.subtract:
				self.currNum = self.currNum - num
			case Operations.multiply:
				self.currNum = self.currNum * num
			case Operations.divide:
				if(num == 0):
					raise Exception("Error: Division by 0")
				self.currNum = self.currNum / num
			case _:
				raise Exception("Error: No such command") 

		return self.currNum	

	def getVal(self) -> int | Decimal:
		if self.currNum != int(self.currNum):
			return self.currNum
		else:
			return int(self.currNum)


# Window
root = Tk()
root.title("Calculator")

e = Entry(root)
e.grid(row=0, column=0, columnspan=4, padx=20, pady=10)


# Commands
calcNums = CalcNums()

def button_click(number):
	num = str(e.get()) + str(number)
	
	e.delete(0, END)
	e.insert(0, num)

def button_command(command: Operations):
	global calcNums

	line = e.get()

	if line != "":
		calcNums.currNum = Decimal(line)
	else:
		calcNums.currNum = 0

	calcNums.lastCommand = command

	e.delete(0, END)

def button_equal():
	global calcNums

	calcNums.exectueLastComm(num=Decimal(e.get()))
	calcNums.lastCommand = Operations.equal

	e.delete(0, END)
	e.insert(0, calcNums.getVal())

def button_ce():
	global calcNums
	calcNums.clear()

	e.delete(0, END)

def button_clear():
	e.delete(0, END)

def button_delchar():
	line = e.get()
	e.delete(0, END)
	e.insert(0, line[:-1])

# Defining Buttons
#check if we have scale
#button_1 = Button(root, text="1", padx=40, pady=20, command=lambda: button_click(1))
button_1 = Button(root, text="1", width=15, justify="center", pady=20, command=lambda: button_click(1))
button_2 = Button(root, text="2", width=15, justify="center", pady=20, command=lambda: button_click(2))
button_3 = Button(root, text="3", width=15, justify="center", pady=20, command=lambda: button_click(3))
button_4 = Button(root, text="4", width=15, justify="center", pady=20, command=lambda: button_click(4))
button_5 = Button(root, text="5", width=15, justify="center", pady=20, command=lambda: button_click(5))
button_6 = Button(root, text="6", width=15, justify="center", pady=20, command=lambda: button_click(6))
button_7 = Button(root, text="7", width=15, justify="center", pady=20, command=lambda: button_click(7))
button_8 = Button(root, text="8", width=15, justify="center", pady=20, command=lambda: button_click(8))
button_9 = Button(root, text="9", width=15, justify="center", pady=20, command=lambda: button_click(9))
button_0 = Button(root, text="0", width=15, justify="center", pady=20, command=lambda: button_click(0))
															  
button_dot  = Button(root, text=".", width=15, justify="center", pady=20, command=lambda: button_click('.'))
button_conv = Button(root, text="+/-", width=15, justify="center", pady=20)

button_add    = Button(root, text="+", width=15, justify="center", pady=20, command=lambda: button_command(Operations.add))
button_substr = Button(root, text="-", width=15, justify="center", pady=20, command=lambda: button_command(Operations.subtract))
button_mult   = Button(root, text="*", width=15, justify="center", pady=20, command=lambda: button_command(Operations.multiply))
button_divide = Button(root, text="/", width=15, justify="center", pady=20, command=lambda: button_command(Operations.divide))
button_equal  = Button(root, text="=", width=15, justify="center", pady=20, command=button_equal)

button_ce      = Button(root, text="CE", width=15, justify="center", pady=20, command=button_ce)
button_clear   = Button(root, text="C", width=15, justify="center", pady=20, command=button_clear)
button_delchar = Button(root, text="Del", width=15, justify="center", pady=20, command=button_delchar)

button_ce.grid     (row=1,column=0)
button_clear.grid  (row=1,column=1)
button_delchar.grid(row=1,column=2)
button_divide.grid (row=1,column=3)

button_7.grid   (row=2,column=0)
button_8.grid   (row=2,column=1)
button_9.grid   (row=2,column=2)
button_mult.grid(row=2,column=3)

button_4.grid     (row=3,column=0)
button_5.grid     (row=3,column=1)
button_6.grid     (row=3,column=2)
button_substr.grid(row=3,column=3)

button_1.grid  (row=4,column=0)
button_2.grid  (row=4,column=1)
button_3.grid  (row=4,column=2)
button_add.grid(row=4,column=3)

button_conv.grid (row=5,column=0)
button_0.grid    (row=5,column=1)
button_dot.grid  (row=5,column=2)
button_equal.grid(row=5,column=3)

# Start
root.mainloop()