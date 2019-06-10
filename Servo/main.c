#include "keyboard.h"
#include "servo.h"

int main ()
{	
	ServoInit(2000);
	KeyboardInit();

	while(1)
	{
			switch(eKeyboardRead())
			{
				case BUTTON_1:
											ServoCallib();
											break;
				case BUTTON_2:
											ServoGoTo(50);
											break;
				case BUTTON_3:
											ServoGoTo(100);
											break;	
				case BUTTON_4:
											ServoGoTo(150);
											break;
				case RELASED:
											break;
			}
		
	}
}
