create table Product(
	maker varchar(15),
	model varchar(10),
	type varchar(10),
	constraint product_pk primary key(model),
	constraint type_dom check(type in ('PC','Laptop','Printer'))
);
create table PC(
	model varchar(10),
	speed number,
	RAM number,
	hd number,
	cd varchar(15) default 'none',
	price number(15,2),
	constraint pc_pk primary key (model),
	constraint pc_product_ref foreign key (model) references Product(model),
	constraint pc_speed_dom check(speed>0),
	constraint pc_RAM_dom check(RAM>0),
	constraint pc_hd_dom check(hd>0),
	constraint pc_price_dom check(price>0)
);
create table Laptop(
	model varchar(10),
	speed number,
	RAM number,
	hd number,
	screen number,
	price number(15,2),
	constraint laptop_pk primary key (model),
	constraint laptop_speed_dom check(speed>0),
	constraint laptop_RAM_dom check(RAM>0),
	constraint laptop_hd_dom check(hd>0),
	constraint laptop_screen_dom check(screen>0),
	constraint laptop_price_dom check(price>0),
	constraint laptop_product_ref foreign key (model) references Product(model)
);
create table Printer(
	model varchar(10),
	color varchar(10),
	type varchar(10),
	price number(15,2),
	constraint printer_pk primary key (model),
	constraint printer_price_dom check(price>0),
	constraint printer_color_dom check(color in ('BW','Color')),
	constraint printer_product_ref foreign key (model) references Product(model)
);
insert into Product (maker,model,type) values('&maker','&model','&type');
ABC
1000
PC
/
XYZ
1001
PC
insert into Product (maker,model,type)values('XYZ','1002','PC');
insert into Product (maker,model,type)values('ABC','1003','PC');
insert into Product (maker,model,type)values('XYZ','1004','PC');
insert into Product (maker,model,type)values('XYZ','1005','PC');
insert into Product (maker,model,type)values('ABC','1006','PC');
insert into Product (maker,model,type)values('PQR','1007','PC');
insert into Product (maker,model,type)values('ABC','2000','Laptop');
insert into Product (maker,model,type)values('ABC','2001','Laptop');
insert into Product (maker,model,type)values('ABC','3000','Printer');
insert into Product (maker,model,type)values('ABC','3001','Printer');
insert into Product (maker,model,type)values('ABC','2002','Printer');
insert into Product (maker,model,type)values('ABC','2003','PC');
insert into Product (maker,model,type)values('XYZ','2004','PC');

insert into PC (model,speed,RAM,hd,cd,price) values('&model',&speed,&RAM,&hd,'&cd',&price);
1000
512
1024
320
LG
29995
/
1001
1024
2048
320
LG
32995
insert into PC (model,speed,RAM,hd,cd,price)values('1002',512,2048,500,'SamSung',32995);
insert into PC (model,speed,RAM,hd,cd,price)values('1003',2048,8000,4000,'LG',52995);
insert into PC (model,speed,RAM,hd,cd,price)values('1004',2048,1024,1000,'LG',39995);
insert into PC (model,speed,RAM,hd,cd,price)values('1005',8000,1024,4000,'ASUS',59995);
insert into PC (model,speed,RAM,hd,cd,price)values('1006',16000,8024,4000,'ASUS',89995);
insert into PC (model,speed,RAM,hd,cd,price)values('1007',512,512,400,'ASUS',89995);
insert into PC (model,speed,RAM,hd,cd,price)values('2003',16000,512,400,'ASUS',89995);
insert into PC (model,speed,RAM,hd,cd,price)values('2004',16000,512,400,'ASUS',89995);

insert into Laptop (model,speed,RAM,hd,screen,price) values('&model',&speed,&RAM,&hd,&screen,&price);
2000
256
2048
320
15
31999
/
2001
1024
4196
1000
13
44999
insert into Laptop (model,speed,RAM,hd,screen,price)values('2002',10024,4196,1000,13,44999);

insert into Printer (model,color,type,price) values('&model','&color','&type',&price);
3000
BW
LaserJet
6999
/
3001
Color
BubbleJet
2999

drop table Printer;
drop table Laptop;
drop table PC;
drop table Product;

"Find the laptops whose speed is slower than that of any PC"

select distinct model,speed,RAM,hd,screen,price from 
Laptop left join (select distinct speed as speedpc from PC)temp
on (Laptop.speed < temp.speedpc);

"Find average hard disk size of PC for all these manufacturers that make printers"

select *
from Product inner join PC
on(product.model=PC.model)
where Product.maker 
in (select distinct maker 
	from Product inner join 
	printer using(model)
);

"Find the maker(s) of the PC(s) with the fastest processor among all those PC's that have the smallest amount of RAM"
select maker from PC inner join Product
on (Pc.model=product.model 
	and pc.ram=(select min(RAM) from PC)
	and pc.speed=(select max(speed) from PC));
"Find those harddisk sizes that occur in three or more PCs"
select hd from pc 
group by hd having 
count(hd)>=3;
"Find the manufacturers that make at least three different models of PC"
select product.maker from 
PC inner join product on(PC.model=product.model)
group by product.maker
having count(product.model)>=3;
