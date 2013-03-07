#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<process.h>


fstream fd,fp;
void main()
{
	int ch,n;
	char *names1,infile[20],outfile[20];
	char names[10][10];
	clrscr();
	for(;;)
	{
		cout<<"1-std in to std op,2-....";
		cout<<"ch?";
		cin>>ch;
		switch(ch)
		{
			case 1:cout<<"enter the number of student";
				cin>>n;
				cout<<"enter the names";
				for(int i=0;i<n;i++)
				{
					cin>>names[i];
					cout<<strrev(names[i])<<endl;
				}
				break;
			case 2: cout<<"enter the number of student";
				cin>>n;
				cout<<"enter op fname";
				cin>>outfile;
				fd.open(outfile,ios::out);
				cout<<"enter the names";
				for(i=0;i<n;i++)
				{
					cin>>names[i];
					fd<<strrev(names[i])<<endl;
				}
				break;
			case 3: cout<<"enter in fname";
				cin>>infile;
				fd.open(infile,ios::in);
				while(fd)
				{
					fd>>names1;
					cout<<names1<<endl;
				}
				break;
			case 4: cout<<"enter in fname";
				cin>>infile;
				fd.open(infile,ios::in);
				cout<<"enter op fname";
				cin>>outfile;
				fp.open(outfile,ios::out);
				while(fd)
				{
					fd>>names[i];
					fp<<strrev(names[i])<<endl;
				}
				break;
			case 5: exit(0);
		}
		getch();
	}
}

