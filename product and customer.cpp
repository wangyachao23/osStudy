
#include<Windows.h>
#include<iostream>
using namespace std;
const int n=4;

//����ȫ�ֱ���
int i=0,j=0;	//i��j�ֱ�ָ�򻺳���
int buffer[n];	//�����
int ItemP=0;	//������������Ĳ�Ʒ
int ItemC=0;	//����������ѵĲ�Ʒ

//�������
HANDLE mutex;	//������ź���
HANDLE empty;	//�ջ������ź���
HANDLE full;	//���������ź���
HANDLE pThread;	//producer�߳̾��
HANDLE cThread;	//consumer�߳̾��

//�������̺���
DWORD WINAPI producer(LPVOID IpParameter);
DWORD WINAPI consumer(LPVOID IpParameter);

int main()
{
	//�����ź���
	mutex = CreateSemaphore(NULL,1,1,NULL);
	empty = CreateSemaphore(NULL,1,4,NULL);
	full = CreateSemaphore(NULL,0,4,NULL);

	cout<<"�г�������ʼ����������"<<endl;

	//�����߳�
	pThread = CreateThread(NULL,0,producer,NULL,0,NULL);
	cThread = CreateThread(NULL,0,consumer,NULL,0,NULL);

	//�ȴ���Ӧ�߳̽���
	WaitForSingleObject(pThread,INFINITE);
	WaitForSingleObject(cThread,INFINITE);


	//�ر��߳̾��
	CloseHandle(pThread);
	CloseHandle(cThread);

	//�ر��ź������
	CloseHandle(mutex);
	CloseHandle(empty);
	CloseHandle(full);

	cout<<"�����г���Ӫ������������"<<endl;
	return 0;
}

	//producer�̺߳����Ķ���
	DWORD WINAPI producer(LPVOID IpParameter)
	{
		for(int k=0;k<5;k++)
		{
			cout<<"\nproducer����һ����Ʒ"<<endl;
			ItemP=ItemP+1;			//����һ����Ʒ
			WaitForSingleObject(empty,INFINITE);	//P����
			WaitForSingleObject(mutex,INFINITE);
			cout<<"\n��һ����Ʒ������һ���յĻ�����"<<endl;
			buffer[i]=ItemP;		//����Ʒ���뻺����
			i=(i+1)%n;
			ReleaseSemaphore(mutex,1,NULL);		//V����
			ReleaseSemaphore(full,1,NULL);
		}
		return 0;
	}

	DWORD WINAPI consumer(LPVOID IpParameter)
	{
		for(int k=0;k<5;k++)
		{
			WaitForSingleObject(full,INFINITE);	//P����
			WaitForSingleObject(mutex,INFINITE);
			ItemC=buffer[j];		//����������Ĳ�Ʒȡ�����������Ѳ�Ʒ��ͷ
			j=(j+1)%n;				//jָ����һ�����Ļ�����
			ReleaseSemaphore(mutex,1,NULL);		//V����
			ReleaseSemaphore(empty,1,NULL);
			cout<<"\n����������һ����Ʒ"<<endl;
			ItemC=ItemC-1;			//����һ����Ʒ

		}
		return 0;
	}


