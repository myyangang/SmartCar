/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_device_icm20602
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�                                        ��Ƭ���ܽ�
*                   //------------------Ӳ�� SPI ����------------------//
*                   SCL/SPC             �鿴 zf_device_icm20602.h �� ICM20602_SPC_PIN �궨��
*                   SDA/DSI             �鿴 zf_device_icm20602.h �� ICM20602_SDI_PIN �궨��
*                   SA0/SDO             �鿴 zf_device_icm20602.h �� ICM20602_SDO_PIN �궨��
*                   CS                  �鿴 zf_device_icm20602.h �� IPS114_CS_PIN �궨��
*                   //------------------Ӳ�� SPI ����------------------//
*                   //------------------��� IIC ����------------------//
*                   SCL/SPC             �鿴 zf_device_icm20602.h �� ICM20602_SCL_PIN �궨��
*                   SDA/DSI             �鿴 zf_device_icm20602.h �� ICM20602_SDA_PIN �궨��
*                   //------------------��� IIC ����------------------//
*                   ��Դ����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
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
// @brief       ICM20602 �Լ� �ڲ�����
// @param       void
// @return      uint8_t         1-�Լ�ʧ�� 0-�Լ�ɹ�
//-------------------------------------------------------------------------------------------------------------------
static uint8_t icm20602_self_check(void)
{
    uint8_t dat = 0;
    volatile int16_t timeout_count = ICM20602_TIMEOUT_COUNT;

    while(0x12 != dat && timeout_count)                                         // �ж� ID �Ƿ���ȷ
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
// @brief       ��ʼ�� ICM20602
// @param       void
// @return      uint8_t         1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8_t icm20602_init (void)
{
    uint8_t val = 0x0;
    volatile int16_t timeout_count = ICM20602_TIMEOUT_COUNT;

    system_delay_ms(10);  //�ϵ���ʱ

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

    icm20602_write_register(ICM20602_PWR_MGMT_1, 0x80);                          //��λ�豸
    system_delay_ms(2);


    do                                                                          // �ȴ���λ�ɹ�
    {
        val = icm20602_read_register(ICM20602_PWR_MGMT_1);

        system_delay_ms(10);
    }while(0x41 != val && timeout_count--);
    if(timeout_count < 0)
    {
        zf_log(0, "ICM20602 restart error.");
        return 1;
    }

    icm20602_write_register(ICM20602_PWR_MGMT_1,     0x01);                     // ʱ������
    icm20602_write_register(ICM20602_PWR_MGMT_2,     0x00);                     // ���������Ǻͼ��ٶȼ�
    icm20602_write_register(ICM20602_CONFIG,         0x01);                     // 176HZ 1KHZ
    icm20602_write_register(ICM20602_SMPLRT_DIV,     0x07);                     // �������� SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm20602_write_register(ICM20602_GYRO_CONFIG,    0x18);                     // ��2000 dps
    icm20602_write_register(ICM20602_ACCEL_CONFIG,   0x10);                     // ��8g
    icm20602_write_register(ICM20602_ACCEL_CONFIG_2, 0x03);                     // Average 4 samples   44.8HZ   //0x23 Average 16 samples
    system_delay_ms(100);
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       ��ȡ ICM20602 ���ٶȼ�����
// @param       void
// @return      void
// Sample usage:                ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
// @brief       ��ȡICM20602����������
// @param       void
// @return      void
// Sample usage:                ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
//  ���º�����ʹ�����SPIͨ�ţ���Ƚ�Ӳ��SPI�����SPI���Ÿ���������ʹ��������ͨIO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ͨ��SPIдһ��byte,ͬʱ��ȡһ��byte
//  @param      byte        ���͵�����
//  @return     uint8_t       return ����status״̬
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
//  @brief      ��valд��cmd��Ӧ�ļĴ�����ַ,ͬʱ����status�ֽ�
//  @param      cmd         ������
//  @param      val         ��д��Ĵ�������ֵ
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
//  @brief      ��ȡcmd����Ӧ�ļĴ�����ַ
//  @param      cmd         ������
//  @param      *val        �洢��ȡ�����ݵ�ַ
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
//  @brief      ��ȡcmd����Ӧ�ļĴ�����ַ
//  @param      cmd         ������
//  @param      *val        �洢��ȡ�����ݵ�ַ
//  @param      num         ��ȡ������
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
//  @brief      ICM20602�Լ캯��
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

        //��������ԭ�������¼���
        //1 ICM20602���ˣ�������µ������ĸ��ʼ���
        //2 ���ߴ������û�нӺ�
        //3 ��������Ҫ����������裬������3.3V
    }while(0x12 != val);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���SPI����ʼ��ICM20602
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
    icm20602_self4_check();//���

    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//��λ�豸
    system_delay_ms(2);
    do
    {//�ȴ���λ�ɹ�
        icm_simspi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
    }while(0x41 != val);

    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,     0x01);            //ʱ������
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_2,     0x00);            //���������Ǻͼ��ٶȼ�
    icm_simspi_w_reg_byte(ICM20602_CONFIG,         0x01);            //176HZ 1KHZ
    icm_simspi_w_reg_byte(ICM20602_SMPLRT_DIV,     0x07);            //�������� SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_simspi_w_reg_byte(ICM20602_GYRO_CONFIG,    0x18);            //��2000 dps
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG,   0x10);            //��8g
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x03);            //Average 8 samples   44.8HZ

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡICM20602���ٶȼ�����
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:               ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
//  @brief      ��ȡICM20602����������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:               ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
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
 *�ǶȽ��㣬ht 2022.4.10
 *
 *
 *
 *
 */
