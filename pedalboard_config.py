import serial
import serial.tools.list_ports as ser_port_list
import time
import tkinter as tk

''' Widget imports '''
from serial_select import SerialSelect
from io_channel_select import IOChannelSelect

''' Setup routing configuration for arduino pedalboard '''
class PedalboardConfig(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent

        ''' Serial port select widget '''
        self.port_select = SerialSelect(self.parent)
        self.port_select.pack(side = tk.LEFT)

        ''' Channel routing widgets '''
        self.channel_1 = IOChannelSelect(self.parent, title = "Channel 1")
        self.channel_1.pack(side = tk.LEFT)

        self.channel_2 = IOChannelSelect(self.parent, title = "Channel 2")
        self.channel_2.pack(side = tk.LEFT)

        self.channel_3 = IOChannelSelect(self.parent, title = "Channel 3")
        self.channel_3.pack(side = tk.LEFT)

        self.channel_4 = IOChannelSelect(self.parent, title = "Channel 4")
        self.channel_4.pack(side = tk.LEFT)


if __name__ == "__main__":
    root = tk.Tk()
    PedalboardConfig(root).pack(fill="both", expand = False)
    root.mainloop()