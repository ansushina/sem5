          
#include <LPC23xx.H>

#define STB 26 //Port1.26
#define CLK 27 //Port1.27
#define DIO	28 //Port1.28

void delay(unsigned int t) {
//Сбросить таймер
	T0TC = 0x00000000;
//Установить задержку в мс в регистре совпадения MCR
	T0MR0 = t;
//Запустить таймер
	T0TCR = 0x00000001;
//Ожидаем окончания счета
	while (T0TCR&0x1) {};
}

void tm1638_sendbyte(unsigned int x) {
	unsigned int i;
	IODIR1 |= (1<<DIO);//Устанавливаем пин DIO на вывод
	for(i = 0; i < 8; i++)
    {
		IOCLR1=(1<<CLK);//Сигнал CLK устанавливаем в 0
		delay(1);//Задержка 
		if (x&1) 	{IOSET1=(1<<DIO);} //Устанавливаем значение на выходе DIO
		else 			{IOCLR1=(1<<DIO);}
		delay(1);//Задержка
      	x  >>= 1;
     	IOSET1=(1<<CLK);//Сигнал CLK устанавливаем в 1
      	delay(2);			
    }
}

unsigned int tm1638_receivebyte() {
	unsigned int i;
	unsigned int x=0;
	IODIR1 &= ~(1<<DIO);//Устанавливаем пин DIO на ввод
	for(i = 0; i < 32; i++)
   	{
		IOCLR1=(1<<CLK);//Сигнал CLK устанавливаем в 0
		delay(1);
		if (IOPIN1&(1<<DIO)) {
			x |= (1<<i);
		}
		delay(1);
      	IOSET1=(1<<CLK);
      	delay(2);			
    }
	return x;
}

void tm1638_sendcmd(unsigned int x)
{
			IOSET1=(1<<STB);
			IODIR1 = (1<<CLK)|(1<<DIO)|(1<<STB);
			IOCLR1=(1<<STB);
			tm1638_sendbyte(x);
}


void tm1638_setadr(unsigned int adr) {
		tm1638_sendcmd(0xC0|adr);	
}

void tm1638_init() {
		unsigned int i;
		tm1638_sendcmd(0x88);	
		tm1638_sendcmd(0x40);
		tm1638_setadr(0);
		for (i=0;i<=0xf;i++)
			tm1638_sendbyte(0);
		tm1638_sendcmd(0x44);
}


void Timer0_Init(void){
	T0PR = 12000;
	T0TCR = 0x00000002;
	T0MCR = 0x00000006;
	T0MR0 = 1000;
}	


int main (void) {

	unsigned int n,i;

	Timer0_Init(); 

	tm1638_init();

  while(1) {
		tm1638_setadr(1);
		tm1638_sendbyte(1);
		delay(2000);
		tm1638_setadr(1);
		tm1638_sendbyte(0);
		while (1) {
			/* Бесконечный цикл */
			i = 1;
			tm1638_sendcmd(0x46);
			i = tm1638_receivebyte();
			if (i) { 
				tm1638_setadr(5);
				tm1638_sendbyte(1);
				delay(5000);
				tm1638_setadr(5);
				tm1638_sendbyte(0);
				tm1638_setadr(3);
				tm1638_sendbyte(0);
				break;
			}
			else { 
				tm1638_setadr(3);
				tm1638_sendbyte(1);
			} 
		}
	}
}
