import mmap
import os
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
filename = "/home/plus/Desktop/dst.bmp"

file = open(filename, "r+")
size = os.path.getsize(filename)
data = mmap.mmap(file.fileno(), size)
#data = mmap.mmap(os.open(filename, os.O_RDWR), 1)
#number = ord(data.read(1))
#print (number)
#img1 = Image.new("RGB",(200,200))
img = np.empty([200,200,3])
cnt = 0
while True:
    p = ord(data[0])
    q = ord(data[1])
    print p,q
    #img1.show()
    for 
    
    for i in range(200):
        for j in range(200): 
            B = ord(data[3*200*i+3*j+54+0+120000*p])
            G = ord(data[3*200*i+3*j+54+1+120000*p])
            R = ord(data[3*200*i+3*j+54+2+120000*p])
            #img1.putpixel((j,i),(R,G,B))
            img[j][i][:] = [R,G,B]
    str = '/home/plus/Desktop/pic/img_%d_%d_%d.jpg'%(cnt,p,q)
    img.save(str)
    #plt.imshow(img1)
    #plt.show()
    #img1.show()
        
    cnt = cnt+1
        #plt.imshow(img1)
        #plt.show()
        #img2.show()

