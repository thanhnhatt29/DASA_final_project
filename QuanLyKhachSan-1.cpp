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
	int Income=0;		//Thu Nhap
};


// nhung bien tam giup chuong trinh
Customer x;
Employee emp;
int i, key;
char fileName[] = "Danhsach.txt";
char fileNameNV[] = "Nhanvien.txt";
char stat[] = "SaoKe.txt";



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
	int Revenue=0;	
	
	//Nhan vien:
	Employee NV[N];
	int Len=0;						//Length: so luong nhan vien
	void Hire(Employee emp);		//hàm thuê nhân viên moi
	void ShowEmployee();			//hien thi thong tin nhan vien
	void Fired(char *empid);
	void PaySalary();
	
		
	//Thao tac thong tin tren phong:
	void Create();					//khoi tao gia tri tung phong (Bed,Status,...)
	void Rent(Customer x,int to);	//hàm dang ky khách thuê phòng
	void Pay(int from);				//hàm thanh toán tien phong
	void Change();					//hàm doi phòng cho khách
	
	
	//Hien thi thong tin:
	void ShowCustomer();			//hien thi thong tin khach hang
	void Map();						//hien thi danh sach phong khach san
	void UpdateCusInfo(int roomid); // sua chua thong tin khach o phong roomid
	void ShowRoomInfo(int i);
	
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
	void DocFileNV(char fileNameNV[]);
	void GhiFileNV(char fileNameNV[]);
	void GhiThongKe(char stat[], char s[], int i, int y);
	void DocThongKe(char stat[]);
	
	//Cac ham tao menu
	void RoomManagement();
	void InformationManagement();
	void EmployeeManagement();
	void ServiceManagement();
	void DataManagement();
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
	// cac ham khoi tao phong, khach hang, nhan vien
	A.Create();
	A.DocFileNV(fileNameNV);
	A.DocFile(fileName);
	//A.Map();

	int key;
	while(true) 
	{
		cout << "\n\t\t    MOTEL MANAGEMENT \n";
		cout << "\t\t=====================MENU===================\n";
		cout << "\t\t||  1. Room Management.                   ||\n";
		cout << "\t\t||  2. Get & Update Information.          ||\n";
		cout << "\t\t||  3. Employee Management.               ||\n";
		cout << "\t\t||  4. Services.                          ||\n";
		cout << "\t\t||  5. Read & Write data to file.         ||\n";
		cout << "\t\t||  0. Exit.                              ||\n";
		cout << "\t\t======================END==================\n";
		key=keyPress(1);

		switch(key)
		{
			case 1:
				// Goi menu Room
				A.RoomManagement();
				break;
			case 2:
				//Goi menu Info
				A.InformationManagement();
				break;
			case 3:
				//Goi menu Employee
				A.EmployeeManagement();
				break;
			case 4:
				//Goi menu Service
				A.ServiceManagement();
				break;
			case 5:
				//Nhan y kien ve phong
				A.DataManagement();
				break;
			
			case 0:
				//Thoat
				// hien thi thong tin
				system("cls");
				cout << "\n\t\t\t****************************";
				cout << "\n\t\t\t* MOTEL MANAGEMENT PROJECT *";
				cout << "\n\t\t\t****************************";
				cout << "\n\n\t\tDeveloped By:";
				cout << "\t Phuoc las ngons && Nhatjj && Khang westside";
				getch();
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



//Menu RoomManagement
void Motel::RoomManagement()
{

	while (true)
	{

		system("cls");
		cout << "\n\t\t*************************";
		cout << "\n\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t      * ROOM MENU *";
		cout << "\n\t\t*************************";
		cout << "\n\n\n\t\t1.Book A Room";
		cout << "\n\t\t2.Check Out";
		cout << "\n\t\t3.Change To Another Room";
		cout << "\n\t\t0.Return";
		key=keyPress(1);

		switch (key)
		{

		case 1:	// thue phong
			Map();
			Rent(InfoCus(x),RoomNumber(i));
			break;

		case 2: // tra phong
			Pay(RoomNumber(i));
			break;

		case 3: // chuyen phong
			Map();
			Change();
			break;
	
		case 0: // khi quay ve menu chinh 
				// thi gia su 1 ngay troi qua
				// tuong tu voi nhung ham khac
			OneDay();
			return;

		default:
			{
	
				cout << "\n\n\t\tWrong choice.....!!!";
	
			}

		}
		keyPress(0);
	}

}



// Menu get & update motel information
void Motel::InformationManagement()
{

	while (true)
	{

		system("cls");
		cout << "\n\t\t*************************";
		cout << "\n\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t      * MOTEL MENU *";
		cout << "\n\t\t*************************";
		cout << "\n\n\n\t\t1.Show list of customers.";
		cout << "\n\t\t2.Map Room Allocated";
		cout << "\n\t\t3.Total income of the Motel";
		cout << "\n\t\t4.Update Customer information";
		cout << "\n\t\t5.Show Room information";
		cout << "\n\t\t0.Return";
		key=keyPress(1);

		switch (key)
		{

		case 1:	// hien thi list khach hang
			ShowCustomer();
			break;

		case 2: // hien thi map motel
			Map();
			break;
		case 3:
				//Hien thi tong doanh thu
				printf("\n\t\tDoanh thu tinh toi hien tai: %d",Revenue);
				break;
		case 4: // sua thong tin khach hang
			UpdateCusInfo(RoomNumber(i));
			break;
		case 5: // show thong tin phong
			ShowRoomInfo(RoomNumber(i));
			break;
		case 0: 
			OneDay();
			return;

		default:
			{
	
				cout << "\n\n\t\tWrong choice.....!!!";
	
			}

		}
		keyPress(0);
	}

}

// Menu Employee
void Motel::EmployeeManagement()
{
	while (true)
	{

		system("cls");
		cout << "\n\t\t*************************";
		cout << "\n\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t    * EMPLOYEE MENU *";
		cout << "\n\t\t*************************";
		cout << "\n\n\n\t\t1.Show list of Employees.";
		cout << "\n\t\t2.Hire employee.";
		cout << "\n\t\t3.Fire an employee with ID.";
		cout << "\n\t\t4.Paid salaries to employees.";
		cout << "\n\t\t0.Return";
		key=keyPress(1);

		switch (key)
		{

		case 1:	// hien thi list nhan vien
			ShowEmployee();
			break;

		case 2: // thue nhan vien
			Hire(InfoEmp(emp));
			break;
		case 3: // sa thai nhan vien
			printf("Nhap ID: ");
			cin>>emp.ID;
			Fired(emp.ID);
			break;
		case 4:
			PaySalary();
			break;
		case 0: 
			OneDay();
			return;

		default:
			{
	
				cout << "\n\n\t\tWrong choice.....!!!";
	
			}

		}
		keyPress(0);
	}
}



void Motel::ServiceManagement()
{
	while (true)
	{

		system("cls");
		cout << "\n\t\t*************************";
		cout << "\n\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t   * SERVICES MENU *";
		cout << "\n\t\t*************************";
		cout << "\n\n\n\t\t1.Complain.";
		cout << "\n\t\t2.Maintain.";
		cout << "\n\t\t3.Other Service.";
		cout << "\n\t\t0.Return";
		key=keyPress(1);

		switch (key)
		{

		case 1:	// phan nan
			Complain(RoomNumber(i));
			break;

		case 2: // sua chua
			Maintain(RoomNumber(i));
			break;
			
		case 3: // dich vu
			Service(RoomNumber(i));
			break;
			
		case 0: 
			OneDay();
			return;

		default:
			{
	
				cout << "\n\n\t\tWrong choice.....!!!";
	
			}

		}
		keyPress(0);
	}
}

// menu Data
void Motel::DataManagement()
{
	while (true)
	{

		system("cls");
		cout << "\n\t\t*************************";
		cout << "\n\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t      * DATA MENU *";
		cout << "\n\t\t*************************";
		cout << "\n\n\n\t\t1.Read data Customer from file.";
		cout << "\n\t\t2.Write data Customer to file.";
		cout << "\n\t\t3.Read data Employee from file.";
		cout << "\n\t\t4.Write data Employee to file.";
		cout << "\n\t\t5.Read data Statistic from file.";
		cout << "\n\t\t0.Return";
		key=keyPress(1);

		switch (key)
		{

		case 1:	// doc file tu Danhsach.txt
			DocFile(fileName);
			break;

		case 2: // ghi vao cung file
			GhiFile(fileName);
			break;
		case 3:	// doc file tu Danhsach.txt
			DocFileNV(fileNameNV);
			break;

		case 4: // ghi vao cung file
			GhiFileNV(fileNameNV);
			break;
			
		case 5: //doc file tu SaoKe.txt
			DocThongKe(stat);
			break;
				
		case 0: 
			OneDay();
			return;

		default:
			{
	
				cout << "\n\n\t\tWrong choice.....!!!";
	
			}

		}
		keyPress(0);
	}
}
// ham dung de thue 1 phong
void Motel::Rent(Customer x, int to){
	int i = to; //to la so phong` (room-number) nhap tu ben ngoai
	
	if( Room[i].Status == false )
	{
		
		if( x.Age<18 )
		{
			printf("\nKhong du tuoi thue!");
			return;
		}
		else if( CheckID(x.ID)==true )
		{
			printf("\nID khong hop le!");
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
			printf("\n\nDa thanh toan phong %d voi gia tien %d", i, Room[i].Price);
			printf("\nDoanh thu +%d", Room[i].Price);
		}
		else
		{
			Revenue += Room[i].Bill;
			printf("\n\nDa thanh toan phong %d voi gia tien %d", i, Room[i].Bill);
			printf("\nDoanh thu +%d", Room[i].Bill);
		}
		
		ResetInfo(i); //xoa thong tin phong
	}
	else 
	{
		printf("\nPhong trong");
	}
}



// chuyen so phong cho khach
void Motel::Change()
{
	printf("Nhap phong hien tai: ");
	int from = RoomNumber(from);
	printf("Nhap phong chuyen toi: ");
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
	
	Room[i].Bill =Room[i].Cus.Age =Room[i].Cus.Year =Room[i].Cus.Home[20] = Room[i].Cus.ID[15] = Room[i].Cus.Name[20] = 0;
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


void Motel::UpdateCusInfo(int roomid)
{ 
	if( Room[roomid].Status == true )
	{
		
		Customer x = InfoCus(x);
		if( x.Age<18 )
		{
			printf("\nKhong du tuoi thue!");
			return;
		}
		else if( CheckID(x.ID)==true )
		{
			printf("\nID khong hop le!");
			return;
		}
		
		Room[roomid].Cus=x;
			
	}
	else
	{
		printf("Phong trong!");
	}
}


void Motel::ShowRoomInfo(int i)
{
	cout<<"Thong tin phong "<<i;
	printLine(34);
	cout<<"|So giuong |Loai Phong |Gia Tien |"<<endl;
	printf("|%-10d", Room[i].Bed);
	if(Room[i].Vip) printf("|Vip        ");
	else printf("|Normal     ");
	printf("|%-9d|", Room[i].Price);
	printLine(34);
	
	
	
	cout<<"\n\nThong tin khach hang o phong "<<i;
	printLine(71);
	cout << "|TT|   \tID\t   |\t Ten \t\t|Nam Sinh|Que Quan            |";
	printf("\n|%-2d", i);
	printf("|%15s", Room[i].Cus.ID);
	printf("|%-20s", Room[i].Cus.Name);
	printf("|%-8d", Room[i].Cus.Year);
	printf("|%-20s|", Room[i].Cus.Home);
	printLine(71);
}


void Motel::Fired(char *empid)
{
	int j=0;
	for (int i = 0; i < Len ; i++)
	{
		if(strcmp(NV[i].ID,empid)==0)
		{
			j=i;
			break;
		}
	}
	cout<<"\nDa sa thai nhan vien: "<<NV[j].Name;
	for (int i = j; i < Len-1 ; i++)
	{
		strcpy(NV[i].Name,NV[i+1].Name);
		strcpy(NV[i].ID,NV[i+1].ID);
		strcpy(NV[i].Home,NV[i+1].Home);
		NV[i].Age=NV[i+1].Age;
		NV[i].Income=NV[i+1].Income;
		NV[i].Job=NV[i+1].Job;
		NV[i].Salary=NV[i+1].Salary;
		NV[i].Year=NV[i+1].Year;
	}
	Len--;
}
void Motel::ShowEmployee()
{
	printLine(110);
	cout << "|      ID       |         Ten        | Namsinh|          Que quan  |Luong theo ngay|     Chuc vu        |";
	
	for (int i = 0; i < Len ; i++)
	{
		// in Employee thu i ra man hinh
//		continue;
		
	
		printf("\n|%15s", NV[i].ID);
		printf("|%-20s", NV[i].Name);
		printf("|%8d", NV[i].Year);
		printf("|%20s", NV[i].Home);
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
	printLine(110);
}



void Motel::PaySalary()
{
	for(int i=0; i< Len;i++)
	{
		cout<<"Nhan Vien: "<<NV[i].Name<<" co luong tinh tu luc bat dau " <<NV[i].Income<<endl;
		Revenue -= NV[i].Income;
		NV[i].Income = 0;
	}
	cout<<"\nDa tra luong cho tat ca Nhan Vien";
	printf("\nDoanh thu hien tai con:%d",Revenue);
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
				
				GhiThongKe(stat,"don dep",i,50000);

				break;
			case 2:
				printf("Da thuc hien giat ui. ");
				printf("Phi dich vu la: 70,000. ");
				
				Room[i].Bill += 70000;
				
				GhiThongKe(stat,"giat ui",i,70000);
				
				break;
			case 3:
				printf("Da thuc hien don ly chen. ");
				printf("Phi dich vu la: 50,000. ");
				
				Room[i].Bill += 50000;
				
				//
				
				break;
			case 4:
				printf("Thuc an da duoc don len. ");
				printf("Chi phi thuc an va phi dich vu: 1,000,000. ");
				
				Room[i].Bill += 1000000;
				
				GhiThongKe(stat,"do an nhanh",i,1000000);
				
				break;
			case 5:
				printf("Thuoc la da duoc phuc vu. ");
				printf("Chi phi san pham va phi dich vu: 20,000. ");
				
				Room[i].Bill += 20000;
				
				GhiThongKe(stat,"thuoc la",i,20000);
				
				break;
			case 6:
				printf("Da phuc vu. ");
				printf("Chi phi dich vu: 600,000. ");
				
				break;
			case 7:
				{
					printf("\n1.Xe may\n2.Xe oto\nNhap lua chon: ");
					scanf("%d",&b);
					switch(b){
						case 1:
							printf("Da cho thue xe may");
							printf("Chi phi dich vu: 180,000");
							
							Room[i].Bill += 180000;
							
							GhiThongKe(stat,"thue xe may",i,180000);
							break;
						case 2:
							printf("Da cho thue xe oto");
							printf("Chi phi dich vu: 1,200,000");
							
							Room[i].Bill += 1200000;
							
							GhiThongKe(stat,"thue xe oto",i,1200000);
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
void Motel::DocFileNV(char fileNameNV[])
{
	
	FILE * fp;
	int a,i = 0;
	
	fp = fopen (fileNameNV, "r");
	cout << endl;
	cout << "Chuan bi doc file: "<<fileNameNV<<".............."<<endl; //puts(fileName);

	Employee x;
	while (fscanf(fp, "%[^\t] %[^\t] %4d %[^\t] %1d %6d\n", &x.Name,
 &x.ID, &x.Year, &x.Home,&x.Job,&x.Salary) != EOF) 
	{
		CheckName(x.Name);
		Hire(x);
		i++;
	}
	
	cout << " So luong Nhan vien co san trong file la: " << i << endl;
	printLine(40);
	
	fclose (fp);
	return ;
	
}

//ham doc file Statistic (thong ke)
void Motel::DocThongKe(char stat[]){
	FILE * fp;
	char s[500];
	
	fp = fopen (stat, "r");
	cout << endl;
	cout << "Chuan bi doc file: "<< stat <<".............."<<endl; //puts(fileName);
	
	
	while (fgets(s, 500, fp) != NULL)
    {
        printf("%s", s);
    }
	
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
	}
	
	printf("\n\t\tOne day has passed.\n");
}

//ham kiem tra ID hop le
bool Motel::CheckID(char s[15])
{
	if( strlen(s)<8 )
	{
		return true;
	}
	
	for(int i=0; i <= N; i++)
	{
		
		if( Room[i].Status == true )
		{
			if(strcmp(Room[i].Cus.ID,s)==0)
			{
				return true;
			}
		}
		
	}
	for(int j = 0; j < Len; j++)
	{
		if(strcmp(NV[j].ID,s)==0)
		{
			return true;
		}
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
	cout<<"Da ghi du lieu khach hang vao file thanh cong";
}

void Motel::GhiFileNV(char fileNameNV[]) 
{
	
	FILE * fp;
	fp = fopen(fileNameNV, "w");
	
	for (int i = 0; i < Len ; i++) 
	{
		fprintf(fp, "%-s\t %-s\t %4d %-s\t %d %d\n", NV[i].Name, NV[i].ID, NV[i].Year, NV[i].Home, NV[i].Job, NV[i].Salary );
	}
	
	fclose(fp);
	cout<<"Da ghi du lieu Nhan vien vao file thanh cong";
}

void Motel::GhiThongKe(char stat[], char s[], int i, int y){
	FILE * fp;
	fp = fopen(stat, "a");

	fprintf(fp, "Khach hang %s da su dung dich vu %s voi gia %d\n",Room[i].Cus.Name,s,y);
	
	fclose(fp);
	//printf("Da ghi lai thong tin sao ke");
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
		
		printf("\nNhap so phong: ");
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


// lay thong tin khach hang
Customer InfoCus(Customer x)
{
	fflush(stdin);
	
	printf("Nhap ten khach hang: ");
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
	if( CheckID(emp.ID) == true )
	{
		printf("ID khong hop le\n");
	}
	else
	{
		NV[Len] = emp;
		Len++;
		printf("Da duoc nhan\n");
	}
	
	
}

int keyPress(int Clear) 
{
	if (Clear==0)
	{
		fflush(stdin);
		cout << "\n\n\t\tPress a key to continue....";
		getch();
		system("cls");
		return 0;
		
	}
	else
	{
		
		cout << "\n\n\t\tPress a key to do a function: ";
		int keyp;
		cin >> keyp;
		return keyp;
		
	}
}



