#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <ctype.h>
#include <time.h>
#include "myheader.h"
void *currentfont;
#define sizes 7
#define MAXI 7
char push[] = "Push", pop[] = "Pop", insert[7] = "Insert", del[] = "Delete", empty[] = "Stack is Empty!";
char over[] = "OverFlow", under[] = " Underflow", emp[] = " No elements to display in queue";



class button
{
	int x1, y1, x2, y2;
	int state;
	char str[10];

public:
	button()
	{

	}
	button(int x11, int y11, int x22, int y22, char *str1)
	{
		x1 = x11;
		y1 = y11;
		x2 = x22;
		y2 = y22;
		state = 1;
		strcpy_s(str, str1);
	}
	void draw();
	void togglestate();
	int insidebutton(int x, int y);
};

class stack
{
	button s[sizes];
	int top;

public:
	stack()
	{
		top = -1;
	}
	int stfull();
	button pop();
	void push(int item);
	int stempty();
	void displaystack();
};
stack st;

class queu
{
	button que[MAXI];
	int front, rear;
public:
	queu()
	{
		front = -1;
		rear = -1;
	}
	void displayqueue();
	void insert_element();
	void delete_element();
};
queu q;

void setFont(void *font)
{
	currentfont = font;
}

void drawstring(float x, float y, char string[50])
{
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, *c);
	}
}

void button::draw()
{
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(1.0, 1.0, 1.0);
	drawstring(x1 + 10, y1 + 10, str);
	glColor3f(0.2, 0.2, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
	if (state == 0)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
	else if (state == 1)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glEnd();
	}
}

void button::togglestate(void)
{
	/*if(state==1)
		state=0;
	else if(state==0)
		state=1;*/
	state = (state == 1) ? 0 : 1;
}

int button::insidebutton(int x, int y)
{
	if (x > x1&&x<x2&&y>y1&&y < y2)
		return 1;
	else return 0;
}
button btn1(100, 100, 175, 150, push);
button btn2(200, 100, 275, 150, pop);
button btn3(300, 100, 375, 150, insert);
button btn4(400, 100, 475, 150, del);

//
// Stack functions start
//
int stack::stfull() {
	if (st.top >= sizes - 1)
		return 1;
	else
		return 0;
}

void stack::push(int item) {
	char str[10];
	snprintf(str, sizeof(str), "%d", item);
	button btn(100, 250 + st.top * 50, 150, 300 + st.top * 50, str);
	st.top++;

	st.s[st.top] = btn;

}

int stack::stempty() {
	if (st.top == -1)
		return 1;
	else
		return 0;
}

button stack::pop() {
	button item;
	item = st.s[st.top];
	st.top--;

	return (item);
}

void stack::displaystack() {
	int i;
	if (st.stempty())
		drawstring(10, 10, empty);
	if (st.stfull()) {
		drawstring(10, 10, over);
		for (i = st.top; i >= 0; i--)
			st.s[i].draw();

	}

	else {
		for (i = st.top; i >= 0; i--)
			st.s[i].draw();
	}
}
//
//stack functions end
//
//

// queue function starts
//
void queu::insert_element()
{
	static int num = 0;
	char str[10];
	snprintf(str, sizeof(str), "%d", num++);
	button btn(300, 250 + rear * 50, 350, 300 + rear * 50, str);
	if (rear == MAXI - 1 && front != MAXI - 1)
		drawstring(10, 10, over);
	else if (front == -1 && rear == -1)
	{
		front = rear = 0;
		que[rear] = btn;

	}
	else if (rear == MAXI - 1 && front != 0)
	{
		rear = 0;
		que[rear] = btn;
	}
	else
	{
		rear++;
		que[rear] = btn;
	}
}
void queu::delete_element()
{
	button element;
	if (front == -1)
	{
		drawstring(300, 10, under);
	}
	element = que[front];
	if (front == rear)
		front = rear = -1;
	else
	{
		if (front == MAXI - 1)
			front = 0;
		else
			front++;
		//     printf("\n The deleted element is: %s",element.str);
	}

}

void queu::displayqueue()
{
	int i;


	if (rear == MAXI - 1 && front == 0) {
		drawstring(300, 10, over);
		for (i = front; i <= rear; i++)
		{
			que[i].draw();
		}
	}

	else if (rear == MAXI - 1) {
		drawstring(300, 10, over);
		for (i = front; i <= rear; i++)
		{
			que[i].draw();
		}
	}
	if (front == -1)
		drawstring(300, 10, emp);

	else
	{
		//     printf("\n The queue elements are:\n ");
		for (i = front; i <= rear; i++)
		{
			que[i].draw();
		}
	}
}
//
// queue function ends
//

