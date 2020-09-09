create Table Hotel (
	hotel_no varchar(3),
	hotel_name varchar(10),
	city varchar(10),
	constraint hotel_pk primary key (hotel_no)
);
create table Room (
	room_no varchar(5),
	hotel_no varchar(3),
	type varchar(10),
	price Number(10,2),
	constraint room_pk primary key (room_no,hotel_no),
	constraint hotel_ref foreign key (hotel_no) references Hotel(hotel_no)
);
create table Guest(
	guest_no varchar(10),
	guest_name varchar(20),
	guest_address varchar(30),
	constraint guest_pk primary key (guest_no)
);
create table Booking (
	hotel_no varchar(3),
	guest_no varchar(10),
	datefrom date,
	dateto date,
	room_no varchar(5),
	constraint booking_pk primary key (guest_no,hotel_no,room_no),
	constraint hotel_booking_ref foreign key (hotel_no) references Hotel(hotel_no),
	constraint guest_ref foreign key (guest_no) references Guest(Guest_no),
	constraint room_ref	foreign key (room_no,hotel_no) references Room(room_no,hotel_no)
);
insert into hotel(hotel_no,hotel_name,city) values(&hotel_no,'&hotel_no','&city');
1
Rose
kolkata
/
2
Oberoy
kolkata
/
3
Taj
kolkata
/
4
ITC
kolkata
/
5
Citrus
asansol
/
6
Grand
asansol
insert into Room(room_no,hotel_no,type,price) values(&room_no,&hotel_no,'&type',&price);
1
1
luxury
10.23
/
2
1
luxury
10000.23
/
3
1
luxury
10000.23
/
4
1
luxury
10000.23
/
1
2
luxury
1000.23
/
2
2
luxury
100.23
/
3
2
luxury
100000.23
/
1
3
luxury
10000.23
/
2
5
simple
1000.23
/
2
3
double bed
1000.23
/
3
3
double bed
100000.23

/
4
5
double bed
1000.23
/
3
6
double bed
100000.23
/
4
6
double bed
1000.23
insert into Guest(Guest_no,guest_name,guest_address) values(&guest_no,'&guest_name','&guest_address');
1
d.roy
anickpur
/
2
e.roy
anickpur
/
3
r.roy
delhi
/
4
t.roy
mumbai
/
5
l.roy
anickpur
/
6
v.roy
mumbai
/
7
b.roy
chennai
/
8
dn.roy
anickpur
/
9
o.roy
anickpur 
/
10
b.roy
kolkata 
/
11
dn.roy
kolkata
/
12
o.roy
kolkata 
insert into Booking(hotel_no,guest_no,datefrom,dateto,room_no) values(&hotel_no,&guest_no,to_date('&datefrom','DD/MM/YY'),to_date('&dateto','DD/MM/YY'),&room_no);
1
1
1/9/11
2/10/11
1
/
2
2
1/9/11
2/10/12
2
/
1
6
1/9/11
2/10/12
4
/
1
5
1/9/11
2/10/11
2
/
2
3
1/9/12
2/10/12
1
/
6
5
1/9/11
2/10/11
4
/
6
4
1/9/11
2/2/12
3
insert into Booking(hotel_no,guest_no,datefrom,room_no) values(&hotel_no,&guest_no,to_date('&datefrom','DD/MM/YY'),&room_no);
1
9
1/9/11
3
/
6
2
12/12/11
4

"1.List the booking for which no 'dateto' has been specified."
select *
from Booking 
where dateto is null;

"2.List the number of rooms in each hotel in kolkata."
select hotel_no "Hotel no",count(room_no) "Number of rooms"
from Room right outer join (
	select hotel_no
	from Hotel
	where city='kolkata'
)using(hotel_no)
group by hotel_no;

"3.what is the loss of income from unoccupied rooms at each hotel today?"
select hotel_no,sum(price) "Loss of income today"
from Room inner join (
	(
		select room_no,hotel_no
		from Room
	)minus(
		select room_no,hotel_no
		from Booking
		where sysdate between datefrom and dateto
	)
)using(room_no,hotel_no)
group by hotel_no;

"4.List all double bed rooms with a price below Rs 15000-/ per night in descending order of price."
select *
from Room
where type='double bed'
and price<15000
order by price desc;

"5.List the name,address of all guests living in kolkata alphabetically ordered by name."
select guest_name,guest_address
from Guest inner join (
	select guest_no
	from Hotel inner join Booking
	using(hotel_no)
	where city='kolkata'
	and sysdate between datefrom and dateto
)using(guest_no)
order by guest_name;

"6.what is the total income from booking for the grand hotel."
select sum(price*duration) "Total income of Grand hotel"
from (
	select price,case when dateto is null then (sysdate-datefrom) else (dateto-datefrom) end as duration
	from Booking inner join Room
	using(room_no,hotel_no)
	where hotel_no in (
		select hotel_no
		from Hotel
		where hotel_name='Grand'
	)
);