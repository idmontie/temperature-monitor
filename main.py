import wmi
import serial
import time

ser = serial.Serial(
    port='/dev/tty.usbmodem1411',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.open()

while True:
    w = wmi.WMI(namespace="root\OpenHardwareMonitor")
    temperature_infos = w.Sensor()
    for sensor in temperature_infos:
        if sensor.SensorType==u'Temperature':
            print(sensor.Name)
            print(sensor.Value)

    ser.write("CPU: 42°C\GPU: 62°C")
    timesleep(1)

ser.close()