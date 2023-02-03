/////////////////problem for read()

//all other functions for initial
///////5 times enter in modify
///////showpoint,justify

#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<ctype.h>          //////////////////Want to exit screen
#include<dos.h>              ///////long accno
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<iomanip.h>
////////////////////////////////////unsigned long int
int lastaccno(); /////////////////////do this

struct ddmmyy
 { char dd,mm;
   int yy;       ////////////////[10] for check error
 };

struct date date;

void clear(int y)
 { gotoxy(1,y);
   for(int i=0;i<79;i++)cout<<" ";
 }

class initial
 { int accno;
   char name[30];
   char address[50];        ///////  char verify_name[25];//should be last priority
   float balance;
  public:
   void read(int a=1);
   void print(int i[]);
   int get_accno(){return accno;}
   float get_balance(){return balance;}
 }I;

void initial::read(int a)
    { int f=0;
      if(a==1) accno=lastaccno()+1;
      while(!f)
       { textcolor(0);
	 gotoxy(1,1);cout<<"Name:";gets(name);textcolor(RED);
	 if(strlen(name)>=30){gotoxy(5,2);cprintf("Name should not be greater than 30 characters");}
	 else if(!strlen(name)){gotoxy(5,2);cprintf("Name should not be vaccant");delay(1000);clear(2);}
	 else f=1;
       }f=0;
      while(!f)
       { textcolor(0);
	 gotoxy(1,2);cprintf("Address:");gets(address);textcolor(RED);
	 if(strlen(name)>=30){gotoxy(5,2);cprintf("Name should not be greater than 30 characters");}
	 else if(!strlen(name)){gotoxy(5,2);cprintf("Name should not be vaccant");delay(1000);clear(2);}
	 else f=1;textcolor(0);
       }f=0;

      if(a==1){ cout<<"Initial Deposit:";cin>>balance; }
    }

void initial::print(int i[])
 { for(int j=1;j<5;j++)
    { gotoxy(i[j],i[0]);
      switch(j)
       { case 1:cout<<' '<<accno;break;
	 case 2:cout<<name;break;
	 case 3:cout<<address;break;
	 case 4:
	  cout<<setw(13)<<setprecision(2)
	      <<setiosflags(ios::right)
	      <<setiosflags(ios::showpoint)
	      <<setiosflags(ios::fixed)
	      <<balance;break;
       }
    }
 }

class account
 { int accno;
   ddmmyy dmy;
   char type[10],tran[10];        ///////////////read type and tran using t=getch()
   float amount,balance;      ///amount ----deposit or withdrawl
  public:
    void initilize()
     { accno=I.get_accno();
       getdate(&date);
       gets(type);			 ////int get_accno(){return accno;}
			// ddmmyy get_date(){return d;}
			// char * get_type(){return type;}
     }			  // char get_tran(){return tran[0];}
			// float get_amount(){return amount;}
			   // float get_balance(){return balance;}
 }A;

int lastaccno()
 { int i=0;
   ifstream file("initial.dat",ios::in|ios::binary);
   while(file)
    { file.read((char *)&I,sizeof(I));
      if(!file)break;
      i++;
    }
   if(i==0)return i;
   return I.get_accno();
 }

void dot(int n,char ch='n')
 { for(int i=0;i<n;i++)
    { cout<<'.';
      if(ch=='y')    delay(50);
    }
   if(ch!='y')    for(;i<10;i++)cout<<' ';
 }


void time(int i=0)
 { char *mer;
   do { struct dostime_t t;
       _dos_gettime(&t);
       gotoxy(68,24);
       textcolor(3);
       if(t.hour<12)  	strcpy(mer,"AM");
	else           	strcpy(mer,"PM");
       if(t.hour>12) 	t.hour-=12 ;
       cprintf ("%d:%02d:%02d %s",t.hour,t.minute,t.second,mer) ;
      }while((!i)&&(!kbhit));
   if(!i)  getch();
   gotoxy(0,0);textcolor(7);
 }

