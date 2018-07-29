/*#include<whatsmyidea.h>
	Building Maintenence and Management App*/

#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<iomanip.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>

struct account
{       char no[10];
	long double balance;
};

struct log
{	char des[10],username[10],password[10];
	};

struct date d;
void displaydate()
{       printf("The current date is: %02d/%02d/%4d\n",
		d.da_day, d.da_mon, d.da_year);
	}
struct time tm;
void displaytime()
{       printf("The current time is: %2d:%02d:%02d.%02d\n",
		tm.ti_hour, tm.ti_min, tm.ti_sec, tm.ti_hund);
	}

class flat
{	int nrooms,nbathrooms;
	char furnished;
	public:
		int rno;
		char util_billdone;
		int eleccount,watcount,gascount;
		char vacant;
		void rent();
		long double rrent;
		void getdata();
		void showdata();
		int getrooms()
		{	return nrooms;
			}
	};

void flat::getdata()
{	cout<<"Enter the room number : ";
	cin>>rno;
	vacant='Y';
	util_billdone='N';
	cout<<"Enter the no of rooms : ";
	cin>>nrooms;
	cout<<"Enter the no. of bathrooms : ";
	cin>>nbathrooms;
	furnished='Y';
	if(vacant== 'Y')
	{	if(nrooms==2)
			rrent = 100000;
		else
			rrent = 120000;
		}
	}

void flat::showdata()
{       cout<<setw(4)<<rno<<"  "<<setw(10)<<nrooms<<"  "<<setw(14)<<nbathrooms<<"   "<<setw(6)<<vacant<<"    "<<setw(9)<<furnished<<"    "<<setw(6)<<rrent<<endl;
	}

void create()
{ 	fstream fout("Flat.dat",ios::out|ios::binary/*Error due to this*/);
	flat f;
	int i;
	for(i=0;i<6;i++)
	{	f.getdata();
		fout.write((char*)&f,sizeof(f));
		}
	fout.close();
	}

void display()
{	fstream fin("Flat.dat",ios::in|ios::binary);
	flat f;
	cout<<"\t\t\tROOM DETAILS\n";
	cout<<setw(4)<<"R.No."<<"  "<<setw(10)<<"No.ofRooms"<<"  "<<setw(14)<<"No.ofBathRooms"<<"  "<<setw(6)<<"Vacant"<<"  "<<setw(9)<<"Furnished"<<"  "<<setw(4)<<"Rent"<<endl;
	while(fin.read((char*)&f,sizeof(f)))
		f.showdata();
	fin.close();
	getch();
	}

class person
{       public:
		char name[30],desig[10],eid[10]; //Standard id length??
		account acc;
	};

class tenant : public person
{       date duedate;
	double elecbill,watbill,gasbill;
	public:
		int roomno;
		long double duerent;
		char comp[10];
		void getdata();
		void showdata();
		void report();
		int vacate();
		void payrent();
		void paybills();
		char* getname()
		{	return name;
			}
		char* geteid()
		{	return eid;
			}
		void updateutilitybill(double a,double b,double c,int x,int y,int z)
		{       if(x==1)
				elecbill = a;
			if(y==1)
				watbill = b;
			if(z==1)
				gasbill = c;
			}
	};

void tenant::getdata()
{  	cout<<"Enter your name : ";
	gets(name);
	cout<<"Enter your Emirates ID : ";
	gets(eid);
	cout<<"Enter your company : ";
	gets(comp);
	cout<<"Enter your account no. : ";
	gets(acc.no);
	randomize();
	acc.balance = random(20000)+120000;
	strcpy(desig,"Tenant");
	}

void tenant::showdata()
{	cout<<setw(4)<<roomno<<"  "<<setw(25)<<getname()<<"  "<<setw(15)<<comp<<"  "<<setw(8)<<duerent<<"  "<<setw(12)<<geteid()<<"  "<<endl;
	}

