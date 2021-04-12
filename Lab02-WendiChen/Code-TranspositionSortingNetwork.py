import sys

if sys.version_info.major == 2:
    from Tkinter import *
elif sys.version_info.major == 3:
    from tkinter import *


class MyCanvas(Canvas):
    def __init__(self, master, hLineWidth=1, vLineWidth=1, radius=2, **kwargs):
        Canvas.__init__(self, master, kwargs)
        self.hLineWidth = hLineWidth
        self.vLineWidth = vLineWidth
        self.radius = radius

    def create_segment_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x + l - self.radius, y - self.radius, x + l - self.radius, y + self.radius, fill='black')

    def create_segment_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x - self.radius, y + l - self.radius, x + self.radius, y + l + self.radius, fill='black')

    def create_line_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)

    def create_line_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)


class Sorter:
    def __init__(self, size):
        self.size = size

    def draw(self, cvs, hMargin, vMargin, hScale, vScale,W,H):
        if self.size > 1:
            for i in range(self.size):
                cvs.create_line_h(hMargin, vMargin+i*vScale,W-2*hMargin)
        
        for i in range ((self.size)//2):
            for j in range(i+1):
                cvs.create_segment_v(hMargin+hScale+hScale*(2*i),vMargin+vScale*(2*j),vScale)
                cvs.create_segment_v(W-hMargin-hScale-hScale*(2*i),vMargin+vScale*(2*j),vScale)
                if i+1<(self.size+1)//2 : 
                    cvs.create_segment_v(hMargin+hScale+hScale*(2*i+1),vMargin+vScale*(2*j+1),vScale)
                    cvs.create_segment_v(W-hMargin-hScale-hScale*(2*i+1),vMargin+vScale*(2*j+1),vScale)


if __name__ == '__main__':
    n = int(input('please input the number n: '))
    sortingNetwork = Sorter(n)

    winW, winH = 2400 * 0.6, 1500 * 0.6
    hMargin, vMargin = winW / 20, winH / 20
    hScale, vScale = (winW - 2 * hMargin) / (2*n-2), (winH - 2 * vMargin) / (n -1)

    root = Tk()
    root.title('Transposition Sorting Network with n=%d (Drawn by Python Tkinter)' % n)
    cvs = MyCanvas(root, bg='white', width=winW, height=winH)
    sortingNetwork.draw(cvs, hMargin, vMargin, hScale, vScale,winW,winH)
    cvs.pack()
    root.mainloop()
