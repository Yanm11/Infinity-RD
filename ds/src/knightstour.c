#include <assert.h>  /* assert */
#include <stdio.h> /* printf */
#include <stdlib.h> /* abs */
#include "knightstour.h"

#define NUM_OF_MOVES 8 
#define END_RESULT 0x1FFFFFF /* 5*5 -> 25th 1 in binary 33554431 decimal */
#define POS_TO_X(position) (position>> 4)
#define POS_TO_Y(position) (position & 0x0F)
#define XY_TO_POS(x, y) ((x << 4) + y)
#define XY_TO_INDEX(x,y) (x * NUM_OF_ROWS + y)
#define INDEX_TO_X(index) (index / NUM_OF_ROWS)
#define INDEX_TO_Y(index) (index % NUM_OF_ROWS)

typedef int (*func_ptr)(int, int);

static int SearchPath(position_t *path,
					   size_t bitarr,
					   position_t position,
					   size_t moves);
static int Valid(size_t i, size_t bitarr, int x, int y, size_t moves);

static int UpLeft(int x, int y);
static int UpRight(int x, int y);
static int LeftUp(int x, int y);
static int LeftDown(int x, int y);
static int DownLeft(int x, int y);
static int DownRight(int x, int y);
static int RightDown(int x, int y);
static int RightUp(int x, int y);

static func_ptr lut_moves[NUM_OF_MOVES] = {&DownRight, &DownLeft,
										   &RightUp, &RightDown,
										   &UpLeft, &UpRight, 
										   &LeftDown, &LeftUp};

void PrintBits(size_t num, int bits);

position_t BuildPosition(unsigned char row, unsigned char col)
{
	return XY_TO_POS(row,col);
}

knights_tour_status_e RunKnightsTour(position_t path[PATH_LENGTH], 
                                     position_t starting_position, 
                                     int use_heuristic, 
                                     unsigned int time_limit)
{
	size_t bitarr = 0;
	size_t moves = 1;
	int status = 0;
	int x = POS_TO_X(starting_position);
	int y = POS_TO_Y(starting_position);
	int index_to_move_to = XY_TO_INDEX(x, y);
/*	position_t position = 0;*/
	(void)use_heuristic;
	(void)time_limit;
	
	/* updating position */
	path[moves] = starting_position;
			
	/* updating bitarr */
	bitarr = bitarr | (1 << index_to_move_to);
	
/*	printf("moves: %lu\n", moves);*/
/*	printf("index_to_move_to: %d\n", index_to_move_to);*/
/*	PrintBits(bitarr, 25);*/
/*	*/
/*	x = INDEX_TO_X(index_to_move_to);*/
/*	y = INDEX_TO_Y(index_to_move_to);*/
/*	printf("x: %d\ny: %d\n", x, y);*/
/*	position = XY_TO_POS(x,y);*/
/*	printf("pos: %d\n", position);*/
/*	printf("starting_position: %d\n", starting_position);*/
/*	index_to_move_to = lut_moves[5](x,y);*/
/*	printf("index_to_move_to: %d\n", index_to_move_to);*/
	status = SearchPath(path, bitarr, starting_position, moves);
	
/*	printf("----\nmoves: %lu\ni: %lu\n", moves, 0);*/
/*	printf("index_to_move_to: %d\n", index_to_move_to);*/
/*	printf("Moving to: %d (x: %d, y: %d)\n----\n", position, x, y);*/
/*	PrintBits(bitarr, PATH_LENGTH);*/
	if (0 == status)
	{
		return SUCCESS;
	}
	
	printf("failed to find a path\n");
	
	return BAD_PATH;

}


/*********** HELPER FUNCTION ***************/

