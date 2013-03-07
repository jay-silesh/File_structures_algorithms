#include<jay.h>

class student
{
	char usn[10],name[10],sem[10],dept[10];

	public:	void pack();
		void sort(int mode);
		int search(char *usn1);
		void del(char *usn1);
		void unpack();
		void read();
		void search1(char *usn1);
		void del1(char *key);
};

int count=0;
int pos=0;
fstream fd,fd1,fd3;

void student::read()
{
	cout<<"\n\nDetails\n";
	cin>>usn>>name>>sem>>dept;

}

void student::pack()
{
	read();
	char buf[100];
	fd.close();
	fd.open("file.txt",ios::app);
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
	
	fd1.close();				/*	Primary Index	*/
	fd1.open("x.txt",ios::app);
	strcpy(buf,usn);
	strcat(buf,"|");
	fd1<<buf;
	fd1.close();
	fd1.open("x.txt",ios::app);
	fd1<<pos;
	fd1.close();
	fd1.open("x.txt",ios::app);
	fd1<<endl;
	fd1.close();
	fd.open("file.txt",ios::in);
	fd.seekg(0,ios::end);
	pos=fd.tellg();
	fd.close();

	fd3.open("c.txt",ios::app);		/*	Secondary Index	*/
	strcpy(buf,name);
	strcat(buf,"|");
	strcat(buf,usn);
	strcat(buf,"\n");
	fd3<<buf;
	fd3.close();
}

void student::sort(int mode)
{
	char buf[100][100];
	int i=0,l=0;
	
	if(mode==1)
		fd1.open("x.txt",ios::in|ios::out);
	else
		fd1.open("c.txt",ios::in|ios::out);
	
	
	while(fd1)
	{
		fd1.getline(buf[i],100,'\n');
		if(buf[i]==NULL)continue;
		if(fd1)
		i++;
	}

	for(int x=0;x<i;x++)
	{
		for(int y=x+1;y<i;y++)
		{
			if(strcmp(buf[x],buf[y])>0)
			{
				char temp[100];
				strcpy(temp,buf[x]);
				strcpy(buf[x],buf[y]);
				strcpy(buf[y],temp);
			}
		}
	}

	fd1.close();
	if(mode==1)
	{
		remove("x.txt");
		fd1.open("x.txt",ios::out);
	}
	
	if(mode==2)
	{	
		remove("c.txt");
		fd1.open("c.txt",ios::out);
	}
	
	while(l<i)
	fd1<<buf[l++]<<endl;
	fd1.close();

}




void student::unpack()
{
	fd.open("file.txt",ios::in);
	char buf[100];
	while(fd)
	{
		fd.getline(buf,100,'#');
		cout<<"\n\n"<<buf;
	}
	fd.close();
}

int student::search(char *key)
{
	fd1.close();
	fd1.open("x.txt",ios::in);
	fd1.seekg(0,ios::beg);
	char buf[100],buf1[100],buf2[100];
	while(fd1)
	{
		fd1.getline(buf,100,'\n');
		strcpy(buf1,buf);
		strtok(buf1,"|");
		char *ptr=strtok(NULL,"\0");
		
		if(!strcmp(ptr,"\0")){cout<<"\n\nNo Data";return -1;}
		
		if(strcmp(key,buf1)==0)
		{
			int x=atoi(ptr);
			fd.open("file.txt",ios::in);
			fd.seekg(x,ios::beg);
			fd.getline(buf2,100,'#');
			cout<<"\n\nKey found in search\n"<<buf2;
			fd1.close();
			fd.close();
			return x;
		}
	}
	cout<<"\n\nKey not found";
	return -1;
}


void student::search1(char *key)
{
	fd1.close();
	fd1.open("c.txt",ios::in);
	fd1.seekg(0,ios::beg);
	char buf[100],buf1[100],buf2[100];
	while(fd1)
	{
		fd1.getline(buf,100,'\n');
		strcpy(buf1,buf);
		strtok(buf1,"|");
		char *ptr=strtok(NULL,"\0");
		
		if(!strcmp(ptr,"\0")){cout<<"\n\nNo Data";getch();return;}
		
		if(strcmp(key,buf1)==0)
		{
			fd1.close();
			search(ptr);
			return;
		}
	}
	fd1.close();
	cout<<"\n\nKey not found";
	return;
}

void student::del(char *key)
{
	int x=search(key);
	if(x==-1)
	return;
	    char buf[100],buf1[100],buf2[100],bufx[100];
	fd.close();
	fd.open("x.txt",ios::in);
	fd.seekg(0,ios::beg);
	while(fd)
	{
		fd.getline(buf,100,'\n');
		strcpy(buf1,buf);
		strtok(buf1,"|");
		char *ptr=strtok(NULL,"\n");
		strcpy(bufx,ptr);
		
		if(!strcmp(buf1,"\0")){cout<<"\n\nNo data error";getch();return;}
		
		if(strcmp(key,buf1)==0)
		{
			cout<<"\n\nKey found in del"<<buf;
			strcat(buf,"\n");
			int y=strlen(buf);
			int tel=fd.tellg();
			fd.close();
			fd.open("x.txt",ios::out|ios::in);
			fd.seekp(tel,ios::beg);
			fd.seekp(-(y+1),ios::cur);
			fd<<"*";
			fd.close();

			int q=atoi(ptr);
			fd.open("file.txt",ios::out|ios::in);
			fd.seekp(q,ios::beg);
			fd<<"*";
			fd.close();
			cout<<"\n\nKey deleted";

			return;
		}
	}

		fd.close();
		cout<<"\n\nCouldnt del";
		return;
}


void student::del1(char *key)
{
	char buf[100],buf1[100],buf2[100],bufx[100];
	fd.close();
	fd.open("c.txt",ios::in);
	fd.seekg(0,ios::beg);
	while(fd)
	{
		fd.getline(buf,100,'\n');
		strcpy(buf1,buf);
		strtok(buf1,"|");
		char *ptr=strtok(NULL,"\n");
		strcpy(bufx,ptr);
		
		if(!strcmp(buf1,"\0")){cout<<"\n\nNo data error";getch();return;}
		
		if(strcmp(key,buf1)==0)
		{
			
			strcat(buf,"\n");
			int y=strlen(buf);
			int tel=fd.tellg();
			fd.close();
			fd.open("c.txt",ios::out|ios::in);
			fd.seekp(tel,ios::beg);
			fd.seekp(-(y+1),ios::cur);
			fd<<"*";
			fd.close();
			del(bufx);
			return;
		}
	}

		fd.close();
		cout<<"\n\nCouldnt del";
		return;
}

void main()
{
	int ch,i;
	clrscr();
		student s;
		char key[100];
	for(;;)
	{

		cout<<"\n\n1.Pack\n2.Unpack\n3.Search\n4.Del\n5.search by name\ndel by name\n7.exit\n\n";
		cin>>ch;
		switch(ch)
		{
			case 1:s.pack();
				s.sort(1);
				s.sort(2);
				break;

			case 3:cout<<"\n\nKey:";
				cin>>key;
				s.search(key);
				break;

			case 4:cout<<"\n\nKey:";
				cin>>key;
				s.del(key);
				break;

			case 2:s.unpack();
				break;

			case 5:cout<<"\n\nKey:";
				cin>>key;
				s.search1(key);
				break;

			case 6:cout<<"\n\nKey:";
				cin>>key;
				s.del1(key);
				break;

			case 7:exit(0);
				break;

			case 9:remove("file.txt");
				remove("x.txt");
				remove("c.txt");
				break;


			}
	}
}


