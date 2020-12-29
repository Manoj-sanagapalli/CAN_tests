#include "operations.h"

// Function for converting decimal to hexa decimal
std::string dec_hex(int decimal)
{
    // adding 256 to convert signed to unsigned
    if (decimal < 0)
        decimal = decimal + 256;
    int r;
    std::string hexdec_num = "0x";
    char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    while (decimal > 0) {
        r = decimal % 16;
        hexdec_num = hexdec_num + hex[r];
        decimal = decimal / 16;
    }
    return hexdec_num;
}

// Function for converting hexa decimal to decimal
float hex_dec(__u8 hexValue)
{
}

void translate(float vx, float vy, float vz, float ax, float ay, float az)
{
    factored_vx = vx * factor;
    factored_vy = vy * factor;
    factored_vz = vz * factor;
    factored_ax = ax * factor;
    factored_ay = ay * factor;
    factored_az = az * factor;
    vx_hex = dec_hex(factored_vx);
    vy_hex = dec_hex(factored_vy);
    vz_hex = dec_hex(factored_vz);
    ax_hex = dec_hex(factored_ax);
    ay_hex = dec_hex(factored_ay);
    az_hex = dec_hex(factored_az);
}
void sendTo_can()
{
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW); // domain,type,protocol
    struct sockaddr_can addr; // the socket address structure
    struct ifreq ifr; // interface name structure
    strcpy(ifr.ifr_name, "vcan0"); // vcan0 is the virtual can
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr*)&addr, sizeof(addr)); // binding the defined socket to the interface
    //frame 1 for linear velocities
    struct can_frame frame1;
    frame1.can_id = 0x20;
    frame1.can_dlc = 6;
    int d =102;
    frame1.data[0] = 0;
    frame1.data[1] = factored_vx,
    frame1.data[2] = 0;
    frame1.data[3] = factored_vy;
    frame1.data[4] = 0;
    frame1.data[5] = factored_vz;
    int write_bytes = write(s, &frame1, sizeof(struct can_frame));

    //frame2 for angular velocities
    struct can_frame frame2;
    frame2.can_id = 0x21;
    frame2.can_dlc = 6;
    frame2.data[0] = 0;
    frame2.data[1] = factored_ax,
    frame2.data[2] = 0;
    frame2.data[3] = factored_ay;
    frame2.data[4] = 0;
    frame2.data[5] = factored_az;
    int write_angular = write(s, &frame2, sizeof(struct can_frame));
}

void recieveFrom_can()
{
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW); // domain,type,protocol
    struct sockaddr_can addr; // the socket address structure
    struct ifreq ifr; // interface name structure
    strcpy(ifr.ifr_name, "vcan0"); // vcan0 is the virtual can
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr*)&addr, sizeof(addr));

    struct can_frame frame;
    int nbytes = read(s, &frame, sizeof(struct can_frame));
    std::cout << "can id = " << unsigned(frame.can_id) << "\n";
    float v_lin_x,v_lin_y,v_lin_z,v_ang_x,v_ang_y,v_ang_z;
    if (frame.can_id == 0x40) {
        int vx,vy,vz;
        vx=frame.data[1]; vy=frame.data[3]; vz= frame.data[5];
        v_lin_x= vx/factor; v_lin_y = vy/factor; v_lin_z= vz/factor;
        odom.twist.twist.linear.x = v_lin_x;
        odom.twist.twist.linear.y = v_lin_y;
        odom.twist.twist.linear.z = v_lin_z;
    }
    else if (frame.can_id == 0x41) {
        int ax,ay,az;
        ax=frame.data[1]; ay=frame.data[3]; az= frame.data[5];
        v_ang_x= ax/factor; v_ang_y = ay/factor; v_ang_z= az/factor;
        odom.twist.twist.angular.x = v_ang_x;
        odom.twist.twist.angular.y = v_ang_y;
        odom.twist.twist.angular.z = v_ang_z;
    }
}