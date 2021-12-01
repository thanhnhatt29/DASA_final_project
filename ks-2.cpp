#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<iostream>
#include <iomanip>
using namespace std;
#define N 50



struct Customer		//Khai báo 'câu trúc thông tin khách hàng 
{
	char Name[20];	//Ten
	char ID[15];	//CMND 
	int Year;		//Nam Sinh 
	int Age;		//Tuoi 
	char Home[20];	//Que Quan
};

struct Employee		//Khai báo 'câu trúc thông tin nhân viên khách san.
{
	char Name[20];	
	char ID[15];	
	int Year;		
	int Age;		
	char Home[20];	
	int Job;		//Cong Viec
	int Salary;		//Luong
	int Income;		//Thu Nhap
};

struct Inroom		//khai báo 'câu trúa thông tin phòng trong khách san.
{
	Customer Cus;		//khai báo Customer Khach de truy cap thong tin khach hang
	//init();
	int Bed;		//(1: giuong don || 2: giuong doi)
	bool Status;	//(true = co nguoi dang o  || false = phong trong (empty))
	bool Vip;		//(true = phong Vip (deluxe) || false = phong thuong (standard))
	int Price;		//(giá phòng)
	int Bill=0;		//(hoa don cua phong)
	int Fixing;		//(sua chua phong)
};

class Motel{
	
public:	//Cac chuc nang chinh:

	
	//Thông tin phòng trong khach san:
	Inroom Room[N];	
	
	//Tong doanh thu:
	int Revenue;	
	
	//Nhan vien:
	Employee NV[N];
	int Len=0;						//Length: so luong nhan vien
	void Hire(Employee emp);		//hàm thuê nhân viên moi
	void ShowEmployee();			//hien thi thong tin nhan vien
		
	//Thao tac thong tin tren phong:
	void Create();					//khoi tao gia tri tung phong (Bed,Status,...)
	void Rent(Customer x,int to);	//hàm dang ky khách thuê phòng
	void Pay(int from);				//hàm thanh toán tien phong
	void Change();					//hàm doi phòng cho khách
	
	
	//Hien thi thong tin:
	void ShowCustomer();			//hien thi thong tin khach hang
	void Map();						//hien thi danh sach phong khach san
	
	
	//Cac loai dich vu:
	void Complain(int i);			//ham "than phiên`": dùng khi có các vân de xay ra voi phong nhu chuyen phong,...
	void Maintain(int i);			//ham "bao tri": dùng khi bao trì phòng
	void Service(int i);			//ham "dich vu": cac dich vu phu tro khach hang
	
	
	//Cac chuc nang phu tro:
	bool CheckID(char s[15]);		//kiem tra CMND hop le
	void ResetInfo(int i);			//xoa toan bo thong tin hien tai cua phòng
	void OneDay();					//ham dung de qua ngay moi
	
	
	//Thao tac thong tin tren file:
	void DocFile(char fileName[]);	//doc thong tin tu file
	void GhiFile(char fileName[]);	//ghi thong tin vao file
};



void printLine(int n); 
void CheckName( char *s);
int RoomNumber(int i);
Customer InfoCus(Customer x);
//void checkname( char *s);
int keyPress(int Clear); 
Employee InfoEmp(Employee emp);