void loading()
 {int k,i,n;
  char p[7]={219,201,187,186,200,188,205};
  _setcursortype(_NOCURSOR);
  cout<<"\n\n\n\n\t\tWelcome user\n\t\t";
  for(k=0;k<12;k++)cout<<p[6];
  cout<<"\n\n\n\n\n\t loading,please wait";
  dot(0);
  textcolor(3);
  cout<<"\n\t"; cprintf("%c",p[1]);
  for(k=0;k<50;k++)
  cprintf("%c",p[6]); cprintf("%c",p[2]);
  cout<<"\n\t"; cprintf("%c",p[3]);
  for(k=0;k<50;k++)cout<<' ';
  cprintf("%c",p[3]); cout<<"\n\t"; cprintf("%c",p[4]);
  for(k=0;k<50;k++)cprintf("%c",p[6]);
  cprintf("%c",p[5]); cout<<"\n";
  for(n=1;n<=100;n++)
   { gotoxy(29,11);
     dot(n%10);
     cout<<n<<"%";
     textcolor(2);
     if(n%2==0)
      {gotoxy(9+n/2,13);
       cprintf("%c",p[0]);
      }
     time(1);delay(150);
     if(n==100)break;
     time(1);
   }textcolor(7);
  _setcursortype(_NORMALCURSOR);
 }

char * pass(int n)
 { char s[65]; //65-7/--100
   for(int i=n;i>0;i--)
    s[i-1]=(48+i);
   s[n]='\0';
   return s;
 }

char * a[1]={"aamir"};

void pass()
 { clrscr();
   int f=0;
   char p[10],username[10];
   while(f<6)
    {clrscr();                  //textbackground(0);
     gotoxy(28,12);
     textcolor(2);
     cprintf("Username :");
     gets(username);
     gotoxy(28,15);
     textcolor(5);
     cprintf("Password :");
     gets(p);textcolor(7);
     if((strcmp(p,pass(strlen(username))))||(strcmp(username,a[0])))
      {clrscr();
       cout<<"\n\n\n\t\tYou entered a wrong username or password!!!\a";
       f++;
       if(f>=5)
	{ clrscr();
	  gotoxy(12,10);
	  cout<<"You have entered incorrect username or password '5' times.";
	  gotoxy(20,15);
	  cout<<"Now the program will be terminated!";
	  getch();exit(0);
	}
      }
    else
     break;
   }
 }

void graphics()
 { int gdriver=DETECT ,gmode,errorcode;
   initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
   errorcode=graphresult();
   if(errorcode!=grOk)
    {printf("Graphics error: %s\n", grapherrormsg(errorcode));
     printf("Press any key to halt.");
     getch();exit(0);
    }
 }

void message()
 {  clrscr();
    graphics();
    char *text[10]={"This project can keep record of daily banking transactions.\n",
    "This program is capable of holding any no. of acccount",
    " - In first option you can open New Account.",
    " - In second option you can see the list of all the Accounts.",
    " - In third option you can see all the transaction of Individual Account.",
    " - Through fourth option you can do Banking Transactions (Deposit/Withdraw).",
    " - In fifth option you can take Month Wise Individual Account Report.",
    " - In sixth option you can modify or delete any Account.",
    " Note:- Opening amount should not less than         .",
    " - And last option is Quit (Exit to Windows)."};
    setbkcolor(8);   //1,8
    settextstyle(4,HORIZ_DIR,5); //1,4,8,7,10
    setcolor(11);     //11,2
    outtextxy(50,45,"Welcome To Banking Project");
    line(60,100,560,100);
    settextstyle(2,HORIZ_DIR,5);
    setcolor(22);
    for(int i=0,j=120 ; j<=390; i++,j=j+30)
     { delay(500);outtextxy(50,j,text[i]);
       if(i==8)
	{ setcolor(2);outtextxy(390,360,"Rs. 500");
	  line(390,380,440,380);setcolor(22);
	}
     }setcolor(2);
    settextstyle(7,HORIZ_DIR,3);
    delay(1500);
    outtextxy(50,420,"Press any key to continue . . .");
    getch();
    closegraph();
 }


void box()
 { clrscr();int p=35,q=25,r=2,s=5,t=75;
   textcolor(3); //6
   for(int x=0;x<2;x++,r+=4,s+=9,p-=9,q-=4,t-=9)
    {gotoxy(s-1,r);
     for(int i=0;i<p;i++)cprintf(" *");
     gotoxy(s-1,q);
     for(i=0;i<p;i++)cprintf(" *");
     for(i=r;i<=q;i++)
      {gotoxy(s,i);
       cprintf("*");
       gotoxy(t,i);
       cprintf("*");
      }
    }
 }

