// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "ctype.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------
int numThreads;
int numShouts;
int numPeople; 
int numMessPerBox; 
int numMessSend; 
Lock *myLock = new Lock("testLock"); 
char arr[] = "IHaveSwag";
char arr2[] = "ITooHaveSwag";
char arr3[] = "MySwagIsStrong";
char arr4[] = "IAmTheSwag";
char arr5[] = "TheSwagIsMe";
bool postoffice[10000][10000]; 
int sender[10000][10000]; 
int totalMess = numMessSend;
int messCount[10000]; 
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void Task1(int which)//Begin code changes Jardain Kenner
{
	printf("Task %d has been chosen\n", which);
	char userIn[50]; 
	printf("Enter some input:");
	scanf("%[^\n]%*c", userIn); 
	int size = strlen(userIn); 
	bool isNum = false; 
	bool isChar =false; 
	bool isDec = false;
	bool isNeg = false;
	int decCount = 0;
	if(userIn[0] == '-')//Special Case 1: if '-'is the first input
	{
		if(size != 1){
		isNeg = true;}
		else{
		isChar = true;}
	}	
	if(isdigit(userIn[0] && size == 1))
	{isNum = true;}
	if(isdigit(userIn[0]) && userIn[0] != '0')//Special Case 3: if the only input is a single digit
	{
		isNum = true;
	} 
	if(ispunct(userIn[0]) && userIn[0] != '-')//if the only input is a punctuation mark 
	{
		isNeg = false;
		isNum = false;
		isDec = false;
		isChar = true;
	}
	if(userIn[0] == '-' && userIn[1] == '.')//Special Case 4: if the only input is '-' or '.'
	{isChar = true;}
	for(int i = 0; i < size; i++)//loop through the 
	{	
		if((isdigit(userIn[i]) && i > 0))//if it is a digit after the first one in the array
		{				
			if(!isChar && userIn[0] != '0')// if it is not a character and the first slot is not 0
			{
				isNum = true;
			}
		}
		if(isalpha(userIn[i]))
		{
			isNum = false;
			isNeg = false;
			isDec = false;
			isChar = true;
			break;
		}
		if(userIn[i] == ' '){isChar = true; break;}//if there is a space anywhere, it is a character or character string
		if((ispunct(userIn[i]) && i > 0) || (ispunct(userIn[i]) && size < 2))//check if it is a decimal
		{
			if(userIn[i] == '.')
			{
				decCount++; 
				if(decCount == 1 &&  !isChar)
				{
					if(userIn[0] != '.')
					{
						isDec = true;
					}
					else{
					isNum = false;
					isChar = true;} 
				}
				else{isChar = true;}
			}
			else{
			isNeg = false;
			isNum = false;
			isDec = false;
			isChar = true;
			}
		}
		if(isChar)
		{
			break;
		}
	}
	//Special Case: 0 is invalid if it is not of the following format (0.0, 0.1, 0.3, etc);  
	if((userIn[0] == '0' && size > 1) || (userIn[0] == '-' && userIn[1] == '0' && userIn[2]!= '.'))
	{
		if(userIn[0] == '0' && userIn[1] == '.' && !isChar)
		{
		isDec = true; 
		}else{
		printf("INVALID INPUT\n");
		isNeg = false;
		isNum = false;
		isDec = false;
		isChar = false;}
	}
	if(userIn[0] == '0' && size == 1)
	{isNum = true;}
	if(isChar)// redundant, but ensures that the proper output is displayed
	{	
		isNeg = false;
		isDec = false;
		isNum = false;
		if(size == 1){
		printf("\nThis is a character\n");}
		else{printf("\nThis is a character string\n");} 
	}	

	if(isDec)
	{
		isNum = false;
		if(userIn[size-1] == '.'){ //Special Case: if a decimal point is the last input
			isDec = false;
			isNeg =false; 
			printf("This is a character string\n");
		}
		else{
		printf("This is a decimal\n");
		}
	}

	if(isNum)
	{ 
		printf("This is an integer\n");
	}
	if(isNeg)
	{
		printf("This is negative\n");
	}
	printf("\n");

}
void Task2(int which)
{
	int count = 1;
	which++; 
	while(count <= numShouts)
	{
		int randomNum2 = (Random()) % 5 +2; 
		for(int i = 2; i < randomNum2; i++)
		{
			currentThread->Yield(); 
		}
		int randomNum = Random() % 5; 
		switch(randomNum)
		{
			case 0: 	
				printf("\n %s %d has shouted %s and has shouted %d time(s)\n", currentThread->getName(),which ,arr, count);
				count++;
				break;
			case 1:
				printf("\n %s %d has shouted %s and has shouted %d time(s)\n", currentThread->getName(),which,arr2, count);
				count++;
				break; 
			case 2:
				printf("\n %s %d has shouted %s and has shouted %d time(s)\n", currentThread->getName(),which,arr3, count);
				count++;
				break; 	
			case 3: 
				printf("\n %s %d has shouted %s and has shouted %d time(s)\n", currentThread->getName(),which,arr4, count);
				count++;
				break; 
			case 4:
				printf("\n %s %d has shouted %s and has shouted %d time(s)\n", currentThread->getName(),which,arr5, count);
				count++;
				break;
			default: 
				break; 
		}
	}	

}
int getMessageCount(int person)
{
	int  numMessages = 0; 
	for(int i = numMessSend; i > 0; i--)
	{
		if(postoffice[person][i-1] == true)
		{
			numMessages++; 
		}
	}
	return numMessages;
}

