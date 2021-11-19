//Program to implement SJF Algorithm
//CED19I056
//Nandita M

#include<bits/stdc++.h>
using namespace std;

//Structure for a process
struct PCB{
    int pid,AT,BT,CT,TAT,WT;
};

//Function to print a line
void pline(int x){
    int i;
    for(int i=0;i<x;i++){
        printf("-");
    }
    printf("\n");
}

//Comparator for sorting the vector p
bool comp(PCB a,PCB b){
    if(a.AT==b.AT){
        if(a.BT==b.BT){
            return a.pid<b.pid;
        }
        else{
            return a.BT<b.BT;
        }
    }
    return a.AT<b.AT;
}

//Comapartor of pushing into the priority_Queue Queue
struct compare
{
    bool operator()(PCB &a,PCB &b)
    {
        return a.BT > b.BT;
    }
};


int main(){
    int n;
    printf("Enter the number of processes :");
    cin>>n;

    int sum=0;
    int TotalTAT=0;
    int TotalWT=0;

    vector<PCB>p(n);

    for(int i=0;i<n;i++){
        printf("Enter the Arrival Time ,Burst Time for process %d :\n",i+1);
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].pid=i+1;
    }

    sort(p.begin(),p.end(),comp);
    vector<PCB>ans;

    priority_queue<PCB,vector<PCB>,compare> Queue;
    Queue.push({p[0]});

    int i=1;
    int current_time=Queue.top().AT;

    while(!Queue.empty()){
        int burst_time=Queue.top().BT;
        struct PCB top=Queue.top();
        Queue.pop();
        ans.push_back(top);
        current_time=current_time+burst_time;

        while(true){
            if(i<n && p[i].AT<=current_time){
                Queue.push({p[i]});
                i++;
            }
            else
                break;
        }
    }
        ans[0].CT=ans[0].AT+ans[0].BT;
        ans[0].TAT=ans[0].CT-ans[0].AT;
        ans[0].WT=ans[0].TAT-ans[0].BT;

    for(int i=1;i<ans.size();i++){
        ans[i].CT=ans[i-1].CT+ans[i].BT;
        ans[i].TAT=ans[i].CT-ans[i].AT;
        ans[i].WT=ans[i].TAT-ans[i].BT;
    }
    
    //Printing the table of AT,WT,BT,TAT,CT
    
    pline(44);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<ans.size();i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",ans[i].pid,ans[i].AT,ans[i].BT,ans[i].CT,ans[i].TAT,ans[i].WT);
        TotalTAT=TotalTAT+ans[i].TAT;
        TotalWT=TotalWT+ans[i].WT;
    }
        pline(44);
        float avgTAT=(float)TotalTAT/(float)n;
        float avgWT=(float)TotalWT/(float)n;
        printf("Average Turnaround Time is %.3f\n",avgTAT);
        printf("Average Waiting Time is %.3f\n",avgWT);
        return 0;
    }
    
