/*
 ============================================================================
 Name        : Mini.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
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
int vehicle_speed = 80;
int room_temp = 25;
int AC = OFF;
int engine_temp = 125;
int Engine_temp_controller = OFF;
/*Functions prototype*/
void display_start_menu(void);
void display_sensors_set_menu(void);
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
	unsigned char flag;
	char start_input, sensors_input;
	if (vehicle_speed == 30) {/*Check if the initial speed is 30 km/hr*/
		speed_is30();/*doing the 30 km/hr speed scenario*/
	}
	do {
		flag = 1;
		display_start_menu();
		scanf(" %c", &start_input);
		switch (start_input) {
		case 'A':
		case 'a':
			while (flag != 0) {
				display_sensors_set_menu();
				scanf(" %c", &sensors_input);
				switch (sensors_input) {
				case 'A':
				case 'a':
					printf("Turn off the vehicle engine\n\n");
					flag = 0;
					break;

				case 'B':
				case 'b':
					traffic_color_func();
					if (vehicle_speed == 30) {/*if the traffic light is orange*/
						speed_is30();
					}
					Display_the_current_vehicle_state();
					break;

				case 'C':
				case 'c':
					room_temperature();
					Display_the_current_vehicle_state();
					break;
#if WITH_ENGINE_TEMP_CONTROLLER==1
				case 'D':
				case 'd':
					engine_temperature();
					Display_the_current_vehicle_state();
					break;
#endif
				default:
					printf("WRONG INPUT!!");
				}
			}

			break;

		case 'B':
		case 'b':
			printf("Turn off the vehicle engine\n\n");
			flag = 0;
			break;

		case 'C':
		case 'c':
			printf("Quit the system\n");
			return Quit;

		default:
			printf("WRONG CHOICE!!");
		}

	} while (flag == 0);
}

void display_start_menu(void) {
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
}

void display_sensors_set_menu(void) {
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER==1
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif
}
void traffic_color_func(void) {
	printf("Enter the required color:\n");
	char traffic_color;
	scanf(" %c", &traffic_color);
	switch (traffic_color) {
	case 'g':
	case 'G':
		vehicle_speed = 100;
		return;

	case 'o':
	case 'O':
		vehicle_speed = 30;
		return;

	case 'r':
	case 'R':
		vehicle_speed = 0;
		return;
	default:
		printf("WRONG CHOISE!!");

	}
}
void room_temperature(void) {
	printf("Enter the room temperature:\n");
	scanf(" %d", &room_temp);
	if ((room_temp < 10) || (room_temp > 30)) {
		AC = ON;
		room_temp = 20;

	} else {
		AC = OFF;

	}
}
#if WITH_ENGINE_TEMP_CONTROLLER==1
void engine_temperature(void) {
	printf("Enter the engine temperature:\n");
	scanf(" %d", &engine_temp);
	if ((engine_temp < 100) || (engine_temp > 150)) {
		Engine_temp_controller = ON;
		engine_temp = 125;

	} else {
		Engine_temp_controller = OFF;

	}
}
#endif
void Display_the_current_vehicle_state(void) {
	printf("Engine is ON\n");
	if (AC == ON)
		printf("AC is ON\n");
	else
		printf("AC is OFF\n");
	printf("Vehicle Speed:  %d Km/Hr\n", vehicle_speed);
	printf("Room Temperature:  %d C\n", room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER==1
	if (Engine_temp_controller == ON)
		printf("Engine Temperature Controller is ON\n");
	else
		printf("Engine Temperature Controller is OFF\n");
	printf("Engine Temperature:  %d C\n\n", engine_temp);
#endif

}
void speed_is30(void) {
	if (AC == OFF) {
		AC = ON;
		room_temp = room_temp * 5 / 4 + 1;
	}
#if WITH_ENGINE_TEMP_CONTROLLER==1
	if (Engine_temp_controller == OFF) {
		Engine_temp_controller = ON;
		engine_temp = engine_temp * 5 / 4 + 1;
	}
#endif

}
