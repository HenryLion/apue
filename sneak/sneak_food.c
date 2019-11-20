#include <unistd.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAP_ROW 15
#define MAP_COL 15
#define PROMPT_LINE 3
#define MAP_LINE 7
#define SNEAK_LEN 4
#define BLINK_TIME 300000
#define NEXT_STAGE_LEN	11 

int g_usleep_time = 400000;
int g_score = 0;
int level = 1;

typedef enum game_state
{
	INVALID,
	NORMAL,
	NEXT_STAGE,
	GAME_OVER,
} Game_state;

typedef struct sneak_node
{
	int x;
	int y;
	struct sneak_node *next;
} Sneak_node;

typedef struct sneak_body_list
{
	Sneak_node *head;
	Sneak_node *tail;
	int sneak_len;
} Sneak_body_list;

typedef Sneak_node Food;

char g_map[MAP_ROW][MAP_COL];
int direction = KEY_RIGHT;
int new_direction = KEY_RIGHT;
Food g_food;
Sneak_body_list g_sneak_body_list;

int kbhit (void);

void get_score ()
{
	g_score += level * 10;
}

Sneak_node* create_sneaknode (int pos_x, int pos_y)
{
	Sneak_node *new_sneak_node = (Sneak_node*)malloc (sizeof (Sneak_node));
	if (NULL != new_sneak_node)
	{
		new_sneak_node->x = pos_x;
		new_sneak_node->y = pos_y;
		new_sneak_node->next = NULL;
		return new_sneak_node;
	}
	else
	{
		return NULL;
	}
}

void add_newnode_to_sneakbody (Sneak_node *new_node)
{
	if (NULL == new_node)
		return;

	new_node->next = g_sneak_body_list.head;
	g_sneak_body_list.head = new_node;
	if (g_sneak_body_list.tail == NULL)
	{
		g_sneak_body_list.tail = new_node;
	}
	g_sneak_body_list.sneak_len++;
	return;
}

void init_sneakbody_list ()
{
	int idx = 0;
	Sneak_node *node = NULL;
	g_sneak_body_list.head = NULL;
	g_sneak_body_list.tail = NULL;
	g_sneak_body_list.sneak_len = 0;
	for (idx = 0; idx < SNEAK_LEN; ++idx)
	{
		node = create_sneaknode (3, 3+idx);
		if (NULL != node)
		{
			add_newnode_to_sneakbody (node);
		}
	}
}

void release_tail_node ()
{
	Sneak_node *first = g_sneak_body_list.head->next;
	Sneak_node *second = g_sneak_body_list.head;
	while (first->next != NULL)
	{
		first = first->next;
		second = second->next;
	}
	free (first);
	second->next = NULL;
	g_sneak_body_list.sneak_len--;
	return;
}

void release_all_node ()
{
	Sneak_node *first = g_sneak_body_list.head->next;
	Sneak_node *second = g_sneak_body_list.head;
	while (first->next != NULL)
	{
		free (second);
		second = first;
		first = first->next;
	}
	free (first);
	
}

int food_confict_with_sneak_body (int food_pos_x, int food_pos_y)
{
	Sneak_node *for_each_node = g_sneak_body_list.head;
	while (for_each_node != NULL)
	{
		if (food_pos_x == for_each_node->x && food_pos_y == for_each_node->y)
		{
			return true;
		}
		for_each_node = for_each_node->next;
	}
	return false;
}

void create_food_pos ()
{
	srand (time(NULL));
	do 
	{
		g_food.x = rand () % MAP_ROW;
		g_food.y = rand () % MAP_COL;
	} while (food_confict_with_sneak_body (g_food.x, g_food.y));
}


int is_eat_food ()
{
	return ((g_food.x == g_sneak_body_list.head->x) && (g_food.y == g_sneak_body_list.head->y));
}

void on_handler_food_eat ()
{
	/* 把食物位置设置为蛇身 */
	g_map[g_food.x][g_food.y] = 1;
	/* 重新生成食物 */
	create_food_pos ();
	/* 更新分数 */
	get_score ();
}

void init_map ()
{
	int i = 0;
	memset (g_map, 0, sizeof (g_map));
	init_sneakbody_list ();
	create_food_pos ();
}

void update_sneakbody_food_to_map ()
{
	int i = 0;
	memset (g_map, 0, sizeof (g_map));
	
	Sneak_node *for_each_node = g_sneak_body_list.head;
	while (for_each_node != NULL)
	{
		g_map[for_each_node->x][for_each_node->y] = 1;
		for_each_node = for_each_node->next;
	}

	g_map[g_food.x][g_food.y] = 2;
}


void display_prompt ()
{
	attron (A_STANDOUT);
	move (PROMPT_LINE, 8);
	printw ("Sneak Game V0.01, Author Herbert.");
	move (PROMPT_LINE+1, 8);
	attroff (A_STANDOUT);
	printw ("[q for quit.]");
}
void blink_time (int times)
{
	int idx = 0;
	for (idx = 0; idx < times; ++idx)
	{
		move (8,8);
		printw ("Game Over!!!");
		move (LINES-1, COLS-1);
		refresh ();
		usleep (BLINK_TIME);
		clear ();
		move (LINES-1, COLS-1);
		refresh ();
		usleep (BLINK_TIME);
	}
	return ;
}

void game_over ()
{
	clear ();
	release_all_node ();
	blink_time (3);
	move (8,8);
	printw ("Game Over!!!");
	move (LINES-1, COLS-1);
	refresh ();
	sleep (1);
	return;
}

