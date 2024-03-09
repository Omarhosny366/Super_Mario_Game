#include <iostream>
# include<stdlib.h>
# include<time.h>
#include <Windows.h>
#include<conio.h>
#include<string>
#define KEY_8 56
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_x 120

using namespace std;

class Cell{
    private:
char Type;
int x  ;
int y ;
public:
Cell(int x , int y , char c){
    x=0 ;
    y=0;
    Type='-';


}
int getXloc(){
return x ;
}
int getYloc(){

return y ;
}
char getType(){
return Type;
}
void SetXloc(int n ){
x=n ;
}
void SetYloc(int n ){
y=n ;
}
void setType(char c ){
    Type=c;
}
};


class champion : public Cell{
    private:
    int health;
    //int x  ;
   // int y  ;
    int gemsscore;
    int gems;
    int RemaningAbilityMoves;
    public:
    champion(int h , int g ,  int x , int y , char c):Cell( x ,  y ,  c){
        health=h ;
        gemsscore=g;
        RemaningAbilityMoves=2;




        cout<<"Constructor champion() is called"<<endl;;
    }
     void print_champ_info(){
         cout<<"champion pos : "<<"x= "<<getXloc()<<"y= "<<getYloc()<<" health: "<<health<<" gemsscore: "<<gemsscore<<" RemaningAbilityMoves Counter: "<<RemaningAbilityMoves<<endl;
     }
     int getHealth(){
         return health;
     }
     int getX(){
         return getXloc() ;
     }
     int getY(){
         return getYloc() ;
     }
     int getgemScore(){
         return gemsscore;
     }
     int getRemaningAbilityMoves(){
     return RemaningAbilityMoves;
     }
     void setHealth(int n){
         health=n ;
     }
     void setX(int n){
        SetXloc(n);

     }
     void setY(int n){
         SetYloc(n);

     }
     void setRemaningAbilityMoves(int n){
     RemaningAbilityMoves=n;}

     void setgemScore(int n ){
         gemsscore=n;
     }



 virtual void useAbility(){
cout<<"ability x is called"<<endl;

}


};






class Mario : public champion{

public:
    Mario(int h ,int g,int x , int y , char c ):
        champion(h,g,x,y,c){

        }

        void useAbility(){

   setRemaningAbilityMoves(getRemaningAbilityMoves()-1);
         cout<<" Mario Ability is called "<<endl ;


        }





};

class Luigi : public champion{

public:
    Luigi(int h ,int g ,int x , int y , char c ):
        champion(h,g,x,y,c){
        }

         void useAbility(){

   setRemaningAbilityMoves(getRemaningAbilityMoves()-1);
         cout<<" Luigi Ability is called "<<endl ;





        }


};

class Obstacle: public Cell{
private:
int dmg ;

public:
    Obstacle( int x , int y , char c ) : Cell(x,y,c){

   dmg=rand()%5+1;
   c='o';

    }
    int getDmg(){
        srand(time(NULL));
        dmg=rand()%4+1;
    return dmg;
    }

    virtual void execute(champion* c ){

    cout<<"Obstacle execute method is called"<<endl;

    }


};
class Bomb: public Obstacle{
public:
Bomb(int x , int y , char c)  :    Obstacle(x,y,c){

    }
    void execute(champion* c ){
        if(c->getHealth()>0){
            c->setHealth(c->getHealth()-getDmg());

            cout<<"bomb excuted with dmg = "<<getDmg()<<endl ;
        }
    }

};

class Theif : public Obstacle{
public:
Theif(int x , int y , char c) : Obstacle(x,y,c){
}
void execute(champion* c ){
    c->setgemScore(c->getgemScore()-getDmg());
    cout<<"thief executed with dmg = :"<<getDmg()<<endl;
}
};

class Gem : public Cell{
    private :
int points ;

    public:
        Gem(int x , int y , char c) : Cell(x,y,c){
    srand(time(NULL));
   points=rand()%5+5;
   c='g';

        }
        virtual void execute(champion* c){

        cout<<"Gem execute method is called"<<endl;
        }

