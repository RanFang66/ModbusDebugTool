#include "modbus_ctx.h"


modbus_ctx::modbus_ctx(const char* ComPort, int Baud, int Parity, int DataBits, int StopBits)
    : m_ComPort(ComPort), m_Baudrate(Baud), m_ParityCheck(Parity), m_DataBits(DataBits), m_StopBits(StopBits), m_connect_state(false)
{
}

int modbus_ctx::ModbusRtuInit()
{
    ctx = modbus_new_rtu(m_ComPort, m_Baudrate, m_ParityCheck, m_DataBits, m_StopBits);
    if (ctx == NULL)
        return -1;

    return 0;
}

int modbus_ctx::ModbusRtuConnect()
{
    int ret = 0;
    modbus_set_slave(ctx, 1);
    modbus_set_response_timeout(ctx, 3, 0);
    ret = modbus_connect(ctx);
    if (ret != -1) {
        m_connect_state = true;
    }
    return ret;
}

void modbus_ctx::ModbusRtuDisconnect()
{
    modbus_close(ctx);
    m_connect_state = false;
}

void modbus_ctx::setComPort(QString &port)
{
    QByteArray byte = port.toUtf8();
    char *str = byte.data();

    m_ComPort = str;
}

void modbus_ctx::setBaudrate(int baud)
{
    m_Baudrate = baud;
}

int modbus_ctx::WriteHoldingRegs(int addr, int len, register_t *data)
{
    return modbus_write_registers(ctx, addr, len, data);
}

int modbus_ctx::ReadInputRegs(int addr, int len)
{
    return modbus_read_input_registers(ctx, addr, len, RecvBuff);
}

int modbus_ctx::ReadHoldingRegs(int addr, int len)
{
    return modbus_read_registers(ctx, addr, len, RecvBuff);
}

int modbus_ctx::WriteSingleReg(int addr, register_t data)
{
    return modbus_write_register(ctx, addr, data);
}
