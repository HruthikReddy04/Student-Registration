#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE_NAME 30
#define SIZE_ENROLL 15
#define SIZE_COURSENAME 50

int  Course_Slot[5];





struct Course_Sub{
    int Candidates;
    char slot ;
     char name[SIZE_NAME];
    struct Course_Sub* list ;
    struct Student* head;
};
 typedef struct Course_tag {
    char course_name[SIZE_COURSENAME];
    char slot ;
}Course;


 struct Student {
    char name[SIZE_NAME];
    char enroll[SIZE_ENROLL];
     Course c[5];
    struct Student* next;
};

struct Exam_Classroom{
 
 int flag;
 Course c[3];

};

struct Classroom
{
       int room_no;
       int Capacity;
       Course c[5];
       struct Exam_Classroom d[5];
       struct Classroom* next;
};






int maxValue()
{
    int max = Course_Slot[0];
    int i;
    for(i =1;i<5;i++)
    {
        if(max<Course_Slot[i]){
            max= Course_Slot[i];
        }
    }
    return max;
}
void BubbleSort(int array[], int size) {

  int i,j;
  int sorted =0;
  for(int i= 0; i < size - 1 && sorted == 0 ; i++) 
  {
    
    sorted = 1;
    
   
    for (int j = 0; j < size - i - 1 ; j++) {
      
      
      if (array[j] > array[j + 1]) {
        
       
        int temp = array[j];
        array[j] = array[j+ 1];
        array[j + 1] = temp;
        
        sorted= 0;
      } 
    }
  
    
  }
}

void Allot_Classroom(struct Classroom*  clptr , struct Course_Sub *lptr)
{   int i,j,cap;
   struct Classroom*  copy = clptr;
 
    while(lptr!=NULL)
    { 
        int temp = lptr->Candidates;//129
       while(clptr!=NULL)
       {  
         i=lptr->slot-'A';
         j=clptr->d[i].flag;
         if(temp>0 && clptr->d[i].flag<3)//129>0
         {  
           strcpy(clptr->d[i].c[j].course_name,lptr->name);
            cap=temp;
           temp =temp - (clptr->Capacity/3);
           if(temp>=0)
           {    
             printf("%d Students of %s are Alloted to class %d\n",clptr->Capacity/3,lptr->name,clptr->room_no);
           }else{
                 printf("%d Students of %s are Alloted to class %d\n",cap,lptr->name,clptr->room_no); 
           }
          
           clptr->d[i].flag++;
         
         }
         clptr = clptr->next;
       }
      lptr = lptr->list;
      clptr=copy;

    }
}


void Create_Classroom(struct Classroom** clptr ,int max,int n,int Sorted[])
{   
    struct Classroom * curr = *clptr;
    struct Classroom * prev = NULL;
    int i,j=n-1,seats;
    int a=401;
    for(i=1;i<=max;i++)
    {
        curr = (struct Classroom* )malloc(sizeof(struct Classroom));
        curr->room_no=a;
        //printf("Room no : %d ",a);
       
        seats = (Sorted[j]/12 )+1;
        // printf("%d\n",12*seats);
        curr->Capacity= 12*seats;
        j--;
       
        curr->next = prev;
        prev= curr;
        a++;
    }
    *clptr= prev;
   
}


void Collect_Capacities(int Capacities[],struct Course_Sub* lptr)
{
       struct Course_Sub *cptr = lptr;
       int i=0,val;
        while(cptr!=NULL)
       {
           Capacities[i] = cptr->Candidates;
           i++;
           cptr=cptr->list;
       }
}
int Search_Course(struct Classroom* clptr , int i, char slot)
{
    int j =0;
    for(j=0;j<=i;j++)
    {
        if(slot == clptr->c[j].slot)
        {
            return 1;
        }
    }
    return 0;
}

