
class Motor
{
    private:
        int enable, dir1, dir2, encoder_pin;
        int* current_direction;

    public:
        Motor(int enable, int dir1, int dir2, int* current_direction);
        void rotate(int pwm); // pwm is between -255 and 255
};