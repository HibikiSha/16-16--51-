/*-----------------------------------------------
  ���ƣ�16x16������������ʾ
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  Ӳ����LY-51S V4.0 ��Ƭ��������
  ���ݣ�
        P1.0-P1.3�ֱ�����A��B��C��D�����ڿ���16�У�ͨ��2·HC138����
		SER��P1.4 ͨ��2ƬHC595����
        CLKʱ������P1.5
        LAT��������P1.6
		OE��P1.7

  ����ʹ����ͨ�ٶ�51ϵ�е�Ƭ����1��������ʾ��������������ʾ������֣��ظ�ѭ����ʾ��
------------------------------------------------*/
#include<reg52.h>

sbit J32_LAT = P1^6;       //��������
sbit J32_SER = P1^4;       //��������
sbit J32_CLK = P1^5;       //ʱ������
sbit J32_OE  = P1^7;       //ʹ������
sbit J37_LAT = P1^3;       //��������
sbit J37_SER = P1^1;       //��������
sbit J37_CLK = P1^2;       //ʱ������
sbit KEY=P3^3;
unsigned char MoveBitNum,MoveBitNumtemp,IncNum;//�ƶ�λ��,��ʱ�ƶ�λ��������һ���ֽ������ֽ���
unsigned int HzNum;//���ָ���
unsigned char buff[10];
unsigned int flag;
/*-----------------------------------------------
             16x16����ȡģ����
------------------------------------------------*/
unsigned char code hztest1[][32]=    //ȡģѡ���ֽ�����
{


	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //ǰ��һ����С�Ŀ��ַ�������ʾ������������Ĵ�С�޸ģ������1��������
	//����д��1������
	/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x04,0x40,0x0E,0x50,0x78,0x48,0x08,0x48,0x08,0x40,0xFF,0xFE,0x08,0x40,0x08,0x44,
0x0A,0x44,0x0C,0x48,0x18,0x30,0x68,0x22,0x08,0x52,0x08,0x8A,0x2B,0x06,0x10,0x02,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x08,0x01,0xFC,0x7E,0x10,0x22,0x10,0x11,0x20,0x7F,0xFE,0x42,0x02,0x82,0x04,
0x7F,0xF8,0x04,0x00,0x07,0xF0,0x0A,0x10,0x11,0x20,0x20,0xC0,0x43,0x30,0x1C,0x0E,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x08,0x80,0x08,0x80,0x08,0x80,0x11,0xFE,0x11,0x02,0x32,0x04,0x34,0x20,0x50,0x20,
0x91,0x28,0x11,0x24,0x12,0x24,0x12,0x22,0x14,0x22,0x10,0x20,0x10,0xA0,0x10,0x40,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,

/*--  ����:  ǧ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x80,0x20,0x40,0x13,0xFC,0x12,0x04,0x02,0x04,0x03,0xFC,0xF2,0x00,0x13,0xFC,
0x13,0x54,0x15,0x54,0x15,0xFC,0x19,0x54,0x11,0x44,0x11,0x0C,0x28,0x00,0x47,0xFE,





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //β����һ���Ŀ��ַ�����������������������С�йء�
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,


};
unsigned char code hztest2[][32]=    //ȡģѡ���ֽ�����
{


0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",1*/
	//����д��1������		0x
	0xBF,0xFF,0xBF,0xFF,0xDF,0xC0,0xDF,0xEE,
	0xEF,0xEE,0xD7,0xEE,0xDB,0xC0,0xDC,0xFF,
	0xDB,0x00,0xD7,0xFE,0xEF,0xEE,0xDF,0xDE,
	0xDF,0xE0,0xBF,0xFF,0xBF,0xFF,0xFF,0xFF,/*"��",0*/

	0xBF,0xFF,0xBF,0xBF,0xBD,0xDF,0x33,0xE0,
	0xFF,0xDF,0xDF,0xBB,0xDD,0xB1,0xDD,0xBA,
	0x5D,0xBB,0x9D,0xBB,0xDD,0xBB,0xDD,0xBA,
	0xDD,0xB9,0xDF,0xB3,0xFF,0xBF,0xFF,0xFF,/*"��",1*/

	0xFD,0xF7,0xFD,0xFB,0xFD,0xFD,0xFD,0xFE,
	0x3D,0x00,0x4D,0xBF,0x71,0xBF,0x7D,0xBF,
	0x7D,0xBF,0x7D,0xBF,0x7D,0xBF,0x7D,0xBF,
	0x7D,0x00,0xFD,0xFF,0xFD,0xFF,0xFF,0xFF,/*"ʯ",2*/

	0xFF,0xFF,0xEF,0xBF,0xEF,0xDF,0xEF,0xEF,
	0xEF,0xEF,0xEF,0xD7,0xEE,0xBB,0xE9,0xBD,
	0xEF,0xBE,0x6F,0xBF,0xAF,0xBF,0xCF,0xBF,
	0xEF,0xBF,0xFF,0xBF,0xFF,0xBF,0xFF,0xFF,/*"֮",3*/

	0xFF,0xFF,0x07,0x00,0xFE,0xFF,0xF9,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFD,0xFF,0xFD,0xFF,
	0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0xFD,0xBF,
	0xFD,0x7F,0x01,0x80,0xFF,0xFF,0xFF,0xFF,/*"��",4*/





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",1*/


};

