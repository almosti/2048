#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <curses.h>
using namespace std;

#define N 4
#define WIDTH 5

#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2
#define  S_QUIT 3

class Game2048
{
private:
    /* data */
	int data[N][N];
	int status;


	void drawItem(int row, int col, char c)
	{
		move(row, col);
		addch(c);
	}

	void drawNum(int row, int col, int num)
	{
		while (num > 0)
		{
			drawItem(row, col, num % 10 + '0');
			num /= 10;
			--col;
		}
	}
public:
	Game2048(/* args */):status(S_NORMAL)
	{
		setTestData();
	}
    ~Game2048();

	int getStatus() { return status; }

	void processInput()
	{
		char ch = getch();
		if (ch >= 'a'&&ch <= 'z')
		{
			ch -= 32;
		}
		if (ch=='Q')
		{
			status = S_QUIT;
		}
		else
		{
			status = (status + 1) % 3;
		}
	}

    void draw(){
        clear();
        const int offset=12;
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){

                drawItem(i*2,1+j*WIDTH+offset,'+');

                if(i!=N){
                    drawItem(i*2+1,1+j*WIDTH+offset,'|');
                }

                for(int k=1;j!=N&&k<WIDTH;++k){
                    drawItem(i*2,1+j*WIDTH+k+offset,'-');
                }

                if(i!=N&&j!=N){
                    drawNum(i*2+1,(j+1)*WIDTH+offset,data[i][j]);
                }
            }
        }

		mvprintw(2 * N + 2, (5 * (N - 4) - 1) / 2, "W(UP),S(DOWN),A(LEFT),D(RIGHT),Q(QUIT)");
		mvprintw(2 * N + 3, 12 + 5 * (N - 4) / 2, "Mini Game");

		if (status==S_WIN)
		{
			mvprintw(N, 5 * N / 2 - 1, "YOU WIN");
		}
		else if(status==S_FAIL)
		{
			mvprintw(N, 5 * N / 2 - 1, "YOU LOSE");
		}
    }

	void setTestData()
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				data[i][j] = 16 << i << j;
			}
		}
	}
};


void initialize(){

    initscr();

    cbreak();

    noecho();

    curs_set(0);

    srand(time(NULL));
}

void shutdown(){
    endwin();
}

int main(){
    initialize();

	Game2048 game;
    do{
		game.draw();
		game.processInput();
    }while(S_QUIT!=game.getStatus ());

    shutdown();
    return 0;
}