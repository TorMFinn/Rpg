#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

struct Character
{
	int hit_points;
	int mana;
	int level;
	int xp;
	char name[20];
};

struct Enemy{
	int hit_points;
	char* name;
	int level;
};

int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

struct Enemy create_enemy()
{
		struct Enemy enemy;
		enemy.hit_points = 100;
		//sprintf(enemy[i].name, "enemy%d", i);
		enemy.name = "Enemy1";
		enemy.level = 1;

		return enemy;
}

// struct Enemy create_enemy(struct Enemy enemy)
// {
// 		enemy.hit_points = 100;
// 		//sprintf(enemy[i].name, "enemy%d", i);
// 		enemy.name = "Enemy1";
// 		enemy.level = 1;

// 		return enemy;
// }

int fight(struct Character character, struct Enemy enemy){
	int success;
	printf("You have encountered an enemy, %s\n", enemy.name);
	printf("Hp: %d\nlevel: %d\n", enemy.hit_points, enemy.level);
	
	userAction:
	printf("1. attack\n2. Run\n");
	char choice[2];
	getLine("", choice, sizeof(choice));
	int choice2 = atoi(choice);
	switch (choice2)
	{
		case 1:
			success = attack(character, enemy);
			break;
		case 2:
			//runAway();
			break;
		default:
			printf("Unknown input\n");
			goto userAction;
			break;
	}
}

int attack(struct Character character, struct Enemy enemy)
{
	int success = 0; //-1 fail 1 success;
	int damage;
	int miss = 3;

	while(success == 0){
	srand(time(NULL));
	
	damage = (character.level * 1.25) + (rand() % 10 + 5);  
	if(miss == rand() % 6 + 1)
	{
		printf("You missed!\n");
	}
		else if(miss != rand() % 6 + 1){
		printf("You attack %s for %d damage\n", enemy.name, damage);
		sleep(3);
		enemy.hit_points -= damage; //Take damage
		if(enemy.hit_points <= 0){
		success = 1;
		printf("You have killed the enemy\n");
		}
	}
	else
	{
		if(miss == rand() % 6 + 1)
		{
		printf("Enemy missed!\n");
		}else{


		printf("%s attacks you for %d damage\n", enemy.name, damage);
		sleep(3);
		character.hit_points -= damage;
		if(character.hit_points <= 0)
		{
			printf("%s slayed you.... oh no!\n", enemy.name);
			success = -1; //Dead
		}
	}
	}
	}
}

int main()
{
	struct Character character;
	struct Enemy enemy;

	character.hit_points = 2000;
	character.level = 1;
	character.xp = 0;
	character.mana = 125;

	enemy = create_enemy();

	printf("RPG version 0.1 (December 15th 2014)\n");
	getLine("Enter your name:\n", character.name, sizeof(character.name));
	
	if(fight(character, enemy) != -1)
	{
		fight(character, enemy);
		printf("You won!\n\n");
	}


	return 0;
}