
extern double current_velocity; // todo volatile

class Motor
{
    private:
        int enable, dir1, dir2, encoder_pin;

    public:
        Motor(int enable, int dir1, int dir2, int encoder_pin);
        void rotate(int pwm); // pwm is between -255 and 255
};