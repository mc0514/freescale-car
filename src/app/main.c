/******************** (C) COPYRIGHT 2011 蓝宙电子工作室 ********************
 * 文件名       ：main.c
 * 描述         ：工程模版实验
 *
 * 实验平台     ：landzo电子开发版
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/

**********************************************************************************/

#include "include.h"
#include "calculation.h"





/*************************
设置系统的全局变量
*************************/



extern  u8  LPT_INT_count ;
extern  u8  DMA_Over_Flg ;            //采集完成标志位
extern  u8  LinADCout ;





extern u8 TIME0flag_5ms   ;
extern u8 TIME0flag_10ms  ;
extern u8 TIME0flag_15ms  ;
extern u8 TIME0flag_20ms  ;
extern u8 TIME0flag_80ms ;
extern u8 TIME1flag_1s ;

uint8_t i ;
u16 count = 0 ;

void main()
{
  uint8_t action_flag='0';
  DisableInterrupts;
      //禁止总中断 
  
  /*********************************************************
  初始化程序
  *********************************************************/

     /*************************************
    初始化电机
    *************************************/
   /* */
 
   gpio_init (PORTC , 4, GPO,HIGH);                            //电机使能
  // gpio_init (PORTC , 2, GPO,LOW);                             //电机方向使能
    FTM_PWM_init(FTM0 , CH1, 80000,0);
    FTM_PWM_init(FTM0 , CH2, 80000,0);                        //电机占空比设置初始化    占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;

   uart_init (UART0 , 9600);                      //初始化UART0，输出脚PTA15，输入脚PTA14，串口频率 9600
   gpio_init (PORTA , 17, GPO,HIGH); 
   gpio_init (PORTB , 17, GPO,LOW);   
   pit_init_ms(PIT0, 5);                                    //初始化PIT0，定时时间为： 5ms
   pit_init_ms(PIT1, 1000);                                //初始化PIT1，定时时间为： 1000ms    
   EnableInterrupts;			                    //开总中断  
    
   /******************************************
    执行程序
    ******************************************/
    while(1)
    {
     //uart_putchar(UART0,'I');
     
      /*********************
      5ms程序执行代码段
      *********************/
      if(TIME0flag_5ms == 1)
      { 
        TIME0flag_5ms = 0 ;
        
      }
      
      /*********************
      10ms程序执行代码段
      *********************/
      if(TIME0flag_10ms == 1)
      {
        TIME0flag_10ms = 0 ;
      //u8 ch = 'a';
        
        //uart_putchar(UART0,'I');
        //uart_sendX(UART0,0x02);
        i =  uart_getcharflg (UART0)  ;
        //uart_sendStr(UART0,"A");
         if(i){ 
           action_flag= uart_getchar(UART0) ;
          //printf("ation flag: %c\n",action_flag);
           //i=uart_getchar(UART0)+1;
           //uart_putchar(UART0,'L');
            //PTB17_OUT = ~PTB17_OUT;
           //uart_sendX(UART0,action_flag);
           if(action_flag=='1')
           {
              uart_putchar(UART0,'F');
              PTB17_OUT = ~PTB17_OUT;
              FTM_PWM_Duty(FTM0 , CH1,40);
              FTM_PWM_Duty(FTM0 , CH2,0);
          }
           else if(action_flag=='2')
           {
            uart_putchar(UART0,'B');
            FTM_PWM_Duty(FTM0 , CH1,0);
            FTM_PWM_Duty(FTM0 , CH2,40);
          }
          else if(action_flag=='3')
          {
            uart_putchar(UART0,'S');
            FTM_PWM_Duty(FTM0 , CH1,0);
            FTM_PWM_Duty(FTM0 , CH2,0);
          }
          
           
         }

         //uart_putchar(UART0, 'a') ;


      }
      
      /*********************
      15ms程序执行代码段
      *********************/
       if(TIME0flag_15ms == 1)
      {
        TIME0flag_15ms = 0 ;
      //  uart_putchar(UART0,0xff);
        
      }
      
      /*********************
      20ms程序执行代码段
      *********************/
            if(TIME0flag_20ms == 1)
      {
        TIME0flag_20ms = 0 ;
        //uart_putchar(UART0, 0xaa) ;
       
      }
      
      
      
      
//      if(TIME0flag_80ms == 1)
//      {
//        TIME0flag_80ms = 0 ;
//if( count == 3 )
//       {
//          count = 2 ;
//          FTM_PWM_Duty(FTM0 , CH1,50);
//          FTM_PWM_Duty(FTM0 , CH2,0);
//       } else if(count == 2)
//       {
//         
//          count = 1 ;
//          FTM_PWM_Duty(FTM0 , CH1,0);
//          FTM_PWM_Duty(FTM0 , CH2,0);
//          
//       }else if(count == 1)
//       {
//         
//          count = 0 ;
//
//          FTM_PWM_Duty(FTM0 , CH1,0);
//          FTM_PWM_Duty(FTM0 , CH2,50);
//       
//       } else if(count == 0)
//       {
//         
//          count = 3 ;
//          FTM_PWM_Duty(FTM0 , CH1,0);
//          FTM_PWM_Duty(FTM0 , CH2,0);
//          
//       }
//       
//      }
      
      /*********************
      1s程序执行代码段
      *********************/      
      if(TIME1flag_1s == 1)
      {        
        TIME1flag_1s = 0 ; 
        PTA17_OUT = ~PTA17_OUT ; 
     
      }

    }
}




  