void Allocate_Classroom(struct Classroom *clptr , struct Course_Sub* lptr)
{
    struct Classroom* temp = clptr;
    int i=0,flag;
    printf("%d \n\n",temp->room_no);
   

     
    while(lptr!=NULL)
    {    flag = Search_Course(clptr,i,lptr->slot);//flag = 0 if not present.
        if(temp->Capacity >= lptr->Candidates  &&  !flag)
        {    
            strcpy(temp->c[i].course_name,lptr->name);
            printf("  %s\n",lptr->name);
            temp->c[i].slot = lptr->slot;
            i++;
        }
        
        if(flag==1 || i==5)
        {
           temp=temp->next;
           printf("%d \n\n",temp->room_no);
           if(i==5)
           {
            lptr = lptr->list;
           }
           i=0;
           
        
        }else
        {
         lptr=lptr->list;
        }
        
        
    }

    
}




void Insert_in_Course(struct Course_Sub** dptr,struct Student* nptr,char sub_name[],char slot)
{  int isFound =0;//To know if course exits in list or not.
       
     struct Course_Sub* cptr = *dptr;        //Dereferencing Double Pointer
    struct Course_Sub* lptr = cptr;          //Copy of cptr
    struct Course_Sub* prev= NULL;           
    struct Student* cpptr = (struct Student*)malloc(sizeof(struct Student));

     
    
   
   
    if(cptr!=NULL)
    {  
        while(cptr!=NULL && strcmp(cptr->name,sub_name)!=0)
        {  
            prev= cptr;
           cptr=cptr->list;

        }
        if(cptr!=NULL)
        {
         struct Student* mptr = cptr->head;
         if(mptr == NULL){
            strcpy(cpptr->name ,nptr->name);
           strcpy(cpptr->enroll ,nptr->enroll) ;
            mptr = cpptr;
            nptr->next=NULL;
         }else{
            while(mptr->next!=NULL){
                mptr = mptr->next;
            }
            strcpy(cpptr->name ,nptr->name);
           strcpy(cpptr->enroll ,nptr->enroll) ;

            mptr->next = cpptr;
            nptr->next = NULL;
         }
         isFound =1;
         cptr->Candidates++;
        }
       *dptr=lptr;


    }
   if(isFound == 0) 
   {
    struct Course_Sub* new =  (struct Course_Sub*)malloc(sizeof(struct Course_Sub));
   
    new->list = NULL;
    strcpy(new->name,sub_name);
    new->slot=slot;
    Course_Slot[slot-'A']++;
    strcpy(cpptr->name ,nptr->name);
    strcpy(cpptr->enroll ,nptr->enroll);

    new->head = cpptr;
    cpptr->next =NULL;
    if(prev==NULL){
        *dptr=new;
    }else{
         prev->list = new;
        *dptr=lptr;
    }
    new->Candidates=1;
   }
   
   
}

void  Create_Course(struct Course_Sub* cptr , char course_name[],char slot)
{
   
   while(cptr->list!=NULL){
    cptr= cptr->list;
   }
   struct Course_Sub* newCourse = (struct Course_Sub*)malloc(sizeof(struct Course_Sub));
   strcpy(newCourse->name , course_name);
   newCourse->Candidates=0;
   newCourse->slot=slot;
   Course_Slot[slot-'A']++;

   newCourse->head = NULL;
   newCourse->list =  NULL;
   cptr->list = newCourse;

}

void Delete_Course(struct Course_Sub ** cpptr , char course_name[])
{   struct Course_Sub *cptr  = *cpptr;
    struct Course_Sub *temp = cptr;
    struct Course_Sub *nptr = cptr;
    int iter =0;
     while(cptr!=NULL && strcmp(cptr->name,course_name)!=0)
     {    temp = cptr;
          cptr= cptr->list;
          iter=1;
     }
     if(cptr!=NULL)
     {
            if(cptr->head==NULL)
            {
               
                if(cptr->list == NULL && strcmp(cptr->name,course_name)==0)
               {   if(iter == 0)
                    {
                       *cpptr = cptr->list;

                    }
                   
                   free(cptr);

                  
               }else
               { 
                    temp->list = cptr->list;
                     free(cptr);
               }
               Course_Slot[cptr->slot-'A']--;

            }else
            {
                printf("**  Course can't be deleted because Some Students are Enrolled  ** \n\n ");
            }
     }
 
}


