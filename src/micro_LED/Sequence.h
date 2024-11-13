/**
 * Project      graduation-cap-leds
 * @file        micro_LED.ino
 * @author      Sean Duffie
 * @link        https://github.com/SeanDuffie/graduation-cap-leds
 * 
 * The purpose of this project is to create a 
 */

class Sequence {
    public:
        Sequence();
        Sequence(int dx, int dy);

        int getDelay();
        long* nextFrame();
        void insertFrame();

    private:
        // Width of the LED Matrix
        int dim_x;
        // Length of the LED Matrix
        int dim_y;
        // Number of frames in the Sequence
        int fcount;
        // Index of the current frame being displayed
        int cur;
        // Container for frames to be displayed
        // long frames[fcount][256];
        std::vector<std::vector<long>> frames;

        // Seconds per cycle or seconds per frame?
        // int bpm;
};

Sequence::Sequence() : dim_x(16), dim_y(16), fcount(0), cur(0) {
    frames = {};
}

Sequence::Sequence(int dx, int dy) : dim_x(dx), dim_y(dy), fcount(0), cur(0) {
    frames = {};
}

int Sequence::getDelay() {
    return 180;
}

long* Sequence::nextFrame() {
    return self.frames[self.cur++];
}

void Sequence::insertFrame() {

}