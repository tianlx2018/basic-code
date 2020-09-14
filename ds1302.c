/*   �ӳٺ��� */
void delayMS(unsigned int ms)   //@11.0592MHz
{
	unsigned char y;
	while (ms--)
	{
		for (y = 0; y<100; y++)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

void delay2us()		//@11.0592MHz
{
	unsigned char t;

	t = 3;
	while (--t);
}

void DelayXus(uint us)   //@11.0592MHz
{
	while(us--);
}



/*************DS1302ʱ��ģ��&DS18B20�¶�ģ�������������******************************/

/*DS1302��������*/

/*************д��һ�ֽ�****************/
void DS1302_Input_Byte(char Input)  //��ʱ��ICд��һ�ֽ�
{
	char i;
	T_SCLK = 0;
	delay2us();
	ACC =Input;
	for(i=8; i>0; i--)
	{
		T_DIO = ACC_0;            //�൱�ڻ���е� RRC
		delay2us();
		T_SCLK = 1;
		delay2us();
		T_SCLK = 0;
		ACC = ACC >> 1;
	}
}

/*************��ȡһ�ֽ�****************/
char DS1302_Output_Byte(void)      //��ʱ��IC��ȡһ�ֽ�()
{
	char i;
	for(i=8; i>0; i--)
	{
		ACC>>=1;
		T_DIO= 1;
		delay2us();
		ACC_7 = T_DIO;
		T_SCLK = 1;                 //�൱�ڻ���е� RRC
		delay2us();
		T_SCLK = 0;
		delay2us();
	}
	T_DIO = 0;
	delay2us();
	return(ACC);
}

/*************дһ�ֽ�����****************/
void DS1302_Write_one( char addr,dat )       // д���ַ�������ӳ���
{
	T_CE=0;                             //T_CE����Ϊ�ͣ����ݴ�����ֹ
	T_SCLK=0;                          //����ʱ������
	T_CE = 1;                          //T_CE����Ϊ�ߣ��߼�������Ч
	DS1302_Input_Byte(addr);           // ��ַ������
	DS1302_Input_Byte(dat);          // д1Byte����
	T_SCLK = 1;
	T_CE = 0;
}

/*************��һ�ֽ�����****************/
char DS1302_Read ( char addr )    //���ݶ�ȡ�ӳ���
{
	char date;
	T_CE=0;
	T_SCLK=0;
	T_CE = 1;
	DS1302_Input_Byte(addr);        // ��ַ������
	date = DS1302_Output_Byte();         // ��1Byte����
	T_SCLK = 1;
	T_CE = 0;
	return(date);
}


/*************д��ʱ������****************/
void DS1302_Write(char sec_w,min_w,hour_w,day_w,month_w,week_w,year_w)
{
	DS1302_Write_one(0x8e,0x00);
	DS1302_Write_one(0x82,min_w);
	DS1302_Write_one(0x84,hour_w);
	DS1302_Write_one(0x86,day_w);
	DS1302_Write_one(0x88,month_w);
	DS1302_Write_one(0x8a,week_w);
	DS1302_Write_one(0x8c,year_w);
	DS1302_Write_one(0x80,sec_w);
	DS1302_Write_one(0x8e,0x80);

}

/*************ʱ��ת��Ϊ��ʾ��ʽ****************/
void timeConvert()
{
	sec_1 = sec>>4;
	sec_2 = sec&0x0f;
	min_1 = min>>4;
	min_2 = min&0x0f;
	hour_1 = hour>>4;
	hour_2 = hour&0x0f;

}

/*************��оƬ��ȡʱ��****************/
void DS1302_readtime()
{
	sec=DS1302_Read(0x81);                    //����
	min=DS1302_Read(0x83);                    //����
	hour=DS1302_Read(0x85);                   //��ʱ
	day=DS1302_Read(0x87);                    //����
	month=DS1302_Read(0x89);                  //����
	year=DS1302_Read(0x8d);                   //����
	week=DS1302_Read(0x8b);                   //������
	timeConvert();

}




/*************��Ƭ����ʼ������******************************/
void init()
{
	//�ر�����С��
	E1=1;
	E2=1;
	E3=1;
	E4=1;
	MDLIGHT = 1;
	P1 = allclear;
	T_CE = 0;
	T_SCLK = 0;

	//Ĭ�ϳ�ʼ��ʱ��12:00
	sec = 0x00;
	min = 0x00;
	hour = 0x16;
	year = 0x01;
	month = 0x01;
	week = 0x01;
	day = 0x01;
	status = 1;
	keyValue = 0;
	delayMS(1000);
	//DS1302��ʼ���ж��Ƿ���ں󱸵�Դ

	if(DS1302_Read(0x81)&0x80==0x80)
	{
		DS1302_Write_one(0x8e,0x00);
		DS1302_Write_one(0x80,sec);  //����
		DS1302_Write_one(0x8e,0x80);
	}
	else
	{

	}
}
