#include "header.h"

int fd_uart;
pthread_t pid_uart_get;
pthread_t pid_uart_send;


/*************************************************************************************************
* �������ݰ�ת��
* �������ݰ���β:0XFE
* 0XFE --> 0XD5F5
* 0XD5 --> 0XD5A5
**************************************************************************************************/
uint16_t Data_ChangeInto(uint8_t *InBuf, uint16_t InLen, uint8_t *OutBuf)
{
	uint16_t OutLen = 0;
	for(uint16_t i = 0;i < InLen;i++)
		{
		if( InBuf[i] == 0xFE )
			{
			OutBuf[OutLen] = 0xD5;
			OutBuf[OutLen+1] = 0xF5;
			OutLen = OutLen + 2;
			}
		else if( InBuf[i] == 0xD5 )
			{
			OutBuf[OutLen] = 0xD5;
			OutBuf[OutLen+1] = 0xA5;
			OutLen = OutLen + 2;
			}
		else
			{
			OutBuf[OutLen] = InBuf[i];
			OutLen++;
			}
		}

	return OutLen;
}
/*************************************************************************************************
* �������ݰ���ת��
**************************************************************************************************/
uint16_t Data_ChangeBack(uint8_t *InBuf, uint16_t InLen, uint8_t *OutBuf)
{
	uint16_t OutLen = 1;

	OutBuf[0] = InBuf[0];
	for(uint16_t i = 1;i < InLen;i++)
		{
		if( InBuf[i] == 0xF5 && InBuf[i-1] == 0xD5 )
			{OutBuf[OutLen-1] = 0xFE;}
		else if( InBuf[i] == 0xA5 && InBuf[i-1] == 0xD5 )
			{OutBuf[OutLen-1] = 0xD5;}
		else
			{
			OutBuf[OutLen] = InBuf[i];
			OutLen++;
			}
		}

	return OutLen;
}








// ===============================================================================
void serialPutString(const int fd, const uint8_t *buf, const uint16_t len) 
{
	for(uint16_t i = 0;i < len;i++)
		{
		serialPutchar(fd, buf[i]);
		}
}


void* thread_uart_get()
{
	uint8_t  RxData;

	while(1)
		{
		RxData = serialGetchar(fd_uart);
		//�������ݴ���
		...
		}
}

void* thread_uart_send()
{

}
  
int main(void)
{
	void *ret;
	uint8_t FifoBuffer[256];
	int16_t AudioDataBuffer[300];
	
	//��ȡ��ǰ�Ĺ���Ŀ¼
	//getcwd(WorkSpace_Path , 60);  
	//printf("WorkSpace:%s(len:%d)\n" , WorkSpace_Path, strlen(WorkSpace_Path));  	

	//�򿪴���
	if(wiringPiSetup() < 0)
		{return 1;}
	
	//if((fd_uart = serialOpen("/dev/ttyAMA0",460800)) < 0)
	if((fd_uart = serialOpen("/dev/ttyAMA0",115200)) < 0)
		{return 1;}

	//�����߳����ڴ������ݻ�ȡ
	int err = pthread_create(&pid_uart_get, NULL, thread_uart_get, NULL);
	if(err == 0)
  		{printf("Pthread1 create success.\n");}
	else
		{
		printf("Pthread1 create error.\n");
		return 1;
		}

	//�����߳����ڴ������ݷ���
	err = pthread_create(&pid_uart_send, NULL, thread_uart_send, NULL);
	if(err == 0)
  		{printf("Pthread2 create success.\n");}
	else
		{
		printf("Pthread2 create error.\n");
		return 1;
		}	

	//������ѭ��
	while(1)
		{

		}
	
	serialClose(fd_uart);
	return 0;	
}


