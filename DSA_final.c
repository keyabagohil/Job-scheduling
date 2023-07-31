#include <stdio.h>
#include <stdbool.h>  
#include <stdlib.h>
int num = 1;

typedef struct time
{
    int time_dig;
    char indc;
} time;

struct time mngr_strt_time;
struct time mngr_end_time;

int time_diff(time strt,time end)
{
    if (strt.indc == end.indc)
        return (end.time_dig - strt.time_dig);
    else 
        return ((end.time_dig + 12) - strt.time_dig);
}


//creating linked list structure
int format_24(int n){
 return 12+n;
}

struct node
{
    int sr_no;
    char name[20];
    time specific_hour[2];
    int no_hours;
    int spec;
    struct node *next;
 
}*front[23],*rear[23],*emp[12];

void format_12(int a){
	if(a>12)
	 printf("%d p.m  ",a-12); 
	else if(a==12)
	 printf("12 noon");
	else
	 printf("%d a.m  ",a);
}

void time_slot(int s){
	format_12(s);
	printf(" to ");
	format_12(s+1);
}

void empty(){
    for(int i=0;i<12;i++){
        emp[i]=NULL;
    }
}

void display(int n, int s, int e )
{
   printf("The list of employees employed are as follows:\n");
   printf("Time slot\t\t\t\t\t\tEmployee name:\n");
   for(int i=0;i<n;i++){
    time_slot(s+i);
    if(emp[i]!=NULL){
        printf("\t\t\t\t\t%s\n", emp[i]->name);
    }
    else{
        printf("\t\t\t\t\t-------------\n");
    }
	
   }    
}
 

void generate_maxemp(int n)
{
    
    struct node *temp;
    int avail=n;  
    int allot[2];
    int avl = 0,flag = 0;
    
    for(int i=0 ;i<n-1 ; i++)
    {
        temp=front[i];
        
        while(temp != NULL)
        {
            allot[0]=-1,allot[1]=-1;

            for (int i = time_diff(mngr_strt_time,temp->specific_hour[0]); i < (time_diff(mngr_strt_time,temp->specific_hour[0])+temp->no_hours)  && avail!=0; i++)
            {
                if (allot[0] != -1 && emp[i]!=NULL)
                    break;
                else if (allot[0] != -1 && emp[i]==NULL)
                {
                    // allot[1] = i;
                    emp[i] = temp;
                    avail--;
                }
                else if (emp[i] == NULL && allot[0] == -1)
                {                   
                    emp[i]=temp;
                    allot[0] = i;
                }

            }
            temp = temp->next;
        }
    }
    for(int i=n-1;i<2*n-1;i++)
    {
        if(avail!=0)
        {
           temp=front[i];
           while(temp!=NULL)
           {
              if(avail<=temp->no_hours)
              {
                  for(int i=0;i<n;i++)
                  {
                      if(emp[i]==NULL)
                        emp[i]=temp;
                  }
                  avail=0;
                  break;
              }
              else
              { 
                 int k=temp->no_hours;
                 avail=avail-k;
                 for(int i=0;i<n && k!=0;i++)
                  {
                      if(emp[i]==NULL)
                       {
                         emp[i]=temp;
                         k--;
                       }
                  }
              }
            temp=temp->next;          
           }
        }
        else
            break;
    }

}
 