void disptenants()
{	fstream fin("Tenantli.dat",ios::in|ios::binary);
	tenant t;
	int flag=-1;
	while(fin.read((char*)&t,sizeof(t)))
	{	flag=1;
		}
	fin.close();
	if(flag==1)
	{	fstream fin("Tenantli.dat",ios::in|ios::binary);
		cout<<"\n\t\t\tTENANT DETAILS\n";
		cout<<setw(4)<<"R.No."<<"  "<<setw(25)<<"Name"<<"  "<<setw(15)<<"Company"<<"  "<<setw(8)<<"Due Rent"<<"  "<<setw(12)<<"Emirates ID"<<"  "<<endl;
			while(fin.read((char*)&t,sizeof(t)))
		{	t.showdata();
			}
		fin.close();
		getch();
		}
	else
	{       clrscr();
		cout<<"No Tenant Details to display. You're Broke!! HAAHA!!";
		getch();
		}
	}

void flat::rent()
{       fstream fout("Tenantli.dat",ios::app|ios::binary);
	clrscr();
	tenant t;
	t.roomno=rno;
	t.duerent=rrent;
	vacant='N';
	t.getdata();
	fout.write((char*)&t,sizeof(t));
	fout.close();
	}

struct message
{	//the sub, place, date, etc.
	};

void displayvacant()
{	fstream fin("Flat.dat",ios::in|ios::binary);
	flat f;
	int flag=-1;
	while(fin.read((char*)&f,sizeof(f)))
		if(f.vacant=='Y')
			flag=1;
	fin.close();
	if(flag!=-1)
	{       fstream fin("Flat.dat",ios::in|ios::binary);
		cout<<"\t\t\tROOM DETAILS\n";
		cout<<setw(4)<<"R.No."<<"  "<<setw(10)<<"No.ofRooms"<<"  "<<setw(14)<<"No.ofBathRooms"<<"  "<<setw(6)<<"Vacant"<<"  "<<setw(9)<<"Furnished"<<"  "<<setw(4)<<"Rent"<<endl;
		while(fin.read((char*)&f,sizeof(f)))
			if(f.vacant=='Y')
				f.showdata();
		fin.close();
		}
	else
		cout<<"No vacant Flats available";
	getch();
	}

void rentflat(int n)
{       fstream fin("Flat.dat",ios::in|ios::binary);
	flat f;
	int flag=-1;
	while(fin.read((char*)&f,sizeof(f)))
		if(f.vacant=='Y'&&f.getrooms()>=n)
			flag=1;
	fin.close();
	if(flag==-1)
		cout<<"Sorry but no Flats are available";
	else
	{       fstream fin1("Flat.dat",ios::in|ios::binary);
		//fin1.seekg(0,ios::beg); //Not working :(
		cout<<"\n\t\t\tROOM DETAILS\n";
		cout<<setw(4)<<"R.No."<<"  "<<setw(10)<<"No.ofRooms"<<"  "<<setw(14)<<"No.ofBathRooms"<<"  "<<setw(6)<<"Vacant"<<"  "<<setw(9)<<"Furnished"<<"  "<<setw(4)<<"Rent"<<endl;
		while(fin1.read((char*)&f,sizeof(f)))
			if(f.vacant=='Y'&&f.getrooms()>=n)
				f.showdata();
		cout<<"\nEnter the Room no. you would like to rent. (Press 0 to cancel) : ";
		cin>>n;
		fin1.close();
		int flag2 = -1;
		if(n==0)
		{	cout<<"\nCanceled";
			getch();
			}
		fstream fin2("Flat.dat",ios::in|ios::binary);
		fstream fout("Temp.dat",ios::out|ios::binary);
		while(fin2.read((char*)&f,sizeof(f)))
		{       if(f.rno==n&&f.vacant=='Y')
			{       f.rent();
				flag2 = 1;
				}
			fout.write((char*)&f,sizeof(f));
			}
		fin2.close();
		fout.close();
		if (flag2==-1)
		{	cout<<"Error: Try Again";
			}
		remove("Flat.dat");
		rename("Temp.dat","Flat.dat");
		}
	}

