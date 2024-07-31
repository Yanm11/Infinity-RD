/* evelin code review */

#include <assert.h>  /* assert */
#include <stdio.h> /* printf */
#include <stdlib.h> /* abs */
#include <time.h> /* time_t time */

#include "knightstour.h"

#define NUM_OF_MOVES 8 
#define END_RESULT 0xFFFFFFFFFFFFFFFF /* 64 bits of all 1 */
#define POS_TO_X(position) (position>> 4)
#define POS_TO_Y(position) (position & 0x0F)
#define XY_TO_POS(x, y) ((x << 4) + y)
#define XY_TO_INDEX(x,y) (x * NUM_OF_ROWS + y)
#define INDEX_TO_X(index) (index / NUM_OF_ROWS)
#define INDEX_TO_Y(index) (index % NUM_OF_ROWS)

typedef int (*func_ptr)(int, int);

static knights_tour_status_e SearchPath(position_t *path,
									    size_t bitarr,
									    position_t position,
									    size_t moves,
									    time_t limit);
static knights_tour_status_e SearchWandrof(position_t *path,
										   size_t bitarr,
										   position_t position,
										   time_t limit);
static int Valid(size_t i, size_t bitarr, int x, int y, size_t moves);
static void ComputeWarndrofLut(size_t bitarr);
static size_t NextMove(size_t bitarr, int x, int y);

static int UpLeft(int x, int y);
static int UpRight(int x, int y);
static int LeftUp(int x, int y);
static int LeftDown(int x, int y);
static int DownLeft(int x, int y);
static int DownRight(int x, int y);
static int RightDown(int x, int y);
static int RightUp(int x, int y);

/* LUT initialization for all the possible moves */
static func_ptr lut_moves[NUM_OF_MOVES] = {&DownRight, &RightDown,
										   &RightUp, &UpRight,
										   &UpLeft, &LeftUp, 
										   &LeftDown, &DownLeft};
static int warndrof_lut[PATH_LENGTH] = {0};

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
	size_t moves = 0;
	int x = POS_TO_X(starting_position);
	int y = POS_TO_Y(starting_position);
	int index_to_move_to = XY_TO_INDEX(x, y);
	time_t limit = (time_t)time_limit + time(NULL);
	
	(void)time_limit;
	
/*	 updating position */
	path[moves] = starting_position;
			
/*	 updating bitarr */
	bitarr = bitarr | ((size_t)1 << index_to_move_to);
	
	if (use_heuristic)
	{
		return SearchWandrof(path, bitarr, starting_position, limit);
	}
	else
	{
		return SearchPath(path, bitarr, starting_position, moves, limit);	
	}
}

/*********** HELPER FUNCTION ***************/

static knights_tour_status_e SearchPath(position_t *path,
									    size_t bitarr,
									    position_t position,
									    size_t moves,
									    time_t limit)
{
	size_t i = 0;
	int x = POS_TO_X(position);
	int y = POS_TO_Y(position);
	int index_to_move_to = 0;
	int status = 0;
	int x_new = 0;
	int y_new = 0;
	
	if (END_RESULT == bitarr)
	{
		return SUCCESS;
	}
	else if (time(NULL) >= limit)
	{
		return TIME_EXCEEDED;
	}
	
	++moves;
	
	for (i = 0; i < NUM_OF_MOVES; ++i)
	{
		if (Valid(i, bitarr, x, y, moves))
		{
			/* updating new index */
			index_to_move_to = lut_moves[i](x,y);
			
			/* updating position */
			x_new = INDEX_TO_X(index_to_move_to);
			y_new = INDEX_TO_Y(index_to_move_to);
			position = XY_TO_POS(x_new, y_new);
			path[moves] = position;

			/* updating bitarr */
			bitarr = bitarr | ((size_t)1 << index_to_move_to);
			
			status = SearchPath(path, bitarr, position, moves, limit);
			if (SUCCESS == status)
			{
				return SUCCESS;
			}
			else if (TIME_EXCEEDED == status)
			{
				return TIME_EXCEEDED;
			}
			
			/* backtracking -> undo the position visited */
			bitarr = bitarr & (~((size_t)1 << index_to_move_to));
		}
	}
	
	return BAD_PATH;
}

static knights_tour_status_e SearchWandrof(position_t *path,
										   size_t bitarr,
										   position_t position,
										   time_t limit)
{
	size_t i = 0;
	size_t next_move = 0;
	int x = POS_TO_X(position);
	int y = POS_TO_Y(position);
	int index_to_move_to = 0;
	
	
	for (i = 0; i < PATH_LENGTH; ++i)
	{
		/* check if time exceeded */
		if (time(NULL) >= limit)
		{
			return TIME_EXCEEDED;
		}
		
		/* update the path with the visited position */
		path[i] = XY_TO_POS(x, y);
		
		/* finiding the next valid move with the least amount of next moves */
		next_move = NextMove(bitarr, x, y);
		
		/* updating new index */
		index_to_move_to = lut_moves[next_move](x,y);
		
		/* updating x and y to new indexes */
		x = INDEX_TO_X(index_to_move_to);
		y = INDEX_TO_Y(index_to_move_to);

		/* updating bitarr */
		bitarr = bitarr | ((size_t)1 << index_to_move_to);
	}
		
	if (END_RESULT == bitarr)
	{
		return SUCCESS;
	}
	
	return BAD_PATH;
}

static int Valid(size_t i, size_t bitarr, int x, int y, size_t moves)
{
    int index_to_move_to = lut_moves[i](x, y);
    
    if (index_to_move_to == PATH_LENGTH + 1)
    {
        return 0;
    }
 
    if (((bitarr >> index_to_move_to) & 1) == 1)
    {
        return 0;
    }
    
    if (PATH_LENGTH <= moves)
    {
        return 0;
    }
    
    return 1;
}

static void ComputeWarndrofLut(size_t bitarr)
{
	size_t i = 0;
	size_t j = 0;
	
	for (; i < PATH_LENGTH; ++i)
	{
		warndrof_lut[i] = 0;
		
		for (j = 0; j < NUM_OF_MOVES; ++j)
		{
			if (Valid(j, bitarr, INDEX_TO_X(i), INDEX_TO_Y(i), 0))
			{
				++warndrof_lut[i];
			}
		}
	}
}

static size_t NextMove(size_t bitarr, int x, int y)
{
	int min_index_value = NUM_OF_MOVES;
	int index_to_move_to = 0;
	size_t min_pos_move_index = 0;
	size_t i = 0;
	size_t moves = 0;
	
	/* updating the entire lut for everywhere we already visited */
	ComputeWarndrofLut(bitarr);
	
	for (; i < NUM_OF_MOVES; ++i)
	{
		/* check if the move is valid */
		if (Valid(i, bitarr, x, y, moves))
		{
			index_to_move_to = lut_moves[i](x,y);
			/* finding the move with the least amount of next possible moves */
			if (warndrof_lut[index_to_move_to] < min_index_value)
			{
				min_pos_move_index = i;
				min_index_value = warndrof_lut[index_to_move_to];
			}
		}
	}
	
	return min_pos_move_index;
}

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





