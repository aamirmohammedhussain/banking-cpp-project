#include <conio.h>     // For getch(),gotoxy(),clreol()
#include <ctype.h>     // For isdigit(),tolower(),isalpha()
#include <dos.h>       // For getdate(),delay(),gettime()
#include <fstream.h>   // For file related operations
#include <graphics.h>  // For outtextxy(),line()
#include <iomanip.h>   // For setw(),steprecision()
#include <process.h>   // For exit(0)
#include <stdio.h>     // For remove(),rename(),printf()
#include <stdlib.h>    // For rand()
#include <string.h>    // For strlen(),strcpy(),strcmp()

long lastaccno();
void box(int x = 0, int i = 3);
char *a[1] = {"aamir"};
void dot(int n, char ch = 'n');

int integer(long &a, int x, int y, int b = 1) {
  char ch = 'a';
  int i = 0;
  while (ch != 13) {
    ch = getch();
    if (ch == 8) {
      a = int(a / 10);
      if (i)
        i--;
    }
    if (i >= 5)
      continue;
    if (isdigit(ch)) {
      a = a * 10 + ch - 48;
      i++;
    }
    gotoxy(x, y);
    clreol();
    if (b)
      box(1);
    if (a != 0) {
      gotoxy(x, y);
      cout << a;
    }
  }
  return 0;
}

int floating(double &a, int x, int y, int b = 1) {
  char ch = 'a';
  int i = 0;
  while (ch != 13) {
    ch = getch();
    if (ch == 27)
      return -1;
    if (ch == 8) {
      a = double(a / 10);
      if (i)
        i--;
    }
    if (i >= 11)
      continue;
    if (isdigit(ch)) {
      a = a * 10 + ch - 48;
      i++;
    }
    gotoxy(x, y);
    clreol();
    if (b)
      box(1);
    if (a != 0) {
      gotoxy(x, y);
      if (a < 1)
        a = 0;
      cout << a;
    }
  }
  return 0;
}

class initial {
  long accno;
  char name[25];
  char address[30];
  double balance;

 public:
  int read(int a = 0);
  void update(double bal) { balance = bal; }
  void print(int i[]);
  long get_accno() { return accno; }
  char *get_name() { return name; }
  char *get_address() { return address; }
  double get_balance() { return balance; }
} I;

int initial::read(int a) {
  int f = 0, i = 0;
  char ch = 'a';
  struct date date;
  getdate(&date);
  gotoxy(60, 23);
  textcolor(2);
  cprintf(" Cancel = ");
  gotoxy(70, 23);
  textcolor(BROWN);
  cprintf("Esc ");
  textcolor(7);
  if (a == 0)
    accno = lastaccno() + 1;
  gotoxy(10, 7);
  cprintf("Date:%02d/%02d/%02d", date.da_day, date.da_mon, date.da_year);
  gotoxy(10, 9);
  cout << "Account No:" << accno;
  if (a)
    i = strlen(name);
  name[i] = '\0';
  while (!f) {
    box(1);
    gotoxy(10, 11);
    cout << "Name:" << name;
    textcolor(7 + BLINK);
    if (i)
      cprintf("%c", 27);
    textcolor(7);
    while (ch != 13) {
      ch = getch();
      if (ch == 27)
        return 0;
      if (ch == 8)
        if (i)
          name[--i] = '\0';
      if (i > 23)
        continue;
      if (isalpha(ch) || ch == ' ' && ch != 13) {
        name[i] = ch;
        name[++i] = '\0';
      }
      gotoxy(15, 11);
      clreol();
      cout << name;
      textcolor(7 + BLINK);
      if (i)
        cprintf("%c", 27);
      textcolor(7);
      box(1);
    }
    gotoxy(15, 11);
    clreol();
    cout << name;
    box(1);
    textcolor(RED);
    if (strlen(name) > 22) {
      gotoxy(15, 12);
      cprintf("Name should not be greater than 22 characters");
      delay(1000);
    } else if (!strlen(name)) {
      gotoxy(15, 12);
      cprintf("Entry vaccant");
      delay(1000);
    } else
      f = 1;
    textcolor(7);
    if (!f)
      for (int i = 11; i <= 12; i++) {
        gotoxy(10, i);
        clreol();
      }
    ch = 'a';
  }
  f = i = 0;
  ch = 'a';
  if (a)
    i = strlen(address);
  address[i] = '\0';
  while (!f) {
    box(1);
    gotoxy(10, 13);
    cout << "Address:" << address;
    textcolor(7 + BLINK);
    if (i)
      cprintf("%c", 27);
    textcolor(7);
    while (ch != 13) {
      ch = getch();
      if (ch == 13)
        break;
      if (ch == 27)
        return 0;
      if (ch == 8)
        if (i)
          address[--i] = '\0';
      if (i > 28)
        continue;
      if (isalnum(ch) || isspace(ch) || ispunct(ch)) {
        address[i] = ch;
        address[++i] = '\0';
      }
      gotoxy(18, 13);
      clreol();
      cout << address;
      textcolor(7 + BLINK);
      if (i)
        cprintf("%c", 27);
      textcolor(7);
      box(1);
    }
    gotoxy(18, 13);
    clreol();
    cout << address;
    box(1);
    textcolor(RED);
    if (strlen(address) > 27) {
      gotoxy(15, 14);
      cprintf("Address should not be greater than 27 characters");
      delay(1000);
    } else if (!strlen(address)) {
      gotoxy(15, 14);
      cprintf("Entry vaccant");
      delay(1000);
    } else
      f = 1;
    textcolor(7);
    if (!f)
      for (int i = 13; i <= 14; i++) {
        gotoxy(10, i);
        clreol();
      }
    ch = 'a';
  }
  f = 0;
  ch = 'a';
  while (!f) {
    box(1);
    if (!a) {
      balance = 0;
      gotoxy(10, 15);
      cout << "Initial Deposit:";
      clreol();
      box(1);
      if (floating(balance, 26, 15) == -1)
        return 0;
      textcolor(RED);
      if (balance < 1000) {
        balance = 0;
        gotoxy(15, 16);
        cprintf("Balance should not be less than Rs.1000");
        delay(1000);
      } else if (balance > 1000000000) {
        balance = 0;
        gotoxy(15, 16);
        cprintf("Balance should not be greater than Rs.100 Crores");
        delay(1000);
      } else
        f = 1;
      textcolor(7);
      if (!f) {
        gotoxy(15, 16);
        clreol();
      }
    } else
      f = 1;
  }
  ch = 'a';
  i = 1;
  gotoxy(28, 17);
  cout << "Do you want to save:";
  while (ch != 13) {
    textcolor(13);
    gotoxy(32, 19);
    if (i == 1)
      textbackground(6);
    cprintf("Y");
    textcolor(7);
    cprintf("es");
    if (i == 1)
      textbackground(0);
    textcolor(13);
    gotoxy(42, 19);
    if (i == 2)
      textbackground(12);
    cprintf("N");
    textcolor(7);
    cprintf("o");
    if (i == 2)
      textbackground(0);
    ch = getch();
    if (ch == 75)
      i--;
    if (i == 0)
      i = 2;
    if (ch == 77)
      i++;
    if (i == 3)
      i = 1;
    switch (tolower(ch)) {
      case 'y':
        i = 1;
        break;
      case 'n':
        i = 2;
        break;
    }
  }
  return i;
}