void guest()
{	int ch;
	do
	{       clrscr();
		cout<<"Welcome to 'The Building'";
		cout<<"\nMenu : ";
		cout<<"\n\t1. View all flat details";
		cout<<"\n\t2. View vacant flats";
		cout<<"\n\t3. Rent a flat";
		cout<<"\n\t4. Go Back";
		cout<<"\nEnter your choice : ";
		cin>>ch;
		if(ch==4)
			break;
		switch(ch)
		{	case 1 : display();
				 break;
			case 2 : displayvacant();
				 break;
			case 3 : cout<<"\n\n";
				 int n;
				 cout<<"Enter required no. of rooms : ";
				 cin>>n;
				 if(n<=3&&n>=1)
					rentflat(n);
				 else
				 {	cout<<"Error. No rooms are available with "<<n<<" rooms.";
					cout<<"\nTry Again";
					}
				 break;
			case 4 : break;
			}
		}while(ch!=4);
	}
	  /*
void updaterent()
{	fstream fin("Flat.dat",ios::in|ios::binary);
	fstream fout("Temp.dat",ios::out|ios::binary);
	fstream fin1("Tenantli.dat",ios::in|ios::binary);
	fstream fout1("Templi.dat",ios::out|ios::binary);
	flat f;
	tenant t;
	float rper;
	int ch;
	cout<<"How do you want to change the rent?"<<endl;
	cout<<"\t1. Increase"<<endl;
	cout<<"\t2. Decrease"<<endl;
	cout<<"Enter your choice: ";
	cin>>ch;
	cout<<"By what percent do you want to change the rent?: ";
	cin>>rper;
	while(fin.read((char*)&f,sizeof(f)))
	{       int flag=-1;
		if(ch==1)
			f.rrent=f.rrent+((rper*0.01)*f.rrent);
		else if(ch==2)
			f.rrent=f.rrent-((rper*0.01)*f.rrent);
		fin1.seekg(0);
		while(fin1.read((char*)&t,sizeof(t)))
		{	if(t.roomno==f.rno)
			{	t.duerent = f.rrent;
				flag = 1;
				fout1.write((char*)&t,sizeof(t));
				}
			if(flag==1)
				break;
			}
		fout.write((char*)&f,sizeof(f));
		}
	fin.close();
	fout.close();
	fin1.close();
	fout1.close();
	remove("Tenantli.dat");
	rename("Templi.dat","Tenantli.dat");
	remove("Flat.dat");
	rename("Temp.dat","Flat.dat");
	}
	 */modifying
void updaterent()
{	fstream fin("Flat.dat",ios::in|ios::binary);
	fstream fout("Temp.dat",ios::out|ios::binary);
	flat f;
	tenant t;
	float rper;
	int ch;
	cout<<"How do you want to change the rent?"<<endl;
	cout<<"\t1. Increase"<<endl;
	cout<<"\t2. Decrease"<<endl;
	cout<<"Enter your choice: ";
	cin>>ch;
	cout<<"By what percent do you want to change the rent?: ";
	cin>>rper;
	fstream file("Tenantli.dat",ios::in|ios::app|ios::binary);
	while(fin.read((char*)&f,sizeof(f)))
	{       file.read((char*)&t,sizeof(t));
		int flag=-1;
		if(ch==1)
			f.rrent=f.rrent+((rper*0.01)*f.rrent);
		else if(ch==2)
			f.rrent=f.rrent-((rper*0.01)*f.rrent);
		if(t.roomno==f.rno)
		{	t.duerent = f.rrent;
			flag=1;
			}
		fout.write((char*)&f,sizeof(f));
		if(flag==1)
			file.write((char*)&t,sizeof(t));
		}
	fin.close();
	fout.close();
	file.close();
	remove("Flat.dat");
	rename("Temp.dat","Flat.dat");
	}

struct notice
{	date dt;
	char sub[50],body[120];
	};

void issuenotice()
{       fstream fout("Notice.dat",ios::app|ios::binary);
	cout<<"To issue a notice, please follow the instructions";
	notice n;
	//cout<<"\nEnter Issuing date : ";
	//cin>>n.dt.d>>n.dt.m>>n.dt.y;
	cout<<"Enter the subject : ";
	gets(n.sub);
	cout<<"Enter the body: ";
	gets(n.body);
	fout.write((char*)&n,sizeof(n));
	fout.close();
	}