unsigned char code a[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char code b[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


/*-----------------------------------------------
             ��595д��һ���ֽ� ����ɫ
------------------------------------------------*/
void InputByte1( unsigned  char DataR1) //дһ���ֽ�
{
	unsigned  char i;
	for(i=8; i>0; i--)
	{
		J32_SER = (DataR1&0x01);
		J32_CLK = 0;
		J32_CLK = 1;
		DataR1 = DataR1 >> 1;
	}
}
void InputByte2( unsigned  char DataR1) //дһ���ֽ�
{
	unsigned  char i;
	for(i=8; i>0; i--)
	{
		J37_SER = (DataR1&0x01);
		J37_CLK = 0;
		J37_CLK = 1;
		DataR1 = DataR1 >> 1;
	}
}

void Input2Byte1(unsigned char dat1,unsigned char dat2)
{
	unsigned  char i;
	for(i=8; i>0; i--)
	{
		J37_SER = (dat1&0x01);
		J37_CLK = 0;
		J37_CLK = 1;
		dat1 = dat1 >> 1;
	}
		for(i=8; i>0; i--)
	{
		J37_SER = (dat2&0x01);
		J37_CLK = 0;
		J37_CLK = 1;
		dat2 = dat2 >> 1;
	}


}
void Input2Byte2(unsigned char dat1,unsigned char dat2)
{
	unsigned  char i;
		for(i=8; i>0; i--)
	{
		J32_SER = (dat2&0x01);
		J32_CLK = 0;
		J32_CLK = 1;
		dat2 = dat2 >> 1;
	}
	for(i=8; i>0; i--)
	{
		J32_SER = (dat1&0x01);
		J32_CLK = 0;
		J32_CLK = 1;
		dat1 = dat1 >> 1;
	}

}

/*-----------------------------------------------
                    ��ʱ����
------------------------------------------------*/
void Delay(unsigned int t)
{
	while(--t);
}
void DelayUs2x(unsigned char t)
{
 while(--t);
}
void DelayMs(unsigned char t)
{

 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}


/*-----------------------------------------------
                      ������
------------------------------------------------*/
main()
{
	unsigned char count;//16��ɨ�����ݣ���Χ0-15
	unsigned int i, j;
	unsigned char temp;
	unsigned int inter;
	KEY=1; //��������˿ڵ�ƽ�ø�
	inter=0;
	flag=1;
	//���������Ԫ�ظ�����������Ҫ���Ǻ��ֵĸ���
	while(1){
	if(flag==1){
	int lenTotal = sizeof(hztest1) / sizeof(int);  //����
	int lenLow = sizeof(hztest1[0]) / sizeof(int);  //��λ
	int lenHigh = lenTotal / lenLow;  //��λ
	while(1)
	{
		if(!KEY)  //�����⵽�͵�ƽ��˵����������
 {
DelayMs(10); //��ʱȥ����һ��10-20ms
	if(!KEY)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	{
		 while(!KEY);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
			flag++;//�ͷ���ִ����Ҫ�ĳ���
	 		inter=1;
	}
}}
 if(inter==1){
	 inter=0;
	 break;
 }
		i++;
		if(i==180)//���������ٶ�,1T��Ƭ����12T��Ƭ���ٶȴ�Լ5-8����ע����Ĳ���
		{
			i=0;
			MoveBitNum++;
			if(MoveBitNum==16)//ÿ���ƶ���һ�����ִ�С��ѭ��
			{
				MoveBitNum=0;
				HzNum+=1;    //������һ������
				if(HzNum>=lenHigh-1)//��Ҫ��ʾ�ĺ��ָ���������ǰ���һ�����ַ��ĸ��������������Ŀ��ַ�����������,������(���ָ���+1)
					HzNum=0;   //��ȫ��ʾ���ѭ������
			}
		}


		Delay(1);//����ɨ��Ƶ��
		//��ȡ���ֶ�Ӧ��Ļ�����������ݣ���ͬ��С����Ļ��һ��
		for(j=0; j<2; j++) //ȡÿ�����ֵ�ǰ2���ֽڣ�
		{
			//���ָ���+1
			buff[j+j+1]=hztest1[HzNum+j][count+count+1];  //ÿ���ƶ���һ�����ֺ�ѡ����һ������
			buff[j+j]=hztest1[HzNum+j][count+count];


		}
		//�ж��ƶ���λ��
		if(MoveBitNum<8)                   //  �ж��ƶ������Ǵ���һ���ֽڻ���С��һ���ֽڣ���Ϊһ���ֽ������������ֻ��8λ
		{
			IncNum=0;
			MoveBitNumtemp=MoveBitNum;
		}
		else
		{
			IncNum=1;    //����8�ͼ�ȥ8�õ�����ֵ����С��8
			MoveBitNumtemp=MoveBitNum-8;
		}
		J32_LAT=0;       //������Ч
		J37_LAT=0;
		if(count<8)
			{
				if(count==0){Input2Byte1(0xff,a[7]);}
				else{Input2Byte1(a[count-1],0xff);}

			}
			else
			{
				if(count==8){Input2Byte1(a[7],0xff);}
				else{Input2Byte1(0xff,a[count-8-1]);}
			}
		J37_LAT = 1;
		J37_LAT=0;
		for(j=2; j>0; j--)        //��bit�ķ�ʽ�ƶ������������ݣ�Ȼ�������595����ȡ������ֵÿ���ֽ�����һ����λ����
		{
			//�������Ƴ����������ϵ�ǰ����ֽ��У��������ݵ�������
			temp=(buff[j-1+IncNum]<<MoveBitNumtemp)|(buff[j+IncNum]>>(8-MoveBitNumtemp));
			InputByte1(temp);//�����595
		}//8���ֽڴ������������
		//����ʹ�ܶ�
		J32_OE  = 1;
		J32_LAT=1;      //������Ч����ʱһ�е�������ʾ������
		J32_OE = 0;
		count++;
		if(count==16)
			count=0;
	}}
	if(flag==2){
		int lenTotal = sizeof(hztest1) / sizeof(int);  //����
int lenLow = sizeof(hztest1[0]) / sizeof(int);  //��λ
int lenHigh = lenTotal / lenLow;  //��λ

while(1)
{
	if(!KEY)  //�����⵽�͵�ƽ��˵����������
{
DelayMs(10); //��ʱȥ����һ��10-20ms
if(!KEY)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
{
	 while(!KEY);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
		{
		flag++;//�ͷ���ִ����Ҫ�ĳ���
 		inter=1;
}
}}
if(inter==1){
 inter=0;
 break;
}

	i++;
	if(i==180)//���������ٶ�,1T��Ƭ����12T��Ƭ���ٶȴ�Լ5-8����ע����Ĳ���
	{
		i=0;
		MoveBitNum++;
		if(MoveBitNum==16)//ÿ���ƶ���һ�����ִ�С��ѭ��
		{
			MoveBitNum=0;
			HzNum+=1;    //������һ������
			if(HzNum>=lenHigh-1)//��Ҫ��ʾ�ĺ��ָ���������ǰ���һ�����ַ��ĸ��������������Ŀ��ַ�����������,������(���ָ���+1)
				HzNum=0;   //��ȫ��ʾ���ѭ������
		}
	}


	Delay(1);//����ɨ��Ƶ��
	//��ȡ���ֶ�Ӧ��Ļ�����������ݣ���ͬ��С����Ļ��һ��
	for(j=0; j<2; j++) //ȡÿ�����ֵ�ǰ2���ֽڣ�
	{
		//���ָ���+1
	//	buff[j+j+1]=hztest[HzNum+j][count+count+1];  //ÿ���ƶ���һ�����ֺ�ѡ����һ������
		//buff[j+j]=hztest[HzNum+j][count+count];
		buff[j+j]=hztest1[HzNum+j][count+count+1];  //ÿ���ƶ���һ�����ֺ�ѡ����һ������
		buff[j+j+1]=hztest1[HzNum+j][count+count];

	}
	//�ж��ƶ���λ��
	if(MoveBitNum<8)                   //  �ж��ƶ������Ǵ���һ���ֽڻ���С��һ���ֽڣ���Ϊһ���ֽ������������ֻ��8λ
	{
		IncNum=0;
		MoveBitNumtemp=MoveBitNum;
	}
	else
	{
		IncNum=1;    //����8�ͼ�ȥ8�õ�����ֵ����С��8
		MoveBitNumtemp=MoveBitNum-8;
	}
	J32_LAT=0;       //������Ч
	J37_LAT=0;
			if(count<8)
				{
					if(count==0){Input2Byte1(0xff,a[7]);}
					else{Input2Byte1(a[count-1],0xff);}

				}
				else
				{
					if(count==8){Input2Byte1(a[7],0xff);}
					else{Input2Byte1(0xff,a[count-8-1]);}
				}
	J37_LAT = 1;
	J37_LAT=0;
	for(j=0; j<3; j++)        //��bit�ķ�ʽ�ƶ������������ݣ�Ȼ�������595����ȡ������ֵÿ���ֽ�����һ����λ����
	{
		//�������Ƴ����������ϵ�ǰ����ֽ��У��������ݵ�������
		//temp=(buff[j-1+IncNum]<<MoveBitNumtemp)|(buff[j+IncNum]>>(8-MoveBitNumtemp));
		temp = (buff[j-1+IncNum]>>MoveBitNumtemp|buff[j+IncNum]<<(8-MoveBitNumtemp));
		InputByte1(temp);//�����595
	}//8���ֽڴ������������
	//����ʹ�ܶ�
	J32_OE  = 1;
	J32_LAT=1;      //������Ч����ʱһ�е�������ʾ������
	J32_OE = 0;
	count++;
	if(count==16)
		count=0;
}
}
  if(flag==3){
		int lenTotal = sizeof(hztest2) / sizeof(int);  //����
int lenLow = sizeof(hztest2[0]) / sizeof(int);  //��λ
int lenHigh = lenTotal / lenLow;  //��λ


	while(1)
	{
		if(!KEY)  //�����⵽�͵�ƽ��˵����������
	{
	DelayMs(10); //��ʱȥ����һ��10-20ms
	if(!KEY)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
	{
		 while(!KEY);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
			{
			flag++;//�ͷ���ִ����Ҫ�ĳ���
	 		inter=1;
	}
	}}
	if(inter==1){
	 inter=0;
	 if(flag>3){flag=1;}
	 break;
	}

	i++;
	if(i==180)//���������ٶ�,1T��Ƭ����12T��Ƭ���ٶȴ�Լ5-8����ע����Ĳ���
	{
		i=0;
		MoveBitNum++;
		if(MoveBitNum==16)//ÿ���ƶ���һ�����ִ�С��ѭ��
		{
			MoveBitNum=0;
			HzNum+=1;    //������һ������
			if(HzNum>=lenHigh-1)//��Ҫ��ʾ�ĺ��ָ���������ǰ���һ�����ַ��ĸ��������������Ŀ��ַ�����������,������(���ָ���+1)
				HzNum=0;   //��ȫ��ʾ���ѭ������
		}
	}


	Delay(1);//����ɨ��Ƶ��
	//��ȡ���ֶ�Ӧ��Ļ�����������ݣ���ͬ��С����Ļ��һ��
	for(j=0; j<2; j++) //ȡÿ�����ֵ�ǰ2���ֽڣ�
	{
		//���ָ���+1
		buff[j+j]=hztest2[HzNum+j][count+count+1];  //ÿ���ƶ���һ�����ֺ�ѡ����һ������
		buff[j+j+1]=hztest2[HzNum+j][count+count];


	}
	//�ж��ƶ���λ��
	if(MoveBitNum<8)                   //  �ж��ƶ������Ǵ���һ���ֽڻ���С��һ���ֽڣ���Ϊһ���ֽ������������ֻ��8λ
	{
		IncNum=0;
		MoveBitNumtemp=MoveBitNum;
	}
	else
	{
		IncNum=1;    //����8�ͼ�ȥ8�õ�����ֵ����С��8
		MoveBitNumtemp=MoveBitNum-8;
	}
	J32_LAT=0;       //������Ч
	J37_LAT=0;
			if(count<8)
				{
					Input2Byte2(b[count],0x00);

				}
				else
				{
					Input2Byte2(0x00,b[count-8]);
				}
	J37_LAT = 1;
	J37_LAT=0;
	for(j=2; j>0; j--)        //��bit�ķ�ʽ�ƶ������������ݣ�Ȼ�������595����ȡ������ֵÿ���ֽ�����һ����λ����
	{
		//�������Ƴ����������ϵ�ǰ����ֽ��У��������ݵ�������
		temp=(buff[j-1+IncNum]<<MoveBitNumtemp)|(buff[j+IncNum]>>(8-MoveBitNumtemp));
		InputByte2(temp);//�����595
	}//8���ֽڴ������������
	//����ʹ�ܶ�
	J32_OE  = 1;
	J32_LAT=1;      //������Ч����ʱһ�е�������ʾ������
	J32_OE = 0;
	count++;
	if(count==16)
		count=0;
}
	}
}
}
