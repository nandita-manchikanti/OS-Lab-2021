#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
using namespace std;

/*
AT - Arrival Time of the process
BT - Burst time of the process
CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process
Formulas used:
TAT = CT - AT
WT = TAT - BT
*/

//structure to store the process data
struct PCB {
    int pid;
    int AT;
    int BT;
    int start_time;
    int CT;
    int TAT;
    int WT;
    bool isCompleted=0;
};

//function to compare PCBs based on their AT
bool compare1(PCB p1, PCB p2) 
{  
    if(p1.AT == p2.AT){
        return p1.pid < p2.pid;
    }
    else{
        return p1.AT < p2.AT;
    }
}


bool compare2(PCB p1, PCB p2) 
{  
    return p1.pid < p2.pid;
}

int main() {

    int n;
    int quantum;
    struct PCB p[100];
    float avg_turnaround_time;
    float avg_waiting_time;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    int burst_remaining[100];
    int index;

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter time quantum: ";
    cin>>quantum;

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].AT;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].BT;
        burst_remaining[i] = p[i].BT;
        p[i].pid = i+1;
        cout<<endl;
    }

//sort the PCBs based on their AT
    sort(p,p+n,compare1);

    queue<int> q;
    int currTime = 0;
    q.push(0);
    int completed = 0;

    while(completed != n) {
        index = q.front();
        q.pop();

        if(burst_remaining[index] == p[index].BT) {
            p[index].start_time = max(currTime,p[index].AT);
            currTime = p[index].start_time;
        }

        if(burst_remaining[index]-quantum > 0) {
            burst_remaining[index] = burst_remaining[index] - quantum;
            currTime =currTime + quantum;
        }

        if(burst_remaining[index] > 0) {
            q.push(index);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    p[i].isCompleted = 1;
                    break;
                }
            }
        }

        else {
            currTime = currTime + burst_remaining[index];
            burst_remaining[index] = 0;
            completed++;

            p[index].CT = currTime;
            p[index].TAT = p[index].CT - p[index].AT;
            p[index].WT = p[index].TAT - p[index].BT;

            total_turnaround_time =total_turnaround_time+ p[index].TAT;
            total_waiting_time =total_waiting_time+ p[index].WT;
        }


        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].AT <= currTime && p[i].isCompleted == 0) {
                q.push(i);
                p[i].isCompleted = 1;
            }
        }

    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    
    sort(p,p+n,compare2);

    cout<<endl;
    cout<<"Pid\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].CT<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
}

