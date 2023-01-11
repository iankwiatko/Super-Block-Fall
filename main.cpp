/*
Super Cool Brick Fall
Grace Bittence and Ian Kwiatkowski
12/7/2021
Version 1.0
*/

//imports
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//Function Prototypes
void mainMenu();
void controlMenu();
void gameMenu();
void endMenu();
void creditsMenu();

//Button Class -- buttons for user to press
class Button{

    public:
    //constructor
    Button(float xInput, float yInput, float widthInput, float heightInput, char colorInput , char textInput[] );
    //buttonPress- uses given parameters to check wether the button has been pressed
    int buttonPress(float x, float xLower, float xUpper, float y, float yLower, float yUpper);
    //makeButton- creates the button on the screen.
    void makeButton();
    //x and y coordinates of button
    float x,y;

    private:
    //varaibles that attribute to charactersitics of the button -- names indicate what varibales represent.
    float width,height;
    char color;
    char text[20];
};
//Player Class -- player cube within the game
class Player{

    public:
    //constructor for player class
    Player(float xInput, float yInput, float widthInput, float heightInput, char colorInput );
    //playerDraw- draws player model on screen
    void playerDraw();
    //playerHit- checks to see if player was hit by projectile
    int playerHit(float xCheck, float yCheck);
    //playerMove- updates the position of the player model to the cursor x position
    void playerMove(float touchX);
    //x and y position of block
    float x,y;

    private:
    //varaibles that attribute to charactersitics of the button -- names indicate what varibales represent.
    float width,height;
    char color;
};
//Projectile Class -- bricks that fall onto the player.
class Projectile{

    public:
    //projectile constructor
    Projectile(float xInput, float yInput, float widthInput, float heightInput, float accelerationInput, float velocityInput, char colorInput );
    //projectileDraw- draws the projectile on the screen.
    void projectileDraw();
    //projectileUpdate- updates the location of the projectile based on given acceleration and velocity.
    void projectileUpdate();
    //projectileFloorCheck- checks to see wether the projectile has hit the bottom of the screen, resetting position if it has.
    int projectileFloorCheck();
    //position of the brick, along with its acceleration and velocity.
    float x,y,velocity,acceleration;

    private:
    //varaibles that attribute to charactersitics of the button -- names indicate what varibales represent.
    float width,height;
    char color;
};

//Main function -- only starts the game, nothing else.
int main() {
    mainMenu();
    return 0;
}

//Button constructor
Button::Button(float xInput, float yInput, float widthInput, float heightInput, char colorInput, char textInput[]){
    //sets input values from call to newly created object.
    x = xInput;
    y = yInput;
    width = widthInput;
    height = heightInput;
    color = colorInput;
    strcpy (text,textInput);
}

//makeButton Function-- creates the button on the screen
void Button::makeButton(){
    //switch case used to determine color from call. *Could not use string as color enumerators are not a string*
    switch(color){
        case 'g':
            LCD.SetFontColor(GREEN);
            break;
        case 'r':
            LCD.SetFontColor(RED);
            break;
        case 'b':
            LCD.SetFontColor(BLUE);
            break;
        case 't':
            LCD.SetFontColor(BLACK);
            break;
        case 'p':
            LCD.SetFontColor(PURPLE);
            break;
    }
        //Draws button outline to screen
        LCD.DrawRectangle(x,y,width,height);
        //draws text to screen within button.
        LCD.WriteAt(text,x+5,y+10);
}

//buttonPress- detects if button is pressed using inputs from call
int Button::buttonPress(float x, float xLower, float xUpper, float y, float yLower, float yUpper){
    //Checks to see if cursor is with x range
    if(x >= xLower && x <= xUpper){
            //checks to see if cursor is within y range
            if(y >= yLower && y <= yUpper){
                //if both are true, returns 1
                return 1;
            }
    }
    //if false, returns false
    return 0;
}

