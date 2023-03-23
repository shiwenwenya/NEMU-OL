#include "lib.h"
#include "types.h"
#define N 5

sem_t forks[N];

void philosopher(int i)
{
	while (1)
	{
		printf("Philosopher %d: think\n", i);
		sleep(128);
		if (i % 2 == 0)
		{
			sem_wait(&forks[i]);
			sleep(128);
			sem_wait(&forks[(i + 1) % N]);
			sleep(128);
		}
		else
		{
			sem_wait(&forks[(i + 1) % N]);
			sleep(128);
			sem_wait(&forks[i]);
			sleep(128);
		}
		printf("Philosopher %d: eat\n", i);
		sleep(128);
		sem_post(&forks[i]);
		sleep(128);
		sem_post(&forks[(i + 1) % N]);
		sleep(128);
	}
}

int uEntry(void)
{

	// 测试scanf
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	while (1)
	{
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}

	// 测试信号量
	int i = 4;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 0);
	if (ret == -1)
	{
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0)
	{
		while (i != 0)
		{
			i--;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1)
	{
		while (i != 0)
		{
			i--;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.

	//哲学家
	//int ret = 0;
	for (int i = 0; i < 5; i++)
	{
		if (sem_init(&forks[i], 1) == -1)
		{
			printf("Father Process: Semaphore Initializing Failed.\n");
			exit();
		}
	}
	for (int i = 0; i < 4; i++)
	{
		ret = fork();
		if (ret == 0)
		{
			philosopher(i);
			exit();
		}
		else if (ret == -1)
		{
			printf("Father Process: Fork Failed.\n");
			exit();
		}
	}
	philosopher(4);
	//生产者消费者问题

	//读者写者问题

	exit(0);
	return 0;
}
