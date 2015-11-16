/*****************************************************************************
 * Copyright (C) Anshika Gupta   guptaa14.comp@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
/*LIBRARY MANAGEMENT*/
/*NOTE:This management must run in only fullscreen (maximized) window of terminal...sorry for inconvienence*/


#include<ncurses.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define student 2
#define admin 1

void user_login();
void menu();
void add_book();
void add_memeber();
void view_member();
void issue_book();
void return_book(); 
void search_book();
void view_book();
void delete_book();
void delete_member();
void search_member();
void view_issued();

typedef struct member {
	int id;
	char mem_name[10];

} member;

typedef struct book{
	int id;
	char book_name[20];
	char author[20];
	int qty;
	char category[20];
} book;

typedef struct issue {
	int member_id;
	char book_name[20];
	char member_name[20];
	int i_day;
	int i_mon;
	int i_yr;
	int r_day;
	int r_mon;
	int r_yr;

} issue;


/* This Function adds new members to library*/
 void add_member() {
	struct member add;
	char name[50],choice[2];
	int id;
	clear();
	FILE* fm = fopen("member.txt","a");
	if(fm == NULL) {
		printw("ERROR WHILE OPENING FILE\n");
		menu();
	}
	
	else {
		printw("Enter member id :");
		scanw("%d",&add.id);
			
		printw("Enter member Name:");
		scanw("%s",add.mem_name);
			
		fwrite(&add,sizeof(struct member),1,fm);
		fclose(fm);
		printw("Do you want to add more members?(press y) else press any other key\n");
		scanw("%s",choice);
		if(strcmp(choice,"y") == 0) 
			add_member();
			
		printw("\n");
		printw("PRESS ANY KEY TO EXIT\n");
		getch();
		clear();
		menu();
		return;
		
	}

}

/*Shows all the records of member*/
void view_member() {
	struct member view;
	FILE* fm = fopen("member.txt","r");
	clear();
	while (fread (&view, sizeof(struct member),1, fm)) {
		printw("ID = %d   Name = %s \n",view.id, view.mem_name);
	}
	fclose(fm);
	printw("\n");
	printw("PRESS ANY KEY TO EXIT\n");
	getch();
	clear();
	menu();
}

/*Function to add books to library.*/
void add_book() {
	struct book add;
	char choice[2];
	char name[50];
	char author[50];
	char category[50];
	int quantity;
	
	FILE* fp = fopen("book.txt","a");
	clear();
	if(!fp) {
		printw("error\n");		
		return;
	}
	
	else {
		printw("Enter Book id :");
		scanw("%d",&add.id);
		
		printw("Enter Book Name:");
		scanw("%s",name);
		strcpy(add.book_name,name);

		printw("Enter Book Author:");
		scanw("%s",author);
		strcpy(add.author,author);

		printw("Enter number of copies:");
		scanw("%d",&quantity);
		add.qty=quantity;
		
		printw("enter category(kids/recreation/mystery/magazine/novel/lifestyle/academics):");
		scanw("%s",category);
		strcpy(add.category,category);
		
		fwrite(&add,sizeof(struct book),1,fp);
		fclose(fp);
		
		printw("RECORD SAVED..Do you want to add more books in the record?(press y) else press any other key\n");
		scanw("%s",choice);
		
		if(strcmp(choice,"y") == 0) 
			add_book();
			
		printw("\n");
		printw("PRESS ANY KEY TO EXIT\n");
				
		getch();
		clear();			
		menu();
		return;
		
	}
	

}