/*******************************************************************************
* ��  �� ��float FindPos(float*a,int low,int high)
* ��  �� ��ȷ��һ��Ԫ��λ��
* ��  �� ��a  �����׵�ַ
*          low������С�±�
*          high��������±�
* ����ֵ ������Ԫ�ص�λ��low
* ��  ע : ��
*******************************************************************************/
float FindPos(float*a,int low,int high)
{
    float val = a[low];                      //ѡ��һ��Ҫȷ��ֵvalȷ��λ��
    while(low<high)
    {
        while(low<high && a[high]>=val)
             high--;                       //����ұߵ�������VAL�±���ǰ��
             a[low] = a[high];             //���ұߵ�ֵС��VAL��ֵ��A[low]

        while(low<high && a[low]<=val)
             low++;                        //�����ߵ���С��VAL�±�������
             a[high] = a[low];             //����ߵ�ֵ����VAL��ֵ���ұ�a[high]
    }
    a[low] = val;
    return low;
}
/*******************************************************************************
* ��  �� ��void QuiteSort(float* a,int low,int high)
* ��  �� ����������
* ��  �� ��a  �����׵�ַ
*          low������С�±�
*          high��������±�
* ����ֵ ����
* ��  ע : ��
*******************************************************************************/
 void QuiteSort(float* a,int low,int high)
 {
     int pos;
     if(low<high)
     {
         pos = FindPos(a,low,high); //����һ��λ��
         QuiteSort(a,low,pos-1);    //�ݹ����
         QuiteSort(a,pos+1,high);
     }
 }
/********************************************************************************
* ��  �� ��void  SortAver_FilterXYZ(INT16_XYZ *acc,FLOAT_XYZ *Acc_filt,uint8_t n)
* ��  �� ��ȥ��ֵƽ��ֵ�˲���������
* ��  �� ��*acc Ҫ�˲����ݵ�ַ
*          *Acc_filt �˲������ݵ�ַ
* ����ֵ ����
* ��  ע : ��
********************************************************************************/
#define N 20      //�˲����������С

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
    cnt++;      //�����λ�ñ����ڸ�ֵ���󣬷���bufx[0]���ᱻ��ֵ
    if(cnt<n && flag)
        return;   //�������������
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
*������void MPU6050_datainit(void)
*���ܣ���������ǳ�ʼ��ƫ
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
* ��  ����void Prepare_Data(void)
* �����ܣ���������ȥ��ƫ��������˲��������������壬Ϊ��̬������׼��
* ��  ������
* ����ֵ����
**********************************************************************************************************/
#define G           9.80665f                // m/s^2
#define RadtoDeg    57.324841f              //���ȵ��Ƕ� (���� * 180/3.1415)
#define DegtoRad    0.0174533f              //�Ƕȵ����� (�Ƕ� * 3.1415/180)
FLOAT_XYZ   Acc_filt,Gry_filt,Acc_filtold;    //�˲���ĸ�ͨ������
FLOAT_XYZ    Gyr_degree,Gyr_rad;                  //�������ǵĸ�ͨ�����������ݣ�ת���ɻ����� �� ��
uint8_t AccbUpdate = 0;
float   accb[3],DCMgb[3][3];                  //���������󣨽� ��������ϵ ת��Ϊ ��������ϵ��

