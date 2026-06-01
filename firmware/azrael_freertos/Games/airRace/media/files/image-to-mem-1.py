#!/usr/bin/env python

# vim: set ai et ts=4 sw=4:

from PIL import Image
import sys
import os

if len(sys.argv) < 2:
    print("Usage: {} <image-file> <var_name> <W/B bg>".format(sys.argv[0]))
    sys.exit(1)

fname = sys.argv[1]
var_name = sys.argv[2]
bg_type = sys.argv[3]

img = Image.open(fname)
if img.width >= 128 or img.height >= 160:
    print("Error: 128x128 image expected")
    sys.exit(2)

print("const uint16_t {}[][{}] = {{".format(var_name, img.width))
img = img.convert('RGBA')
for y in range(0, img.height):
    s = "{"
    for x in range(0, img.width):
        pixel = img.getpixel((x, y))
        if len(pixel) == 4:
            r, g, b, a = pixel
        else:
            r, g, b = pixel
            a = 255

        if a == 0:
            color565 = 0x0000 if (bg_type == 'black') else 0xFFFF
        else:
            color565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)
            # for right endiness, so ST7735_DrawImage would work
            color565 = ((color565 & 0xFF00) >> 8) | ((color565 & 0xFF) << 8)
        s += "0x{:04X},".format(color565)
    s += "},"
    print(s)

print("};")
