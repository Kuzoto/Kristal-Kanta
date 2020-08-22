import sys
import time
import cs50
from PIL import Image, ImageFilter

before = Image.open("Eat pant.jpg")
after = before.filter(ImageFilter.BLUR)
after.save("out.jpg")