void Add_Student(struct  Student** lpptr ,struct Student std,struct Course_Sub** cpptr){
struct Course_Sub* cptr =*cpptr;
    int i,j,flag=0 ;
    for(i=0;i<5&&!flag;i++){
        for(j=i+1;j<5&&!flag;j++){
            if(std.c[i].slot==std.c[j].slot){
                flag=1;
            }
        }
    }
    if(!flag){
       struct  Student *lptr = *lpptr;
       struct  Student *nptr = (struct Student*)malloc(sizeof(struct Student));
       struct Course_Sub *subject = cptr;
        strcpy(nptr->name , std.name);
        strcpy(nptr->enroll,std.enroll);
        for(i=0;i<5;i++){
            strcpy(nptr->c[i].course_name,std.c[i].course_name);
            nptr->c[i].slot=std.c[i].slot;

            Insert_in_Course(&cptr,nptr,std.c[i].course_name,std.c[i].slot);
                
        }
        nptr->next = lptr;
        lptr = nptr;
        *lpptr = lptr;
        
        *cpptr=cptr;

    }else{
        printf("You had registered  courses having same slot");
        
    }


}






void print_student_list( struct Student* lptr){

    if(lptr!=NULL)
    { 
    int i;
    
    printf("*********************************   Print details ************************************\n");
    while(lptr!=NULL)
      {
    printf("%s  ",lptr->name);
    printf("%s  ",lptr->enroll);
    printf("Courses: ");
       for(i=0;i<5;i++)
       {
        printf("%s  ",lptr->c[i].course_name);
        
       }
       printf("\n\n");
     
       lptr=lptr->next;
      }
     
    }


}
void print_course_list( struct Course_Sub* cptr){
 struct Student* nptr;
    if(cptr!=NULL)
    { 
    int i=1;
    
    while(cptr!=NULL)
      {
    printf("----->%s      Total Candidates:%d\n\n",cptr->name,cptr->Candidates);
    nptr= cptr->head;
    while(nptr!=NULL){
       printf("  %d. %s ",i,nptr->name);
       printf("%s\n",nptr->enroll);
       nptr = nptr->next;
       i++;
    }
       
     cptr=cptr->list;
     printf("\n"); 
     i=1;
      }
     
    }
   


}

struct Student* input(struct Course_Sub** cpptr){
    struct Student* lptr = NULL;
    struct Course_Sub* cptr =*cpptr;
    struct Student abhi;
 

  FILE *fp;
  fp = fopen("data.txt","r");
  if(fp==NULL){
    printf("File can't be opened");
  }else{
    while(fgetc(fp)!=EOF){ 
    fscanf(fp,"%s %s",abhi.name,abhi.enroll);
    fscanf(fp,"%s %c",abhi.c[0].course_name,&abhi.c[0].slot);
    fscanf(fp,"%s %c",abhi.c[1].course_name,&abhi.c[1].slot);
    fscanf(fp,"%s %c",abhi.c[2].course_name,&abhi.c[2].slot);
    fscanf(fp,"%s %c",abhi.c[3].course_name,&abhi.c[3].slot);
    fscanf(fp,"%s %c",abhi.c[4].course_name,&abhi.c[4].slot);
    Add_Student(&lptr,abhi, &cptr);
    }
    fclose(fp);
  
}
*cpptr = cptr;
return lptr;
}

void Del_Student_in_course_list(struct Course_Sub *cptr,char name[])
 {
    if(cptr == NULL){
        printf("Cptr is NULL");
    }
    struct Course_Sub *start = cptr;
    struct Student* lptr =start->head;
    struct Student* nptr = lptr;
    
    while(start!=NULL)
    {
          lptr=start->head;
        //Deletion in Linked List.
        
        
           if(lptr->next ==NULL && strcmp(name,lptr->name)==0 ) 
           {
            free(lptr);
            start->head = NULL;
            
           }else if(strcmp(name,lptr->name)==0)
           {
            lptr=lptr->next;
            free(nptr);
           }else
           {
                while(lptr!=NULL && strcmp(name,lptr->name)!=0 )
              {  nptr= lptr;
              lptr=lptr->next;
              }
              if(lptr!=NULL)
              {
              nptr->next = lptr->next;
              free(lptr);
              }
        
           }

         start->Candidates--;
              

        start = start->list;
    }
    
    
}





