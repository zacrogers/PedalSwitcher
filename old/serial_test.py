import serial
import time
import tkinter as tk


port = 'COM3'
baud = 9600

arduino = serial.Serial(port, baud, timeout = 0.1)


def send(s):
    time.sleep(1)
    arduino.write(s.encode())
    time.sleep(1)


root = tk.Tk()
frame = tk.Frame(root)
frame.pack()

btn1 = tk.Button(frame, text = "LED1", command = lambda : send('test config file'))
btn1.pack(side = tk.LEFT)

btn2 = tk.Button(frame, text = "LED2", command = lambda : send('2'))
btn2.pack(side = tk.LEFT)

btn3 = tk.Button(frame, text = "LED3", command = lambda : send('3'))
btn3.pack(side = tk.LEFT)

btn4 = tk.Button(frame, text = "LED4", command = lambda : send('4'))
btn4.pack(side = tk.LEFT)

root.mainloop()