static int SearchPath(position_t *path,
					   size_t bitarr,
					   position_t position,
					   size_t moves)
{
	size_t i = 0;
	int x = POS_TO_X(position);
	int y = POS_TO_Y(position);
	int index_to_move_to = 0;
	int status = 0;
	

	if (END_RESULT == bitarr)
	{
		return 0;
	}
	
	++moves;
	
	for (i = 0; i < NUM_OF_MOVES; ++i)
	{
		if (Valid(i, bitarr, x, y, moves))
		{
			/* updating new index */
			index_to_move_to = lut_moves[i](x,y);
			
			/* updating position */
			x = INDEX_TO_X(index_to_move_to);
			y = INDEX_TO_Y(index_to_move_to);
			position = XY_TO_POS(x,y);
			path[moves] = position;

			/* updating bitarr */
			bitarr = bitarr | (1 << index_to_move_to);
			
/*			printf("moves: %lu\n", moves);*/
/*			printf("index_to_move_to: %d\n", index_to_move_to);*/
/*			PrintBits(bitarr, PATH_LENGTH);*/
			status = SearchPath(path, bitarr, position, moves);
			if (0 == status)
			{
/*				printf("----\nmoves: %lu\ni: %lu\n", moves, i);*/
/*				printf("index_to_move_to: %d\n", index_to_move_to);*/
/*				printf("Moving to: %d (x: %d, y: %d)\n----\n", position, x, y);*/
/*				PrintBits(bitarr, PATH_LENGTH);*/
				return 0;
			}
			bitarr = bitarr & ~(1 << index_to_move_to);
		}
	}
	
	return 1;
}

static int Valid(size_t i, size_t bitarr, int x, int y, size_t moves)
{
    int new_x = 0, new_y = 0;
    int index_to_move_to = lut_moves[i](x, y);
    
    if (index_to_move_to == PATH_LENGTH + 1)
    {
        return 0;  /* Invalid move */
    }
    
    new_x = INDEX_TO_X(index_to_move_to);
    new_y = INDEX_TO_Y(index_to_move_to);
    
    
    if (new_x < 0 || new_x >= NUM_OF_ROWS || new_y < 0 || new_y >= NUM_OF_ROWS)
    {
        return 0;
    }
    
    if (((bitarr >> index_to_move_to) & 1) == 1)
    {
        return 0;
    }
    
    if (PATH_LENGTH < moves)
    {
        return 0;
    }
    
    return 1;
}

/*static int Valid(size_t i, size_t bitarr, int x, int y, size_t moves)*/
/*{*/
/*	int index_to_move_to = lut_moves[i](x,y);*/
/*	*/
/*	if (PATH_LENGTH < index_to_move_to ||*/
/*		((bitarr >> index_to_move_to) & 1) == 1 || */
/*		PATH_LENGTH < moves)*/
/*	{*/
/*		return 0;*/
/*	}*/
/*	*/
/*	return 1;*/
/*}*/

static int UpLeft(int x, int y)
{
	x = x - 2;
	y = y - 1;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int UpRight(int x, int y)
{
	x = x - 2;
	y = y + 1;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int LeftUp(int x, int y)
{
	x = x - 1;
	y = y - 2;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int LeftDown(int x, int y)
{
	x = x + 1;
	y = y - 2;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int DownLeft(int x, int y)
{
	x = x + 2;
	y = y - 1;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int DownRight(int x, int y)
{
	x = x + 2;
	y = y + 1;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int RightDown(int x, int y)
{
	x = x + 1;
	y = y + 2;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

static int RightUp(int x, int y)
{
	x = x - 1;
	y = y + 2;
	
	if (x < 0 || y < 0 || x >= NUM_OF_ROWS || y >= NUM_OF_ROWS)
	{
		return PATH_LENGTH + 1;
	}
	
	return XY_TO_INDEX(x, y);
}

void PrintBits(size_t num, int bits)
{
    int i = 0;
    for (i = bits - 1; i >= 0; --i)
    {
        printf("%d", (int)((num >> i) & 1));
        if (i % 4 == 0 && i != 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}





