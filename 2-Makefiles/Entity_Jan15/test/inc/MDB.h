
#ifndef  _MMPL_C_H_
#define  _MMPL_C_H_

#include "Main.h"


#define RD_BLK_SIZE_REGINFO 32

unsigned char  ModbusOP(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer, unsigned char  numRetries);
unsigned char  ConstructRequest(unsigned char  slaveNo, unsigned char  functionCode, short int startAddress, short int  numItems, unsigned char  *dataBuffer,MDB_REQ_ADU *MbReqAdu, MDB_RSP_ADU *MbRspAdu);
unsigned char  DecodeResponse(MDB_REQ_ADU *pMbReqAdu, MDB_RSP_ADU *pMbRspAdu, unsigned char  *dataBuffer, short int numItems);
unsigned char CheckCrc(MDB_RSP_ADU *pMbRspAdu);

void AppendCrc(MDB_REQ_ADU *pMbReqAdu);
void ShortIntsToBuffer(short int *pSrcBuffer,unsigned char  *pDstBuffer, short int noOfRegs);
void BufferToShortInts(unsigned char  *pSrcBuffer, short int *pDstBuffer, short int noOfRegs);

/**********************************************************************************************************************************************************
**********************************************************************************************************************************************************
	Description: 
	This method is called by the library when it requires reading data bytes from a communication port. If less than the requested number of 
	bytes could be read before timeout occurs, then the function should return CSPL_TRUE and set pNoOfBytesRead to the actual number of bytes read.
	Parameters: 
	a) networkNo (IN): A number identifying the port to be read.
	b) noOfBytesToRead (IN): The number of bytes to read on this port.
	c) pNoOfBytesRead (OUT): A pointer to the variable that receives the actual number of bytes read.
	d) pBuffer (OUT): A pointer to the buffer that receives the data read from the port.
	e) pErrorCode (OUT): A pointer to the variable that receives an error code in case of failure of this function.
	Returns: 
	CSPL_TRUE if the function succeeds, else CSPL_FALSE. If the return value is CSPL_FALSE, then an error code indicating 
	the reason for failure should be stored in the pErrorCode parameter.
**********************************************************************************************************************************************************
**********************************************************************************************************************************************************/


unsigned char ReadPort(short int noOfBytesToRead, unsigned char  *pBuffer);

/**********************************************************************************************************************************************************
**********************************************************************************************************************************************************
	Description: 
	This method is called by the library when it requires writing data bytes to a communication port. If less than the requested number of bytes 
	could be written before timeout occurs, then the function should return CSPL_TRUE and set pNoOfBytesWritten to the actual number of bytes 
	written.
	Parameters: 
	a) noOfBytesToWrite(IN): The number of bytes to write on this port.
**********************************************************************************************************************************************************
***********************************************************************************************************************************************************/

unsigned char WritePacket(short int noOfBytesToWrite);


#endif   
