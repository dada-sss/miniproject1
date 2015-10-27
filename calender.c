
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"project.h"
#define student 1
#define admin 2

struct book{
	int id;
	char name[50];
	char author[50];
	int quantity;
	int rackno;
};

struct issue {
	int member_id;
	char book_name[50],member_name[50];
	int i_day,i_mon,i_yr;
	int r_day,r_mon,r_yr;

};

struct member {
	int id;
	char name[50];

};

/*Function to add members to library.
 *The user(the "Librarian" only!) has to input the member ID and name of student.
 *It gets stored in file*/
void addmember() {
	int choice;
	struct member mem;
	char name[50];
	int id;
	FILE *fm;

	fm = fopen("member.txt","a");
	if(!fm) {
		printf("error\n");
		mem.id=0;
	}

	do {
			printf("Enter member id :");
			scanf("%d",&mem.id);
			
			printf("Enter member Name:");
			scanf("%s",mem.name);

l
}

/*Shows all the records of member- Their ID and names*/
void viewmember() {
	FILE *fm;
	struct member read;
	fm = fopen("member.txt","r");

	while (fread (&read, sizeof(struct member),1, fm)){
		printf ("ID = %d   Name = %s \n",read.id,read.name);
	}
	fclose(fm);
	menu();
}

/*Function to add books to library.
 *The user(the "Librarian" only!) has to input the book ID,name of book,author,copies and rack number.
 *It gets stored in file*/

void addbooks(){
	int choice;
	struct book bk;
	char name[50], author[50];
	FILE *fp;
	fp = fopen("book.txt","a");

	if(!fp){
		printf("error\n");		
		bk.id=0;
	}

	do {
			printf("Enter Book id :");
			scanf("%d",&bk.id);
		
			printf("Enter Book Name:");
			scanf("%s",&name);
			strcpy(bk.name,name);

			printf("Enter Book Author:");
			scanf("%s",bk.author);

			printf("Enter number of copies:");
			scanf("%d",&bk.quantity);
		
		
			printf("enter rack number :");
			scanf("%d",&bk.rackno);
			

		
		
		printf("Save the record and go to menu? 1.Yes 2.No \n");
		scanf("%d",&choice);
		if(choice == 1){
			fwrite(&bk,sizeof(bk),1,fp);
			fclose(fp);
			menu();
			return;
		}
	}while(choice == 1);
	if(choice == 2) {
		menu();
	}
	

}
void displayrules() {
	char array[1600];
	FILE *fp
	fp = fopen("rules.txt","r");
	if(!fp){
		printf("error\n");
	)
	fscanf(fp,%s,array);
	printf("%s\n", array);
	fclose(fp);
}
































