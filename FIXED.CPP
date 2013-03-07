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

fstream fd,fd1;    
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
	char ast[1000];
	for(int i=0;i<999;i++)
       ast[i]='*';
	ast[i]='\0';

	strcpy(buf,usn);strncat(buf,ast,10-strlen(usn));
	strcat(buf,"|");
	strcat(buf,name);strncat(buf,ast,10-strlen(name));
	strcat(buf,"|");
	strcat(buf,sem);strncat(buf,ast,10-strlen(sem));
	strcat(buf,"|");
	strcat(buf,dept);strncat(buf,ast,10-strlen(dept));
	strcat(buf,"#");
	fd<<buf;
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
		fd.close();  char buf[100],buff[100];

		fd.open("file.txt",ios::in);
		while(fd)
		{
			fd.getline(buf,10,'*');
			int len=strlen(buf);
			fd.seekg(-(len+1),ios::cur);
			cout<<"\n\nBUf contains :"<<buf;
			fd.getline(buff,100,'#');

			if(strcmp(key,buf)==0)
			{
				cout<<"\n\nRecord found\n\n"<<buff;
				fd.close();
				return;
			}
		}
		cout<<"\n\nKey not found\n";fd.close();
		return;
}

void student::modify(char *key)
{

		fd.close();char ast[100];
		fd.open("file.txt",ios::out|ios::in);
		for(int i=0;i<9;i++)
			ast[i]='*';
			ast[i]='\0';


		char buf[100],buff[100];
		while(fd)
		{
			fd.getline(buf,10,'*');
			int len=strlen(buf);
			fd.seekg(-(len+1),ios::cur);
			int x=fd.tellg();
			fd.seekp(x,ios::beg);
			fd.getline(buff,100,'#');
			
			if(strcmp(key,buf)==0)
			{
				cout<<"\n\nRecord found\n\n"<<buff;
				int len1=strlen(buff);
				fd.seekp(-(len1+1),ios::cur);
				read();
				strcpy(buf,usn);strncat(buf,ast,10-strlen(usn));
				strcat(buf,"|");
				strcat(buf,name);strncat(buf,ast,10-strlen(name));
				strcat(buf,"|");
				strcat(buf,sem);strncat(buf,ast,10-strlen(sem));
				strcat(buf,"|");
				strcat(buf,dept);strncat(buf,ast,10-strlen(dept));
				strcat(buf,"#");
				fd<<buf;
				fd.close();
				return;
			}
		}

		fd.close();

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

	
