#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

const int width = 300, height = 500;    //size of screen
const int cubeSize = 20;                //size of snake part
struct snake { int x,y;}  s[285];        //snake part position
int snakeLen = 4;                       //lenght of the snake
struct apple { int x,y;}  f;             //apple position
float timer=0, delay=0.2;                 //tick
int stopper=0;                          //Trigger to stop the game (Dead)
int dir=2;                               //direction of snake (i.e right,left,up,down)
int score=0;                            //score

void Tick(){
    for (int i=snakeLen; i>0; --i)
        {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

    /// Eating food ///
    if ((s[0].x==f.x) && (s[0].y==f.y))
     {snakeLen++; f.x=rand()%15; f.y=rand()%19; score++;}

     /// Hitting the edge ///
    if (s[0].x>14) stopper = 1;  if (s[0].x<0) stopper = 1;
    if (s[0].y>18) stopper = 1;  if (s[0].y<0) stopper = 1;

    /// Hitting the body ///
    for (int i=1;i<snakeLen;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  stopper = 1;


}

int main()
{

    RenderWindow window(VideoMode(width, height), "Snake Game");

    //Playing Area
    Texture t1,t2,t3,t4;
    t1.loadFromFile("asset/playingfield.png");
    t2.loadFromFile("asset/head.png");
    t3.loadFromFile("asset/body.png");
    t4.loadFromFile("asset/apple.png");

    Sprite playingfield;
    playingfield.setTexture(t1);
    playingfield.setPosition(0,0);

    Sprite head, body, apple;
    head.setTexture(t2);
    body.setTexture(t3);
    apple.setTexture(t4);

    Font font;
    font.loadFromFile("font/arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Black);
    text.setPosition(90, 420);

    //Initial Position
    s[0].x = 4;
    s[0].y = 4;
    s[1].x = 3;
    s[1].y = 4;
    s[2].x = 2;
    s[2].y = 4;
    s[3].x = 1;
    s[3].y = 4;

    Clock clock;
    while (window.isOpen())
    {
        //Calculate the tick
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        /// Change direction base on input
        if (Keyboard::isKeyPressed(Keyboard::Left)&& dir!=2) dir=1;
        if (Keyboard::isKeyPressed(Keyboard::Right)&& dir!=1) dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)&& dir!=0) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)&& dir!=3) dir=0;

        //Tick
        if(timer>delay && stopper == 0){
            text.setString("Score: "+to_string(score));
            timer=0;
            Tick();
        }
       
        //Render
        window.clear(Color(179, 107, 0)); //color brownish
        window.draw(playingfield);          //Render the playing field
        window.draw(text);

        head.setPosition(s[0].x*cubeSize, s[0].y*cubeSize); //Head Position
        window.draw(head);   /// Render the Head

        for (int i=1;i<snakeLen;i++){
        body.setPosition(s[i].x*cubeSize, s[i].y*cubeSize);
        window.draw(body);   /// Render the Body
        }

        apple.setPosition(f.x*cubeSize, f.y*cubeSize);  
        window.draw(apple); //Render Apple

        window.display();
    }

    return 0;
}