void generate_minemp(int n)
{
    struct node *temp;
    int avail=n;
    int allot[2];

     for(int i=2*n-1;i>n-2;i--)
    {   // printf("@");
        if(avail!=0)
        {  //printf("!");
           temp=front[i];
           while(temp!=NULL)
           {
              if(avail<=temp->no_hours)
              { //  printf("if");
                  for(int i=0;i<n;i++)
                  {
                      if(emp[i]==NULL)
                        emp[i]=temp;
                  }
                  avail=0;
                  break;
              }
              else
              { // printf("else");
                 int k=temp->no_hours;
				 avail=avail-k;
                 for(int i=0;i<n && k!=0;i++)
                  {
                      if(emp[i]==NULL)
                       {
                         emp[i]=temp;
                         k--;
                       }                      
                  }
              }
			  temp=temp->next; 
           }
                    
        }
        else
            break;
	}	    
    
    for(int i=n-2; i>=0 && avail!=0 ; i--)
    {
        temp=front[i];        
        while(temp != NULL)
        {
            allot[0]=-1,allot[1]=-1;

            for (int i = time_diff(mngr_strt_time,temp->specific_hour[0]); i < (time_diff(mngr_strt_time,temp->specific_hour[0])+temp->no_hours)  && avail!=0 ; i++)
            {
                if (allot[0] != -1 && emp[i]!=NULL)
                    break;
                else if (allot[0] != -1 && emp[i]==NULL)
                {
                    emp[i] = temp;
                    avail--;
                }
                else if (emp[i] == NULL && allot[0] == -1)
                {
                     emp[i]=temp;
                    allot[0] = i;
                }

            }
            temp = temp->next;
        }
    }
}
 
