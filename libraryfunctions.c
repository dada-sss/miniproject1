
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
/*Allows librarian to issue books to students.
 *Input is the date of issue and return and also the book name and member ID*/
void issuebooks(){
	FILE *fm, *fi;
	int flush,id;
	struct member read;
	struct issue iss;

	fm = fopen("member.txt","r");
	fi = fopen("issue.txt","a");

	printf("Enter book name");
	scanf("%d",&flush);
	fgets(iss.book_name,50,stdin);

	printf("Enter member ID:");
	scanf("%d",&id);
	iss.member_id=id;

	printf("Enter date of issue");
	scanf("%d",&iss.i_day);

	printf("Enter month of issue");
	scanf("%d",&iss.i_mon);

	printf("Enter year of issue");
	scanf("%d",&iss.i_yr);

	printf("Enter date of return");
	scanf("%d",&iss.r_day);

	printf("Enter month of return");
	scanf("%d",&iss.r_mon);

	printf("Enter year of return");
	scanf("%d",&iss.r_yr);
	
	while (fread (&read, sizeof(struct member), 1, fm)) {
		if(read.id==iss.member_id){
			strcpy(iss.member_name,read.name);
		}
	}

	fwrite(&iss,sizeof(iss),1,fi);
	fclose(fi);
	fclose(fm);
	menu();
}

/*The student and also the librarian can search a particular book according to its name or book ID*/
void searchbooks(){
	FILE *fp;
	char name[50];
	int id,choice,flush;
	struct book read;

	fp = fopen("book.txt","r");
	printf("Search by : 1. ID or 2. Name \n");
	scanf("%d",&choice);

	if(choice==1){
		printf("Enter book ID:\n");
			scanf("%d",&id);
		while (fread (&read, sizeof(struct book), 1, fp)) {
			if(read.id==id){
				printf("Name: %s   Author: %s   Quantity:%d  Rack No:  %d\n",read.name,read.author,read.quantity,read.rackno);
			}
		}
	}
	if(choice==2){
		printf("Enter book Name:\n");
			scanf("%d",&flush);
		while (fread (&read, sizeof(struct book), 1, fp)) {
			fgets(name,50,stdin);
			if(strcmp(read.name,name)==0){
				printf("ID: %d   Author: %s   Quantity:%d  Rack No:  %d\n",read.id,read.author,read.quantity,read.rackno);
			}
		}
	}
	fclose(fp);
	menu();
} 

/*Shows the entire list of books in library*/
void viewbooks() {
	FILE *fp,*fi;
	int count,confirm = 1;
	struct book read;
	struct issue iss;

	fp = fopen("book.txt","r");
	fi = fopen("issue.txt","r");
	if(!fi) {
		confirm = 0;	
	}
	while (fread (&read, sizeof(struct book), 1, fp)) {
		count=0;
		if(confirm == 1) {
			while (fread (&iss, sizeof(struct issue), 1, fi))
			{
					if(strcmp(read.name,iss.book_name)==0)
						count++;
			}
		}
		printf ("ID = %d   Name = %s  Author = %s  Quantity = %d   Rack No = %d \n",read.id,read.name,read.author,read.quantity-count,  			read.rackno);
	}
	fclose(fp);
	if(confirm == 1) {
		fclose(fi);
	}
	menu();
}

/*The librarian can search a particular student according to its ID*/
void searchmembers(){
	FILE *fm;
	char name[50];
	int id,choice,flush;
	struct member mem;
	fm = fopen("member.txt","r");
	printf("Search by : 1. ID or 2. Name \n");
	scanf("%d",&choice);
	if(choice==1){
		printf("Enter member ID:\n");
		scanf("%d",&id);
		while (fread (&mem, sizeof(struct member), 1, fm))
		{
			if(mem.id==id){
				printf("Name: %s   ID : %d\n",mem.name,mem.id);
			}
		}
	}
	
	if(choice==2){
		printf("Enter book Name:\n");
		scanf("%d",&flush);
		while (fread (&mem, sizeof(struct member), 1, fm))
		{
			fgets(name,50,stdin);
			if(strcmp(mem.name,name)==0){
				printf("ID: %d   Name: %s \n", mem.id, mem.name);
			}
		}
	}
	fclose(fm);
	menu();
}
































