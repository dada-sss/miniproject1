TITLE:LIBRARY MANAGEMENT

NAME:ANSHIKA GUPTA

MIS:111403056

Dear reader,
This database management is a small versionaof a library system that attempts perform tasks taht a database is expecte d to do
such as:- 

1.ADDING AND DELETING BOOK RECORDS FROM A FILE
	This function accepts input from user and stores in a text file called:"book.txt"
	The delete function takes nput as a book name and deletes that particular book record from the file "book.txt"
	it does so by first copying all contents of the original file "book.txt" except for the record giiven as input for deletion 
	these are stored in a file called "temp.txt" and are hen re-read into book.txt
	thus in this manner a record can be deleted
	

2.ADDING AND DELETING MEMBER RECORDS FROM A FILE 
	THIS function also works similar to the above mentioned function except here the storage of member records is in "member.txt"
	and the temporary file used is "newmem.txt"
	

3.ISSUING AND ACCEPTING BOOKS WITH PROPER FINE FOR LATE SUBMISSION
	ISSUING: this function issues a bok by takin MEMBER ID as the only input along with BOOK NAME and automatically finds out the name of 		the member that the ID corresponds to and adds a record in the file called "issue.txt"
	RETURNING: this fuction accepts back the book and implys fine in case the due date of submission is surpassed 
	
thus in this way all effective functions that should be carried out in a library program are successfully inplemented
n curses has also been used for a friendly user interface
	
