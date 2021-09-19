#include <unistd.h>
#ifndef MATRIX_H
# define MATRIX_H
# define N 4
# define SIZE ((N)*(N))
# define VOLUME ((N)*(N)*(N))
# define COL_UP 0
# define COL_DOWN 1
# define ROW_LEFT 2
# define ROW_RIGHT 3

// cube[i][j][k]의 값
# define OFF 0 
# define AVAIL 1
# define NUMBERED 2

// depth_check, search_cube의 반환값
# define PASS 0
# define PUT 1
# define STOP -1
# define NUMBERED 2

// find_way의 반환값
# define END 0
# define EXIT -1
// scan input -> init matrix, cube
#define TRUE 1
#define FALSE 0


#endif
int	g_end = FALSE;
void	input_numbers(char* input, int(*inputs)[N]);
void	print_matrix(int(*matrix)[N]);
void	init_matrix(int(*matrix)[N], int(*inputs)[N]);
void	set_matrix_input_N_col(int(*matrix)[N], int(*inputs)[N]);
void	set_matrix_input_N_row(int(*matrix)[N], int(*inputs)[N]);
void	set_matrix_input_1_col(int(*matrix)[N], int(*inputs)[N]);
void	set_matrix_input_1_row(int(*matrix)[N], int(*inputs)[N]);

void	manage_cube(int(*matrix)[N], int(*inputs)[N]);
void	init_cube(int(*matrix)[N], char(*cube)[N][N]);
void	set_cube(int(*matrix)[N], char(*cube)[N][N]);
void	paint_cube(char(*cube)[N][N], int row, int column, int height);
int		search_cube(char(*cube)[N][N], int(*matrix)[N]);
int		depth_check(char(*cube)[N][N], int row, int column, int* height);
void	sync_matrix(int(*matrix)[N], char(*cube)[N][N]);
void	copy_cube(char(*cube)[N][N], char(*pre_cube)[N][N]);
void	find_way(char(*pre_cube)[N][N], int(*inputs)[N], int remainder);

int	one_row_check(int(*matrix)[N], int(*inputs)[N], int i);
int	row_check(int(*matrix)[N], int(*inputs)[N]);
int	one_col_check(int(*matrix)[N], int(*inputs)[N],int i);
int	col_check(int(*matrix)[N], int(*inputs)[N]);
int	answer_check(int(*matrix)[N], int(*inputs)[N]);

/*=======================================================================*/
int	main(int argc, char* argv[])
{
	int	inputs[4][N];
	int	main_matrix[N][N];

	if (argc == 2)
	{
		input_numbers(argv[1], inputs);
		init_matrix(main_matrix, inputs);
		manage_cube(main_matrix, inputs);
	}
	if(!g_end)
		write(1, "Error\n", 6);
	return (0);
}
void	input_numbers(char* input, int(*inputs)[N])
{
	int	i;

	i = 0;
	while (*input)
	{
		if ('0' <= (*input) && (*input) <= '9')
		{
			inputs[0][i] = (*input) - '0';
			i++;
		}
		input++;
	}// input은 정상적으로 들어온다고 하자
}

void	print_matrix(int(*matrix)[N])
	{
		int	i;
		int	j;
		char number;

		i = 0;
		while (i < N)
		{
			j = 0;
			while (j < N)
			{
				number = '0' + matrix[i][j];
				write(1, &number, 1);
				if (j < N - 1)
					write(1, " ", 1);
				j++;
			}
			write(1, "\n", 1);
			i++;
		}
	}
void	init_matrix(int(*matrix)[N], int(*inputs)[N])
	{
		int i;
		int j;
		i = 0;
		while (i < N)
		{
			j = 0;
			while (j < N)
			{
				matrix[i][j] = 0;
				j++;
			}
			i++;
		}
		set_matrix_input_N_col(matrix, inputs);
		set_matrix_input_N_row(matrix, inputs);
		set_matrix_input_1_col(matrix, inputs);
		set_matrix_input_1_row(matrix, inputs);
	}	// 0으로 깔고 inputs 보고 고정점들 기입
void	set_matrix_input_N_col(int(*matrix)[N], int(*inputs)[N]) {
		int i;
		int j;

		i = 0;
		while (i < N) {
			if (inputs[COL_UP][i] == N)
			{
				j = 0;
				while (j++ < N)
					matrix[j - 1][i] = j;
			}
			if (inputs[COL_DOWN][i] == N)
			{
				j = 0;
				while (j++ < N)
					matrix[j - 1][i] = N + 1 - j;
			}
			i++;
		}
	}
void	set_matrix_input_N_row(int(*matrix)[N], int(*inputs)[N]) {
		int i;
		int j;

		i = 0;
		while (i < N) {
			if (inputs[ROW_LEFT][i] == N)
			{
				j = 0;
				while (j++ < N)
					matrix[i][j - 1] = j;
			}
			if (inputs[ROW_RIGHT][i] == N)
			{
				j = 0;
				while (j++ < N)
					matrix[i][j - 1] = N + 1 - j;
			}
			i++;
		}
	}
