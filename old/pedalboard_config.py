import serial
import serial.tools.list_ports as ser_port_list
import time
import tkinter as tk
import tkinter.filedialog as tkfile
import os

''' Widget imports '''
from serial_select import SerialSelect
from io_channel_select import IOChannelSelect
from options import Options
from board_profile import BoardProfile



''' 
    Setup routing configuration for arduino pedalboard 

    Child frame classes handle layout, all logic handled in PedalboardConfig    
    except for SerialSelect
'''
class PedalboardConfig(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent
        self.pad_x = 10

        self.baud = 9600
        self.port = None
        self.is_synched = False

        self.current_profile = BoardProfile("Profile", 0, 0, 0, 0, 0)

        self.init_gui()


    def init_gui(self):
        ''' Serial port select widget '''
        self.port_select = SerialSelect(self.parent)
        self.port_select.connect_btn.configure(command = self.board_connect)
        self.port_select.pack(side = tk.LEFT, padx = self.pad_x, pady = 10)

        ''' Channel routing widgets '''
        self.main_input = IOChannelSelect(self.parent, title = "Input")
        self.main_input.pack(side = tk.LEFT, padx = self.pad_x)

        self.return_1 = IOChannelSelect(self.parent, title = "Return 1")
        self.return_1.radio_btns[0].configure(state = tk.DISABLED)
        self.return_1.pack(side = tk.LEFT, padx = self.pad_x)

        self.return_2 = IOChannelSelect(self.parent, title = "Return 2")
        self.return_2.radio_btns[1].configure(state = tk.DISABLED)
        self.return_2.pack(side = tk.LEFT, padx = self.pad_x)

        self.return_3 = IOChannelSelect(self.parent, title = "Return 3")
        self.return_3.radio_btns[2].configure(state = tk.DISABLED)
        self.return_3.pack(side = tk.LEFT, padx = self.pad_x)

        self.return_4 = IOChannelSelect(self.parent, title = "Return 4")
        self.return_4.radio_btns[3].configure(state = tk.DISABLED)
        self.return_4.pack(side = tk.LEFT, padx = self.pad_x)

        ''' Options frame for syncing to board'''
        self.options = Options(self.parent)
        self.options.save_btn.configure(command = self.save_profile)
        self.options.load_btn.configure(command = self.load_profile)
        self.options.sync_to_btn.configure(command = self.sync_to)
        self.options.sync_from_btn.configure(command = self.sync_from)
        self.options.pack(side = tk.LEFT, padx = self.pad_x, expand = False)


    ''' Connect to currently selected serial device '''
    def board_connect(self):
        self.port = self.port_select.port_list.get("active")
        print(self.port)


    ''' Toggle sync flag and set sync indicator '''
    def toggle_sync(self):
        if(self.is_synched is False):
            self.is_synched = True
            self.options.synched_label.configure(bg = "green")
        else:
            self.is_synched = False
            self.options.synched_label.configure(bg = "red")     


    ''' Save profile to disk '''
    def save_profile(self):
        pass


    ''' Load profile from disk '''
    def load_profile(self):
        f_name = tkfile.askopenfilename(initialdir = f"{os.getcwd()}", 
                                        filetypes = (("Config files", "*.pbcfg"),
                                                     ("All files","*.*"), 
                                                     ("Text file", "*.txt")),
                                        title = "Choose a file"
                                        )

        try:
            with open(f_name, 'r') as f:
                print(f.read())

        except:
            print("No file exists")


    ''' Get current profile from pedalboard '''
    def sync_from(self):
        board = serial.Serial(self.port, self.baud, timeout = 0.1)
        board.write("SYNC FROM".encode())

        reply = board.read()

        if(reply == "CONNECTED"):
            self.toggle_sync()


    ''' Send current profile to pedalboard '''
    def sync_to(self):
        board = serial.Serial(self.port, self.baud, timeout = 0.1)
        board.write("SYNC TO".encode())

        reply = board.read()

        if(reply == "CONNECTED"):
            self.toggle_sync()



if __name__ == "__main__":
    root = tk.Tk()
    root.title("Pedalboard Config")
    PedalboardConfig(root).pack(fill="both", expand = False)
    root.mainloop()