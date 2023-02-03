//change colour ,background ,size
//
//
//      ---------------convert char a=12345 to int a=12345-------------------------
			   //REQUIRED HEADER FILES

#include<fstream.h>        //cin,cout,
#include<process.h>        //exit(0)
#include<string.h>         //strcmp()
#include<stdio.h>          //gets(),remove(),rename()
#include<conio.h>          //clrscr(),getch(),gotoxy(),cprintf()
#include<dos.h>            //delay()

			   //CLASS STUDENT
class student
 {
  int roll,mark;
  char name[30];
  public:
   void getdata()                                //ch=getch();
    {
     cout<<"\nRoll:";cin>>roll;
     cout<<"Name:";gets(name);
     cout<<"Mark:";cin>>mark;
    }
   int getroll(){return roll;}
  void putdata()
    {
     cout<<"\nRoll:"<<roll<<"\nName:"<<name<<"\nMark:"<<mark;
    }
 }S,N;

void time(int i=0)
 { char *mer;
   do
    { struct dostime_t t;
      _dos_gettime(&t);
      gotoxy (68,48);
      textcolor(3);
      if (t.hour<12)
       strcpy(mer,"AM");
      else
       strcpy(mer,"PM");
      if (t.hour>12)
       t.hour-=12 ;
      cprintf ("%d:%02d:%02d %s",t.hour,t.minute,t.second,mer) ;
    }while((!i)&&(!kbhit));
  if(!i)
   getch();
  gotoxy(0,0);
  textcolor(7);
 }

			       //FUNCTION DOT
void dot(int n,char ch='n')
 { for(int i=0;i<n;i++)
    { cout<<'.';
      if(ch=='y')
       delay(500);
    }
   if(ch!='y')
    for(;i<10;i++)
     cout<<' ';
 }

			       //FUNCTION LOADING
void loading()                 //give colour to progress bar
 {int k,i,n;
  char p[8]={219,177,201,187,186,200,188,205};
  for(n=0;n<=100;n++)
   {for(i=0;i<2;i++)
     {textcolor((i+3));
      cout<<"\n\t";cprintf("%c",p[2]);
      for(k=0;k<50;k++)
       cprintf("%c",p[7]);
      cprintf("%c",p[3]);cout<<"\n\t";cprintf("%c",p[4]);
      for(k=(50-n/2);k<50;k++)
       {textcolor(2);cprintf("%c",p[i]);textcolor(i+3);}
      for(k=n/2;k<50;k++)
       cout<<' ';
      cprintf("%c",p[4]);cout<<"\n\t";cprintf("%c",p[5]);
      for(k=0;k<50;k++)
       cprintf("%c",p[7]);
      cprintf("%c",p[6]);cout<<"\n";
     }time(1);
    delay(150);
    if(n==100)break;
    time(1);
    clrscr();
    cout<<"\n\n\n\n\t\tWelcome user\n\t\t";
    for(k=0;k<12;k++)cout<<p[7];
    cout<<"\n\n\n\n\n\t loading,please wait";
    dot(n%10);
    cout<<n+1<<"%\n";
   }
  textcolor(7);
 }			   //FUNCTION PASSWORD
char * pass(int n)
 {
   char s[63]; //65-7/--100
   for(int i=n;i>0;i--)
    s[i-1]=(48+i);
   s[n]='\0';
   return s;
 }

void pass()                //FUNCTION PASSWORD
 {
   clrscr();
   int f=0;
   char p[10],username[10];
   while(f<6)
   { clrscr();
     textbackground(0);
     gotoxy(28,18);
     textcolor(2);
     cprintf("Username :");
     gets(username);
     gotoxy(28,21);
     textcolor(5);
     cprintf("Password :");
     gets(p);
     textcolor(7);
     if((strcmp(p,pass(strlen(username))))||(strcmp(username,"aamir")))
      {clrscr();
       cout<<"\n\n\n\t\tYou entered a wrong username or password!!!\a";
       f++;
       if(f>=5)
	{ clrscr();
	  cout<<"\n\n\n\n\n\n   \tYou have entered incorrect username or password '5' times."
	      <<"\n\n\n  \t\tNow the program will be terminated!";
	  getch();
	  exit(0);
	}
      }
    else
     break;
   }
 }

			   //FUNCTION MESSAGE
void message()
 {
   cout<<"\t\t\tWelcome to database\n"
       <<"\n\t1.Create new records"
       <<"\n\t2.Sort the records"
       <<"\n\t3.Modify a record"
       <<"\n\t4.Insert a new record"
       <<"\n\t5.View a record"
       <<"\n\t6.Delete a record"
       <<"\n\t7.Print all the records"
       <<"\n\t8.Save records in text file"
       <<"\n\t9.Exit\n\t";
  }

			   //FUNCTION CREATE
