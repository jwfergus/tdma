#!/usr/bin/python

##################
# initial gui testing
#  Issues commands to nodes.
# v0.2
# author: Joshua Ferguson <jwfergus@asu.edu>
# 
##################

from Tkinter import *
import kill_and_flush
import start_user_app
import start_node_MEL
import update_repos


class App:

    def __init__(self, master):

        frame = Frame(master)
        frame.pack()

        self.button = Button(frame, text="QUIT", fg="red", command=frame.quit)
        self.button.pack(side=LEFT)

        self.update = Button(frame, text="update Repos", command=update_repos.update)
        self.update.pack(side=LEFT)

        self.kill_and_flush = Button(frame, text="Kill and Flush", command=kill_and_flush.kill_and_flush)
        self.kill_and_flush.pack(side=LEFT)

        self.start_node_MEL = Button(frame, text="Start Node MEL", command=start_node_MEL.start)
        self.start_node_MEL.pack(side=LEFT)

        self.start_user_app = Button(frame, text="Start User App", command=start_user_app.start_user_app)
        self.start_user_app.pack(side=LEFT)



root = Tk()

app = App(root)

root.mainloop()