/*issue books to students*/
void issue_book() {
	struct member read;
	struct issue iss;
	struct book confirm;
	char name[50],choice[2];
	
	FILE *fp = fopen("book.txt","a");
	FILE *fm = fopen("member.txt","r");
	FILE *fi = fopen("issue.txt","a");
	clear();
	printw("Enter book name");
	scanw("%s",name);
	while (fread(&confirm, sizeof(struct book), 1, fp)) {
		if(strcmp(confirm.book_name,name) == 0) 
			continue;
		else { 
			printw("This book record does not exist!\n");
			menu();
		}
	}
	
	printw("Please Enter member ID:");
	scanw("%d",&iss.member_id);

	printw("Enter date of issue");
	scanw("%d",&iss.i_day);

	printw("Enter month of issue");
	scanw("%d",&iss.i_mon);

	printw("Enter year of issue");
	scanw("%d",&iss.i_yr);

	printw("Enter date of return");
	scanw("%d",&iss.r_day);

	printw("Enter month of return");
	scanw("%d",&iss.r_mon);

	printw("Enter year of return");
	scanw("%d",&iss.r_yr);
	//we make sure that the member that the book is issued to exists in the records
	while (fread (&read, sizeof(struct member), 1, fm)) {
		if(read.id == iss.member_id) {
			strcpy(iss.member_name, read.mem_name);
		}
	}

	fwrite(&iss,sizeof(iss),1,fi);
	/*we write this record in the issue file so that these files can be viewed at once*/
	printw("ISSUED..Do you want to issue more books?(press y) else press any other key\n");
	scanw("%s",choice);
	if(strcmp(choice,"y") == 0) 
		issue_book();
					
	fclose(fi);
	fclose(fp);
	fclose(fm);
	getch();
	clear();
	menu();
}
/*function to accept books is return books and imply fine if given late*/
void return_book() {

	char book[50],name[20];
	struct issue read;
	int fine, date = 15 ;
	clear();
	
	printw("Enter the members name");
	scanw("%s",name);
	
	FILE *fi = fopen("issue.txt","r");
	while (fread (&read, sizeof(struct issue), 1, fi)) {
		if( strcmp(read.member_name,name) == 0 ) { 
			
			printw ("Member ID = %d\n",read.member_id); 
			printw("Member Name = %s\n",read.member_name);
			printw("Issue date =  %d/%d/%d\n",read.i_day,read.i_mon,read.i_yr);  
			printw("Return Date  %d/%d/%d\n",read.r_day,read.r_mon,read.r_yr);

		}
	}	
	if(15 <= read.r_day) {
		printw("On time.no fine.Thankyou\n");
	}
	else if(15 > read.r_day) {
		fine = (date - read.r_day)*50;
		printw("Book not returned on time.Please pay fine of %d\n",fine);
	}
	getch();
	clear();
	menu();
}

/*The student and also the librarian can search a particular book according to its name or book ID*/
void search_book() {
	FILE *fp;
	char name[50],cho[2];
	int id,selection;
	struct book read;
	
	fp = fopen("book.txt","r");
	clear();
	printw("Search by : 1. ID or 2. Name \n");
	scanw("%d",&selection);

	if(selection == 1) {
		printw("Enter book ID:\n");
			scanw("%d",&id);
		while (fread (&read, sizeof(struct book), 1, fp)) {
		
			if(read.id==id) {
			
				printw("Name: %s\n", read.book_name);
				printw("Author: %s\n", read.author);
				printw("Quantity:%d\n", read.qty);
				printw("Category:%d\n",read.category);
				     
			}
		}
	}
	if(selection == 2) {
	
		printw("Enter book Name:\n");
		scanw("%s",name);
		while (fread (&read, sizeof(struct book), 1, fp)) {
			if(strcmp(read.book_name,name) == 0) { 
				printw("ID: %d\n",read.id);
				printw("Author: %s\n" ,read.author);
				printw("Quantity:%d\n",read.qty);
				printw("Category:  %s\n",read.category);
			}
		}
	}
	printw("ANOTHER SEARCH?(press y) else press any other key\n");
			scanw("%s",cho);
				if(strcmp(cho,"y") == 0) 
					search_book();
					
	fclose(fp);
	getch();
	clear();
	menu();
} 
/*Shows the entire list of books in library*/
void view_book() {
	FILE *fp;
	struct book view;
	int x = 2;
	fp = fopen("book.txt","r");
	clear();
	move(2,2);
	printw("ID");
	move(2,20);
	printw("NAME");
	move(2,35);
	printw("AUTHOUR");
	move(2,50);
	printw("QUANTITY");
	move(2,65);
	printw("CATEGORY");
	printw("\n");
	while (fread (&view, sizeof(struct book), 1, fp)) {
		x = x + 2;
		move(x,2);
		printw("%d",view.id);
		move(x,20);
		printw("%s",view.book_name);
		move(x,35);
		printw("%s",view.author);
		move(x,50);
		printw("%d",view.qty);
		move(x,65);
		printw("%s",view.category);
		printw("\n");
	}
	
	fclose(fp);
	printw("PRESS ANY KEY TO EXIT\n");
	getch();
	clear();
	
	menu();

}

