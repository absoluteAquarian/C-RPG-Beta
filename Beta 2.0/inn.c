void inn(){
	int choice = 0, decision = 0, prevCoin = player.currentCoin;
	int luckIncCheck = 0;
	float recoverHP;
	printf("====================\n");	//20 equals signs, indicates new menu
	printf("Welcome to the INN!\n");
	delay(1);
	printf("Choose an option:\n");
	while(true){
		fflush(stdin);
		printf("(1) Recover some of my HP\n(2) Recover most of my HP\n(3) Recover all of my HP\n(4) Remove status effects\n(5) Leave\n");
		printf("-> ");
		scanf("%d", &choice);
		if(choice > 5 || choice < 1){
			printf("Sorry hun, that's not an option.  Try again.\n");
		}else if(choice == 1){
			while(true){
				fflush(stdin);
				printf("All right, that will be 80 coin.  Are you sure?\n(1) Yes\n(2) No\n-> ");
				scanf("%d", &decision);
				if(decision == 1){
					player.currentCoin -= 80;
					if(player.currentCoin < 0){
						player.currentCoin = prevCoin;
						printf("Sorry hun, you don't have enough coin.  You need 80 coin and you only have %d coin.", player.currentCoin);
						break;
					}else{
						recoverHP = ((float) player.maxHealth) * 0.125 + 0.5;
						player.currentHealth += (int) recoverHP;
						if(player.currentHealth > player.maxHealth)
							player.currentHealth = player.maxHealth;
						printf("There, your wounds are healed.\n");
						luckIncCheck = 1;
						break;
					}
				}else if(decision == 2){
					printf("Come back soon!\n");
					break;
				}else
					printf("You just cannot do that!\n");
			}
			break;
		}else if(choice == 2){
			while(true){
				fflush(stdin);
				printf("All right, that will be 250 coin.  Are you sure?\n(1) Yes\n(2) No\n-> ");
				scanf("%d", &decision);
				if(decision == 1){
					player.currentCoin -= 250;
					if(player.currentCoin < 0){
						player.currentCoin = prevCoin;
						printf("Sorry hun, you don't have enough coin.  You need 250 coin and you only have %d coin.", player.currentCoin);
						break;
					}else{
						recoverHP = ((float) player.maxHealth) * 0.55 + 0.5;
						player.currentHealth += (int) recoverHP;
						if(player.currentHealth > player.maxHealth)
							player.currentHealth = player.maxHealth;
						printf("There, your wounds are healed.\n");
						luckIncCheck = 1;
						break;
					}
				}else if(decision == 2){
					printf("Come back soon!\n");
					break;
				}else
					printf("You just cannot do that!\n");
			}
			break;
		}else if(choice == 3){
			while(true){
				fflush(stdin);
				printf("All right, that will be 450 coin.  Are you sure?\n(1) Yes\n(2) No\n-> ");
				scanf("%d", &decision);
				if(decision == 1){
					player.currentCoin -= 450;
					if(player.currentCoin < 0){
						player.currentCoin = prevCoin;
						printf("Sorry hun, you don't have enough coin.  You need 450 coin and you only have %d coin.", player.currentCoin);
						break;
					}else{
						recoverHP = (float) player.maxHealth;
						player.currentHealth += (int) recoverHP;
						if(player.currentHealth > player.maxHealth)
							player.currentHealth = player.maxHealth;
						printf("There, your wounds are healed.\n");
						luckIncCheck = 1;
						break;
					}
				}else if(decision == 2){
					printf("Come back soon!\n");
					break;
				}else
					printf("You just cannot do that!\n");
			}
			break;
		}else if(choice == 4){
			while(true){
				fflush(stdin);
				printf("All right, that will be 100 coin.  Are you sure?\n(1) Yes\n(2) No\n-> ");
				scanf("%d", &decision);
				if(decision == 1){
					player.currentCoin -= 100;
					if(player.currentCoin < 0){
						player.currentCoin = prevCoin;
						printf("Sorry hun, you don't have enough coin.  You need 100 coin and you only have %d coin.", player.currentCoin);
						break;
					}else{
						player.poisoned = 0;
						player.burned = 0;
						printf("There, you look as fresh as a farm egg!\n");
						break;
					}
				}else if(decision == 2){
					printf("Come back soon!\n");
					break;
				}else
					printf("You just cannot do that!\n");
			}
			break;
		}else if(choice == 5)
			break;
	}
	if(player.luckCheck == 1 || luckIncCheck == 0){
		player.tkarma = player.tkarma;
	}else if(player.luckCheck == 0 && luckIncCheck == 1){
		player.tkarma += 20;
		player.luckCheck = 1;
	}
	update_player_data();
}