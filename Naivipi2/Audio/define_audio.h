#ifndef DEFINE_AUDIO_H
#define DEFINE_AUDIO_H

#endif // DEFINE_AUDIO_H
#pragma once
/*------------------------------joystick-----------------------------------------*/
#define		H_ENUM_HANGED_BUTTONSENSOR 0x04 //Nut dieu khien cam bien bi treo    TAY CAM
#define		H_ENUM_IMPEDIMENT 0x02 //Dam phai chuong ngai vat    TAY CAM
#define		H_ENUM_OUT_IMPACT 0x03 //Bi do xe do tac dong ben ngoai    TAY CAM
#define		H_ENUM_STAIR_SLIDE 0x01 //Truot cau thang    TAY CAM
#define		H_ENUM_HOLE 0x05 //Ho ga    TAY CAM

#define		M_ENUM_DOWNGRADE 0x03 //Xe xuong doc    TAY CAM
#define		M_ENUM_POTHOLE 0x04 //O ga    TAY CAM
#define		M_ENUM_USER_STROKE 0x02 //Nguoi su dung bi ngat, dot quy,...    TAY CAM
#define		M_ENUM_MCU_HANG 0x01 //Vi dieu khien bi treo    TAY CAM

#define		L_ENUM_DRAGED_SENSOR 0x03 //Cam bien bi troi    TAY CAM
#define		L_ENUM_SPIN_AROUND 0x02 //Xe quay tron do loi cam bien    TAY CAM
#define		L_ENUM_BUMPY_WAY 0x04 //Duong soc    TAY CAM

/*--------------------------------------Slave---------------------------------------*/
# define    H_SLAVE_CHECK_HALL 0x04 //Check_Hall    SLAVE
# define    H_SLAVE_RUN_MOTOR 0x02 //Run_Motor    SLAVE
# define    H_SLAVE_OVER_CURRENT 0x01 //Over_Current    SLAVE
# define    H_SLAVE_DIRECTION 0x03 //Direction    SLAVE

# define    M_SLAVE_HANGED_SENSOR 0x01 //Vi dieu khien bi treo    SLAVE
# define    M_SLAVE_OVER_TEMPERATURE 0x02 //Qua nhiet    SLAVE

# define    L_SLAVE_UNDERSTAND 0x01 //Understand    SLAVE

/*--------------------------------------Sensor--------------------------------------*/
# define    H_SENSORS_SPIN_AROUND 0x04   //Xe quay tron do loi cam bien    SENSORS
# define    H_SENSORS_IMPEDIMENT 0x02    //Dam phai chuong ngai vat    SENSORS
# define    H_SENSORS_OUT_IMPACT 0x03   //Bi do xe do tac dong ben ngoai    SENSORS
# define    H_SENSORS_STAIR_SLIDE 0x01  //Truot cau thang    SENSORS
# define    H_SENSORS_HOLE 0x05          //Ho ga    SENSORS
# define    H_SENSORS_ZICZAG 0x06        //Xe lang lach    SENSORS

# define    M_SENSORS_HANGED_MCU 0x02    //Vi dieu khien bi treo    SENSORS
# define    M_SENSORS_POTHOLE 0x01       //O ga    SENSORS
# define    M_SENSORS_DOWNGRADE 0x03     //Xe xuong doc    SENSORS
# define    M_SENSORS_MPU6050_ERROR 0x04 //Cam bien MPU6050 hong    SENSORS

# define    L_SENSORS_SENSOR_ERROR 0x02  //Cam bien khac hong    SENSORS
# define    L_SENSORS_OVER_SAFETEMP 0x03 //> nhiet do an toan    SENSORS
# define    L_SENSORS_HUMIDITY 0x04      //Do am?1:0    SENSORS
# define    L_SENSORS_PRESSURE 0x05      //Ap luc?1:0    SENSORS
# define    L_SENSORS_LIGHT 0x06         //Anh sang?1:0    SENSORS
# define    L_SENSORS_SUPERSONIC_L 0x07  //Sieu am _L?1:0    SENSORS
# define    L_SENSORS_SUPERSONIC_R 0x08  //Sieu am _R?1:0    SENSORS
# define    L_SENSORS_BUMPY_WAY 0x01     //Duong soc    SENSORS
