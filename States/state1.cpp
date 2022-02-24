#include <iostream.h> 

enum State {InWork, InPub, AtHome};

enum Event {GoWork,GoPub,GoHome,AnotherBeer};

void signout();
void lockDoor();
void hic();
void minesAPint();
void Transition(Event e);

using namespace std;

int main (void)
{
    int x;

	//models transitions:

  	   cout << "\nEnter a number between 0 and 4:\n";

  	   cout<< "0 = GoWork event \n 1: = GoPub event\n ";

	   cout <<  "2: = GoHome\n 3: = Anotherbeer\n 4:  exit program\n";
 	
    while (x!=4)
	{ 
      cin >> x;
	  Transition ((Event)x);
	}
}



void Transition(Event e)
//deals with state transitions and actions
{
	State s = AtHome;

	switch(s)
	{

	case AtHome:

		switch(e)

		{

		case GoWork:

			s = InWork;

			lockDoor();

			break;

		}

		break;

	case InWork:

		switch(e)

		{

		case GoPub:

			s = InPub;

			signout();

			break;

		case GoHome:

			s = AtHome;

			signout();

			break;

		}

		break;

	case InPub:

		switch(e)

		{

			case GoHome:
				s = AtHome;

				hic();
				break;

			case  AnotherBeer:
				minesAPint();

				break;
		}

		break;
	}

}



void minesAPint()
{ cout<<"Mines a pint!!\n"; }

void signout()
{ cout<<"Good night worker W101\n"; }

void hic()
{ cout<<"I'm off home! Hic!!\n"; }

void lockDoor()
{ cout<<"Click - doors locked - off to work!!\n"; }