void
Read(int person, int senders, int message)
{	
	int randomNum = Random() % 7; 
	switch(randomNum)
	{
		case 0:
			printf("-------------ke>%s recieved -%s- from Person %d\n", currentThread->getName(), "IHAVESWAG", senders); 
			postoffice[person][message-1] = false; 
			break;
		case 1:
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "THESWAGISME", senders);
			postoffice[person][message-1] = false; 
			break;
		case 2: 
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "IAMTHESWAG", senders);
			postoffice[person][message-1] = false; 
			break;
		case 3:
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "GREATISMYSWAG", senders);
			postoffice[person][message-1] = false; 
			break;
		case 4: 
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "MYSWAGISIMPECABLE", senders);
			postoffice[person][message-1] = false; 
			break;
		case 5: 
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "MYSWAGISMAXIMUMER",senders);
		        postoffice[person][message-1] = false;
			break;
		case 6:
			printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "MYSWAGISMAXIMUM", senders); 
			postoffice[person][message-1] =false;
	                break;
		case 7: printf("------------>%s recieved -%s- from Person %d\n", currentThread->getName(), "AAAAAAAAHHHHHHH", senders);
			postoffice[person][message-1] = false;
			break;

	}
}


void 
Task3(int which)
{
	int messCounter = 0;
	while(numMessSend > 0)
	{
		messCount[which] = getMessageCount(which); 
		//step 1: Enter the post office
		printf("----->%s has entered the post office\n", currentThread->getName()); 
		//step 2: Read a message in my mailbox, step:4 if there is more, keep reading till there are no more
		if(messCount[which] > 0)
		{
		do
		{	
			Read(which, sender[which][messCount[which]-1], messCount[which]);
			 	
			//step 3: Yield  
			currentThread->Yield(); 
			
		}
		while(messCount[which] > 0);	
		}
		
			int randomNum = which; 
			while(randomNum == which)
			{
				randomNum = (Random() % numPeople); 
			}	
 			
		//step6: Prepare a message 
			if(postoffice[randomNum][numMessPerBox-1] != true)
			{
				for(int i = 0; i < numMessPerBox; i++)
				{
					if(postoffice[randomNum][i] != true)
					{
						sender[randomNum][i] = which;
						postoffice[randomNum][i] = true;
						printf("--->%s is preparing a message for Person %d\n", currentThread->getName(), randomNum);
						break; 
					}
				}
				numMessSend--; 
			}
			else
			{       //step 7: enter a busy waiting loop until mailbox is free
				int count = 1;
				printf("i have entered deadlock\n"); 
				while(postoffice[randomNum][numMessPerBox-1] == true)
				{
					printf("------------->%s is trying to give a message\n", currentThread->getName());

					if(count == 3)
					{
						printf("------------->prevented deadlock, message could not be sent\n"); 
						break;
					}
					count++; 
					currentThread->Yield(); 
				}

			}
			//step 8: leave office
			printf("--->%s is leaving the post office\n", currentThread->getName()); 
			//step 9: wait a few cycles to reenter post office 
			int randomCycle = (Random() % 3) + 2; 
			for(int i = 0; i < randomCycle; i++)
			{
				currentThread->Yield(); 
			}
		}
	}