void initial::print(int i[]) {
  for (int j = 1; j < 5; j++) {
    gotoxy(i[j], i[0]);
    switch (j) {
      case 1:
        cout << ' ' << accno << '.';
        break;
      case 2:
        cout << name;
        break;
      case 3:
        cout << address;
        break;
      case 4:
        cout << setw(13) << setprecision(2) << setiosflags(ios::right)
             << setiosflags(ios::showpoint) << setiosflags(ios::fixed)
             << balance;
        break;
    }
  }
}

long lastaccno() {
  long i = 0;
  ifstream file("initial.dat", ios::in | ios::binary);
  while (file) {
    file.read((char *)&I, sizeof(I));
    if (!file)
      break;
    i++;
  }
  if (i == 0)
    return i;
  return I.get_accno();
}

class account {
  long accno;
  struct date d;
  char type[10], tran[10];
  double amount, balance;

 public:
  void print(int i[]);
  long get_accno() { return accno; }
  char get_tran() { return tran[0]; }
  double get_amount() { return amount; }
  int get_month() { return int(d.da_mon); }
  int get_year() { return d.da_year; }
  void initilize() {
    accno = I.get_accno();
    getdate(&d);
    strcpy(type, "INITIAL");
    strcpy(tran, "DEPOSIT");
    balance = amount = I.get_balance();
  }
  void transaction(long &a, struct date &t, char tp[], char tr[], double &amt, double &bal) {
    accno = a;
    d = t;
    strcpy(type, tp);
    strcpy(tran, tr);
    amount = amt;
    balance = bal;
  }
} A, T;

void account::print(int i[]) {
  for (int j = 1; j < 6; j++) {
    gotoxy(i[j], i[0]);
    switch (j) {
      case 1:
        gotoxy(i[j] + 1, i[0]);
        cprintf("%02d/%02d/%02d", d.da_day, d.da_mon, d.da_year);
        break;
      case 2:
        gotoxy(i[j] + 1, i[0]);
        cout << type;
        break;
      case 3:
        if (tran[0] == 'D')
          cout << setw(13) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << amount;
        break;
      case 4:
        if (tran[0] == 'W')
          cout << setw(13) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << amount;
        break;
      case 5:
        cout << setw(15) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << balance;
        break;
    }
  }
}

long double bal_dep_with(int i[], int y, long accno, char ch = 'a', int m = 0, int year = 0) {
  double d = 0, w = 0;
  long double b = 0;
  ifstream file("banking.dat", ios::in | ios::binary);
  while (file) {
    file.read((char *)&A, sizeof(A));
    if (!file)
      break;
    if (m == 0 && A.get_accno() == accno) {
      if (A.get_tran() == 'D')
        d += A.get_amount();
      if (A.get_tran() == 'W')
        w += A.get_amount();
    } else if (A.get_accno() == accno) {
      if (A.get_month() == m && A.get_year() == year)
        if (A.get_tran() == 'D')
          d += A.get_amount();
      if (A.get_tran() == 'W')
        w += A.get_amount();
    }
    b = d - w;
  }
  file.close();
  if (ch == 'r')
    return b;
  for (int j = 3; j < 6; j++) {
    gotoxy(i[j], y);
    switch (j) {
      case 3:
        cout << setw(13) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << d;
        break;
      case 4:
        cout << setw(13) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << w;
        break;
      case 5:
        cout << setw(15) << setprecision(2) << setiosflags(ios::right) << setiosflags(ios::showpoint) << setiosflags(ios::fixed) << b;
        break;
    }
  }
  return 0;
}

void dot(int n, char ch) {
  for (int i = 0; i < n; i++) {
    cout << '.';
    if (ch == 'y')
      delay(50);
  }
  if (ch != 'y')
    for (; i < 10; i++)
      cout << ' ';
}

