#include <stdio.h>
#include <ncurses.h>
struct Player { int hp; int max_hp; int damage; int lvl; int exp; int exp_to_lvl; char name[64]; };
int current_line;
int main(int argc, char **argv)
{	
	current_line = 2;
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	system("clear");
	initscr();
	int enemy_level = 1;
	
	struct Player player = { 50, 50, 10, 1, 0, 100, "Hero"};
	struct Player enemy  = { 5000, 5000, 10, 1, 0, 100, "Ogre"};
	
	int turn = 1;
	while(1)
	{
		noecho();
		int action;
		draw_ui(&player.hp, &enemy.hp, turn);
		if(enemy.hp <= 0) 
		{
			//printw("%s is dead\n", enemy.name);
			//break;
		}
		refresh();
		action = getch(); 
		switch( action )
		{
			case 'a':
				if(enemy.hp > 0)
				{
					attack(&player, &enemy, turn);
				}
				turn++;
				break;
		}
	}
	endwin();
	printf("Game over in %i turns\n", turn);
	return 0;
}

void attack(struct Player *attacker, struct Player *defender, int turn)
{
	defender->hp -= attacker->damage;
	add_exp(attacker, attacker->damage);
	move(current_line, 5);
	current_line++;
	printw("%s attacked %s with %i damage", attacker->name, defender->name, attacker->damage);
}

void draw_ui(struct Player *player, struct Player *enemy, int turn_number)
{
	move(0,1);
	printw("HP: %i" , player->hp);
	move(0,15);
	printw("LVL: %i", player->lvl); 
	move(0,30);
	printw("EXP: %i/%i", player->exp, player->exp_to_lvl);
	move(0,60);
	printw("Enemy HP: %i", enemy->hp);
	move(0,100);
	printw("Turn: %i", turn_number);
	refresh();
}

void lvlup(struct Player *player)
{
	player->lvl++;
	player->exp = 0;
	player->exp_to_lvl = player->exp_to_lvl * 2;
	player->max_hp += 50;
	player->damage += 5;
	player->hp = player->max_hp;
	move(current_line, 5);
	current_line++;
	printw("%s lvlupped", player->name);
}

void add_exp(struct Player *player, int exp)
{
	player->exp += exp;
	if(player->exp >= player->exp_to_lvl)
	{
		lvlup(player);
	}
}