/*The librarian can search a particular student according to its ID*/
void search_member(){
	FILE *fm;
	char name[50],cho[2];
	int id,choice;
	struct member search;
	fm = fopen("member.txt","r");
	clear();
	printw("Search by : 1. ID or 2. Name \n");
	scanw("%d",&choice);
	if(choice == 1){
		printw("Enter member ID:\n");
		scanw("%d",&id);
		while (fread (&search, sizeof(struct member), 1, fm)) {
			if(search.id==id)
			
				printw("Name: %s   ID : %d\n",search.mem_name,search.id);
			
		}	
	}
	
	if(choice == 2){
		printw("Enter Member Name:\n");
		scanw("%s",name);
		while (fread (&search, sizeof(struct member), 1, fm))
		
			if(strcmp(search.mem_name,name)==0)
			
				printw("ID: %d   Name: %s \n", search.id, search.mem_name);
			
		
	}
	printw("search again?(press y) else press any other key\n");
	scanw("%s",cho);
	if(strcmp(cho,"y") == 0) 
		search_member();
					
	fclose(fm);
	getch();
	clear();
	menu();
}

/*It deletes a particular book record completely.
 *Input is name of book*/
void delete_book() {

	struct book delete;
	
	int success;
	char name[50],cho[2];

	FILE* fo = fopen("book.txt","r");
	FILE* ft = fopen("temp.txt","w");
	clear();
	
	printw("Enter name of Book to be deleted\n");
	scanw("%s",name);
	
	while (fread (&delete, sizeof(struct book), 1, fo)) {//reads all record except the one that matches into a new temporary file
		if(strcmp(delete.book_name, name) != 0)
			fwrite(&delete,sizeof(struct book),1,ft);
	}
	fclose(fo);
	fclose(ft);

	fo = fopen("book.txt","w");
	ft = fopen("temp.txt","r");
	/*reads back the content of new file into the old which now does not contain deleted record*/
	while (fread (&delete, sizeof(struct book), 1, ft)) {
		fwrite(&delete,sizeof(struct book), 1, fo);
	}
	fclose(fo);
	fclose(ft);

	printw("Delete Success\n");
	printw("search again?(press y) else press any other key\n");
	scanw("%s",cho);
	if(strcmp(cho,"y") == 0) 
		delete_book();
				
	printw("\n");
	printw("PRESS ANY KEY TO EXIT\n");
	getch();
	clear();
	menu();
}

/*It deletes a particular member record completely.
 *Input is name of member*/
void delete_member() {

	struct member delete;
	char old[10]="member.txt",new[10]="newmem.txt";
	int id;

	FILE* fo = fopen("member.txt","r");
	FILE* fn = fopen("newmem.txt","w");
	clear();
	printw("Enter ID of Member to be deleted\n");
	scanw("%d",&id);
	//writing all records from old file to new file except matching records	
	while (fread (&delete, sizeof(struct member), 1, fo))
		if(delete.id != id)
			fwrite(&delete,sizeof(struct member),1,fn);
	
	fclose(fo);
	fclose(fn);

	fo = fopen("member.txt","w");
	fn = fopen("newmem.txt","r");
	//write from new file back into old file..without the deleted record
	while (fread (&delete, sizeof(struct member), 1, fn))
		fwrite(&delete,sizeof(struct member),1,fo);
	
	fclose(fo);
	fclose(fn);

	printw("DELETED\n");
	printw("\n");
	printw("PRESS ANY KEY TO EXIT\n");
	getch();
	clear();
	menu(admin);

}

/*Displays list of issued books*/
void view_issued() {
	int x = 2;
	struct issue view;
	FILE* fi = fopen("issue.txt","r");
	clear();
		move(2,20);
		printw("Member ID");
		move(2,35);
		printw("Member Name");
		move(2,50); 
		printw("Issue date:");
		move(2,65); 
		printw("Return Date");  
		
	
	while (fread (&view, sizeof(struct issue), 1, fi)) {
		x = x + 2;
		move(x,20);
		printw("%d",view.member_id);
		move(x,35);
		printw("%s",view.member_name);
		move(x,50);
		printw("%d/%d/%d",view.i_day,view.i_mon,view.i_yr);
		move(x,65);
		printw("%d/%d/%d",view.r_day,view.r_mon,view.r_yr);
		
	}
	getch();
	clear();
	menu();
}

