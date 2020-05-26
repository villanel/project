#include<windows.h>        
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#define object_number 100 //物品数量
#define SIZE 21//地图大小
#define up 'w'//上
#define down 's'//下
#define left 'a'//左
#define right 'd'//右
#define quit 'q'//退出
int show_num;//效果显示
int ifshow [9];//效果是否已显示
struct {
int x;
int y;}position;//位置
struct{
 int health;
 int money;
 int padlock;
 int key;
}character;// 角色
void display_character();//函数原型
void printf_color_block(int);
void Setpox(int x,int y);
void init_carte ();
void display_card ();
int move_character ();
void init_character ();
int judge(int,int*);
int carte[SIZE][SIZE];
void Setpox(int x,int y){//设置坐标         
   COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
     CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);

}
void Setcolor(unsigned short color){//设置颜色
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,color);
}
void printf_color_block(int color){//打印方块
    Setcolor(color);
    printf("■");
}
void display(int num){//显示对应色块
    switch (num)
            {
            case 0 :
                printf_color_block(10);
                break;
            case 1 :
                printf_color_block(12);
                break;
            case 2 :
                printf_color_block(2);
                break;
            case 3 :
                printf_color_block(8);
                break;
            case 4 :
                printf_color_block(6);
                break;
            case 5 :
                printf_color_block(14);
                break;
            case 6 :
                printf_color_block(7);
                break;
            case 7 :
                printf_color_block(13);
                break;
            case 8 :
                printf_color_block(5);
                break;
            case 9 :
                printf_color_block(9);
                break;
                default:
                break;
            }
}
void init_characher(){//初始化角色
character.health=10;
character.money=0;
character.key=0;
character.padlock=0;
position.x=1;
position.y=1; 
show_num=0;
for(int i=1;i<=8;i++){
    ifshow[i]=0;
}
}
void init_carteAndcharacter (){//初始化地图与角色
memset(carte,0,SIZE*SIZE*sizeof(int));//地图坐标对应内容设为0
srand((unsigned)time(NULL));
for(int i=0;i<=object_number;i++){
carte[rand()%21][rand()%21]=rand()%8+1;//随机放置物品
}
carte[1][1]=9;//设置人物初始位置
init_characher();//初始化角色
}
void display_card(){//输出地图
    int j=0;
    for(int i=1;i<SIZE;i++){
        Setpox(1,i);
        for ( j=1;j<SIZE;j++){
           display(carte[i][j]);//显示对应色块
             }
    }
}
int judge(int num,int *point){//判断
    if(position.x==0||position.x==21||position.y==0||position.y==21){//判断是否越界
    position.x=*point;//回溯
    position.y=*(point+1);
    }
     switch (num)
           {case -1 :
                 exit(0);
                 break;
            case 0 ://草
                break;
            case 1 ://花
                character.health++;
                if((ifshow[1]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(12);
                printf("花！生命值获得提升");
                }
            case 2://树
                break;
                position.x=*point;
                position.y=*(point+1);
                if((ifshow[2]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(2);
                printf("这是树，你无法走过去");
                }
                break;
            case 3 ://石头
                position.x=*point;
                position.y=*(point+1);
                if((ifshow[3]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(8);
                printf("这是石头，你无法走过去"); 
                }
                break;
            case 4 ://钥匙
                character.key++;
                if(character.padlock!=0){character.money+=5;character.key--;character.padlock--;}
                if((ifshow[4]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(6);
                printf("这是一把钥匙，再找到一个挂锁或许会有惊喜呦");
                }
                break;
            case 5 ://金币
                character.money++;
                if((ifshow[5]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(14);
                printf("是金币！找到10个金币就可以获胜啦");
                }
                break;
            case 6 ://锁
                character.padlock++;
                if(character.key!=0){character.money+=5;character.key--;character.padlock--;}
                if((ifshow[6]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(7);
                printf("这是一个挂锁，有钥匙的话或许可以打开");
                }
                break;
            case 7 ://陷阱
                character.health-=8;
                character.money=0;
                if((ifshow[7]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(13);
                printf("是陷阱！你将会失去你拥有的金币，并扣去8点生命值");
                }
                break;
            case 8 ://怪物
                character.health-=5;
                if((ifshow[8]--)==0){
                Setpox(50,7+show_num);show_num++;
                printf_color_block(5);
                printf("是怪物！很不幸，你失去了5点生命值");
                }
                break;
                default:
                break;
            }if(num!=2&&num!=3&&num!=9){//人物移动
                carte[*point][*(point+1)]=0;
                carte[position.x][position.y]=9;
                *point=position.x;
                *(point+1)=position.y;}
                Setcolor(15);
                if(character.health<=0){
                    Setpox(1,25);
                    printf("你输了");
                    return 1;}
                if(character.money>=10){
                    Setpox(1,25);
                    printf("你赢了");
                    return 1;}    
                    return 0;

}
int  move_character(){    //移动角色并返回对应色块编号
    char str=' ';
        str=getch();
        if(str!=left&&str!=right&&str!=up&&str!=down&&str!=quit){
            return 9;
        }
        switch(str){
            case left :--position.y;break;
            case right : ++position.y;break;
            case up :--position.x;break;
            case down :++position.x;break;
            case quit :return -1;
        }
       
     return carte[position.x][position.y];
    }
    void display_character(){//显示角色属性
        Setcolor(15);
        Setpox(50,1);
        printf("health: %2d",character.health);
        Setpox(50,2);
        printf("money:  %2d",character.money);
        Setpox(50,3);
        printf("key:    %2d",character.key); 
         Setpox(50,4);
        printf("padlock:%2d",character.padlock);
        Setpox(50,6);
        printf_color_block(9);
        printf("character");}

int main(){//主方法
    restart:
    system("cls");
    int pre[2]={1,1};
    init_carteAndcharacter();
   while(1){
        display_character();
        display_card();
        int i=move_character();
        if (i==-1)return 0;
        int j=judge(i,pre);
        if(j==1){
          Setpox(1,23);
          printf("按任意键重新开始");
          getch();
          goto restart;
          }
    }
    return 0;
}