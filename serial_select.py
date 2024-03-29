import serial
import serial.tools.list_ports as ser_port_list
import tkinter as tk

''' Display serial ports of all connected devices '''
class SerialSelect(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent 

        ''' Widget header '''
        self.header = tk.Label(self, text="Serial Ports")
        self.header.pack(side = tk.TOP, fill = "x", expand=True)

        ''' Listbox of available serial ports '''
        self.port_list = tk.Listbox(self)
        self.port_list.pack(fill = "x", expand=True)   

        ''' Buttons '''
        self.btn_frame = tk.Frame(self)

        self.refresh_btn = tk.Button(self.btn_frame, text = "Refresh", command = self.ports_refresh)
        self.refresh_btn.pack(side = "left", fill = "x", expand=True)  

        self.connect_btn = tk.Button(self.btn_frame, text = "Connect", command = self.port_set)
        self.connect_btn.pack(side = "right", fill = "x", expand=True) 

        self.btn_frame.pack(side="bottom", fill="both", expand=True)

        ''' Available serial ports '''
        self.ports = ser_port_list.comports()

        for port in self.ports:
            self.port_list.insert("end", port.device)

        ''' Selected serial port '''
        self.current_port = None

    def ports_refresh(self):
        self.port_list.delete(0, "end")
        self.ports = ser_port_list.comports()

        for port in self.ports:
            self.port_list.insert("end", port.device)

    def port_set(self):
        self.current_port = self.port_list.get("active")

if __name__ == "__main__":
    root = tk.Tk()
    SerialSelect(root).pack(side="top", fill="both", expand=True)
    root.mainloop()