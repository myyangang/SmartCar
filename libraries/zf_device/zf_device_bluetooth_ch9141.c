/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_device_bluetooth_ch9141
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note
********************************************************************************************************************/

#include "zf_device_type.h"
#include "zf_device_bluetooth_ch9141.h"

uint8_t uart_flag;
uint8_t uart_data;

volatile uint8_t at_mode = 0;         //0:����͸��ģʽ 1:ATģʽ 2:ģ�鸴λ��
volatile uint8_t at_mode_num;         //atģʽʱ����ָʾ���ݽ��յ�����
volatile uint8_t at_mode_data[30];    //����at����Ļ���
volatile uint8_t at_mode_cmd_flag;    //OKӦ��������ճɹ��ı�־λ

uint8_t mac_address[17];              //����mac��ַ


bluetooth_ch9141_info_struct bluetooth_ch9141[] = BLUETOOTH_CH9141_DEVICE_INFO_BUFFER;

uint8_t bluetooth_ch9141_rx_buffer[BLUETOOTH_CH9141_NUMBER];

void bluetooth_ch9141_check_response(void);

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� �����жϻص�����
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �ú�����ISR�ļ� ����8�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_uart_callback_ch2(void)
{
    if(1 == at_mode)
    {
        //����ATģʽ ����Ӧ���ź� �˴�if����ڴ����û���Ҫ�Ķ�
        at_mode_data[at_mode_num++] = ((USART_TypeDef*)uart_index[bluetooth_ch9141[1].uart_n])->DATAR & 0x01FF;
        bluetooth_ch9141_check_response();
    }
    else if(2 == at_mode)
    {
        //ģ�����ڸ�λ�� �˴�if����ڴ����û���Ҫ�Ķ�
        at_mode_num++;
    }
    else
    {
        //͸��ģʽ �û��ڴ˴�������Ե��������͹����Ķ�����
        //�ӵ�һ���ֽں�Ƭ���������˴���ͨ���ڴ˴���ȡuart_data����ȡ������

        // ��ȡ���ߴ��ڵ����� ������λ���ձ�־
        uart_flag = 1;
        uart_data = ((USART_TypeDef*)uart_index[bluetooth_ch9141[1].uart_n])->DATAR & 0x01FF;
    }


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� �����жϻص�����
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �ú�����ISR�ļ� ����8�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_uart_callback_ch1(void)
{

    if(1 == at_mode)
    {
        //����ATģʽ ����Ӧ���ź� �˴�if����ڴ����û���Ҫ�Ķ�
        at_mode_data[at_mode_num++] = ((USART_TypeDef*)uart_index[bluetooth_ch9141[0].uart_n])->DATAR & 0x01FF;
        bluetooth_ch9141_check_response();
    }
    else if(2 == at_mode)
    {
        //ģ�����ڸ�λ�� �˴�if����ڴ����û���Ҫ�Ķ�
        at_mode_num++;
    }
    else
    {
        //͸��ģʽ �û��ڴ˴�������Ե��������͹����Ķ�����
        //�ӵ�һ���ֽں�Ƭ���������˴���ͨ���ڴ˴���ȡuart_data����ȡ������

        // ��ȡ���ߴ��ڵ����� ������λ���ձ�־
        uart_flag = 1;
        uart_data = ((USART_TypeDef*)uart_index[bluetooth_ch9141[0].uart_n])->DATAR & 0x01FF;
    }


}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ����OKӦ���ź�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �û��������
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_check_response(void)
{
    if(4 <= at_mode_num)
    {
        if(0 == strncmp("OK\r\n", (int8_t *)&at_mode_data[at_mode_num-4], 4))
        {
            at_mode_cmd_flag = 1;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�鷢��һ��û�в���������ȴ�Ӧ���ź�
//  @param      *str    ��Ҫ���͵����� �����ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �û��������
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_send_at_command(uart_index_enum uart_n,const int8_t *str)
{
    int16_t timeout = BLUETOOTH_CH9141_INIT_TIMEOUT;

    at_mode_num = 0;        //������������
    uart_write_string(uart_n, str);
    uart_write_string(uart_n, "\r\n");

    //�ȴ��յ�Ӧ���ź�
    while(!at_mode_cmd_flag&& timeout-- > 0)
    {
        system_delay_ms(1);
    }

    if(timeout <= 0)                            // ��ʱ
          return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�鷢��һ�����в���������ȴ�Ӧ���ź�
//  @param      *cmd    ��Ҫ���͵���������
//  @param      *data   ��Ҫ���͵�����
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       �û��������
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_send_at_command_parameter(uart_index_enum uart_n,const int8_t *cmd, const int8_t *data)
{
    int16_t timeout = BLUETOOTH_CH9141_INIT_TIMEOUT;
    at_mode_num = 0;        //������������
    uart_write_string(uart_n, "AT+");
    uart_write_string(uart_n, cmd);
    uart_write_string(uart_n, "=");
    uart_write_string(uart_n, data);
    uart_write_string(uart_n, "\r\n");

    //�ȴ��յ�Ӧ���ź�
    while(!at_mode_cmd_flag&& timeout-- > 0)
    {
        system_delay_ms(1);

    }
    at_mode_cmd_flag = 0;

    if(timeout <= 0)                            // ��ʱ
          return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�����ATģʽ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_enter_at_mode(uart_index_enum uart_n)
{
    system_delay_ms(600);  //���ͽ���ATģʽ������ǰ��Ҫ��֤ģ����550ms��û�н��չ��κ�����
    at_mode = 1;            //����ATģʽ

    return bluetooth_ch9141_send_at_command(uart_n, "AT...");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���˳�ATģʽ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_exit_at_mode(uart_index_enum uart_n)
{
    if(bluetooth_ch9141_send_at_command(uart_n,"AT+EXIT"))
        return 1;
    at_mode = 0;            //����͸��ģʽ
    system_delay_ms(300);  //�ȴ��ɹ�����ATģʽ
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�鸴λ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_reset(uart_index_enum uart_n)
{
    if(bluetooth_ch9141_send_at_command(uart_n, "AT+RESET"))
        return 1;
    at_mode = 2;            //���������ɹ����
    at_mode_num = 0;
    while(7 > at_mode_num); //�ȴ�����ģ����ɸ�λ
    at_mode = 0;            //��λ֮��ģ���Զ�����͸��ģʽ
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ȡ����MAC��ַ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       ���ô˺�����Ҫ�ȵ���bluetooth_ch9141_enter_at_mode��������CMD���� ����ATģʽ
//              ��Ҫ�ر�ע��bluetooth_ch9141_enter_at_mode�����ڲ���500ms����ʱ
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_get_mac_address(uart_index_enum uart_n)
{
    if(bluetooth_ch9141_send_at_command(uart_n, "AT+MAC?"))
        return 1;


    //mac��ַΪС�θ�ʽ��mac_address[0]�������mac��ַ���λ
    memcpy(mac_address, (uint8_t *)at_mode_data, 17);
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�����÷��͹���
//  @param      tx_power    ���÷��͹��ʣ�������ѡ��鿴CH9141_TX_POWEER_enumö�ٳ�Ա
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_set_tx_power(uart_index_enum uart_n, ch9141_tx_power_enum tx_power)
{
    int8_t tx_power_data;

    tx_power_data = (uint8_t)tx_power + '0';
    return bluetooth_ch9141_send_at_command_parameter(uart_n, "TPL", &tx_power_data);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ������ģʽ
//  @param      mode    ģʽ���ã�������ѡ��鿴CH9141_MODE_enumö�ٳ�Ա
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_set_mode(uart_index_enum uart_n, ch9141_mode_enum mode)
{
    int8_t mode_data;

    mode_data = (uint8_t)mode + '0';
    return bluetooth_ch9141_send_at_command_parameter(uart_n, "BLEMODE", &mode_data);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ȡ״̬
//  @param      mode    ģʽ���ã�������ѡ��鿴CH9141_MODE_enumö�ٳ�Ա
//  @return     CH9141_STATUS_enum  ����״̬��Ϣ
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_wait_connect_success(uart_index_enum uart_n, ch9141_mode_enum mode)
{
    int16_t timeout = BLUETOOTH_CH9141_INIT_TIMEOUT;
    ch9141_status_enum ret;

    //�ȴ��յ�Ӧ���ź�
    while((MASTER_CONNECTED != ret)&& timeout-- > 0)
    {
        system_delay_ms(1);
        ret = bluetooth_ch9141_get_status(uart_n, mode);
    }

    if(timeout <= 0)                            // ��ʱ
          return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ȡ״̬
//  @param      mode    ģʽ���ã�������ѡ��鿴CH9141_MODE_enumö�ٳ�Ա
//  @return     CH9141_STATUS_enum  ����״̬��Ϣ
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
ch9141_status_enum bluetooth_ch9141_get_status(uart_index_enum uart_n, ch9141_mode_enum mode)
{
    ch9141_status_enum ch9141_status;
    int8_t mode_data;

    mode_data = (uint8_t)mode + '0';
    bluetooth_ch9141_send_at_command_parameter(uart_n, "BLEMODE", &mode_data);

    bluetooth_ch9141_send_at_command(uart_n, "AT+BLESTA?");

    ch9141_status = (at_mode_data[0] - '0') * 10 + (at_mode_data[1] - '0');
    if(SLAVE_MODE == mode)
    {
        ch9141_status += SLAVE_NO_INIT;
    }

    return ch9141_status;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�������豸����
//  @param      *str    ��������
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       ���Ƴ��Ȳ��ܳ���18���ַ� ��ֻ��ΪӢ��������
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_set_name(uart_index_enum uart_n, const int8_t *str)
{
    if(bluetooth_ch9141_send_at_command_parameter(uart_n, "NAME", str))
        return 1;
    if(bluetooth_ch9141_send_at_command_parameter(uart_n, "PNAME", str))
        return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ����������
//  @param      enable      ʹ������ 0����ʹ�����룬1��ʹ������������ӱ��豸
//  @param      *password   ������ַ��� ����Ϊ6���ַ�
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_set_password(uart_index_enum uart_n, uint8_t enable, const int8_t *password)
{
    if(0 == enable)
    {
        //�ر�����
        if(bluetooth_ch9141_send_at_command_parameter(uart_n, "PASEN", "OFF"))
            return 1;
    }
    else
    {
        //�������벢ʹ��
        if(bluetooth_ch9141_send_at_command_parameter(uart_n, "PASEN", "ON"))
            return 1;
        if(bluetooth_ch9141_send_at_command_parameter(uart_n, "PASS", password))
            return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ��ָ��MAC��ַ��������������
//  @param      *mac_and_password      ��Ҫ���ӵ��豸mac��ַ������
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       bluetooth_ch9141_connect("58:B7:33:E4:C2:84,000000");
//              58:B7:33:E4:C2:84Ϊmac��ַ ,Ϊ�ָ��� 000000Ϊ�ӻ���������
//              ===================�ر�ע��==================
//              ���ʹ���ֻ��鿴������mac��ַ����ʹ�ñ��������ӵ�ʱ���뽫mac����һ��
//              �����ֻ��鿴����mac��ַΪ61:62:63:64:65:66����ʹ�ñ��������ӵ�ʱ��Ӧ��д
//              bluetooth_ch9141_connect("66:65:64:63:62:61,000000");
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_connect(uart_index_enum uart_n, const int8_t *mac_and_password)
{
    return bluetooth_ch9141_send_at_command_parameter(uart_n, "CONN", mac_and_password);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ��Ĭ�����Ӳ������ã����úú�ÿ�ο����������Զ���������豸��
//  @param      *mac_and_password      ��Ҫ���ӵ��豸mac��ַ������
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       bluetooth_ch9141_default_connect("58:B7:33:E4:C2:84,000000");
//              58:B7:33:E4:C2:84Ϊmac��ַ ,Ϊ�ָ��� 000000Ϊ�ӻ���������
//              ===================�ر�ע��==================
//              ���ʹ���ֻ��鿴CH9141��mac��ַ����CH9141����Ϊ�ӻ���ʹ���ֻ�����
//              ��ʹ�ñ��������ӵ�ʱ���뽫mac����һ��
//              �����ֻ��鿴����mac��ַΪ61:62:63:64:65:67����ʹ�ñ��������ӵ�ʱ��Ӧ��д
//              bluetooth_ch9141_default_connect("67:65:64:63:62:61,000000");
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_default_connect(uart_index_enum uart_n, const int8_t *mac_and_password)
{
    return bluetooth_ch9141_send_at_command_parameter(uart_n, "CONADD", mac_and_password);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ȡrssi(�ź�ǿ��)
//  @param      void
//  @return     int8_t    �����ź�ǿ��0��-127
//  @since      v1.0
//  Sample usage:
//  @note       ���ô˺�����Ҫ�ȵ���bluetooth_ch9141_enter_at_mode��������CMD���� ����ATģʽ
//              ��Ҫ�ر�ע��bluetooth_ch9141_enter_at_mode�����ڲ���500ms����ʱ
//-------------------------------------------------------------------------------------------------------------------
int16_t bluetooth_ch9141_get_rssi(uart_index_enum uart_n)
{
    uint8_t i;
    size_t length;
    int16_t  rssi;

    if(bluetooth_ch9141_send_at_command_parameter(uart_n, "RSSI", "ON,0"))
        return 200;
    length = strlen((int8_t *)at_mode_data);
    length -= 12;//����RSSI �ж���λ

    rssi = 0;
    for(i=0; i<length; i++)
    {
        rssi = rssi*10 + (at_mode_data[0] - '0');
    }

    return -rssi;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� ���ͺ���
//  @param      buff        ��Ҫ���͵����ݵ�ַ
//  @param      len         ���ͳ���
//  @return     uint32      ʣ��δ���͵��ֽ���
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint32_t bluetooth_ch9141_send_buff(uart_index_enum uart_n, uint8_t *buff, uint32_t len)
{
    bluetooth_ch9141_info_struct *temp_info = NULL;
    uint8_t i = 0;

    for(i = 0; i<BLUETOOTH_CH9141_NUMBER; i++)
    {
        if(bluetooth_ch9141[i].uart_n == uart_n)
        {
            temp_info = &bluetooth_ch9141[i];
            break;
        }
    }

    while(len)
    {
        //���ؼ�� RTSΪ�߱�ʾ����ģ���ڲ����������޷�������������

        //RTSΪ�ߴ���ʽһ�������⵽RTSΪ�����������ݲ��ټ������ͣ�������ֵȴ�
        if(gpio_get_level(temp_info->rts_pin))
        {
            break;
        }

        //RTSΪ�ߴ���ʽ���������⵽RTSΪ����ȴ�RTSΪ��֮�������������
        //while(gpio_get(BLUETOOTH_CH9141_RTS_PIN));  //���RTSΪ�͵�ƽ���������������

        //��������
        uart_write_byte(temp_info->uart_n, *buff);


        buff++;
        len--;
    }

    return len;
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ʼ��
//  @param      mode    ����ģʽ MASTER_MODE(����)����SLAVE_MODE(�ӻ�)
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8_t bluetooth_ch9141_init(void)
{
    uint8_t i = 0;

    //������ʹ�õĲ�����Ϊ115200��Ϊ����ת����ģ���Ĭ�ϲ����ʣ�����������������ʹ����λ���޸�ģ�����
    //��ʼ����������
    wireless_type = BULETOOTH_CH9141;
    interrupt_enable_all(0);

    for(i = 0; i<BLUETOOTH_CH9141_NUMBER; i++)
    {
        uart_init(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].baud, bluetooth_ch9141[i].tx_pin, bluetooth_ch9141[i].rx_pin);
        gpio_init(bluetooth_ch9141[i].rts_pin, GPI, 1, GPI_PULL_UP);
        uart_rx_interrupt(bluetooth_ch9141[i].uart_n, ENABLE);

        //������Ϊ������ӻ�ģʽ������������Ҫ���ӳɹ��ͱ�����һ��Ϊ��������һ��Ϊ�ӻ������Ե��ó�ʼ����ʱ����Ҫ�������д�����������ܳɹ�������
        //������Ϊ������ӻ�ģʽ������������Ҫ���ӳɹ��ͱ�����һ��Ϊ��������һ��Ϊ�ӻ������Ե��ó�ʼ����ʱ����Ҫ�������д�����������ܳɹ�������
        //�ϵ�˳����ôӻ����ϵ磬Ȼ���������ϵ�

        if(MASTER_MODE == bluetooth_ch9141[i].mode)
        {
            //1.����������Ϊ����ģʽ��Ȼ������ָ��mac��ַ�Ĵӻ��豸
            if(bluetooth_ch9141_enter_at_mode(bluetooth_ch9141[i].uart_n))  //����ATģʽ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_set_mode(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].mode))   //��������ģʽ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_get_mac_address(bluetooth_ch9141[i].uart_n))//��ȡ����MAC��ַ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_reset(bluetooth_ch9141[i].uart_n))                  //������ɺ���Ҫ��λ�����òŻ���Ч
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_enter_at_mode(bluetooth_ch9141[i].uart_n))          //����ATģʽ
            {
                 zf_assert(0);
                 return 1;
            }
            system_delay_ms(500);
            //������ģʽ֮����Ҫ��λȻ���ٴν���ATģʽ���ܼ���������������������ģʽ���ò��ɹ�
            if(bluetooth_ch9141_set_tx_power(bluetooth_ch9141[i].uart_n, TX_POWER_4DB))//�����������͹���
            {
                 zf_assert(0);
                 return 1;
            }
            system_delay_ms(500);
            //===================�ر�ע��==================
            //���ʹ���ֻ��鿴������mac��ַ����ʹ�ñ��������ӵ�ʱ���뽫mac����һ��
            //�����ֻ��鿴����mac��ַΪ61:62:63:64:65:66����ʹ�ñ��������ӵ�ʱ��Ӧ��д
            //bluetooth_ch9141_connect("66:65:64:63:62:61,000000");
            //58:B7:33:E4:C2:84Ϊmac��ַ ,Ϊ�ָ��� 000000Ϊ�ӻ���������
            //�ӻ�MAC��ַ������
            //int8_t salve_mac_password[] = "80:90:2C:E4:C2:84,000000";
            if(bluetooth_ch9141_default_connect(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].salve_mac_password))  //����Ĭ�����Ӳ�������ʹ�´β�����Ҳ���Զ����Ӵӻ�
            {
                zf_assert(0);
                return 1;
            }
            system_delay_ms(500);
            if(bluetooth_ch9141_connect(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].salve_mac_password))          //�����������õĴӻ���ַ
            {
                zf_assert(0);
                return 1;
            }

            //�ȴ����ӳɹ�
            if(bluetooth_ch9141_wait_connect_success(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].mode))
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_exit_at_mode(bluetooth_ch9141[i].uart_n))                       //�˳�ATģʽ
            {
                zf_assert(0);
                return 1;
            }
        }
        else if(SLAVE_MODE == bluetooth_ch9141[i].mode)
        {
            //2.��������Ϊ�ӻ����ȴ�����
            if(bluetooth_ch9141_enter_at_mode(bluetooth_ch9141[i].uart_n))  //����ATģʽ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_set_mode(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].mode))   //��������ģʽ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_get_mac_address(bluetooth_ch9141[i].uart_n))//��ȡ����MAC��ַ
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_reset(bluetooth_ch9141[i].uart_n))                  //������ɺ���Ҫ��λ�����òŻ���Ч
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_enter_at_mode(bluetooth_ch9141[i].uart_n))          //����ATģʽ
            {
                zf_assert(0);
                return 1;
            }
            //������ģʽ֮����Ҫ��λȻ���ٴν���ATģʽ���ܼ���������������������ģʽ���ò��ɹ�
            if(bluetooth_ch9141_set_tx_power(bluetooth_ch9141[i].uart_n, TX_POWER_4DB))//�����������͹���
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_set_name(bluetooth_ch9141[i].uart_n, "ble"))
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_set_password(bluetooth_ch9141[i].uart_n, 1, "000000"))  //000000Ϊ������������Լ��޸�
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_reset(bluetooth_ch9141[i].uart_n))                  //������ɺ���Ҫ��λ�����òŻ���Ч
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_enter_at_mode(bluetooth_ch9141[i].uart_n))          //����ATģʽ
            {
                zf_assert(0);
                return 1;
            }
            //�ȴ����ӳɹ�
            if(bluetooth_ch9141_wait_connect_success(bluetooth_ch9141[i].uart_n, bluetooth_ch9141[i].mode))
            {
                zf_assert(0);
                return 1;
            }
            if(bluetooth_ch9141_exit_at_mode(bluetooth_ch9141[i].uart_n))          //�˳�ATģʽ
            {
                zf_assert(0);
                return 1;
            }
        }
    }
    //������ȡ�����ź�ǿ�ȿ��԰��������ʾ������
    //bluetooth_ch9141_enter_at_mode();
    //int16_t  rssi = bluetooth_ch9141_get_rssi();

    interrupt_disable_all();
    return 0;
}





