#include <stdio.h>
#include <ncurses.h>
struct Player { int hp; int damage; int lvl; int exp; int exp_to_lvl; char name[64]; };
int current_line;
int main(int argc, char **argv)
{	
	current_line = 2;
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	system("clear");
	initscr();
	int enemy_level = 1;
	
	struct Player player = { 50, 10, 1, 0, 100, "Hero"};
	struct Player enemy  = { 50, 10, 1, 0, 100, "Ogre"};
	
	int turn = 1;
	while(1)
	{
		attroff(COLOR_PAIR(1));
		noecho();
		int action;
		draw_ui(&player.hp, &enemy.hp, turn);
		if(enemy.hp <= 0) 
		{
			printw("%s is dead\n", enemy.name);
			break;
		}
		refresh();
		action = getch(); 
		switch( action )
		{
			case 'a':
				attack(&player, &enemy, turn);
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
	move(current_line, 5);
	current_line++;
	printw("%s attacked %s with %i damage", attacker->name, defender->name, attacker->damage);
}

void draw_ui(int *player_hp, int *enemy_hp, int turn_number)
{
	move(0,1);
	printw("Your hp: %i" , *player_hp); 
	move(0,30);
	printw("Enemy hp: %i", *enemy_hp);
	move(0,60);
	printw("Turn: %i", turn_number);
	refresh();
}

