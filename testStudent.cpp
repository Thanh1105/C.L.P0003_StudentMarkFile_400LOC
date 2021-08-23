#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 100
using namespace std;
 
typedef struct Student {    
    int id;
    char name[30];
    float mark1;
    float mark2;
    float mark3;
    float mark4;
    float mark5;
    float AVG = 0;
    char RANK[10] = "-";
} ST;
 
void printLine(int n) {     
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("_");
    }
    printf("\n");
}
 void  calMark(ST &st) {    ///50LOC
    st.AVG = ((st.mark1*2) + (st.mark2*2) + (st.mark3*2) + (st.mark4*2)+ (st.mark5*2)) / 11;    
}
 
void rank(ST &st) {
    if(st.AVG >= 8) strcpy(st.RANK, "S");
    else if(st.AVG >= 6.5) strcpy(st.RANK, "A");
    else if(st.AVG >= 5) strcpy(st.RANK, "B");
    else strcpy(st.RANK, "C");
}
  
void inputInfoStudents(ST &st, int id) {
    printf("\n Input Name: "); 
	fflush(stdin); gets(st.name);
    printf(" Input Mark 1: "); 
	scanf("%f", &st.mark1);
    printf(" Input Mark 2: "); 
	scanf("%f", &st.mark2);
    printf(" Input Mark 3: "); 
	scanf("%f", &st.mark3);
    printf(" Input Mark 4: "); 
	scanf("%f", &st.mark4);
    printf(" Input Mark 5: "); 
	scanf("%f", &st.mark5);
    st.id = id;
    calMark(st);
    rank(st);
}
 
void inputNo(ST a[], int id, int n) {   ///50LOC
    printLine(40);
    printf("\n Input Student's %dth:", n + 1);
    inputInfoStudents(a[n], id);
    printLine(40);
}
 
void showStudent(ST a[], int n) {       
    printLine(100);
    printf("\n\NO\tID\tNAME\tMARK 1\tMARK 2\tMARK 3\tMARK 4\tMARK 5\tAVERAGE\tRANK");
    for(int i = 0; i < n; i++) {
        printf("\n %d", i + 1);
        printf("\t%d", a[i].id);
        printf("\t%s", a[i].name);
        printf("\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f", a[i].mark1, a[i].mark2, a[i].mark3, a[i].mark4, a[i].mark5);
        printf("\t%.2f", a[i].AVG);
        printf("\t%s", a[i].RANK);
    }
    printLine(100);
}