int head_conflict_with_body (int head_x, int head_y)
{
	return food_confict_with_sneak_body (head_x, head_y);
}

Game_state update_map (int new_direction)
{
	Sneak_node *new_node = NULL;
	if (new_direction != KEY_UP && new_direction != KEY_DOWN && new_direction != KEY_LEFT && new_direction != KEY_RIGHT)
	{
		return INVALID;
	}
	Sneak_node *head = g_sneak_body_list.head;
	int head_x_pos = head->x;
	int head_y_pos = head->y;
	switch (new_direction)
	{
		case KEY_UP:
		{
			if (direction == KEY_DOWN)
			{
				if (head_x_pos == MAP_ROW - 1)
				{
					//head_x_pos = 0;
					return GAME_OVER;
				}
				else
				{
					head_x_pos++;
				}
				new_direction = KEY_DOWN;
			}
			else
			{
				if (head_x_pos == 0)
				{
					head_x_pos = MAP_ROW - 1;
					return GAME_OVER;
				}
				else
				{
					head_x_pos--;
				}
			}

			break;
		}
		case KEY_DOWN:
		{
			if (direction == KEY_UP)
			{
				if (head_x_pos == 0)
				{
					head_x_pos = MAP_ROW - 1;
					return GAME_OVER;
				}
				else
				{
					head_x_pos--;
				}
				new_direction = KEY_UP;
			}
			else
			{
				if (head_x_pos == MAP_ROW - 1)
				{
					head_x_pos = 0;
					return GAME_OVER;
				}
				else
				{
					head_x_pos++;
				}
			}
			break;
		}
		case KEY_LEFT:
		{
			if (direction == KEY_RIGHT)
			{
				if (head_y_pos == MAP_COL - 1)
				{
					head_y_pos = 0;
					return GAME_OVER;
				}
				else
				{
					head_y_pos++;
				}
				new_direction = KEY_RIGHT;
			}
			else
			{
				if (head_y_pos == 0)
				{
					head_y_pos = MAP_COL - 1;
					return GAME_OVER;
				}
				else
				{
					head_y_pos--;
				}
			}
			break;
		}
		case KEY_RIGHT:
		{
			if (direction == KEY_LEFT)
			{
				if (head_y_pos == 0)
				{
					head_y_pos = MAP_COL - 1;
					return GAME_OVER;
				}
				else
				{
					head_y_pos--;
				}
				new_direction = KEY_LEFT;
			}
			else
			{
				if (head_y_pos == MAP_COL - 1)
				{
					head_y_pos = 0;
					return GAME_OVER;
				}
				else
				{
					head_y_pos++;
				}
			}
			break;
		}
		default:
			break;
	}

	if (head_conflict_with_body (head_x_pos, head_y_pos))
	{
		return GAME_OVER;
	}
	new_node = create_sneaknode (head_x_pos, head_y_pos);
	if (new_node != NULL)
	{
		add_newnode_to_sneakbody (new_node);
	}

	if (is_eat_food ())
	{
		on_handler_food_eat ();	
		if (g_sneak_body_list.sneak_len == NEXT_STAGE_LEN)
		{
			level++;
			return NEXT_STAGE;
		}
	}
	else
	{
		release_tail_node ();
	}
	direction = new_direction;
	return NORMAL;
}

void display_map ()
{
	int i,j;
	for (i = 0; i < MAP_ROW; ++i)
	{
		move (MAP_LINE+i, 8);
		for (j = 0; j < MAP_COL; ++j)
		{
			if (g_map[i][j] == 0)
			{
				printw (". ");
			}
			else if (g_map[i][j] == 1)
			{
				printw ("@ ");
			}
			else if (g_map[i][j] == 2)
			{
				printw ("o ");
			}
		}
	}
	move (LINES-1, COLS-1);
	refresh ();
}


void init_next_stage ()
{	
	clear ();
	refresh ();
	move (8,8);
	printw ("Next Level");
	refresh ();
	sleep (1);

	g_usleep_time -= (g_usleep_time/7);
	release_all_node ();
	init_map ();
	direction = KEY_RIGHT;
	new_direction = KEY_RIGHT;
}

void display_level_and_score ()
{
	move (8, 30+MAP_COL);
	printw ("Level: %d", level);
	move (9, 30+MAP_COL);
	printw ("Score: %d", g_score);
}


void display_screen ()
{
	Game_state state = INVALID;
	display_prompt ();
	display_map ();
	while (1)
	{
		if (kbhit ())
		{
			new_direction = getch ();
		}
		if ('q' == new_direction)
		{
			game_over ();
			break;
		}
		else if ('s' == new_direction)
		{
			continue;
		}
		state = update_map (new_direction);
		if (state == GAME_OVER)
		{
			game_over ();
			return;
		}
		else if (state == NEXT_STAGE)
		{
			init_next_stage ();
		}

		move(30,8);
		printw ("sneak_len = %d", g_sneak_body_list.sneak_len);
		display_level_and_score ();
		update_sneakbody_food_to_map ();
		display_map ();
		usleep (g_usleep_time);
	}
}

int kbhit ()
{
	struct timeval tv;
	fd_set rdfds;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO (&rdfds);
	FD_SET (STDIN_FILENO, &rdfds);

	select (STDIN_FILENO+1, &rdfds, NULL, NULL, &tv);
	return FD_ISSET (STDIN_FILENO, &rdfds);
}

int main (void)
{
	initscr ();
	init_map ();
	update_sneakbody_food_to_map ();

	keypad (stdscr, 1);
	noecho ();

	display_screen ();	

	echo ();
	keypad (stdscr, 0);
	endwin ();
	return 0;
}

