#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

class student {
	char usn[11];
	char name[11];
	char branch[11];
	char sem[11];

	public:
	void read()
	{	cout<<"\nname:";cin>>name;
		cout<<"\nusn:";cin>>usn;
		cout<<"\nbranch:";cin>>branch;
		cout<<"\nsem:";cin>>sem;
	}
	void pack();
      friend void makefile();
      friend int hash(char *usn);
      friend void search(char *usn);
};
int hash(char *usn)
{       char ch=usn[0];
	char ch1=usn[1];
	char ch2=ch+ch1;
	return (ch2%19)*50;
}
void student::pack()
{
       fstream file("records",ios::in|ios::out);
       if(!file)
	 { 
	cout<<"\nerror in opening file!";
       	exit(1);
       	 }
       file.seekp(0,ios::beg);
       file.seekg(0,ios::beg);
       char ast[]="************************************************************************";
       int pos=hash(usn);
       char ch,buff[100]={0};
       file.seekg(pos,ios::beg);
       file.seekp(pos,ios::beg);
       while(file)
       {  file.get(ch);
	  if(ch!='!')
	  file.seekp(++pos,ios::beg);
	  else
	  break;
       }
       strcpy(buff,usn);strcat(buff,"|");
       strcat(buff,name);strcat(buff,"|");
       strcat(buff,branch);strcat(buff,"|");
       strcat(buff,sem);
       if(strlen(buff)<49) strncat(buff,ast,49-strlen(buff));
       strcat(buff,"#");
       file.seekp(--pos,ios::beg);
       file<<buff;
}

void makefile()
{
     fstream file("records",ios::out);
     if(!file) { cout<<"\nerror in opening file!";
     exit(1);
     }
     char j='0';
     char k='!';
     for(int i=1;i<=1000;i++)
     {	  if(i%50==0) file<<k;
	  else 
	  file<<j;
     }
     return;
}

void search(char *usn)
{
	fstream file("records",ios::in);
	if(!file) { cout<<"\nerror in opening file!";
	exit(1);
	}
	char ch,buf[80]={0};
	int pos=hash(usn);
	file.seekg(pos,ios::beg);
	while(file)
	{    file.get(ch);
	     if((ch!='0')&&(ch!='!')) {
		file.seekg(pos,ios::beg);
		file.getline(buf,50,'|');
		if(!strcmp(buf,usn))
		{	cout<<"\ndetails...\n";
			cout<<buf<<"|";
			file.getline(buf,50,'#');
			strtok(buf,"*");
			cout<<buf<<endl;
			return;
		}
	     }
	     pos++;
	     file.seekg(pos,ios::beg);
	}
	cout<<"\nunsuccessful search!";
}

int main()
{
	student s;
        makefile();
	char usn[11];
	int choice;
	clrscr();
	for(;;)
	{	cout<<"\n1-pack 2-search 3-exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1: s.read();
				s.pack();
			break;

			case 2: cout<<"\nusn:";cin>>usn;
				search(usn);
				getch();
			break;

			default: return 0;
		}
	}
}