import tkinter as tk

class IOChannelSelect(tk.Frame):
    def __init__(self, parent, title, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent    

        self.title = tk.Label(self, text=title)
        self.title.pack(side = tk.TOP)

        self.labels = [
            ("Send 1", 0), 
            ("Send 2", 1), 
            ("Send 3", 2), 
            ("Send 4", 3),
            ("Output", 4)
        ]

        self.radio_btns = []
        v = tk.StringVar()
        v.set(0)

        for text, mode in self.labels:
            b = tk.Radiobutton(self, text = text, variable = v, value = mode)
            b.pack(side = tk.TOP, pady = 5)
            self.radio_btns.append(b)