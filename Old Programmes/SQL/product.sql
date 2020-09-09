create table Customer(
	cid varchar(10),
	cname varchar(15),
	city varchar(15),
	discount number(3),
	constraint customer_pk primary key (cid),
	constraint cid_dom check(cid like 'c%'),
	constraint discount_dom check(discount between 0 and 100)
);
create table Agents(
	aid varchar(10),
	aname varchar(15),
	city varchar(15),
	percent_commision number(3),
	constraint agents_pk primary key (aid),
	constraint aid_dom check(aid like 'a%'),
	constraint percent_commision_dom check(percent_commision between 0 and 100)
);
create table Products(
	pid varchar(10),
	pname varchar(15),
	city varchar (15),
	quantity number(10,5),
	price number(10,2),
	constraint products_pk primary key (pid),
	constraint pid_dom check(pid like 'p%'),
	constraint quantity_dom check(quantity>=0),
	constraint price_dom check(price>=0)
);
create table Orders(
	orderno integer,
	month number(2),
	cid varchar(10),
	aid varchar(10),
	pid varchar(10),
	quantity number(10,5),
	Rupees number(10,2),
	constraint orders_pk primary key (orderno),
	constraint month_dom check (month between 1 and 12),
	constraint orders_quantity_dom check(quantity>=0),
	constraint Rupees_dom check(Rupees>=0),
	constraint cid_ref foreign key (cid) references Customer(cid) on delete cascade,
	constraint aid_ref foreign key (aid) references Agents(aid) on delete set null,
	constraint pid_ref foreign key (pid) references Products(pid) on delete cascade
);

insert into Customer (cid,cname,city,discount) values('&cid','&cname','&city',&discount);
c01
Ram
Kolkata
10
/
c02
Amal
Delhi
10
/
c03
Bimal
Mumbai
5
/
c16
Shyam
Kolkata
20
insert into Agents (aid,aname,city,percent_commision) values('&aid','&aname','&city',&percent_commision);
a01
Jadu
Mumbai
70
/
a02
Madhu
Delhi
30
/
a03
Kamal
Delhi
50
/
a04
Shyamal
Kolkata
80
/
a05
Nilesh
Kolkata
80
/
a06
Nilanjan
Kolkata
80
insert into Products (pid,pname,city,quantity,price) values('&pid','&pname','&city',&quantity,&price);
p01
ABC
Kolkata
5000
50
/
p02
XYZ
Kolkata
5000
50
/
p03
PQR
Asansol
5000
50
/
p16
PQR
Asansol
5000
50
insert into Orders (orderno,month,cid,aid,pid,quantity,Rupees) values(&orderno,&month,'&cid','&aid','&pid',&quantity,&Rupees);
1
5
c01
a01
p01
10
500
/
2
5
c02
a01
p01
10
100
/
3
6
c03
a02
p01
20
200
/
4
7
c03
a02
p02
30
100
/
5
5
c03
a02
p03
10
300
/
6
8
c03
a03
p01
50
100
/
7
5
c03
a03
p02
140
300
/
8
1
c03
a03
p03
10
100
/
9
2
c03
a05
p01
15
400
/
10
2
c16
a06
p03
15
400
/
11
2
c16
a06
p16
15
400
/
12
5
c01
a01
p16
10
500
 
"Get the names of the Agents with a name beginning with the letter 'N' who does not place Orders for any product in Asansol."

select aname as "Agent Name" 
from agents 
where Agents.aname like 'N%' and
aid not in
	(
		select orders.aid from
		orders inner join 
		(
			select pid from products where city like 'Asansol'
		)
		using(pid)
	);

select aname as "Agent Name" 
from Agents inner join (
	(
		select aid 
		from Agents
	)
	minus 
	(
		select orders.aid
		from orders inner join products
		using(pid)
		where products.city like 'Asansol'
	)
)
using(aid)
where Agents.aname like 'N%';

"Find all (cid,aid,pid) triples for Customer,agent,product combinations. no two of which are in the same city"
select Customer.cid,temp.aid,temp.pid
from Customer inner join (
	select  Agents.aid,products.pid,Agents.city,products.city as city1 
	from Agents inner join products
	on Agents.city<>products.city
)temp
on (Customer.city<>temp.city 
	AND customer.city<>temp.city1) ;


"Get cids of customers who order product p01 and product p16"

(select orders.cid from
orders where orders.pid like 'p01')
INTERSECT
(select orders.cid from
orders where orders.pid like 'p16') ;

"Find the names of Agents who has order for all Products ordered by customer c03, the Agents names must be in sorted order."

select Agents.aname from
Agents where Agents.aid in (
select agents.aid from
agents inner join orders 
on (agents.aid=orders.aid and orders.cid like 'c03')
group by agents.aid 
having count(agents.aid)=(
	select count(distinct pid) from
	orders where cid like 'c03'
	)
) order by agents.aname asc;

"Display all the pairs of aids for agents who live in the same city"

select Agents.aid as aid1,temp.aid as aid2
from Agents inner join Agents temp
on (Agents.city=temp.city and Agents.aid<>temp.aid)
;
