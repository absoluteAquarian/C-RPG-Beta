void initWindow(){
	if((window = initscr()) == NULL){
		printf("Error loading game.  Contact the developer about this, ja?\n");
	}
	start_color();
	if(has_colors()){
		init_pair(1, COLOR_WHITE, COLOR_BLACK);			//Standard text
		init_pair(2, COLOR_GREEN, COLOR_BLACK);			//Used for upgrades and text
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_CYAN, COLOR_BLACK);
		init_pair(7, COLOR_YELLOW, COLOR_BLACK);
		init_pair(8, COLOR_WHITE, COLOR_BLACK);			//Unused colour
		init_pair(9, COLOR_WHITE, COLOR_WHITE);			//Used for health bars and maps
		init_pair(10, COLOR_BLACK, COLOR_BLACK);
		init_pair(11, COLOR_RED, COLOR_RED);
		init_pair(12, COLOR_YELLOW, COLOR_YELLOW);
		init_pair(13, COLOR_GREEN, COLOR_GREEN);
		init_pair(14, COLOR_WHITE, COLOR_BLACK);		//Unused colour
		init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(16, COLOR_WHITE, COLOR_BLACK);		//Unused colour
		init_pair(17, COLOR_BLUE, COLOR_BLUE);
		init_pair(18, COLOR_WHITE, COLOR_RED);			//White text on other colour backgrounds
		init_pair(19, COLOR_WHITE, COLOR_YELLOW);
		init_pair(20, COLOR_WHITE, COLOR_GREEN);
		init_pair(21, COLOR_WHITE, COLOR_CYAN);
		init_pair(22, COLOR_WHITE, COLOR_BLUE);
		init_pair(23, COLOR_WHITE, COLOR_MAGENTA);
	}else{
		endwin();
		printf("This application requires colours to function.\n");
		delay(5);
		exit(EXIT_FAILURE);
	}
}

void* movement(){
	//Thread for collison and detecting movement
	char pIcon = 'O', space = ' ', wall = '#', input = '\0', water = '@', tree = '$';
	char prev;
	int* x = &flags.mapx, *y = &flags.mapy, loc;
	loc = (79 * *y) + *x;
	map[loc] = pIcon;
	while(1){
		wresize(window, WINY, WINX);
		loc = (79 * *y) + *x;
		drawMap();
		color_set(1, NULL);
		prev = compmap[loc];
		input = wgetch(window);
		if(input == 'w'){
			map[loc] = prev;
			(*y)--;
			if(map[loc - 79] == wall){
				map[loc] = pIcon;
				(*y)++;
				map[loc - 79] = wall;
			}else
				map[loc - 79] = pIcon;
		}else if(input == 'a'){
			map[loc] = prev;
			(*x)--;
			if(map[loc - 1] == wall){
				map[loc] = pIcon;
				(*x)++;
				map[loc - 1] = wall;
			}else
				map[loc - 1] = pIcon;
		}else if(input == 's'){
			map[loc] = prev;
			(*y)++;
			if(map[loc + 79] == wall){
				map[loc] = pIcon;
				(*y)--;
				map[loc + 79] = wall;
			}else
				map[loc + 79] = pIcon;
		}else if(input == 'd'){
			map[loc] = prev;
			(*x)++;
			if(map[loc + 1] == wall){
				map[loc] = pIcon;
				(*x)--;
				map[loc + 1] = wall;
			}else
				map[loc + 1] = pIcon;
		}
		if(*y > 23){
			*y = 23;
			map[loc] = pIcon;
		}if(*y < 0){
			*y = 0;
			map[loc] = pIcon;
		}if(*x > 78){
			*x = 78;
			map[loc] = pIcon;
		}if(*x < 0){
			*x = 0;
			map[loc] = pIcon;
		}
		delay(1.0 / 30.0);
	}
}

