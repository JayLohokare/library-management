
#include<stdio.h>                   
#include<stdlib.h>
#include<string.h>                  
               
#include<termios.h>
#include<time.h>
#include <termios.h>
#include <unistd.h>

#define RETURNTIME 15


char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechnnical","Architecture"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void issuerecord();
void try();


char password[20]={"library"};

//The conio.h lib is unavailable for ubuntu
//These are the getch and getche functions which are otherwise present in conio.h
int getch(void)
{
struct termios oldattr, newattr;
int ch;
tcgetattr( STDIN_FILENO, &oldattr );
newattr = oldattr;
newattr.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
return ch;
}

int getche(void)
{
struct termios oldattr, newattr;
int ch;
tcgetattr( STDIN_FILENO, &oldattr );
newattr = oldattr;
newattr.c_lflag &= ~( ICANON );
tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
return ch;
}



//list of global files that can be accessed form anywhere in program
FILE *fp,*ft,*fs;

//list of global variable
int s;
char findbook;



struct Date
{
    int mm,dd,yy;
};


struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct Date issued;
    struct Date duedate;
};

struct books a;

int main()

{
	Password();
	mainmenu();
	//try();
	getch();
	return 0;

}
void mainmenu()
{
	  system("clear");
    	printf("\n\n");
       
	int i;
	
	printf("\n\n\n*********************MAIN MENU *************************\n\n\n");
	
	printf("1. Add Books\n");
	
	printf("2. Delete books\n");
	
	printf("3. Search Books\n");
	
	printf("4. Issue Books\n");
	
	printf("5. View Book list\n");
	
	printf("6. Edit Book's Record\n");
	
	printf("7. Close Application\n\n");
	
	printf("*********************************************************\n\n");
	
	
	printf("Enter your choice:\n\n");

	switch(getch())
	{
	case '1':
		
		addbooks();
		break;
	case '2':
		deletebooks();
		break;

	case '3':
		searchbooks();
	    break;
	case '4':
		issuebooks();
	    break;
	case '5':
		viewbooks();
		break;
	case '6':
		editbooks();
		break;
	case '7':
	    {
		
		printf("Exiting");
		system("clear");
		exit(0);
	    }
	default:
		{
		
		printf("\aWrong Entry!!Please re-entered correct option");
		if(getch())
		mainmenu();
		}

    }
}


