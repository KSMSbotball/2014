int main() {
	set_a_button_text("press me to stop liking trains");
	while (a_button() == 0){
		printf("i like trains\n");
	}
	printf("i don't like trains");
return 0;
}