void time(int i = 0) {
  char *mer;
  do {
    struct date d;
    struct dostime_t t;
    _dos_gettime(&t);
    getdate(&d);
    // if (d.da_year >= 2013 && int(d.da_mon) >= 5 && int(d.da_day) >= 4)
    //    exit(0);
    gotoxy(5, 24);
    textcolor(3);
    if (i == 2)
      printf("%02d/%02d/%02d", int(d.da_day), int(d.da_mon), d.da_year);
    else
      cprintf("%02d/%02d/%02d", int(d.da_day), int(d.da_mon), d.da_year);
    gotoxy(68, 24);
    textcolor(3);
    if (t.hour < 12)
      strcpy(mer, "AM");
    else
      strcpy(mer, "PM");
    if (t.hour > 12)
      t.hour -= 12;
    if (t.hour == 0)
      t.hour = 12;
    if (i == 2)
      printf("%02d:%02d:%02d %s", t.hour, t.minute, t.second, mer);
    else
      cprintf("%02d:%02d:%02d %s", t.hour, t.minute, t.second, mer);
  } while ((!i) && (!kbhit()));
  if (!i)
    getch();
  gotoxy(0, 0);
  textcolor(7);
}

void loading() {
  cleardevice();
  _setcursortype(_NOCURSOR);
  cout << "\n\n\n\n\t\tWelcome user\n\t\t";
  for (int i = 0; i < 12; i++)
    cout << char(205);
  cout << "\n\n\n\n\n\t loading,please wait";
  setcolor(3);
  for (i = 0; i < 4; i++)
    rectangle(75 - i, 195 - i, 485 + i, 225 + i);
  setcolor(2);
  settextstyle(3, HORIZ_DIR, 5);
  for (i = 0; i < 400; i++) {
    for (int j = 0; j < 20; j++)
      line(80, 200 + j, 80 + i, 200 + j);
    delay(28);
    time(2);
    gotoxy(29, 11);
    dot((i / 4) % 10);
    cout << (i / 4) + 1 << '%';
  }
  closegraph();
  textcolor(7);
  _setcursortype(_NORMALCURSOR);
}

char *pass(int n) {
  char s[65];
  for (int i = n; i > 0; i--)
    s[i - 1] = (48 + i);
  s[n] = '\0';
  return s;
}

void pass() {
  clrscr();
  int f = 0, i;
  char ch, p[10] = " ", username[10] = " ";
  while (f < 6) {
    clrscr();
    ch = 'a';
    i = 0;
    textcolor(2);
    gotoxy(28, 12);
    cprintf("Username :");
    textcolor(7);
    while (ch != 13) {
      ch = getch();
      if (ch == 8)
        if (i)
          username[--i] = '\0';
      if (i >= 9)
        continue;
      if (isalpha(ch) || ch == ' ' && ch != 13) {
        username[i] = ch;
        username[++i] = '\0';
      }
      gotoxy(38, 12);
      clreol();
      cout << username;
    }
    ch = 'a';
    i = 0;
    gotoxy(28, 15);
    textcolor(5);
    cprintf("Password :");
    textcolor(7);
    while (ch != 13) {
      gotoxy(38, 15);
      clreol();
      for (int k = 0; k < i; k++)
        cout << '*';
      ch = getch();
      if (ch == 13)
        break;
      if (ch == 8)
        if (i)
          p[--i] = '\0';
      if (i >= 9)
        continue;
      if (isalnum(ch) || isspace(ch) || ispunct(ch)) {
        p[i++] = ch;
        p[i] = '\0';
      }
    }
    if ((strcmp(p, pass(strlen(username)))) || (strcmp(username, a[0]))) {
      clrscr();
      f++;
      cout << "\n\n\n\t\tYou entered a wrong username or password!!!\a";
      if (f >= 5) {
        clrscr();
        gotoxy(12, 10);
        cout << "You have entered incorrect username or password '5' times.";
        gotoxy(20, 15);
        cout << "Now the program will be terminated!";
        getch();
        exit(0);
      }
    } else
      break;
  }
}

void graphics() {
  int gdriver = DETECT, gmode, errorcode;
  initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
  errorcode = graphresult();
  if (errorcode != grOk) {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt.");
    getch();
    exit(0);
  }
}

void message() {
  clrscr();
  graphics();
  setcolor(2);
  settextstyle(1, HORIZ_DIR, 4);
  char *text[10] = {"This project can keep record of daily banking transactions.\n",
                    "This program is capable of holding any no. of account",
                    " * In first option you can open New Account.",
                    " * In second option you can see the List Of All The Accounts.",
                    " * In third option you can see all the transaction of Individual Accounts.",
                    " * Through fourth option you can do Banking Transactions (Deposit/Withdraw).",
                    " * In fifth option you can take Month Wise Individual Account Report.",
                    " * In sixth option you can Modify or Delete any Account.",
                    "Note:- Opening amount should not be less than        .",
                    "Note:- Use arrow keys to navigate."};
  rectangle(2, 2, getmaxx() - 1, getmaxy() - 1);
  setcolor(15);
  outtextxy(85, 45, "Welcome To Banking Project");
  setcolor(1);
  outtextxy(84, 44, "Welcome To Banking Project");
  setcolor(4);
  line(60, 100, 560, 100);
  settextstyle(2, HORIZ_DIR, 5);
  setcolor(22);
  for (int i = 0, j = 120; j <= 420; i++, j = j + 30) {
    delay(500);
    outtextxy(50, j, text[i]);
    if (i == 8) {
      setcolor(2);
      outtextxy(400, 360, "Rs.1000");
      line(400, 380, 450, 380);
      setcolor(22);
    }
  }
  setcolor(3);
  settextstyle(7, HORIZ_DIR, 3);
  delay(1500);
  outtextxy(50, 420, "Press any key to continue . . .");
  getch();
}

