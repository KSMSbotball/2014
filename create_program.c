// Created on Sat February 16 2013
	/*
	
	*/
#define TRACE {printf("*** EXECUTING at line %d\n", __LINE__);}// debugging statment
#define REFLECTOR_PORT 0
#define SLEEPTIME 1
#define LIGHTSENSOR 2
//For seeding set SEEDING=1, For double elmination set RUNMODE=2
#define RUNMODE 1
void navigate();


int main()
{
	int connect_result;
	connect_result = create_connect();

		//wait_for_light(LIGHTSENSOR);
	//run_for(115,*navigate);
	//navigate();
	shut_down_in(120);
	navigate();
		
} //close int main

void navigate()
{
	
		int white_counter=0;
		int spin_counter=0;
		int turn_counter=0;
		int stage=0;
		double start_time=seconds();
		double turn_time=start_time;
		
		int wall_sensor;
		
	while (1)//navigation routine
		{	 
			printf("***navigating routine\n");				
			if(RUNMODE==1) // RUNMODE 1 is for seeding 
			{

				if(analog(REFLECTOR_PORT)<130)//In white
					{
					//Turn right
					int leftspeed=10;//250(-60)
					int rightspeed=200;//-60(250)
					
					create_drive_direct(rightspeed,leftspeed);
					msleep(1);//3.2				
					white_counter++;
					}
				
				else if(analog(REFLECTOR_PORT)>130)//In Black
					{
					// turn left
					int leftspeed=250;//40 
					int rightspeed=70;//100
					
					create_drive_direct(rightspeed,leftspeed);
					msleep(1);
					white_counter = 0;
					}
				
				if(white_counter > 7) //90 DEGREE ANGLE REACHED OR IM LOST
					{
					//turn 90 degrees

					int leftspeed=-35;//120(-60)
					int rightspeed=100;//10(250)
				    
						while (analog(REFLECTOR_PORT)<130)//turn until in black again
						{
						create_drive_direct(rightspeed,leftspeed);
					    msleep(1);
						}
						
					spin_counter++;
					printf("spin_counter: %d\n", spin_counter);
					}
					if(spin_counter>=6)//100,50
					{
					
						printf("Entering BOX/n");
					{
			
					create_spin_CW(50);
					msleep(200000000);
					}
				
				if(white_counter>=10)//100,50
					{
					
						printf("I'm LOST on the RIGHT/n");
						int leftspeed=500;//40 
						int rightspeed=-100;//100
						
						create_drive_direct(rightspeed,leftspeed);
						msleep(200);
						
						white_counter = 0;
					}
					
				
			
			
	// RUNMODE 2 is for double elimination		
			if(RUNMODE==2) 
			{
				printf("**double elimination\n");
				if(analog(REFLECTOR_PORT)<130)//In white
					{
					//Turn right
					int leftspeed=10;//250(-60)
					int rightspeed=200;//-60(250)
					
					create_drive_direct(rightspeed,leftspeed);
					msleep(1);//3.2				
					white_counter++;
					}
				
				else if(analog(REFLECTOR_PORT)>130)//In Black
					{
					// turn left
					int leftspeed=250;//40 
					int rightspeed=70;//100
					
					create_drive_direct(rightspeed,leftspeed);
					msleep(1);
					white_counter = 0;
					}
				
				if(white_counter > 7) //90 DEGREE ANGLE REACHED OR IM LOST
					{
					//turn 90 degrees
					int leftspeed=-35;//120(-60)
					int rightspeed=10;//10(250)
				    
						while (analog(REFLECTOR_PORT)<130)//turn until in black again
						{
						create_drive_direct(rightspeed,leftspeed);
					    msleep(1);
						}
						
					spin_counter++;
					printf("spin_counter: %d\n", spin_counter);
					}
					if(spin_counter>=4)//completed circle
					{
						//finished 90 degree turn
						printf("completed 90 degree turn!/n");
						msleep(500);
						//drive straight ahead after 90 degree
						create_drive_straight(1000);
						msleep(900);
						//left 90 degree turn into box
						int spinspeed=2000;
						create_spin_CCW(spinspeed);
						msleep(330);
						//drive into otherside rocket area
						create_drive_straight(750);//1000
						msleep(1300);//1500
						
						break;
					}
				}
	}//close navigate while	
}//close navigate
}
}



		

