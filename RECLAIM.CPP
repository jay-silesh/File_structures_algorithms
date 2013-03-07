#include<jay.h>

class student
{
	char usn[10],name[10],dept[10],sem[10];

	public:

void unpack();
void modify(char *key);
void del(char *key);

int search(char *key);

void pack(int mode);
void read();


};

fstream fd;
int top=-1;
int count=0;
int avail[100];

void make()
{
	for(int i=0;i<99;i++)
	avail[i]=-1;
}


void student::read()
{
	cout<<"\n\nDetails\n";
	cin>>usn>>name>>sem>>dept;
}

void student::pack(int mode)
{
	read();
	if(count>0 && mode==2)
	{
		fd.close();
		fd.open("file.txt",ios::in|ios::out);
		int pos;
		pos=avail[top--];
		count--;
		fd.seekp(pos,ios::beg);
	}

	char buf[100];

	strcpy(buf,usn);strcat(buf,"|");
	strcat(buf,name);strcat(buf,"|");
	strcat(buf,sem);strcat(buf,"|");
	strcat(buf,dept);
	int x=strlen(buf);
	for(int i=x;i<39;i++)
	strcat(buf,"*");
	strcat(buf,"#");
	fd<<buf;
	fd.close();
}

int student::search(char *key)
{
	fd.close();         char buf1[100],buf2[100];
	fd.open("file.txt",ios::in);
	fd.seekg(0,ios::beg);
	while(fd)
	{
		fd.getline(buf1,100,'#');
		strcpy(buf2,buf1);
		strtok(buf2,"|");
		if(strcmp(key,buf2)==0)
		{
			int x=strlen(buf1);
			cout<<"\n\nKey found\n";
			cout<<"\n\n"<<buf1;
			fd.seekg(-(x+1),ios::cur);
			int p;
			p=fd.tellg();
			return p;
		}
	}
	cout<<"\n\nKey not found";
	return -1;
}

void student::del(char *key)
{
	int pos=search(key);
	if(pos==-1)
	return;

	fd.close();
	fd.open("file.txt",ios::in|ios::out);
	fd.seekp(pos,ios::beg);
	fd<<"*";
	count++;
	avail[++top]=pos;
	cout<<"\n\nKey deleted";
	return;
}

void student::modify(char *key)
{
	int pos=search(key);
	if(pos==-1)
	return;
	
	fd.close();
	fd.open("file.txt",ios::in|ios::out);
	fd.seekp(pos,ios::beg);
	pack(1);
	return;
}

void student::unpack()
{
		    char buf1[100],buf2[100],crap[100];
		    fd.close();
		fd.open("file.txt",ios::in);
		fd.seekg(0,ios::beg);
		while(fd)
	{
		fd.getline(buf1,2,'|');
		if(strcmp(buf1,"*")==0)
		fd.getline(crap,100,'#');
		else
		{
			fd.seekg(-1,ios::cur);
			fd.getline(buf2,100,'#');
			strtok(buf2,"*");
			cout<<"\n\n"<<buf2;
		}
	}
	fd.close();
}

		
		
	
void main()
{
	student s;
	clrscr();
	make();
	int i,ch;
	char key[100];
	for(;;)
	{
		cout<<"\n\n1.Pack\n2.unpack\n3.Search\n4.modify\n5.del\n6.exit\n\n";
		cin>>ch;
		switch(ch)
		{
			case 1: fd.open("file.txt",ios::app);
				s.pack(2);
				break;

			case 2:s.unpack();
				break;

			case 3:cout<<"\n\nKey:";
				cin>>key;
				s.search(key);
				break;

			case 4:cout<<"\n\nKey:";
				cin>>key;
				s.modify(key);
				break;
			case 5:cout<<"\n\nKey:";
				cin>>key;
				s.del(key);
				break;
			case 6:exit(0);
			case 9:remove("file.txt");

				break;
		}
	}
}