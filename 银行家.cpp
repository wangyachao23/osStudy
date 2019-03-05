#include <iostream>
using namespace std;
int Available[100];
int Max[50][100];
int Allocation[50][100];
int Need[50][100];
int Request[50][100];
int Finish[50];
int p[50];
int m,n;

int Safe()
{
    int i,j,l=0;
    int Work[100];
    for (i=0;i<n;i++)
        Work[i]=Available[i];
    for (i=0;i<m;i++)
        Finish[i]=0;
    for (i=0;i<m;i++)
    {
        if (Finish[i]==1)//Finish[i]==1Ϊtrue
        continue;
        else
        {
            for (j=0;j<n;j++)
            {
                if (Need[i][j]>Work[j])
                    break;
            }
            if (j==n)
            {
                Finish[i]=1;
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];
                p[l++]=i;
                i=-1;
            }
            else continue;
        }
        if (l==m)
        {
            cout<<"OK, It's a SAFE state."<<endl;
            cout<<"The safe state is:"<<endl;
            for (i=0;i<l;i++)
            {
                cout<<p[i];
                if (i!=l-1)
                    cout<<"-->";
            }
            cout<<'\n';
            return 1;
        }
    }
}

int main()
{
    int i,j,mi;
    cout<<"input process number:";
    cin>>m;
    cout<<"input process kind:";
    cin>>n;
    cout<<"input MAX:"<<m<<"x"<<n;
    for (i=0;i<m;i++)
        for(j=0;j<n;j++)
            cin>>Max[i][j];
    cout<<"input Allocation:"<<m<<"x"<<n;
    for (i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>Allocation[i][j];
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if (Need[i][j]<0)
            {
                cout<<"input"<<i+1<<"process"<<j+1<<"error";
                j--;
                continue;
            }
        }
    }
    cout<<"please input Available:";
    for (i=0;i<n;i++)
    cin>>Available[i];
    Safe();
    while (1)
    {
        cout<<"input request resource process:";
        cin>>mi;
        cout<<"request resource number:";
        for (i=0;i<n;i++)
        cin>>Request[mi][i];
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
                cout<<"It is more need";
                return 0;
            }
            if (Request[mi][i]>Available[i])
            {
                cout<<"It is more resource!";
                return 0;
            }
        }
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];
            Allocation[mi][i]+=Request[mi][i];
            Need[mi][i]-=Request[mi][i];
        }
        if (Safe())
            cout<<"ok";
        else
        {
            cout<<"sorry";
            for (i=0;i<n;i++)
            {
                Available[i]+=Request[mi][i];
                Allocation[mi][i]-=Request[mi][i];
                Need[mi][i]+=Request[mi][i];
            }}}}/*
        }
        for (i=0;i<m;i++)
            Finish[i]=0;
        char Flag;
        cout<<"yes:Y/y,no:N/n";
        while (1)
        {
            cin>>Flag;
            if (Flag=='Y'||Flag=='y'||Flag=='N'||Flag=='n')
            break;
            else
            {
                cout<<"Please input:";
                continue;
            }
        }
        if (Flag=='Y'||Flag=='y')
        continue;
        else break;
    }*/


/*
5
3
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

3 3 2

1

1 0 2

0
0 2 0
4
3 3 0


*/
