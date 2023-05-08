""" pixel_gen.py
"""
import csv
import os
import sys
from tkinter import filedialog

import cv2

BATCH = True

class PixelFactory:
    """ Pixel factory is a Python script used to make images usable by arduino LEDs

    This program will allow the user to select a directory, which will then be parsed for images
    to convert. These images will be downscaled to various sizes of pixel arrays, then will be
    converted into hexadecimal pixel arrays, which can be copy/pasted into an arduino scripts
    easily.

    TODO: Figure out how to auto crop images to squares to prevent stretching
    """
    def __init__(self):
        # Image array is used to store the input images
        img_arr = []

        if BATCH:
            folder = filedialog.askdirectory()

            if folder == "":
                print("No directory selected")
                sys.exit(1)

            for file in os.listdir(folder):
                print(f"Appending: {folder}/{file}")
                img = cv2.imread(folder + "/" + file, cv2.IMREAD_COLOR)
                img_arr.append([file, img])
        else:
            file = filedialog.askopenfilename()
            img = cv2.imread(file, cv2.IMREAD_COLOR)
            img_arr.append([file, img])

        # Error Handling for cancelling file select
        if len(img) == 0:
            print("No file selected or directory")
            sys.exit(1)

        # Generate Resizes
        for img in img_arr:
            self.generate_resize(16,16,img)
            self.generate_resize(22,22,img)
            self.generate_resize(32,32,img)
            self.generate_resize(64,64,img)

    def generate_resize(self, x: int, y: int, img):
        """ Resizes the input image to the input dimensions, then produces a csv of hex colors

        Args:
            - x (int): output image width
            - y (int): output image height
            - img (np.array): Original imput array of pixels
        Returns:
            - None
        """
        scaled_img = cv2.resize(img[1], [x,y])

        out_path = f"./outputs/{x}-{y}/"
        out_name = f"{os.path.basename(img[0])}".split(".")[0]
        print(f"Resizing: {out_path}{out_name}")

        if not os.path.exists(out_path):
            os.mkdir(out_path)

        cv2.imwrite(out_path + out_name + ".png", scaled_img)

        # Generate Pixel CSV
        with open(out_path + out_name + ".csv", 'w', newline='', encoding="utf-8") as csvfile:
            csv.register_dialect("dil", delimiter=",", lineterminator=",\r\n")
            wrtr = csv.writer(csvfile, dialect="dil", delimiter=',')
            r, c, z = scaled_img.shape
            for i in range(r):
                current_row = []
                for j in range(c):
                    current_row.append(self.bgr_to_hex(scaled_img[i, j]))
                wrtr.writerow(current_row[:len(current_row)])

    def bgr_to_hex(self, pixel):
        """ Converts a single BGR pixel to a hexadecimal value

        Args:
            - pixel (np.array): Contains 3 elements for blue, green, and red values
        Returns:
            - hex_val (str): hexadecimal color from rgb values
        """

        # Extracts the colors from the pixel, change the order to switch from BGR to RGB
        r: int = pixel[2]
        g: int = pixel[1]
        b: int = pixel[0]

        hex_val: str = f'0x{r:02x}{g:02x}{b:02x}'

        return hex_val



if __name__ == "__main__":
    pix = PixelFactory()
