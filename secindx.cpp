#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
#include<fstream>
#include<string.h>
#define maxlen 43
class student
{
	private:
		char name[26],usn[11],sem[2],dept[4];
		char *file, *pindex, *sindex;
		fstream f,pdx,sdx;
	public:
		student(char[],char[],char[]);
		void read();
		void pack(int );
		void unpack();
		void searchdelete(int,char[]);
		void print(int);
		void sort(int);
};
student::student(char fl[],char idx1[], char idx2[])
{
	file = new char [maxlen];
	pindex=new char [maxlen];
	sindex=new char [maxlen];
	
	strcpy(file,fl);
	strcpy(pindex,idx1);
	strcpy(sindex,idx2);
	
	f.open(file,ios::out|ios::trunc);
	f.close();
	
	pdx.open(pindex,ios::out|ios::trunc);
	pdx.close();
	
	sdx.open(sindex,ios::out|ios::trunc);
	sdx.close();
	
}
void student::read()
{
	cout<<"\nName: ";
	cin>>name;
	cout<<"\nUSN: ";
	cin>>usn;
	cout<<"\nSem: ";
	cin>>sem;
	cout<<"\nDept: ";
	cin>>dept;
}
void student::pack(int mode)
{
	char *buffer= new char[maxlen*2];
	int disp;
	strcpy(buffer,usn);
	strcat(buffer,"|");
	strcat(buffer,name);
	strcat(buffer,"|");
	strcat(buffer,sem);
	strcat(buffer,"|");
	strcat(buffer,dept);
	strcat(buffer,"\n");
	
	if(!mode)
	{
		f.open(file, ios::out|ios::app);
		f.seekp(0,ios::end);
		disp = f.tellp();
	}
	f<<buffer;
	f.close();
	
	if(!mode)
	{
		pdx.open(pindex,ios::out|ios::app);
		pdx<<usn<<"\t"<<disp<<endl;
		pdx.close();
	
		sdx.open(sindex,ios::out|ios::app);
		sdx<<name<<"\t"<<usn<<endl;
		sdx.close();
	}
}
void student::unpack()
{
	f.getline(usn,30,'|');
	f.getline(name,30,'|');
	f.getline(sem,30,'|');
	f.getline(dept,30,'\n');
}
void student::searchdelete(int mode,char key[])
{
	char pkey[11],buffer[maxlen*2]={0},sname[26],skey[11],number[5];
	int offset,r,flag=0;
	switch(mode)
	{
		case 1:
		case 2:
			pdx.open(pindex,ios::out|ios::in);
			while(!pdx.eof())
			{
				pdx>>pkey;
				pdx>>offset;
				r=strcmp(pkey,key);
				if(r==0)
				{
					flag = 1;
					cout<<"\nRecord Found in Primary Index File!\n";
					f.open(file,ios::out|ios::in);
					f.seekg(offset,ios::beg);
					unpack();
					
					if(mode==1)
					{
						f.close();
						cout<<"\nName: "<<name;
						cout<<"\nUSN: "<<usn;
						cout<<"\nSem: "<<sem;
						cout<<"\nDept: "<<dept;
					}
					else
					{
						usn[0] = '*';
						
						f.seekp(offset, ios::beg);
						pack(1);
						strcpy(buffer,usn);
						strcat(buffer,"\t");
						
						sprintf(number,"%d",offset);
						strcat(buffer,number);
						
						pdx.seekp(-(strlen(buffer)),ios::cur);
						pdx<<buffer<<endl;
						
						sdx.open(sindex,ios::out|ios::in);
						while(!sdx.eof())
						{
							sdx>>sname;
							sdx>>skey;
							r=strcmp(skey,pkey);
							if(r==0)
							{
								sname[0] = '*';
								strcpy(buffer,sname);
								strcat(buffer,"\t");
								strcat(buffer,usn);
								sdx.seekp(-(strlen(buffer)),ios::cur);
								sdx<<buffer<<endl;
							}
						}
						sdx.close();
					}
					break;
				}
			}
			pdx.close();
			if(flag==0)
				cout<<"\nRecord Not found in Primary Index File!\n";
			break;
		case 3:
		{
			sdx.open(sindex,ios::out|ios::in );
			while (!sdx.eof())
			{
				sdx>>sname;
				sdx>>skey;
				r=strcmp(key,sname);
				if(r==0)
				{
					flag = 1;
					cout<<"\nRecord Found in Secondary Index file! ";
					searchdelete(1,skey);
					break;
				}
			}
			if(flag == 0)
				cout<<"\nRecord Not found in the Secondary Index file \n";
			break;
		}
	}
}
void student::print(int mode)
{
	char pkey[11],sname[25], offset[4];
	switch(mode)
	{
		case 1:
			cout<<"\nPrinting Data File: ";
			f.open(file, ios::out |ios::in );
			while(!f.eof())
			{
				unpack();
				if(usn[0] != '*')
					cout<<endl<<name<<"\t"<<usn<<"\t"<<sem<<"\t"<<dept;
			}
			f.close();
			break;
		case 2:
			sort(1);
			cout<<"\nPrinting Primary Index File";
			pdx.open(pindex,ios::out|ios::in);
			while(!pdx.eof())
			{
				pdx>>pkey;
				pdx>>offset;
				
				if(pkey[0] != '*')
					cout<<endl<<pkey<<"\t"<<offset;
			}
			pdx.close();
			break;
		case 3:
			sort(2);
			cout<<"\nPrinting Secondary Index File: ";
			sdx.open(sindex,ios::out|ios::in );
			while (!sdx.eof())
			{
				sdx.getline(sname,30,'\t');
				sdx.getline(pkey,30,'\n');
				
				if(sname[0] != '*')
					cout<<endl<<sname<<"\t"<<pkey;
			}
			break;
		default:
			cout<<"\nInvalid Option";
	}
}
void student::sort (int mode)
{
	int n,i,swp,j,r,pos;
	char pkey[11],offset[3],sname[26],small[26],temp[26],buffer[20][26]={{0}};
	switch(mode)
	{
		case 1:
			pdx.open(pindex,ios::out|ios::in);
			for (n=0; !pdx.eof(); n ++ )
			{
				pdx>>pkey;
				pdx>>offset;
				strcpy(buffer[n],pkey);
				strcat(buffer[n],"\t");
				strcat(buffer[n],offset);
			}
			pdx.close();
			break;
		case 2:
			sdx.open(sindex,ios::out|ios::in);
			for(n=0; !sdx.eof(); n++)
			{
				sdx>>sname;
				sdx>>pkey;
				strcpy(buffer[n],sname);
				strcat(buffer[n],"\t");
				strcat(buffer[n],pkey);
			}
			sdx.close();
			break;
	}
	for(i=0; i < n-1 ; i ++)
	{
		swp = 1;
		strcpy (small, buffer[i]);
		for(j=i+1; j<n; j++)
		{
			r=strcmp(small, buffer[j]);
			if(r>0)
			{
				swp = 1; 
				pos = j;
				strcpy(small,buffer[j]);
			}
		}
		if(swp)
		{
			strcpy(temp,buffer[i]);
			strcpy(buffer[i],buffer[pos]);
			strcpy(buffer[pos],temp);
		}
	}
	switch(mode)
	{
		case 1:
			pdx.open(pindex,ios::out|ios::trunc);
			for(i=0;i<n;i++)
				pdx<<buffer<<endl;
			pdx.close();
			break;
		case 2:
			sdx.open(sindex,ios::out|ios::trunc);
			for(i=0;i<n;i++)
				sdx<<buffer<<endl;
			sdx.close();
			break;
	}
}
int main()
{
	student s("./file.txt","./p.txt","./s.txt");
	int ch,ch2;
	char key[11],name[26];
	for(;;)
	{
		cout<<"\n1.Insert\t2.Delete\t3.Search by Pkey\t4.Search by Skey\t5.Print\t6.Exit";
		cout<<"\nChoice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				s.read();
				s.pack(0);
				break;
			case 2:
				cout<<"\nEnter USN: ";
				cin>>key;
				s.searchdelete(2,key);
				break;
			case 3:
				cout<<"\nEnter USN: ";
				cin>>key;
				s.searchdelete(1,key);
				break;
			case 4:
				cout<<"\nEnter Name: ";
				cin>>name;
				s.searchdelete(3,name);
				break;
			case 5:
				cout<<"\n1.Data File\t2.Primary Index\t3.Secondary Index";
				cout<<"\nChoice: ";
				cin>>ch2;
				s.print(ch2);
				break;
			case 6:
				exit(0);
			default:
				cout<<"\nInvalid Option!";
		}
	}
}

				
				
		
		
