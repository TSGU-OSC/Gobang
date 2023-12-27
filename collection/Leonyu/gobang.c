#include<bits/stdc++.h>
using namespace std;
char go[10][10]={' ','A','B','C','D','E','F','G','H','I'};
void put_all(char go[10][10])//初始化棋盘 
{
	for(int i=1;i<10;i++){
		for(int j=0;j<10;j++){
			go[i][j]='*';
		}
	}
}
void put_line(char go[10][10])//初始化纵标 
{
	for(int i=1;i<=9;i++){
		go[i][0]='0'+i;
	}
}
void print(char go[10][10])//输出棋盘 
{
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			cout<<go[i][j];
		}
		cout<<endl;
	}
}
bool judge(int x,int y,char here)
{
	int left=0,right=0,i=1;///////////////////////////////////列 
	while(go[x+i][y]==here){
		right++;
		i++;
	}
	i=1;
	while(go[x-i][y]==here){
		left++;
		i++;
	}
	if((right+left+1)>=5){
		return 1;
	}
	left=0,right=0,i=1;//////////////////////////////////////行 
	while(go[x][y+i]==here){
		right++;
		i++;
	}
	i=1;
	while(go[x][y-i]==here){
		left++;
		i++;
	}
	if((right+left+1)>=5){
		return 1;
	}
	left=0,right=0,i=1;/////////////////////////////////////右斜 
	while(go[x-i][y+i]==here){
		left++;
		i++;
	}
	i=1;
	while(go[x+i][y-i]==here){
		right++;
		i++;
	}
	if((right+left+1)>=5){
		return 1;
	}
	
	left=0,right=0,i=1;/////////////////////////////////////左斜 
	while(go[x-i][y-i]==here){
		left++;
		i++;
	}
	i=1;
	while(go[x+i][y+i]==here){
		right++;
		i++;
	}
	if((right+left+1)>=5){
		return 1;
	}
	return 0;
}
bool put_black()//下黑棋 
{
	char x,y;
	while(1){
		cin>>x>>y;
		if('1'<=x&&x<='9'&&'A'<=y&&y<='I'){
			if(go[x-'0'][y-'A'+1]=='*'){
				go[x-'0'][y-'A'+1]='X';//黑棋下棋 
				print(go);
				if(judge(x-'0',y-'A'+1,'X')){
					return 1;
				}
				break;
			}else{
				cout<<"已被落子，请重新下棋"<<endl;
			}
		}else{
			cout<<"请输入正确坐标"<<endl;
		}
	} 
	return 0;
}
bool put_white()//下白棋 
{
	char x,y;
	while(1){
		cin>>x>>y;
		if('1'<=x&&x<='9'&&'A'<=y&&y<='I'){
			if(go[x-'0'][y-'A'+1]=='*'){
				go[x-'0'][y-'A'+1]='O';//黑棋下棋 
				print(go);
				if(judge(x-'0',y-'A'+1,'O')){
					return 1;
				}
				break;
			}else{
				cout<<"已被落子，请重新下棋"<<endl;
			}
		}else{
			cout<<"请输入正确坐标"<<endl;
		}
	}
	return 0;
}
bool play(char go[10][10])///////////////////////////////////////////////////////////////////////////////// 
{
	while(1){
		if(put_black()){
			cout<<"black win";
			return 1;
		}
		if(put_white()){
			cout<<"white win";
			return 1;
		}
	}
	return 0;
}/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	put_all(go);
	put_line(go);
	print(go);
	play(go);
	return 0;
}