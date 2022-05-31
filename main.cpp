// 408410990 踩地雷最終版 12/22 
 
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define DIRECTION_KEY 224
#define UP 72
#define DOWN 80 
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define f 102        

int Mine[18][18];
int Display[18][18];

void gotoxy(int xpos, int ypos)	{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void Random(int x,int y){
	int Random[256];
	int i,j,r,skip=0;
	for(i=0;i<256;i++){
		Random[i]=i;
	}
	
	Random[(y-1)*16+x-1]=Random[skip];
	skip+=1;
	if(x>1 && y>1){
		Random[(y-2)*16+x-2]=Random[skip];
		skip+=1;
	}
	if(y>1){
		Random[(y-2)*16+x-1]=Random[skip];
		skip+=1;
	}
	if(x<16 && y>1){
		Random[(y-2)*16+x]=Random[skip];
		skip+=1;
	}
	if(x>1){
		Random[(y-1)*16+x-2]=Random[skip];
		skip+=1;
	}
	if(x<16){
		Random[(y-1)*16+x]=Random[skip];
		skip+=1;
	}
	if(x>1 && y<16){
		Random[y*16+x-2]=Random[skip];
		skip+=1;
	}
	if(y<16){
		Random[y*16+x-1]=Random[skip];
		skip+=1;
	}
	if(x<16 && y<16){
		Random[y*16+x]=Random[skip];
		skip+=1;
	}
	
	srand(time(NULL));
	for(i=0;i<40;i++){
		r=rand()%(256-i-skip)+i+skip;
		Mine[Random[r]/16+1][Random[r]%16+1]=9;
		Random[r]=Random[i+skip];
	}
	for(j=0;j<17;j++){
		for(i=0;i<17;i++){
			if(Mine[j][i]==9){
				if(Mine[j-1][i-1]!=9) Mine[j-1][i-1]+=1;
				if(Mine[j-1][i]!=9) Mine[j-1][i]+=1;
				if(Mine[j-1][i+1]!=9) Mine[j-1][i+1]+=1;
				if(Mine[j][i-1]!=9) Mine[j][i-1]+=1;
				if(Mine[j][i+1]!=9) Mine[j][i+1]+=1;
				if(Mine[j+1][i-1]!=9) Mine[j+1][i-1]+=1;
				if(Mine[j+1][i]!=9) Mine[j+1][i]+=1;
				if(Mine[j+1][i+1]!=9) Mine[j+1][i+1]+=1;
			}
		}
	}
	return;
}

void Open(int x,int y){
	if(Mine[y-1][x-1]!=9 && Display[y-1][x-1]==0 && x>1 && y>1){
		if(Mine[y-1][x-1]==0){
			gotoxy(x*2-2,y-1);
			printf("  ");
			Display[y-1][x-1]=1;
			Open(x-1,y-1);
		}
		else{
			gotoxy(x*2-2,y-1);
			printf(" %d",Mine[y-1][x-1]);
			Display[y-1][x-1]=1;
		}
	}
	if(Mine[y-1][x]!=9 && Display[y-1][x]==0 && y>1){
		if(Mine[y-1][x]==0){
			gotoxy(x*2,y-1);
			printf("  ");
			Display[y-1][x]=1;
			Open(x,y-1);
		}
		else{
			gotoxy(x*2,y-1);
			printf(" %d",Mine[y-1][x]);
			Display[y-1][x]=1;
		}
	}
	if(Mine[y-1][x+1]!=9 && Display[y-1][x+1]==0 && x<16 && y>1){
		if(Mine[y-1][x+1]==0){
			gotoxy(x*2+2,y-1);
			printf("  ");
			Display[y-1][x+1]=1;
			Open(x+1,y-1);
		}
		else{
			gotoxy(x*2+2,y-1);
			printf(" %d",Mine[y-1][x+1]);
			Display[y-1][x+1]=1;
		}
	}
	if(Mine[y][x-1]!=9 && Display[y][x-1]==0 && x>1){
		if(Mine[y][x-1]==0){
			gotoxy(x*2-2,y);
			printf("  ");
			Display[y][x-1]=1;
			Open(x-1,y);
		}
		else{
			gotoxy(x*2-2,y);
			printf(" %d",Mine[y][x-1]);
			Display[y][x-1]=1;
		}
	}
	if(Mine[y][x+1]!=9 && Display[y][x+1]==0 && x<16){
		if(Mine[y][x+1]==0){
			gotoxy(x*2+2,y);
			printf("  ");
			Display[y][x+1]=1;
			Open(x+1,y);
		}
		else{
			gotoxy(x*2+2,y);
			printf(" %d",Mine[y][x+1]);
			Display[y][x+1]=1;
		}
	}
	if(Mine[y+1][x-1]!=9 && Display[y+1][x-1]==0 && x>1 && y<16){
		if(Mine[y+1][x-1]==0){
			gotoxy(x*2-2,y+1);
			printf("  ");
			Display[y+1][x-1]=1;
			Open(x-1,y+1);
		}
		else{
			gotoxy(x*2-2,y+1);
			printf(" %d",Mine[y+1][x-1]);
			Display[y+1][x-1]=1;
		}
	}
	if(Mine[y+1][x]!=9 && Display[y+1][x]==0 && y<16){
		if(Mine[y+1][x]==0){
			gotoxy(x*2,y+1);
			printf("  ");
			Display[y+1][x]=1;
			Open(x,y+1);
		}
		else{
			gotoxy(x*2,y+1);
			printf(" %d",Mine[y+1][x]);
			Display[y+1][x]=1;
		}
	}
	if(Mine[y+1][x+1]!=9 && Display[y+1][x+1]==0 && x<16 && y<16){
		if(Mine[y+1][x+1]==0){
			gotoxy(x*2+2,y+1);
			printf("  ");
			Display[y+1][x+1]=1;
			Open(x+1,y+1);
		}
		else{
			gotoxy(x*2+2,y+1);
			printf(" %d",Mine[y+1][x+1]);
			Display[y+1][x+1]=1;
		}
	}
	return;
}

int Result_Check(int t){
	int count=0;
	for(int j=1;j<17;j++){
		for(int i=1;i<17;i++){
			if(Mine[j][i]==9 && Display[j][i]==1){
				system("cls");
				printf("failed !!\n\n");
				printf("遊戲花費時間 : %d 秒",time(NULL)-t);
				return 0;
			}
			if(Mine[j][i]!=9 && Display[j][i]==1) count+=1;	
		}
	}
	if(count==216){
		system("cls");
		printf("Victory !!\n\n");
		printf("遊戲花費時間 : %d 秒",time(NULL)-t);
		return 0;
	}
	return 1;
}

int main(){
	int i,j,t=0,step=0,marked=0;
	int x=1,y=1;
	printf("\n  ");
	for(j=1;j<17;j++){
		for(i=1;i<17;i++){
			printf("■");
			Mine[j][i]=0;
		}
		printf("\n  ");
	}
	gotoxy(40,1);
	printf("地雷總數 : 40");
	gotoxy(40,3);
	printf("已使用標記 : 0");
	gotoxy(x*2,y);
	unsigned char key;
	while(Result_Check(t)){
		key=getch();
		switch(key){
			case DIRECTION_KEY:
				switch(key=getch()){
					case UP:
						if(y>1){
							y-=1;
							gotoxy(x*2,y);
						}
						break;
					case DOWN:
						if(y<16){
							y+=1;
							gotoxy(x*2,y);
						}
						break;
					case LEFT:
						if(x>1){
							x-=1;
							gotoxy(x*2,y);
						}
						break;
					case RIGHT:
						if(x<16){
							x+=1;
							gotoxy(x*2,y);
						}
						break;
				}
				break;
			case SPACE:
				if(step==0){
					Random(x,y);
					t = time(NULL); 
					step=1;
				}
				if(Display[y][x]==0){
					if(Mine[y][x]==9){
						printf("●");
					}
					else if(Mine[y][x]==0){
						printf("  ");
						Open(x,y);
					}
					else{
						printf(" %d",Mine[y][x]);
					}
					Display[y][x]=1;
					gotoxy(x*2,y);
				}
				break;
			case f:
				if(Display[y][x]==0){
					printf("★");
					Display[y][x]=2;
					marked+=1;
					gotoxy(53,3);
					printf("%d  ",marked);
				}
				else if(Display[y][x]==2){
					printf("■");
					Display[y][x]=0;
					marked-=1;
					gotoxy(53,3);
					printf("%d  ",marked);
				}
				gotoxy(x*2,y);
				break;
		}
	}
	getch();
	return 0;
}
