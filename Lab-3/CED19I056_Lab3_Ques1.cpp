/*
//Program to implement Priority Scheduling (Premptive)
//CED19I056
//Nandita M
*/
//Priority Scheduling (Primitive)

#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;

struct PCB {
    int pid;
    int AT;
    int BT;
    int priority;
    int CT;
    int TAT;
    int WT;
    bool isCompleted;
};

int main() {

    int n;
    struct PCB p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];
    

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].AT;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].BT;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].BT;//initialize burst remaining
        cout<<endl;
    }

    int currTime = 0;
    int completed = 0;

    while(completed != n) {
        int index = -1;
        int maxpriority = -1;

        for(int i = 0; i < n; i++){
            
            if(p[i].AT <= currTime && p[i].isCompleted == 0) {
                if(p[i].priority > maxpriority) { 
                    maxpriority = p[i].priority;
                    index = i;
                }
                if(p[i].priority == maxpriority) {
                    if(p[i].AT < p[index].AT) {
                        maxpriority = p[i].priority;
                        index = i;
                    }
                }
            }
        }

        if(index != -1) {//if index is not -1, then process is ready to be executed
            burst_remaining[index] = burst_remaining[index] - 1;
            currTime++;
            
            if(burst_remaining[index] == 0) {
                p[index].CT = currTime;
                p[index].TAT = p[index].CT - p[index].AT;
                p[index].WT = p[index].TAT - p[index].BT;

                total_turnaround_time = total_turnaround_time+ p[index].TAT;
                total_waiting_time = total_waiting_time + p[index].WT;
                p[index].isCompleted = 1;
                completed++;
            }
        }
        else {//if no process is ready
             currTime++;
        }  
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    
    for(int i = 0; i < n; i++) {//Find min arrival time and max completion time
        min_arrival_time = min(min_arrival_time,p[i].AT);
        max_completion_time = max(max_completion_time,p[i].CT);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;//Calculate average turnaround time
    avg_waiting_time = (float) total_waiting_time / n;//Calculate average waiting time

    cout<<endl<<endl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {//Print all processes
        cout<<p[i].pid<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].priority<<"\t"<<p[i].CT<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;


}