void box(int x, int i) {
  int p = 35, q = 25, r = 2, s = 5, t = 75, a, b;
  textcolor(i);
  a = wherex();
  b = wherey();
  for (; x < 2; x++, r += 4, s += 9, p -= 9, q -= 4, t -= 9) {
    gotoxy(s - 1, r);
    for (int i = 0; i < p; i++)
      cprintf(" *");
    gotoxy(s - 1, q);
    for (i = 0; i < p; i++)
      cprintf(" *");
    for (i = r; i <= q; i++) {
      gotoxy(s, i);
      cprintf("*");
      gotoxy(t, i);
      cprintf("*");
    }
  }
  textcolor(7);
  gotoxy(a, b);
}

void line(int x, int y, int size) {
  char c = 205;
  gotoxy(x, y);
  for (int i = 0; i < size; i++)
    cprintf("%c", c);
}

void vline(int x, int y, int size) {
  char c = 186;
  for (int i = 0; i < size; i++) {
    gotoxy(x, y + i);
    cprintf("%c", c);
  }
}

void open() {
  clrscr();
  int i = 1;
  box(1);
  textcolor(5);
  gotoxy(32, 4);
  cprintf("Open New Account");
  textcolor(BROWN);
  line(32, 5, 16);
  textcolor(7);
  i = I.read();
  if (i == 0 || i == 2)
    return;
  A.initilize();
  if (i == 1) {
    ofstream file;
    file.open("initial.dat", ios::out | ios::app | ios::binary);
    file.write((char *)&I, sizeof(I));
    file.close();
    file.open("banking.dat", ios::out | ios::app | ios::binary);
    file.write((char *)&A, sizeof(A));
    file.close();
    gotoxy(28, 21);
    cout << "Saving";
    dot(15, 'y');
    gotoxy(28, 21);
    clreol();
    box(1);
    cout << "Saved";
    dot(2, 'y');
    delay(500);
  }
}

void box2(int *i, int c_no, int n, int x = 4) {
  line(2, x, 78);
  line(2, x + 2, 78);
  line(2, (*i)++, 78);
  for (int j = 1; j <= c_no; j++)
    vline(i[j] - 2, x + 1, n);
  vline(80, x + 1, n);
  gotoxy(2, x);
  cout << char(201);
  gotoxy(2, x + 2);
  cout << char(204);
  gotoxy(2, *i - 1);
  cout << char(200);
  for (int l = 2; l <= c_no; l++) {
    gotoxy(i[l] - 2, x);
    cout << char(203);
    gotoxy(i[l] - 2, x + 2);
    cout << char(206);
    gotoxy(i[l] - 2, *i - 1);
    cout << char(202);
  }
  gotoxy(80, x);
  cout << char(187);
  gotoxy(80, x + 2);
  cout << char(185);
  gotoxy(80, *i - 1);
  cout << char(188);
}

void list() {
  clrscr();
  int n = 3, f = 1, i[5] = {7, 4, 12, 37, 66};
  char ch;
  long double balance = 0;
  ifstream file("initial.dat", ios::in | ios::binary);
  if (!file) {
    cout << "File not found!!!";
    getch();
    return;
  }
abc:
  clrscr();
  time(1);
  gotoxy(32, 2);
  textcolor(5);
  cprintf("Account List");
  textcolor(BROWN);
  line(32, 3, 12);
  textcolor(7);
  gotoxy(25, 10);
  clreol();
  cprintf("loading,please wait.......");
  delay(25);
  gotoxy(25, 10);
  clreol();
  for (int j = 1; j < 5; j++) {
    gotoxy(i[j], 5);
    switch (j) {
      case 1:
        cprintf("Accno#");
        break;
      case 3:
        cprintf("Address");
        break;
      case 2:
        cprintf("Name");
        break;
      case 4:
        gotoxy(i[j] + 3, 5);
        cprintf("Balance");
        break;
    }
  }
  while (file) {
    if (f % 15 != 0) {
      file.read((char *)&I, sizeof(I));
      if (!file)
        break;
      balance += I.get_balance();
      I.print(i);
      cout << endl;
      (*i)++;
      f++;
      n++;
    } else {
      box2(i, 4, n);
      textcolor(13 + BLINK);
      gotoxy(39, 24);
      cprintf("%c%c", 281, 281);
      textcolor(7);
      while (ch != 80) {
        while (!kbhit())
          time(1);
        ch = getch();
      }
      *i = 7;
      f = 1;
      n = 3;
      ch = 'a';
      goto abc;
    }
  }
  (*i)++;
  box2(i, 4, n);
  gotoxy(i[2] - 5, *i);
  file.close();
  cout << "Total Balance in Bank : ";
  dot(28);
  cout << " Rs.";
  gotoxy(i[4], *i);
  clreol();
  cout << setw(13) << setprecision(2) << setiosflags(ios::right)
       << setiosflags(ios::showpoint) << setiosflags(ios::fixed)
       << balance << endl;
  if (f % 14 != 0)
    cout << endl;
  cout << "   Press any key to continue";
  dot(10, 'y');
  time();
}