void addbooks(void)    //funtion that add books
{
	
	int i;
	
	printf("\n************************SELECT CATEGOIES***********************\n\n");
	
	printf("1. Computer\n");
	
	printf("2. Electronics\n");
	
	printf("3. Electrical\n");
	
	printf("4. Civil\n");
	
	printf("5. Mechanical\n");
	
	printf("6. Architecture\n");
	
	printf("7. Back to main menu\n\n");
	
	printf("****************************************************************\n\n");
	
	printf("Enter your choice:\n");
	
	scanf("%d",&s);
	if(s==7)
	mainmenu() ;

	system("clear");
	if(s>0 && s<8){
	fp=fopen("Library.dat","ab+");

	if(getdata()==1)
	{
	a.cat=catagories[s-1];
	fseek(fp,0,SEEK_END);
	fwrite(&a,sizeof(a),1,fp);
	fclose(fp);
	printf("\n");
	printf("The record is sucessfully saved");
	printf("\n");
	addbooks();
	}
}
	else{
	printf("Wrong choice");
	addbooks();
	}
	
	
}
void deletebooks()    //function that delete items from file fp
{
    system("clear");
    int d;
    
	system("clear");
	printf("\n");
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("Library.dat","rb+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
	    if(a.id==d)
	    {

		printf("\n");
		printf("The book record is available");
		printf("\n");
		printf("Book name is %s",a.name);
		printf("\n");
		printf("Rack No. is %d",a.rackno);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    printf("\n");
	    printf("No record is found modify the search");
	    if(getch())
	    mainmenu();
	}
	if(findbook=='t' )
	{
	    printf("\n");
	    ft=fopen("test.dat","wb+");  //temporary file for delete
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
		    if(a.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);
			fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
		    }                              //we want to delete
		}
		fclose(ft);
		fclose(fp);
		remove("Library.dat");
		rename("test.dat","Library.dat"); //copy all item from temporary file to fp except that
		fp=fopen("Library.dat","rb+");    //we want to delete
		printf("The record is sucessfully deleted\n\n");
		mainmenu();

	
	}
    printf("\n");


}
void searchbooks()
{
    system("cl");
    int d;
    printf("*****************************Search Books*********************************");
    printf("\n");printf("\n");
    printf("1. Search By ID");
    printf("\n");
    printf("2. Search By Name");
    printf("\n");
    printf("Enter Your Choice");
    fp=fopen("Library.dat","rb+"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
	  case '1':
	{
	    system("clear");
	    printf("\n");
	    printf("****Search Books By Id****");
	    printf("\n");
	    printf("Enter the book id:");
	    scanf("%d",&d);
	    printf("\n");
	    printf("Searching........");
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(a.id==d)
		{
		    
		    printf("\n");
		    printf("The Book is available");
		    printf("\n");
		    printf("***********************************************************");
		    printf("\n");
		    printf("->ID:%d",a.id);printf("\n");
		    printf("\n");
		    printf("->Name:%s",a.name);printf("\n");
		    printf("\n");
		    printf("->Author:%s ",a.Author);printf("\n");
		    printf("\n");
		    printf("->Qantity:%d ",a.quantity);printf("\n");
		    printf("\n");
		    printf("->Price:Rs.%.2f",a.Price);printf("\n");
		    printf("\n");
		    printf("->Rack No:%d ",a.rackno);printf("\n");
		    printf("\n");
		    printf("***********************************************************");
		    printf("\n");
		    findbook='t';
		}

	    }
	    if(findbook!='t')  //checks whether conditiion enters inside loop or not
	    {
	    printf("***********************************************************");
	    printf("\n");
	    printf("\n");printf("\n");
	    printf("***********************************************************");
	    printf("\n");
            printf("\aNo Record Found");
	    }
	    printf("\n");
	    
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("clear");
	    printf("\n");
	    printf("****Search Books By Name****");
	    printf("\n");
	    printf("Enter Book Name:");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
		{
		    printf("\n");
		    printf("The Book is available");
		    printf("\n");
		     printf("***********************************************************");
		    printf("\n");
		    printf("->ID:%d",a.id);printf("\n");
		    printf("\n");
		    printf("->Name:%s",a.name);printf("\n");
		    printf("\n");
		    printf("->Author:%s ",a.Author);printf("\n");
		    printf("\n");
		    printf("->Qantity:%d ",a.quantity);printf("\n");
		    printf("\n");
		    printf("->Price:Rs.%.2f",a.Price);printf("\n");
		    printf("\n");
		    printf("->Rack No:%d ",a.rackno);printf("\n");
		    printf("\n");
		    printf("************************************************************");
		    printf("\n");
		    d++;
		}

	    }
	    if(d==0)
	    {
	    printf("************************************************************");
	    printf("\n");printf("\n");printf("\n");
	    printf("************************************************************");
	    printf("\n");printf("\aNo Record Found");
	    }
	    
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
    int t;

    system("clear");
    printf("********************************ISSUE SECTION**************************");
    printf("\n");
    printf("->1. Issue a Book");
    printf("\n");
    printf("->2. View Issued Book");
    printf("\n");
    printf("->3. Search Issued Book");
    printf("\n");
    printf("->4. Remove Issued Book");
    printf("\n");
    printf("Enter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{
		system("clear");
		int c=0;
		char another='y';
		while(another=='y')
		{
			system("clear");
			printf("\n");
			printf("***Issue Book section***");
			printf("\n");
			printf("Enter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Library.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0) //issues those which are present in library
			{
			     printf("\n");
			     printf("The book record is available");
			     printf("\n");
			     printf("There are %d unissued books in library ",a.quantity);
			     printf("\n");
			     printf("The name of book is %s",a.name);
			     printf("\n");
			     printf("Enter student name:");
			     scanf("%s",a.stname);
			   
			     printf("\n");
			     printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
			     printf("\n");
			     printf("The BOOK of ID %d is issued",a.id);
			     a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
			     a.duedate.mm=a.issued.mm;
			     a.duedate.yy=a.issued.yy;
			     if(a.duedate.dd>30)
			     {
				 a.duedate.mm+=a.duedate.dd/30;
				 a.duedate.dd-=30;

			     }
			     if(a.duedate.mm>12)
			     {
				a.duedate.yy+=a.duedate.mm/12;
				a.duedate.mm-=12;

			     }
			     printf("\n");
			     printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			     fseek(fs,sizeof(a),SEEK_END);
			     fwrite(&a,sizeof(a),1,fs);
			     fclose(fs);
			     c=1;
			}
			if(c==0)
			{
			printf("\n");
			printf("No record found");
			}
			printf("\n");
			
			fflush(stdin);			
			fclose(fp);
			mainmenu();
		}

		break;
	}
	case '2':  //show issued book list
	{
		system("clear");
		int j=4;
		printf("*******************************Issued book list*******************************\n");
		printf("\n");
		
	       fs=fopen("Issue.dat","rb");
		while(fread(&a,sizeof(a),1,fs)==1)
		{

			printf("\t\t");
			printf("%s",a.stname);
			printf("\t\t");
			printf("%s",a.cat);
			printf("\t\t");
			printf("%d",a.id);
			printf("\t\t");
			printf("%s",a.name);
			printf("\t\t");
			printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
			printf("\t\t");
			printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			
			printf("\n");

			j++;

		}
		fclose(fs);
		printf("\n");
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		system("clear");
		printf("\n");
		printf("Enter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==p)
				{
					issuerecord();
					printf("\n");
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				printf("\n");
				printf("No Record Found");
			}
			printf("\n");
			mainmenu();
	}
	break;
	case '4':  //remove issued books from list
	{
		system("clear");
		int b;
		FILE *fg;  //declaration of temporary file for delete
		char another='y';
		while(another=='y')
		{
			printf("\n");
			printf("Enter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.dat","rb+");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					printf("\n");
					
					
						fg=fopen("record.dat","wb+");
						rewind(fs);
						while(fread(&a,sizeof(a),1,fs)==1)
						{
							if(a.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&a,sizeof(a),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						
						printf("\nThe issued book is removed from list");
						mainmenu();

				       

				}
				if(findbook!='t')
				{
					printf("\n");
					printf("No Record Found");
				}
			}
			printf("\n");
			mainmenu();
		}
	}
	default:
	printf("\n");
	printf("\aWrong Entry!!");
    getch();
	issuebooks();
	break;
      }
      printf("\n");
      returnfunc();
}}