void Prepare_Data(void)
{
    static uint8_t IIR_mode = 1;

//  MPU6050_Read();    //������ȡ ����������
//            MPU_Get_Accelerometer(&acc_x,&acc_y,&acc_z);
//            MPU_Get_Gyroscope(&gyro_x,&gyro_y,&gyro_z);
    //MPU6050_Offset();  //��MPU6050���д�����ȥ��ƫ�����û�м�����ƫ�ͼ�����ƫ

    get_icm20602_gyro_simspi();
    get_icm20602_accdata_simspi();


//  Aver_FilterXYZ(&MPU6050_ACC_RAW,&Acc_filt,12);//�Լ��ٶ�ԭʼ���ݽ��л��������˲�
    SortAver_FilterXYZ(&icm_acc_x,&icm_acc_y,&icm_acc_z,&Acc_filt,12);//�Լ��ٶ�ԭʼ���ݽ���ȥ��ֵ���������˲�

    //���ٶ�ADֵ ת���� ��/ƽ����
    Acc_filt.X = (float)Acc_filt.X * Acc_Gain * G;
    Acc_filt.Y = (float)Acc_filt.Y * Acc_Gain * G;
    Acc_filt.Z = (float)Acc_filt.Z * Acc_Gain * G;
//  printf("ax=%0.2f ay=%0.2f az=%0.2f\r\n",Acc_filt.X,Acc_filt.Y,Acc_filt.Z);

    //������ADֵ ת���� ����/��
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
* ��  ����static float invSqrt(float x)
* ������: ���ټ��� 1/Sqrt(x)
* ��  ����Ҫ�����ֵ
* ����ֵ������Ľ��
* ��  ע������ͨSqrt()����Ҫ���ı�See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
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
* ��  ����void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
* �����ܣ���ȡ��̬��
* ��  ����Gyr_rad  ָ����ٶȵ�ָ�루ע�ⵥλ�����ǻ��ȣ�
*         Acc_filt  ָ����ٶȵ�ָ��
*         Att_Angle ָ����̬�ǵ�ָ��
* ����ֵ����
* ��  ע�������Ԫ����ŷ���Ƕ��ڴ˺��������
**********************************************************************************************************/
//kp=ki=0 ������ȫ����������
#define Kp 1.50f                         // proportional gain governs rate of convergence to accelerometer/magnetometer
                                         //����������Ƽ��ٶȼƣ������Ƶ���������
#define Ki 0.005f                        // integral gain governs rate of convergence of gyroscope biases
                                         //���������������ƫ��������ٶ�
#define halfT 0.005f                     // half the sample period �������ڵ�һ��

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;    // scaled integral error
#define RadtoDeg    57.324841f              //���ȵ��Ƕ� (���� * 180/3.1415)
#define DegtoRad    0.0174533f              //�Ƕȵ����� (�Ƕ� * 3.1415/180)
FLOAT_ANGLE ATT_Angle;

void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
{
    uint8_t i;
    float matrix[9] = {1.f,  0.0f,  0.0f, 0.0f,  1.f,  0.0f, 0.0f,  0.0f,  1.f };//��ʼ������
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

    //���ٶȼƲ�������������(��������ϵ)
    norm = invSqrt(ax*ax + ay*ay + az*az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;
    //  printf("ax=%0.2f ay=%0.2f az=%0.2f\r\n",ax,ay,az);

    //�����ǻ��ֹ�����������(��������ϵ)
    vx = 2*(q1q3 - q0q2);
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;
    // printf("vx=%0.2f vy=%0.2f vz=%0.2f\r\n",vx,vy,vz);

    //��������������������������������������������
    ex = (ay*vz - az*vy); //+ (my*wz - mz*wy);
    ey = (az*vx - ax*vz); //+ (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx); //+ (mx*wy - my*wx);

    //��������������л���
    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

    //�����PI�󲹳���������
    gx = gx + Kp*ex + exInt;
    gy = gy + Kp*ey + eyInt;
    gz = gz + Kp*ez + ezInt;//�����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�

    //��Ԫ�ص�΢�ַ���
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

    //��λ����Ԫ��
    norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;

    //����R ����������ϵ(n)ת������������ϵ(b)
    matrix[0] = q0q0 + q1q1 - q2q2 - q3q3;  // 11(ǰ�к���)
    matrix[1] = 2.f * (q1q2 + q0q3);        // 12
    matrix[2] = 2.f * (q1q3 - q0q2);        // 13
    matrix[3] = 2.f * (q1q2 - q0q3);        // 21
    matrix[4] = q0q0 - q1q1 + q2q2 - q3q3;  // 22
    matrix[5] = 2.f * (q2q3 + q0q1);        // 23
    matrix[6] = 2.f * (q1q3 + q0q2);        // 31
    matrix[7] = 2.f * (q2q3 - q0q1);        // 32
    matrix[8] = q0q0 - q1q1 - q2q2 + q3q3;  // 33

    //��Ԫ��ת����ŷ����(Z->Y->X)
    Att_Angle->yaw += Gyr_rad->Z *RadtoDeg*0.01f;
//    Att_Angle->yaw = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)* 57.3f; // yaw
    Att_Angle->rol = -asin(2.f * (q1q3 - q0q2))* 57.3f;                            // roll(����Ҫע��)
    Att_Angle->pit = -atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3)* 57.3f ; // pitch
    for(i=0;i<9;i++)
    {
        *(&(DCMgb[0][0])+i) = matrix[i];
    }

    //ʧ�ر��� (����ʱ��ע�͵�)
//  Safety_Check();
}
