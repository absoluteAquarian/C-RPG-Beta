void town(){
	
}

void adventure(){
	
}

void* startMap(){
	//Starts the map and creates the threads for movement and transitions
	pthread_create(&collmov, NULL, movement, NULL);
	pthread_create(&transit, NULL, transition, NULL);
	while(1){
		if(flags.inmap == false){
			pthread_detach(collmov);
			pthread_detach(transit);
			pthread_cancel(collmov);
			pthread_cancel(transit);
			break;
		}
	}
}