
#ifndef  _MMPL_DEFS_H_
#define  _MMPL_DEFS_H_
 			 
typedef enum BOOL{
	FALSE, 
	TRUE 
}BOOL;

/*******************************************************************************************************************
 A structure to hold the complete Modbus request ADU including the "addtional address" field as well as the CRC bytes 
********************************************************************************************************************/
#define RX_BUFFER_SIZE	30
#define TX_BUFFER_SIZE	30

typedef struct
{
	unsigned char  TxBuffer[RX_BUFFER_SIZE];
	unsigned char  pduSize;
}MDB_REQ_ADU;

/*******************************************************************************************************************
 A structure to hold the complete Modbus response ADU including the "addtional address" field as well as the CRC bytes 
/********************************************************************************************************************/
typedef struct
{
	unsigned char  RxBuffer[TX_BUFFER_SIZE];
	unsigned char  pduSize;
}MDB_RSP_ADU;


#define  MODBUS_RTU		0				/* Networks that run off Modbus RTU protocol are usually on RS232 or RS485 media interface */


/**********************************************************************************************************************************************************
*********************************************************************************************************************************************************** 
	The CRC table is an array of 256 bytes used in computing the CRC of Modbus APDUs. By default, for improving efficiency, 
	this array is populated once in the beginning and stored in RAM to be used every time the CRC is to be generated. However, 
	this uses up 256 bytes of data memory which can cause a resource crunch in small foot print devices. So the library 
	provides for two ways of addressing this issue. One is: Since the CRC table is static, it provides an option of placing 
	it in code memory (i.e. flash or EPROM). Other is: It provides an option of dynamically generating the CRC table values 
	as and when the CRC is being computed. 
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/
#define  IN_RAM				0			/* The CRC table is placed in RAM (data memory) */
#define  IN_ROM				1			/* The CRC table is placed in ROM (code memory) */

/********************************************************************************************************************************************************* 
												lIST OF THE ERROR CODES IN MODBUS
**********************************************************************************************************************************************************/

#define  MMPL_NO_ERROR			0x00
#define  UNKNOWN_ERROR			0x01	/* An unknown error occurred reading / writing to port */
#define  INVALID_HANDLE			0x02	/* An invalid handle or path ID was used to read from / write to the port */
#define  INVALID_NETWORKNUM		0x03	/* An uninitialized network number was passed as a parameter */
#define  READ_WRITE_FAIL		0x04	/* Device failure reading / writing to port */
#define  READ_WRITE_TIMEOUT		0x05	/* Timeout occurred reading / writing bytes */
#define  ID_MISMATCH			0x06	/* The slave ID found in the Modbus request does not match this device */
#define  CRC_ERR				0x07	/* The message contained incorrect CRC Bytes */
#define  BUFFER_TOO_SMALL		0x08	/* The request message has more bytes than the available size of buffer */
#define  PORT_CLOSED			0x09	/* The communication port was closed when trying to read or write on it */
#define  INVALID_FC				0x0A	/* An invalid/unsupported function code is requested to be serviced */
#define  TXID_MISMATCH			0x0B	/* The Transaction ID of the Modbus request does not match the response's Transaction ID */
#define  INVALID_PROTCODE		0x0C	/* Invalid Protocol code in the response */
#define  EXCEPTION_RESPONSE		0x0D	/* Exception response from slave */
#define  FC_MISMATCH			0x0E	/* The function code of the Modbus request does not match the response's function code */
#define  INVALID_BYTECNT		0x0F	/* Invalid Byte count in the response */
#define  INVALID_DATA_VALUE		0x10	/* Invalid Data Value */
#define  INVALID_PKTLEN			0x11	/* Invalid Packet Length in the response */
#define  INVALID_SLAVE_ADDR		0x12	/* Invalid Slave ID */
#define  INVALID_NUM_ITEMS		0x13	/* Invalid number of items */
#define  READ_ERROR			    0x14
/********************************************************************************************************************************************************* 
												lIST OF THE IILEGAL FUNCTIONS IN MODBUS
**********************************************************************************************************************************************************/

#define ILLEGAL_FUNCTION		0x01
#define ILLEGAL_DATA_ADDRESS	0x02
#define ILLEGAL_DATA_VALUE		0x03
#define SLAVE_DEVICE_FAILURE	0x04
#define ACKNOWLEDGE				0x05
#define SLAVE_DEVICE_BUSY		0x06
#define MEMORY_PARITY_ERROR		0x08
#define GW_PATH_UNAVAIL			0x0A
#define GW_TARGET_DEV_TIMEOUT	0x0B

 
/********************************************************************************************************************************************************* 
												lIST OF THE INDEX IN MODBUS
**********************************************************************************************************************************************************/
#define INDEX_SLAVE_ID			0
#define INDEX_FUNC_CODE			1
#define INDEX_START_ADDR1		2
#define INDEX_START_ADDR2		3
#define INDEX_NUM_ITEMS1		4
#define INDEX_NUM_ITEMS2		5
#define INDEX_VALUE1			4	 
#define INDEX_VALUE2			5
#define INDEX_WRITE_BYTE_CNT	6
#define INDEX_WRITE_START_DATA	7


#define INDEX_RESP_BYTE_CNT		2
#define INDEX_RESP_START_DATA	3

/**********************************************************************************************************************************************************
												lIST OF THE FUNCTION CODES IN MODBUS
**********************************************************************************************************************************************************/
#define FC_READ_COILS			0x01
#define FC_READ_DISC_IPS		0x02
#define FC_READ_HOLD_REGS		0x03
#define FC_READ_IP_REGS			0x04
#define FC_WRITE_SINGLE_COIL	0x05
#define FC_WRITE_SINGLE_REG		0x06
#define FC_WRITE_MULTIPLE_COILS	0x0F
#define FC_WRITE_MULTIPLE_REGS	0x10

#define SIZE_RESP_PDU_WRITE_BASIC	5
#define WR_BLK_SIZE_REGINFO	64
#define WR_BLK_SIZE_BITINFO 64



#endif 