        int getPoints(){
             srand(time(NULL));
            points=rand()%10+5;
        return points ;
        }

};
class Potion : public Gem{

public:
    Potion(int x , int y , char c):Gem(x,y,c){
    }
    void execute(champion* c ){

if(c->getHealth()+getPoints()>100){
    c->setHealth(100);
}else{
c->setHealth(c->getHealth()+getPoints());
}

cout<<"Potion executed with points ="<<getPoints()<<endl;
}
};
class Coin : public Gem{
public:
    Coin(int x , int y , char c):Gem(x,y,c){


    }


    void execute(champion* c){
        c->setgemScore(c->getgemScore()+getPoints());

        cout<<"Coin executed with points ="<<getPoints()<<endl;


    }


};
class map {
private:

    public:

       int gems=(rand()%20)+40;
       int gems1 =gems;
        char mapbase[10][10];


    map(){





        srand(time(NULL));
 mapbase[10][10];
        cout<<"Constructor map() is called"<<endl;
       randomize_map();

    }
    void print_map(){
        for(int i =9 ; i>=0;i--){
            for(int j = 0 ; j<10;j++){
                cout<<mapbase[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"print_map() called"<<endl;
    }
   void randomize_map(){


for(int i = 0 ; i<10;i++){
    for(int j= 0 ; j<10;j++){
        mapbase[i][j]='-';
    }
}

 mapbase[0][0]='C';

srand(time(NULL));

int po = 40;
     int o = 20;
       while(po>0){
           int p1= rand()%10;
         int p2 =rand()%10;

           if(mapbase[p1][p2]=='-'){
               mapbase[p1][p2]='g';

               po--;

           }
       }
       while(o>0){
            int p1= rand()%10;
         int p2 =rand()%10;

          if(mapbase[p1][p2]=='-'){
              mapbase[p1][p2]='o';

               o--;
           }
       }
       cout<<"randomize_map() called"<<endl;
   }
};
class Actions{
    public:
    champion* c = new champion(100,0,0,0,'C');
   //Mario* c = new Mario(100,0,0,0,'C');
  Mario* M = new Mario(100,0,0,0,'C');
   Luigi* L= new Luigi(100,0,0,0,'C');
map m ;
int No=0;
bool Continue=false;
bool run=true;
char champ;
Potion *p;
 Coin *co;
 Bomb *b;
 Theif *f;
Actions(){
    p= new Potion(0,0,'g');
co=new Coin(0,0,'g');
b=new Bomb(0,0,'o');
f=new Theif(0,0,'o');



    while(true){

    cout<<"Choose Mario press m or for Luigi press l  "<<endl;
    cin>>champ;
    if(champ=='m'){

        break;
    }if(champ=='l'){

      break;
    }
    }

    while(run){
            m.print_map();
       c->print_champ_info();
    char input;
    cout<<"Enter  r to Randomize the map And Enter p to play the game "<<endl;
    cin>>input;
    if(input=='r'){
        m.randomize_map();
       system("cls");
       Actions A ;
    }
    if(input=='p'){
        Continue=true;
    }
   else{
    run = false;
   }
// char in = getch();
   while(Continue){
       // cout<<m.gems1<<endl;
cout<<"Press 8 to move upward or 5 to move downward or press 6 to move to right or press 4 to move left or X for ability "<<endl;
 char in = getch();



       switch(in){
       case KEY_x:
           if(champ=='m'){
                if(M->getRemaningAbilityMoves()<=0){


            system("cls");
    m.print_map();
    c->print_champ_info();
      cout<<"NO ABILITY LEFT "<<endl;
                }
          else if(M->getRemaningAbilityMoves()>0){
                M->useAbility();
                c->setRemaningAbilityMoves(c->getRemaningAbilityMoves()-1);
                cout<<"Choose the direction of the ability  "<<endl;
           char i = getch();
           switch(i){
               case KEY_8:
              if(c->getY()<8){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setY(c->getY()+2);
      m.mapbase[c->getY()][c->getX()]='C';
           }
            system("cls");
    m.print_map();
    c->print_champ_info();
        break;



        case KEY_5:
            if(c->getY()>1){
      m.mapbase[c->getY()][c->getX()]='-';
     c->setY(c->getY()-2);
    m.mapbase[c->getY()][c->getX()]='C';
            }
              system("cls");
    m.print_map();
    c->print_champ_info();
        break;

         case KEY_6:
            if(c->getX()<8){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setX(c->getX()+2);
        m.mapbase[c->getY()][c->getX()]='C';
          }
            system("cls");
    m.print_map();
    c->print_champ_info();
        break;
        case KEY_4:
             if(c->getX()>1){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setX(c->getX()-2);
    m.mapbase[c->getY()][c->getX()]='C';
            }
            system("cls");
    m.print_map();
    c->print_champ_info();
        break;

           }
           }
           break;


           }

           else{
                if(L->getRemaningAbilityMoves()<=0){


            system("cls");
    m.print_map();
    c->print_champ_info();
      cout<<"NO ABILITY LEFT "<<endl;
                }
               if(L->getRemaningAbilityMoves()>0){

                   L->useAbility();
                   c->setRemaningAbilityMoves(c->getRemaningAbilityMoves()-1);
               cout<<"Choose the direction of the ability for upwards press w or downward press s or right press d or left a  "<<endl;
           char i ;
           cin>>i;
            int pos ;
            int posx;
            int posy;
           switch(i){
           case 'w':
               posx=c->getX();
               posy=c->getY();
           pos= c->getY();
            while(pos<=9){
                if(m.mapbase[pos][c->getX()]=='o'){
                    m.mapbase[pos][c->getX()]='-';
                }
                pos++;
            }

             // m.mapbase[posy][posx]='C';
    system("cls");
    m.print_map();
    c->print_champ_info();
        break;

        case 'd':
             posx=c->getX();
               posy=c->getY();
             pos = c->getX();
            while(pos<=9){
                if(m.mapbase[c->getY()][pos]=='o'){
                    m.mapbase[c->getY()][pos]='-';
                }
                pos++;
            }
            //  m.mapbase[posy][posx]='C';
    system("cls");

    m.print_map();
    c->print_champ_info();
        break;

        case 's':
             posx=c->getX();
               posy=c->getY();
             pos = c->getY();
            while(pos>=0){
                if(m.mapbase[pos][c->getX()]=='o'){
                    m.mapbase[pos][c->getX()]='-';

                }
                pos--;
            }
        //    m.mapbase[posy][posx]='C';
    system("cls");
    m.print_map();
    c->print_champ_info();
        break;

          case 'a':
               posx=c->getX();
               posy=c->getY();
             pos = c->getX();
            while(pos>=0){
                if(m.mapbase[c->getY()][pos]=='o'){
                    m.mapbase[c->getY()][pos]='-';
                }
                pos--;
            }
            //  m.mapbase[posy][posx]='C';
    system("cls");
    m.print_map();
    c->print_champ_info();
        break;










           }




               }




break;
           }

    case KEY_8:
        if(c->getY()!=9){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setY(c->getY()+1);
            if(m.mapbase[c->getY()+1][c->getX()]=='g'){
                    m.mapbase[c->getY()][c->getX()]='C';
                    int e= rand()%1;
                    if(e==1){


                         system("cls");

    m.print_map();

     p->execute(c);
c->print_champ_info();
                    }else{


                         system("cls");

    m.print_map();

     co->execute(c);
     c->print_champ_info();
                    }


            }
             if(m.mapbase[c->getY()][c->getX()]=='o'){
                 m.mapbase[c->getY()][c->getX()]='C';

              if(No==0){
system("cls");
    m.print_map();

                b->execute(c);
                 c->print_champ_info();
                No++;
              }else{
       system("cls");
    m.print_map();
               f->execute(c);
                c->print_champ_info();
               No--;

              }


        }
         if(m.mapbase[c->getY()][c->getX()]=='-'){
            m.mapbase[c->getY()][c->getX()]='C';

            system("cls");
    m.print_map();
    c->print_champ_info();

        }



        }

        break;
        case KEY_5:
            if(c->getY()!=0){
      m.mapbase[c->getY()][c->getX()]='-';
     c->setY(c->getY()-1);
            if(m.mapbase[c->getY()][c->getX()]=='g'){

                    m.mapbase[c->getY()][c->getX()]='C';
                     int e= rand()%1;
                    if(e==1){
    system("cls");
    m.print_map();

                        p->execute(c); c->print_champ_info();
                    }else{
    system("cls");
    m.print_map();

                        co->execute(c); c->print_champ_info();
                    }
            }
             if(m.mapbase[c->getY()][c->getX()]=='o'){
                 m.mapbase[c->getY()][c->getX()]='C';
            if(No==0){
                    system("cls");
    m.print_map();

                b->execute(c); c->print_champ_info();
                No++;
              }else{
                  system("cls");
    m.print_map();

               f->execute(c); c->print_champ_info();
               No--;
              }


        }
         if(m.mapbase[c->getY()][c->getX()]=='-'){
            m.mapbase[c->getY()][c->getX()]='C';
            system("cls");
    m.print_map();
    c->print_champ_info();
        }



        }
            break;

        case KEY_6:
            if(c->getX()!=9){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setX(c->getX()+1);
            if(m.mapbase[c->getY()][c->getX()]=='g'){

                    m.mapbase[c->getY()][c->getX()]='C';
                     int e= rand()%1;
                    if(e==1){
  system("cls");
    m.print_map();

                        p->execute(c);c->print_champ_info();
                    }else{
  system("cls");
    m.print_map();

                        co->execute(c);c->print_champ_info();
                    }
            }
             if(m.mapbase[c->getY()][c->getX()]=='o'){
                 m.mapbase[c->getY()][c->getX()]='C';
           if(No==0){
 system("cls");
    m.print_map();

                b->execute(c); c->print_champ_info();
                No++;
              }else{
 system("cls");
    m.print_map();

               f->execute(c);c->print_champ_info();
               No--;
              }


        }
        if(m.mapbase[c->getY()][c->getX()]=='-'){
            m.mapbase[c->getY()][c->getX()]='C';
system("cls");
    m.print_map();
    c->print_champ_info();
        }




        }

        break;
        case KEY_4:
             if(c->getX()!=0){
      m.mapbase[c->getY()][c->getX()]='-';
      c->setX(c->getX()-1);
            if(m.mapbase[c->getY()][c->getX()]=='g'){

                    m.mapbase[c->getY()][c->getX()]='C';
                      int e= rand()%1;
                    if(e==1){
   system("cls");
    m.print_map();

                        p->execute(c);c->print_champ_info();
                    }else{
system("cls");
    m.print_map();

                        co->execute(c); c->print_champ_info();
                    }
            }
             if(m.mapbase[c->getY()][c->getX()]=='o'){
                 m.mapbase[c->getY()][c->getX()]='C';
                  if(No==0){
   system("cls");
    m.print_map();

                b->execute(c);  c->print_champ_info();
                No++;
              }else{
 system("cls");
    m.print_map();

               f->execute(c);c->print_champ_info();
               No--;
              }



        }
        if(m.mapbase[c->getY()][c->getX()]=='-'){
            m.mapbase[c->getY()][c->getX()]='C';
system("cls");
    m.print_map();
    c->print_champ_info();
        }




        }

        break;

        }





Continue=EndGame(*c);
if(Continue==false)
    run=false;
   }






    }

}





bool EndGame(champion c){
    if(c.getHealth()<=0){

        cout<<"You Lost"<<endl;
        return false;
    }
    if(c.getgemScore()>200){
        cout<<"You Win"<<endl;
        return false;
    }
    return true;



}



    };
int main()
{
    Actions A ;
getch();

    return 0;
}