int main()
{
	
	Motel A;
	A.Create();

	Customer x;
	Employee emp;
	int i;
	
	char fileName[] = "Danhsach.txt";
	
	
	A.Map();
	
	int key;
	while(true) 
	{
		cout << "\n\t\t    Motel INFORMATION MANAGEMENT \n";
		cout << "\t\t=====================MENU===================\n";
		cout << "\t\t||  1. Read data from file.               ||\n";
		cout << "\t\t||  2. Rent a room.                       ||\n";
		cout << "\t\t||  3. Pay a room.                        ||\n";
		cout << "\t\t||  4. Change room.                       ||\n";
		cout << "\t\t||  5. Complain.                          ||\n";
		cout << "\t\t||  6. Maintain.	                       ||\n";
		cout << "\t\t||  7. Show list of customers.            ||\n";
		cout << "\t\t||  8. Service.                           ||\n";
		cout << "\t\t||  9. Write customer list to file.       ||\n";
		cout << "\t\t|| 10. One day pass.                      ||\n";
		cout << "\t\t|| 11. Motel map.                         ||\n";
		cout << "\t\t|| 12. Total income of the Motel.         ||\n";
		cout << "\t\t|| 13. Hire employee.                     ||\n";
		cout << "\t\t|| 14. Show list of employees.             ||\n";		
		cout << "\t\t||  0. Thoat                              ||\n";
		cout << "\t\t======================END==================\n";
		key=keyPress(1);

		switch(key)
		{
			case 1:
				//Doc du lieu tu file
				A.DocFile(fileName);
				break;
			case 2:
				//Hien thi so do va cho phep thue phong
				A.Map();
				A.Rent(InfoCus(x),RoomNumber(i));
				break;
			case 3:
				//Tra phong va thanh toan
				A.Pay(RoomNumber(i));
				break;
			case 4:
				//Hien thi so do va cho phep chuyen phong
				A.Map();
				A.Change();
				break;
			case 5:
				//Nhan y kien ve phong
				A.Complain(RoomNumber(i));
				break;
			case 6:
				//Thuc hien bao duong phong
				A.Maintain(RoomNumber(i));
				break;
			case 7:
				//Hien thi danh sach khach hang va phong tuong ung
				A.ShowCustomer();
				break;
			case 8:
				//Dich vu phong
				A.Service(RoomNumber(i));
				break;
			case 9:
				//Ghi thong tin ra file
				A.GhiFile(fileName);
				break;
			case 10:
				//Qua mot ngay moi
				A.OneDay();
				break;
			case 11:
				//Hien thi so do phong va tinh trang, cac loai phong va gia phong
				A.Map();
				break;
			case 12:
				//Hien thi tong doanh thu
				printf("Doanh thu tinh toi hien tai:%d",A.Revenue);
				break;
			case 13:
				//Thue nhan vien
				A.Hire(InfoEmp(emp));
				break;
			case 14:
				//Hien thi danh sach nhan vien
				A.ShowEmployee();
				break;
			case 0:
				//Thoat
				printf("\nDa thoat chuong trinh!");
				return 0;
			default:
				printf("Khong co chuc nang nay!\nVui long chon chuc nang trong menu");
				break;
		}
		
		keyPress(0);
	}
	
	return 0;
}


void Motel::Create(){
	//Bed = 1 => giuong don, Bed = 2 => giuong doi
	//Vip = false => phong tieu chuan, Vip = true => phong Vip
	
	
	for(int i=1;i<=N;i++)
	{
		if(i<=10)
		{
			Room[i].Bed=1;
			Room[i].Vip=false;
			Room[i].Price=200000;
			Room[i].Status=false;
			Room[i].Fixing=0;
		}
		else if(i<=20)
		{
			Room[i].Bed=2;
			Room[i].Vip=false;
			Room[i].Price=400000;
			Room[i].Status=false;
			Room[i].Fixing=0;
		}
		else if(i<=30)
		{
			Room[i].Bed=1;
			Room[i].Vip=true;
			Room[i].Price=500000;
			Room[i].Status=false;
			Room[i].Fixing=0;
		}
		else
		{
			Room[i].Bed=2;
			Room[i].Vip=true;
			Room[i].Price=1000000;
			Room[i].Status=false;
			Room[i].Fixing=0;
		}
	}
	
}


// ham dung de thue 1 phong
void Motel::Rent(Customer x, int to){
	int i = to; //to la so phong` (room-number) nhap tu ben ngoai
	
	if( Room[i].Status == false )
	{
		
		if( x.Age<18 )
		{
			printf("Khong du tuoi thue!");
			return;
		}
		else if( CheckID(x.ID)==true )
		{
			printf("ID khong hop le!");
			return;
		}
		
		Room[i].Cus=x;
		Room[i].Status=true;	
			
	}
	else
	{
		printf("Phong nay da co khach!");
	}
}



// ham thanh toan cho khach
void Motel::Pay(int from)
{
	int i = from;//so phong` (room-number) can thanh toan

	if( Room[i].Status == true )
	{
		if( Room[i].Bill == 0 )
		{
			Revenue += Room[i].Price;
			printf("Da thanh toan phong %d voi gia tien %d", i, Room[i].Price);
			printf("\nDoanh thu+%d", Room[i].Price);
		}
		else
		{
			Revenue += Room[i].Bill;
			printf("Da thanh toan phong %d voi gia tien %d", i, Room[i].Bill);
			printf("\nDoanh thu+%d", Room[i].Bill);
		}
		
		ResetInfo(i); //xoa thong tin phong
	}
	else 
	{
		printf("Phong trong");
	}
}



