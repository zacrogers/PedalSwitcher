import tkinter as tk

class IOChannelSelect(tk.Frame):
    def __init__(self, parent, title, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent    

        self.title = tk.Label(self, text=title)
        self.title.pack(side = tk.TOP)

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
            b = tk.Radiobutton(self, text = text, 
                                variable = v, value = mode)
            b.pack(side = tk.TOP)
            self.radio_btns.append(b)