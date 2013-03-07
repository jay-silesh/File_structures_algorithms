#include<jay.h>

class student
{
	char list1[100][20],list2[100][20];
	int n1,n2;
	public:
		void loadlist(char *file1,char *file2);
			void sort();
		void merge(char *out);

};

fstream fd1,fd2,fd3;

void student::loadlist(char *file1,char *file2)
{
	
	fd1.open(file1,ios::in);
	fd2.open(file2,ios::in);
	
	if(!fd1 || !fd2)
	{
		cout<<"\n\nError in file";
		getch();
		return;
	}
	n1=n2=-1;
	
	while(fd1)
	{
	
		fd1.getline(list1[++n1],20,'\n');
		if(!strcmp(list1[n1],"\0"))
		n1--;
	}
	while(fd2)
	{
	
		fd2.getline(list2[++n2],20,'\n');
		if(!strcmp(list2[n2],"\0"))
		n2--;
	}
	cout<<"\n\nValue of N1:"<<n1<<"\n\nValue of N2:"<<n2<<endl;getch();
}

void student::sort()
{
	
	int i;                             char temp[100];
	
	for(i=0;i<=n1;i++)
	{
		for(int j=i+1;j<=n1;j++)
		{
			if(strcmp(list1[i],list1[j])>0)
			{
				strcpy(temp,list1[i]);
				strcpy(list1[i],list1[j]);
				strcpy(list1[j],temp);
			}	
		}
	}

	cout<<"\n\nList1 sorted\n\n";
	for(i=0;i<=n1;i++)
	cout<<"\n"<<list1[i];
	getch();

	
	for(i=0;i<=n2;i++)
	{
		for(int j=i+1;j<=n2;j++)
		{
			if(strcmp(list2[i],list2[j])>0)
			{
				strcpy(temp,list2[i]);
				strcpy(list2[i],list2[j]);
				strcpy(list2[j],temp);
			}	
		}
	}

	cout<<"\n\nList2 sorted\n\n";
	for(i=0;i<=n2;i++)
	cout<<"\n"<<list2[i];
	getch();
}

void student::merge(char *out)
{

	fd3.open(out,ios::out);
	
	int i=0,j=0;

	cout<<"\n\n"<<out<<": sorted\n";
	while((i<=n1) &&(j<=n2))
	{
		int r=strcmp(list1[i],list2[j]);
	
			if(r==0)
			{
				
				fd3<<list1[i]<<endl;
				cout<<list1[i]<<endl;
				i++;j++;
			}
			else if(r>0)
			{
				
				j++;
			}	

			else
			{
				
				i++;
			}	
	}

	
	fd3.close();
	fd1.close();
	fd2.close();
	
}


	

void main()
{
	int i;
	student s;
	cout<<"\n\nStarting now\n";
	
		s.loadlist("file1.txt","file2.txt");
		s.sort();
		s.merge("out.txt");
	
	
	cout<<"\n\ndone";
	getch();
}