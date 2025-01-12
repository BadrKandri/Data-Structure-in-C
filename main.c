#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct student{
      char *name,*bus;
      struct student *next;
}student;

student *head=NULL;
student *current=NULL;
int nb_student=0;
int x;

void clear_screen() {
    system("cls");
}

student* aloc_node(){
    student *n_student=(student*)malloc(sizeof(student));
    char t[20];
    printf("Enter student name: ");
    scanf("%s",t);
    n_student->name = (char *)malloc((strlen(t) + 1) * sizeof(char));
    strcpy(n_student->name, t);
    printf("Enter student bus: ");
    scanf("%s",t);
    n_student->bus = (char *)malloc((strlen(t) + 1) * sizeof(char));
    strcpy(n_student->bus, t);
    
    n_student->next = NULL;
    return n_student;
}

student* addStudent(){
    student* temp=aloc_node();
    if (head==NULL){
            head=temp;
            current=temp;
    }else{
            current->next=temp;
            current=temp; 
    }
    return temp;
}
student* addStudent_intrv(student*temp){
    if (head==NULL){
            head=temp;
            current=temp;
    }else{
            current->next=temp;
            current=temp;     
    }
    current->next = NULL;
    return temp;
}
void displayAllStudents(student *head){
    student *temp1=head;
    printf("STUDENT LIST:\n");
    while(temp1 != NULL){
        printf("[%s : %s]\n",temp1->name,temp1->bus);
        temp1=temp1->next;
    }
    printf("--->Total students: %d\n",nb_student);
}
void modifier(student*temp4){
    char t[20];
    printf("Enter new student name: ");
    scanf("%s",t);
    temp4->name = (char *)malloc((strlen(t) + 1) * sizeof(char));
    strcpy(temp4->name, t);
    printf("Enter new student bus: ");
    scanf("%s",t);
    temp4->bus = (char *)malloc((strlen(t) + 1) * sizeof(char));
    strcpy(temp4->bus, t); 
}
void supprimer(student*temp4,student*preced,int cnt){
    if(cnt==0){
        head=temp4->next;
        temp4->next=NULL;
    }else{
        preced->next=temp4->next;
        temp4->next=NULL;
    }
    free(temp4);
    nb_student--;  
}
void mdf_sup(char *to_find){
    int m;
        printf("voulez vous le modifer ou suprimer?                                                                               \n*pour modifier : 1\n*pour suprimer : 2\n*pour retourner dans le menu : 3\n----->");       
        if (scanf("%d", &m) != 1) {
        printf("Invalid input. Please enter an integer next time.\n");
        Sleep(2000);
        while (getchar() != '\n');
        return;}
        clear_screen();
        student *temp4 = head;
        if(m==1){
            while (temp4 != NULL) {
                if (  (strcmp(to_find, temp4->name) == 0) || (strcmp(to_find, temp4->bus) == 0)  ){
                    modifier(temp4);
                    break;
                }
                temp4 = temp4->next;}
            clear_screen();
            printf("<DATA CHANGED SUCCESSFULLY>\r");
            Sleep(2000);
        }else if(m==2){
            int cnt=0;
            student *preced = head;
            while (temp4 != NULL) {
                if (  (strcmp(to_find, temp4->name) == 0) || (strcmp(to_find, temp4->bus) == 0)  ){
                    supprimer(temp4,preced,cnt);
                    break;
                }else{
                    temp4 = temp4->next;
                    cnt++;
                }
                if(cnt>1){
                    preced = preced->next;
                }
                }
            clear_screen();
            printf("<DATA DELETED>\r");
            Sleep(2000);
        }
}
void searchStudent(student *head){
    char t[20];
    printf("Enter student or station name: ");
    scanf("%s", t);
    char *to_find = (char *)malloc((strlen(t) + 1) * sizeof(char));
    strcpy(to_find, t);

    student *temp2 = head;
    int found_name = 0,found_bus=0;
    char *info = (char *)malloc(20 * sizeof(char));

    while (temp2 != NULL) {
        if (strcmp(to_find, temp2->name) == 0) {
            found_name = 1;
            strcpy(info, temp2->bus);
            break;
        }else if(strcmp(to_find, temp2->bus) == 0){
            found_bus = 1;
            strcpy(info, temp2->name);
            break;
        }
        temp2 = temp2->next;
    }
    if (!found_name && !found_bus){
        int v;
        clear_screen();
        printf("ERROR !!, %s is not in the database.\nWould you like to add it? (1/0): ", to_find);
        scanf("%d",&v);
        if(v){
            student *temp3 = (student*)malloc(sizeof(student));
            temp3->name = (char *)malloc((strlen(to_find) + 1) * sizeof(char));
            strcpy(temp3->name, to_find);
            printf("Enter student bus: ");
            scanf("%s",t);
            temp3->bus = (char *)malloc((strlen(t) + 1) * sizeof(char));
            strcpy(temp3->bus, t);
            addStudent_intrv(temp3);
            clear_screen();
            printf("<%s ADDED TO SYSTEM>\r", temp3->name);
            Sleep(2500);
            nb_student++;
        } else {
            clear_screen();
        }
    }else if(found_name && !found_bus){
        clear_screen();
        printf("Yes, %s is in the database, and going to: %s\r", to_find,info);
        Sleep(2500);
        mdf_sup(to_find);
        clear_screen();
    }else if(found_bus){
        clear_screen();
        printf("Yes, there is a student who is going to %s, their name is %s\r", to_find,info);
        Sleep(2500);
        mdf_sup(to_find);
        clear_screen();
}
    free(to_find);
    free(info);}

void menu(int x){
    switch(x){
            case 1: addStudent();
                    clear_screen();
                    printf("<%s ADDED TO SYSTEM>\r",current->name);
                    Sleep(2000);
                    nb_student++;
                    break;
            case 2: displayAllStudents(head);
                    break;
            case 3: searchStudent(head);
                    break;            
            case 0: printf("HAVE A NICE DAY !\r");
                    Sleep(1000);
                    break;
           }
}
void lib_esp(student *head){
      while(head!=NULL){
            student *temp =head;
            head=temp->next;
            free(temp);
}}
void print_menu(){
    do{
    printf("MENU:                                                                                                                             \nto add student type 1\nto print list of student type 2\nto search for a student type 3\nto end the program type 0\n-----> ");
    if (scanf("%d", &x) != 1){
        clear_screen();
        printf("input invalid! try again ");
        Sleep(1500);
        clear_screen();
        while (getchar() != '\n');
        print_menu();
    }
    clear_screen();
    menu(x);
}while(x!=0);
if(x!=0){
    print_menu();
    }}

int main(){
        print_menu();
        lib_esp(head);
      return 0;
}
