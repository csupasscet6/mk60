/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

uint8  nrf_rx_buff[CAMERA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8  nrf_tx_buff[CAMERA_SIZE + 2*COM_LEN + DATA_PACKET];         //Ԥ��
uint8 *imgbuff = (uint8 *)(((uint8 *)&nrf_tx_buff) + COM_LEN);     //ͼ���ַ

//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler();
void PORTE_IRQHandler();

uint8  var1 = 20, var2;
uint16 var3, var4;
uint32 var5, var6;


/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� ���ߵ��� ����ʵ��
 */
uint32 number  = 0;
void main()
{
  gpio_init(PTD15,GPO,LOW);
  gpio_init(PTC0,GPO,HIGH);
  Oled_Menu_init();
  ftm_pwm_init(FTM0,FTM_CH0,10*1000,5000);
  ftm_pwm_init(FTM0,FTM_CH1,10*1000,0);
  ftm_pwm_init(FTM0,FTM_CH2,10*1000,5000);
  ftm_pwm_init(FTM0,FTM_CH3,10*1000,0);
   
  while(1)
  {
    float num[7] ={10.0,20.0,15.0,15.5,12.2,16.0,12.0};
    Display_Page1(num);
   
    
    ftm_pwm_duty(FTM0,FTM_CH0,2500);
    ftm_pwm_duty(FTM0,FTM_CH1,0);
    ftm_pwm_duty(FTM0,FTM_CH2,2500);
    ftm_pwm_duty(FTM0,FTM_CH3,0);
  }
}
void  main1(void)
{
    Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size     = {80, 60}; //{LCD_W, LCD_H};       //��ʾ����ͼ���С
    uint32 i;
    com_e     com;
    nrf_result_e nrf_result;
    uint8 imgtxflag = 0;    //0��ʾ����ͼ��

    /************************ ���� K60 �����ȼ�  ***********************/
    //K60 ��Ĭ�����ȼ� ��Ϊ 0
    //�ο����ӣ������ж�Ƕ�׵����� - ���ܳ������� - ɽ����̳
    //          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
    NVIC_SetPriorityGrouping(4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�

    NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�
    NVIC_SetPriority(PORTE_IRQn,1);         //�������ȼ�
    NVIC_SetPriority(DMA0_IRQn,2);          //�������ȼ�
    NVIC_SetPriority(PIT0_IRQn,3);          //�������ȼ�

    /************************** LED ��ʼ��  ***************************/
    led_init(LED_MAX);


    /************************ LCD Һ���� ��ʼ��  ***********************/
    LCD_init();

    /************************ ����ģ�� NRF ��ʼ��  ***********************/
    while(!nrf_init());
    //�����жϷ�����
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);                //���� PORTE ���жϷ�����Ϊ PORTE_VECTORn
    enable_irq(PORTE_IRQn);
    nrf_msg_init();                                                     //����ģ����Ϣ��ʼ��

    //����ͷģ�飬��Ҫ ���� ������� ���԰�ģ�飬����������� ����ͼ��ʧ�ܶ�������������
    i = 20;
    while(i--)
    {
        nrf_msg_tx(COM_RETRAN,nrf_tx_buff);                              //���Ͷ�� �� �����ȥ��������� ���ն˵Ļ�������
    }

    /*********************** ������Ϣ ��ʼ��  ***********************/
    key_event_init();                                                   //������Ϣ��ʼ��
    pit_init_ms(PIT0,10);                                               //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);                  //���� PIT0 ���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq(PIT0_IRQn);

    /************************ ����ͷ ��ʼ��  ***********************/
    camera_init(imgbuff);                                   //����ͷ��ʼ������ͼ��ɼ��� imgbuff ��ַ
    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);      //���� DMA0 ���жϷ�����Ϊ DMA0_IRQHandler


    while(1)
    {
        /************************ ͼ��ɼ�����ʾ  ***********************/
        camera_get_img();                           //����ͷ��ȡͼ��

        /************************ ���߷��ͺͽ�������  ***********************/
        do
        {
            nrf_result = nrf_msg_rx(&com, nrf_rx_buff);
            if(nrf_result == NRF_RESULT_RX_VALID)
            {
                switch(com)
                {
                    case COM_IMG:
                        //��ʾ �� ��Ļ��
#if     ( CAMERA_COLOR == 1 )                                       //�Ҷ�����ͷ
                        LCD_Img_gray_Z(site,size, imgbuff,imgsize);
#elif   ( CAMERA_COLOR == 0 )                                       //�ڰ�����ͷ
                        LCD_Img_Binary_Z(site,size, imgbuff,imgsize);
#endif
                        break;

                    case COM_VAR:
                        if(last_tab == CAR_CTRL)                    //����� ���� С�� ����
                        {
                            switch(car_ctrl_get())                  //��ȡС��������������д���
                            {
                            case CAR_START:                         //����
                                //�˴����� ���� ����
                                led(LED0,LED_ON);
                                break;

                            case CAR_STOP:                          //ͣ��
                                //�˴����� ͣ�� ���� �����磺�رյ���������ر�ʹ�ܣ�
                                led(LED0,LED_OFF);
                                break;

                            case CAR_IMG_OPEN:
                                imgtxflag = 0;
                                break;

                            case CAR_IMG_CLOSE:
                                imgtxflag = 1;
                                break;


                            default:
                                //��Ч���������κδ���
                                break;
                            }
                        }

                        break;
                    default:
                        break;
                }
            }
        }while(nrf_result != NRF_RESULT_RX_NO);         //���ղ������� ���˳�

        if(!imgtxflag)
        {
            //��ͼ�� ���ͳ�ȥ
            nrf_msg_tx(COM_IMG,nrf_tx_buff);
        }

#if     ( CAMERA_COLOR == 1 )                                       //�Ҷ�����ͷ
        LCD_Img_gray_Z       (site,size, imgbuff,imgsize);
#elif   ( CAMERA_COLOR == 0 )                                       //�ڰ�����ͷ
        LCD_Img_Binary_Z(site,size, imgbuff,imgsize);
#endif

        if(!imgtxflag)
        {
            while(nrf_tx_state() == NRF_TXING);             //�ȴ��������
        }

        /*********************** ������Ϣ ����  ***********************/
        deal_key_event();
    }
}