void line(int x,int y,int size)
 { char c=205;gotoxy(x,y);
  for(int i=0;i<size;i++) cprintf("%c",c);
 }

void vline(int x,int y,int size)
 { char c=186;
  for(int i=0;i<size;i++)
   { gotoxy(x,y+i); cprintf("%c",c);
   }
 }

void open()
 {  clrscr();
    I.read();
    ofstream file("initial.dat",ios::out|ios::app|ios::binary);
    file.write((char *)&I,sizeof(I));
    cout<<"\nSaving";dot(20,'y');
    file.close();
    getch();
 }

void box2(int *i,int n)
 {  line(2,(*i)++,78);
    line(2,4,78);line(2,6,78);
    for(int j=1;j<5;j++)
      vline(i[j]-2,i[1]+1,n);
    vline(80,i[1]+1,n);
    gotoxy(2,4);cout<<char(201);
    gotoxy(2,6);cout<<char(204);
    gotoxy(2,*i-1);cout<<char(200);
    for(int l=2;l<5;l++)
     {gotoxy(i[l]-2,4);cout<<char(203);
      gotoxy(i[l]-2,6);cout<<char(206);
      gotoxy(i[l]-2,*i-1);cout<<char(202);
     }
    gotoxy(80,4);cout<<char(187);
    gotoxy(80,6);cout<<char(185);
    gotoxy(80,*i-1);cout<<char(188);

 }

void list()
 { clrscr();long double balance=0;
   int n=3,i[5]={7,4,12,37,66};
   ifstream file("initial.dat",ios::in|ios::binary);
   if(!file){cout<<"File not found!!!";getch();return;}
   gotoxy(32,2);cout<<"Account List";line(32,3,12);
   for(int j=1;j<5;j++)
    { gotoxy(i[j],5);
      switch(j)
       { case 1:cout<<"Accno#";break;
	 case 2:cout<<"Name";break;
	 case 3:cout<<"Address";break;
	 case 4:gotoxy(i[j]+3,5);cout<<"Balance";break;
       }
    }
   while(file)
    {  file.read((char *)&I,sizeof(I));
       if(!file)break;n++;
       balance+=I.get_balance();
       I.print(i);cout<<endl;
       (*i)++;
    }(*i)++;
    box2(i,n);
    gotoxy(i[2]-5,*i);cout<<"Total Balance in Bank :  ";dot(28);
    cout<<"   Rs.";gotoxy(i[4],*i);cout<<setw(13)<<setprecision(2);
    cout<<setiosflags(ios::right)
	<<setiosflags(ios::showpoint)
	<<setiosflags(ios::fixed)
	<<balance;
    file.close();
    getch();
 }

void modify()
 { clrscr();
   cout<<"Modify";
   int accno,f=0;
   long pos;
   fstream file("initial.dat",ios::in|ios::out|ios::binary);
   cout<<"Enter the account no: ";
   cin>>accno;
   while(file)
    { pos=file.tellg();
      file.read((char *)&I,sizeof(I));
      if(I.get_accno()==accno)
       { f=1;
	 cout<<"Enter new data\n";     ////////////other
	 I.read(0);
	 file.seekg(pos);
	 file.write((char *)&I,sizeof(I));
	 cout<<"\nSaving";dot(20,'y');
	 break;
       }
    }
  file.close();
  if(f==0)
    cout<<"Account no does not exist";
 getch();
 }