void searchName(ST a[], char name[], int n) {   ///50LOC
    ST arrayFound[MAX];
    char nameST[30];
    int found = 0;
    for(int i = 0; i < n; i++) {
        strcpy(nameST, a[i].name);
        if(strstr(strupr(nameST), strupr(name))) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showStudent(arrayFound, found);
}
 
  
void sortByAVG(ST a[], int n) {     ///50LOC
    ST tmp;
    for(int i = 0;i < n;i++) {
        for(int j = i+1; j < n;j++) {
            if(a[i].AVG > a[j].AVG) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void sort(ST a[], int n){
		ST tmp;
		char t[50];
		for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
         if (strcmp(a[j-1].name, a[j].name) < 0) {
            strcpy(t, a[j - 1].name);
            strcpy(a[j - 1].name, a[j].name);
            strcpy(a[j].name, t);
         }
      }
	}
}

int idFirst (ST a[], int n) {
    int idMax = 0;
    if (n > 0) {
        idMax = a[0].id;
        for(int i = 0;i < n; i++) {
            if (a[i].id > idMax) {
                idMax = a[i].id;
            }
        }
    }
    return idMax;
}
 
int readFile(ST a[], char rFileName[]) {    ///50LOC
    FILE * fp;
    int i = 0;
    fp = fopen (rFileName, "r");
    printf("Prepare to read the file: "); puts(rFileName);
    while (fscanf(fp, "%5d%30s%10f%10f%10f%10f%10f%10f%10s\n", &a[i].id, &a[i].name, 
            &a[i].mark1, &a[i].mark2, &a[i].mark3, &a[i].mark4, &a[i].mark5, 
            &a[i].AVG, &a[i].RANK) != EOF) {
       i++;
    }
    printf(" Number of students in the file: %d\n", i);
    printf("\n");
    fclose (fp);
    return i;
}
 
void writeFile(ST a[], int n, char wFileName[]) {   ///50LOC
    FILE * fp;
    fp = fopen (wFileName,"w");
    for(int i = 0;i < n;i++){
        fprintf(fp, "%5d%30s%10f%10f%10f%10f%10f%10f%10s\n", a[i].id, a[i].name,a[i].mark1, 
            a[i].mark2, a[i].mark3, a[i].mark4, a[i].mark5, a[i].AVG, a[i].RANK);
    }
    fclose (fp);
}
 
void pressAnyKey() {
    printf("\n\nPress any key...");
    getch();
    system("cls");
}
int main() {    ///20LOC
    int key;
    char rFileName[] = "student.txt";
    char wFileName[] = "student2.txt";
    ST arrayST[MAX];
    int numeOfStudent = 0;
    int idCount = 0;
    numeOfStudent = readFile(arrayST, rFileName);
    idCount = idFirst (arrayST, numeOfStudent);
 
    while(true) {
         
       	printf( "-------------------------------------------------------\n");
        printf( "    1. Add a student into the list.                    \n");
        printf( "    2. Calculate the average mark of all students.     \n");
        printf( "    3. Search a student by name.                       \n");
        printf( "    4. Sort students in descending mark average order. \n");
        printf( "    5. Write student list to student2.txt.            \n");
        printf( "    6. Exit the program.                               \n");
       	printf("--------------------------------------------------------\n");
        printf( "Enter choice(1-6): ");
        scanf("%d", &key);
        switch(key){
            case 1:
               	printf("\n1. Add Student.");
                idCount++;
                inputNo(arrayST, idCount, numeOfStudent);
                printf("\nStudent has been added to list successfully!");
                numeOfStudent++;
                pressAnyKey();
                break;
            case 2:
                 if(numeOfStudent > 0){
                    printf("\n2. Show anverage of students from file %s ", rFileName);
                    showStudent(arrayST, numeOfStudent);
                }else{
                    printf("\nCan't' find list student!");
                }
                pressAnyKey();
                break;
            case 3:
                 if(numeOfStudent > 0) {
                    printf("\n3. Search a student by name.");
                    char strName[30];
                    printf("\nEnter name to search: ");
					fflush(stdin); gets(strName);
                    searchName(arrayST, strName, numeOfStudent);
                }else{
                    printf("\nStudent is not existed!");
                }
                pressAnyKey();
                break;
            case 4:
            			printf("1. Sort students in descending AVG.\n");
       				 	printf("2. Sort students in descending enrollment in alphabet order.\n");
       				 	printf("3. Back to menu\n");
            		int choice1;
            		scanf("%d", &choice1);
            	  switch (choice1){
        			
        	case 1:
        		  if(numeOfStudent > 0) {
                    printf("\n4. Sort students in descending AVG.");
                    sortByAVG(arrayST, numeOfStudent);
                    showStudent(arrayST, numeOfStudent);
                }else{
                    printf("\nCan't find list student!");
                }
                getch();
                return 0;
        	case 2:
        	  if(numeOfStudent > 0) {
                    printf("\nDisplay : Sort students in descending enrollment in alphabet order.");
                    sort(arrayST, numeOfStudent);
                    showStudent(arrayST, numeOfStudent);
                }else{
                    printf("\nCan't find list student!");
                }
                getch();
                return 0;
			case 3:
				pressAnyKey();
                }
				break;
			case 5:
                if(numeOfStudent > 0){
                    printf("\n5. Write student list after sorted to file.");
                    writeFile(arrayST, numeOfStudent, wFileName);
                }else{
                    printf("\nCan't' find list student!");
                }
                printf("\nWrite student list after sorted to file %s successfully!", wFileName);
                pressAnyKey();
                break;
            case 6:
                printf("\nYou have chosen to exit the program!");
                getch();
                return 0;
            default:
                printf("\nThere is no such function!");
                printf("\nPlease choose back from 1 to 6!");
                pressAnyKey();
                break;
        }
    }
}
  

