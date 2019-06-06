/* ========================================
 *
 * Main file of the project for the PSoC 6 master.

 * @author: Davide Marzorati
 * ========================================
*/
#include "project.h"
#include "stdio.h"

// Mask for master status errors
#define MASTER_ERROR_MASK  (CY_SCB_I2C_MASTER_DATA_NAK | CY_SCB_I2C_MASTER_ADDR_NAK    | \
                            CY_SCB_I2C_MASTER_ARB_LOST | CY_SCB_I2C_MASTER_ABORT_START | \
                            CY_SCB_I2C_MASTER_BUS_ERR)    

// I2C Write and Read bytes
#define I2C_WRITE (0x00)
#define I2C_READ  (0x01)

// I2C Slave Address
#define I2C_SLAVE_ADDR (0x20)

// Packet start and command position
#define PACKET_START_POS (0x00)
#define PACKET_CMD_POS   (0x01)

// Packet size
#define TX_PACKET_SIZE    (0x02)
#define RX_PACKET_SIZE    (0x01)

// Status codes
#define TRANSFER_ERROR    (0xFF)
#define TRANSFER_CMPLT    (0x00)
#define READ_ERROR        (TRANSFER_ERROR)
#define READ_CMPLT        (TRANSFER_CMPLT)

void HandleError(void);
static void    CreateCommandPacket(uint8_t cmd);
static uint8_t WriteCommandPacket(uint8_t cmd);
static uint8_t ReadStatusPacket(uint8_t cmd);
static bool    WaitOneUnit(uint32* timeout);

/**
 * Global variables
**/
/* Structure for master transfer configuration */
cy_stc_scb_i2c_master_xfer_config_t masterTransferCfg =
{
    .slaveAddress = I2C_SLAVE_ADDR,
    .buffer       = NULL,
    .bufferSize   = 0U,
    .xferPending  = false
};

uint8_t buffer[TX_PACKET_SIZE];
uint8_t rxBuffer[RX_PACKET_SIZE];

int main(void)
{

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    cy_en_scb_i2c_status_t i2cInitStatus;   // I2C Init Status
    cy_en_scb_i2c_status_t dataRateSet;     // Datarate set Status
    cy_en_sysint_status_t sysStatus;
    cy_en_scb_i2c_status_t deviceStatus;    // Status of I2C connection
    char message[20];       // Data to be sent over uart
    uint8_t cmd = 0;
    
    // Set up I2C master
    i2cInitStatus = Cy_SCB_I2C_Init(I2CM_HW, &I2CM_config, &I2CM_context);
    if (i2cInitStatus != CY_SCB_I2C_SUCCESS)
    {
        HandleError();
    }
    // Set up I2C data rate
    dataRateSet = Cy_SCB_I2C_SetDataRate(I2CM_HW, I2CM_DATA_RATE_HZ, I2CM_CLK_FREQ_HZ);
    if (dataRateSet > I2CM_DATA_RATE_HZ)
    {
        HandleError();
    }
    
    /* Hook interrupt service routine. */
    sysStatus = Cy_SysInt_Init(&I2CM_SCB_IRQ_cfg, &I2CM_Interrupt);
    if(sysStatus != CY_SYSINT_SUCCESS)
    {
        HandleError();
    }
    /* Enable interrupt in NVIC. */
    NVIC_EnableIRQ((IRQn_Type) I2CM_SCB_IRQ_cfg.intrSrc);
    
    Cy_SCB_I2C_Enable(I2CM_HW);
    
    __enable_irq(); /* Enable global interrupts. */
    
    // Set up UART
    cy_en_scb_uart_status_t uartInitStatus;
    uartInitStatus = Cy_SCB_UART_Init(UART_HW, &UART_config, &UART_context);
    if (uartInitStatus != CY_SCB_UART_SUCCESS)
    {
        HandleError();   
    }
    
    Cy_SCB_UART_Enable(UART_HW);

    Cy_SCB_UART_PutString(UART_HW, "** I2C Master **\r\n");
    
    uint8_t increasing = 1;
    
    for(;;)
    {
        /* Place your application code here. */
        
        // Write command packet to slave
        // Check correct completion of transfer
        if (TRANSFER_CMPLT == WriteCommandPacket(cmd))
        {
            if (READ_CMPLT == ReadStatusPacket(cmd))
            {
                // Increase value from 0 to 255
                if (increasing)
                {
                    cmd++;
                    if ( cmd == 0)
                    {
                        increasing = 0;
                        cmd = 254;
                    }
                }
                // Decrease value from 255 to 0
                else
                {
                    cmd--;
                    if ( cmd == 255)
                    {
                        increasing = 1;
                        cmd = 1;
                    }
                }
                // Print out some debug messages
                sprintf(message, "Cmd %d written and checked\r\n", cmd);
                UART_PutString(message);
            }
            else 
            {
                // Print out some debug messages
                sprintf(message, "Cmd %d written but not checked\r\n", cmd);
                UART_PutString(message);  
            }
        }
        else
        {
            sprintf(message, "Cmd %d not written\r\n", cmd);
            UART_PutString(message);
        }
        Cy_SysLib_Delay(10); 
    }
}

