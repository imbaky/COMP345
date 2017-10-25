#include <iostream>

using namespace std;

// function declaration
void start_game();

int main()
{

    cout<<"Lets play !\n"<<endl;

    cout << "██████╗ ██╗███████╗██╗  ██╗\n"<<
            "██╔══██╗██║██╔════╝██║ ██╔╝\n"<<
            "██████╔╝██║███████╗█████╔╝ \n"<<
            "██╔══██╗██║╚════██║██╔═██╗ \n"<<
            "██║  ██║██║███████║██║  ██╗\n"<<
            "╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝\n\n" << endl;
    start_game();


}

void start_game(){
    bool valid_input=false;
    char input;
    while(!valid_input){
        cout<<"Would you like to start the game? (y/n)"<<endl;
        cin>>input;
        if(input=='y'){
            valid_input=true;
        }else if(input!='n')
                cerr<<"invalid input !!"<<endl;
    }
}