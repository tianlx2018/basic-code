/*   延迟函数 */
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



/*************DS1302时间模块&DS18B20温度模块相关驱动函数******************************/

/*DS1302驱动函数*/

/*************写入一字节****************/
void DS1302_Input_Byte(char Input)  //向时钟IC写入一字节
{
	char i;
	T_SCLK = 0;
	delay2us();
	ACC =Input;
	for(i=8; i>0; i--)
	{
		T_DIO = ACC_0;            //相当于汇编中的 RRC
		delay2us();
		T_SCLK = 1;
		delay2us();
		T_SCLK = 0;
		ACC = ACC >> 1;
	}
}

/*************读取一字节****************/
char DS1302_Output_Byte(void)      //从时钟IC读取一字节()
{
	char i;
	for(i=8; i>0; i--)
	{
		ACC>>=1;
		T_DIO= 1;
		delay2us();
		ACC_7 = T_DIO;
		T_SCLK = 1;                 //相当于汇编中的 RRC
		delay2us();
		T_SCLK = 0;
		delay2us();
	}
	T_DIO = 0;
	delay2us();
	return(ACC);
}

/*************写一字节数据****************/
void DS1302_Write_one( char addr,dat )       // 写入地址、数据子程序
{
	T_CE=0;                             //T_CE引脚为低，数据传送中止
	T_SCLK=0;                          //清零时钟总线
	T_CE = 1;                          //T_CE引脚为高，逻辑控制有效
	DS1302_Input_Byte(addr);           // 地址，命令
	DS1302_Input_Byte(dat);          // 写1Byte数据
	T_SCLK = 1;
	T_CE = 0;
}

/*************读一字节数据****************/
char DS1302_Read ( char addr )    //数据读取子程序
{
	char date;
	T_CE=0;
	T_SCLK=0;
	T_CE = 1;
	DS1302_Input_Byte(addr);        // 地址，命令
	date = DS1302_Output_Byte();         // 读1Byte数据
	T_SCLK = 1;
	T_CE = 0;
	return(date);
}


/*************写入时间数据****************/
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

/*************时间转换为显示格式****************/
void timeConvert()
{
	sec_1 = sec>>4;
	sec_2 = sec&0x0f;
	min_1 = min>>4;
	min_2 = min&0x0f;
	hour_1 = hour>>4;
	hour_2 = hour&0x0f;

}

/*************从芯片读取时间****************/
void DS1302_readtime()
{
	sec=DS1302_Read(0x81);                    //读秒
	min=DS1302_Read(0x83);                    //读分
	hour=DS1302_Read(0x85);                   //读时
	day=DS1302_Read(0x87);                    //读日
	month=DS1302_Read(0x89);                  //读月
	year=DS1302_Read(0x8d);                   //读年
	week=DS1302_Read(0x8b);                   //读星期
	timeConvert();

}




/*************单片机初始化函数******************************/
void init()
{
	//关闭所有小灯
	E1=1;
	E2=1;
	E3=1;
	E4=1;
	MDLIGHT = 1;
	P1 = allclear;
	T_CE = 0;
	T_SCLK = 0;

	//默认初始化时间12:00
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
	//DS1302初始化判断是否存在后备电源

	if(DS1302_Read(0x81)&0x80==0x80)
	{
		DS1302_Write_one(0x8e,0x00);
		DS1302_Write_one(0x80,sec);  //起振
		DS1302_Write_one(0x8e,0x80);
	}
	else
	{

	}
}
