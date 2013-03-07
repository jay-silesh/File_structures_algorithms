#include<jay.h>

class student
{
	char list1[100][20],list2[100][20];
	int n1,n2;
	public:
		void loadlist(char *file1,char *file2);
			void sort();
		void merge(char *out);
		void kmerge();
};

char iff[10][10]={"1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt"};
char of[10][10]={"1o.txt","2o.txt","3o.txt","4o.txt","5o.txt","6o.txt","7o.txt"};

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
				fd3<<list2[j]<<endl;
				cout<<list2[j]<<endl;
				j++;
			}	

			else
			{
				fd3<<list1[i]<<endl;
				cout<<list1[i]<<endl;
				i++;
			}	
	}

	while(i<=n1)
	{
		cout<<list1[i]<<endl;
		fd3<<list1[i++]<<endl;
	}

	while(j<=n2)
	{
		cout<<list2[j]<<endl;
		fd3<<list2[j++]<<endl;
	}
	fd3.close();
	fd1.close();
	fd2.close();
	
}


void student::kmerge()
{
	
	
	int k=4;
	for(int i=0;i<6;i=i+2)
	{
		loadlist(of[i],of[i+1]);
		sort();
		merge(of[k]);
		++k;
	}
}	

void main()
{
	int i;int k=0;
	student s;
	cout<<"\n\nStarting now\n";
	for(i=0;i<=6;i=i+2)
	{
		s.loadlist(iff[i],iff[i+1]);
		s.sort();
		s.merge(of[k++]);
	}
	s.kmerge();
	cout<<"\n\ndone";
	getch();
}