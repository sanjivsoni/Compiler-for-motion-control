import Tkinter as tk
import subprocess

root = tk.Tk()

root.minsize(675 ,415)
root.maxsize(675,415)


def  serveParse():
    subprocess.call(['make motionController'], shell=True)

def serveMake(rowEntry,colEntry,obstacleEntry,startEntry,endEntry):
    fileObj=open('/Users/abhisheksachdeva/Desktop/Compiler-for-motion-control/config.in','r+')
    fileObj.seek(0)
    fileObj.truncate()
    fileObj.write("columns = ")
    fileObj.write(str(colEntry.get()))
    fileObj.write("\nrows = ")
    fileObj.write(str(rowEntry.get()))
    fileObj.write("\nobstacle = ")
    fileObj.write(str(obstacleEntry.get()))
    fileObj.write("\nstart = ")
    fileObj.write(str(startEntry.get()))
    fileObj.write("\nend = ")
    fileObj.write(str(endEntry.get()))
    
    
    
def window():

    label = tk.Label( text="Welcome to Compiler Motion Control", font=("Helvetica",28))
    label.place(x=115, y=25)
    
    rows=tk.Label(text="Rows ", font=("Helvetica",16))
    rows.place(x=80,y=100)
    rowEntry=tk.Entry(width=40)
    rowEntry.place(x=190,y=100)
    
    cols=tk.Label(text="Columns ", font=("Helvetica",16))
    cols.place(x=80,y=140)
    colEntry=tk.Entry(width=40)
    colEntry.place(x=190,y=140)
    
    obstacle=tk.Label(text="Obstacles ", font=("Helvetica",16))
    obstacle.place(x=80,y=180)
    obstacleEntry=tk.Entry(width=40)
    obstacleEntry.place(x=190,y=180)
    
    start=tk.Label(text="Start Point ", font=("Helvetica",16))
    start.place(x=80,y=220)
    startEntry=tk.Entry(width=40)
    startEntry.place(x=190,y=220)
    
    end=tk.Label(text="End Point ", font=("Helvetica",16))
    end.place(x=80,y=260)
    endEntry=tk.Entry(width=40)
    endEntry.place(x=190,y=260)
    
    make=tk.Button(text="Make File", font=("Helvetica",16) , command=lambda: serveMake(rowEntry,colEntry,obstacleEntry,startEntry,endEntry))
    make.place(x=190, y=320)
    
    parse=tk.Button(text="Generate Path", font=("Helvetica",16) , command=lambda: serveParse())
    parse.place(x=300, y=320)


window()
root.title("Motion Control")
root.mainloop()