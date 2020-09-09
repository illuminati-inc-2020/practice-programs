create table t(
	x varchar(10) primary key,
	a nchar
);

insert into t values ('\0985',UNISTR('\0985'));