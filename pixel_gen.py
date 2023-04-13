""" pixel_gen.py
"""
import cv2
import os

class Pixel_Factory:
    def __init__(self, filename):
        self.filename = filename

        self.img = cv2.imread(self.filename, cv2.IMREAD_COLOR)

        self.generate_resize(16,16)
        self.generate_resize(22,22)
        self.generate_resize(32,32)
        self.generate_resize(64,64)

    def generate_resize(self, x, y):
        scaled_img = cv2.resize(self.img, [x,y])

        out_path = f"./outputs/{x}-{y}/"
        out_name = f"{self.filename}.png"

        if not os.path.exists(out_path):
            os.mkdir(out_path)

        cv2.imwrite(out_path + out_name, scaled_img)
        cv2.imshow(out_name, scaled_img)


if __name__ == "__main__":
    pix = Pixel_Factory('noot-noot.png')