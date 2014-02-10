void forward();
int  main(){
	//wait_for_light(1);
	//shut_down_in(118);
	motor(0,200);
	motor(2,200);
	msleep(3*1000); //move forward for three seconds
	printf("done");
return 0;
}
	//:)
