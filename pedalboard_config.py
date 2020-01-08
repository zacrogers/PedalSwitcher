import serial
import serial.tools.list_ports as ser_port_list
import time
import tkinter as tk


''' Widget imports '''
from serial_select import SerialSelect


class IOChannelSelect(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent    

        self.labels = [
            ("Loop 1", "1"), 
            ("Loop 2", "2"), 
            ("Loop 3", "3"), 
            ("Loop 4", "4"),
            ("Main Out", "4")
        ]
        self.radio_btns = []
        v = tk.StringVar()
        v.set("INIT")

        for text, mode in self.labels:
            b = tk.Radiobutton(parent, text = text, 
                                variable = v, value = mode)
            b.pack()

            self.radio_btns.append(b)

class PedalboardConfig(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent

        ''' Channel routing widgets '''
        self.channel_1 = IOChannelSelect(self).pack(side = tk.LEFT)
        # self.channel_2 = IOChannelSelect(self).pack(side = tk.LEFT)
        # self.channel_3 = IOChannelSelect(self).pack(side = tk.LEFT)
        # self.channel_4 = IOChannelSelect(self).pack(side = tk.LEFT)

        ''' Serial port select widget '''
        self.port_select = SerialSelect(self)
        self.port_select.pack(side = tk.LEFT)



if __name__ == "__main__":
    root = tk.Tk()
    PedalboardConfig(root).pack(side="top", fill="both", expand=True)
    root.mainloop()