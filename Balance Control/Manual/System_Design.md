# 平衡系统架构设计

- 主控制器
    - 读取加速度、转角
    - 计算需要的转速、转动方向、滑块目标位置
    - SPI 传送参数给步进电机控制器
    - 通讯序列定义：  
    //// 尽量短，避免多个byte来表示一个数，但有时候必须用多个byte

        - 转速或所需转速对应的PWM半周期参数
        - 滑块目标位置 
        /// 根据后面设计的控制算法，包括了方向反馈，这里应该不需要提供方向的参数了
        - 校验位
        /// 校验不通过则放弃接收结果，步进电机控制器相应指示灯亮

    - 编码器的信号得同时输入主控制器和步进电机控制器

- 步进电机控制器
    - 中断接收参数
    /// 进入中断后可能要立即把PWM信号暂时交由Timer来维持（也许可以Arduino）
    - for 循环输出PWM
    - for 循环内侦测已经移动的距离，修改for 循环参数以控制输出的脉冲数
    - 步进电机控制器伪代码：

<code>

    //// 单向控制 ////
    //// 如果加入方向，需要处理 i 和 round 的大小问题 ////

    int round = 1000;   // 目标位置
    int half_T = 5000;  // PWM半周期控制参数
    int i,j;
    for(i=Read_Encoder_Value();abs(i-round);i+=direction){
        // Duty Half Period
        PWM_High();    // Set IO Level High
        for(j=0;j<half_T,abs(i-round);j++){
            Set_Direction(i,round);     // Set direction
            i=Read_Encoder_Value();     // Update index. 
            /// 这里 i（脉冲序号） 和 编码器读数应该需要考虑一下换算关系
            half_T=Correct_PWM_halfT();
        }

        // Ground Half Period
        PWM_Low();
        for(j=0;j<half_T,abs(i-round);j++){
            Set_Direction(i,round);
            i=Read_Encoder_Value();
        }
    }
</code>