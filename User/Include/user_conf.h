
/************************ (C) COPYRIGHT 2015 FT *******************************
* File Name          : 
* Author             : Application Team  Tom.wang 
* Version            : V2.0.0
* Date               : 06/15/2015
* Description        : 警告：禁止修改,删除 结构体定义 会导致未知错误
********************************************************************************
/*******************************************************************************
* All Rights Reserved
*******************************************************************************/

#ifndef __USER_CONF_H
#define __USER_CONF_H

//&& 读写  %% 只读  单位 *  标幺值 -- 无单位
//_IQ15 最小分辨率 0.0000306 范围-0.9999 ~0.9999
//------------------------------------------------------------------------
//停机方式                
#define FREE_DOWN           (0xF1)              //单位-- %%  自由停机
#define SLOWING_DOWN        (0xF2)              //单位-- %%  减速停机   没有测试
#define BREAK_DOWN          (0xF3)              //单位-- %%  刹车
#define BREAK_DOWNWALTNMS   (50)               //单位-- &&  刹车持续时间 持续刹车Nms 才允许在启动
#define BREAK_VALUE         _IQ(1.0)            //单位-- &&  刹车强度 0.0~1.0 
#define STOPMODE            (FREE_DOWN)      //单位-- && 

//自举电容充电参数设置                          //单位-- && 下桥长低模式不需要，充电
#define CHARGEDUTY          _IQ(0.5)            //单位** && 充电占空比
#define CHARGENMS           (0)                 //单位-- &&  充电时间

//上电等待时间
#define POWER_ON_NMS        (100)               //单位ms && 上电等待时间100ms 500ms 
//======================================================================
//位置反馈模式 
#define SENSORLESS        1                //单位-- %% 无感模式
#define HALLSENSOR        2                //单位-- %% HALL位置传感器检测位置
#define POSITION_FB_MODE  SENSORLESS       //单位-- && 位置反馈检测方式

//======================================================================
//----------------------------------------------------------------------
//HALLSENSOR 参数调整区
//hall安装方式
#define HALLPTDPE        (0)                 //单位-- && hall 内部上拉使能
#define DEGREES_120      (0)                 //单位-- %% hall 120度安装模式
#define DEGREES_60       (1)                 //单位-- %% hall 60度安装模式
#define HALL_SENSORS_PLACEMENT DEGREES_120   //单位-- 选择

//HALLADVANCEEANGLE 设置范围（-10~-50 或者0~30）整数 
//1、不超前换相  设置范围-10~-50度超前角   0~30 为滞后换相
//2、设置超前换相时，如果电机不正常运行，请调换HALL线
//3、定义Ctl.direction == CW(正转)时 定义HALL顺序为 Drv.Hall.Section 1->2->3->4->5->6->1……
#define HALLADVANCEFIX    (0)               //开启超前换相如果电机运行不正常，修改此参数 1 or 0
#define HALLADVANCEEANGLE (0)               //单位° && HALL安装角度调整 hall Advance Eangle  

//HALLSENSOR 参数调整区结束
//======================================================================
//----------------------------------------------------------------------
//SENSORLESS参数调整区
//无HALL调试模式 等待 过程 调试模式   软件会在此过程中运行，不会进行下一步动作
#define NO_WAIT           0                //单位-- %% 无等待
#define WAIT_STRACK       4                //单位-- %% 转速跟踪
#define WAIT_PRECHARGE    5                //单位-- %% 充电
#define WAIT_ALIGNMENGT   6                //单位-- %% 定位
#define WAIT_RAMPUP       7                //单位-- %% 拖动
#define WAIT_STEP         NO_WAIT          //单位-- && 等待状态
//MOSI 过零点   NSS屏蔽过零点信号
#define BEMF_TEST         (1)              //单位-- && BEMF测试信号输出使能 
//----------------------------------------------------------------------
//转速跟踪启动
#define STRACK_EN          (2)              //单位-- &&转速跟踪启动使能 1反转等待  2反转自动刹车  
#define STKNMS             (30)             //单位ms 转速跟踪监测时间
#define SRKBNUM            (5)              //单位-- 转速跟踪检测次数
//----------------------------------------------------------------------
//定位参数设置     峰岹模式2 20 5 10 10000 10000
#define ALIGNMENTNMS      (0)              //单位ms 定位时间                
#define ALIGNMENT_DUTY    _IQ(0.05)         //单位ms 定位力矩            
//Ramp Up参数配置 
#define RAMP_MODE         (1)              //单位-- &&  pamp 模式   1 2 3
#define PAMP_PWM_FREQ     (8000)           //单位Hz &&  启动频率          
#define RAMP_TIM_STA      (15)             //单位ms &&  爬坡开始步进时间， 
#define RAMP_TIM_END      (8)              //单位ms &&  爬坡结束步进时间，     
#define RAMP_TIM_STEP     (35)             //单位ms &&  爬坡步进时间递减增量， 
#define RAMP_DUTY_STA     _IQ(0.2)      //单位* &&   爬坡开始力矩   
#define RAMP_DUTY_END     _IQ(0.22)       //单位* &&   爬坡结束力矩   
#define RAMP_DUTY_INC     _IQ(0.01)        //单位*  &&  爬坡步进力矩增量
#define RAMP_STEP_COUNTER  (5)             //单位-- &&  爬坡结束后维持步数  pamp 模式 2有效