//Player constructor
Player::Player(float xInput, float yInput, float widthInput, float heightInput, char colorInput){
    //sets input values from call to newly created object.
    x = xInput;
    y = yInput;
    width = widthInput;
    height = heightInput;
    color = colorInput;
}
void Player::playerDraw(){
    //switch case used to determine color from call. *Could not use string as color enumerators are not a string*
    switch(color){
        case 'g':
            LCD.SetFontColor(GREEN);
            break;
        case 'r':
            LCD.SetFontColor(RED);
            break;
        case 'b':
            LCD.SetFontColor(BLUE);
            break;
        case 'p':
            LCD.SetFontColor(PURPLE);
            break;
    }
    //draws player model on screen.
    LCD.FillRectangle(x,y,width,height);
}

//playerMove- moves the player to cursor location
void Player::playerMove(float touchX){
    //if the cursor is on the screen, move the player model
    if(touchX >= x-100 && x <=x+125){
        //updates player postion to cursor location
        x = touchX-12.5;
    }
}

//playerHit- checks if player is hit by projectile.
int Player::playerHit(float xCheck, float yCheck){
    //Checks to see wither left pint of block hist player
    if(xCheck <= x+25 && xCheck >= x){
        //if projectile range is in y range
        if(yCheck + 25 >= y){
            return 0;
        }
    }
    //Checks to see wether right point of block hits player
    if(x <= xCheck+25 && x >= xCheck){
        //if projectile is in y range
        if(yCheck + 25 >= y){
            return 0;
        }
    }
//1 is return if the player did not get hit
return 1; 
}
//Projectile constructor
Projectile::Projectile(float xInput, float yInput, float widthInput, float heightInput, float accelerationInput, float velocityInput, char colorInput){
    //sets input values from call to newly created object.
    x = xInput;
    y = yInput;
    width = widthInput;
    height = heightInput;
    acceleration = accelerationInput;
    velocity = velocityInput;
    color = colorInput;
}

//projectileDraw- creates the projectile on screen
void Projectile::projectileDraw(){
    //switch case used to determine color from call. *Could not use string as color enumerators are not a string*
    switch(color){
        case 'g':
            LCD.SetFontColor(GREEN);
            break;
        case 'r':
            LCD.SetFontColor(RED);
            break;
        case 'b':
            LCD.SetFontColor(BLUE);
            break;
        case 'p':
            LCD.SetFontColor(PURPLE);
            break;
    }
    //draws the projectile
    LCD.FillRectangle(x,y,width,height);
}

//projectileFloorCheck- Checks to see wether or not the projectile has hit the bottom of the screen.
int Projectile::projectileFloorCheck(){
    //if the block reachs the bottom of the screen
    if(y>=215){
        //reset block to top at new random postion with velocity of 0
        y = 0;
        x = rand() % 295+1;
        velocity = 0;
        return 0;
    }
//returns 1 if projectile has not hit the ground
return 1;
}

