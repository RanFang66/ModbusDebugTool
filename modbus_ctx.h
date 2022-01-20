#ifndef MODBUS_CTX_H
#define MODBUS_CTX_H

#include "QtCore"
#include "modbus.h"

#define     BUFF_SIZE   128

typedef uint16_t register_t;

class modbus_ctx
{
public:
    modbus_ctx(const char *ComPort = "COM1", int Baud = 38400, int Parity = 'N', int DataBits = 8, int StopBits = 1);
    int ModbusRtuInit(void);
    int ModbusRtuConnect();
    void ModbusRtuDisconnect();
    void setComPort(QString &);
    void setBaudrate(int baud);

    int ReadInputRegs(int addr, int len);
    int ReadHoldingRegs(int addr, int len);
    int WriteSingleReg(int addr, register_t data);
    int WriteHoldingRegs(int addr, int len, register_t *data);

    inline bool ModbusRtuIsConnected()
    {
        return m_connect_state;
    }
private:
    modbus_t *ctx;
    const char* m_ComPort;
    int     m_Baudrate;
    int     m_ParityCheck;
    int     m_DataBits;
    int     m_StopBits;
    bool    m_connect_state;
    register_t     RecvBuff[BUFF_SIZE];
    register_t     SendBuff[BUFF_SIZE];
};

#endif // MODBUS_CTX_H