// chuyen so phong cho khach
void Motel::Change()
{
	printf("Nhap phong hien tai ");
	int from = RoomNumber(from);
	printf("Nhap phong chuyen toi ");
	int to = RoomNumber(to);
	if( Room[from].Status == true && Room[to].Status == false )	//kiem tra tinh trang phong
	{
		Room[from].Status = false;
		Rent(Room[from].Cus,to);
		Room[to].Bill = Room[from].Bill;
		ResetInfo(from);
		printf("Da chuyen phong");
		Complain(from);
	}
	else printf("Thong tin khong hop le\n");
}


//xoa thong tin khach hang tai phong i
void Motel::ResetInfo(int i)
{
	
	Room[i].Bill = 0;
	Room[i].Cus.Age = Room[i].Cus.Home[20] = Room[i].Cus.ID[15] = Room[i].Cus.Name[20] = Room[i].Cus.Year = NULL;
	Room[i].Status = false;	

}


// ham show thong tin nhung phong dang duoc thue va thong tin khach tai phong do
void Motel::ShowCustomer()
{
	printLine(110);
	cout << "|TT|   \tID\t   |\t Ten \t\t|Nam Sinh|Que Quan            |";
	
	for (int i = 1; i <= N ; i++)
	{
		// in Customer thu i ra man hinh
		if (!Room[i].Status) continue;
	
		printf("\n|%-2d", i);
		printf("|%15s", Room[i].Cus.ID);
		printf("|%-20s", Room[i].Cus.Name);
		printf("|%-8d", Room[i].Cus.Year);
		printf("|%-20s|", Room[i].Cus.Home);
		
	}
	printLine(110);
}

void Motel::ShowEmployee()
{
//	printLine(110);
	cout << "|      ID       |         Ten        | Namsinh|          Que quan  |Luong theo ngay|     Chuc vu        |";
	
	for (int i = 0; i < Len ; i++)
	{
		// in Employee thu i ra man hinh
//		continue;
		
	
		printf("\n|%15s", NV[i].ID);
		printf("|%-20s", NV[i].Name);
		printf("|%-8d", NV[i].Year);
		printf("|%-20s", NV[i].Home);
		printf("|%15d",NV[i].Salary);
		switch(NV[i].Job)
		{
			case 1:
				printf("|            Tiep tan|");
				break;
			case 2:
				printf("|              Tap vu|");
				break;
			case 3:
				printf("|  Nhan vien sua chua|");
				break;
		}
		
	}
//	printLine(110);
}

void Motel::Service(int i)
{
	int a;
	int b;
	if(Room[i].Status==true)
	{
		printf("\nDanh sach dich vu:\n1.Don dep phong\n2.Giat ui\n3.Don ly chen\n4.Thuc an\5.Thuoc la\n6.Dich vu ngoai luong\n7.Thue xe\nNhap lua chon:");
		scanf("%d",&a);
		switch(a)
		{
			case 1:
				printf("Da thuc hien don dep. ");
				printf("Phi dich vu la: 50,000. ");
				
				Room[i].Bill += 50000;
				break;
			case 2:
				printf("Da thuc hien giat ui. ");
				printf("Phi dich vu la: 70,000. ");
				
				Room[i].Bill += 70000;
				break;
			case 3:
				printf("Da thuc hien don ly chen. ");
				printf("Phi dich vu la: 50,000. ");
				
				Room[i].Bill += 50000;
				break;
			case 4:
				printf("Thuc an da duoc don len. ");
				printf("Chi phi thuc an va phi dich vu: 1,000,000. ");
				
				Room[i].Bill += 1000000;
				break;
			case 5:
				printf("Thuoc la da duoc phuc vu. ");
				printf("Chi phi san pham va phi dich vu: 20,000. ");
				
				Room[i].Bill += 20000;
				break;
			case 6:
				printf("Da phuc vu. ");
				printf("Chi phi dich vu: 600,000. ");
				
				Room[i].Bill += 600000;
				break;
			case 7:
				{
					printf("\n1.Xe may\n2. Xe oto\nNhap lua chon: ");
					scanf("%d",&b);
					switch(b){
						case 1:
							printf("Da cho thue xe may");
							printf("Chi phi dich vu: 180,000");
							Room[i].Bill += 180000;
							break;
						case 2:
							printf("Da cho thue xe oto");
							printf("Chi phi dich vu: 1,200,000");
							Room[i].Bill += 1200000;
							break;
						default:
							printf("Khong co lua chon nay");
							break;
					}
					break;
				}
				
			default:printf("Khong co gi");
		
		}
	}
	else
	{
		printf("Phong khong co khach");
	}
}

