#include <xmc_gpio.h>
#include <xmc_common.h>
#include <xmc4_gpio.h>

uint32_t button1check;

uint32_t button2check;

uint32_t currenttime=0;

uint32_t button1firstpush=0;

uint32_t button1secondpush=0;

uint32_t button1timediff=0;

char button1time_str[];

uint32_t clk=0;

int dottime_ms=100;

void countdown(){
	if(clk!=0x00){
	clk--;
}
}



void dot(void){

XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1,1);
wait(1);
XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1,1);

}

void dash(void){
XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1,1);
wait(3);
XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1,1);
}

void wait(int numdot){
//for(int32_t waiter=12000*dottime_ms*numdot; waiter >= 0; waiter--);
clk=numdot*100;
while (clk!=0){}

}

void SysTick_Handler(void){
countdown();
currenttime++;

}


void sequence(char letter){
switch(letter){
case 'A':
dot();
wait(1);
dash();
break;

case 'B':

dash();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
break;

case 'C':
dash();
wait(1);
dot();
wait(1);
dash();
wait(1);
dot();
break;


case 'D':
dash();
wait(1);
dot();
wait(1);
dot();
break;


case 'E':
dot();
break;

case 'F':
dot();
wait(1);
dot();
wait(1);
dash();
wait(1);
dot();
break;

case 'G':
dash();
wait(1);
dash();
wait(1);
dot();
break;

case 'H':
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
break;

case 'I':
dot();
wait(1);
dot();
break;

case 'J':
dot();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
break;

case 'K':
dash();
wait(1);
dot();
wait(1);
dash();
break;

case 'L':
dot();
wait(1);
dash();
wait(1);
dot();
wait(1);
dot();
break;


case 'M':
dash();
wait(1);
dash();
break;

case 'N':
dash();
wait(1);
dot();
break;

case 'O':
dash();
wait(1);
dash();
wait(1);
dash();
break;

case 'P':
dot();
wait(1);
dash();
wait(1);
dash();
wait(1);
dot();
break;

case 'Q':
dash();
wait(1);
dash();
wait(1);
dot();
wait(1);
dash();
break;

case 'R':
dot();
wait(1);
dash();
wait(1);
dot();
break;

case 'S':
dot();
wait(1);
dot();
wait(1);
dot();
break;

case 'T':
dash();
break;

case 'U':
dot();
wait(1);
dot();
wait(1);
dash();
break;

case 'V':
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dash();
break;

case 'W':
dot();
wait(1);
dash();
wait(1);
dash();
break;

case 'X':
dash();
wait(1);
dot();
wait(1);
dot();
wait(1);
dash();
break;

case 'Y':
dash();
wait(1);
dot();
wait(1);
dash();
wait(1);
dash();
break;

case 'Z':
dash();
wait(1);
dash();
wait(1);
dot();
wait(1);
dot();
break;

case ' ':
wait(1);
break;

case '1':
dot();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
break;

case '2':
dot();
wait(1);
dot();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
break;

case '3':
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dash();
wait(1);
dash();
break;

case '4':
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dash();
break;

case '5':
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
break;

case '6':
dash();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
break;

case '7':
dash();
wait(1);
dash();
wait(1);
dot();
wait(1);
dot();
wait(1);
dot();
break;

case '8':
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dot();
wait(1);
dot();
break;

case '9':
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dot();
break;

case '0':
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
dash();
wait(1);
break;
}
}



int main(void) {
 
XMC_GPIO_SetMode(XMC_GPIO_PORT1,1,XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
SystemInit();

SysTick_Config(SystemCoreClock/1000);
//SysTick_Config(SystemCoreClock/1000);

char str[]="I CAN MORSE";
int lengthstr=strlen(str);
int lentime;
int transmission=0;
int flag=0;

while(1){
button1check=XMC_GPIO_GetInput(XMC_GPIO_PORT1,14);
button2check=XMC_GPIO_GetInput(XMC_GPIO_PORT1,15);


if(button1check==0 && button1firstpush==0 && flag!=1){
transmission=1;
button1firstpush=currenttime;
flag=1;

}

if(button1check==0 && button1firstpush !=0 && button1secondpush==0 && flag !=1){
transmission=1;
button1secondpush=currenttime;
flag=1;

}

if(button1check==0 && button1firstpush !=0 && button1secondpush!=0 && flag!=1){
transmission=1;
button1firstpush=button1secondpush;
button1secondpush=currenttime;
flag=1;

}

flag=0;



//if(transmission && button2check==1){
if(transmission){

for(uint8_t ind=0 ; ind<lengthstr ; ind++){

sequence(str[ind]);

wait(3);

}
transmission=0;
//wait(47);


}

if(button2check==0 && button1secondpush==0){

itoa(button1firstpush,button1time_str,10);
lentime=strlen(button1time_str);

for(uint8_t ind=0 ; ind<lentime ; ind++){

sequence(button1time_str[ind]);

wait(3);

}


}

if(button2check==0 && button1secondpush!=0){

	button1timediff=button1secondpush-button1firstpush;
	itoa(button1timediff,button1time_str,10);
	lentime=strlen(button1time_str);

for(uint8_t ind=0 ; ind<lentime ; ind++){

sequence(button1time_str[ind]);

wait(3);

}


}


}

	
  return 0;
}
