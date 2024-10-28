# 关于

TinyCmd是一个运行在微控制器上的紧凑型命令模块。它使用回调函数提供了一个类似 Bash 的控制系统，支持命令输入与执行，以及信息输出，使用简单容易移植，无论是在开发阶段进行功能测试，还是编写跨设备的控制功能（例如AT指令）TinyCmd都可以为你提供一个简单高效的方法去完成这些功能。

例如stm32单片机中，只需要一个串口发送字符的函数和一个串口中断函数（如果你需要中断）就可以实现一个命令行控制各种功能的系统，例如使用命令控制LED亮灭，控制PWM的输出，等各种功能。



<img src=".\media\TinyCmd_Logo.jpg" alt="LOGO" width="400" height="auto">



#### 小广告

- 你不需要再使用stdio.h和printf重定向了，TinyCmd为你提供了一个类似printf的字符串输出函数，你可以像使用printf那样打印你的到任意位置，完成这个功能只需要1行代码。
- TinyCmd创建命令及其方便，你只需要2行代码就可以创建一个可用的命令，当然，实现命令功能的回调函数是需要你自己编写的，编写起来也非常方便。
- TinyCmd提供了一个超方便的参数转数字函数，你只需要传入等待赋值的参数的地址和需要转换的参数的索引，以及需要转换的参数的类型，TinyCmd就会为你将这个字符串参数转换为合适的数字。
- 还在犹豫要不要使用TInyCmd吗，如果你错过了一天，那你就真的错过了一天，快点下载TinyCmd并开始使用吧



# 文档

[README简体中文](./README_ZH.md)		

[README](./README.md)		

### API 参考

[API手册中文](./API_Reference_ZH.md)

[API Reference](https://tongyi.aliyun.com/API_Reference.md)



# 测试功能

编译示例代码 `gcc *.c` 并运行

- `./a.exe`
- `./a.out`

#### 输出



<img src=".\media\Output.jpg" alt="Output" width="400" height="auto">

更多详情请参见 `demo.c` 文件。



### 在 STM32F103C8T6 上测试

测试电路图如下所示。

示例路径：`.\Demo\STM32F103C8T6\Demo_ARMCompiler6`



<img src=".\media\TinyCmd_STM32_Demo.jpg" alt="Schematic" width="400" height="auto">



### 在 Arduino Uno 上测试

测试电路图如下所示。

示例路径：`.\Demo\Arduino\ATMEGA328P`



<img src=".\media\TinyCmd_Arduino_Uno.jpg" alt="Schematic" width="400" height="auto">



#### 持续更新中...