/*

֪ʶ�� ����;

1.ӥ�� ����ͷ �ɼ�������ͼ���� ѹ��ͼ����Ҫ���н�ѹ���ο����� ����:
        ӥ��ͼ���ѹ��תΪ ��ά���� - ���ܳ������� - ɽ����̳
        http://www.vcan123.com/forum.php?mod=viewthread&tid=17


2.ͼ�� ��ַ ת��Ϊ ��ά���顣
        ����� ӥ�ۣ��ο� ��1��֪ʶ��˵��

        ��������� �Ҷ�ͼ������ͷ���޸����´���:
        uint8 *imgbuff = (uint8 *)(((uint8 *)&nrf_buff) + COM_LEN);     //ͼ���ַ
        ��Ϊ
        uint8 (*imgbuff)[CAMERA_H][CAMERA_W] =   (uint8 (*)[CAMERA_H][CAMERA_W])(((uint8 *)&nrf_buff) + COM_LEN);     //ͼ���ַ
        ʵ���� ����ǿ�� ����ת����

3.����ͷ�Ĳɼ���ַ ���� ����ͷ��ʼ���Ǵ��ݽ�ȥ�ģ��˺��ͼ�񶼲ɼ����õ�ַ�ϡ�
        camera_init(imgbuff);                                   //����ͷ��ʼ������ͼ��ɼ��� imgbuff ��ַ

4.����ģ�飬������ݽ��պ󣬲Ž��� ���ͣ��������Ծ������� ����ģ��ͬʱ���� ����״̬��

5.Ƕ���жϵ����⣬�ο���������:
        �����ж�Ƕ�׵����� - ���ܳ������� - ɽ����̳
        http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270

6.����ɨ�裬�ǲ��ö�ʱɨ�跽ʽ����ɨ���


*/



/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    //while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif

}

/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
        nrf_handler();
    }
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler()
{
    key_IRQHandler();

    PIT_Flag_Clear(PIT0);
}

