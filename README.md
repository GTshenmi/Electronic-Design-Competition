# Electronic-Design-Competition

###  `放大器非线性失真研究装置`

#### `项目介绍`
-------

        本项目是根据2020江苏省电子设计竞赛E题-放大器非线性失真研究装置的要求，参考集成运放电路的设计原则，制作出了一款放大器非线性失真
    研究装置，能够生成放大后的标准正弦波，以及四种失真的正弦波形（顶部失真、底部失真、双向失真、交越失真波形），并基于stm32f407平台，计
    算出任意波形的总谐波失真，显示在OLED屏幕上。
    
#### `系统展示`
-------
|   电源电路及电压抬升电路    |   波形产生电路    |   波形切换测试    |   
|:---------------:|:---------------:|:---------------:| 
|![image10](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/10.JPG)|![image12](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/12.jpg)|![image11](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/11.jpeg)|
|   顶部失真波形    |波形切换及总谐波失真测量电路|   底部失真波形    |   
|![image4](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/4.jpeg)|![image3](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/3.jpeg)|![image5](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/5.jpeg)|
|   双向失真波形    |    正常波形             |      交越失真波形            |   
|![image7](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/7.jpeg)|![image6](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/6.jpeg)|![image8](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/8.jpeg)|

###  `纸张计数装置`

#### `项目介绍`
-------

        本装置是基于模板匹配算法实现的纸张计数测量系统，主要由单片机控制模块、OLED液晶屏幕、FDC2214、按键、蜂鸣器等构成。纸张计数模块测量由三块亚克力立板和两块   
    极板构成，与测量显示电路模块通过20cm导线相连，测试时抬起顶层亚克力板，放置纸张，放下亚克力板，通过FDC2214来测量纸张张数的变化。此装置以MK66为主控芯片，由其
    读取FDC2214传感器的数据、进行模式选择，数据运算及控制显示。 
    
#### `系统展示`
-------
|   纸张计数显示    |   纸张计数装置    |
|:---------------:|:---------------:|
|![image0](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/0.jpeg)|![image1](https://github.com/GTshenmi/Electronic-Design-Competition/blob/main/Display%20Image/1.jpeg)|