void	set_matrix_input_1_col(int(*matrix)[N], int(*inputs)[N])
	{
		int i;

		i = 0;
		while (i < N) {
			if (inputs[COL_UP][i] == 1)
			{
				matrix[0][i] = N;
				if (inputs[COL_DOWN][i] == 2)
					matrix[N - 1][i] = N - 1;
			}
			if (inputs[COL_DOWN][i] == 1)
			{
				matrix[N - 1][i] = N;
				if (inputs[COL_UP][i] == 2)
					matrix[0][i] = N - 1;
			}
			i++;
		}
	}
void	set_matrix_input_1_row(int(*matrix)[N], int(*inputs)[N]) {
		int i;

		i = 0;
		while (i < N) {
			if (inputs[ROW_LEFT][i] == 1)
			{
				matrix[i][0] = N;
				if (inputs[ROW_RIGHT][i] == 2)
					matrix[i][N - 1] = N - 1;
			}
			if (inputs[ROW_RIGHT][i] == 1)
			{
				matrix[i][N - 1] = N;
				if (inputs[ROW_LEFT][i] == 2)
					matrix[i][0] = N - 1;
			}
			i++;
		}
	}

void manage_cube(int(*main_matrix)[N], int(*inputs)[N])
{
	char main_cube[N][N][N];
	int signal;
	int remainder;
	int i;
	
	init_cube(main_matrix, main_cube);
	signal = search_cube(main_cube, main_matrix);
	if (signal == STOP)
	{
		g_end = TRUE;
		print_matrix(main_matrix);
	}
	else if (signal == PASS) // 백트래킹 시작
	{
		remainder = 0;
		i = 0;
		while (i < SIZE)
		{
			if (main_matrix[0][i] == 0)
				remainder++;
			i++;
		}
		find_way(main_cube, inputs, remainder);
	}
}
void init_cube(int(*matrix)[N], char(*cube)[N][N]) {
		int i;
		int j;
		int k;

		i = 0;
		while (i < N)
		{
			j = 0;
			while (j < N)
			{
				k = 0;
				while (k < N)
				{
					cube[i][j][k] = AVAIL;
					k++;
				}
				j++;
			}
			i++;
		}
		set_cube(matrix, cube);
	}
void set_cube(int (*matrix)[N], char(*cube)[N][N]) {
		int i;
		int j;

		i = 0;
		while (i < N)
		{
			j = 0;
			while (j < N)
			{
				if (matrix[i][j] != 0)
					paint_cube(cube, i, j, matrix[i][j]);
				j++;
			}
			i++;
		}
	}
void paint_cube(char (*cube)[N][N], int row, int column, int height) {
		int i;

		i = 0;
		while (i < N)
		{
			cube[i][column][height - 1] = OFF;
			cube[row][i][height - 1] = OFF;
			cube[row][column][i] = OFF;
			i++;
		}
		cube[row][column][height - 1] = NUMBERED;
	} // 숫자 놓을때 큐브에 OFF 칠하기
int	search_cube(char(*cube)[N][N], int(*matrix)[N])
{
	int height;
	int signal;
	int filled_box;
	int i;

	filled_box = 0;
	i = 0;
	while (i < SIZE) {
		signal = depth_check(cube, i / N, i % N, &height);
		if (signal == PUT)
		{
			paint_cube(cube, i / N, i % N, height); // cube에 반영하기 index를 가져다 놔버령
			matrix[i / N][i % N] = height;
			filled_box = 0;
			i = 0;
			continue;
		}
		else if (signal == NUMBERED)
			filled_box++;
		i++;
	}
	if (filled_box < SIZE)
		return PASS; // 백트래킹으로 넘어가세요
	return STOP; // 끝났으니 인쇄하세요
}
int depth_check(char(*cube)[N][N], int row, int column, int* height) {
		int avail;
		int i;

		avail = 0;
		i = 0;
		while (i < N)
		{
			if (cube[row][column][i] == NUMBERED)
				return NUMBERED;
			else if (cube[row][column][i] == AVAIL)
			{
				(*height) = i + 1;
				avail++;
			}
			i++;
		}
		if (avail == 1)
			return PUT;
		if (avail == 0)
			return STOP;
		return PASS;
	}
void sync_matrix(int(*matrix)[N], char(*cube)[N][N]) {
		int i;
		int j;

		i = 0;
		while (i < SIZE)
		{
			j = 0;
			while (!cube[0][i][j])
				j++;
			matrix[0][i] = j + 1;
			i++;
		}
	}
