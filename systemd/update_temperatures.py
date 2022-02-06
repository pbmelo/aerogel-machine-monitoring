import time
import numpy as np
import serial
import glob

#ws_root = "/var/www/localhost/htdocs/"
ws_root = "/var/www/html/"
data_file2 = ws_root+"graphs/data.csv"
data2 = []
max_len = 20

available_devices=glob.glob('/dev/ttyACM*')
for each_device in available_devices:
    print(each_device)

ser = serial.Serial(available_devices[0], 115200, timeout=2, xonxoff=False, rtscts=False, dsrdtr=False)
ser.flushInput()
ser.flushOutput()

sensor_string = "Sensor outputs"

time_init = time.time()

while (True):
    if(ser.in_waiting):
        #data_raw = str(ser.readline())
        data_raw = ser.readline().decode('unicode_escape')
        if (sensor_string in data_raw):
            temperature1 = str(round(float(data_raw.split(" ")[-9].replace("\n","")),1))
            temperature2 = str(round(float(data_raw.split(" ")[-8].replace("\n","")),1))
            temperature3 = str(round(float(data_raw.split(" ")[-7].replace("\n","")),1))
            temperature4 = str(round(float(data_raw.split(" ")[-6].replace("\n","")),1))
            pressure1 = str(data_raw.split(" ")[-5].replace("\n",""))
            pressure2 = str(data_raw.split(" ")[-4].replace("\n",""))
            pressure3 = str(data_raw.split(" ")[-3].replace("\n",""))
            relay1 = str(data_raw.split(" ")[-2].replace("\n",""))
            relay2 = str(data_raw.split(" ")[-1].replace("\n",""))
        else:
            continue
        time_unix = time.time()
        time_std = time.ctime()
        time_fmt = time.strftime('%H:%M:%S', time.localtime(time_unix))
        #data2.append(str(time_unix-time_init)+","+str(np.cos(time_unix)))
        #data2.append(time_fmt+","+str(50.0+10.0*np.cos(time_unix)))
        data2.append(time_fmt+","+temperature1+","+temperature2+","+temperature3+","+temperature4+","+pressure1+","+pressure2+","+pressure3+","+relay1+","+relay2)
        #print(data[-1])
        print(data2[-1].rstrip())
        if (len(data2) > max_len):
            data2.pop(0)
            with open(data_file2,"w") as f_out2:
                f_out2.write("datetime,temperature1,temperature2,temperature3,temperature4,pressure1,pressure2,pressure3,relay1,relay2\n")
                for each_entry in data2:
                    f_out2.write(each_entry)
                    f_out2.write("\n")
    else:
        time.sleep(0.1)
