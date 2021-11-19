/*Program to implement FCFS Algorithm
CED19I056
Nandita M*/

#include<stdio.h>

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


int main(){
    int n;
    printf("Enter the number of processes :");
    scanf("%d",&n);

    //Array of process structure
    struct PCB p[10];
    struct PCB temp;

    int sum;
    int TotalTAT=0;
    int TotalWT=0;


    for(int i=0;i<n;i++){
        printf("Enter the Arrival Time ,Burst Time for process %d :\n",i+1);
        scanf("%d %d",&p[i].AT,&p[i].BT);
        p[i].pid=i+1;
    }

    //Sort the processes according to the arrival time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].AT > p[j+1].AT){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    //caluculating the Waiting time ,Turn around time and completion time
    for(int i=0;i<n;i++)
	{
		if(i==0)
		{
			p[i].CT=p[i].AT+p[i].BT;
		}
		else
		{
            p[i].CT=p[i-1].CT+p[i].BT;
		}
	}
    for(int i=0;i<n;i++)
	{
		p[i].TAT = p[i].CT-p[i].AT;
        TotalTAT=TotalTAT+p[i].TAT;
	}
	
	for(int i=0;i<n;i++)
	{
        p[i].WT=p[i].TAT-p[i].BT;
        TotalWT=TotalWT+p[i].WT;
	}

    pline(44);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    pline(44);

    //Printing the table of AT,BT,CT,TAT,WT
    for(int i=0;i< n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT);
    }
    pline(44);

    float avgTAT=(float)TotalTAT/(float)n;
    float avgWT=(float)TotalWT/(float)n;
    printf("Average Turnaround Time is %.3f\n",avgTAT);
    printf("Average Waiting Time is %.3f\n",avgWT);
    return 0;
}