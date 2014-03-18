#define LIGHT_SENSOR 0

//declaration
int main()
{
	/* FIRST CALIBRATION: based on poms position adjust starting position
	*/
	while (a_button_clicked() == 0) {

		
		printf("IR sensor value is: %d \n" , analog(LIGHT_SENSOR));
		printf("press b button for IR reading, a button to exit\n");
		while (b_button_clicked() == 0 & a_button_clicked() == 0) {
			msleep(25);
		}
	}
	printf("the end...\n");
}