void viewbooks(void)  //show the list of book persists in library
{
    int i=0,j;
    system("clear");
    printf("\n");
    printf("*********************************Book List*****************************");
    printf("\n");
    
    fp=fopen("Library.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
	printf("\n");
	printf("Category : %s",a.cat);
	printf("\t\t");
	printf("ID : %d",a.id);
	printf("\t\t");
	printf("Name : %s",a.name);
	printf("\t\t");
	printf("Author : %s",a.Author);
	printf("\t\t");
	printf("Quantity : %d",a.quantity);
	printf("\t\t");
	printf("Price : %.2f",a.Price);
	printf("\t\t");
	printf("Rack number : %d",a.rackno);
	printf("\n\n");
	j++;
	i=i+a.quantity;
      }
      printf("\n");
      printf("Total Books =%d",i);
      fclose(fp);
      printf("\n");
      returnfunc();
}
void editbooks(void)  //edit information about book
{
	system("clear");
	int c=0;
	int d,e;
	printf("\n");
	printf("****Edit Books Section****");
	char another='y';
	while(another=='y')
	{
		system("clear");
		printf("\n");
		printf("Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("Library.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("\n");
				printf("The book is availble");
				printf("\n");
				printf("The Book ID:%d",a.id);
				printf("\n");
				printf("Enter new name:");scanf("%s",a.name);
				printf("\n");
				printf("Enter new Author:");scanf("%s",a.Author);
				printf("\n");
				printf("Enter new quantity:");scanf("%d",&a.quantity);
				printf("\n");
				printf("Enter new price:");scanf("%f",&a.Price);
				printf("\n");
				printf("Enter new rackno:");scanf("%d",&a.rackno);
				printf("\n");
				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("\n");
				printf("No record found");
			}
		}
		printf("\n");fflush(stdin);
		mainmenu();
		
		
	}
		
}
void returnfunc(void)
{
    {
	printf(" Press any key to return to main menu\n\n");
    }
    a:
    if(getch())
    mainmenu();
    else
    goto a;
}
int getdata()
{
	int t;
	printf("\n");printf("Enter the Information Below\n\n");
	printf("\n");printf("****************************************************\n\n");
	printf("Category:");
	printf("\n");
	printf("%s",catagories[s-1]);
	printf("\n");
	printf("Book ID:\t");
	printf("\n");
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		printf("\n");
		printf("\aThe book id already exists\a\n");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	printf("\n");
	printf("Book Name:\t\t");
	scanf("%s",a.name);
	printf("\n");
	printf("Author:\t\t");
	scanf("%s",a.Author);
	printf("\n");
	printf("Quantity:\t\t");
	scanf("%d",&a.quantity);
	printf("\n");
	printf("Price:\t\t");
	scanf("%f",&a.Price);
	printf("\n");
	printf("Rack No:\t\t");
	scanf("%d",&a.rackno);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}

void Password(void)
{
   
   system("clear");
   char d[25]="Password Protected";
   char ch,pass[10];
   int i=0,j;
  
   printf("\n");
   printf("\n");printf("\n");
   printf("Enter Password:");

   while(ch!=10)
   {
	ch=getch();

	if(ch!=10 && ch!=8){
	printf("*");
	pass[i] = ch;
	i++;
	}
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {

	printf("\n");
	printf("Password match\n");
	
	printf("Press any key to countinue.....\n\n\n");
	getch();
	mainmenu();
   }
   else
   {
	 printf("\n");
	 printf("\aWarning!! Incorrect Password");
	 getch();
	 Password();
   }
}

void issuerecord()  //display issued book's information
{
		 system("clear");
		 printf("\n");
		 printf("The Book has taken by Mr. %s",a.stname);
		 printf("\n");
		 printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
		 printf("\n");
		 printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}



//End of program