void output(int x, int y, char const*string)
{
	glColor3f(0, 0, 0);
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	glFlush();
}

void displaystacknqueue()
{
	st.displaystack();
	q.displayqueue();
}
void display()
{
	glClearColor(0.8, 0.2, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	btn1.draw();
	btn2.draw();
	btn3.draw();
	btn4.draw();
	displaystacknqueue();
	output(5, 570, "Click Right Mouse Button For More Options");
	glFlush();
	glutSwapBuffers();
	//glutPostRedisplay();
}


//1st function
// initialize the values requried
void myinit() {
	// background
	glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SCREEN_X, 0.0, SCREEN_Y);


	// creates color of cube and outline color
	int i;
	for (i = 0; i < 15; i++) {
		queue[i].r = 0;
		queue[i].g = 0.25;
		queue[i].b = 0.75;
		queue[i].rl = 1;
		queue[i].gl = 0;
		queue[i].bl = 0;
	}

	float step = DIST / MAX;
	queue[0].x1 = OFFSET_X;
	queue[0].x2 = queue[0].x1 + step;

	for (i = 1; i <= 15; i++) {
		queue[i].x1 = queue[i - 1].x1 + step;
		queue[i].x2 = queue[i].x1 + step;
	}

}





//2nd function
//function to draw a square
void square(int x1, int y1, int x2, int y2) {
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}





//3rd function
//function to draw the outline the square
void drawOutline(int x1, int y1, int x2, int y2) {
	int temp;
	if (x1 < x2) {
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 < y2) {
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}





//4th function
//function to draw a string to the output screen
void drawString(const char *str, double x = 0, double y = 0, double size = 5.0) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 4.0);
	glColor3f(1, 0, 0);
	int itemCt = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}






//5th function
//function to draw the queue arrow anywhere requried
void drawArrow(int x1, const char* s) {
	glBegin(GL_LINES);
	glVertex2f(x1, 3 * SCREEN_Y / 4);
	glVertex2f(x1, 3 * SCREEN_Y / 4 - ARROW_LENGTH);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, 3 * SCREEN_Y / 4 - ARROW_LENGTH);
	glVertex2f(x1 - ARROW_LENGTH / 4, 3 * SCREEN_Y / 4 - ARROW_LENGTH + ARROW_LENGTH / 4);
	glVertex2f(x1 + ARROW_LENGTH / 4, 3 * SCREEN_Y / 4 - ARROW_LENGTH + ARROW_LENGTH / 4);
	glEnd();
	if (strcmp(s, "BACK"))
		drawString(s, x1 - ARROW_LENGTH / 3, 3 * SCREEN_Y / 4 + ARROW_LENGTH / 2, 1.0 / (2 * FONT_RATIO));
	else
		drawString(s, x1 - ARROW_LENGTH / 3, 3 * SCREEN_Y / 4 + ARROW_LENGTH / 4, 1.0 / (2 * FONT_RATIO));
}






