void potion(){
	if(player.potionCheck == 1)
		printf("\nWhoops!  You can't use more than one potion per turn!\n");
	if(player.etherCheck == 1)
		printf("\nWhoops!  You can't use more than one ether per turn!\n");
	int choice, option;
	if(player.currentHealth == player.maxHealth){
		printf("\nYou fool!  You don't need to use a potion yet!\n\n");
		return;
	}
	while(true){
		fflush(stdin);
		printf("Use\n(1) a Potion\n(2) an Ether\n-> ");
		scanf("%d", &option);
		if(option == 1 || option == 2)
			break;
	}
	if(option == 1){
		while(true){
			fflush(stdin);
			if(player.level < 71){
				printf("\n\nYou have %d Small Potions, %d Potions, and %d Large Potions left.\n", player.potion1_count, player.potion2_count, player.potion3_count);
				printf("Which one would you like to use?\n(1) Small Potion\n(2) Potion\n(3) Large Potion\n(5) or Exit Menu?\n-> ");
			}else if(player.level >= 71){
				printf("\n\nYou have %d Small Potions, %d Potions, %d Large Potions, and %d Super Potions left.\n", player.potion1_count, player.potion2_count, player.potion3_count, player.potion4_count);
				printf("Which one would you like to use?\n(1) Small Potion\n(2) Potion\n(3) Large Potion\n(4) Super Potion\n(5) or Exit Menu?\n-> ");
			}
			scanf("%d", &choice);
			if(choice == 1){
				if(player.potion1_count == 0)
					printf("\nYou try to drink an imaginary potion.  You fool.\n\n");
				else if(player.potion1_count != 0){
					player.potion1_count--;
					printf("You drank the potion and recovered 20 HP!\n\n");
					player.currentHealth += 35;
					if(player.currentHealth > player.maxHealth)
						player.currentHealth = player.maxHealth;
					player.potionCheck = 1;
					break;
				}
			}else if(choice == 2){
				if(player.potion2_count == 0)
					printf("\nYou try to drink an imaginary potion.  You fool.\n\n");
				else if(player.potion2_count != 0){
					player.potion2_count--;
					printf("You drank the potion and recovered 45 HP!\n\n");
					player.currentHealth += 80;
					if(player.currentHealth > player.maxHealth)
						player.currentHealth = player.maxHealth;
					player.potionCheck = 1;
					break;
				}
			}else if(choice == 3){
				if(player.potion3_count == 0)
					printf("\nYou try to drink an imaginary potion.  You fool.\n\n");
				else if(player.potion3_count != 0){
					player.potion3_count--;
					printf("You drank the potion and recovered 75 HP!\n\n");
					player.currentHealth += 175;
					if(player.currentHealth > player.maxHealth)
						player.currentHealth = player.maxHealth;
					player.potionCheck = 1;
					break;
				}
			}else if(choice == 4 && player.level >= 71){
				if(player.potion4_count == 0)
					printf("\nYou try to drink an imaginary potion.  You fool.\n\n");
				else if(player.potion4_count != 0){
					player.potion3_count--;
					printf("You drank the potion and recovered 200 HP!\n\n");
					player.currentHealth += 355;
					if(player.currentHealth > player.maxHealth)
						player.currentHealth = player.maxHealth;
					player.potionCheck = 1;
					break;
				}
			}else if(choice == 4 && player.level < 71){
				printf("You can't use this potion yet.\n\n");
			}else if(choice == 5)
				return;
			else
				printf("Invalid input.\n\n");
		}
	}else if(option == 2){
		printf("This feature isn't in the game yet.\n\n");
	}
}