void owner()
{       fstream fin("login.txt",ios::in);
	log l;
	char u[10],p[10];
	int flag=-1,access=0;;
	while(flag!=1)
	{       clrscr();
		fin>>l.des;
		if(!strcmpi(l.des,"owner"))
		{       flag=1;
			cout<<"Logging in as Owner";
			cout<<"\n\tEnter Username: ";
			cin>>u;
			cout<<"\tEnter Password: ";
			cin>>p;
			fin>>l.username>>l.password;
			if(!strcmpi(l.username,u)&&!strcmpi(l.password,p))
				access = 1;
			else
			{	cout<<"The Username and Password you entered dont match. Try Again.";
				getch();
				}
			}
		else
		{	fin>>l.username;
			fin>>l.password;
			}
		}
	fin.close();
	if(access==1)
	{	int ch;
		do
		{       clrscr();
			cout<<"Hello Owner Sahab";
			cout<<"\n\t1. Update Rent for all rooms";
			cout<<"\n\t2. Publish a notice";
			cout<<"\n\t3. View tenant details";
			cout<<"\n\t4. Log Out";
			cout<<"\nEnter your choice : ";
			cin>>ch;
			switch(ch)
			{	case 1 : updaterent();
					 break;
				case 2 : issuenotice();
					 break;
				case 3 : disptenants();
					 break;
				}
			}while(ch!=4);
		}
	}


//security-sec_flatmaintenence
struct m_flat
{       int m_roomno;
	char d_plumb,d_light,d_doors,d_windows,d_power,d_ac,d_gas,d_water,painting,d_exhaust,d_roof,d_firesystem;
	};


void create1()
{	fstream fout("Flatmai.dat",ios::out|ios::binary);
	fstream fin("Flat.dat",ios::in|ios::binary);
	flat f;
	m_flat mf;
	while(fin.read((char*)&f,sizeof(f)))
	{	mf.m_roomno = f.rno;
		mf.d_plumb = 'N';
		mf.d_light = 'N';
		mf.d_doors = 'N';
		mf.d_windows = 'N';
		mf.d_power = 'N';
		mf.d_ac = 'N';
		mf.d_gas = 'N';
		mf.d_water = 'N';
		mf.painting = 'N';
		mf.d_exhaust= 'N';
		mf.d_roof = 'N';
		mf.d_firesystem = 'N';
		fout.write((char*)&mf,sizeof(mf));
		}
	fin.close();
	fout.close();
	}

void display1()
{	fstream fin("Flatmai.dat",ios::in|ios::binary);
	m_flat mf;
	cout<<"\t\t\tMaintenence File\n";
	cout<<setw(4)<<"R.no"<<" "<<setw(5)<<"Plumb"<<" "<<setw(5)<<"Light"<<" "<<setw(3)<<"Gas"<<" "<<setw(5)<<"Water"<<" "<<setw(5)<<"Power"<<" "<<setw(3)<<"AC"<<" "<<setw(7)<<"Exhaust"<<" "<<setw(5)<<"Doors"<<" "<<setw(7)<<"Windows"<<" "<<setw(4)<<"Roof"<<" "<<setw(10)<<"Firesystem"<<endl;
	while(fin.read((char*)&mf,sizeof(mf)))
	{	cout<<setw(4)<<mf.m_roomno<<" "<<setw(5)<<mf.d_plumb<<" "<<setw(5)<<mf.d_light<<" "<<setw(3)<<mf.d_gas<<" "<<setw(5)<<mf.d_water<<" "<<setw(5)<<mf.d_power<<" "<<setw(3)<<mf.d_ac<<" "<<setw(7)<<mf.d_exhaust<<" "<<setw(5)<<mf.d_doors<<" "<<setw(7)<<mf.d_windows<<" "<<setw(4)<<mf.d_roof<<" "<<setw(10)<<mf.d_firesystem;
		cout<<endl;
		}
	fin.close();
	}

