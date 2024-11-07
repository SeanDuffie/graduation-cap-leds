class Sequence {
    public:
        // Width of the LED Matrix
        int dim_x = 16;
        // Length of the LED Matrix
        int dim_y = 16;
        // Number of frames in the Sequence
        int fcount = 1;
        // Index of the current frame being displayed
        int cur = 0;
        //
        long frames[fcount][dim_x * dim_y];
        // Is it a 

        int getDelay();
        long* nextFrame();

        // Default Constructor
        Sequence()
};

Sequence::Sequence() {

}

int Sequence::getDelay() {
    if 
}

long* Sequence::nextFrame() {
    return self.frames[self.cur++];
}