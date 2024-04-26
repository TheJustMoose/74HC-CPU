# From here: https://realpython.com/python-gui-tkinter/
#

import tkinter as tk
from PIL import Image, ImageTk

window = tk.Tk()
greeting = tk.Label(text="Hello, Tkinter")
greeting.pack()
label = tk.Label(text="Hello, Tkinter", background="#34A2FE")
label.pack()
button = tk.Button(text="Click me!", width=25, height=5, bg="blue", fg="yellow")
button.pack()

# Load and display an image
image = Image.open('cat-fish.jpg')
image = ImageTk.PhotoImage(image)

# Create a label to display the image
image_label = tk.Label(window, image=image)
image_label.pack()

entry = tk.Entry()
entry.pack()
window.mainloop()
