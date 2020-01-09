
#include <stdio.h>
#include <windows.h>

const int readers_count = 5;
const int writers_count = 3;
const int iterations = 5;

HANDLE mutex;
HANDLE can_read;
HANDLE can_write;

HANDLE writers[writers_count];
HANDLE readers[readers_count];

volatile LONG active_readers = 0;
volatile LONG waiting_readers = 0;
volatile LONG waiting_writers = 0;
bool writing = false;


int value = 0;



int init_handles()
{
	mutex = CreateMutex(NULL, FALSE, NULL);
	if (mutex == NULL) 
    {
		perror("Can't create mutex");
		return 1;
	}

	can_read = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (can_read == NULL) 
    {
		perror("Can't create event can read");
		return 1;
	}

	can_write = CreateEvent(NULL, TRUE, TRUE, NULL);
	if (can_write == NULL) 
    {
		perror("Can't create event can write");
		return 1;
	}
	return 0;
}

void start_read()
{
    InterlockedIncrement(&waiting_readers);
	if (writing || WaitForSingleObject(can_write, 0) == WAIT_OBJECT_0) 
    {
		WaitForSingleObject(can_read, INFINITE);
	}
    InterlockedDecrement(&waiting_readers);
	InterlockedIncrement(&active_readers);
	SetEvent(can_read);
}

void stop_read()
{
	InterlockedDecrement(&active_readers);
	if (active_readers == 0) 
    {
		SetEvent(can_write);
	}
}

void start_write()
{
    InterlockedIncrement(&waiting_writers);
	if (writing || active_readers > 0) 
    {
		WaitForSingleObject(can_write, INFINITE);
	}
    WaitForSingleObject(mutex, INFINITE);
    InterlockedDecrement(&waiting_writers);
	writing = true;
    printf("Writer %ld wrote %ld\n", GetCurrentThreadId(), ++value);
	ResetEvent(can_write);
	ReleaseMutex(mutex);
}

void stop_write()
{
	writing = false;
	if (WaitForSingleObject(can_read, 0) == WAIT_OBJECT_0) 
    {
		SetEvent(can_read);
	}
	else 
    {
		SetEvent(can_write);
	}
} 

DWORD WINAPI reader(LPVOID)
{
    srand(GetCurrentThreadId());
	while (value < writers_count * iterations) 
    {
        Sleep(rand() % 5 * 100);
		start_read();
		printf("Reader %ld read %d\n", GetCurrentThreadId(), value);
		stop_read();
	}

	return 0;  
}

DWORD WINAPI writer(LPVOID)
{
    srand(GetCurrentThreadId());
	for (int i = 0; i < iterations; i++) 
    {
        Sleep(rand() % 5 * 100);
		start_write();
		stop_write();
	}

	return 0;
}


int create_threads()
{
	for (int i = 0; i < writers_count; i++) 
    {
		writers[i] = CreateThread(NULL, 0,  writer, NULL, 0, NULL); 
		if (writers[i] == NULL) 
        {
			perror("Can't create writer");
			return 1;
		}
	}

	for (int i = 0; i < readers_count; i++) 
    {
		readers[i] = CreateThread(NULL, 0, reader, NULL, 0, NULL);
		if (readers[i] == NULL) 
        {
			perror("Can't create reader");
			return 1;
		}
	}

	return 0;
}


int main()
{
	setbuf(stdout, NULL);
	int rc = 0;

	if ((rc = init_handles()) != 0) 
    {
		return rc;
	}

	if ((rc = create_threads()) != 0) 
    {
		return rc;
	}

	
	WaitForMultipleObjects(writers_count, writers, TRUE, INFINITE);
	WaitForMultipleObjects(readers_count, readers, TRUE, INFINITE);

	CloseHandle(mutex);
	CloseHandle(can_read);
	CloseHandle(can_write);

	system("pause");

	return rc;
}