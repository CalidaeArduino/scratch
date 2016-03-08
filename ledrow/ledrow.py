import serial, time
from subprocess import check_output, PIPE

# Setup connection (/dev/ttyUSBX, check with ls or something)
arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(1) #give the connection a second to settle

# Define your max X
screen_width = 1366


lastLed = False
while True:
	# Get your mouse X (sudo apt-get install xdotool)
	mouse_x = int(check_output(["xdotool", "getmouselocation"]).split(":")[1].split(" ")[0])

	# Transform to world 0-7 (row leds)
	led = int(mouse_x/float(screen_width)*8)

	if led != lastLed:
		print str(led)
		arduino.write(str(led))
		lastLed = led
		time.sleep(1)





# import serial, time
# arduino = serial.Serial('/dev/ttyUSB0', 9600)
# time.sleep(1) #give the connection a second to settle
# arduino.write("Hello from Python!")