#define RampMaskTime      (0.1)            //单位ms &&  续流屏蔽时间
#define RampNumFail       (2)              //单位-- &&  
#define RampDetecBEMFCnt  (100)             //单位-- &&  启动检测BEMF过零点个数
#define RampDetecBEMFCntFilt (50)           //单位-- &&  启动检测错误BEMF过零点个数
//换相参数配置
#define MASK_ANGLE        (0)              //单位° && 续流屏蔽角度，单位°
#define DELAY_ANGLE       (0)              //单位° && 换相进角角度，单位° 

//----------------------------------------------------------------------
#define CMPSAME_EN        (2)              //单位-- TIM2触发比较器采样使能 0失能 1使能 2使能+切换  采样点在PWM高电平中间位置
#define CMPSAMESWITCH     (RAMP_DUTY_END+_IQ(0.0))  //单位* && 采样模式切换阈值
//SENSORLESS参数调整区结束
//======================================================================
//调速方式 参数调整请见constant.h文件
#define  ADCSREF_EN         (0)               //单位-- &&模拟调速使能
#define  PWMINSREF_EN       (1)               //单位-- &&PWMIN调速使能

#define  ADCONOFF_EN        (0)               //单位-- && SREF控制ONOFF使能
#define  PWMINONOFF_EN      (1)               //单位-- && PWMIN控制启停
#define  KEYONOFF_EN        (0)               //单位-- && Key/端子 控制ONOFF使能   1 轻触式开关 2端子是开关
//----------------------------------------------------------------------
//电流闭环控制  电流环内环
#define  CURRENT_LIMIT_EN   (0)                //单位-- && 电流限制使能 
#define  CURRENT_LIMIT_MAXREF (35)            //单位A  && 限制电流

#define  CURRENT_CLOSE_EN   (0) 
#define  CURRENT_CTL_CNT    (3)                  //单位-- 电流调节频率计数器
#define  CURRENT_PTERM      _IQ(300.0/32767.0)   //单位* 电流环kp
#define  CURRENT_ITERM      _IQ(50.0/32767.0)    //单位* 电流环ki
#define  CURRENT_INMAX      _IQ(3000.0/32767.0)  //单位* 电流环，输入限幅值

#define  CURRENT_OUTMIN     (_IQ(8000.0/32767.0))//单位* 电流环输出限幅
#define  CURRENT_OUTMAX     (_IQ(1.0))             //单位* 电流环输出限幅
//----------------------------------------------------------------------
//速度控制  
#define  SPEED_CALC_EN      (0)                //单位-- &&转速计算使能 失能优化计算时间 0->不计算   1->标幺值  2->标幺值+实际转速
#define  SPEED_CLOSE_EN     (0)                //单位-- 速度闭环使能
#define  SPEED_CTL_CNT      (20)               //单位-- 速度调节频率计数器
#define  SPEED_PTERM        _IQ(20.0/32767.0)  //单位* 速度环kp
#define  SPEED_ITERM        _IQ(50.0/32767.0)  //单位* 速度环ki
#define  SPEED_OUTMIN       _IQ(8000.0/32767.0)//单位* 速度环 
#define  SPEED_OUTMAX       _IQ(1.0)           //单位* 速度环 

#define  SPEED_REF_TAR      _IQ(0.5)           //单位* 控制目标速度 默认值     速度闭环 
#define  SPEED_REF_INIT     _IQ(0.001)         //单位* 控制目标速度 初始值     速度闭环 
//开环
#define  MOTOR_TARGRT_DUTY   _IQ(0.1)          //单位* 开环目标占空比 默认值   速度开环控制
#define  MOTOR_INIT_DUTY     _IQ(0.01)         //单位* HALL模式初始占空比      速度开环控制