/*It gives access to Student or Administrator(Librarian)*/
void user_login() {	
	int choice;
	printw("ENTER CHOICE : 1.STUDENT   2.ADMINISTRATOR\n");
	scanw("%d", &choice);
	
	if(choice == 1)
				
			menu(student);
			
	else if(choice == 2) 
	
			menu(admin);
        	
        else {
        	getch();
                printw("incorrect user or choice\n");
                user_login();
        }

}
 /*Displays the menu for student and librarian separately according to the input the user-whether student or librarian*/ 
void menu(int x) {

	int choice;
	if(x == student) {
	
		printw("---------------------------------------WELCOME STUDENT-----------------------------------\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t 1. Search a book\t\t********\n");
		printw("****\t\t\t\t 2. View book list\t\t********\n");
		printw("****\t\t\t\t 3. Exit\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("---------------------------------------------------------------------------------\n");
		printw("\n");
		printw("****************************Enter your choice********************************************\n");
		scanw("%d", &choice);	
			
		if(choice == 1){
				search_book();
				
		}
		else if(choice == 2) {	
				view_book();
				
		}
		else if(choice == 3) {
				return;
		}
		else {
				printw("Wrong choice! please Enter again....\n");
				menu(student);
		}		
			
	}
	else {
	
		printw("---------------------------------------WELCOME ADMINISTRATOR---------------------------\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t 1. Add book\t\t\t********\n");
		printw("****\t\t\t\t 2. Add member\t\t\t********\n");
		printw("****\t\t\t\t 3. Issue a book\t\t********\n");
		printw("****\t\t\t\t 4. Search a book\t\t********\n");
		printw("****\t\t\t\t 5. View book list\t\t********\n");
		printw("****\t\t\t\t 6. Delete a book record\t********\n");
		printw("****\t\t\t\t 7. View member list\t\t********\n");
		printw("****\t\t\t\t 8. Search member\t\t********\n");
		printw("****\t\t\t\t 9. Delete member\t\t********\n");
		printw("****\t\t\t\t 10. View Issued Books\t\t********\n");
		printw("****\t\t\t\t 11.Return book\t\t\t********\n");
		printw("****\t\t\t\t 12. Exit\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("****\t\t\t\t\t\t\t\t********\n");
		printw("---------------------------------------------------------------------------------\n");
		printw("\n");
		printw("*********************Enter your choice*********************************\n");
		scanw("%d",&choice);		
		
		if(choice ==1) {
				add_book();
				
			}
		else if(choice == 2) {	
				add_member();
				return;
		}
		else if(choice == 3) {	
				issue_book();
				
		}
		else if(choice == 4) {	
				search_book();
				
		}
		else if(choice == 5) {	
				view_book();
				
		}
		else if(choice == 6) {	
				delete_book();
				
		}
		else if(choice == 7) {	
				view_member();
				
		}
		else if(choice == 8) {	
				search_member();
				
		}
		else if(choice == 9) {	
				delete_member();
				
		}
		else if(choice == 10) {	
				view_issued();
				
		}
		else if(choice == 11) {	
				return_book();
				
		}
		else if(choice == 12) {
				return;
				
		}
		else {
				printw("Wrong choice! Enter again");
				menu(admin);
		}
	}
}
int main() {
	initscr();
	raw();
	int a = 4;
	start_color();
	
	init_pair(1, COLOR_BLUE, COLOR_YELLOW);
	attron(COLOR_PAIR(1));
	bkgd(COLOR_PAIR(1));
	
	printw("---------------------------------------LIBRARY MANAGEMENT-------------------------\n");
	printw("****\t\t\t\t\t\t\t\t********\n");
	printw("****\t\t\t\t\t\t\t\t********\n");
	printw("****\t\t\t\tPlease Verify User\t\t********\n");
	printw("****\t\t\t\t\t\t\t\t********\n");
	printw("****\t\t\t\t\t\t\t\t********\n");
	printw("---------------------------------------------------------------------------------\n");
	user_login();
	attroff(COLOR_PAIR(1));
	getch();
	endwin();
	return 0;
}














