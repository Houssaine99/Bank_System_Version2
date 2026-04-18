
#include <iostream>

#include "Lib/clsUtil.h"
#include "Screens/clsLoginScreen.h"


 

int main()
{
	
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}

	return 0;
}
