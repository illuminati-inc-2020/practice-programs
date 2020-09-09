create table customer_tr(
	cust_id number(4),
	cust_name varchar(15),
	annual_revenue number(10) default 5000,
	cust_type varchar(12) ,
	constraint cust_pk primary key(cust_id),
	constraint cust_id_chk check(cust_id between 100 and 5000),
	constraint cust_type_chk check(cust_type in ('manufacturer','wholesaler','retailer'))
);
create table truck(
	truck_no varchar(10),
	driver_name varchar(15),
	constraint truck_pk primary key (truck_no,driver_name)
);
create table city(
	city_name varchar(15) ,
	population number,
	constraint city_pk primary key (city_name),
	constraint pop_ch check(population > 0)
);
create table shipment(
	shipment_no number(4),
	cust_id number(4) ,
	weight number(10,3) ,
	truck_no varchar(10),
	destination varchar(15) ,
	ship_date date,
	constraint shipment_pk primary key(shipment_no),
	constraint cust_chk check(cust_id between 100 and 5000),
	constraint cust_fk foreign key(cust_id)  references customer_tr(cust_id),
	constraint weight_chk check(weight>0.000),
	constraint dest_fk foreign key (destination) references city(city_name)
);

insert into customer_tr (cust_id,cust_name,annual_revenue,cust_type)values(&cust_id,'&cust_name',&annual_revenue,'&cust_type');
101
Karinghan
10000
manufacturer
/
102
Knuth
9000
manufacturer
insert into customer_tr (cust_id,cust_name,annual_revenue,cust_type)values(103,'Tanenbaum',9000,'manufacturer');
insert into customer_tr (cust_id,cust_name,annual_revenue,cust_type)values(104,'Rosen',8000,'wholesaler');
insert into customer_tr (cust_id,cust_name,annual_revenue,cust_type)values(105,'Galvin',5000,'retailer');

insert into truck (truck_no,driver_name)values('&truck_no','&driver_name');
WB000001
Lui
/
WB000001
Harbinth Singh
insert into truck (truck_no,driver_name)values('WB000002','Robert');
insert into truck (truck_no,driver_name)values('WB000002','Harbinth Singh');
insert into truck (truck_no,driver_name)values('WB000003','Sumitava');
insert into truck (truck_no,driver_name)values('WB000003','Harbinth Singh');
insert into truck (truck_no,driver_name)values('WB000004','Lui');
insert into truck (truck_no,driver_name)values('WB000005','Korth');
insert into truck (truck_no,driver_name)values('WB000006','Navathe');
insert into truck (truck_no,driver_name)values('WB000007','Harbinth Singh');

insert into city (city_name,population)values('&city_name',&population);
Chennai
50000
/
Mumbai
150000
insert into city (city_name,population)values('Kolkata',100000);
insert into city (city_name,population)values('Delhi',100000);

insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(&shipment_no,&cust_id,&weight,'&truck_no','&destination',to_date('&ship_date','DD/MM/YYYY'));
4
101
40000
WB000001
Kolkata
07/07/2007
/
7
103
10000
WB000002
Kolkata
07/07/2007
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(19,103,10000,'WB000006','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(20,103,10000,'WB000007','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(22,103,10000,'WB000003','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(21,103,10000,'WB000001','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(8,103,20000,'WB000004','Mumbai',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(11,103,10000,'WB000005','Chennai',to_date('07/08/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(12,103,20000,'WB000005','Mumbai',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(13,104,50000,'WB000006','Chennai',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(14,105,10000,'WB000005','Delhi',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(15,102,10000,'WB000002','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(16,104,30000,'WB000006','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(17,105,15000,'WB000005','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));
insert into shipment (shipment_no,cust_id,weight,truck_no,destination,ship_date)values(18,105,15000,'WB000003','Kolkata',to_date('07/07/2007','DD/MM/YYYY'));

drop table shipment;
drop table city;
drop table truck;
drop table customer_tr;

"List customer_tr names who have had shipments delivered by every truck"
select cust_name as "customer_tr Name"
from customer_tr
where cust_id in (
	select customer_tr.cust_id
	from customer_tr inner join shipment
	on( customer_tr.cust_id=shipment.cust_id)
	group by customer_tr.cust_id
	having count(distinct shipment.truck_no)=(
		select count(distinct truck_no)
		from truck
	)
);

"For each customer_tr, what is the average weight of a package (shipment) sent by that customer_tr"
select customer_tr.cust_name as "customer_tr ID",avg(shipment.weight) as "Average weight"
from shipment right join customer_tr
on( shipment.cust_id=customer_tr.cust_id)
group by (customer_tr.cust_id,customer_tr.cust_name);

"List cities that have recieved shipment for every customer_tr"
select destination
from shipment
group by destination
having count(distinct cust_id)=(
	select count(cust_id)
	from customer_tr
);

"List the truck_nos driven by Harbinth Singh which have never delivered a shipment to mumbai"
(
	select truck_no
	from truck
	where driver_name='Harbinth Singh'
)minus(
	select distinct truck.truck_no
	from truck inner join shipment
	on(shipment.truck_no=truck.truck_no) 
	and truck.driver_name='Harbinth Singh'
	and shipment.destination='mumbai'
);

"List driver name whose truck have delivered shipment to every city"
select truck.driver_name
from shipment inner join truck
on(shipment.truck_no=truck.truck_no)
group by truck.driver_name
having count(distinct shipment.destination)=(
	select count(city_name)
	from city
);

"Which cities in the database have the largest and smallest population"
select city_name,population
from city
where population=(
	select max(population)
	from city
)or population=(
	select min(population)
	from city
);
