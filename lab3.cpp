#include <windows.h>
#include <iostream>
#include "lab3.h"

#define NUMBER_OF_THREADS 11

using namespace std;

unsigned int lab3_thread_graph_id() 
{
    return 11;
}

const char* lab3_unsynchronized_threads()
{
    return "bcde";
}

const char* lab3_sequential_threads()
{
    return "deg";
}

HANDLE tid[NUMBER_OF_THREADS], semD, semE, semG, mut;

DWORD WINAPI ThreadA(LPVOID);
DWORD WINAPI ThreadB(LPVOID);
DWORD WINAPI ThreadC(LPVOID);
DWORD WINAPI ThreadD(LPVOID);
DWORD WINAPI ThreadE(LPVOID);
DWORD WINAPI ThreadF(LPVOID);
DWORD WINAPI ThreadG(LPVOID);
DWORD WINAPI ThreadH(LPVOID);
DWORD WINAPI ThreadI(LPVOID);
DWORD WINAPI ThreadK(LPVOID);
DWORD WINAPI ThreadM(LPVOID);

DWORD ThreadID;



DWORD WINAPI ThreadA(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'a' << flush;
		computation();
		ReleaseMutex(mut);
	}
	return 0;
};

DWORD WINAPI ThreadD(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
	}
	

	//ждём A
	WaitForSingleObject(Threads[0], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
	}

	//запускаем E
	tid[2] = CreateThread(NULL, 0, ThreadE, NULL, 0, &ThreadID);
	//запускаем B
	tid[3] = CreateThread(NULL, 0, ThreadB, NULL, 0, &ThreadID);
	//запускаем C
	tid[4] = CreateThread(NULL, 0, ThreadC, NULL, 0, &ThreadID);

	//ждём B
	WaitForSingleObject(tid[3], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
	}
	
	//запускаем F
	tid[5] = CreateThread(NULL, 0, ThreadF, NULL, 0, &ThreadID);
	//ждём F
	WaitForSingleObject(tid[5], INFINITE);
	//ждём C
	WaitForSingleObject(tid[4], INFINITE);

	tid[6] = CreateThread(NULL, 0, ThreadG, NULL, 0, &ThreadID);

	for (int i = 0; i < 3; i++)
	{
		//semD down
		WaitForSingleObject(semD, INFINITE);
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
		//semE up
		ReleaseSemaphore(semE, 1, NULL);
	}

	//ждём E
	WaitForSingleObject(tid[2], INFINITE);
	//ждём G
	WaitForSingleObject(tid[6], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
	}

	//запускаем K
	tid[7] = CreateThread(NULL, 0, ThreadK, NULL, 0, &ThreadID);
	//запускаем I
	tid[8] = CreateThread(NULL, 0, ThreadI, NULL, 0, &ThreadID);
	//запускаем H
	tid[9] = CreateThread(NULL, 0, ThreadH, NULL, 0, &ThreadID);
	
	return 0;
};

DWORD WINAPI ThreadE(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'e' << flush;
		computation();
		ReleaseMutex(mut);
	}
	
	//ждём B
	WaitForSingleObject(tid[3], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'e' << flush;
		computation();
		ReleaseMutex(mut);
	}
	
	//ждём F
	WaitForSingleObject(tid[5], INFINITE);
	//ждём C
	WaitForSingleObject(tid[4], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		//semE down
		WaitForSingleObject(semE, INFINITE);
		WaitForSingleObject(mut, INFINITE);
		cout << 'd' << flush;
		computation();
		ReleaseMutex(mut);
		//semG up
		ReleaseSemaphore(semG, 1, NULL);
	}


	return 0;
};

DWORD WINAPI ThreadB(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'b' << flush;
		computation();
		ReleaseMutex(mut);
	}
	return 0;
};

DWORD WINAPI ThreadC(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'c' << flush;
		computation();
		ReleaseMutex(mut);
	}
	

	//ждём B
	WaitForSingleObject(tid[3], INFINITE);
	
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'c' << flush;
		computation();
		ReleaseMutex(mut);
	}
	
	return 0;
};

DWORD WINAPI ThreadF(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'f' << flush;
		computation();
		ReleaseMutex(mut);
	}
	return 0;
};

DWORD WINAPI ThreadG(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		//semG down
		WaitForSingleObject(semG, INFINITE);
		WaitForSingleObject(mut, INFINITE);
		cout << 'g' << flush;
		computation();
		ReleaseMutex(mut);
		//semD up
		ReleaseSemaphore(semD, 1, NULL);
	}
	return 0;
};

DWORD WINAPI ThreadH(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'h' << flush;
		computation();
		ReleaseMutex(mut);
	}
	return 0;
};

DWORD WINAPI ThreadI(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'i' << flush;
		computation();
		ReleaseMutex(mut);
	}
	return 0;
};

DWORD WINAPI ThreadK(LPVOID name)
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'k' << flush;
		computation();
		ReleaseMutex(mut);
	}
	
	
	//ждём I
	WaitForSingleObject(tid[8], INFINITE);
	//ждём H
	WaitForSingleObject(tid[9], INFINITE);
	//ждём D
	WaitForSingleObject(tid[1], INFINITE);

	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(mut, INFINITE);
		cout << 'k' << flush;
		computation();
		ReleaseMutex(mut);
	}

	//запускаем M
	tid[10] = CreateThread(NULL, 0, ThreadM, NULL, 0, &ThreadID);
	
	return 0;
};







int lab3_init()
{
    	mut = CreateMutex(NULL, 0, NULL);

	if (mut == NULL) 
	{
		cout << "CreateMutex error: " << GetLastError();
		return 1;
	}

    semD = CreateSemaphore(NULL, 1, 1, NULL);

    if (semD == NULL) 
	{
		cout << "CreateSemaphore error: " << GetLastError();
		return 1;
	}

    semE = CreateSemaphore(NULL, 0, 1, NULL);

    if (semD == NULL) 
	{
		cout << "CreateSemaphore error: " << GetLastError();
		return 1;
	}

    semG = CreateSemaphore(NULL, 0, 1, NULL);

    if (semD == NULL) 
	{
		cout << "CreateSemaphore error: " << GetLastError();
		return 1;
	}
    

	tid[0] = CreateThread(NULL, 0, ThreadA, NULL, 0, &ThreadID);
    	tid[1] = CreateThread(NULL, 0, ThreadD, NULL, 0, &ThreadID);
	//ждём A
	WaitForSingleObject(tid[0], INFINITE);
	//ждём D
	WaitForSingleObject(tid[1], INFINITE);
	//ждём K
	WaitForSingleObject(tid[7], INFINITE);
	//ждём M
	WaitForSingleObject(tid[10], INFINITE);

	for (int i = 0; i < NUMBER_OF_THREADS; i++) 
	{
       		CloseHandle(tid[i]);
	}
	
	CloseHandle(semD);
	CloseHandle(semE);
	CloseHandle(semG);
	CloseHandle(mut);

    return 0;
}
