// Created on Thu March 13 2014

#define A 0

int main()
{
	create_connect();
	
	create_drive_straight(200);
	
	
	create_disconnect();
	//what are you guys trying to do here?
	if (A)=(1)
	
	else
	//hey guys here is a "nicer way" more programer like to write teh same thing below
	//while(!get_create_lbump() && !get_create_rbump());
	//we could also create a function that does go forward until bumping against something
	//KIPR program has a similar function forwardUntilBlackLine(int inches) which goes forward
	//for either the number of inches or when it encounter the black or goes over 
	//void 	(no infrared reflection)
	while (get_create-lbump() == 0 && get_create_rbump() == 0) {
		//sleep i.e do nothing
		msleep(50);
	}
	// I now stop since I have bumped against something. 
	create_stop();
	
	
	return 0;
	
}