//6th function
//function to display all things to the screen
void displayEQDQ() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	strcpy_s(displayString, enter_str);
	strcat_s(displayString, blinking);

	drawString(displayString, ENTER_POSITION_X, ENTER_POSITION_Y, 1.0 / (FONT_RATIO));

	for (int i = 0; i < b; i++) {
		glColor3f(queue[i].r, queue[i].g, queue[i].b);
		square(queue[i].x1, SCREEN_Y / 2, queue[i].x2, SCREEN_Y / 2 + YD);
		glColor3f(queue[i].rl, queue[i].gl, queue[i].bl);
		drawOutline(queue[i].x1, SCREEN_Y / 2, queue[i].x2, SCREEN_Y / 2 + YD);
		if (queue[i].r != 1.0 || queue[i].b != 1.0 || queue[i].g != 1.0) {
			double ln = strlen(queue[i].num);
			double width = queue[i].x2 - queue[i].x1;
			double step = width / (ln + 1);
			double step_y = YD / 4;
			drawString(queue[i].num, queue[i].x1 + step, SCREEN_Y / 2 + step_y, 1.0 / FONT_RATIO);
		}
	}

	drawArrow(queue[f].x1 + OFFSET_X / 2, "FRONT");
	drawArrow(queue[b].x1 + OFFSET_X / 2, "BACK");
	if (enqORdq == ENQUEUE1)
		drawString("LAST OPERATION: ENQUEUE from front", OPERATION_POSITION_X, OPERATION_POSITION_Y + 50, 1.0 / (FONT_RATIO));
	else if (enqORdq == ENQUEUE2)
		drawString("LAST OPERATION: ENQUEUE from back", OPERATION_POSITION_X, OPERATION_POSITION_Y + 50, 1.0 / (FONT_RATIO));
	else if (enqORdq == DEQUEUE1)
		drawString("LAST OPERATION: DEQUEUE from front", OPERATION_POSITION_X, OPERATION_POSITION_Y + 50, 1.0 / (FONT_RATIO));
	else if (enqORdq == DEQUEUE2)
		drawString("LAST OPERATION: DEQUEUE from back", OPERATION_POSITION_X, OPERATION_POSITION_Y + 50, 1.0 / (FONT_RATIO));
	else
		drawString("LAST OPERATION: NO OPERATION YET", OPERATION_POSITION_X, OPERATION_POSITION_Y + 50, 1.0 / (FONT_RATIO));

	//message
	if (message == EMPTY) {
		drawString("QUEUE EMPTY!", OPERATION_POSITION_X + 80, OPERATION_POSITION_Y, 1.0 / (FONT_RATIO));
	}
	else if (message == FULL) {
		drawString("QUEUE FULL!", OPERATION_POSITION_X + 80, OPERATION_POSITION_Y, 1.0 / (FONT_RATIO));
	}

	//instructions
	drawString("Instructions:", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y + 60, 1.0 / (1.5*FONT_RATIO));
	drawString("Press I or i to enqueue from back", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y + 40, 1.0 / (2 * FONT_RATIO));
	drawString("Press O or o to enqueue from front", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y, 1.0 / (2 * FONT_RATIO));
	drawString("and F or f to dequeue from front.", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y - 20, 1.0 / (2 * FONT_RATIO));
	drawString("and B or b to dequeue from back.", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y + 20, 1.0 / (2 * FONT_RATIO));
	drawString("Press E or e to Exit.", OPERATION_POSITION_X - 180, OPERATION_POSITION_Y - 40, 1.0 / (2 * FONT_RATIO));
	output(5, 10, "Click Right Mouse Button For More Options");
	glutSwapBuffers();
}




//7th function
//adding datavalue from the back end of the queue
void backEnqueue(char *s) {
	int len = strlen(s);
	int i;
	if (b < MAX) {
		len = strlen(s);
		for (i = 0; i < len - 1 && s[i] == '0'; i++);
		strcpy_s(queue[b].num, s + i);

		queue[f].r = 0;
		queue[f].g = 0.25;
		queue[f].b = 0.75;

		queue[f].rl = 1;
		queue[f].gl = 0;
		queue[f].bl = 0;

		b++;
		enqORdq = ENQUEUE2;
		message = NO_MESSAGE;
	}
	if (b == MAX)
		message = FULL;
}







//8th function
//adding datavalue from the front end of the queue
void frontEnqueue(char *s) {
	int len = strlen(s);
	int i;
	if (f > 0) {
		len = strlen(s);
		f--;
		for (i = 0; i < len - 1 && s[i] == '0'; i++);
		strcpy_s(queue[f].num, s + i);

		queue[f].r = 0;
		queue[f].g = 0.25;
		queue[f].b = 0.75;

		queue[f].rl = 1;
		queue[f].gl = 0;
		queue[f].bl = 0;


		enqORdq = ENQUEUE1;
		message = NO_MESSAGE;
	}
	if (f == 0)
		message = FULL;
}





//9th function
// removing datavalue form the front end of the queue
void frontDequeue(void) {
	if (b <= 0 || b <= f) {
		message = EMPTY;
		return;
	}

	queue[f].r = BACKGROUND_R;
	queue[f].g = BACKGROUND_G;
	queue[f].b = BACKGROUND_B;

	queue[f].rl = BACKGROUND_R;
	queue[f].gl = BACKGROUND_G;
	queue[f].bl = BACKGROUND_B;

	f++;
	enqORdq = DEQUEUE1;
	message = NO_MESSAGE;

	if (b <= f) {
		message = EMPTY;
	}
	if (b >= MAX)
		message = FULL;
}






//10th function
//removing datavalue from the back end of the queue
void backDequeue(void) {
	if (f >= MAX || f >= b) {
		message = EMPTY;
		return;
	}


	b--;
	enqORdq = DEQUEUE2;
	message = NO_MESSAGE;
	if (f >= b) {
		message = EMPTY;
	}
	if (b >= MAX)
		message = FULL;
}







//11th function
//to check which is greater of two values
int max(int a, int b) {
	return a ? (a > b) : b;
}








