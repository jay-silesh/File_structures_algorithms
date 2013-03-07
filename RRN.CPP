#include<jay.h>

class student
{
	char usn[10],name[10],dept[10],sem[10];

	public:

void unpack();

void ret();



void pack();
void read();


};

fstream fd,fd1;
int count=0;
int x=0;
void student::read()
{
	cout<<"\n\nDetails\n";
	cin>>usn>>name>>sem>>dept;
}

void student::pack()
{
	read();
	char buf[100];


	fd.open("file.txt",ios::out|ios::app);

	strcpy(buf,usn);
	strcat(buf,"|");
	strcat(buf,name);
	strcat(buf,"|");
	strcat(buf,sem);
	strcat(buf,"|");
	strcat(buf,dept);
	strcat(buf,"#");

	fd<<buf;
	fd.close();
	fd.open("file.txt",ios::in);
	fd.seekg(0,ios::end);
	int last=fd.tellg();
	fd.close();
	count++;
	fd1.open("x.txt",ios::app|ios::out);
	fd1<<(x)<<endl;
	fd1.close();
	x=last;

}

void student::ret()
{
	cout<<"\n\nEnter the RRN:";
	int rrn;
	cin>>rrn;
	int pos=0;
	int bcount;
	fd.close();
	fd1.close();
	fd1.open("x.txt",ios::in);
   
	if(rrn>count)
	{
		cout<<"\n\nExceeded rrn";

		return;
	}
	  char buf[100];
		if(rrn==1)
		{
			fd.open("file.txt",ios::in);
			fd.seekg(0,ios::beg);
			fd.getline(buf,100,'#');
			cout<<"\n\nFound\n\n"<<buf;
			fd.close();
			fd1.close();
			return;
		}

		bcount=0;
		fd1.seekg(0,ios::beg);
				char posx[200];
		while(bcount<(rrn))
		{
			fd1>>pos;
			cout<<"\n\nPos:"<<pos;getch();
			++bcount;
	       	}
			fd.open("file.txt",ios::in);
			fd.seekg(pos,ios::beg);
			fd.getline(buf,100,'#');
			cout<<"\n\nFound\n\n"<<buf;
			fd.close();
			fd1.close();
			return;

}

void student::unpack()
{
	fd.close();
	fd.open("file.txt",ios::in);
	fd.seekg(0,ios::beg);
	char buf[100];
	while(fd)
	{
		fd.getline(buf,100,'#');
		cout<<"\n"<<buf;
	}
	cout<<"\nEnd";
	fd.close();
}
	
int main()
{
	student s;
	clrscr();
       //	make();
	int i,ch;
	char key[100];
	for(;;)
	{
		cout<<"\n\n1.Pack\n2.unpack\n3.ret\n4.exit\n\n";
		cin>>ch;
		switch(ch)
		{
			case 1: 
				s.pack();
				break;

			case 2:s.unpack();
				break;

			case 3:
				s.ret();
				break;

			case 4:
		   //	remove("file.txt");
		    //	remove("x.txt");

			exit(0);


			case 9:remove("file.txt");
			       remove("x.txt");
				break;
		}
	}
}