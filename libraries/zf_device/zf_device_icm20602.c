/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_icm20602
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             接线定义：
*                   ------------------------------------
*                   模块管脚                                        单片机管脚
*                   //------------------硬件 SPI 引脚------------------//
*                   SCL/SPC             查看 zf_device_icm20602.h 中 ICM20602_SPC_PIN 宏定义
*                   SDA/DSI             查看 zf_device_icm20602.h 中 ICM20602_SDI_PIN 宏定义
*                   SA0/SDO             查看 zf_device_icm20602.h 中 ICM20602_SDO_PIN 宏定义
*                   CS                  查看 zf_device_icm20602.h 中 IPS114_CS_PIN 宏定义
*                   //------------------硬件 SPI 引脚------------------//
*                   //------------------软件 IIC 引脚------------------//
*                   SCL/SPC             查看 zf_device_icm20602.h 中 ICM20602_SCL_PIN 宏定义
*                   SDA/DSI             查看 zf_device_icm20602.h 中 ICM20602_SDA_PIN 宏定义
*                   //------------------软件 IIC 引脚------------------//
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_icm20602.h"
#include "math.h"

int16_t icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16_t icm_acc_x,icm_acc_y,icm_acc_z;

#if ICM20602_USE_SOFT_IIC
static soft_iic_info_struct icm20602_iic_struct;

#define icm20602_write_register(reg,data)       soft_iic_write_8bit_register(&icm20602_iic_struct,reg,data)
#define icm20602_read_register(reg)             soft_iic_read_8bit_register(&icm20602_iic_struct,reg)
#define icm20602_read_registers(reg,data,len)   soft_iic_read_8bit_registers(&icm20602_iic_struct,reg,data,len)
#else
static void icm20602_write_register(uint8_t reg, uint8_t dat)
{
    ICM20602_CS(0);
    spi_write_8bit_register(ICM20602_SPI, reg, dat);
    ICM20602_CS(1);
}

static uint8_t icm20602_read_register(uint8_t reg)
{
    uint8_t dat;
    ICM20602_CS(0);
    dat = spi_read_8bit_register(ICM20602_SPI, reg|ICM20602_SPI_R);
    ICM20602_CS(1);
    return dat;
}

static void icm20602_read_registers(uint8_t reg, uint8_t *dat, uint8_t len)
{
    ICM20602_CS(0);
    spi_read_8bit_registers(ICM20602_SPI, reg|ICM20602_SPI_R, dat, len);
    ICM20602_CS(1);
}
#endif


