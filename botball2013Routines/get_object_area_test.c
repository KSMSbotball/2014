// Created on Sat March 9 2013
#define chan 0

int main()
{	
	camera_open(LOW_RES);
	while(1){
		int i=0;
		while(i<=10){
			camera_update();
			i++;
		}
		int area=get_object_area(chan, 0);
		if(get_object_count(chan)>0){
			
			printf("The area of the largest object is %d\n", area);
			msleep(10);
		}else{
			printf("No objects detected\n");
		}
	}
	return 0;
}
