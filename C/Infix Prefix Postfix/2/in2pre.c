char* in2pre(char *s)
{
	int i,l=strlen(s);
	char scpy[MAXSTACK],d[MAXSTACK];
	strcpy(scpy,s);
	strrev(scpy);
	for(i=0;i<l;i++)
		scpy[i]=(scpy[i]=='(' || scpy[i]=='{' || scpy[i]=='[')?')':(scpy[i]==')' || scpy[i]=='}' || scpy[i]==']')?'(':scpy[i];
	in2post(scpy,d);
	return strrev(d);
}
