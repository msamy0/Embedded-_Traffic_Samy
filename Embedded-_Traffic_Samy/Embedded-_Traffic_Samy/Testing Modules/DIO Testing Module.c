#include "../MCAL/DIO/DIO.h"

#define TEST_PIN 18
#define TEST_PORT B

DIO_error_handler result = -1;
int main ()
{
	
	if ((result = DIO_init(TEST_PIN,TEST_PORT,OUT_pin)) != DIO_OK)
	{
		return 1;
	}
	while (1)
	{
		if((result = DIO_write(TEST_PIN,TEST_PORT,ON_value) != DIO_OK))
		{	
		return 1;
		}
		for (int x =0 ; x <100 ; x++)
		{
			//delay some time
		}
		
		if((result = DIO_write(TEST_PIN,TEST_PORT,OFF_value) != DIO_OK))
		{
			return 1;
		}
		for (int x =0 ; x <5000 ; x++)
		{
			//delay some time
		}
	}
	return 0;
}