// solve this thing
// look list()
void ind() {
  clrscr();
  long accno = 0;
  int f = 0, n = 1, i[7] = {10, 4, 19, 32, 48, 64};
  ifstream file;
  file.open("banking.dat", ios::in | ios::binary);
  if (!file) {
    cout << "File not found!!!";
    getch();
    return;
  }
  gotoxy(32, 2);
  textcolor(5);
  cprintf("Individual Account");
  textcolor(BROWN);
  line(32, 3, 18);
  textcolor(7);
  cout << "\n\n Account No:";
  while (!accno)
    integer(accno, 13, 5, 0);
  textcolor(5 + BLINK);
  for (int t = 1; t <= 14; t++) {
    gotoxy(2, 8);
    clreol();
    cprintf("Searching");
    dot(t % 7, 'y');
  }
  textcolor(7);
  gotoxy(2, 8);
  clreol();
  while (file) {
    file.read((char *)&A, sizeof(A));
    if (!file)
      break;
    if (A.get_accno() == accno) {
      A.print(i);
      cout << endl;
      (*i)++;
      n++;
      f = 1;
    }
  }
  file.close();
  if (!f) {
    cout << "Account no does not exist.\n\n Press any key to continue";
    dot(10, 'y');
    getch();
    return;
  }
  file.open("initial.dat", ios::in | ios::binary);
  while (file) {
    file.read((char *)&I, sizeof(I));
    if (!file)
      break;
    if (I.get_accno() == accno) {
      gotoxy(2, 5);
      clreol();
      cout << "Account No:" << I.get_accno();
      gotoxy(20, 5);
      cout << I.get_name();
      gotoxy(20, 6);
      cout << I.get_address();
    }
  }
  file.close();
  gotoxy(1, 8);
  clreol();
  for (int j = 1; j < 6; j++) {
    gotoxy(i[j], 8);
    clreol();
    switch (j) {
      case 1:
        cprintf("    Date");
        break;
      case 2:
        cprintf("Particular");
        break;
      case 3:
        cprintf("   Deposit");
        break;
      case 4:
        cprintf("  Withdrawal");
        break;
      case 5:
        cprintf("    Balance");
        break;
    }
  }
  box2(i, 5, n + 1, 7);
  gotoxy(5, *i);
  cout << "Total :";
  bal_dep_with(i, *i, accno);
  cout << "\n\n   Press any key to continue";
  dot(10, 'n');
  time();
}

void daily() {
  long pos, accno = 0;
  int i = 1, f = 0;
  struct date d;
  char ch, type[10], tran[10];
  double amount = 0, balance = 0;
  char *tn[2] = {"Deposit", "Withdraw"}, *s[2] = {"Yes", "No"},
       *tp[2] = {"Cash", "Cheque"};
  clrscr();
  getdate(&d);
  ifstream file1;
  file1.open("initial.dat", ios::in | ios::binary);
  if (!file1) {
    cout << "File not found!!!";
    getch();
    return;
  }
  gotoxy(32, 2);
  textcolor(5);
  cprintf("Daily Transaction");
  textcolor(BROWN);
  line(32, 3, 17);
  textcolor(7);
  gotoxy(2, 5);
  cprintf("Date:%02d/%02d/%02d", d.da_day, d.da_mon, d.da_year);
  gotoxy(2, 7);
  cout << "Account No:";
  while (!accno)
    integer(accno, 13, 7, 0);
  while (file1) {
    file1.read((char *)&I, sizeof(I));
    if (!file1)
      break;
    if (I.get_accno() == accno) {
      gotoxy(2, 7);
      clreol();
      cout << "Account No:" << I.get_accno();
      gotoxy(20, 7);
      cout << I.get_name();
      gotoxy(20, 8);
      cout << I.get_address();
      f = 1;
      break;
    }
  }
  file1.close();
  if (!f) {
    cout << "\n\n Account no does not exist.\n\n Press any key to continue";
    dot(10, 'y');
    getch();
    return;
  }
  f = 0;
  gotoxy(2, 11);
  cout << "Transaction mode:";
  if (I.get_balance() >= 1000000000)
    i = 2;
  while (ch != 13) {
    for (int k = 1; k < 3; k++) {
      gotoxy(30, 10 + k);
      if (i == k)
        textbackground(6);
      cprintf("%s", strupr(tn[k - 1]));
      if (i == k)
        textbackground(0);
    }
    ch = getch();
    if (ch == 72)
      i--;
    if (ch == 80)
      i++;
    if (i == 0)
      i = 2;
    if (i == 3)
      i = 1;
    if (I.get_balance() >= 1000000000)
      i = 2;
    if (I.get_balance() == 1000)
      i = 1;
  }
  ch = 'a';
  strcpy(tran, strupr(tn[i - 1]));
  for (int a = 1; a < 3; a++) {
    gotoxy(30, 10 + a);
    clreol();
  }
  gotoxy(2, 11);
  cout << "Transaction mode:" << tran;
  gotoxy(2, 14);
  cout << "Transaction type:";
  i = 1;
  while (ch != 13) {
    for (int k = 1; k < 3; k++) {
      gotoxy(30, 13 + k);
      if (i == k)
        textbackground(6);
      cprintf("%s", strupr(tp[k - 1]));
      if (i == k)
        textbackground(0);
    }
    ch = getch();
    if (ch == 72)
      i--;
    if (ch == 80)
      i++;
    if (i == 0)
      i = 2;
    if (i == 3)
      i = 1;
  }
  ch = 'a';
  strcpy(type, strupr(tp[i - 1]));
  i = 1;
  for (a = 1; a < 3; a++) {
    gotoxy(30, 13 + a);
    clreol();
  }
  gotoxy(2, 14);
  cout << "Transaction type:" << type;
  while (!f) {
    gotoxy(2, 17);
    clreol();
    cout << "Amount:";
    amount = 0;
    while (!int(amount))
      floating(amount, 9, 17, 0);
    if (tran[0] == 'D') {
      balance = I.get_balance() + amount;
      if (balance > 1000000000) {
        textcolor(RED);
        gotoxy(20, 18);
        balance = 1000000000 - I.get_balance();
        cprintf("Amount should not be greater than Rs.%g", balance);
        delay(2000);
        gotoxy(20, 18);
        clreol();
        textcolor(7);
      } else
        f = 1;
    } else {
      balance = I.get_balance() - amount;
      if (balance < 1000) {
        textcolor(RED);
        gotoxy(20, 18);
        balance = I.get_balance() - 1000;
        cprintf("Amount should not be greater than Rs.%g", balance);
        delay(2000);
        gotoxy(20, 18);
        clreol();
        textcolor(7);
      } else
        f = 1;
    }
  }
  gotoxy(30, 20);
  cout << "Continue transaction:";
  while (ch != 13) {
    for (int k = 1; k < 3; k++) {
      gotoxy(30 + k * 5, 22);
      if (i == k)
        textbackground(6);
      cprintf("%s", s[k - 1]);
      if (i == k)
        textbackground(0);
    }
    ch = getch();
    if (ch == 75)
      i--;
    if (ch == 77)
      i++;
    if (i == 0)
      i = 2;
    if (i == 3)
      i = 1;
  }
  ch = 'a';
  if (i == 2)
    return;
  i = 0;
  gotoxy(30, 24);
  cout << "Saving Transaction";
  dot(15, 'y');
  gotoxy(30, 24);
  clreol();
  cout << "Transaction Saved";
  dot(2, 'y');
  delay(500);
  A.transaction(accno, d, type, tran, amount, balance);
  fstream file("initial.dat", ios::in | ios::out | ios::binary);
  while (file) {
    pos = file.tellg();
    file.read((char *)&I, sizeof(I));
    if (!file)
      break;
    if (I.get_accno() == accno) {
      I.update(balance);
      file.seekg(pos);
      file.write((char *)&I, sizeof(I));
      break;
    }
  }
  file.close();
  file1.open("banking.dat", ios::in | ios::binary);
  ofstream file2("temp.dat", ios::out | ios::binary);
  while (file1) {
    file1.read((char *)&T, sizeof(T));
    if (accno < T.get_accno()) {
      file2.write((char *)&A, sizeof(A));
      file2.write((char *)&T, sizeof(T));
      i = 1;
      break;
    } else {
      if (!file1)
        break;
      file2.write((char *)&T, sizeof(T));
    }
  }
  if (!i)
    file2.write((char *)&A, sizeof(A));
  while (file1) {
    file1.get(ch);
    if (!file1)
      break;
    file2.put(ch);
  }
  file1.close();
  file2.close();
  remove("banking.dat");
  rename("temp.dat", "banking.dat");
}

