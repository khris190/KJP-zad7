import sys, os

import gi
import subprocess
import re

gi.require_version("Gtk", "3.0")
from gi.repository import GLib, Gtk
import numpy as np

from matplotlib.backends.backend_gtk3agg import  FigureCanvasGTK3Agg
from matplotlib.figure import Figure

def Extract(lst, pos):
    return list(list(zip(*lst))[pos])

class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="Button Demo")
        self.set_border_width(10)

        hbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL,spacing=5)
        buttonBox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL,spacing=2)
        self.add(hbox)

        self.button = Gtk.Button("Run")
        self.button.connect("clicked", self.on_click_me_clicked)
        buttonBox.pack_start(self.button, True, True, 0)

        label = Gtk.Label("iterations:")
        buttonBox.pack_start(label, True, True, 0)
        
        self.entry = Gtk.Entry()
        self.entry.set_text("10000000")
        self.entry.connect("changed", self.on_text_change)
        buttonBox.pack_start(self.entry, True, True, 0)

        fig = Figure(figsize=(1,1), dpi=100)
        self.ax = fig.add_subplot()
        
        self.ax.plot([0], [0])

        self.canvas = FigureCanvasGTK3Agg(fig)  # a Gtk.DrawingArea
        self.canvas.set_size_request(600, 600)

        hbox.add(buttonBox)
        hbox.add(self.canvas)
        
        files = os.listdir(os.path.dirname(__file__))
        self.executable = 'zad7.exe'
        if 'zad7' in files:
          self.executable = 'zad7'
        
    
    def on_text_change(self, entry):
        entry_context = entry.get_style_context()
        if entry.get_text().isnumeric():
            entry_context.remove_class("error")
            self.button.set_sensitive(True)
        else:        
            entry_context.add_class("error")
            self.button.set_sensitive(False)
    
    
    def on_click_me_clicked(self, button):
        print('"Click me" button was clicked')
        win.ax.clear()
        if self.entry.get_text().isnumeric():
            prog =  os.path.dirname(__file__) + '/' + self.executable + ' ' + self.entry.get_text()
            output = os.popen( prog).read()
            res = re.findall("([ \w]+)\\: (\d+)ns\.", output)
            names = [match[0] for match in res]
            vals = [int(match[1]) for match in res]
            self.ax.set_ylabel('Time (ns)')
            self.ax.bar(names,vals, color ='blue', width = 0.4)
            self.canvas.draw()
        else:        
            self.ax.plot([0], [0])
            self.canvas.draw()

css = '.error { border-color: #f00; }'
css_provider = Gtk.CssProvider()
css_provider.load_from_data(css)

win = MyWindow()
win.set_resizable(False)
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()