void sec_flatmaintenence()
{       display1();
	int n,flag=-1;
	//choose the room to clear the maintainance
	cout<<"Enter the room no. to be cleared(Press 0 to cancel) : ";
	cin>>n;
	fstream fin("Flatmai.dat",ios::in|ios::binary);
	fstream fout("Temp.dat",ios::out|ios::binary);
	m_flat mf;
	if(n==0)
	{	cout<<"\nCanceled";
		getch();
		}
	while(fin.read((char*)&mf,sizeof(mf)))
	{	if(mf.m_roomno==n)
		{       flag=1;
			if(mf.d_plumb=='Y')
			{	clrscr();
				cout<<"The plumb line has been damaged. Contact xxxxxxxx.\n";
				mf.d_plumb = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_light=='Y')
			{	clrscr();
				cout<<"Damage in the light system. Contact xxxxxxxx.\n";
				mf.d_light = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_gas=='Y')
			{	clrscr();
				cout<<"Gas jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_gas = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_water=='Y')
			{	clrscr();
				cout<<"Water jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_water = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_power=='Y')
			{	clrscr();
				cout<<"power jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_power = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_ac=='Y')
			{	clrscr();
				cout<<"AC jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_ac = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_exhaust=='Y')
			{	clrscr();
				cout<<"exhaust jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_exhaust = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_doors=='Y')
			{	clrscr();
				cout<<"doors jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_doors = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_windows=='Y')
			{	clrscr();
				cout<<"windows jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_windows = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_roof=='Y')
			{	clrscr();
				cout<<"roof jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_roof = 'N';
				cout<<"Clear notification";
				getch();
				}
			if(mf.d_firesystem=='Y')
			{	clrscr();
				cout<<"Firesystem jdgioihdoh. Contact xxxxxxxx.\n";
				mf.d_firesystem = 'N';
				cout<<"Clear notification";
				getch();
				}
			clrscr();
			cout<<"Cleared all notifications. \nMaintenence agency has ben notified. Repair work will be done in 5 hours";
			cout<<"\n\nGo Back";
			getch();
			}
		fout.write((char*)&mf,sizeof(mf));
		}
	if(flag==1)

	fin.close();
	fout.close();
	remove("Flatmai.dat");
	rename("Temp.dat","Flatmai.dat");
	clrscr();
	}

//void sec_buildmaintanance()
/*
struct m_building
{	int m_floorno;
	char d_light,d_door_window,d_ac,d_lift1,d_lift2,d_roof,d_garbage;
	}b;
	*/

void sec_buildmaintenence()
{     	int ch;
	do
	{       clrscr();
		cout<<"Report/Request maintenence service for : ";
		cout<<"\n\t1. Light";
		cout<<"\n\t2. Door and Window damages";
		cout<<"\n\t3. AC Repair and Cleaning";
		cout<<"\n\t4. Lift Repair";
		cout<<"\n\t5. Roof Leakage and Damage";
		cout<<"\n\t6. Garbage disposal system damage";
		cout<<"\n\t7. Go Back";
		cout<<"\nEnter your choice: ";
		cin>>ch;
		switch(ch)
		{	case 1 : //what to do here??
			case 2 :
			case 3 :
			case 4 :
			case 5 :
			case 6 : cout<<"The maintenence agency has been notified.";
				 cout<<"\nMaintainence services will be done shortly.";
				 cout<<"\nGo Back:";
				 getch();
			}
		}while(ch!=7);
		clrscr();
	}

void utilitybilling(flat f)
{       fstream fin("Tenantli.dat",ios::in|ios::binary);
	fstream fout("Temp1.dat",ios::app|ios::binary);
	tenant t;
	while(fin.read((char*)&t,sizeof(t)))
	{	if(f.rno==t.roomno)
		{       double elec,wat,gas;
			elec = f.eleccount*0.28;
			wat = f.watcount*0.035;
			gas = f.gascount*14.7;
			int x=1,y=1,z=1;
			t.updateutilitybill(elec,wat,gas,x,y,z);
			}
		fout.write((char*)&t,sizeof(t));
		}
	fin.close();
	fout.close();
	remove("Tenantli.dat");
	rename("Temp1.dat","Tenantli.dat");
	}

void utilitycount()
{       fstream fin("Flat.dat",ios::in|ios::binary);
	fstream fout("temp.dat",ios::out|ios::binary);
	flat f;
	int flag = -1;
	while(fin.read((char*)&f,sizeof(f)))
	{	if(f.util_billdone=='N')
		{       flag = 1;
			cout<<"Update utility count for room "<<f.rno<<" : \n";
			cout<<"Enter the electricity metre reading (kWh) : \n";
			cin>>f.eleccount;
			cout<<"Enter the water metre reading (IG) : \n";
			cin>>f.watcount;
			cout<<"Enter the gas count (units) : ";
			cin>>f.gascount;
			utilitybilling(f);
			f.util_billdone='Y';
			}
		fout.write((char*)&f,sizeof(f));
		}
	fin.close();
	fout.close();
	remove("Flat.dat");
	rename("temp.dat","Flat.dat");
	if(flag==-1)
	{	cout<<"Utility count has been updated for all flats";
		getch();
		}
	clrscr();
	}

void security()
{       clrscr();
	//Hello Security!!
	fstream fin("login.txt",ios::in);
	log l;
	char u[10],p[10];
	int flag=-1,access=0;;
	while(flag!=1)
	{	fin>>l.des;
		if(!strcmpi(l.des,"security"))
		{       flag=1;
			cout<<"Logging in as Security";
			cout<<"\n\tEnter Username: ";
			cin>>u;
			cout<<"\tEnter Password: ";
			cin>>p;
			fin>>l.username>>l.password;
			if(!strcmpi(l.username,u)&&!strcmpi(l.password,p))
				access = 1;
			else
			{	cout<<"The Username and Password you entered dont match. Try Again.";
				getch();
				}
			}
		else
		{	fin>>l.username;
			fin>>l.password;
			}
		}
	fin.close();
	if(access==1)
	{	int ch;
		do
		{       clrscr();
			cout<<"Check and update:\n";
			cout<<"\t1. Flat Maintainance Reports\n";
			cout<<"\t2. Building Maintainance Reports\n";
			cout<<"\t3. Utility Count\n";
			cout<<"\t4. Log Out\n";
			//average water consumption 550 litres
			//average elctricity consumption is 5000kWh
			//average gas consumption???
			cout<<"Enter your Choice : ";
			cin>>ch;
			if(ch==4)
				break;
			switch(ch)
			{	case 1 : sec_flatmaintenence();
					 break;
				case 2 : sec_buildmaintenence();
					 break;
				case 3 : utilitycount();
					 break;
				}
			}while(ch!=4);
		}
	}

/*------------Freya's Part-----------*/
void readnotice()
{	fstream fin("Notice.dat",ios::in|ios::binary);
	notice n;
	while(fin.read((char*)&n,sizeof(n)))
	{      //	cout<<"Date: "<<n.dt.d<<"/"<<n.dt.m<<"/"<<n.dt.y<<".";
		cout<<"\n\t\t\t\tNOTICE";
		cout<<"\n\n\t\tSub: ";
		puts(n.sub);
		cout<<"\n\n";
		puts(n.body);
		cout<<"\nPress any key to continue: ";
		getch();
		}
	fin.close();
	}

void tenant::report()
{	fstream fin("Flatmai.dat",ios::in|ios::binary);
	fstream fout("Temp.dat",ios::out|ios::binary);
	m_flat mf;
	int ch;
	while(fin.read((char*)&mf,sizeof(mf)))
	{	if(mf.m_roomno==roomno)
		{	do
			{       clrscr();
				cout<<"Request Maintenence Service for repairing: ";
				cout<<"\n\t1. Plumb Line";
				cout<<"\n\t2. Light ";
				cout<<"\n\t3. Gas ";
				cout<<"\n\t4. Water System";
				cout<<"\n\t5. Power and Electric Switches";
				cout<<"\n\t6. AC Cleaning, damage repair,etc.";
				cout<<"\n\t7. Exhaust Fan";
				cout<<"\n\t8. Doors";
				cout<<"\n\t9. Windows";
				cout<<"\n\t10. Roof";
				cout<<"\n\t11. Firesystem";
				cout<<"\n\t12. Go Back";
				cout<<"\nEnter your choice: ";
				cin>>ch;
				switch(ch)
				{	case 1 : mf.d_plumb = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 2 : mf.d_light = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 3 : mf.d_gas = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 4 : mf.d_water = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 5 : mf.d_power = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 6 : mf.d_ac = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 7 : mf.d_exhaust= 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 8 : mf.d_doors = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 9 : mf.d_windows = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 10: mf.d_roof = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					case 11: mf.d_firesystem = 'Y';
						 cout<<"\nReport forwarded succesfully.";
						 getch();
						 break;
					}
				}while(ch!=12);
			}
			fout.write((char*)&mf,sizeof(mf));
		}
		fin.close();
		fout.close();
		remove("Flatmai.dat");
		rename("Temp.dat","Flatmai.dat");
	}

int tenant::vacate()
{       char ch;
	clrscr();
	cout<<"Are you sure you want to vacate? (Y for yes, N for No) : ";
	cin>>ch;
	if(ch=='Y')
	{	fstream fin("Flat.dat",ios::in|ios::binary);
		fstream fout("TempFlat.dat",ios::out|ios::binary);
		flat f;
		while(fin.read((char*)&f,sizeof(f)))
		{	if(f.rno==roomno)
				f.vacant = 'Y';
			fout.write((char*)&f,sizeof(f));
			}
		fin.close();
		fout.close();
		remove("Flat.dat");
		rename("TempFlat.dat","Flat.dat");
		cout<<"\n\nYou have vacated your room. We wish you Good Luck!";
		getch();
		return 1;
		}
	else if(ch=='N')
	{	cout<<"\nYou have canceled your request to vacate";
		return 0;
		}
	else
	{	cout<<"Error. Try Again";
		return 0;
		}
	}


void tenant::payrent()
{    	int ch;
	do
	{       clrscr();
		cout<<"Do you wish to: ";
		cout<<"\n\t1. View your due rent.";
		cout<<"\n\t2. Pay due rent.";
		cout<<"\n\t3. Go Back.";
		cout<<"Enter your choice: ";
		cin>>ch;
		if(ch==1)
		{	cout<<"Your due rent is: "<<duerent;
			getch();
			}
		else if(ch==2)
		{	cout<<"Your due rent is: "<<duerent;
			cout<<"\nPayment has been done.";
			duerent = 0;
			getch();
			}
		}while(ch!=3);
	}

void tenant::paybills()
{	int x,y,z,ch1;
	fstream fin("Flat.dat",ios::in|ios::binary);
	flat f;
	while(fin.read((char*)&f,sizeof(f)))
	{       if(f.rno==roomno)
		{	if(f.util_billdone=='Y')
			{       do
				{	clrscr();
					cout<<"Select Utility: ";
					cout<<"\n\t1. Electricity.";
					cout<<"\n\t2. Water.";
					cout<<"\n\t3. Gas.";
					cout<<"\n\t4. Go Back.";
					cout<<"Enter your choice: ";
					cin>>ch1;
					if(ch1==4)
						break;
					char ch2;
					switch(ch1)
					{	case 1 : cout<<"Electricity Bill: "<<elecbill;
							 cout<<"\nWould you like to pay the rent? (Y for yes, N for no): ";
							 cin>>ch2;
							 if(ch2=='Y')
								x = 1;
							 else
								x = 0;
							 cout<<"\nYour Electricity Bill has been cleared";
							 getch();
							 break;
						case 2 : cout<<"Water Bill: "<<elecbill;
							 cout<<"\nWould you like to pay the rent? (Y for yes, N for no): ";
							 cin>>ch2;
							 if(ch2=='Y')
								y = 1;
							 else
								y = 0;
							 cout<<"\nYour Water Bill has been cleared";
							 getch();
							 break;
						case 3 : cout<<"Gas Bill: "<<elecbill;
							 cout<<"\nWould you like to pay the rent? (Y for yes, N for no): ";
							 cin>>ch2;
							 if(ch2=='Y')
								z = 1;
							 else
								z = 0;
							 cout<<"\nYour Gas Bill has been cleared";
							 getch();
							 break;
						}
					updateutilitybill(0,0,0,x,y,z);
					}while(ch1!=4);
				}
			else
				cout<<"The Bills have not been updated yet";
			}
		}
	}

void tenants()
{ 	clrscr();
	fstream fin("login.txt",ios::in);
	log l;
	char u[10],p[10];
	int flag=-1,access=0,n=0;
	cout<<"Logging in as Tenant";
	cout<<"\n\tEnter Username: ";
	cin>>u;
	while(flag!=1)  // poda
	{ 	fin>>l.des>>l.username;
		if(!strcmpi(l.username,u))
		{       flag=1;
			for(int i=0;l.des[i]!='\0';i++)
				n = n*10 + (int(l.des[i])-48);
			cout<<"\tEnter Password: ";
			cin>>p;
			fin>>l.password;
			if(!strcmpi(l.password,p))
				access = 1;
			else
			{	cout<<"The Username and Password you entered dont match. Try Again.";
				getch();
				}
			}
		else
			fin>>l.password;
		if(fin.eof())
			break;
		}
	fin.close();
	if(flag==-1)
	{	cout<<"\nError. Username does not exist.";
		getch();
		}
	int exist=-1;
	if(access==1)
	{       fstream fin("Tenantli.dat",ios::in|ios::binary);
		fstream fout("Templi1.dat",ios::app|ios::binary);
		tenant t;
		int chvacate = 0;
		while(fin.read((char*)&t,sizeof(t)))
		{	if(t.roomno==n)
			{       exist=1;
				int ch;
				do
				{	clrscr();
					cout<<"\nHello "<<t.getname()<<endl;
					cout<<"\t1. Read notices \n";
					cout<<"\t2. Request maintenence services \n";
					cout<<"\t3. Vacate your flat \n";
					cout<<"\t4. View/Pay rent \n";
					cout<<"\t5. Pay bills \n";
					cout<<"\t6. Log Out \n";
					cout<<"Enter your choice : ";
					cin>>ch;
					if(ch==6)
						break;
					switch(ch)
					{ 	case 1 : readnotice();
							 break;
						case 2 : t.report();
							 break;
						case 3 : chvacate = t.vacate();
							 break;
						case 4 : t.payrent();
							 break;
						case 5 : t.paybills();
							 break;
						}
					}while(ch!=6);
				    }
			if(!chvacate)
				fout.write((char*)&t,sizeof(t));
			}
		fin.close();
		fout.close();
		remove("Tenantli.dat");
		rename("Templi1.dat","Tenantli.dat");
		if(exist==-1)
		{	cout<<"Error. User does not exist.";
			getch();
			}
		}
	}

/*FREYA*/

void main()
{	clrscr();
	int ch;
				getdate(&d);     //Hehe extra
				//displaydate();
				gettime(&tm);
				//displaytime();
	create();  // reset
	display();
	create1();
	display1();
	getch();
	do    //login do
	{       clrscr();
		cout<<"\t\t_________Building______";
		cout<<"\n\nLogin as :\n";
		cout<<"\t1. Owner\n";
		cout<<"\t2. Security\n";
		cout<<"\t3. Tenant\n";
		cout<<"\t4. Guest\n";
		cout<<"\t5. Exit\n";
		cout<<"Enter your choice : ";
		cin>>ch;
		if(ch==5)
			exit(0);
		switch(ch)
		{	case 1 : owner();
				 break;
			case 2 : security();
				 break;
			case 3 : tenants();
				 break;
			case 4 : guest();
				 break;
			case 5 : exit(0);
			}
		}while(ch!=5); //login do
		disptenants();
		getch();
	}