void HandleError(void)
{
    // Right now nothing is done to handle errors
    return;   
}


static uint8_t WriteCommandPacket(uint8_t cmd)
{
    uint8_t status = TRANSFER_ERROR;
    cy_en_scb_i2c_status_t  errorStatus;
    // Create packet to be sent to slave
    CreateCommandPacket(cmd);    
    
    // Set up transfer configuration
    masterTransferCfg.buffer = buffer;
    masterTransferCfg.bufferSize = TX_PACKET_SIZE;
    
    // Write buffer over I2C using HIGH LEVEL APIs
    errorStatus = Cy_SCB_I2C_MasterWrite(I2CM_HW, &masterTransferCfg, &I2CM_context);
    
    if(errorStatus == CY_SCB_I2C_SUCCESS)
    {
        uint32_t masterStatus;
        bool     timeOutStatus = false;
        
        //Timeout 1 sec (one unit is us) 
        uint32_t timeout = 1000000UL;
        
        // If write operation is successfull wait until transfer is completed
        do {
            masterStatus = Cy_SCB_I2C_MasterGetStatus(I2CM_HW, &I2CM_context);
            timeOutStatus = WaitOneUnit(&timeout);
        } while((0UL != (masterStatus & CY_SCB_I2C_MASTER_BUSY))
                    && (timeOutStatus == false)); 

        if (timeOutStatus)
        {
            // Timeout recovery 
            Cy_SCB_I2C_Disable(I2CM_HW, &I2CM_context);
            Cy_SCB_I2C_Enable (I2CM_HW);
            UART_PutString("Timeout occurred\r\n"); 
        }
        else
        {
            if ((0u == (masterStatus & MASTER_ERROR_MASK )) && 
                    (TX_PACKET_SIZE == Cy_SCB_I2C_MasterGetTransferCount(I2CM_HW, &I2CM_context)))
            {
                status = TRANSFER_CMPLT;    
            }
        }
    }
        
    return status;
}


static void CreateCommandPacket(uint8_t cmd)
{
    buffer[PACKET_START_POS]   = 0x00;
    buffer[PACKET_CMD_POS]   = cmd;
}

static uint8_t ReadStatusPacket(uint8_t cmd)
{
    uint8_t status = READ_ERROR;
    cy_en_scb_i2c_status_t errorStatus;
    
    // Set up transfer configuration
    masterTransferCfg.buffer = rxBuffer;
    masterTransferCfg.bufferSize = RX_PACKET_SIZE;
    
    uint8_t data;
    
    errorStatus = Cy_SCB_I2C_MasterRead(I2CM_HW, &masterTransferCfg, &I2CM_context);
    if (errorStatus == CY_SCB_I2C_SUCCESS)
    {
        uint32_t masterStatus;
        bool     timeOutStatus = false;
        uint32_t timeout = 100000UL;
        
        do
        {
            masterStatus  = Cy_SCB_I2C_MasterGetStatus(I2CM_HW, &I2CM_context);
            timeOutStatus = WaitOneUnit(&timeout);
        } while ( 0UL != (masterStatus & CY_SCB_I2C_MASTER_BUSY) 
            && (timeOutStatus == false));
        
        if (timeOutStatus)
        {
            Cy_SCB_I2C_Disable(I2CM_HW, &I2CM_context);
            Cy_SCB_I2C_Enable(I2CM_HW);
        }
        else
        {
            if (0u == (MASTER_ERROR_MASK & masterStatus))
            {
                if ( rxBuffer[0] == cmd)
                {
                    status = READ_CMPLT;    
                }
            }
        }
        
    }
    return (status);
}


static bool WaitOneUnit(uint32_t *timeout)
{
    uint32_t status = 0UL;

    /* If the timeout equal to 0. Ignore the timeout. */
    if (*timeout > 0UL)
    {
        Cy_SysLib_DelayUs(CY_SCB_WAIT_1_UNIT);
        --(*timeout);

        if (0UL == *timeout)
        {
            status = true;
        }
    }

    return (status);
}

/* [] END OF FILE */
