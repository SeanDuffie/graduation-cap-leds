""" pixel_gen.py
"""
import cv2
import os
from tkinter import filedialog
import sys

BATCH = True

class Pixel_Factory:
    def __init__(self):
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

        if len(img) == 0:
            print("No file selected or directory")
            sys.exit(1)

        # self.filename = filedialog.askopenfilename()

        for img in img_arr:
            self.generate_resize(16,16,img)
            self.generate_resize(22,22,img)
            self.generate_resize(32,32,img)
            self.generate_resize(64,64,img)

    def generate_resize(self, x, y, img):
        scaled_img = cv2.resize(img[1], [x,y])

        out_path = f"./outputs/{x}-{y}/"
        out_name = f"{os.path.basename(img[0])}".split(".")[0]
        print(f"Resizing: {out_path}{out_name}")

        if not os.path.exists(out_path):
            os.mkdir(out_path)

        cv2.imwrite(out_path + out_name + ".png", scaled_img)
        cv2.imshow(out_name, scaled_img)


if __name__ == "__main__":
    pix = Pixel_Factory()