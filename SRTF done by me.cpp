#include<iostream>
#include<algorithm>
using namespace std;

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,starttime;
}ps[10];


int main()
{

    int n;
    float btremaining[50];
    bool iscompleted[50]={false},isfirstprocess=true;
    int currenttime = 0;
    int completed = 0;;
    float sumoftat=0,sumofwt=0,sumofrt=0,totalidletime=0,lengthcycle,prev=0;
    float cpuutilization;
    int maxcompletiontime,minarrivaltime;
    cout<<"Enter total number of processes: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process" <<i<< "Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid=i;
    }

    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process" <<i<< "Burst Time: ";
        cin >> ps[i].bt;
        btremaining[i]= ps[i].bt;
    }


    while(completed!=n)
    {
        int minindex = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= currenttime && iscompleted[i] == false) {
                if(btremaining[i] < minimum) {
                    minimum = btremaining[i];;
                    minindex = i;
                }
                if(btremaining[i]== minimum) {
                    if(ps[i].at < ps[minindex].at) {
                        minimum= btremaining[i];;
                        minindex = i;
                    }
                }
            }
        }


        if(minindex==-1)
        {
            currenttime++;
        }
        else
        {
            if(btremaining[minindex] == ps[minindex].bt)
            {
                        ps[minindex].starttime = currenttime;
                        totalidletime += (isfirstprocess==true) ? 0 : (ps[minindex].starttime -  prev);
                        isfirstprocess=false;
            }
            btremaining[minindex] -= 1;
            currenttime++;
            prev=currenttime;
            if(btremaining[minindex] == 0)
            {
                ps[minindex].ct = currenttime;
                ps[minindex].tat = ps[minindex].ct - ps[minindex].at;
                ps[minindex].wt= ps[minindex].tat - ps[minindex].bt;
                ps[minindex].rt = ps[minindex].starttime - ps[minindex].at;


                sumoftat +=ps[minindex].tat;
                sumofwt += ps[minindex].wt;
                sumofrt += ps[minindex].rt;
                completed++;
                iscompleted[minindex]=true;


            }
        }
    }
    maxcompletiontime = INT_MIN;
    minarrivaltime = INT_MAX;
    for(int i=0;i<n;i++)
    {
        maxcompletiontime = max(maxcompletiontime,ps[i].ct);
        minarrivaltime = min(minarrivaltime,ps[i].at);
    }
    lengthcycle = maxcompletiontime - minarrivaltime;
    cout<<"\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i=0;i<n;i++)
     cout<<i<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
    cout<<endl;
    cout<<"\nAverage Turn Around time= "<< sumoftat/n;
    cout<<"\nAverage Waiting Time= "<<sumofwt/n;
    cout<<"\nAverage Response Time= "<<sumofrt/n;

    return 0;
}
