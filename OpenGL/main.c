/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 001
#include <stdio.h>
#include <GL/freeglut.h> 
#include <GL/gl.h>
#include <GL/glu.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

#define bool char
#define true 1
#define false 0

FT_Library  library;
FT_Face		face; // this is the font


//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;



bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // this gives us the pixel grid that we want (the same layout as SDL with 0,0 in the upper left hand corner.
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
	
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
	
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void render(){
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    //Render quad
    glBegin( GL_QUADS );
		glColor3f(1,0,0); glVertex2s( 100, 100 );
        glColor3f(0,1,0); glVertex2s( 100, 300 );
        glColor3f(0,1,1); glVertex2s( 300, 300 );
        glColor3f(1,0,1); glVertex2s( 300, 100 );
		/*
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
        */
        /*
        glVertex2f( 0.5f, 0.5f );
        glVertex2f( 0.5f, 0.8f );
        glVertex2f( 0.8f, 0.8f );
        glVertex2f( 0.8f, 0.5f );
        */
        
    glEnd();
    
    glutSwapBuffers();
    
}

void runMainLoop( int val );

//*********************************************
//* RenderToDisplay()                       *
//*********************************************

GLfloat UpwardsScrollVelocity = -10.0;
float view=20.0;

char quote[6][80];
int numberOfQuotes=0,i;



void RenderToDisplay()
{
    int l,lenghOfQuote, i;

    glTranslatef(0.0, -100, UpwardsScrollVelocity);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glScalef(0.1, 0.1, 0.1);



    for(  l=0;l<numberOfQuotes;l++)
    {
        lenghOfQuote = (int)strlen(quote[l]);
        glPushMatrix();
        glTranslatef(-(lenghOfQuote*37), -(l*200), 0.0);
        for (i = 0; i < lenghOfQuote; i++)
        {
            glColor3f((UpwardsScrollVelocity/10)+300+(l*10),(UpwardsScrollVelocity/10)+300+(l*10),0.0);
            glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
        }
        glPopMatrix();
    }

}


//this acts as a replacement for GL_FillRect
void GL_FillRect(int x, int y, int w, int h, int color){
	//clear the color buffer
	//glClear( GL_COLOR_BUFFER_BIT );
	// quadrilateral
	glBegin(GL_QUADS);
	//process color
	glColor3ub(color/0x10000, (color/0x100)&0xff, color&0xff );
	//generate verticies
	glVertex2s(x,   y	);
	glVertex2s(x+h, y	);
	glVertex2s(x+h, y+h	);
	glVertex2s(x,   y+h	);
	//end the quad
	glEnd();
	RenderToDisplay();
}


void my_draw_bitmap( FT_Bitmap *theBmp, int x, int y){
	FILE *myFile = fopen("outputFrom my_draw_bitmap.txt", "w");
	int i,j;
	for(i=0; i<theBmp->width; i++){
		for(j=0; j<24; j++){
			fprintf(myFile,"%d ", theBmp->buffer[i*24+j]);
		}
		fprintf(myFile,"\n");
	}
}



void FT_RenderText(){
	FT_GlyphSlot  slot = face->glyph;  /* a small shortcut */
	int           pen_x, pen_y, n;
	bool error;
	pen_x = 300;
	pen_y = 200;
	char text[] = "Hello World!";
	int num_chars = sizeof(text);
	for ( n = 0; n < num_chars; n++ ){
		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Char( face, text[n], FT_LOAD_RENDER );
		if ( error ){
			continue;  /* ignore errors */
			printf("Error");
		}
		/* now, draw to our target surface */
		my_draw_bitmap( &slot->bitmap,
						pen_x + slot->bitmap_left,
						pen_y - slot->bitmap_top );
		
		/* increment pen position */
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6; /* not useful for now */
	}
}





int main( int argc, char* args[] )
{
	strcpy(quote[0],"Luke, I am your father!.");
    strcpy(quote[1],"Obi-Wan has taught you well. ");
    strcpy(quote[2],"The force is strong with this one. ");
    strcpy(quote[3],"Alert all commands. Calculate every possible destination along their last known trajectory. ");
    strcpy(quote[4],"The force is with you, young Skywalker, but you are not a Jedi yet.");
    numberOfQuotes=5;
	
	
	//Initialize FreeGLUT
	glutInit( &argc, args );
	
	
	
	//Create OpenGL 2.1 context
	glutInitContextVersion( 2, 1 );
	
	//Create Double Buffered Window
	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" ); 
	
	//Do post window/context creation initialization
	if( !initGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
	}
	
	if( FT_Init_FreeType(&library)) exit(101); 
	//load the font
	if(FT_New_Face( library, "8bitoperator.ttf", 0, &face ) ) exit(102);
	//set font attributes
	if(FT_Set_Char_Size(
            face,    /* handle to face object           */
            0,       /* char_width in 1/64th of points  */
            16*64,   /* char_height in 1/64th of points */
            300,     /* horizontal device resolution    */
            300 ) ) exit(103);
	
	FT_RenderText();
	glutSwapBuffers();
	
	Sleep(3000);
	
	//Set rendering function
	glutDisplayFunc( render );
	
	//Set main loop
	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );
	
	//Start GLUT main loop
	glutMainLoop();
	
	return 0;
}



void runMainLoop( int val )
{
    render();
	
    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}
