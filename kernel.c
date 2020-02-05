#include <GL/glut.h>       
#include <GL/gl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void drawBitmapText(char *string,float x,float y); 
void pid_number(char pid_info[][20]);
void DoMenu(int value);
void mouseWheel(int, int, int, int);


char nam[15]={'1'};


void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT); 
	char *filename;
	int fd,fc,i,j, count, x=0, y=0;
	int readn;
	char nam_re[25]={};
	char buf[1]={};
	char pid_info[250][20] = {};
	char vm_info[2000][2000] = {};
	char add_info[100][100] = {};
	char image_info[100][40] = {};
	float posi_x=-0.95, posi_y=0.95;


	pid_number(pid_info);

	
	for(i=0; i<250; i++){                      // pid_number loading
		if(pid_info[i] == NULL)
			break;
		drawBitmapText(pid_info[i],posi_x,posi_y); // pid_number text output
		posi_y -= 0.05;
		if(posi_y <= -1){
			posi_x += 0.10;
			posi_y = 0.95;
		}
	}

	drawBitmapText("Present Process ID :",-0.35,0.95);       //PID output
	drawBitmapText(nam,-0.15,0.95);

	//sprintf(nam_re,"%s%s%s","/proc/",nam,"/maps");
	

	//filename = nam_re;

	fd = open("text2.txt", O_RDONLY);


	while((readn = read(fd, buf, 1)) > 0)  //vm_info load
	{

	
		if((int)buf[0] != 10)   //ascii code 10
		{
			vm_info[x][y] = buf[0];
			y+=1;
		}
		else
		{
			x+=1;
			y=0;
		}	

	}
	close(fd);


	for(i =5; i<100 ; i++){              //address_info
		for(j=26 ; j<34 ; j++){
			add_info[i][j-26] = vm_info[i][j];
			//if(add_info[i][j] == 32) break;
		}
		add_info[i][8]= '-';
		for(j=47;j<55;j++){
			add_info[i][j-38]=vm_info[i][j];
		}
	}

	for(i = 5; i<100 ; i++){              // image_info
		for(j=60 ; j<90 ; j++){
			image_info[i][j-60] = vm_info[i][j];
		}
	}




	posi_x = 0.9;
	posi_y = 0.865;
	for(i=5; i<55; i++){	                         //draw to rectangle
		if(image_info[i][0] == 0){
			glBegin(GL_QUADS);
			glColor3f(1,0,0);
		 	glVertex2f(-0.35, posi_x);
	 		glVertex2f(-0.35, posi_y);
	 		glVertex2f(0, posi_y);//0
	 		glVertex2f(0, posi_x);//0
			glColor3f(1,1,1);
			glEnd();
			}
		else{
			glBegin(GL_LINE_LOOP);
		 	glVertex2f(-0.35, posi_x);
	 		glVertex2f(-0.35, posi_y);
	 		glVertex2f(0, posi_y);
	 		glVertex2f(0, posi_x);
			glEnd();
		}
		posi_x-=0.035;
		posi_y-=0.035;
		//printf(" i value : %d",i);
	}

	posi_x = 0.9;
	posi_y = 0.865;
	for(i=55; i<105; i++){	                         //draw to rectangle
		if(image_info[i][0] == 0){
			glBegin(GL_QUADS);
			glColor3f(1,0,0);
		 	glVertex2f(+0.35, posi_x);
	 		glVertex2f(+0.35, posi_y);
	 		glVertex2f(0.7, posi_y);//0
	 		glVertex2f(0.7, posi_x);//0
			glColor3f(1,1,1);
			glEnd();
			}
		else{
			glBegin(GL_LINE_LOOP);
		 	glVertex2f(+0.35, posi_x);
	 		glVertex2f(+0.35, posi_y);
	 		glVertex2f(0.7, posi_y);
	 		glVertex2f(0.7, posi_x);
			glEnd();
		}
		posi_x-=0.035;
		posi_y-=0.035;
		//printf(" i value : %d",i);
	}

	drawBitmapText("Virtual Memory",-0.25,-0.95);




	
	posi_x = 0.05;
	posi_y = 0.85;

	for(i=5; i<55; i++){                      // pid_image loading
		if(vm_info[i] == NULL)
			break;
		drawBitmapText(image_info[i],posi_x,posi_y+0.03);
		posi_y -=0.035;
	}

	posi_x = -0.25;  //init
	posi_y = 0.85;

	for(i=55; i<105; i++){                      // pid_image loading
		if(vm_info[i] == NULL)
			break;
		drawBitmapText(image_info[i],posi_x+1,posi_y+0.03);
		posi_y -=0.035;
	}

	posi_x = -0.25;  //init
	posi_y = 0.85;


	for(i=5; i<55; i++){                      // addr loading
		if(vm_info[i] == NULL)
			break;
		drawBitmapText(add_info[i],posi_x,posi_y+0.028);
		posi_y -=0.035;
	}

	posi_x = -0.25;  //init
	posi_y = 0.85;

	
	for(i=55; i<105; i++){                      // addr loading
		if(vm_info[i] == NULL)
			break;
		drawBitmapText(add_info[i],posi_x+0.7,posi_y+0.028);
		posi_y -=0.035;
	}



	glFlush(); 
}



void dotimer(int value)
{

	glutPostRedisplay();
	glutTimerFunc(150,dotimer,1);

}



void init()
{

}

int main(int argc, char** argv)
{

	glutInit(&argc,argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(2500,1500);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("VirtualMemory TeamProject_OpenGL"); 
	glutCreateMenu(DoMenu);
	glutAddMenuEntry("input pid",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutTimerFunc(150,dotimer,1);
	init();
	glutMainLoop();
	glutMouseWheelFunc(mouseWheel);


}

void DoMenu(int value)
{
	switch(value){
		case 1 :
			printf("process ID number :");
			fgets(nam,sizeof(nam),stdin);
			nam[strlen(nam)-1] = '\0'; 
			break;
	}

}





void drawBitmapText(char *string,float x,float y) 
{  
	char *c;
	glRasterPos2f(x,y);

	for (c=string; *c != 0; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}



void pid_number(char test[][20])
{

	char buf[1]={};
	int ze, x=0, y=0;
	int readk;



	system("ls /proc > test123.txt");
	ze = open("test123.txt", O_RDONLY);


	while((readk = read(ze, buf, 1)) > 0)
	{

		if((int)buf[0] > 64){       //ASCIIcode character
			break;
		}
		if((int)buf[0] != 10)   //개행문자 10
		{
			test[x][y] = buf[0];
			y+=1;
		}
		else
		{
			x+=1;
			y=0;
		}
	}

	close(ze);
}





void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
 	y = y + 10;
        // Zoom in
    }
    else
    {
        // Zoom out
    }

    return;
}




