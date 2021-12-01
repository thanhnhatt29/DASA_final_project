#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define N 50


void printLine(int n); 
void checkname( char *s);
struct customer{
	char name[20];
	char ID[15];
	int year;
	int age()
	{
		return 2021-year;
	}
	char home[20];
};

struct inroom{
	customer khach;
	init();
	int bed;//(1 or 2)
	bool status;//(true=thue--false=trong)
	bool vip;//(true=room vip---false=room thuong)
	int price;//(gia room)
	int bill=0;//(hoa don thue room)
};

class motel{
	inroom room[N];
	int money;//(tong doanh thu)
public:
	void Create();
	void Rent(customer x,int to);
	void Pay(int from);
	void oneday();
	void ShowCustomer();
	void Change(int from, int to);
	void docFile(char fileName[]);
	void ResetInfo(int i);
	void ghiFile(char fileName[]);
};

void motel::Create(){
	//bed = 1 => giuong don, bed = 2 => giuong doi
	//vip = false => phong tieu chuan, vip = true => phong vip
	for(int i=1;i<=N;i++)
	{
		if(i<=10)
		{
			room[i].bed=1;
			room[i].vip=false;
			room[i].price=200000;
			room[i].status=false;
		}
		else if(i<=20)
		{
			room[i].bed=2;
			room[i].vip=false;
			room[i].price=400000;
			room[i].status=false;
		}
		else if(i<=30)
		{
			room[i].bed=1;
			room[i].vip=true;
			room[i].price=500000;
			room[i].status=false;
		}
		else
		{
			room[i].bed=2;
			room[i].vip=true;
			room[i].price=1000000;
			room[i].status=false;
		}
	}
}

// su dung ham nay  de tang tong bill theo tung ngay
void motel::oneday()
{
	for(int i=1;i<=50;i++)
	{
		if(room[i].status==true)
		{
			room[i].bill+=room[i].price;
		}
	}
}
// ham thanh toan cho khach
void motel::Pay(int from)
{
	int i=from;//so room can thanh toan

	if(room[i].status==true)
	{
		if(room[i].bill==0)
		{
			money+=room[i].price;
		}
		else{
			money+=room[i].bill;
		}
		printf("Da thanh toan phong %d voi gia tien %d",i,room[i].bill);
		ResetInfo(i);
	}
	else printf("Phong trong");
}
//xoa thong tin khach hang tai phong i
void motel::ResetInfo(int i)
{
	room[i].bill=0;
	room[i].khach.home[20]=room[i].khach.ID[15]=room[i].khach.name[20]=room[i].khach.year=NULL;
	room[i].status=false;	
}
// chuyen so phong cho khach
void motel::Change(int from, int to)
{
	Rent(room[from].khach,to);
	room[to].bill=room[from].bill;
	ResetInfo(from);
}
int sophong(int i)
{
	do{
		printf("Nhap phong:");
		scanf("%d",&i);
	}while(i<1||i>N);
	return i;
}
// get thong tin khach hang
customer Info(customer x){
	fflush(stdin);
	printf("Nhap ten: ");	gets(x.name);
	printf("Nhap ID: ");	gets(x.ID);
	printf("Nhap que quan: ");	gets(x.home);
	printf("Nhap nam sinh: ");	scanf("%d",&x.year);
	return x;
}
// ham dung de thue 1 phong
void motel::Rent(customer x,int to){
	int i = to; //to la so room nhap tu ben ngoai
	
	if( room[i].status == false )
	{
		
		if( x.age()<18)
		{
			printf("Khong du tuoi thue!");
			return;
		}
		room[i].khach=x;
		room[i].status=true;		
	}
	else
		printf("Phong nay da co khach");
}
// ham show thong tin nhung phong dang duoc thue va thong tin khach tai phong do
void motel::ShowCustomer()
{
	printLine(110);
	cout << "|TT|   \tID\t   |\t Ten \t\t|Nam Sinh|Que Quan            |";
	for (int i = 1; i <= N ; i++)
	{
		// in Student thu i ra man hinh
		if (!room[i].status) continue;
		printf("\n|%-2d", i);
		printf("|%15s", room[i].khach.ID);
		printf("|%-20s", room[i].khach.name);
		printf("|%-8d", room[i].khach.year);
		printf("|%-20s|", room[i].khach.home);
	}
	printLine(110);
}
void printLine(int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "=";
	}
	cout << endl;
}


void motel::docFile(char fileName[])
{
	FILE * fp;
	int a,i = 0;
	fp = fopen (fileName, "r");
	cout << endl;
	cout << "Chuan bi doc file: "<<fileName<<".............."<<endl; //puts(fileName);
	customer x;
	while (fscanf(fp, "%2d %[^\t] %[^\t] %4d %[^\n]",&a, &x.name,
 &x.ID, &x.year, &x.home) != EOF) 
	{
		checkname(x.name);
		Rent(x,a);
		i++;
	}
	cout << "So luong Student co san trong file la: " << i << endl;
	printLine(40);
	fclose (fp);
	return ;
}


void motel::ghiFile(char fileName[]) 
{
	FILE * fp;
	fp = fopen(fileName, "w");
	for (int i = 1; i <= N; i++) 
	{
		if(!room[i].status) continue;
		fprintf(fp, "%2d %-s\t %-s\t %4d %-s\n",i, room[i].khach.name, room[i].khach.ID,room[i].khach.year,room[i].khach.home);
	}
	fclose(fp);
}
void checkname( char *s) // chuan hoa chuoi
{
	int L=strlen(s);
	//
	if (s[L-1]!=0) s[L]=0;
	bool inword=false;// qui uoc IW=false thi boqua, true moi lay
	int k=0;
	char c;

	for(int i=0;i<L;i++)
	{
		c=s[i];//lay chu trong chuoi
		if (c!=' ')
		{
			if (inword== false)// neu c= chudautu thi chuyen IW=true, sau do lay tat ca chu cua tu do
				inword= true;
				s[k++]=c;
			//if (k==1) s[k-1]=s[k-1]-32;
		}
		else if (inword==true)// khi da het chu, chuyen IW=false, chi lay 1 khoang trong sau do
		{
			inword=false;
			s[k++]=c;
		}
		if (i==L-1 &&s[i]!=' ') inword=false;
		//xuatchuoi(s);
	}
	//printf("%d",k);
	while(inword==false) 
	{
		s[k++]='\0';
		if (k==L+1) inword=true;
	}
	L=strlen(s);
	for(int i=0;i<L;i++)
	{
		if(i==0&& s[i]>96&&s[i]<123)	s[i]=s[i]-32;
		if(s[i]!=' '&&s[i-1]==' '&&s[i]>96&&s[i]<123) s[i]=s[i]-32;
	}
	//printf("%d",L);
}
int main()
{
	int s;
	motel A;
	customer x,y;
	int i;
	char fileName[] = "Danhsach.txt";
	A.Create();
	// tao 1 khach hang de tien test
	strcpy(y.name,"thanh nhat");
	strcpy(y.ID,"20133076");
	y.year=2002;
	strcpy(y.home,"quang ngai");

	//A.Rent(Info(x),sophong(i));// sophong lay so phong, Info lay thong tin


	
	//doc tu file	
	A.docFile(fileName);
	//ham show danh sach cac phong
	A.ShowCustomer();
	//mot ngay da troi qua
	A.oneday();
	// khach o phong 29 yeu cau chuyen qua phong 31
	A.Change(29,31);
	A.oneday();
	// khach o phong 31 checkout
	A.Pay(31);
	//ghi file
	A.ghiFile(fileName);
}