void monthly() {
  clrscr();
  long accno = 0;
  int year, f = 0, n = 1, i[7] = {10, 4, 19, 32, 48, 64}, l = 1, p = 0;
  char d = 'a', *y[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  ifstream file;
  file.open("banking.dat", ios::in | ios::binary);
  if (!file) {
    cout << "File not found!!!";
    getch();
    return;
  }
  gotoxy(30, 2);
  textcolor(5);
  cprintf("Monthly Report");
  textcolor(BROWN);
  line(30, 3, 14);
  textcolor(7);
  gotoxy(2, 7);
  cout << "Month:";
  while (d != 13) {
    for (int i = 0, k = 0; i < 3; i++)
      for (int j = 0; j < 4; k++, j++) {
        gotoxy(25 + j * 5, 7 + i);
        if (l == k + 1)
          textbackground(6);
        cprintf("%s", y[k]);
        if (l == k + 1)
          textbackground(0);
      }
    d = getch();
    if (d == 75 && l != 1)
      l--;
    if (d == 77 && l != 12)
      l++;
    if (d == 72)
      l -= 4;
    if (d == 80)
      l += 4;
    for (int x = 0; x < 4; x++)
      if (l == 13 + x)
        l = 9 + x;
      else if (l == x - 3)
        l = x + 1;
  }
  d = 'a';
  for (int a = 0; a < 3; a++)
    for (int b = 0; b < 4; b++) {
      gotoxy(25 + b * 5, 7 + a);
      clreol();
    }
  gotoxy(2, 7);
  cout << "Month:";
  clreol();
  cout << y[l - 1];
  gotoxy(2, 9);
  cout << "Year:";
  year = 2001;
  while (d != 13) {
    for (int i = 0, k = 2001; i < 5; i++)
      for (int j = 0; j < 10; k++, j++) {
        gotoxy(25 + j * 5, 9 + i);
        if (year == k)
          textbackground(6);
        cprintf("%d", k);
        if (year == k)
          textbackground(0);
      }
    d = getch();
    if (d == 75 && year != 2001)
      year--;
    if (d == 77 && year != 2050)
      year++;
    if (d == 72)
      year -= 10;
    if (d == 80)
      year += 10;
    for (int x = 0; x < 10; x++)
      if (year == 2051 + x)
        year = 2041 + x;
      else if (year == 1991 + x)
        year = 2001 + x;
  }
  for (a = 0; a < 5; a++)
    for (b = 0; b < 10; b++) {
      gotoxy(25 + b * 5, 9 + a);
      clreol();
    }
  gotoxy(2, 9);
  clreol();
  cout << "Year:" << year;
  cout << "\n\n Account No:";
  while (!accno)
    integer(accno, 13, 11, 0);
  textcolor(5 + BLINK);
  for (int t = 1; t <= 14; t++) {
    gotoxy(2, 13);
    clreol();
    cprintf("Searching");
    dot(t % 7, 'y');
  }
  textcolor(7);
  gotoxy(2, 13);
  clreol();
  while (file) {
    file.read((char *)&A, sizeof(A));
    if (!file)
      break;
    if (A.get_accno() == accno) {
      if (!f)
        for (t = 0; t < 3; t++) {
          gotoxy(2, 7 + t * 2);
          clreol();
        }
      if (A.get_month() == l && A.get_year() == year) {
        A.print(i);
        cout << endl;
        (*i)++;
        n++;
        p = 1;
      }
      f = 1;
    }
  }
  file.close();
  if (!f) {
    cout << "Account no does not exist.\n\n Press any key to continue";
    dot(10, 'y');
    getch();
    return;
  }
  file.open("initial.dat", ios::in | ios::binary);
  while (file) {
    file.read((char *)&I, sizeof(I));
    if (!file)
      break;
    if (I.get_accno() == accno) {
      gotoxy(2, 5);
      clreol();
      cout << "Account No:" << I.get_accno();
      gotoxy(20, 5);
      cout << I.get_name();
      gotoxy(20, 6);
      cout << I.get_address();
    }
  }
  file.close();
  if (p == 1) {
    gotoxy(1, 8);
    clreol();
    for (int j = 1; j < 6; j++) {
      gotoxy(i[j], 8);
      clreol();
      switch (j) {
        case 1:
          cprintf("    Date");
          break;
        case 2:
          cprintf("Particular");
          break;
        case 3:
          cprintf("   Deposit");
          break;
        case 4:
          cprintf("  Withdrawal");
          break;
        case 5:
          cprintf("    Balance");
          break;
      }
    }
    (*i);
    box2(i, 5, n + 1, 7);
    gotoxy(5, *i);
    cout << "Total :";
    bal_dep_with(i, *i, accno, 'a', l, year);
  } else {
    gotoxy(3, 6);
    clreol();
    gotoxy(1, 5);
    clreol();
    gotoxy(3, 5);
    cout << "No Report available....";
  }
  cout << "\n\n  Press any key to continue";
  dot(10, 'n');
  time();
}

void modify() {
  clrscr();
  box(1);
  long accno = 0;
  unsigned long pos, x;
  char ch;
  fstream file("initial.dat", ios::in | ios::out | ios::binary);
  if (!file) {
    cout << "File not found!!!";
    getch();
    return;
  }
  gotoxy(30, 4);
  textcolor(5);
  cprintf("Modify Account");
  textcolor(BROWN);
  line(30, 5, 14);
  textcolor(7);
  gotoxy(10, 6);
  cout << "Enter the account no:";
  x = wherex();
  while (!accno)
    integer(accno, x, 6);
  gotoxy(10, 6);
  clreol();
  box(1);
  while (file) {
    pos = file.tellg();
    file.read((char *)&I, sizeof(I));
    if (I.get_accno() == accno) {
      x = I.read(1);
      if (x == 0 || x == 2) {
        file.close();
        return;
      }
      file.seekg(pos);
      gotoxy(28, 21);
      cout << "Saving";
      dot(15, 'y');
      file.write((char *)&I, sizeof(I));
      gotoxy(28, 21);
      clreol();
      box(1);
      cout << "Saved";
      dot(2, 'y');
      delay(500);
      file.close();
      return;
    }
  }
  gotoxy(10, 6);
  cout << "Account no does not exist.";
  gotoxy(10, 8);
  cout << "Press any key to continue";
  dot(10, 'y');
  getch();
  file.close();
}

void del() {
  clrscr();
  long accno = 0;
  int f = 0, i = 1;
  char d = 'a';
  ofstream file1("temp.dat", ios::out | ios::binary);
  ifstream file2("initial.dat", ios::in | ios::binary);
  if (!file2) {
    cout << "File not found!!!";
    getch();
    return;
  }
  gotoxy(30, 2);
  textcolor(5);
  cprintf("Close Account");
  textcolor(BROWN);
  line(30, 3, 13);
  textcolor(7);
  gotoxy(2, 5);
  cout << "Account no: ";
  while (!accno)
    integer(accno, 13, 5, 0);
  while (file2) {
    file2.read((char *)&I, sizeof(I));
    if (!file2)
      break;
    if (accno == I.get_accno()) {
      gotoxy(1, 5);
      clreol();
      gotoxy(15, 5);
      cout << "Do you want to delete the following account?\n\n";  // use capsule
      gotoxy(3, 11);
      clreol();
      cout << "* Account No:" << accno;
      gotoxy(3, 13);
      cout << "* Name:" << I.get_name();
      gotoxy(3, 15);
      cout << "* Address:" << I.get_address();
      gotoxy(3, 17);
      cout << "* Balance:" << I.get_balance();
      while (d != 13) {
        textcolor(13);
        gotoxy(30, 8);
        if (i == 1)
          textbackground(6);
        cprintf("Y");
        textcolor(7);
        cprintf("es");
        if (i == 1)
          textbackground(0);
        textcolor(13);
        gotoxy(40, 8);
        if (i == 2)
          textbackground(12);
        cprintf("N");
        textcolor(7);
        cprintf("o");
        if (i == 2)
          textbackground(0);
        d = getch();
        if (d == 75)
          i--;
        if (i == 0)
          i = 2;
        if (d == 77)
          i++;
        if (i == 3)
          i = 1;
        switch (tolower(d)) {
          case 'y':
            i = 1;
            break;
          case 'n':
            i = 2;
            break;
        }
      }
      if (i == 1) {
        ofstream file3("temp1.dat", ios::out | ios::binary);
        ifstream file4("banking.dat", ios::in | ios::binary);
        while (file4) {
          file4.read((char *)&A, sizeof(A));
          if (!file4)
            break;
          if (A.get_accno() != accno)
            file3.write((char *)&A, sizeof(A));
        }
        file3.close();
        file4.close();
        f = 1;
        remove("banking.dat");
        rename("temp1.dat", "banking.dat");
        gotoxy(28, 21);
        cout << "Deleting";
        dot(15, 'y');
        gotoxy(28, 21);
        clreol();
        cout << "Deleted";
        dot(2, 'y');
        delay(500);
      } else {
        file1.close();
        file2.close();
        remove("temp.dat");
        return;
      }
    } else {
      if (!file2)
        break;
      file1.write((char *)&I, sizeof(I));
    }
  }
  file1.close();
  file2.close();
  if (f) {
    remove("initial.dat");
    rename("temp.dat", "initial.dat");
  } else if (!f) {
    remove("temp.dat");
    gotoxy(12, 5);
    cout << " does not exist.\n\n Press any key to continue";
    dot(10, 'y');
    getch();
  }
}

void menu_names(int i, char a[], char *b[]) {
  for (int l = 1; l <= strlen(a); l++) {
    textcolor(13);
    gotoxy(30, 9 + l);
    if (i == l)
      textbackground(14);
    cprintf("%c", a[l - 1]);
    textcolor(7);
    cprintf("%s", b[l - 1]);
    if (i == l)
      textbackground(0);
  }
}

void edit() {
  clrscr();
  int i = 1;
  char d = '1', s = 27;
  char *a = "MC", *b[2] = {"odify Account", "lose Account"};
  while (d != 8) {
    while (d != 13) {
      clrscr();
      box(0, 6);
      textcolor(10);
      gotoxy(32, 4);
      cprintf("Edit Account");
      line(32, 5, 12);
      gotoxy(62, 23);
      textcolor(15);
      textbackground(9);
      cprintf(" Back = ");
      gotoxy(70, 23);
      textcolor(10);
      cprintf("%c ", s);
      textbackground(0);
      menu_names(i, a, b);
      d = getch();
      if (d == 8)
        return;
      if (d == 72)
        i--;
      if (i == 0)
        i = 2;
      if (d == 80)
        i++;
      if (i == 3)
        i = 1;
      switch (tolower(d)) {
        case 'm':
          i = 1;
          break;
        case 'c':
          i = 2;
          break;
      }
    }
    switch (i) {
      case 1:
        modify();
        break;
      case 2:
        del();
        break;
    }
    i = 1;
    d = '1';
  }
}

void menu() {
  int i = 1;
  char d = '1';
  char *a = "NLIDME";
  _setcursortype(_NOCURSOR);
  char *b[6] = {"ew Account", "ist of Accounts", "ndividual Account",
                "aily Transaction", "onthly Report", "dit Account"};
  while (d != 27) {
    while (d != 13) {
      clrscr();
      box();
      gotoxy(62, 23);
      textcolor(15);
      textbackground(9);
      cprintf(" Exit = ");
      gotoxy(70, 23);
      textcolor(10);
      cprintf("Esc ");
      textbackground(0);
      gotoxy(35, 4);
      cprintf("BANKING");
      line(35, 5, 7);
      menu_names(i, a, b);
      d = getch();
      if (d == 27) {
        clrscr();
        box();
        gotoxy(35, 4);
        textcolor(10);
        cprintf("BANKING");
        line(35, 5, 7);
        gotoxy(25, 11);
        textcolor(4);
        cprintf("Are you sure you want to exit ?");
        int i = 1;
        char d = 'a';
        while (d != 13) {
          textcolor(13);
          gotoxy(32, 15);
          if (i == 1)
            textbackground(6);
          cprintf("Y");
          textcolor(7);
          cprintf("es");
          if (i == 1)
            textbackground(0);
          textcolor(13);
          gotoxy(42, 15);
          if (i == 2)
            textbackground(12);
          cprintf("N");
          textcolor(7);
          cprintf("o");
          if (i == 2)
            textbackground(0);
          d = getch();
          if (d == 75)
            i--;
          if (i == 0)
            i = 2;
          if (d == 77)
            i++;
          if (i == 3)
            i = 1;
          switch (tolower(d)) {
            case 'y':
              i = 1;
              break;
            case 'n':
              i = 2;
              break;
          }
        }
        if (i == 1)
          return;
      }
      if (d == 72)
        i--;
      if (i == 0)
        i = 6;
      if (d == 80)
        i++;
      if (i == 7)
        i = 1;
      switch (tolower(d)) {
        case 'n':
          i = 1;
          break;
        case 'l':
          i = 2;
          break;
        case 'i':
          i = 3;
          break;
        case 'd':
          i = 4;
          break;
        case 'm':
          i = 5;
          break;
        case 'e':
          i = 6;
          break;
      }
    }
    switch (i) {
      case 1:
        open();
        break;
      case 2:
        list();
        break;
      case 3:
        ind();
        break;
      case 4:
        daily();
        break;
      case 5:
        monthly();
        break;
      case 6:
        edit();
        break;
    }
    i = 1;
    d = '1';
  }
}

void animate(char ch = '.') {
  int i = 0;
  while (i != 2028) {
    gotoxy(rand() % 80, rand() % 26);
    cout << ch;
    i++;
    delay(1);
  }
}

void credits() {
  animate();
  animate(' ');
  animate(' ');
  clrscr();
  _setcursortype(_SOLIDCURSOR);
  char s[5][30] = {"Created By", "Aamir Mohammed Hussain", "XII A", "2012-2013", "Press any key to continue.."};
  int p[4] = {30, 25, 33, 31};
  for (int i = 0; i < 4; i++) {
    gotoxy(p[i], 5 + i * 3);
    for (int j = 0; s[i][j]; j++) {
      cout << s[i][j];
      delay(150);
    }
  }
  delay(1000);
  gotoxy(23, 22);
  for (int j = 0; s[i][j]; j++) {
    cout << s[i][j];
    delay(150);
  }
  getch();
  _setcursortype(_NOCURSOR);
  animate();
  animate(' ');
}

void main() {
  message();
  loading();
  // pass();
  menu();
  credits();
  clrscr();
}
///////////////////////////////////////////////////////////////////////////////
//////////////////// **.*.*.*.*   ***      **   **.*.*     ////////////////////
//////////////////// **           ** **    **   **      *  ////////////////////
//////////////////// **.**.**     **   **  **   **       * ////////////////////
//////////////////// **           **    ** **   **      *  ////////////////////
//////////////////// **.*.*.*.*   **      ***   **.*.*     ////////////////////
///////////////////////////////////////////////////////////////////////////////