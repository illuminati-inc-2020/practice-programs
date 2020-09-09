create table Aircraft(
	aid varchar(5) primary key,
	type varchar(15)
);
create table Flights(
	flno number primary key,
	aid varchar(5) references Aircraft(aid),
	company varchar(15)
);
create table Employee(
	eid varchar(5) primary key,
	ename varchar(15),
	salary number(15,2) check (salary>=0.00)
);
create table Certified(
	eid varchar(5) references Employee(eid),
	aid varchar(5) references Aircraft(aid)
);
create table Schedule(
	eid varchar(5) references Employee(eid),
	flno number references Flights(flno),
	source_city varchar(15),
	destination_city varchar(15),
	schdate_date date
);

insert into Aircraft values('A1','Jet');
insert into Aircraft values('A2','Turbo');
insert into Aircraft values('A3','Jet');
insert into Aircraft values('A4','Jet');
insert into Aircraft values('A5','Helicopter');
insert into Aircraft values('A6','Jet');

insert into Flights values(1,'A1','Boeing');
insert into Flights values(2,'A2','JumboJet');
insert into Flights values(3,'A2','JumboJet');
insert into Flights values(4,'A3','AirBus');
insert into Flights values(5,'A1','Boeing');
insert into Flights values(6,'A6','Cruiser');
insert into Flights values(7,'A5','AirBus');
insert into Flights values(8,'A4','AirBus');

insert into Employee values('E1','Dibas',150000.00);
insert into Employee values('E2','Rakesh',170000.00);
insert into Employee values('E3','Dibyayan',120000.00);
insert into Employee values('E4','Asif',130000.00);
insert into Employee values('E5','Romit',50000.00);
insert into Employee values('E6','Sujoy',100000.00);
insert into Employee values('E7','Anirudh',100000.00);

insert into Schedule values('E1',1,'Kolkata','London',to_date('11/11/11','DD/MM/YYYY'));
