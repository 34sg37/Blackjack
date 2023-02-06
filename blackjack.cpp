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
                    if (val==1) ace=1;
                }
                void print()const{
                    if(value==1) cout<<"Ace"<<" of "<< sign<<endl;
                    else if(value==11) cout<<"Joker"<<" of "<< sign<<endl;
                    else if(value==12) cout<<"Queen"<<" of "<< sign<<endl;
                    else if(value==13) cout<<"King"<<" of "<< sign<<endl;
                    else cout<<value<<" of "<< sign<<endl;
                }
                int getValue()const {return value;}
                bool isAce()const{return ace;}
            protected:
                int value,no;
                bool ace=0;
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
                int evaluate() {
                    int sum=0;
                    for(int i=0; i<cardAmount; i++){
                        if(card[i].getValue()>10) sum+=10;
                        else sum+=card[i].getValue();
                    }
                    return sum;
                }
                void hit(){
                    Deck::Card* temp = new Deck::Card[cardAmount+1];
                    for(int i=0;i<cardAmount;i++){
                        temp[i]=card[i];
                    }
                    temp[cardAmount]=cards[num];
                    num++;
                    cardAmount++;
                    card=temp;
                }
                void printCards()const {
                    for (int i=0; i<cardAmount; i++){
                        card[i].print();
                    }
                }
                int getCardAmount()const{
                    return cardAmount;
                }
                Card* getCards()const{
                    return card;
                }
                void setValue(int val){
                    value= val;
                }
                int getValue()const{
                    return value;
                }
            private:
                Deck::Card* card;
                int cardAmount=2;
                int value;
        };
        Game(int num) : numberOfPlayers(num){
            players = new Players[num];
        }
        ~Game(){
            delete[] players;
        }
        void play(){
            for(int i=0; i<numberOfPlayers; i++){
                int _value=players[i].evaluate();
                bool ace=0;
                cout<<endl<<"Player "<<i+1<<"\t Value: "<<_value<<endl;
                players[i].printCards();
                if(_value<=11){
                    for(int j=0; j<players[i].getCardAmount();j++){
                        if(players[i].getCards()->isAce()){
                            _value+=10;
                            ace=1;
                            break;
                        }
                    }
                    while(_value<17){
                        players[i].hit();
                        _value=players[i].evaluate();
                        if(ace==1) _value+=10;
                        if(_value>21 && ace==1){
                            _value-=10;
                            ace=0;
                        }
                    }
                }
                else if(_value>11 && _value<17){
                    while(_value<17){
                        players[i].hit();
                        _value=players[i].evaluate();
                    }
                }
                if(_value>21 && ace==1){
                    _value-=10;
                    ace=0;
                    while(_value<17){
                        players[i].hit();
                        _value=players[i].evaluate();
                    }
                }
                players[i].setValue(_value);
            }
            cout<<endl<<"---------------------------------------------"<<endl;
            for(int i=0; i<numberOfPlayers; i++){
                cout<<endl<<"Player "<<i+1<<"\t Value: "<<players[i].getValue()<<endl;
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