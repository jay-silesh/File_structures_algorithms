#include<jay.h>

class student
{
	char usn[10],name[10],dept[10],sem[10];

	public:

void unpack();
void modify(char *key);
void search(char *key);
void pack();
void read();


};

fstream fd,fd1;     int count=0;

void student::read()
{
	cout<<"\n\nDetails\n";
	cin>>usn>>name>>sem>>dept;
}

void student::pack()
{
	read();
	fd.close();
	fd.open("file.txt",ios::out|ios::app);
	char buf[100];

	strcpy(buf,usn);strcat(buf,"|");
	strcat(buf,name);strcat(buf,"|");
	strcat(buf,sem);strcat(buf,"|");
	strcat(buf,dept);
	strcat(buf,"#");
	fd<<buf;  ++count;
	fd.close();
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

void student::search(char *key)
{
		fd.close();  char buf[100],buf1[100];
	
		fd.open("file.txt",ios::in);
		while(fd)
		{
			fd.getline(buf,100,'#');
			strcpy(buf1,buf);
			strtok(buf1,"|");
			if(strcmp(buf1,key)==0)
			{
				cout<<"\n\nRecord found\n\n"<<buf;
				fd.close();
				return;
			}
		}
		cout<<"\n\nKey not found\n";fd.close();
		return;
}

void student::modify(char *key)
{

		fd.close();
		fd.open("file.txt",ios::out|ios::in);
		fd1.open("dump.txt",ios::out|ios::app);
		   int y=count;		       char buf[100],buf1[100];  int x=0;
		while(fd && y<=count)
		{
			fd.getline(buf,100,'#');
			strcpy(buf1,buf);
			strtok(buf1,"|");

			if(strcmp(buf1,key)==0)
			{

				read();
				char buf[100];

			strcpy(buf,usn);strcat(buf,"|");
			strcat(buf,name);strcat(buf,"|");
			strcat(buf,sem);strcat(buf,"|");
			strcat(buf,dept);
			strcat(buf,"#");
			fd1<<buf;
			   ++x;--y;
			}
			else
			{
				if(x!=count)
				strcat(buf,"#");
				fd1<<buf; ++x;--y;

			}
		}

		fd.close();
		fd1.close();
		remove("file.txt");
		rename("dump.txt","file.txt");
}


void main()
{
	int ch,i;
	clrscr();
		student s;
		char key[100];
	for(;;)
	{

		cout<<"\n\n1.Pack\n2.Unpack\n3.Search\n4.Modify\n5.exit\n\n";
		cin>>ch;
		switch(ch)
		{
			case 1:s.pack();
				break;

			case 3:cout<<"\n\nKey:";
				cin>>key;
				s.search(key);
				break;
			case 5:exit(0);

			case 4:cout<<"\n\nKey:";
				cin>>key;
				s.modify(key);
				break;

			case 2:s.unpack();
				break;

			case 9:remove("file.txt");
				remove("dump.txt");
				break;
			
			}
	}
}

	