#define  SPEED_INCVALUE     (500)               //单位* 加速爬坡步进增量 每100us     100
#define  SPEED_DECVALUE     (500)               //单位* 减速爬坡步进增量 每100us     100

//----------------------------------------------------------------------
//输出限幅
#define  MOTOR_VS_MAX        _IQ(1.0)      //单位*   最大输出占空比
#define  MOTOR_VS_MIN        _IQ(0.01)      //单位*   最小输出占空比
//======================================================================
//----------------------------------------------------------------------
//故障和保护参数配置  注意：有位置反馈 一般堵转保护设置为大于1000ms。 失速保护关闭
//堵转失速保护
#define  STA_EN              (1)            //堵转保护使能
#define  STANMS              (15)           //单位ms  堵转保护时间  

#define  STB1_EN             (1)            //超速保护使能
#define  STB1SPEED           (300000)        //单位rpm &&  
#define  STB1NMS             (100)          //单位ms  失速检测时间

#define  STB2_EN             (1)            //低速保护使能
#define  STB2SPEED           (500)          //单位rpm &&  
#define  STB2NMS             (100)          //单位ms  失速检测时间

#if (POSITION_FB_MODE == SENSORLESS)
  #define  STB3_EN             (0)             //失速保护使能
#else
  #define  STB3_EN             (0)             //有HALL关闭 速度3检测
#endif

#define  STB3WAIT            (100)             //大于3
#define  SRB3TIMEFILT        (20)              //StepTime滤波值
#define  STB3ERRVALUE        (20)              //检测次数
  
//堵转保护重启参数  STA_EN  STB1_EN  STB2_EN STB3_EN 故障均自动清除故障，启动                
#define  STALLRESTART_EN     (1)           //单位-- && 堵转保护重启使能  
#define  STALLRESTARTNUM     (1)         //单位-- && 堵转重启次数   
#define  STALLRESTARTTIM     (1)           //单位1ms 堵转重启延迟时间 
//----------------------------------------------------------------------
//硬件过流 FO触发保护并关闭输出
#define  HARD_OC_EN          (0)           //单位- 使能硬件过流    禁止关闭
//逐波限流 使能逐波限流会取消硬件过流保护 cycle  by  cycle  current protection
//0 取消逐波限流，硬件FO直接保护  1 连续CBCCP_NUM次FO信号保护 2不会报保护，只限流
//高压一般不逐波限流功能 验证此功能有误
#define  CBCCP_EN            (0)           //单位- && 逐波限流使能 
#define  CBCCP_NUM           (100)         //单位- && 逐波限流使能 
//过流保护参数设置
#define  IBUS_CALC_EN        (0)           //单位-  失能，建议关闭，不影响过流保护
#define  OVERCURRENT_EN      (0)           //单位-  过流保护
#define  OVERCURRENT         (60)          //单位A  过流值
#define  OCNMS               (4)           //单位ms 过流监测时间

//过流保护重启参数                         
#define  OCRESTART_EN        (1)           //单位- && 过流重启使能  包括硬件过流 软件过流 过载
#define  OCRESTARTNUM        (50)           //单位* && 母线过流重启次数
#define  OCRESTARTTIM        (5)           //单位ms && 过流重启延迟时间

//----------------------------------------------------------------------
//过压、欠压保护重启参数 
#define  VBUS_CALC_EN        (1)           //单位-  失能,建议关闭，不影响过欠压保护 AD2
#define  OVERVOLTAGE_EN      (0)           //单位-  过压保护使能  
#define  UNDERVOLTAGE_EN     (0)           //单位-  欠压保护使能
#define  VBUSRECOVER_EN      (0)           //单位-  母线电压恢复重启使能

#define  DCVOLTAGE           (36.0)        //单位V   控制器基本电压
#define  OVERVOLTAGE         (80.0)        //单位V   过压保护电压    //(DCVOLTAGE*1.2) 
#define  UNDERVOLTAGE        (10.0)        //单位V   欠压保护电压    //(DCVOLTAGE*0.8)  
#define  OVREERVOLTAGE       (65.0)        //单位V   回差电压        //(DCVOLTAGE*1.15)
#define  UNREDERVOLTAGE      (12.0)        //单位V   回差电压        //(DCVOLTAGE*0.85) 
#define  UVNMS               (500)         //单位ms  母线过压判断时间，
#define  OVNMS               (500)         //单位ms  母线欠压判断时间
#define  NONMS               (500)         //单位ms  母线恢复判断时间

