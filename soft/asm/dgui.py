# From here: https://realpython.com/python-gui-tkinter/
#

import tkinter as tk

window = tk.Tk()
greeting = tk.Label(text="Hello, Tkinter")
greeting.pack()
label = tk.Label(text="Hello, Tkinter", background="#34A2FE")
label.pack()
button = tk.Button(text="Click me!", width=25, height=5, bg="blue", fg="yellow")
button.pack()
entry = tk.Entry()
entry.pack()
window.mainloop()