void del()
 { clrscr();
   cout<<"\t\tDeleting\n\t\t様様様様\n";
   int accno,f=0,i=1; char d='1';
   ofstream file1("temp.dat",ios::out|ios::binary);
   ifstream file2("initial.dat",ios::in|ios::binary);
   cout<<"Enter account no: ";
   cin>>accno;
   while(file2)
    { file2.read((char *)&I,sizeof(I));
      if(!file2)break;
      if(accno==I.get_accno())
       {f=1;
	while(d!=13)
	 { clrscr();
	   cout<<"Want to delete the following acount:*\n";
////////////////
	       /////////////////////

	   ////I.print(); /////////////////////////////////////////////
	   textcolor(13);gotoxy(30,10);if(i==1)textbackground(6);cprintf("Y");textcolor(7);cprintf("es");if(i==1)textbackground(0);
	   textcolor(13);gotoxy(40,10);if(i==2)textbackground(12);cprintf("N");textcolor(7);cprintf("o");if(i==2)textbackground(0);
	   d=getch();
	   if(d==75) i--;      if(i==0) i=2;
	   if(d==77) i++;      if(i==3) i=1;
	   switch(tolower(d)) { case 'y':i=1;break; case 'n':i=2;break; }
	 }
	 if(i==1)
	   { cout<<"\nDeleting the account";
	     dot(20,'y');
	   }
	 else
	   file1.write((char *)&I,sizeof(I));
       }
      else
       { if(!file2)break;
	 file1.write((char *)&I,sizeof(I));
       }
    }
   file1.close();
   file2.close();
   if(f==1)
    { remove("initial.dat");
      rename("temp.dat","initial.dat");
    }
   else if(f==0)
    { remove("temp.dat");
      cout<<"Account no does not exist";getch();
    }
 }

void menu_names(int i,char a[],char *b[])
 { for(int l=1;l<=strlen(a);l++)
    { textcolor(13);
     gotoxy(30,9+l);if(i==l)textbackground(14);cprintf("%c",a[l-1]);
     textcolor(7);cprintf("%s",b[l-1]);if(i==l)textbackground(0);
    }
 }

void edit()
 { int i=1; char d='1',s=27;
   char *a="MC",*b[2]={"odify Account","lose Account"};
   clrscr(); _setcursortype(_NOCURSOR);
   while(d!=8)
    {while(d!=13)
      { clrscr();box();
       textcolor(10);gotoxy(32,4);cprintf("Edit Account");
       line(32,5,12);
       gotoxy(62,23);textcolor(15);textbackground(9);
       cprintf(" Back = ");gotoxy(70,23);textcolor(10);cprintf("%c ",s);textbackground(0);
       menu_names(i,a,b);d=getch();
       if(d==8)return;
       if(d==72) i--;      if(i==0) i=2;
       if(d==80) i++;      if(i==3) i=1;
       switch(tolower(d)) { case 'm':i=1;break; case 'c':i=2;break; }
      }
     switch(i)
      { case 1:modify();break;
	case 2:del();break;
      }i=1;d='1';        ///////////////while go back
    }
 }

void menu()
 { int i=1; char d='1';
   char *a="NLIDME";
   char *b[6]={"ew Account","ist of Accounts",
	       "nd Account","aily Transaction",
	       "onthly Report","dit Account"};
   while(d!=27)
    { while(d!=13)                                 // 9
       { clrscr();box();
	 gotoxy(62,23);textcolor(15);textbackground(9);cprintf(" Exit = ");
	 gotoxy(70,23);textcolor(10);cprintf("Esc ");textbackground(0);
	 gotoxy(35,4);cprintf("BANKING");
	 line(35,5,7);
	 menu_names(i,a,b);_setcursortype(_NOCURSOR);    /////////////////do _NORMALCRURSOR
	 d=getch();
	 if(d==27)return;  //////////do you want to exit
	 if(d==72) i--;       //   up72 down80 left75  right77
	 if(i==0) i=6;
	 if(d==80) i++;
	 if(i==7) i=1;
	 //clear(8+i);
	 switch(tolower(d))
	  { case 'n':i=1;break; case 'l':i=2;break; case 'i':i=3;break;
	    case 'd':i=4;break; case 'm':i=5;break; case 'e':i=6;break;
	  }
       }
      switch(i)
       { case 1:open();break;          //open();getch(); break;    ////////////may be getch() in open()
	 case 2:list();break;
	 case 3: //ind();break;
	 case 4://daily();break;
	 case 5://monthly();break;
	 case 6:edit();break; /////////    here check password
       }i=1;d='1';
    }
 }

void main()
 {     // _setcursortype(_NOCURSOR); // _NORMALCURSOR _SOLIDCURSOR   ////////////////////////////////
  // message();
  //  loading();
  //  pass();
    menu();
    clrscr();
       ////////////////////  credit();

 }



/////////////////////////////////end//////////////////////////