void create()
 { clrscr();
   cout<<"\t\tCreate\n\t\t様様様\n";
   char ch[5];
   cout<<"Do you want to want to delete existing file ?\n";
   cin>>ch;
   if(ch[0]=='y'||ch[0]=='Y')
    remove("marks.dat");
   ofstream A("marks.dat",ios::out|ios::app|ios::binary);
   cout<<"Enter details";
   do
    {
      S.getdata();
      A.write((char *)&S,sizeof(S));
      cout<<"Want to enter more....?";
      cin>>ch;
    }while(ch[0]=='y'||ch[0]=='Y');
   A.close();
 }

void modify()
 {
  clrscr();
  cout<<"\t\tModify\n\t\t様様様\n";
  int roll,f=0;
  long pos;
  fstream A("marks.dat",ios::in|ios::out|ios::binary);
  cout<<"Enter the roll no\n";
  cin>>roll;
  while(A)
   { pos=A.tellg();
     A.read((char *)&S,sizeof(S));
     if(S.getroll()==roll)
      { f=1;
	cout<<"Enter new data\n";
	S.getdata();
	A.seekg(pos);
	A.write((char *)&S,sizeof(S));
	break;
      }
   }
  A.close();
  if(f==0)
    cout<<"Roll no does not exist";
 }

			   //FUNCTION INSERT
void insert()
 {  clrscr();
    cout<<"\t\tInsert\n\t\t様様様\n";
    char ch;int f=0;
    ofstream A("temp.dat",ios::out|ios::binary);
    ifstream B("marks.dat",ios::in|ios::binary);
    cout<<"Enter new record\n";
    N.getdata();
    while(B)
     {
       B.read((char *)&S,sizeof(S));
       if(N.getroll()<=S.getroll())
	 {
	   A.write((char *)&N,sizeof(N));
	   A.write((char *)&S,sizeof(S));
	   f=1;
	   break;
	 }
       else
	{
	  if(!B)break;
	  A.write((char *)&S,sizeof(S));
	}
     }
    if(f==0)
     A.write((char *)&N,sizeof(N));
    while(B)
     { B.get(ch);
       if(!B)break;
       A.put(ch);
     }
       A.close();
       B.close();
       remove("marks.dat");
       rename("temp.dat","marks.dat");
 }

			   //FUNCTION DELETE
void del()
 { clrscr();
   cout<<"\t\tDeleting\n\t\t様様様様\n";
   char ch[5];int roll,f=0;
   ofstream A("temp.dat",ios::out|ios::binary);
   ifstream B("marks.dat",ios::in|ios::binary);
   cout<<"Enter roll\n";
   cin>>roll;
   clrscr();
   while(B)
    { B.read((char *)&S,sizeof(S));
      if(!B)break;
	if(roll==S.getroll())
	  { f=1;
	    cout<<"Want to delete the following record:*\n";
	    S.putdata();
	    cout<<endl;
	    cin>>ch;
	    if(!(ch[0]=='y'||ch[0]=='Y'))
	      A.write((char *)&S,sizeof(S));
	    else
	     {
	      cout<<"Deleting the record";
	      for(int i=0;i<20;i++){delay(50);cout<<".";}
	     }
	  }
	else
	 {
	  if(!B)break;
	   A.write((char *)&S,sizeof(S));
	 }
    }
   A.close();
   B.close();
   if(f==1)
    {
      remove("marks.dat");
      rename("temp.dat","marks.dat");
    }
   else if(f==0)
    {remove("temp.dat");cout<<"Roll no does not exit\n";}
 }

			   //FUNCTION PRINT
void print()
 { clrscr();
   cout<<"\t\tPrinting\n\t\t様様様様\n";
   ifstream A("marks.dat",ios::in|ios::binary);
   while(A)
    { A.read((char *)&S,sizeof(S));
      if(!A)break;
      S.putdata();
      if(A)cout<<"\n様様様様様様様様様様";
    }A.close();
 }

void save()                       //FUNCTION RENAME
 {

 clrscr();
  char oldname[80], newname[80];

/* prompt for file to rename and new name */
printf("File to rename: ");
gets(oldname);
printf("New name: ");
gets(newname);

/* Rename the file */
if (rename(oldname, newname) == 0)
   printf("Renamed %s to %s.\n", oldname, newname);
else
   perror("rename");
 }


int main()
 {
  clrscr();
  loading();
 // time();
  pass();
  char ch[5];
  int c,f;
  do
   {  clrscr();
      message();
      cin>>c;
      f=0;
      switch(c)
       {
	 case 1:create();break;
	 case 2:cout<<"In progress";for(int i=0;i<10;i++){delay(50);cout<<".";}break;
	 case 3:modify();break;
	 case 4:insert();break;
	 case 5: //View cout<<"To be continued....\n"; break; //cout<<"To view the record,enter the ROLL NO:";//cin>>roll;
	 case 6:del();break;
	 case 7:print();break;
	 case 8://save()
	 case 9:return 0;
	 default:
	   cout<<"You entered an invalid option.\nPlease try again";
	   f=2;
	   dot(10,'y');
       }
   if(f!=2)
    { cout<<"\nDo you want to continue ?";
      cin>>ch;
    }
   }while(ch[0]=='y'||ch[0]=='Y'||f==2);
  getch();
  clrscr();
  return 0;
 }