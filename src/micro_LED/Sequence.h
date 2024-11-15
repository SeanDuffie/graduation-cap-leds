/**
 * Project      graduation-cap-leds
 * @file        micro_LED.ino
 * @author      Sean Duffie
 * @link        https://github.com/SeanDuffie/graduation-cap-leds
 * 
 * The purpose of this project is to create a 
 */

#include <vector>

class Sequence {
    public:
        Sequence();
        Sequence(int dx, int dy);

        float getDelay();
        std::vector<long> nextFrame();
        std::vector<long> prevFrame();
        void insertBatch(std::vector<std::vector<long>> img_arr);
        void insertFrame(std::vector<long> new_frame);
        void removeFrame(int index);

    private:
        // Width of the LED Matrix
        int dim_x;
        // Length of the LED Matrix
        int dim_y;
        // Index of the current frame being displayed
        int cur;
        // Container for frames to be displayed
        // long frames[fcount][256];
        std::vector<std::vector<long>> frames;

        // Seconds per cycle or seconds per frame?
        // int bpm;
};

Sequence::Sequence() : dim_x(16), dim_y(16), cur(0) {
    frames = {};
}

Sequence::Sequence(int dx, int dy) : dim_x(dx), dim_y(dy), cur(0) {
    frames = {};
}

float Sequence::getDelay() {
    return 1/180;
}

std::vector<long> Sequence::nextFrame() {
    if (frames.size() == 0) {
        return;
    } if (cur >= frames.size()) {
        cur = 0;
    } else {
        cur++;
    }
    return frames[cur];
}

std::vector<long> Sequence::prevFrame() {
    if (frames.size() == 0) {
        return;
    } if (cur >= frames.size()) {
        cur = 0;
    } else {
        cur++;
    }
    return frames[cur];
}

void Sequence::insertBatch(std::vector<std::vector<long>> img_arr) {
    for (std::vector<long> img : img_arr) {
        insertFrame(img);
    }
}

void Sequence::insertFrame(std::vector<long> new_frame) {
    frames.insert(frames.end(), new_frame);
}

void Sequence::removeFrame(int index) {
    if (index < 0 || index >= frames.size()) {return;}
    frames.erase(frames.begin() + index);
}