int main()
{
    //declaring variables
    int inp = 0;
    printf("\n\n\nJOB Scheduling Programm..");
    man_again:
    printf("\n\nManager..\n\nEnter Starting Time:-\nchoose  1. to enter from AM \n\t2. to enter from PM..\nWhat to do:");
    scanf("%d",&inp);
    
    switch (inp)
    {
    case 1:
     one1:printf("\nEnter in AM : ");
         scanf("%d",&mngr_strt_time.time_dig);
         mngr_strt_time.indc = 'a';
         if(mngr_strt_time.time_dig<7){
           printf("INVALID INPUT!");
           goto one1;
        }
         break;
    case 2:
     two:printf("\nEnter in PM : ");
        scanf("%d",&mngr_strt_time.time_dig);
        mngr_strt_time.indc = 'p';
        if(mngr_strt_time.time_dig>6){
           printf("INVALID INPUT!");
           goto two;
        }
        break;
    default:
        printf("\nPlease Enter valid input...");
        goto man_again;
        break;
    }
    printf("\n\nEnter End Time:-\nchoose  1. to enter from AM \n\t2. to enter from PM..\nWhat to do:");
    scanf("%d",&inp);
    switch (inp)
    {
    case 1:
    three:printf("\nEnter in AM : ");
        scanf("%d",&mngr_end_time.time_dig);
        mngr_end_time.indc = 'a';
        if(mngr_strt_time.time_dig<7){
           printf("INVALID INPUT!");
           goto three;
        }
        break;
    case 2:
    four:printf("\nEnter in PM : ");
        scanf("%d",&mngr_end_time.time_dig);
        mngr_end_time.indc = 'p';
        if(mngr_end_time.time_dig>6){
           printf("INVALID INPUT!");
           goto four;
        }
        break;
    default:
        printf("\nPlease Enter valid input...");
        goto man_again;
        break;
    }
    if ( time_diff(mngr_strt_time,mngr_end_time) < 0)
    {
        printf("\nInvalid Input..");
        goto man_again;
    }
    

    int n= time_diff(mngr_strt_time ,mngr_end_time);
    
      
//menu driven code
one:    printf("\nENTER\n");
        printf("1 to Add the details of the employee\n");
        printf("2 to Generate the schedule for the job with minimum employees\n");
        printf("3 to Generate the schedule for the job with maximum employees\n");
        printf("4 to Exit\n");
        int d;
        scanf("%d",&d);
 
    switch(d)
    {
        case 1:
    {
        struct node* ptr = (struct node*)malloc(sizeof(struct node));
        ptr->next=NULL;
        printf("\nENTER\n");
        printf("Enter the name of the employee\n");
        fflush(stdin);
        scanf("%[^\n]s",ptr->name);
        ptr->sr_no=num++;
reenter:printf("Enter--1: If the time is specific\n\t0:if the time is not specific\nWhat to do :");
        scanf("%d",&ptr->spec);
        if(ptr->spec==1)
        {
            epagain:
            printf("\nManager's Required Time ~ %d:%cm to %d:%cm.",mngr_strt_time.time_dig,mngr_strt_time.indc,mngr_end_time.time_dig,mngr_end_time.indc);
            printf("\nEnter Time according to this duration...");
            inp = 0;
            printf("\nEnter the starting hours"); 
            printf("\n1.to enter in am\n2.to enter in pm\n");

            scanf("%d",&inp);
            if(inp == 1)
                ptr->specific_hour[0].indc = 'a';
            else if(inp == 2){
                ptr->specific_hour[0].indc = 'p';
				ptr->specific_hour[0].time_dig=format_24(ptr->specific_hour[0].time_dig);
			}
            else 
            {printf("\nEnter valid inp..");
            goto reenter;}
            printf("\nEnter : ");
            scanf("%d",&ptr->specific_hour[0].time_dig);
            inp =0;
            // if (time_diff(mngr_strt_time,ptr->specific_hour[0]) < 0)
            // {
            //     printf("\nInvalid Input....");
            //     goto epagain;
            // }
            
            printf("\nEnter the end hours"); 
            printf("\n1.to enter in am\n2.to enter in pm\n");
            scanf("%d",&inp);
            if(inp == 1)
                ptr->specific_hour[1].indc = 'a';
            else if(inp == 2){
				ptr->specific_hour[1].time_dig=format_24(ptr->specific_hour[1].time_dig);
                ptr->specific_hour[1].indc = 'p';
			}
            else {
                printf("Enter valid input..");
                goto reenter;
            }
            printf("\nEnter  :");
            scanf("%d",&ptr->specific_hour[1].time_dig);
            if (time_diff(ptr->specific_hour[1],mngr_end_time) < 0)
            {
                printf("\nInvalid Input....");
                goto epagain;
            }
            
            ptr->no_hours=time_diff(ptr->specific_hour[0],ptr->specific_hour[1]);
            if(ptr->no_hours==n)
            {
                if(front[2*n-2]==NULL){
                  ptr->next=NULL;
                  front[2*n-2]=ptr;
				  rear[2*n-2]=ptr;
                }
                else{
                  rear[2*n-2]->next=ptr;
                  ptr->next=NULL;
                  rear[2*n-2]=ptr;
                }
            }
            else if(front[ptr->no_hours-1]==NULL)
            {
                
                front[ptr->no_hours-1] = ptr;
				rear[ptr->no_hours-1]=ptr;
                ptr->next=NULL;
            }
            else{
                rear[ptr->no_hours-1]->next=ptr;
                ptr->next=NULL;
                rear[ptr->no_hours-1]=ptr;
            }
                
        }
        //for non specific hours
        else if(ptr->spec==0)
        {
            nonagain:
            printf("\nManager's Required Hours : %d",time_diff(mngr_strt_time,mngr_end_time));
            printf("\nEnter Number of hours of sevice :");
            scanf("%d",&ptr->no_hours);
            if (ptr->no_hours > time_diff(mngr_strt_time,mngr_end_time))
            {
                printf("\nIncorrect Input please enter within range...");
                goto nonagain;
            }
            
            
            ptr->specific_hour[0].time_dig=-1;
            ptr->specific_hour[1].time_dig=-1;
            if(front[ptr->no_hours+(n-2)]==NULL){
                front[ptr->no_hours+(n-2)]=ptr;
				rear[ptr->no_hours+(n-2)]=ptr;
			}
            else{
                rear[ptr->no_hours+(n-2)]->next=ptr;
                ptr->next=NULL;
                rear[ptr->no_hours+(n-2)]=ptr;
            }
        }
        else
        {
            printf("Invalid Input\n");
            goto reenter;
        }
        
       goto one;
    }
    case 2:
    {
        generate_minemp( n);
		display(n,mngr_strt_time.time_dig,mngr_end_time.time_dig);
        empty();
        goto one; 
    }
    case 3:
    {
        generate_maxemp(n);
        display(n,mngr_strt_time.time_dig,mngr_end_time.time_dig);
        empty();
    goto one; 
    }
    case 4:
    {
        return 0;
    }
    case 5:
    {
        printf("Invalid Input");
        goto one;
    }
 
    }
   
}