/* Author			:	Rakesh Malik
 * Date				:	27/10/2011
 * Subject			:	String class
 */

#include <iostream>
#include <cstring>

using namespace std;

class String
{
	long length;
	char *buf;
public:
	String(char*);
	String(const String&);
	~String();
	long getLength();
	char* getString();
	char& operator[](int);
	String substring(int);
	String operator=(String);
	String operator+=(String);
	void deleteChar(int);
	void insertChar(int,char);
	void insertString(int,String);
	bool operator==(String);
	bool operator!=(String);
friend	String operator+(String,String);
friend	ostream& operator<<(ostream&,String);
};
String::String(char *buf=(char*)"\0")
{
	String::length=strlen(buf);
	String::buf=new char[String::length+1];
	strcpy(String::buf,buf);
}
String::String(const String &x)
{
	String::length=x.length;
	String::buf=new char[String::length+1];
	strcpy(String::buf,x.buf);
}
String::~String()
{
	String::length=0;
	delete String::buf;
}
char* String::getString()
{
	return String::buf;
}
long String::getLength()
{
	return String::length;
}
char& String::operator[](int index)
{
	if(index>=0 && index<String::length)
		return String::buf[index];
	else
		throw index;
}
String String::substring(int index)
{
	String x;
	if(index>=0 && index<String::length)
	{
		delete x.buf;
		x.length=String::length-index;
		x.buf=new char[x.length+1];
		strcpy(x.buf,String::buf+index);
	}
	return x;
}
String String::operator=(String x)
{
	delete String::buf;
	String::length=strlen(x.buf);
	String::buf=new char[String::length+1];
	strcpy(String::buf,x.buf);
	return *this;
}
String String::operator+=(String y)
{
	String x=*this,z;
	z.length=x.length+y.length;
	z.buf=new char[z.length+1];
	strcpy(z.buf,x.buf);
	strcat(z.buf,y.buf);
	delete String::buf;
	String::length=strlen(z.buf);
	String::buf=new char[String::length+1];
	strcpy(String::buf,z.buf);
	return *this;
}
void String::deleteChar(int index)
{
	if(index<0 || index>=String::length)
		throw index;
	char *buf=new char[String::length-1];
	for(int i=0;i<String::length-1;i++)
		if(i<index)
			buf[i]=String::buf[i];
		else
			buf[i]=String::buf[i+1];
	delete String::buf;
	String::buf=buf;
	String::length--;
}
void String::insertChar(int index,char c)
{
	if(index<0 || index>=String::length)
		throw index;
	char *buf=new char[String::length+1];
	for(int i=0;i<String::length+1;i++)
		if(i<index)
			buf[i]=String::buf[i];
		else if(i==index)
			buf[i]=c;
		else
			buf[i]=String::buf[i-1];
	delete String::buf;
	String::buf=buf;
	String::length++;
}
void String::insertString(int index,String s)
{
	if(index<0 || index>=String::length)
		throw index;
	char *buf=new char[String::length+s.length];
	for(int i=0;i<String::length;i++)
		if(i<index)
			buf[i]=String::buf[i];
		else
			buf[i+s.length]=String::buf[i];
	for(int i=0;i<s.length;i++)
		buf[index+i]=s.buf[i];
	delete String::buf;
	String::buf=buf;
	String::length+=s.length;
}
bool String::operator==(String y)
{
	if(String::length!=y.length)
		return false;
	for(int i=0;i<String::length;i++)
		if(String::buf[i]!=y.buf[i])
			return false;
	return true;
}
bool String::operator!=(String y)
{
	if(String::length!=y.length)
		return true;
	for(int i=0;i<String::length;i++)
		if(String::buf[i]!=y.buf[i])
			return true;
	return false;
}
String operator+(String x,String y)
{
	String z;
	z.length=x.length+y.length;
	z.buf=new char[z.length+1];
	strcpy(z.buf,x.buf);
	strcat(z.buf,y.buf);
	return z;
}
ostream& operator<<(ostream &os,String x)
{
	os<<x.buf;
	return os;
}

main()
{
	String s1=(char*)"Bonjour";
	cout<<s1<<endl;
	String s2;
	s2=(char*)"Monde";
	cout<<s2<<endl;
	String s3;
	s3=s1+(char*)" "+s2;
	cout<<s3<<endl;
	s3.deleteChar(7);
	cout<<s3<<endl;
	s3.insertString(7,(String)(char*)"__");
	cout<<s3<<endl;
}