//ham than phien ve cac van de cua phong 
void Motel::Complain(int i)
{
	int a;
	printf("\nVan de gap phai:\n1.Hong dieu hoa\n2.Phong am thap\n3.Phong cach am kem\n4.Giuong bi hong\n5.Phong khong co nuoc\n0.Khong van de\nNhap lua chon:");
	scanf("%d",&a);
	
	switch(a)
	{
		case 1:
			Room[i].Fixing=1;
			break;
		case 2:
			Room[i].Fixing=2;
			break;
		case 3:
			Room[i].Fixing=3;
			break;
		case 4:
			Room[i].Fixing=4;
			break;
		case 5:
			Room[i].Fixing=5;
			break;
		default:printf("Khong co gi");
	}
}

//ham bao tri de sua chua cac van de cua phong
void Motel::Maintain(int i)
{
	
	switch( Room[i].Fixing )
	{
		case 1:
			printf("Dieu hoa da duoc sua.");
			Revenue -= 500000;
			break;
		case 2:
			printf("Da sua chua nhung khu vuc am thap.");
			Revenue -= 450000;
			break;
		case 3:
			printf("Da gia co tuong va cac vat dung cach am.");
			Revenue -= 400000;
			break;
		case 4:
			printf("Da sua lai giuong.");
			Revenue -= 350000;
			break;
		case 5:
			printf("Da sua chua he thong nuoc.");
			Revenue -= 300000;
			break;
		case 0:
			printf("Khong co van de.");
			break;
		default:
			printf("Khong tim ra su co.");
			Room[i].Fixing=0;
			
	}
	
}

//ham hien thi so do phong khach san
void Motel::Map()
 {
 	
 	for(int i=N/10; i>0; i--)
 	{
 		printf("\n\n");
 		
 		for(int j=(i-1)*10+1;j<=i*10;j++)
		{
			printf("  [%2d]:",j);
			
		 	if(Room[j].Status==true)
		 	{
		 		printf("R ");
			}			
			if(Room[j].Fixing==true)
			{
				printf("F ");
			}
			else if(Room[j].Status==false)
			{
			printf("E ");
			}
			
		}
	}
	
	printf("\n\nNote:	  R:Rented  F:Fixing  E:Empty");
	
	printf("\n[01-10]:(1 Bed-Common):200,000\n[11-20]:(2 Bed-Common):400,000\n[21-30]:(1 Bed-Luxury):500,000\n[31-50]:(2 Bed-Luxury):1,000,000\n");
	
 }
 
 
 //ham doc thong tin tu file
void Motel::DocFile(char fileName[])
{
	
	FILE * fp;
	int a,i = 0;
	
	fp = fopen (fileName, "r");
	cout << endl;
	cout << "Chuan bi doc file: "<<fileName<<".............."<<endl; //puts(fileName);

	Customer x;
	while (fscanf(fp, "%2d %[^\t] %[^\t] %4d %[^\n]",&a, &x.Name,
 &x.ID, &x.Year, &x.Home) != EOF) 
	{
		CheckName(x.Name);
		Rent(x,a);
		i++;
	}
	
	cout << " So luong Khach hang co san trong file la: " << i << endl;
	printLine(40);
	
	fclose (fp);
	return ;
	
}

// su dung ham nay  de tang tong Bill theo tung ngay
void Motel::OneDay()
{
	for(int i=1; i <= 50; i++)
	{
		if(Room[i].Status == true)
		{
			Room[i].Bill += Room[i].Price;
		}
	}
	for(int j=0; j < Len; j++)
	{
		NV[j].Income += NV[j].Salary;
		Revenue -= NV[j].Salary;
	}
	
	printf("One day has passed.\n");
}

//ham kiem tra ID hop le
bool Motel::CheckID(char s[15])
{
	bool cus;
	bool emp;
	
	for(int i=0; i <= N; i++)
	{
		
		if( Room[i].Status == true )
		{
			if(strcmp(Room[i].Cus.ID,s)==0)
			{
				cus = true;
			}
		}
		
	}
	for(int j = 0; j < Len; j++)
	{
		if(strcmp(NV[j].ID,s))
		{
			emp = true;
		}
	}
	if( cus == true || emp == true || strlen(s)<9 )
	{
		return true;
	}
	
	return false;
}


