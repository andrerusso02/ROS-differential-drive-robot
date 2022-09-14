
namespace ENCODERS_global_vars
{
    extern int current_direction_left_motor;
    extern int current_direction_right_motor;
    extern double current_velocity_left;
    extern double current_velocity_right;
    extern double current_position_left;
    extern double current_position_right;
}

void ENCODERS_update_current_velocity_measures();
void ENCODERS_init_callbacks(int pinL, int pinR);