#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>

class cosequential
{
	char list1[100][20],list2[100][20];
	int n1,n2;
	public:void seq_sort();
		void match();
		void load();
};

fstream f1,f2,of;
void cosequential::seq_sort()
{
	char temp[20];
	for(int i=0;i<n1;i++)
	{
		for(int j=i+1;j<n1;j++)
		{
			if(strcmp(list1[i],list1[j])>0)
			{
				strcpy(temp,list1[i]);
				strcpy(list1[i],list1[j]);
				strcpy(list1[j],temp);
			}
		}
	}
	for(i=0;i<n2;i++)
	{
		for(int j=i+1;j<n2;j++)
		{
			if(strcmp(list2[i],list2[j])>0)
			{
				strcpy(temp,list2[i]);
				strcpy(list2[i],list2[j]);
				strcpy(list2[j],temp);
			}
		}
	}
}
void cosequential::load()
{
	n1=n2=-1;
	while(!f1.eof())
	{
		f1.getline(list1[++n1],20,'\n');
	}
	while(!f2.eof())
	{
		f2.getline(list2[++n2],20,'\n');
	}
}
void cosequential::match()
{
	int i=0,j=0;
	cout<<"\nMatching names";
	while((i<=n1) && (j<=n2))
	{
		if(strcmp(list1[i],list2[j])==0)
		{
			cout<<endl<<list1[i];
			of<<list1[i]<<endl;
			i++;
			j++;
			continue;
		}
		else if(strcmp(list1[i],list2[j])>0)
			j++;
		else
			i++;
	}
}
void main()
{
	cosequential cq;
	clrscr();
	f1.open("std71.txt",ios::in);
	f2.open("std72.txt",ios::in);
	if(f1.fail() || f2.fail())
	{
		cout<<"Cannot open file";
		getch();
		exit(1);
	}
	cq.load();
	f1.close();
	f2.close();
	f1.open("std71.txt",ios::in);
	f2.open("std72.txt",ios::in);
	of.open("std73.txt",ios::out);
	cq.seq_sort();
	cq.match();
	f1.close();
	f2.close();
	of.close();
	getch();
}
