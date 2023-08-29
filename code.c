/*
 ============================================================================
 Name        : Mini project1.c
 Author      : Omar Shaaban
 Version     :
 Copyright   : Your copyright notice
 Description : Vehicle Control system
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 /*To control engine control data*/
enum vehicle_state {
	Turn_on, Turn_off, Quit
};
enum state {
	OFF, ON
};
/*Global Variables*/
char start_input, sensors_input;
int ret_script;
int vehicle_speed = 80;
int room_temp = 25;
int AC = OFF;
int engine_temp = 125;
int Engine_temp_controller = OFF;
/*Functions prototype*/
void display_start_menu(void);
int chosen_script(char *start_input_ptr);
void display_sensors_set_menu(void);
void chosen_sensor(char *sensors_input_ptr);
void Turn_off_func(int indicator);
void Turn_on_func(void);
void traffic_color_func(void);
void room_temperature(void);
#if WITH_ENGINE_TEMP_CONTROLLER==1
void engine_temperature(void);
#endif
void Display_the_current_vehicle_state(void);
void speed_is30(void);
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	if (vehicle_speed == 30) {/*Check if the initial speed is 30 km/hr*/
		speed_is30();/*doing the 30 km/hr speed scenario*/
	}
	display_start_menu();
	scanf(" %c", &start_input);
	ret_script = chosen_script(&start_input);
	if (ret_script == Quit) {
		return 0;
	}

	return 0;
}
/*START MENU*/
void display_start_menu(void) {
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
}
/*CHOSEN SCRIPT FROM START MENU*/
int chosen_script(char *start_input_ptr) {
	switch (*start_input_ptr) {
	case 'A':
	case 'a':
		Turn_on_func();
		break;

	case 'B':
	case 'b':
		Turn_off_func(0);/*pass '0' indicates that 'chosen_script' is the caller*/
		break;

	case 'C':
	case 'c':
		printf("Quit the system\n");
		return Quit;

	default:
		printf("WRONG CHOICE!!");
	}
	return -1;/*TERMINATE THE FUNCTION*/
}
/*SENSORS SET MENU*/
void display_sensors_set_menu(void) {
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER==1
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif
}
/*CHOSEN SCRIPT FROM SNSORS MENU*/
void chosen_sensor(char *sensors_input_ptr) {
	switch (*sensors_input_ptr) {
	case 'A':
	case 'a':
		Turn_off_func(1);/*pass '1' indicates that 'chosen_sensor' is the caller*/
		break;

	case 'B':
	case 'b':
		traffic_color_func();
		break;

	case 'C':
	case 'c':
		room_temperature();
		break;
#if WITH_ENGINE_TEMP_CONTROLLER==1
	case 'D':
	case 'd':
		engine_temperature();
		break;
#endif
	default:
		printf("WRONG INPUT!!");

	}

}
/*Turn off function (there are two scenario depends on the caller)*/
void Turn_off_func(int indicator) {
	if (indicator == 0) {/* '0' if called from start menu*/
		while (start_input == 'b' || start_input == 'B') {
			printf("Turn off the vehicle engine\n\n");
			display_start_menu();
			scanf(" %c", &start_input);
		}
		chosen_script(&start_input);

	}

	else if (indicator == 1) {/* '1' if called from snsors menu*/
		if (sensors_input == 'a' || sensors_input == 'A') {
			start_input = 'b'; /*to get in the loop*/
			while (start_input == 'b' || start_input == 'B') {
				printf("Turn off the vehicle engine\n\n");
				display_start_menu();
				scanf(" %c", &start_input);
			}
		}

		chosen_script(&start_input);

	}
}
/*Turn on function*/
void Turn_on_func(void) {
	display_sensors_set_menu();
	scanf(" %c", &sensors_input);
	chosen_sensor(&sensors_input);
}
/*Traffic color function*/
void traffic_color_func(void) {
	printf("Enter the required color:\n");
	char traffic_color;
	scanf(" %c", &traffic_color);
	switch (traffic_color) {
	case 'g':
	case 'G':
		vehicle_speed = 100;
		Display_the_current_vehicle_state();
		Turn_on_func();
		return;

	case 'o':
	case 'O':
		vehicle_speed = 30;
		speed_is30();/*doing the 30 km/hr speed scenario*/
		Display_the_current_vehicle_state();
		Turn_on_func();
		return;

	case 'r':
	case 'R':
		vehicle_speed = 0;
		Display_the_current_vehicle_state();
		Turn_on_func();
		return;
	default:
		printf("WRONG CHOISE!!");

	}
}
/*Room temperature function*/
void room_temperature(void) {
	printf("Enter the room temperature:\n");
	scanf(" %d", &room_temp);
	if (room_temp < 10) {
		AC = ON;
		room_temp = 20;
		Display_the_current_vehicle_state();
		Turn_on_func();

	} else if (room_temp > 30) {
		AC = ON;
		room_temp = 20;
		Display_the_current_vehicle_state();
		Turn_on_func();

	} else {
		AC = OFF;
		Display_the_current_vehicle_state();
		Turn_on_func();
	}
}
/*Engine temperature function*/
#if WITH_ENGINE_TEMP_CONTROLLER==1
void engine_temperature(void){
	printf("Enter the engine temperature:\n");
	scanf(" %d",&engine_temp);
	if(engine_temp<100){
		Engine_temp_controller=ON;
		engine_temp=125;
		Display_the_current_vehicle_state();
		Turn_on_func();

	}
	else if(engine_temp>150){
		Engine_temp_controller=ON;
		engine_temp=125;
		Display_the_current_vehicle_state();
		Turn_on_func();

	}
	else{
		Engine_temp_controller=OFF;
		Display_the_current_vehicle_state();
		Turn_on_func();
	}
}
#endif
/*Display the current vehicle state*/
void Display_the_current_vehicle_state(void) {
	printf("Engine is ON\n");
	if (AC == ON)
		printf("AC is ON\n");
	else
		printf("AC is OFF\n");
	printf("Vehicle Speed:  %d Km/Hr\n", vehicle_speed);
	printf("Room Temperature:  %d C\n", room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER==1
	if(Engine_temp_controller==ON)
	printf("Engine Temperature Controller is ON\n");
	else
	printf("Engine Temperature Controller is OFF\n");
	printf("Engine Temperature:  %d C\n\n",engine_temp);
#endif

}
/*30 km/hr speed scenario*/
void speed_is30(void) {
	if (AC == OFF) {
		AC = ON;
		room_temp = room_temp * 5 / 4 + 1;
	}
#if WITH_ENGINE_TEMP_CONTROLLER==1
	if(Engine_temp_controller==OFF){
					Engine_temp_controller=ON;
					engine_temp=engine_temp*5/4+1;
				}
#endif

}

