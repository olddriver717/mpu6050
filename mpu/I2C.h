#ifndef __MPUI2C_H
#define __MPUI2C_H

#include "sys.h"

// IO方向设置
#define SDA_IN()                  \
    {                             \
        GPIOB->CRH &= 0XFFFFFF0F; \
        GPIOB->CRH |= 8 << 4;     \
    }
#define SDA_OUT()                 \
    {                             \
        GPIOB->CRH &= 0XFFFFFF0F; \
        GPIOB->CRH |= 3 << 4;     \
    }

// IO口引脚定义
#define IIC_SCL PBout(8) // SCL
#define IIC_SDA PBout(9) // SDA
#define READ_SDA PBin(9) // 输入SDA

// IIC所有操作函数
void IIC_Init(void);                      // 初始化IIC的IO口
int IIC_Start(void);                      // 发送IIC开始信号
void IIC_Stop(void);                      // 发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);          // IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack); // IIC读取一个字节
int IIC_Wait_Ack(void);                   // IIC等待ACK信号
void IIC_Ack(void);                       // IIC发送ACK信号
void IIC_NAck(void);                      // IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
unsigned char I2C_Readkey(unsigned char I2C_Addr);

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr, unsigned char addr);
unsigned char IIC_Write_Byte(unsigned char dev, unsigned char reg, unsigned char data);
uint8_t IIC_Write_Bytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_Write_Bits(uint8_t dev, uint8_t reg, uint8_t bitStart, uint8_t length, uint8_t data);
uint8_t IIC_Write_Bit(uint8_t dev, uint8_t reg, uint8_t bitNum, uint8_t data);
uint8_t IIC_Read_Bytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);

int I2C_Write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int I2C_Read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

#endif