//projectileUpdate- updates the position of the projectile according to the acceleration and velocity
void Projectile::projectileUpdate(){
    velocity += acceleration;
    y += velocity;
}
//Main Menu- contains the main menu of our game
void mainMenu() {
//Running 
int running = 1;
//cursor positions
float x,y;
    //Keeps menu open 
    while(running==1) {
        //Background color,clear and write title
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();
        LCD.SetFontColor(PURPLE);
        LCD.WriteAt("Super Block Fall Game :D",10,10);

        //Play Button
        Button Play(105,40,110,40,'g',"Play");
        Play.makeButton();

        //Control Button
        Button Control(105,90,110,40,'r',"Controls");
        Control.makeButton();

        //Credits
        Button Credits(105,140,110,40,'b',"Credits");
        Credits.makeButton();

        //Quit
        Button Quit(105,190,110,40,'p',"Quit");
        Quit.makeButton();

        //Detects where touch of stylus/cursor is
        while (!LCD.Touch(&x,&y)) {}
            LCD.Touch(&x,&y);

            //checks to see if play button is pressed
            if(Play.buttonPress(x,Play.x,Play.x+110,y,Play.y,Play.y+40)==1){
                running = 0;
                gameMenu();
            }
            //checks to see if control button is pressed
            if(Control.buttonPress(x,Control.x,Control.x+110,y,Control.y,Control.y+40)==1){
                running = 0;
                controlMenu();
            }
            //checks to see if credits button is pressed
            if(Credits.buttonPress(x,Credits.x,Credits.x+110,y,Credits.y,Credits.y+40)==1){
                running = 0;
                creditsMenu();
            }
            //checks to see if quit button is pressed
            if(Quit.buttonPress(x,Quit.x,Quit.x+110,y,Quit.y,Quit.y+40)==1){
                    running = 0;
            }
        //Updates screen
        LCD.Update();
    }
}
//controlMenu- includes instruction on how to play the game.
void controlMenu() {
//running
int running = 1;
//cursor positions
float x=0;
float y=0;
//while running is true
while(running==1) {
    //worte controls to screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    LCD.WriteAt("Controls:",5,0);
    LCD.WriteAt("To control your block,",5,20);
    LCD.WriteAt("drag the mouse left to",5,40);
    LCD.WriteAt("right.",5,60);
    LCD.WriteAt("Bricks will fall faster",5,80);
    LCD.WriteAt("as the game progresses.",5,100);
    LCD.WriteAt("A point for each block",5,120);
    LCD.WriteAt("that reaches the bottom is",5,140);
    LCD.WriteAt("counts as a point.",5,160);
    //Creates back button
    Button Back(5,195,110,40,'r',"Back");
    Back.makeButton();
    //searches for location of cursor along with if its clicked
    while (!LCD.Touch(&x,&y)) {}
    LCD.Touch(&x,&y);
    //back button
    if(Back.buttonPress(x,Back.x,Back.x+110,y,Back.y,Back.y+40)==1){
        running = 0;
        mainMenu();
    }
    //update screen
    LCD.Update();    
    }
}
//creditsMenu- contains the credits for the game
void creditsMenu() {
//running
int running = 1;
//cursor
float x=0;
float y=0;

while(running==1) {
    //writes credits of game
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    LCD.SetFontColor(BLUE);
    LCD.WriteAt("Credits:",5,0);
    LCD.WriteAt("Game Design, Code",5,20);
    LCD.WriteAt("Website and Documentation",5,40);
    LCD.WriteAt("By-",5,60);
    LCD.WriteAt("Grace Bittence",5,80);
    LCD.WriteAt("and",5,100);
    LCD.WriteAt("Ian Kwiatkowski",5,120);
    //back button
    Button Back(5,195,110,40,'b',"Back");
    Back.makeButton();
    //while cursor is on button and clicked
    while (!LCD.Touch(&x,&y)) {}
    LCD.Touch(&x,&y);
    //checks to see if back button pressed
    if(Back.buttonPress(x,Back.x,Back.x+110,y,Back.y,Back.y+40)==1){
        running = 0;
        mainMenu();
    }
    //updates screen
    LCD.Update();  
    }
}
//gameMenu- actual screen where game is played
void gameMenu() {
//Initial Variables
int running = 1;
int totalScore = 0;
//constructing projectiles to be used in all levels
Projectile p1((rand() % 295+1),0,25,25,.15,0,'b');
Projectile p2_1((rand() % 295+1),0,25,25,.25,0,'g');
Projectile p2_2((rand() % 295+1),0,25,25,.2,0,'g');
Projectile p3_1((rand() % 295+1),0,25,25,.275,0,'p');
Projectile p3_2((rand() % 295+1),0,25,25,.3,0,'p');
Projectile p3_3((rand() % 295+1),0,25,25,.315,0,'p');
//constructs player model
Player player(120,210,25,25,'r');
//location of cursor
float touchX = 0;
float touchY = 0;
//while running
while(running==1) {
        //creates background of game, along with total score.
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();
        LCD.WriteAt("Score:",0,1);
        LCD.WriteAt(totalScore,70,1);
        //level one-- while score <6
        if(totalScore < 6){
            //prints level
            LCD.WriteAt("Level:1",0,21);
            //draws projectile, then updates it
            p1.projectileDraw();
            p1.projectileUpdate();
            //checks to see if player was hit by block
            if(player.playerHit(p1.x,p1.y)==0){
                running=0;
                endMenu();
            }
            //checks to see if projectile hits floor
            else if(p1.projectileFloorCheck()==0){
            totalScore += 1;
            }
        }
        //level two-- two blocks while score >=6 and <20
        else if(totalScore>=6 && totalScore < 20){
            //prints level
            LCD.WriteAt("Level:2",0,21);
            //draws projectile, then updates it
            p2_1.projectileDraw();
            p2_2.projectileDraw();
            p2_1.projectileUpdate();
            p2_2.projectileUpdate();
            //checks to see if player was hit by block
            if(player.playerHit(p2_1.x,p2_1.y)==0 || player.playerHit(p2_2.x,p2_2.y)==0){
            running=0;
            endMenu();
            }
            //checks to see if projectile hits floor
            else if(p2_1.projectileFloorCheck()==0 || p2_2.projectileFloorCheck()==0){
            totalScore += 1;
            }
        }
        //level 30-- 3 blocks with increasing speed per 10 score
        else if(totalScore >= 20){
            //prints level
            LCD.WriteAt("Level:3",0,21);
            //draws projectile, then updates it
            p3_1.projectileDraw();
            p3_2.projectileDraw();
            p3_3.projectileDraw();
            p3_1.projectileUpdate();
            p3_2.projectileUpdate();
            p3_3.projectileUpdate();
            //checks to see if player was hit by block
            if(player.playerHit(p3_1.x,p3_1.y)==0 || player.playerHit(p3_2.x,p3_2.y)==0 || player.playerHit(p3_3.x,p3_3.y)==0){
                running=0;
                endMenu();
            }
            //checks to see if projectile hits floor
            else if(p3_1.projectileFloorCheck()==0 || p3_2.projectileFloorCheck()==0 || p3_3.projectileFloorCheck()==0){
                totalScore += 1;
            }
            //if the score is a factor of 10, inrease the acceleration of the blocks
            if(totalScore%10==0){
                p3_1.acceleration += .02;
                p3_2.acceleration += .02;
                p3_3.acceleration += .02;
            }
        }
        //draws player model at cursor location
        player.playerDraw();
        //gets location of cursor
        LCD.Touch(&touchX,&touchY);
        player.playerMove(touchX);   
        
        //Checks to see if player is along the right edge
        if(player.x >= 295){
            player.x = 295;
        }
        //checks to see if player is along the left edge
        else if(player.x <= 0){
            player.x = 0;
        }
        //updates screen
        LCD.Update();     
    }
}
//endMenu- menu that is presented after game is lost
void endMenu() {
//running
int running = 1;
//cursor positions
float x,y;
//while running is true
while(running==1) {
    //writes game over to screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    LCD.WriteAt("GAME OVER!",100,110);
    LCD.WriteAt("THANKS FOR PLAYING!",45,130);
    //creates play again and quit buttons
    Button playAgain(5,195,110,40,'p',"Replay");
    Button Quit(205,195,110,40,'g',"Quit");
    //draws play again and quit buttons on screen
    playAgain.makeButton();
    Quit.makeButton();
    //updates location of cursor and if clicked
    while (!LCD.Touch(&x,&y)) {}
    LCD.Touch(&x,&y);
    //if play again is pressed
    if(playAgain.buttonPress(x,playAgain.x,playAgain.x+110,y,playAgain.y,playAgain.y+40)==1){
        running = 0;
        mainMenu();
    }
    //if quit is pressed
    if(Quit.buttonPress(x,Quit.x,Quit.x+110,y,Quit.y,Quit.y+40)==1){
        running = 0;
    }
    //updates screen
    LCD.Update();
    }
}