#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"
#include<windows.h>
#include<bits/stdc++.h>
using namespace std;

#define COLUMNS 40
#define ROWS 40
#define FPS 10

string s;
extern short sDirection;
bool gameOver = false;
int score = 0;
char msg[50],text[50]=" your score is ";

void name_find(){
    name:
    cout<<"Enter your name: ";
    getline(cin,s);
    if(s.length()==0){
        cout<<"You didn't enter your name. Enter your name first: ";
        goto name;
    }
}

void display_callback(){
    glClear(GL_COLOR_BUFFER_BIT);//clear the pixels
    glLoadIdentity();
    drawGrid();//function on game.cpp
    drawSnake();
    drawFood();
    glutSwapBuffers();//displays the next frame
    if(gameOver==true){
        name_find();
        char _score[10];
        itoa(score,_score,10);
        for(int i=0;i<s.length();i++) msg[i]=s[i];
        strcat(msg,text);
        strcat(msg,_score);
        MessageBox(NULL,msg,"Game Over",0);
        exit(0);
    }
}

void reshape_callback(int w,int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);//sets the viewport of the window
    glMatrixMode(GL_PROJECTION);//our display type will be projection type
    glLoadIdentity();//load the start mode/type
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);//initialize our graph for window position
    glMatrixMode(GL_MODELVIEW);//work on model view mode
    glLoadIdentity();
}

void timer_callback(int){
    glutPostRedisplay();//calls the display function after the operation of the main function display
    glutTimerFunc(1000/FPS,timer_callback,0);
}


void keyboard_callback(int key,int x,int y){
    switch(key){
    case GLUT_KEY_UP:
        if(sDirection!=DOWN) sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP) sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT) sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT) sDirection=LEFT;
        break;
    }
}

void init(){
    glClearColor(0.0,0.0,0.0,1.0);//red,green,blue,alpha
    initGrid(COLUMNS,ROWS);//initialization of grid

}



int main(int argc, char **argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(1000,400);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake Game - hemel18681");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);//it will reshape my windows if it is move/increase/decrease
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}
