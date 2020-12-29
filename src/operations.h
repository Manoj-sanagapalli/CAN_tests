#include "linux/can.h"
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <sstream>
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
nav_msgs::Odometry odom;

unsigned char d3;
float linearvx, linearvy, linearvz, linear;
float V_lin_x, V_lin_y, V_lin_z, V_ang_x, V_ang_y, V_ang_z;
int factored_vx,factored_vy,factored_vz,factored_ax,factored_ay,factored_az;  
std::string vx_hex, vy_hex, vz_hex, ax_hex, ay_hex, az_hex;
int vz, ax, ay, az;
const int factor = 1024;
void sendTo_can();
void translate(float linearvx, float linearvy, float linearvz, float angularx, float angulary, float angularz);
std::string dec_hex(int value);
float hex_dec(__u8 hexValue);

void recieveFrom_can();
