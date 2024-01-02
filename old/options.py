import tkinter as tk
import serial
from board_profile import BoardProfile

class Options(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent
        self.pad_y = 5

        self.patch_label = tk.Label(self, text = "Patches")
        self.patch_label.pack(side = tk.TOP, fill = "both", expand = True)

        self.patch_names = [
            "1", 
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"
        ]
        self.selected = tk.StringVar()
        self.selected.set(self.patch_names[0])

        self.patch_list = tk.OptionMenu(self, self.selected, *self.patch_names)
        self.patch_list.pack(side = tk.TOP, fill = "both", expand = True, pady = self.pad_y)

        self.save_btn = tk.Button(self, text = "Save")
        self.save_btn.pack(side = tk.TOP, fill = "both", expand = True, pady = self.pad_y)

        self.load_btn = tk.Button(self, text = "Load")
        self.load_btn.pack(side = tk.TOP, fill = "both", expand = True, pady = self.pad_y)

        self.sync_from_btn = tk.Button(self, text = "Sync from")
        self.sync_from_btn.pack(side = tk.TOP, fill = "both", expand = True, pady = self.pad_y)

        self.sync_to_btn = tk.Button(self, text = "Sync to")
        self.sync_to_btn.pack(side = tk.TOP, fill = "both", expand = True, pady = self.pad_y)

        self.synched_label = tk.Label(self, text = "Sync", bg = "red")
        self.synched_label.pack(side = tk.TOP, fill = "both", expand = False, pady = self.pad_y)

        self.is_synched = False

  

