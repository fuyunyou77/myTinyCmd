#include "TinyCmd.h"


#define LED_PIN 8

volatile bool is_blinking = false;
volatile int n_times = 0;
volatile unsigned long last_blink_time = 0;

TinyCmd_CallBack_Ret LED_Callback() {
  // Command: LED ON
  // Effect: Turn on LED on PA1.
  if (TinyCmd_Arg_Check("ON", 0) == TINYCMD_SUCCESS) {
    digitalWrite(LED_PIN, HIGH);
    return TINYCMD_SUCCESS;
  }
  // Command: LED OFF
  // Effect: Turn off LED on PA1.
  else if (TinyCmd_Arg_Check("OFF", 0) == TINYCMD_SUCCESS) {
    digitalWrite(LED_PIN, LOW);
    return TINYCMD_SUCCESS;
  }
  
  return TINYCMD_FAILED;
}

TinyCmd_Command LED_Command = {"LED", LED_Callback};

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("Setup started");

  // 添加命令到命令列表
  TinyCmd_Add_Cmd(&LED_Command);

  // 设置LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Setup completed");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    // 将读取的字符添加到缓冲区
    TinyCmd_buf.input[TinyCmd_buf.length++] = c;

    // 检查是否接收到换行符
    if (c == '\n') {

      // 打印接收到的字符串
      Serial.print("Received: ");
      Serial.println(TinyCmd_buf.input);

      // 调用命令处理器
      TinyCmd_Handler();

    }
  }
}



// 主函数
int main(void) {
  setup();

  sei();  // 启用全局中断

  while (1) {
    loop();
  }

  return 0;
}