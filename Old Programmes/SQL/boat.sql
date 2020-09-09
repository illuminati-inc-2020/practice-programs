create table Sailors (
	sid Number(4),
	s_name varchar(20),
	rating Number(4),
	age Number(3),
	constraint sailor_pk primary key (sid),
	constraint sid_dom check (sid between 100 and 5000),
	constraint age_dom check (age > 0)
);
create table Boats (
	bid Number(3),
	bname varchar(20),
	color Varchar(6), 
	constraint boats_pk  primary key (bid),
	constraint bid_dom check (bid between 100 and 500),
	constraint color_dom check (color in ('Red','Green','Blue','Yellow'))
);
create table Reserves (
	sid Number(4),
	bid Number(3),
	day Number(1),
	constraint reserves_pk primary key (sid,bid,day),
	constraint sailor_ref foreign key (sid) references sailors(sid) on delete cascade,
	constraint boat_ref foreign key (bid) references Boats(bid) on delete set null,
	constraint day_dom check (day between 1 and 7)
);
insert into sailors(sid,s_name,rating,age) values(&sid,'&s_name',&rating,&age);
100
arin
50
40
/
101
arin
55
40
/
102
arinesh
40
40
/
103
arinshu
40
30
/
104
arinsha
70
44
/
105
brine
70
40
/
106
brian
56
40
/
107
mohit
50
40
/
108
ram
50
35
insert into Boats(bid,bname,color) values(&bid,'&bname','&color');
100
rosy
Green
/
200
shark
Red
/
201
oddi
Yellow
/
202
sharktooth
Red
insert into Reserves(sid,bid,day) values(&sid,&bid,&day);
100
100
2
/
101
100
3
/
102
100
4
/
102
200
5
/
102
202
6
/
105
200
7
/
106
100
1
/
107
201
2
/
107
200
2
/
107
202
2
/
107
100
2
/
107
200
3

"1.Find the names of sailors who have reserved boat 200."
select s_name
from Sailors inner join (
	select distinct sid
	from Boats inner join Reserves
	using(bid)
	where bid=200
)using(sid);

"2.Find sailors whose rating is better than some sailor called 'arin'"
select s_name
from Sailors
where rating>some(
	select rating
	from Sailors
	where s_name='arin'
);

"3.Find the names of sailors who are older than the average age of the sailors with a rating 50."
select s_name
from Sailors
where age>(
	select avg(age)
	from Sailors
	where rating=50
);

"4.Find the names of sailors who have reserved all the boats.;"
select s_name
from Sailors
where sid in (select sid
	from Sailors left outer join Reserves
	using(sid)
	group by sid
	having count(distinct bid)=(
		select count(bid)
		from Boats
	)
);

"5.Find the average age of sailors for each rating level that has at least two sailors.	"
select rating,avg(age) "average age"
from Sailors
group by rating
having rating in (
	select rating
	from Sailors
	group by rating
	having count(sid)>=2
);

"6.For each 'Red' boat find the number of reservations."
select bid,count(sid) "number of reservations"
from Boats left outer join Reserves
using(bid)
where color='Red'
group by bid;