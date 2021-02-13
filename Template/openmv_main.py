import time
from pyb import UART

uart = UART(3,115200,timeout_char = 1000)

while(True):

    if uart.any():
       #a = uart.read(1)
       #a = uart.readline().decode()
       uart.write('s')

       time.sleep(500)

#import sys,sensor,os,time,math,image

#from pyb import UART


##system init

#uart1 = UART(1,9600,timeout_char = 1000)
#uart3 = UART(3,9600,timeout_char = 1000)

#clock = time.clock()

#sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QVGA)
#sensor.skip_frames()

#def main():

    #print("Dog Jin Is A Dog.")

    #while True:

        #clock.tick()

        #img = GetImage(sensor,sensor.RGB565,is_use_filter = False)

        #ImageProcess(img)

        #SendDataToK66(uart3,"Dog Jin Is A Dog.")

        #print(clock.fps())


#def GetImage(cap,img_format,is_use_filter):

    #img = cap.snapshot(pixformat = img_format)

    #if img_format == cap.GRAYSCALE:
        #img = img.to_grayscale()

    #if is_use_filter:
        #ImageFilter(img)
    #else:
        #return img


#def ImageFilter(img):

    #return img.mean(1)


## 图像处理函数
#def ImageProcess(img):

    #if img.format() != sensor.GRAYSCALE:
        #gimg = img.to_grayscale()

    #gimg.find_edges(image.EDGE_CANNY, threshold=(50, 80))



#def rgb2gray(rgbFrame):
    #grayFrame = rgbFrame
    #for x in range(0,rgbFrame.width()):
        #for y in range(0,rgbFrame.height()):
            #rgb = rgbFrame.get_pixel(x, y)
            #gray_data = int(image.rgb_to_grayscale(rgb)/3)
            #gray = (gray_data,gray_data,gray_data)
            #grayFrame.set_pixel(x,y,gray)
    #return grayFrame;

#def SendDataToK66(uart,data):

    #uart.write(data)

#def ReadDataFromK66(uart,length):

    #data = 0

    #data = uart.read(length)

    #return data


#if __name__=='__main__':

    #try:
        #main()
    #except Exception as e:
        #print(e)