//----------------------------------------------------------------------
//过热保护
#define  OH1_EN              (0)           //单位- 过热使能
#define  OH2_EN              (0)           //单位- 过热使能                        
#define  OH3_EN              (0)           //过热使能              
#define  OHRE_EN             (0)           //单位- 恢复重启
#define  OH1NMS              (5000)        //单位- 过热检测时间 OH1
#define  OH2NMS              (5000)        //单位- 过热检测时间 OH2

//======================================================================

//电机参数设置 电机选择
#define  MOTOR_USER_CP       001   //客户产品板电机参数  
//...
#define  MOTOR_VERSION       MOTOR_USER_CP   //电机选择

//板子选择 板子参数选择
#define  FU68xx_USER_CP      001   //客户产品板参数
#define  FU6831_XQ_DDGJ      101   //20.0   2.0   0.002  30.0  1.0
#define  FU68xx_ZY_DEMO      107   //20.0   2.0   0.002  51.0  2.0 
#define  FU6811_FD6536_DEMO  106   //990.0  12.0  0.05   12.0  2.0 
#define  FU68xx_DT_DEMO      301   //10.0   2.0   0.001  20.0  2.0
//...
#define  BOARD_VERSION       FU68xx_USER_CP    //板子选择

//电流保护 计算电机设定  电压保护 根据板子设定
#if (MOTOR_VERSION == MOTOR_USER_CP)
    #define POLE_PAIR     1          //单位* 电机极对数         Y
    #define BASE_VOLTAGE  310        //单位V 电机额定电压       Y
    #define BASE_SPEED    400000       //单位rpm 电机额定转速*1.5 Y
    #define BASE_Rr       23.8        //单位Ω   电机定子电阻     NC
    #define BASE_Ce       35.0        //单位*   电机反电势系数   NC
#endif
//------------------------------------------------------------------------
//The board version         

#if (BOARD_VERSION == FU68xx_USER_CP) 
    //------------------------------------------------------------------------
    //母线电压采样
    #define RV_BUS_1 (10.0)           //单位KΩ 分压电阻    Y
    #define RV_BUS_2 (2.0)            //单位KΩ 采样电阻    Y
    //------------------------------------------------------------------------
    //电流采样
    #define Rs    (0.002)             //单位Ω   采样电阻    Y
    #define RI_BUS_1   (20.0)         //单位KΩ  运算放大器电阻 Y
    #define RI_BUS_2   (2.0)          //单位KΩ  运算放大器电阻 Y
    #define IBUSOFFSET (0)   

#elif (BOARD_VERSION == FU68xx_DT_DEMO) 
    //------------------------------------------------------------------------
    //母线电压采样
    #define RV_BUS_1 (10.0)           //单位KΩ 分压电阻    Y
    #define RV_BUS_2 (2.0)            //单位KΩ 采样电阻    Y
    //------------------------------------------------------------------------
    //电流采样
    #define Rs    (0.01)             //单位Ω   采样电阻    Y
    #define RI_BUS_1   (20.0)         //单位KΩ  运算放大器电阻 Y
    #define RI_BUS_2   (2.0)          //单位KΩ  运算放大器电阻 Y
    #define IBUSOFFSET (0)  
    
#elif (BOARD_VERSION == FU68xx_ZY_DEMO) 
    //------------------------------------------------------------------------
    //母线电压采样
    #define RV_BUS_1 (20.0)           //单位KΩ 分压电阻    Y
    #define RV_BUS_2 (1.0)            //单位KΩ 采样电阻    Y
    //------------------------------------------------------------------------
    //电流采样
    #define Rs    (0.002)             //单位Ω   采样电阻    Y
    #define RI_BUS_1   (24.0)         //单位KΩ  运算放大器电阻 Y
    #define RI_BUS_2   (2.0)          //单位KΩ  运算放大器电阻 Y
    #define IBUSOFFSET (0)   

#elif (BOARD_VERSION == FU6811_FD6536_DEMO) 
    //------------------------------------------------------------------------
    //母线电压采样
    #define RV_BUS_1 (990.0)           //单位KΩ 分压电阻    Y
    #define RV_BUS_2 (12.0)            //单位KΩ 采样电阻    Y
    //------------------------------------------------------------------------
    //电流采样
    #define Rs    (0.05)             //单位Ω   采样电阻    Y
    #define RI_BUS_1   (12.0)         //单位KΩ  运算放大器电阻 Y
    #define RI_BUS_2   (2.0)          //单位KΩ  运算放大器电阻 Y
    #define IBUSOFFSET (0)            //N
#endif

#endif /*__USER_CONF_H*/

