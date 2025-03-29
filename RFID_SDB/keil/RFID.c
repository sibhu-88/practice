#include <LPC21xx.H>

void UART_INIT(){
	 PINSEL0 |= 0X5;
	 U0LCR = 0x83;
	 U0DLL = 97;
	 U0LCR = 0X03;
}

void UART_TX(char D){
	U0THR = D;
	while(!(U0LSR>>5&1));
}

char UART_RX(){
	while(!(U0LSR&1));
	return	U0RBR;
}

void UART_TX_STR(char *D){
	while(*D){
		UART_TX(*D++);	
	}							   
}


int main(){
	char CH,I;
		UART_INIT();
	//	UART_TX_STR("SDB_RFID\n\r");
	//	while(1){		I=10;
			while(I){
			 	CH = UART_RX();
				UART_TX(CH);
			 	I--;
			}
	//		 UART_TX_STR("\n\r");	}
}

