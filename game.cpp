#include<GL/gl.h>
#include<GL/glut.h>
#include<ctime>
#include "game.h"
#include<windows.h>
#include<bits/stdc++.h>

int snake_length = 5;
short sDirection = UP;
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
extern bool gameOver;
int gridX,gridY;
bool food = true;
int foodX=-1,foodY=-1;
extern int score;


void unit(int x,int y){
    glLoadIdentity();
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1){
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }
    glBegin(GL_LINE_LOOP);//connects the vartex and loop is formed
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void initGrid(int x,int y){
    gridX = x;
    gridY = y;
}

void drawGrid(){
    for(int x=0;x<gridX;x++){
        for(int y=0;y<gridY;y++){
            unit(x,y);
        }
    }
}

void random(int &xx,int &yy){
    int mxX = gridX-2;
    int mxY = gridY-2;
    int mn = 1;
    srand(time(NULL));
    xx = mn + rand()%(mxX-mn);
    yy = mn + rand()%(mxY-mn);
}

void drawFood(){
    if(food==true) random(foodX,foodY);
    food = false;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);
}

void drawSnake(){
    for(int i=snake_length-1;i>0;i--){
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }
    if(sDirection==UP) posY[0]++;
    else if(sDirection==DOWN) posY[0]--;
    else if(sDirection==RIGHT) posX[0]++;
    else if(sDirection==LEFT) posX[0]--;
    for(int i=0;i<snake_length;i++){
        if(i==0) glColor3f(0.0,1.0,0.0);
        else glColor3f(0.0,0.0,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1) gameOver = true;
    else if(posX[0]==foodX && posY[0]==foodY){
        snake_length++;
        score++;
        food = true;
        if(snake_length>Max){
            snake_length=Max;
            MessageBox(NULL,"You Win\nYou can still keep playing but the snake will not grow.","Awsome",0);
        }
    }
    for(int j=1;j<snake_length;j++){
        if(posX[j]==posX[0] && posY[j]==posY[0])
            gameOver=true;
    }
}

