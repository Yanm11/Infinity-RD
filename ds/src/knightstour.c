#include <assert.h> /* assert */

#include "knightstour.h"

#define NUM_OF_MOVES 8
#define POS_TO_X(position) ((position & 0xF0) >> 4)
#define POS_TO_Y(position) (position & 0x0F)
#define XY_TO_POS(x, y) ((x << 4) + y)
#define XY_TO_INDEX(x,y) (x * NUM_OF_ROWS + y)
#define INDEX_TO_X(index) (index / NUM_OF_ROWS)
#define INDEX_TO_Y(index) (index % NUM_OF_ROWS)

typedef int (*func_ptr)(unsigned char, unsigned char);

static int Valid(size_t i, size_t bitarr, position_t position);

static int UpLeft(unsigned char x, unsigned char y);
static int UpRight(unsigned char x, unsigned char y);
static int LeftUp(unsigned char x, unsigned char y);
static int LeftDown(unsigned char x, unsigned char y);
static int DownLeft(unsigned char x, unsigned char y);
static int DownRight(unsigned char x, unsigned char y);
static int RightDown(unsigned char x, unsigned char y);
static int RightUp(unsigned char x, unsigned char y);

static func_ptr lut_moves[NUM_OF_MOVES] = {&UpLeft, &UpRight,
										   &DownLeft, &DownRight, 
										   &LeftDown, &LeftUp,
										   &RightDown, &RightUp};

position_t BuildPosition(unsigned char row, unsigned char col)
{
	return XY_TO_POS(row,col);
}
 
knights_tour_status_e RunKnightsTour(position_t path[PATH_LENGTH], 
                                     position_t starting_position, 
                                     int use_heuristic, 
                                     unsigned int time_limit)
{
	
}


/************ HELPER FUNCTION ****************/

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
		return 1;
	}
	
	++moves;
	
	for (i = 0; i < NUM_OF_MOVES; ++i)
	{
		if Valid(i, bitarr, x, y, moves)
		{
			/* updating new index */
			index_to_move_to = lut_moves[i](x,y);
			
			/* updating position */
			x = INDEX_TO_X(index_to_move_to);
			y = INDEX_TO_Y(index_to_move_to);
			position = XY_TO_POS(x,y);
			path[move] = position;
			
			/* updating bitarr */
			bitarr = bitarr | (1 << index_to_move_to);
			
			status = SearchPath(path, bitarr, position, moves);
			if (1 == status)
			{
				return 1;
			}
			
			
			 
			
		}
	}
	
	return 0
	
}

static int Valid(size_t i, size_t bitarr, int x, int y size_t moves)
{
	int index_to_move_to = lut_moves[i](x,y);
	
	if ((0 > index_to_move_to && PATH_LENGTH < index_to_move_to) ||
		((bitarr >> index_to_move_to) & 1) == 1 || PATH_LENGTH < moves)
	{
		return 0;
	}
	
	return 1
}

static int UpLeft(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x - 2, y - 1));
}

static int UpRight(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x - 2, y + 1));
}

static int LeftUp(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x - 1, y - 2));
}

static int LeftDown(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x + 1, y - 2));
}

static int DownLeft(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x + 2, y - 1));
}

static int DownRight(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x + 2, y + 1));
}

static int RightDown(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x + 1, y + 2));
}

static int RightUp(unsigned char x, unsigned char y)
{
	return (XY_TO_INDEX(x - 1, y + 2));
}







