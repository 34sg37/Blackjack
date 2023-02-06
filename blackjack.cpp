#include <iostream>
#include <string>
#include <time.h>
using std::cout;
using std::cin;
using std::string;
using std::endl;

class Deck{
    public:
        class Card{
            public:
                Card(){}
                Card(int val,int sign,int no) : value(val), no(no){

                    switch(sign){
                        case 0:
                            this->sign = "Diamonds";
                            break;
                        case 1:
                            this->sign = "Hearts";
                            break;
                        case 2:
                            this->sign = "Spades";
                            break;
                        case 3:
                            this->sign = "Clubs";
                            break;
                    }
                }
                void print()const{
                    if(value==1) cout<<"Ace"<<" of "<< sign<<endl;
                    else if(value==11) cout<<"Joker"<<" of "<< sign<<endl;
                    else if(value==12) cout<<"Queen"<<" of "<< sign<<endl;
                    else if(value==13) cout<<"King"<<" of "<< sign<<endl;
                    else cout<<value<<" of "<< sign<<endl;
                }
                int getValue()const {return value;}
            protected:
                int value,no;
                string sign;
        };
        
        Deck(){
            int i=0;
            for(int j=0; j<4; j++){
                for(int k=0; k<13; k++){
                    cards[i]= Card(k+1,j,i+1);
                    i++;
                }
            }
            shuffleDeck();
            printDeck();
        }

        void shuffleDeck(){
            Card temp;
            for(int i=0; i<52;i++){
                int num = rand()%52;
                temp=cards[i];
                cards[i]=cards[num];
                cards[num]=temp;
            }
        }

        void printDeck()const{ for(int i=0; i<52;i++) cards[i].print();}

    protected:
        static Card cards[52];
};
Deck::Card Deck::cards[52];

class Game : public Deck {
    public:
        class Players{
            public:
                Players(){
                    card = new Deck::Card[2];
                    card[0]= cards[num];
                    card[1]= cards[num+1];
                    num=num+2;
                }
                void printCards(){
                    for (int i=0; i<cardAmount; i++){
                        card[i].print();
                    }
                }
            private:
                Deck::Card* card;
                int cardAmount=2;
        };
        Game(int num) : numberOfPlayers(num){
            players = new Players[num];
        }
        ~Game(){
            delete[] players;
        }
        void play(){
            for(int i=0; i<numberOfPlayers; i++){
                cout<<endl<<"Player "<<i+1<<endl;
                players[i].printCards();
            }
        }
    private:
        Players* players;
        static int num;
        int numberOfPlayers;
};
int Game::num=0;

int main(){
    int num;
    srand(time(NULL));
    cout<<"How many players?"<<endl;
    cin>>num;
    Game game(num);
    game.play();
    return 0;
}