void* transition(){
	//Map transitions
	int *x = &flags.mapx, *y = &flags.mapy, prevmap = flags.mapno;
	while(1){
		//Castle transitions
		int prevx = *x, prevy = *y;
		if(flags.mapno == 2){
			if(*x == 78 && (*y == 7 || *y == 8)){	//To map 3, right
				maps(3);
				*x = 1;
			}else if((*x == 34 || *x == 35) && *y == 23){	//To map 5, down
				maps(5);
				*y = 1;
			}
		}else if(flags.mapno == 3){
			if(*y == 7 || *y == 8){
				if(*x == 0){	//To map 2, left
					maps(2);
					*x = 77;
				}else if(*x == 78){	//To map 4, right
					maps(4);
					*x = 1;
				}
			}else if((*x >= 11 || *x <= 66) && *y == 23){	//To map 6, down
				maps(6);
				*y = 1;
			}
		}else if(flags.mapno == 4){
			if(*x == 0 && (*y == 7 || *y == 8)){	//To map 3, left
				maps(3);
				*x = 77;
			}else if((*x == 22 || *x == 23 || *x == 44 || *x == 45) && *y == 23){	//To map 7, down
				maps(7);
				*y = 1;
			}
		}else if(flags.mapno == 5){
			if((*x == 34 || *x == 35) && *y == 0){	//To map 2, up
				maps(2);
				*y = 22;
			}else if((*x == 38 || *x == 39 || *x == 59 || *x == 60) && *y == 23){	//To map 8, down
				maps(8);
				*y = 1;
			}
		}else if(flags.mapno == 6){
			if(*x >= 11 || *x <= 66){
				if(*y == 0){	//To map 3, up
					maps(3);
					*y = 22;
				}else if(*y == 23){	//To map 9, down
					maps(9);
					*y = 1;
				}
			}
		}else if(flags.mapno == 7){
			if((*x == 22 || *x == 23 || *x == 44 || *x == 45) && *y == 0){	//To map 4, up
				maps(4);
				*y = 22;
			}else if((*x == 75 || *x == 76) && *y == 23){	//To map 10, down
				maps(10);
				*y = 1;
			}
		}else if(flags.mapno == 8){
			if((*x == 38 || *x == 39 || *x == 59 || *x == 60) && *y == 0){	//To map 5, up
				maps(5);
				*y = 22;
			}else if(*x == 78 && (*y == 12 || *y == 13)){	//To map 9, right
				maps(9);
				*x = 1;
			}
		}else if(flags.mapno == 9){
			if((*x >= 11 || *x <= 66) && *y == 0){	//To map 6, up
				maps(6);
				*y = 22;
			}else if(*y == 12 || *y == 13){
				if(*x == 0){	//To map 8, left
					maps(8);
					*x = 77;
				}else if(*x == 78){	//To map 10, right
					maps(10);
					*x = 1;
				}
			}
		}else if(flags.mapno == 10){
			if((*x == 75 || *x == 76) && *y == 0){	//To map 7, up
				maps(7);
				*y = 22;
			}else if(*x == 0 && (*y == 12 || *y == 13)){	//To map 9, left
				maps(9);
				*x = 77;
			}
		}
		if(flags.mapno != prevmap)	//If there was a transition, draw the new map
			drawMap();
		delay(1.0 / 30.0);
	}
}

void setColour(int colour){
	color_set(colour, NULL);
}

void findColour(char c){
	//Sets the colour for the specified cell
	if(c == '@')
		setColour(BLUE_BLUE);		//Water
	else if(c == '#')
		setColour(YELLOW_YELLOW);	//Wall
	else if(c == ' ')
		setColour(WHITE_BLACK);		//Empty space
	else if(c == '!')
		setColour(MAGENTA_MAGENTA);	//Special tile
	else if(c == '-' || c == '0' || c == '|')
		setColour(WHITE_WHITE);		//Border tile
	else if(c == '$')
		setColour(GREEN_GREEN);		//Tree tile
	else
		setColour(WHITE_BLACK);		//Fail-safe
}

