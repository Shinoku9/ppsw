#include "keyboard.h"
#include "servo.h"

int main ()
{	
	ServoInit(20);
	KeyboardInit();

	while(1)
	{
			switch(eKeyboardRead())
			{
				case BUTTON_1:
											break;
				case BUTTON_2:
											ServoGoTo(12);
											break;
				case BUTTON_3:
											ServoGoTo(24);
											break;	
				case BUTTON_4:
											ServoGoTo(36);
											break;
				case RELASED:
											break;
			}
		
	}
}
