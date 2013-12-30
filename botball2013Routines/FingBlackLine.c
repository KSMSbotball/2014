// Created on Thu January 31 2013
#define SPEED 10
#define TIME  3

void stopBot ();
void goRight(int time);
void goLeft(int time);
void goStraight(int time);



int main()
{
	
	set_a_button_text("follow on outside");
	set_c_button_text("follow on inside");
	set_b_button_text("stop");
	printf("The bot is aliging against the blackline, please wait");
	while (1) {
		if (analog(5) < 200) {
			printf("going left\n");
			goRight(1);
		}
	
		//all done if both reflector are on black line
		if (analog(5) > 200 ) {
			printf("Breakingfrom first loop\n");
			stopBot();
			break;
		}
		
		
	}
	printf("command the robot using the buttons\n");
	/*
	a variable indicating whether the robot is to follow the black line on the inside 
	or outside
	6 --> outside
	7 --> inside
	*/
	int followOn = 7;
	
	while (1) {
		//printf("a=%i,b=%i,c=%i\n",a_button(),b_button(),c_button());
		/* this will be a multi
		line comment that should end with 
		*/
		
		if (a_button() == 1) {
			//follow black line on the outside 
			printf("following the outside\n");
			followOn = 6;
		}	
		if (c_button() == 1) {
			//follow black line on the inisde
			printf("following the inside\n");
			followOn = 7;
			
		}	
		
		if (analog(followOn) < 200 ) {
			if (followOn == 6) {
				printf("going left\n");
				goLeft(1);
			} 
			if (followOn == 7 ) {
				printf("goig right\n");
				goRight(1);
			}
		} else 	{
			if (followOn == 7) {
				printf("going left\n");
				goLeft(1);
			} 
			if (followOn == 6 ) {
				printf("goig right\n");
				goRight(1);
			}
		}
		msleep (100);

		if (b_button() == 1) {
			//stop the bot
			stopBot();
			msleep(100);
			
		}	
	}
	
	return 0;
}


//goes right for a certain amount of time
void goLeft(int time) {
	motor(0,SPEED/3);
	motor(2,SPEED);
	msleep(time*2);
}

//goes left for a certain amount of time
void goRight(int time) {
	motor(0,SPEED);
	motor(2,SPEED/3);
	msleep(time*2);
}

//goes left for a certain amount of time
void goStraight(int time) {
	motor(0,SPEED);
	motor(2,SPEED);
	msleep(time*2);
}


//thid function stops he ot
void stopBot() {
		printf("Bot is now stopping!\n");
		motor(0,0);
		motor(2,0);
}