void Del_Student(struct Student** lpptr, struct Course_Sub *cptr ,char enroll[SIZE_ENROLL]){
    

   
    struct Student *lptr = *lpptr;
    struct Student *nptr  =NULL;
    if(lptr!=NULL){
        while(lptr!=NULL && strcmp(lptr->enroll,enroll)!=0 )
        {     nptr = lptr;
              lptr=lptr->next;
        }

        if(lptr == NULL){
            printf("\nDeletion Failure\n");
            printf("Student Not Found\n");
          
        }
        else if(lptr->next==NULL){
             Del_Student_in_course_list(cptr,lptr->name);
            free(lptr);
            *lpptr= NULL;
           
            printf("\nDeleted Succesfully\n");
        }
        else if(nptr==NULL){
             Del_Student_in_course_list(cptr,lptr->name);
            *lpptr = lptr->next;
            
            free(lptr);
            printf("\nDeleted Succesfully\n");
        }else{
              Del_Student_in_course_list(cptr,lptr->name);
         nptr->next = lptr->next;
        free(lptr);
        printf("\nDeleted Succesfully\n");
        }
          
        
        

    }

    
}



int main()
{
  struct Student* lptr = NULL;
  struct Course_Sub* cptr = NULL;
  struct Classroom* clptr = NULL;
  lptr =  input(&cptr);
  int count=0,i,j,Capacites[count],Sorted[count];
  
  

  
printf("Enter \n");
printf("1.Add Student to Student List\n");
printf("2.Delete Student to student List\n");
printf("3.Create a new Course \n");
printf("4.Delete a Course\n");
printf("5.Allot Courses to Classrooms for Lectures\n");
printf("6.Allot Courses to Classrooms for Examination\n");
printf("7.Print Student List\n");
printf("8.Print Course List\n");
char course[SIZE_COURSENAME];
do{
scanf("%d",&j);
switch(j)
{
    case 1:
     printf("Enter Student Details:\n\n"); 
     struct Student abhi;
     FILE *fp ;
     fp = fopen(".txt","r");
     fscanf(fp,"%s %s",abhi.name,abhi.enroll);
    fscanf(fp,"%s %c",abhi.c[0].course_name,&abhi.c[0].slot);
    fscanf(fp,"%s %c",abhi.c[1].course_name,&abhi.c[1].slot);
    fscanf(fp,"%s %c",abhi.c[2].course_name,&abhi.c[2].slot);
    fscanf(fp,"%s %c",abhi.c[3].course_name,&abhi.c[3].slot);
    fscanf(fp,"%s %c",abhi.c[4].course_name,&abhi.c[4].slot);
    Add_Student(&lptr,abhi, &cptr);
    print_student_list(lptr);
    break;
     
     case 2:
     printf("Enter Student Enrollment number to be Deleted:");
     char del[SIZE_ENROLL];
     scanf("%s",del);
    Del_Student(&lptr,cptr,del);
     break;


     case 3:
     printf("Enter Name  and Slot of Course that is Created:");
     char slot;
     scanf("%s\n",course);
     scanf("%c",&slot);
     Create_Course(cptr,course,slot);

     break;

     case 4:
     printf("Enter name of Course to be Deleted:");
     scanf("%s\n",course);
     Delete_Course(&cptr,course);
     break;

     case 5:
     for(i=0;i<5;i++)
  {
    count=count+Course_Slot[i];
  }
  
  Collect_Capacities(Capacites,cptr);
  for(i=0;i<count;i++)
  {
    Sorted[i]=Capacites[i];
  }
  BubbleSort(Sorted,count);

  Create_Classroom(&clptr,maxValue(),count,Sorted);
    Allocate_Classroom(clptr,cptr);
     break;

     case 6:
    
     Allot_Classroom(clptr,cptr);
     break;

     case 7:
     print_student_list(lptr);
     break;

   
     case 8:
      print_course_list(cptr);
      break;
     case 9:
     printf("Exit");


}

}while(j!=9);




 

}
