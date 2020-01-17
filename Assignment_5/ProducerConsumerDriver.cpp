/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer producer;
	int selection;
	int enqueueCount = 0;
	// For case 1
	int numTimesProduce;
	string item;
	// For case 2
	int numTimesConsumed;
	while(true){
		menu();
		cin >> selection;
		switch(selection){
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				cin >> numTimesProduce;
				for(int i=1; i<=numTimesProduce;i++){
					cout << "Item" << i << ":" << endl;
					cin >> item;
					producer.enqueue(item);
					enqueueCount ++;
				}
				break;
			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				cin >> numTimesConsumed;
				if(numTimesConsumed > producer.queueSize()){
					for(int i=0; i<enqueueCount; i++){
						cout << "Consumed: " << producer.getQueue()[i] << endl;
						producer.dequeue();
					}
					cout << "No more items to consume from queue" << endl;
					break;
				}
				for(int i=0; i<numTimesConsumed; i++){
					cout << "Consumed: " << producer.getQueue()[i] << endl;
					producer.dequeue();
				}
				break;
			case 3:
				cout << "Number of items in the queue:" << producer.queueSize() << endl;
				return 0;
		}
	}
}
