// Created on Thu March 13 2014

int main()
{
	create_connect();
	
	create_drive_straight(200);
	while(!get_create_lbump() && !get_create_rbump());
	create_stop();
	
	create_disconnect();
	
	return 0;
}
