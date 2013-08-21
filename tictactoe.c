/*	Sun Jun  2 22:42:58 IST 2013
 *	author : nj
 *	A simple tictactoe game.
 *	The board is represented as a 3X3 matrix of characters.
 *	I have used the minmax algorithm for finding out the next
 *	move of the computer. 
 */

#include<stdio.h>

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

/*	enum to hold the state of the game board
 *	USERW -- the user has won
 *	COMPW -- the computer has won
 *	NONE -- it's a tie
 *	INCOMP -- the game's still on
 */
enum bstate { USERW, NONE, INCOM, COMPW };
/* enum to store players
 */
enum player { USR, COMP };
/* Function prototypes
 */

// returns the state of the game board
enum bstate check_winner(char[][3]);

// used to get the score for a particular board (after a move) for the computer
int get_score(char[][3], enum player);

// makes the move for the computer
void comp_move(char[][3]);

// draws the board from the 3X3 array -- board.
void draw_board(char[][3]);

int main()
{
    char board[3][3];
    int move;
    for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
	    	board[i][j] = ' ';
    draw_board(board);
    do {
		printf("Your Move : ");
		scanf("%d", &move);
		if (move >= 0 && move <= 8 && board[move / 3][move % 3] == ' ') {
			board[move / 3][move % 3] = 'X';
			draw_board(board);
		} else {
			printf("Invalid Move!!!\n");
			continue;
		}
		if (check_winner(board) != INCOM)
			break;
		comp_move(board);
		draw_board(board);
		if (check_winner(board) != INCOM)
			break;
    }
    while (1);

    if (check_winner(board) == COMPW)
		printf("Computer wins the Game. Better luck next time\n\n");
    else if (check_winner(board) == USERW)
		printf("You have won the game! \n\n");
    else
		printf("Damn! It's a draw.\n\n");
    return 0;
}

/* Function defintions
 */

void draw_board(char board[3][3])
{
    printf("___________\n");
    for (int i = 0; i < 9; ++i) {
	printf(" %c ", board[i / 3][i % 3]);
	if (i % 3 == 2) {
	    printf("\n-----------\n");
	    continue;
	}
	printf("|");
    }
    printf("\n\n");
    return;
}

enum bstate check_winner(char board[3][3])
{
    int user_num = 3 * 'X', comp_num = 3 * 'o';
    int s1, s2;
    for (int i = 0; i < 3; ++i) {
		s1 = s2 = 0;
	for (int j = 0; j < 3; j++) {
	    s1 += board[i][j];
	    s2 += board[j][i];
	}
	if (s1 == user_num || s2 == user_num)
	    return USERW;
	else if (s1 == comp_num || s2 == comp_num)
	    return COMPW;
    }

    s1 = board[0][0] + board[1][1] + board[2][2];
    s2 = board[0][2] + board[1][1] + board[2][0];
    if (s1 == user_num || s2 == user_num)
		return USERW;
    else if (s1 == comp_num || s2 == comp_num)
		return COMPW;
    for (int i = 0; i < 9; ++i)
		if (board[i / 3][i % 3] == ' ')
	    	return INCOM;
    return NONE;
}

int get_score(char board[3][3], enum player p)
{
    if (check_winner(board) != INCOM)
		return check_winner(board);
    int score = -1;
    for (int i = 0; i < 9; ++i) {
		if (board[i / 3][i % 3] == ' ') {
	    	if (p == USR) {
				board[i / 3][i % 3] = 'X';
				if (score == -1)
		    		score = get_score(board, COMP);
				else
		    		score = min(score, get_score(board, COMP));
	    	} else if (p == COMP) {
				board[i / 3][i % 3] = 'o';
				score = max(score, get_score(board, USR));
	    }
	    board[i / 3][i % 3] = ' ';
	}
    }
    return score;
}

void comp_move(char board[3][3])
{
    int best_move, move_score = -1;
    for (int i = 0; i < 9; ++i) {
		if (board[i / 3][i % 3] == ' ') {
			board[i / 3][i % 3] = 'o';
			if (get_score(board, USR) > move_score) {
				move_score = get_score(board, USR);
				best_move = i;
			}
			board[i / 3][i % 3] = ' ';
		}
    }
    board[best_move / 3][best_move % 3] = 'o';
    return;
}
