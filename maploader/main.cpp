#include <iostream>
#include <stdlib.h>
#include <limits>
#include "Maploader.h"

using namespace std;

int main() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                                                                     " << endl;
    cout << " RRRRRRRRRRRRRRRRR     iiii                   kkkkkkkk               " << endl;
    cout << " R::::::::::::::::R   i::::i                  k::::::k               " << endl;
    cout << " R::::::RRRRRR:::::R   iiii                   k::::::k               " << endl;
    cout << " RR:::::R     R:::::R                         k::::::k               " << endl;
    cout << " R::::R     R:::::Riiiiiii     ssssssssss     k:::::k    kkkkkkk      " << endl;
    cout << " R::::R     R:::::Ri:::::i   ss::::::::::s    k:::::k   k:::::k       " << endl;
    cout << " R::::RRRRRR:::::R  i::::i ss:::::::::::::s   k:::::k  k:::::k        " << endl;
    cout << " R:::::::::::::RR   i::::i s::::::ssss:::::s  k:::::k k:::::k         " << endl;
    cout << " R::::RRRRRR:::::R  i::::i  s:::::s  ssssss   k::::::k:::::k          " << endl;
    cout << " R::::R     R:::::R i::::i    s::::::s        k:::::::::::k           " << endl;
    cout << " R::::R     R:::::R i::::i       s::::::s     k:::::::::::k           " << endl;
    cout << " R::::R     R:::::R i::::i   sssss   s:::::s  k::::::k:::::k          " << endl;
    cout << " RR:::::R     R::::Ri::::i  s:::::ssss::::s  k::::::k k:::::k       " << endl;
    cout << " R::::::R     R::::Ri::::i  s::::::::::::::s k::::::k  k:::::k      " << endl;
    cout << " R::::::R     R::::Ri::::i   s:::::::::::ss  k::::::k   k:::::k     " << endl;
    cout << " RRRRRRRR     RRRRRRRiiiiii    sssssssssss    kkkkkkkk    kkkkkkk    " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


    int option = 2;

    cout<< "Do you wish to load the map in the Map folder?"<<endl;
    cout<< "Press 1 for Yes"<<endl;
    cout<< "Press 2 for No and to exit"<< endl;
    cin >>option;

    while((cin.fail())||(option<1)||(option>2)){
        if (cin.fail()){
            cout << "Erroneous input! Only numbers are accepted!" <<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout<< "Please stick to the follow two valid inputs:"<<endl;
        cout<< "Press 1 for Yes"<<endl;
        cout<< "Press 2 for No and to exit"<< endl;
        cin >> option;
    };

    if(option=2) {
    cout<<" Thank you for playing! (Or testing the exit function of the program!";
        return 0;
    }
    else{
        //read the actual file
        Maploader loader;
        loader.isValid("World.map");
        loader.loadMap("World.map");
        loader.displayMap();
    }



return 0;
}