#include <stdio.h>
#include <windows.h>

#define N 6

typedef int semaphore;  /* �ź�����һ����������ͱ��� */

 semaphore mutex=1;     /* ������� */
 semaphore empty=N;     /* ��¼�������пյĲ��� */
 semaphore full=0;      /* ��¼�����������Ĳ���*/

 semaphore buf[N];      /* ��N�������Ļ�����buf[N]����ʵ��ѭ��������� */
 semaphore front=0, rear=0;

  void p(semaphore *x)  /* p���� */
 {
    *x=(*x)-1;
 }

 void v(semaphore *y)   /* v���� */
 {
    *y=(*y)+1;
 }

  void produce_item(int *item_ptr)
 {
    *item_ptr='f';      /* full */
 }

 void enter_item(int x)
 {
    buf[front]=x;
    printf("������ %c �������� buf[%d]\n", buf[front], front);
    front=(front+1)%N;
 }

void remove_item(int *yy)
{

    printf("�ӻ�����  buf[%d] ȡ�� %c", rear,buf[rear]);

    *yy=buf[rear];
    buf[rear]='e';      /* enpty */
    printf("  ��˻����� buf[%d] ��ɿ��ˣ���%c��ʾ\n", rear, buf[rear]);
    rear=(rear+1)%N;
}
void consume_item(int y)
{
    printf("�����ߴӻ�����ȡ���Ĳ�Ʒ %c\n", y);
}

void producer();
void consumer();

/* ������ */
void producer()
{
    int item;

    while(1){
        Sleep(1000);
        produce_item(&item);
        p(&empty);          /* �ݼ��ղ��� */
        p(&mutex);          /* �����ٽ��� */
        enter_item(item);   /* ��һ���µ���������뻺���� */
        v(&mutex);          /* �뿪�ٽ��� */
        v(&full); /* ���������� */
        if(full==N)         /* �����������Ļ������������߽��� */
            consumer();
    }
}

/* ������ */
void consumer()
{
    int get_item;

    while(1){
        Sleep(1000);
            p(&full);           /* �ݼ������� */
            p(&mutex);          /* �����ٽ��� */
            remove_item(&get_item); /* �ӻ�������ȡ��һ�������� */
            v(&mutex);          /* �뿪�ٽ��� */
            v(&empty);          /* �����ղ��� */
            consume_item(get_item); /* ����������в��������ѣ�*/
            if(empty==N)        /* ��������ȫ�յĻ����������߽��� */
                producer();
    }
 }

 /* ���������ߣ������߽���ʵ�ֽ��̼�ͬ�� */
 int main()
{
    producer();
    consumer();
    return 0;
}