void Motel::GhiFile(char fileName[]) 
{
	
	FILE * fp;
	fp = fopen(fileName, "w");
	
	for (int i = 1; i <= N; i++) 
	{
		if(!Room[i].Status) continue;
		fprintf(fp, "%2d %-s\t %-s\t %4d %-s\n",i, Room[i].Cus.Name, Room[i].Cus.ID, Room[i].Cus.Year, Room[i].Cus.Home);
	}
	
	fclose(fp);
}



void printLine(int n) 
{
	cout << endl;
	
	for (int i = 0; i < n; i++) 
	{
		cout << "=";
	}
	
	cout << endl;
}

int RoomNumber(int i)
{
	do{
		
		printf("\nNhap so phong:");
		scanf("%d",&i);
		
	}while( i<1 || i>N );
	
	return i;
}

void CheckName( char *s) // chuan hoa chuoi
{
	
	int L = strlen(s);
	//
	if ( s[L-1] != 0 ) 
		s[L] = 0;
		
	bool inword = false;// qui uoc IW=false thi boqua, true moi lay
	int k = 0;
	char c;

	for(int i = 0; i < L; i++)
	{
		c = s[i];//lay chu trong chuoi
		if ( c != ' ' )
		{
			if ( inword == false )// neu c= chudautu thi chuyen IW=true, sau do lay tat ca chu cua tu do
				inword = true;
				s[k++] = c;
			//if (k==1) s[k-1]=s[k-1]-32;
		}
		else if ( inword == true )// khi da het chu, chuyen IW=false, chi lay 1 khoang trong sau do
		{
			inword = false;
			s[k++] = c;
		}
		if ( i == L-1 && s[i] != ' ') 
			inword = false;
		//xuatchuoi(s);
	}
	//printf("%d",k);
	
	while( inword == false ) 
	{
		s[k++] = '\0';
		if ( k == L+1 ) 
			inword=true;
	}
	
	L = strlen(s);
	for(int i = 0; i < L; i++)
	{
		if( i == 0 && s[i] > 96 && s[i] <123 )	
			s[i]=s[i]-32;
		if( s[i] != ' ' && s[i-1] == ' ' && s[i] > 96 && s[i] < 123 ) 
			s[i]=s[i]-32;
	}
	//printf("%d",L);
	
}


// get thong tin khach hang
Customer InfoCus(Customer x)
{
	fflush(stdin);
	
	printf("Nhap ten khac hang: ");
	gets(x.Name);
	CheckName(x.Name);
	
	printf("Nhap ID: ");
	gets(x.ID);
	
	printf("Nhap que quan: ");	
	gets(x.Home);
	
	printf("Nhap nam sinh: ");	scanf("%d",&x.Year);
	
	x.Age=2021-x.Year;
	
	return x;
}

Employee InfoEmp(Employee emp)
{
	fflush(stdin);
	
	printf("Nhap ten nhan vien: ");
	gets(emp.Name);
	CheckName(emp.Name);
	
	printf("Nhap ID: ");
	gets(emp.ID);
	
	printf("Nhap que quan: ");	
	gets(emp.Home);
	
	printf("Nhap nam sinh: ");	scanf("%d",&emp.Year);
	
	emp.Age = 2021-emp.Year;
	
	printf("Ung tuyen cong viec:\n1.Tiep tan\n2.Tap vu\n3.Nhan vien ki thuat\nNhap lua chon:");
	
	do
	{
		scanf("%d", &emp.Job);
	}while( emp.Job > 3 || emp.Job<1 );
	
	switch( emp.Job )
	{
		case 1:
			emp.Salary=200000;
			break;
		case 2:
			emp.Salary=150000;
			break;
		case 3:
			emp.Salary=220000;
			break;
			
	}
	
	return emp;
}

void Motel::Hire(Employee emp)
{
	
	if( emp.Age < 18 )
	{
		printf("Khong du tuoi");
	}
	else if( CheckID(emp.ID) == true )
	{
		printf("ID khong hop le");
	}
	else
	{
		NV[Len] = emp;
		Len++;
		printf("Da duoc nhan");
	}
	
	
}

int keyPress(int Clear) 
{
	if (Clear==0)
	{
		fflush(stdin);
		cout << "\n\nPress a key to continue....";
		getch();
		system("cls");
		return 0;
		
	}
	else
	{
		
		cout << "\n\nPress a key to do a function: ";
		int keyp;
		cin >> keyp;
		return keyp;
		
	}
}