void TestLock(int which){
myLock->Acquire();
printf("%s is doing something\n", currentThread->getName()); 
currentThread->Yield();
myLock->Release(); 
}
		
void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");

    bool isValid; 
    bool isValid2;
    char array[5];
    char array2[5];  
    Thread *t;
    Thread *t2; 
    
    if(whichone == 1)	
    { 
        for(int i = 0; i < 10; i++)
	{
		char *c = new char[10]; 
		sprintf(c, "Thread %i", i);
		t = new Thread(c);
		t->Fork(TestLock, i); 
	}
    }
    else if(whichone == 2)
    {
	printf("Enter the number of threads(between 1 and 10000): "); 
	scanf("%[^\n]%*c", array);
	while(!isValid)
	{
		if(atoi(array) > 10000 || atoi(array) < 1)
		{isValid = false;}
		else{isValid = true;}
		switch(isValid)
		{
			case true:
				printf("%d\n", atoi(array)); 
				numThreads = atoi(array); 
				break;
			default:
				printf("\nINVALID INPUT, TRY AGAIN\n\n");
				printf("Enter the number of threads (between 1 and 10000): "); 
				scanf("%[^\n]%*c", array);
		}
	}
	printf("Enter the number of shouts(between 1 and 10000): " );
	scanf("%[^\n]%*c", array2); 
	while(!isValid2)
	{
		if(atoi(array2) > 10000 || atoi(array2) < 1)
		{isValid2 = false;}
		else{isValid2 = true;}
		switch(isValid2)
		{
			case true:
				printf("%d\n", atoi(array2));
				numShouts = atoi(array2);
				break;
			default:
				printf("INVALID INPUT, TRY AGAIN\n\n");
				printf("Enter the number of shouts (between 1 and 10000): ");
				scanf("%[^\n]%*c", array2);
		}
	}
	for(int i = 0; i < numThreads; i++)
	{ 	
		t2 = new Thread("Thread");
		t2->Fork(Task2, i);
	} 

	

    }	
	else if(whichone == 5)
	{
		//Ensure valid input	
		printf("Enter the number of people: ");
		scanf("%[^\n]%*c", array); 
		bool isValid3; 
		while(!isValid2)
		{
			if(atoi(array) > 10000 || atoi(array) < 2)
			{isValid2 = false;}
			else{isValid2 = true;}
			switch(isValid2)
			{
			case true:
				printf("%d\n", atoi(array));
				numPeople = atoi(array);
				break;
			default:
				printf("INVALID INPUT, TRY AGAIN\n\n");
				printf("Enter the number of people (between 2 and 10000): ");
				scanf("%[^\n]%*c", array);
			}
		}
		isValid2=false; 
		printf("Enter the number of messages per mailbox: ");
		scanf("%[^\n]%*c", arr);
		while(!isValid2)
		{
			if(atoi(arr) > 10000 || atoi(arr) < 1)
			{isValid2 = false;}
			else{isValid2 = true;}
			switch(isValid2)
			{
			case true:
				printf("%d\n", atoi(arr));
				numMessPerBox = atoi(arr);
				break;
			default:
				printf("INVALID INPUT, TRY AGAIN\n\n");
				printf("Enter the number of messagesPerBox (between 1 and 10000): ");
				scanf("%[^\n]%*c", arr);
			}
		}
		printf("Enter the number of messages to be sent: "); 
		scanf("%[^\n]%*c", arr2);
		while(!isValid3)
		{
			if(atoi(arr2) > 10000 || atoi(arr2) < 1)
			{isValid3 = false;}
			else{isValid3 = true;}
			switch(isValid3)
			{
			case true:
				printf("%d\n", atoi(arr2));
				numMessSend = atoi(arr2);
				break;
			default:
				printf("INVALID INPUT, TRY AGAIN\n\n");
				printf("Enter the number of messages to be sent (between 1 and 10000): ");
				scanf("%[^\n]%*c", arr2);
			}
		}
		for(int i = 0; i<10000; i++)
		{
			for(int j = 0; j<10000; j++)
			{
				postoffice[i][j]= false; 
			}	
		}
		for(int i =0; i<numPeople; i++)
		{
			char * c = new char [10]; 
			
			sprintf(c, "Person %d", i); 
			t = new Thread(c);
			t->Fork(Task3, i);  
		}
	}
}


