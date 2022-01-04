char* armourName(int ID){
	return itemName[ID];
}

void smithery(){
	int choice = 0, option = 0, decision = 0;
	int previousCoin = player.currentCoin;
	float newCoin;
	printf("====================\n");	//20 equals signs, indicates new menu
	printf("Welcome to the Smithery!\n");
	delay(1);
	printf("What do ye want to do?\n");
	printf("(1) Upgrade something.\n(2) Leave!\n");
	while(true){
		fflush(stdin);
		printf("-> ");
		scanf("%d", &choice);
		if(choice < 1 || choice > 2)
			printf("C'mon mate.  You know that ye can't do that!\n");
		else if(choice == 1){
			printf("Upgrade...\n(1) my head wear.\n(2) my chest thing.\n(3) my pantaloons.\n(4) my weapon.\n(5) nothing.  I changed my mind.\n");
			while(true){
				fflush(stdin);
				printf("-> ");
				scanf("%d", &option);
				if(option == 1){
					if(player.hUpCheck == player.armourH){
						printf("Ye already upgraded that.\n");
						return;
					}else if(player.armourH == 0){
						printf("Puh!  I'm a blacksmith, not a barber!\n");
						return;
					}
					printf("You want to upgrade %s?  That will be %d coin.\n", armourName(player.class, 1, player.armourH), (int) ((float) hCost[player.armourH] * 1.5));
					printf("(1) Yes\n(2) No\n");
					while(true){
						fflush(stdin);
						printf("-> ");
						scanf("%d", &decision);
						if(decision == 1){
							newCoin = (((float) player.currentCoin) - ((float) hCost[player.armourH])) * 1.5;
							player.currentCoin = (int) newCoin;
							if(player.currentCoin < 0){
								player.currentCoin = previousCoin;
								printf("Sorry mate, I don't take credit.  Come back when you're a little... richer!\n\n");
								return;
							}else{
								printf("Hmm... yes.  That's a mighty fine upgrade.\n\n");
								player.hUpCheck = player.armourH;
								return;
							}
						}else if(decision == 2){
							printf("\nSee ya at the shop!\n\n");
							update_player_data();
							return;
						}
					}
				}else if(option == 2){
					if(player.cUpCheck == player.armourC){
						printf("Ye already upgraded that.\n");
						return;
					}else if(player.armourC == 0){
						printf("Hah!  You expect ME to stitch those holes?  I'm a blacksmith, not a tailor!\n");
						return;
					}
					printf("You want to upgrade %s?  That will be %d coin.\n", armourName(player.class, 2, player.armourC), (int) ((float) cCost[player.armourC] * 1.5));
					printf("(1) Yes\n(2) No\n");
					while(true){
						fflush(stdin);
						printf("-> ");
						scanf("%d", &decision);
						if(decision == 1){
							newCoin = (((float) player.currentCoin) - ((float) cCost[player.armourC])) * 1.5;
							player.currentCoin = (int) newCoin;
							if(player.currentCoin < 0){
								player.currentCoin = previousCoin;
								printf("Sorry mate, I don't take credit.  Come back when you're a little... richer!\n\n");
								return;
							}else{
								printf("Hmm... yes.  That's a mighty fine upgrade.\n\n");
								player.cUpCheck = player.armourC;
								return;
							}
						}else if(decision == 2){
							printf("\nSee ya at the shop!\n\n");
							update_player_data();
							return;
						}
					}
				}else if(option == 3){
					if(player.lUpCheck == player.armourL){
						printf("Ye already upgraded that.\n");
						return;
					}else if(player.armourL == 0){
						printf("Ehehe... you've barely got anything there!  My hammer wouldn't do anything to that!\n");
						return;
					}
					printf("You want to upgrade %s?  That will be %d coin.\n", armourName(player.class, 3, player.armourL), (int) ((float) lCost[player.armourL] * 1.5));
					printf("(1) Yes\n(2) No\n");
					while(true){
						fflush(stdin);
						printf("-> ");
						scanf("%d", &decision);
						if(decision == 1){
							newCoin = (((float) player.currentCoin) - ((float) lCost[player.armourL])) * 1.5;
							player.currentCoin = (int) newCoin;
							if(player.currentCoin < 0){
								player.currentCoin = previousCoin;
								printf("Sorry mate, I don't take credit.  Come back when you're a little... richer!\n\n");
								return;
							}else{
								printf("Hmm... yes.  That's a mighty fine upgrade.\n\n");
								player.lUpCheck = player.armourL;
								return;
							}
						}else if(decision == 2){
							printf("\nSee ya at the shop!\n\n");
							update_player_data();
							return;
						}
					}
				}else if(option == 4){
					if(player.wUpCheck == player.weapon){
						printf("Ye already upgraded that.\n");
						return;
					}else if(player.weapon == 0){
						printf("What are ye, a lunatic?  This here hammer would bust yer fingers!\n");
						return;
					}
					printf("You want to upgrade %s?  That will be %d coin.\n", armourName(player.class, 4, player.weapon), (int) ((float) wCost[player.weapon] * 1.5));
					printf("(1) Yes\n(2) No\n");
					while(true){
						fflush(stdin);
						printf("-> ");
						scanf("%d", &decision);
						if(decision == 1){
							newCoin = (((float) player.currentCoin) - ((float) wCost[player.weapon])) * 1.5;
							player.currentCoin = (int) newCoin;
							if(player.currentCoin < 0){
								player.currentCoin = previousCoin;
								printf("Sorry mate, I don't take credit.  Come back when you're a little... richer!\n\n");
								return;
							}else{
								printf("Hmm... yes.  That's a mighty fine upgrade.\n\n");
								player.wUpCheck = player.weapon;
								return;
							}
						}else if(decision == 2){
							printf("\nSee ya at the shop!\n\n");
							update_player_data();
							return;
						}
					}
				}else if(option == 5){
					printf("\nSee ya at the shop!\n\n");
					update_player_data();
					return;
				}
			}
		}else if(choice == 2){
			printf("\nSee ya at the shop!\n\n");
			update_player_data();
			return;
		}
	}
}