//12th function
//funtion to get input from the user by keyboard
void mykey(unsigned char key, int x, int y) {

	if (key == 'C' || key == 'c')
		glutDisplayFunc(display);
	// glutPostRedisplay();
   //display();


	int len = strlen(enter_str);
	if ((key == 'F' || key == 'f') && (cnt_of_chars == 0))
		frontDequeue();
	if ((key == 'B' || key == 'b') && (cnt_of_chars == 0))
		backDequeue();
	if ((key == 'E' || key == 'e') && (cnt_of_chars == 0))
		exit(0);
	else if (isdigit(key) && strlen(enter_str) <= 28) {
		enter_str[len + 1] = '\0';
		enter_str[len] = key;
		cnt_of_chars++;
	}
	else if (key == '\b' && len > start_of_num) {
		enter_str[len - 1] = '\0';
		cnt_of_chars--;
	}
	else if (key == 'i' || key == 'I') {
		char newint[4];
		strncpy_s(newint, enter_str + start_of_num, 3);
		if (newint[0]) {
			backEnqueue(newint);
			enter_str[start_of_num] = '\0';
		}
		cnt_of_chars = 0;
	}
	else if (key == 'o' || key == 'O') {
		char newint[4];
		strncpy_s(newint, enter_str + start_of_num, 3);
		if (newint[0]) {
			frontEnqueue(newint);
			enter_str[start_of_num] = '\0';
		}
		cnt_of_chars = 0;
	}
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	static int itemno = 0;
	y = 600 - y;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (btn1.insidebutton(x, y))
		{
			btn1.togglestate();
			if (!st.stfull())
				st.push(itemno++);
		}
		if (btn2.insidebutton(x, y))
		{
			btn2.togglestate();
			if (!st.stempty())
				st.pop();

		}
		if (btn3.insidebutton(x, y))
		{
			btn3.togglestate();
			q.insert_element();
		}
		if (btn4.insidebutton(x, y))
		{
			btn4.togglestate();
			q.delete_element();
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (btn1.insidebutton(x, y))
		{
			btn1.togglestate();
		}
		if (btn2.insidebutton(x, y))
		{
			btn2.togglestate();
		}
		if (btn3.insidebutton(x, y))
		{
			btn3.togglestate();
		}
		if (btn4.insidebutton(x, y))
		{
			btn4.togglestate();
		}
	}
	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}




void display_about(void)
{
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 0.0, 0.0);
	output(50, 550, "JSS ACADEMY OF TECHNICAL EDUCATION");
	output(175, 500, "COMPUTER GRAPHICS");
	output(200, 450, "MINI PROJECT ON");
	output(200, 400, "STACK AND QUEUE");
	output(50, 300, "By:");
	output(70, 250, "SOWMYA.H.S (1JS16CS104)");
	output(70, 200, "TEJAASWINI.M (1JS16CS112)");
	output(5, 40, "Click Right Mouse Button For More Options");
	//output(250, 030, "Press N/n to know more");
	output(5, 010, "Press E/e to Exit");
	//glFlush();
	glutSwapBuffers();
}



void mymenu(int option)
{
	switch (option)
	{
	case 11:
		glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display);
		break;
	case 22:
		glDisable(GL_DEPTH_TEST);
		strcpy_s(enter_str, "Enter Element to Queue: ");
		start_of_num = strlen("Enter Element to Queue: ");
		glutDisplayFunc(displayEQDQ);
		break;
	case 33:
		glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display_about);
		break;
	case 44:
		exit(0);
	}
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -10, 10);
	else
		glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glutSwapBuffers();
}





//13th function
//main funtion where all the action takes place
int  main(int argc, char **argv) {
	/*char number[1000];
	int i, j, len;
	char c;
	strcpy_s(enter_str, "Enter Element to Queue: ");
	start_of_num = strlen("Enter Element to Queue: ");
jump:
	printf("\n\n\n");
	printf("------------------------------------\n");
	printf("Simulation of  deQueue in OpenGL\n");
	printf("------------------------------------\n\n");
	printf("Enter the number of elements in the deQueue\n(Not greater than 15 and not lesser than 3):\n");
	scanf_s("%d", &MAX);

	while (MAX > 15 || MAX < 3) {
		printf("ERROR: Invalid value! \nEnter again: ");
		scanf_s("%d", &MAX);
	}
	printf("\n\nVALUE ACCEPTED! Program Running...\n");*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("STACK AND QUEUE");
	glutCreateMenu(mymenu);
	glutAddMenuEntry("Stack and Queue", 11);
	glutAddMenuEntry("Enqueue and Dequeue", 22);
	glutAddMenuEntry("Home", 33);
	glutAddMenuEntry("Exit", 44);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display_about);
	printf("Stack and Queue sizes are 7 each");
	//glutReshapeFunc(myReshape);
	glutKeyboardFunc(mykey);
	glutMouseFunc(mouse);
	myinit();
	//glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}