void drawMap(){
	//Draws the border
						   //		   1		 2		   3		 4		   5		 6		   7		 8
						   //0123456789A123456789A123456789A123456789A123456789A123456789A123456789A123456789A1
	char border[BORDER] =	"0-------------------------------------------------------------------------------0"//1
							"|                                                                               |"//2
							"|                                                                               |"//3
							"|                                                                               |"//4
							"|                                                                               |"//5
							"|                                                                               |"//6
							"|                                                                               |"//7
							"|                                                                               |"//8
							"|                                                                               |"//9
							"|                                                                               |"//A	1
							"|                                                                               |"//1
							"|                                                                               |"//2
							"|                                                                               |"//3
							"|                                                                               |"//4
							"|                                                                               |"//5
							"|                                                                               |"//6
							"|                                                                               |"//7
							"|                                                                               |"//8
							"|                                                                               |"//9
							"|                                                                               |"//A	2
							"|                                                                               |"//1
							"|                                                                               |"//2
							"|                                                                               |"//3
							"|                                                                               |"//4
							"|                                                                               |"//5
							"0-------------------------------------------------------------------------------0";//6
	mapTile tile;
	int x, y, loc;
	int maxx, maxy;
	//Draws the border
	for(y = 0; y < 26; y++){
		for(x = 0; x < 81; x++){
			loc = (81 * y) + x;
			findColour(border[loc]);
			if(border[loc] >= " " && border[loc] < 127)
				mvaddch(y, x, border[loc]);
		}
	}
	if(flags.shouldDrawMap){
		//Draws the map
		for(tile.y = 0; tile.y < 24; y++){
			for(tile.x = 0; tile.x < 79; x++){
				tile.location = (79 * tile.y) + tile.x;
				findColour(map[tile.location]);
				if(map[tile.location] >= 32)
					mvaddch(tile.y + 1, tile.x + 1, map[tile.location]);
			}
		}
	}
	getmaxyx(window, maxy, maxx);
	//Sets everything else to white/white
	color_set(16, NULL);
	for(x = 81; x < maxx; x++){
		for(y = 0; y < maxy; y++){
			mvprintw(y, x, ".");
		}
	}
	for(x = 0; x < maxx; x++){
		for(y = 26; y < maxy; y++){
			mvprintw(y, x, ".");
		}
	}
	wmove(window, WINY + 1, WINX + 1);
	refresh();
}

void drawTextBox(){
	int i = 0;
							   //		   1		 2		   3		 4		   5		 6		   7		 8
							   //0123456789A123456789A123456789A123456789A123456789A123456789A123456789A123456789A1
	char box[TEXT_BOX_LENGTH] = "0-------------------------------------------------------------------------------0";
	while(i < 81){	//Draw the box
		findColour(box[i]);
		mvaddch(20, i, box[i]);
	}
	for(int x = 0; x < 78; x++){	//Clear the area in the box
		for(int y = 0; y < 3; y++){
			color_set(1, NULL);
			mvaddch(21 + y, 1 + x, ' ');
		}
	}
}

void drawNameBox(int side, int colour, char* name){
	//Name should be >= 17 characters long!
	int s = 0, loc;
							   //		   1		 2
							   //0123456789A123456789A1
	char box[NAME_BOX_SIZE] =	"0-------------------0"
								"|                   |"
								"0-------------------0";
	if(side == 1)	//Determine whether the box goes on the left or right side of the map
		sideAdd = 0;
	else if(side == 2)
		sideAdd = 60;
	else
		sideAdd = 0;		//Fail-safe
	for(int x = 0; x < 21; x++){
		for(int y = 0; y < 3; y++){
			loc = (21 * y) + x;
			findColour(box[loc]);
			mvaddch(17 + y, x, box[loc]);
		}
	}
	int i = 0;
	setColour(GREEN_BLACK);
	while(i < 19){
		mvaddch(18, sideAdd + i + 1, ' ');	//Clear the area in the box
	}
	if(colour > COLORMAX || colour < COLORMIN)	//Failsafe for developer errors, sets color to green/black if error
		setColour(GREEN_BLACK);
	else
		setColour(colour);
	mvaddstr(18, sideAdd + 2, name);		//Draw the name
}

void* eatInput(){
	noecho();
	while(1){
		wgetch(window);
	}
}

void drawText(int y, int x, double delay_, char* text){
	//If using with drawTextBox(), y is 21, 22, or 23; x is 2
	int len = strlen(text);
	int i = 0;
	pthread_create(&einput, NULL, eatInput, NULL);
	for(i = 0; i < len; i++){
		mvaddch(y, x + i, text[i]);
		delay(delay_);
		refresh();
	}
	pthread_cancel(einput);
	refresh();
}