void copy_cube(char(*cube)[N][N], char(*pre_cube)[N][N]) {
		int i;

		i = 0;
		while (i < VOLUME)
		{
			cube[0][0][i] = pre_cube[0][0][i];
			i++;
		}
	}
void find_way(char(*pre_cube)[N][N], int(*inputs)[N], int remainder) {
	char cube[N][N][N];
	int	matrix[N][N];
	int signal;
	int height;
	int i;

	if (g_end)
		return;
	copy_cube(cube, pre_cube); // 이전 선택의 큐브로부터 복사해오기
	if (remainder == 0) // 뇌피셜이 끝났다면
	{
		sync_matrix(matrix, cube);
		if (answer_check(matrix, inputs))
		{
			print_matrix(matrix);
			g_end=TRUE;
		}
		return;
	}
	i = 0;
	while (i < SIZE) { // 선택지가 있는곳을 찾아야 해여
		// 선택지가 없다면 EXIT해야함
		// 있으면 다음놈을 선택해야함
		signal = depth_check(cube, i / N, i % N, &height);
		if (signal == NUMBERED) // 숫자가 들어있다면
		{
			i++;
			continue;
		}	// 다음 행렬칸으로 넘어간다
		else if (signal == STOP) // 끝나지 않았는데 막혔다면
			return; // 그길은 망한거야 접어

		height = 1;
		while (height <= N) // 여기서 가능한 공간에 대해
		{
			if (cube[i / N][i % N][height - 1] == AVAIL) {
				paint_cube(cube, i / N, i % N, height);
				find_way(cube, inputs, remainder - 1); // 다음 넘을 호출합니다
				copy_cube(cube, pre_cube);
			}
			height++;
		}
		i++;
	}
}

int	one_row_check(int(*matrix)[N], int(*inputs)[N], int i)
	{
		int	j;
		int	cnt[2];
		int	max[2];

		j = 0;
		max[0] = matrix[i][0];
		max[1] = matrix[i][N - 1];
		cnt[0] = 1;
		cnt[1] = 1;
		while (++j < N)
		{
			if (max[0] < matrix[i][j])
			{
				cnt[0]++;
				max[0] = matrix[i][j];
			}
			if (max[1] < matrix[i][N - j - 1])
			{
				cnt[1]++;
				max[1] = matrix[i][N - j - 1];
			}
		}
		if (inputs[ROW_LEFT][i] != cnt[0] || inputs[ROW_RIGHT][i] != cnt[1])
			return (FALSE);
		return (TRUE);
	}
int	row_check(int(*matrix)[N], int(*inputs)[N])
	{
		int	i;

		i = 0;
		while (i < N)
		{
			if (!one_row_check(matrix, inputs, i))
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
int	one_col_check(int(*matrix)[N], int (*inputs)[N], int i)
	{
		int	j;
		int	cnt[2];
		int	max[2];

		j = 0;
		max[0] = matrix[0][i];
		max[1] = matrix[N - 1][i];
		cnt[0] = 1;
		cnt[1] = 1;
		while (++j < N)
		{
			if (max[0] < matrix[j][i])
			{
				cnt[0]++;
				max[0] = matrix[j][i];
			}
			if (max[1] < matrix[N - j - 1][i])
			{
				cnt[1]++;
				max[1] = matrix[N - j - 1][i];
			}
		}
		if (inputs[COL_UP][i] != cnt[0] || inputs[COL_DOWN][i] != cnt[1])
			return (FALSE);
		return (TRUE);
	}
int	col_check(int(*matrix)[N], int(*inputs)[N])
	{
		int	i;

		i = 0;
		while (i < N)
		{
			if (!one_col_check(matrix, inputs, i))
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
int	answer_check(int(*matrix)[N], int(*inputs)[N])
	{
		return (row_check(matrix, inputs) && col_check(matrix, inputs));
	}


	// 큐브를 만들어가면서 백트래킹 하세요

// 하나밖에 없다면 확정
/*
되는놈 있는지 탐색 -> 을 순회한다
로우로 순회한다
컬럼으로 순회한다
계속 동기화해줘 2d랑 3d는
색칠하기
*/


//int	answer_check(int(*matrix)[N], int(*margin)[N], int(*inputs)[N]);  찾으면 1 반환해주세요 못찾으면 0
//void	print_matrix(int(*matrix)[N]); // matrix에 있는거 그냥 읽으시기만 하면 되여

/*
//#include "matrix.h"
	int	main(int argc, char* argv[])
	{
		int	inputs[4][N];
		//int	margin[4][N];
		int	main_matrix[N][N];
		int	i;
		/*
		if (argc == 2)
		{
			scan_input(argv[1],inputs);
			init_matrix(main_matrix,inputs);
			//search_cube(matrix);

			if (answer_check(matrix, margin, inputs))
				{
					print_matrix(matrix);
					return (0);
				}
		}
		write(1, "Error\n", 6);
		return (0);
}*/
