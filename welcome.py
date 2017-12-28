#!/usr/bin/env python

# This is a example of the usage of OLED 1.3'' 128x64 with I2C

# Import of the necessary libraries
import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
import Image
import ImageDraw
import ImageFont
import subprocess

# Raspberry Pi pin configuration:
RST = None  # May be modified later


# 128x32 display with hardware I2C:
# disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
 
# 128x64 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

# Alternatively you can specify an explicit I2C bus number, for example
# with the 128x32 display you would use:
# disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST, i2c_bus=2)


# Initialize library.
disp.begin()

# Clear display.
disp.clear()
disp.display()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new('1', (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
draw.rectangle((0,0,width,height), outline=0, fill=0)

# First define some constants to allow easy resizing of shapes.
padding = 2
shape_width = 20
top = padding
bottom = height-padding
# Move left to right keeping track of the current x position for drawing shapes.
x = padding

# Load default font.
font = ImageFont.load_default()
 
# Alternatively load a TTF font.
# Some other nice fonts to try: http://www.dafont.com/bitmap.php
#font = ImageFont.truetype('Minecraftia.ttf', 10)

# Get IP address
cmd = "hostname -I | cut -d\' \' -f1"
IP = subprocess.check_output(cmd, shell = True )

# Get disk usage
cmd = "df -h | awk '$NF==\"/\"{printf \"Disk: %d/%dGB %s\", $3,$2,$5}'"
Disk = subprocess.check_output(cmd, shell = True )

# Write text.
draw.text((x, top),    'WELCOME ABORD',  font=font, fill=255)
draw.text((x,top+10),'SMART IDEA!', font=font, fill=255)
draw.text((x, top+20), 'www.smart-idea.io', font=font, fill=255)
# Writw IP
draw.text((x, top+35),"IP: " + str(IP),  font=font, fill=255)
#Write disk usage
draw.text((x, top+45),    str(Disk),  font=font, fill=255)

# Display image.
disp.image(image)
disp.display()