//-------------------------------------------------------------------------------------------------------------------
// @brief       ICM20602 自检 内部调用
// @param       void
// @return      uint8_t         1-自检失败 0-自检成功
//-------------------------------------------------------------------------------------------------------------------
static uint8_t icm20602_self_check(void)
{
    uint8_t dat = 0;
    volatile int16_t timeout_count = ICM20602_TIMEOUT_COUNT;

    while(0x12 != dat && timeout_count)                                         // 判断 ID 是否正确
    {
        timeout_count--;
        dat = icm20602_read_register(ICM20602_WHO_AM_I);

        system_delay_ms(10);
    }
    if(timeout_count < 0)
        return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       初始化 ICM20602
// @param       void
// @return      uint8_t         1-初始化失败 0-初始化成功
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8_t icm20602_init (void)
{
    uint8_t val = 0x0;
    volatile int16_t timeout_count = ICM20602_TIMEOUT_COUNT;

    system_delay_ms(10);  //上电延时

#if ICM20602_USE_SOFT_IIC
    soft_iic_init(&icm20602_iic_struct, ICM20602_DEV_ADDR, ICM20602_SOFT_IIC_DELAY, ICM20602_SCL_PIN, ICM20602_SDA_PIN);
#else
    spi_init(ICM20602_SPI, SPI_MODE0, ICM20602_SPI_SPEED, ICM20602_SPC_PIN, ICM20602_SDI_PIN, ICM20602_SDO_PIN, ICM20602_CS_PIN);
#endif


    if(icm20602_self_check())
    {
        zf_log(0, "ICM20602 self check error.");
        return 1;
    }

    icm20602_write_register(ICM20602_PWR_MGMT_1, 0x80);                          //复位设备
    system_delay_ms(2);


    do                                                                          // 等待复位成功
    {
        val = icm20602_read_register(ICM20602_PWR_MGMT_1);

        system_delay_ms(10);
    }while(0x41 != val && timeout_count--);
    if(timeout_count < 0)
    {
        zf_log(0, "ICM20602 restart error.");
        return 1;
    }

    icm20602_write_register(ICM20602_PWR_MGMT_1,     0x01);                     // 时钟设置
    icm20602_write_register(ICM20602_PWR_MGMT_2,     0x00);                     // 开启陀螺仪和加速度计
    icm20602_write_register(ICM20602_CONFIG,         0x01);                     // 176HZ 1KHZ
    icm20602_write_register(ICM20602_SMPLRT_DIV,     0x07);                     // 采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm20602_write_register(ICM20602_GYRO_CONFIG,    0x18);                     // ±2000 dps
    icm20602_write_register(ICM20602_ACCEL_CONFIG,   0x10);                     // ±8g
    icm20602_write_register(ICM20602_ACCEL_CONFIG_2, 0x03);                     // Average 4 samples   44.8HZ   //0x23 Average 16 samples
    system_delay_ms(100);
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       获取 ICM20602 加速度计数据
// @param       void
// @return      void
// Sample usage:                执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void icm20602_get_acc (void)
{
    uint8_t reg = ICM20602_ACCEL_XOUT_H;
    uint8_t dat[6];

    icm20602_read_registers(reg, dat, 6);
    icm_acc_x = (int16_t)(((uint16_t)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16_t)(((uint16_t)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16_t)(((uint16_t)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       获取ICM20602陀螺仪数据
// @param       void
// @return      void
// Sample usage:                执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void icm20602_get_gyro (void)
{
    uint8_t reg = ICM20602_GYRO_XOUT_H;
    uint8_t dat[6];

    icm20602_read_registers(reg, dat, 6);
    icm_gyro_x = (int16_t)(((uint16_t)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16_t)(((uint16_t)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16_t)(((uint16_t)dat[4]<<8 | dat[5]));
}


//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用软件SPI通信，相比较硬件SPI，软件SPI引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      通过SPI写一个byte,同时读取一个byte
//  @param      byte        发送的数据
//  @return     uint8_t       return 返回status状态
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8_t icm_simspi_wr_byte(uint8_t byte)
{
    uint8_t i;

    for(i=0; i<8; i++)
    {
        ICM20602_MOSI(byte&0x80);
        byte <<= 1;
        ICM20602_SCK (0);

        ICM20602_SCK (1);
        byte |= ICM20602_MISO;
    }
    return(byte);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将val写入cmd对应的寄存器地址,同时返回status字节
//  @param      cmd         命令字
//  @param      val         待写入寄存器的数值
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_w_reg_byte(uint8_t cmd, uint8_t val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_W;
    icm_simspi_wr_byte(cmd);
    icm_simspi_wr_byte(val);
    ICM20602_CSN (1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_byte(uint8_t cmd, uint8_t *val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);
    *val = icm_simspi_wr_byte(0);
    ICM20602_CSN (1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @param      num         读取的数量
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_bytes(uint8_t cmd, uint8_t *val, uint8_t num)
{
    uint16_t i;
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);

    for(i=0; i<num; i++)
        val[i] = icm_simspi_wr_byte(0);


    ICM20602_CSN (1);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self4_check(void)
{
    uint8_t val;
    do
    {
        icm_simspi_r_reg_byte(ICM20602_WHO_AM_I,&val);

        //卡在这里原因有以下几点
        //1 ICM20602坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
    }while(0x12 != val);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      软件SPI，初始化ICM20602
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_simspi(void)
{
    uint8_t val;

    gpio_init(ICM20602_SCK_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(ICM20602_MOSI_PIN, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(ICM20602_MISO_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(ICM20602_CSN_PIN, GPO, 1, GPIO_PIN_CONFIG);
    icm20602_self4_check();//检测

    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//复位设备
    system_delay_ms(2);
    do
    {//等待复位成功
        icm_simspi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
    }while(0x41 != val);

    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,     0x01);            //时钟设置
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_2,     0x00);            //开启陀螺仪和加速度计
    icm_simspi_w_reg_byte(ICM20602_CONFIG,         0x01);            //176HZ 1KHZ
    icm_simspi_w_reg_byte(ICM20602_SMPLRT_DIV,     0x07);            //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_simspi_w_reg_byte(ICM20602_GYRO_CONFIG,    0x18);            //±2000 dps
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG,   0x10);            //±8g
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x03);            //Average 8 samples   44.8HZ

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:               执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_simspi(void)
{
    uint8_t dat[6];


    icm_simspi_r_reg_bytes(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm_acc_x = (int16_t)(((uint16_t)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16_t)(((uint16_t)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16_t)(((uint16_t)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:               执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_simspi(void)
{
    uint8_t dat[6];

    icm_simspi_r_reg_bytes(ICM20602_GYRO_XOUT_H, dat, 6);

    icm_gyro_x = (int16_t)(((uint16_t)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16_t)(((uint16_t)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16_t)(((uint16_t)dat[4]<<8 | dat[5]));
}

/********************************************************
 *角度解算，ht 2022.4.10
 *
 *
 *
 *
 */
/*******************************************************************************
* 函  数 ：float FindPos(float*a,int low,int high)
* 功  能 ：确定一个元素位序
* 参  数 ：a  数组首地址
*          low数组最小下标
*          high数组最大下标
* 返回值 ：返回元素的位序low
* 备  注 : 无
*******************************************************************************/
float FindPos(float*a,int low,int high)
{
    float val = a[low];                      //选定一个要确定值val确定位置
    while(low<high)
    {
        while(low<high && a[high]>=val)
             high--;                       //如果右边的数大于VAL下标往前移
             a[low] = a[high];             //当右边的值小于VAL则复值给A[low]

        while(low<high && a[low]<=val)
             low++;                        //如果左边的数小于VAL下标往后移
             a[high] = a[low];             //当左边的值大于VAL则复值给右边a[high]
    }
    a[low] = val;
    return low;
}
/*******************************************************************************
* 函  数 ：void QuiteSort(float* a,int low,int high)
* 功  能 ：快速排序
* 参  数 ：a  数组首地址
*          low数组最小下标
*          high数组最大下标
* 返回值 ：无
* 备  注 : 无
*******************************************************************************/
 void QuiteSort(float* a,int low,int high)
 {
     int pos;
     if(low<high)
     {
         pos = FindPos(a,low,high); //排序一个位置
         QuiteSort(a,low,pos-1);    //递归调用
         QuiteSort(a,pos+1,high);
     }
 }
/********************************************************************************
* 函  数 ：void  SortAver_FilterXYZ(INT16_XYZ *acc,FLOAT_XYZ *Acc_filt,uint8_t n)
* 功  能 ：去最值平均值滤波三组数据
* 参  数 ：*acc 要滤波数据地址
*          *Acc_filt 滤波后数据地址
* 返回值 ：无
* 备  注 : 无
********************************************************************************/
#define N 20      //滤波缓存数组大小

FLOAT_XYZ accfilt;
void  SortAver_FilterXYZ(short *acc_x,short *acc_y,short *acc_z,FLOAT_XYZ *Acc_filt,uint8_t n)
{
    static float bufx[N],bufy[N],bufz[N];
    static uint8_t cnt =0,flag = 1;
    float temp1=0,temp2=0,temp3=0;
    uint8_t i;
    bufx[cnt] = *acc_x;
    bufy[cnt] = *acc_y;
    bufz[cnt] = *acc_z;
    cnt++;      //这个的位置必须在赋值语句后，否则bufx[0]不会被赋值
    if(cnt<n && flag)
        return;   //数组填不满不计算
    else
        flag = 0;

    QuiteSort(bufx,0,n-1);
    QuiteSort(bufy,0,n-1);
    QuiteSort(bufz,0,n-1);
    for(i=1;i<n-1;i++)
     {
        temp1 += bufx[i];
        temp2 += bufy[i];
        temp3 += bufz[i];
     }

     if(cnt>=n) cnt = 0;
     Acc_filt->X  = temp1/(n-2);
     Acc_filt->Y  = temp2/(n-2);
     Acc_filt->Z  = temp3/(n-2);
}

/*******************************************************
*函数：void MPU6050_datainit(void)
*功能：获得陀螺仪初始零偏
************************************************************/
float gyro_x_init,gyro_y_init,gyro_z_init;

void MPU6050_datainit(void)
{
    int i,num=0;
    int gx=0,gy=0,gz=0;
    for(i = 100;i>0;i--)
    {
        get_icm20602_gyro_simspi();

        if(icm_gyro_z != 0 && icm_gyro_y != 0 && icm_gyro_x != 0)
        {
            num++;
            gx+=icm_gyro_x;
            gy+=icm_gyro_y;
            gz+=icm_gyro_z;
        }
        system_delay_ms(6);

        if(gz>30000000 || gz<-30000000)
            break;
    }
    gyro_x_init = gx/num;
    gyro_y_init = gy/num;
    gyro_z_init = (float)gz/num;
}
/*********************************************************************************************************
* 函  数：void Prepare_Data(void)
* 功　能：对陀螺仪去零偏后的数据滤波及赋予物理意义，为姿态解算做准备
* 参  数：无
* 返回值：无
**********************************************************************************************************/
#define G           9.80665f                // m/s^2
#define RadtoDeg    57.324841f              //弧度到角度 (弧度 * 180/3.1415)
#define DegtoRad    0.0174533f              //角度到弧度 (角度 * 3.1415/180)
FLOAT_XYZ   Acc_filt,Gry_filt,Acc_filtold;    //滤波后的各通道数据
FLOAT_XYZ    Gyr_degree,Gyr_rad;                  //把陀螺仪的各通道读出的数据，转换成弧度制 和 度
uint8_t AccbUpdate = 0;
float   accb[3],DCMgb[3][3];                  //方向余弦阵（将 惯性坐标系 转化为 机体坐标系）

void Prepare_Data(void)
{
    static uint8_t IIR_mode = 1;

//  MPU6050_Read();    //触发读取 ，立即返回
//            MPU_Get_Accelerometer(&acc_x,&acc_y,&acc_z);
//            MPU_Get_Gyroscope(&gyro_x,&gyro_y,&gyro_z);
    //MPU6050_Offset();  //对MPU6050进行处理，减去零偏。如果没有计算零偏就计算零偏

    get_icm20602_gyro_simspi();
    get_icm20602_accdata_simspi();


//  Aver_FilterXYZ(&MPU6050_ACC_RAW,&Acc_filt,12);//对加速度原始数据进行滑动窗口滤波
    SortAver_FilterXYZ(&icm_acc_x,&icm_acc_y,&icm_acc_z,&Acc_filt,12);//对加速度原始数据进行去极值滑动窗口滤波

    //加速度AD值 转换成 米/平方秒
    Acc_filt.X = (float)Acc_filt.X * Acc_Gain * G;
    Acc_filt.Y = (float)Acc_filt.Y * Acc_Gain * G;
    Acc_filt.Z = (float)Acc_filt.Z * Acc_Gain * G;
//  printf("ax=%0.2f ay=%0.2f az=%0.2f\r\n",Acc_filt.X,Acc_filt.Y,Acc_filt.Z);

    //陀螺仪AD值 转换成 弧度/秒
    Gyr_rad.X = (float) (icm_gyro_x - gyro_x_init) * Gyro_Gr;
    Gyr_rad.Y = (float) (icm_gyro_y - gyro_y_init) * Gyro_Gr;
    Gyr_rad.Z = (float) (icm_gyro_z - gyro_z_init) * Gyro_Gr;
//    Gyr_rad.X = (float) (icm_gyro_x) * Gyro_Gr;
//    Gyr_rad.Y = (float) (icm_gyro_y) * Gyro_Gr;
//    Gyr_rad.Z = (float) (icm_gyro_z) * Gyro_Gr;

    if(IIR_mode)
    {
        Acc_filt.X = Acc_filt.X * Kp_New + Acc_filtold.X * Kp_Old;
        Acc_filt.Y = Acc_filt.Y * Kp_New + Acc_filtold.Y * Kp_Old;
        Acc_filt.Z = Acc_filt.Z * Kp_New + Acc_filtold.Z * Kp_Old;
//      Gyr_rad.X = Gyr_rad.X * Kp_New + Gyr_radold.X * Kp_Old;
//      Gyr_rad.Y = Gyr_rad.Y * Kp_New + Gyr_radold.Y * Kp_Old;
//      Gyr_rad.Z = Gyr_rad.Z * Kp_New + Gyr_radold.Z * Kp_Old;

        Acc_filtold.X =  Acc_filt.X;
        Acc_filtold.Y =  Acc_filt.Y;
        Acc_filtold.Z =  Acc_filt.Z;
//      Gyr_radold.X = Gyr_rad.X;
//      Gyr_radold.Y = Gyr_rad.Y;
//      Gyr_radold.Z = Gyr_rad.Z;
    }
    accb[0] = Acc_filt.X;
    accb[1] = Acc_filt.Y;
    accb[2] = Acc_filt.Z;

    if(accb[0]&&accb[1]&&accb[2])
    {
        AccbUpdate = 1;
    }
}


/****************************************************************************************************
* 函  数：static float invSqrt(float x)
* 功　能: 快速计算 1/Sqrt(x)
* 参  数：要计算的值
* 返回值：计算的结果
* 备  注：比普通Sqrt()函数要快四倍See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
*****************************************************************************************************/
static float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f375a86 - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/*********************************************************************************************************
* 函  数：void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
* 功　能：获取姿态角
* 参  数：Gyr_rad  指向角速度的指针（注意单位必须是弧度）
*         Acc_filt  指向加速度的指针
*         Att_Angle 指向姿态角的指针
* 返回值：无
* 备  注：求解四元数和欧拉角都在此函数中完成
**********************************************************************************************************/
//kp=ki=0 就是完全相信陀螺仪
#define Kp 1.50f                         // proportional gain governs rate of convergence to accelerometer/magnetometer
                                         //比例增益控制加速度计，磁力计的收敛速率
#define Ki 0.005f                        // integral gain governs rate of convergence of gyroscope biases
                                         //积分增益控制陀螺偏差的收敛速度
#define halfT 0.005f                     // half the sample period 采样周期的一半

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error
#define RadtoDeg    57.324841f              //弧度到角度 (弧度 * 180/3.1415)
#define DegtoRad    0.0174533f              //角度到弧度 (角度 * 3.1415/180)
FLOAT_ANGLE ATT_Angle;

void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
{
    uint8_t i;
    float matrix[9] = {1.f,  0.0f,  0.0f, 0.0f,  1.f,  0.0f, 0.0f,  0.0f,  1.f };//初始化矩阵
    float ax = Acc_filt->X,ay = Acc_filt->Y,az = Acc_filt->Z;
    float gx = Gyr_rad->X,gy = Gyr_rad->Y,gz = Gyr_rad->Z;
    float vx, vy, vz;
    float ex, ey, ez;
    float norm;

    float q0q0 = q0*q0;
    float q0q1 = q0*q1;
    float q0q2 = q0*q2;
    float q0q3 = q0*q3;
    float q1q1 = q1*q1;
    float q1q2 = q1*q2;
    float q1q3 = q1*q3;
    float q2q2 = q2*q2;
    float q2q3 = q2*q3;
    float q3q3 = q3*q3;

    if(ax*ay*az==0)
    return;

    //加速度计测量的重力向量(机体坐标系)
    norm = invSqrt(ax*ax + ay*ay + az*az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;
    //  printf("ax=%0.2f ay=%0.2f az=%0.2f\r\n",ax,ay,az);

    //陀螺仪积分估计重力向量(机体坐标系)
    vx = 2*(q1q3 - q0q2);
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;
    // printf("vx=%0.2f vy=%0.2f vz=%0.2f\r\n",vx,vy,vz);

    //测量的重力向量与估算的重力向量差积求出向量间的误差
    ex = (ay*vz - az*vy); //+ (my*wz - mz*wy);
    ey = (az*vx - ax*vz); //+ (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx); //+ (mx*wy - my*wx);

    //用上面求出误差进行积分
    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

    //将误差PI后补偿到陀螺仪
    gx = gx + Kp*ex + exInt;
    gy = gy + Kp*ey + eyInt;
    gz = gz + Kp*ez + ezInt;//这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减

    //四元素的微分方程
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

    //单位化四元数
    norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;

    //矩阵R 将惯性坐标系(n)转换到机体坐标系(b)
    matrix[0] = q0q0 + q1q1 - q2q2 - q3q3;  // 11(前列后行)
    matrix[1] = 2.f * (q1q2 + q0q3);        // 12
    matrix[2] = 2.f * (q1q3 - q0q2);        // 13
    matrix[3] = 2.f * (q1q2 - q0q3);        // 21
    matrix[4] = q0q0 - q1q1 + q2q2 - q3q3;  // 22
    matrix[5] = 2.f * (q2q3 + q0q1);        // 23
    matrix[6] = 2.f * (q1q3 + q0q2);        // 31
    matrix[7] = 2.f * (q2q3 - q0q1);        // 32
    matrix[8] = q0q0 - q1q1 - q2q2 + q3q3;  // 33

    //四元数转换成欧拉角(Z->Y->X)
    Att_Angle->yaw += Gyr_rad->Z *RadtoDeg*0.01f;
//    Att_Angle->yaw = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)* 57.3f; // yaw
    Att_Angle->rol = -asin(2.f * (q1q3 - q0q2))* 57.3f;                            // roll(负号要注意)
    Att_Angle->pit = -atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3)* 57.3f ; // pitch
    for(i=0;i<9;i++)
    {
        *(&(DCMgb[0][0])+i) = matrix[i];
    }

    //失控保护 (调试时可注释掉)
//  Safety_Check();
}
