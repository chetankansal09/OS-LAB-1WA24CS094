#include<stdio.h>

struct fc{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main(){

    struct fc p[20];
    int i,j,n;
    int time=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter PID, AT, BT for process %d: ",i+1);
        scanf("%d %d %d",&p[i].pid,&p[i].at,&p[i].bt);
    }

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(p[j].at > p[j+1].at){
                struct fc temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    for(i=0;i<n;i++){

        if(time < p[i].at)
            time = p[i].at;

        time = time + p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    return 0;
}
