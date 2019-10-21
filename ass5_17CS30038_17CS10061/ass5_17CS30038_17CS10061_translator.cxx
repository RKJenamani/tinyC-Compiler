#include "ass5_17CS30038_17CS10061_translator.h"
#include<sstream>
#include<string>
#include<iostream>
using namespace std;

//reference to global variables declared in header file 
symtable* globalST;					// Global Symbol Table
quadArray Q;						// Quad Array
string var_type;						// Stores latest type
symtable* ST;						// Points to current symbol table
sym* currSymbolPtr; 					// points to current symbol
basicType bt;                       // basic types
long long int instr_count;	// count of instr (used for sanity check)
bool debug_on;			// bool for printing debug output
void printpattern(){cout<<"";}   // used for debugging

sym::sym(string name, string t, symboltype* arrtype, int width) 
{     //Symbol table entry
		printpattern();
		(*this).name=name;
		printpattern();
		type=new symboltype(t,arrtype,width);       //Generate type of symbol
		printpattern();
		size=computeSize(type);                   //find the size from the type
		printpattern();
		offset=0;                                   //put offset as 0
		printpattern();
		val="-";                                    //no initial value
		printpattern();
		nested=NULL;                                //no nested table
		printpattern();
}
sym* sym::update(symboltype* t) 
{
	printpattern();	
	type=t;										 //Update the new type
	printpattern();
	(*this).size=computeSize(t);                 //new size
	printpattern();
	return this;                                 //return the same variable	
}

symboltype::symboltype(string type,symboltype* arrtype,int width)        // Constructor for a symbol type
{
	printpattern();
	(*this).type=type;
	printpattern();
	(*this).width=width;
	printpattern();
	(*this).arrtype=arrtype;
	printpattern();
}
symtable::symtable(string name)            //Simple constructor for a symbol table
{
	(*this).name=name;
	printpattern();
	count=0;                           //Put count as 0
	printpattern();
}
sym* symtable::lookup(string name)               //Lookup an id in the symbol table
{
	sym* symbol;
	lsit it;                      //it is iterator for list of symbols
	it=table.begin();
	while(it!=table.end()) 
	{
		if(it->name==name) 
			return &(*it);         //find the name of symbol in the symbol table and return if found
		it++;
	}
	//new symbol to be added to table if not found
	symbol= new sym(name);
	table.push_back(*symbol);           //push the symbol into the table
	return &table.back();               //return the symbol
}
void symtable::update()                      //Update the symbol table 
{
	list<symtable*> tb;                 //list of tables
	int off;
	lsit it;
	it=table.begin();
	while(it!=table.end()) 
	{
		if(it==table.begin()) 
		{
			it->offset=0;
			off=it->size;
		}
		else 
		{
			it->offset=off;
			off=it->offset+it->size;
		}
		if(it->nested!=NULL) 
			tb.push_back(it->nested);
		it++;
	}
	list<symtable*>::iterator it1;
	it1=tb.begin();
	while(it1 !=tb.end()) 
	{
	  (*it1)->update();
	  it1++;
	}
}

void symtable::print()                            //print a symbol table
{
	int next_instr=0;
	list<symtable*> tb;                       //list of tables
	for(int t1=0;t1<50;t1++) 
		cout<<"__";             //just for design/formatting
	cout<<endl;
	cout<<"Table Name: "<<(*this).name<<"\t\t\t Parent Name: ";          //table name
	if(((*this).parent==NULL))
		cout<<"NULL"<<endl;
	else
		cout<<(*this).parent->name<<endl; 
	for(int ti=0;ti<50;ti++) 
		cout<<"__";
	cout<<endl;
	cout<<"Name";              //Name
	generateSpaces(11);
	cout<<"Type";              //Type
	generateSpaces(16);
	cout<<"Initial Value";    //Initial Value
	generateSpaces(7);
	cout<<"Size";              //Size
	generateSpaces(11);
	cout<<"Offset";            //Offset
	generateSpaces(9);
	cout<<"Nested"<<endl;       //Nested symbol table
	generateSpaces(100);
	cout<<endl;
	ostringstream str1;
	 
	for(lsit it=table.begin(); it!=table.end(); it++) {          //Print details for the table
		
		cout<<it->name;                                    //Print name
		
		generateSpaces(15-it->name.length());
		     
		string typeres=printType(it->type);               //Use PrintType to print type
			
		cout<<typeres;
		
		generateSpaces(20-typeres.length());
		 
		cout<<it->val;                                    //Print initial value
		
		generateSpaces(20-it->val.length());
		
		cout<<it->size;                                   //Print size
		
		str1<<it->size;
		
		generateSpaces(15-str1.str().length());
		
		str1.str("");
		
		str1.clear();
		
		cout<<it->offset;                                 //print offset
		
		str1<<it->offset;
		
		generateSpaces(15-str1.str().length());
		
		str1.str("");
		
		str1.clear();
		
		if(it->nested==NULL) {                             //print nested
			
			cout<<"NULL"<<endl;
				
		}
		else {
			
			cout<<it->nested->name<<endl;
				
			tb.push_back(it->nested);
			
		}
	}
	
	for(int i=0;i<100;i++) 
		cout<<"-";
	cout<<"\n\n";
	for(list<symtable*>::iterator it=tb.begin(); it !=tb.end();++it) 
	{
    	(*it)->print();                               //print symbol table
	}
			
}
quad::quad(string res,string arg1,string op,string arg2)           //general constructor for quad
{
	printpattern();
	(*this).res=res;
	printpattern();
	(*this).arg1=arg1;
	printpattern();
	(*this).op=op;
	printpattern();
	(*this).arg2=arg2;
	printpattern();
}
quad::quad(string res,int arg1,string op,string arg2)             //general constructor for quad
{
	printpattern();
	(*this).res=res;
	printpattern();
	(*this).arg2=arg2;
	printpattern();
	(*this).op=op;
	printpattern();
	(*this).arg1=convertIntToString(arg1);
	printpattern();
}
quad::quad(string res,float arg1,string op,string arg2)           //general constructor for quad
{
	printpattern();
	(*this).res=res;
	printpattern();
	(*this).arg2=arg2;
	printpattern();
	(*this).op=op;
	printpattern();
	(*this).arg1=convertFloatToString(arg1);
	printpattern();
}
void quad::print() 
{                                    //Print a quad
	// Binary Operations
	int next_instr=0;	
	if(op=="+")
	{	
		printpattern();	
		(*this).type1();
	}
	else if(op=="-")
	{				
		printpattern();
		(*this).type1();
	}
	else if(op=="*")
	{
		printpattern();
		(*this).type1();
	}
	else if(op=="/")
	{	
		printpattern();	
		(*this).type1();
	}
	else if(op=="%")
	{
		printpattern();
		(*this).type1();
	}
	else if(op=="|")
	{
		printpattern();
		(*this).type1();
	}
	else if(op=="^")
	{
		printpattern();	
		(*this).type1();
	}
	else if(op=="&")
	{
		printpattern();				
		(*this).type1();
	}
	// Relational Operations
	else if(op=="==")
	{
		printpattern();
		(*this).type2();
	}
	else if(op=="!=")
	{
		printpattern();
		(*this).type2();
	}
	else if(op=="<=")
	{
		printpattern();
		(*this).type2();
	}
	else if(op=="<")
	{	
		printpattern();			
		(*this).type2();
	}
	else if(op==">")
	{
		printpattern();
		(*this).type2();
	}
	else if(op==">=")
	{
		printpattern();				
		(*this).type2();
	}
	else if(op=="goto")
	{
		printpattern();				
		cout<<"goto "<<res;
	}	
	// Shift Operations
	else if(op==">>")
	{
		printpattern();
		(*this).type1();
	}
	else if(op=="<<")
	{
		printpattern();				
		(*this).type1();
	}
	else if(op=="=")
	{
		printpattern();				
		cout<<res<<" = "<<arg1 ;
	}					
	//Unary Operators..
	else if(op=="=&")
	{
		printpattern();				
		cout<<res<<" = &"<<arg1;
	}
	else if(op=="=*")
	{
		printpattern();
		cout<<res	<<" = *"<<arg1 ;
	}
	else if(op=="*=")
	{	
		printpattern();			
		cout<<"*"<<res	<<" = "<<arg1 ;
	}
	else if(op=="uminus")
	{
		printpattern();
		cout<<res<<" = -"<<arg1;
	}
	else if(op=="~")
	{
		printpattern();				
		cout<<res<<" = ~"<<arg1;
	}
	else if(op=="!")
	{
		printpattern();
		cout<<res<<" = !"<<arg1;
	}
		//Other operations
	else if(op=="=[]")
	{
		printpattern();
		// cout<<"RES:"<<res<<" arg1:"<<arg1<<" arg2:"<<arg2<<endl;
		 cout<<res<<" = "<<arg1<<"["<<arg2<<"]";
	}
	else if(op=="[]=")
	{	
		printpattern(); 
		// cout<<"RES:"<<res<<" arg1:"<<arg1<<" arg2:"<<arg2<<endl;
		cout<<res<<"["<<arg1<<"]"<<" = "<< arg2;
	}
	else if(op=="return")
	{
		printpattern(); 			
		cout<<"return "<<res;
	}
	else if(op=="param")
	{
		printpattern(); 			
		cout<<"param "<<res;
	}
	else if(op=="call")
	{
		printpattern(); 			
		cout<<res<<" = "<<"call "<<arg1<<", "<<arg2;
	}
	else if(op=="label")
	{
		printpattern();
		cout<<res<<": ";
	}	
	else
	{	
		cout<<"Can't find "<<op;
	}			
	cout<<endl;
	
}
void quad::type1()
{
	printpattern();
	cout<<res<<" = "<<arg1<<" "<<op<<" "<<arg2;
	printpattern();
}
void quad::type2()
{
	printpattern();
	cout<<"if "<<arg1<< " "<<op<<" "<<arg2<<" goto "<<res;
	printpattern();
}

void basicType::addType(string t, int s)          //Add new trivial type to type ST
{
	printpattern();
	type.push_back(t);
	printpattern();
	size.push_back(s);
	printpattern();
}
void quadArray::print()                                   //print the quad Array i.e the TAC
{
	for(int i=0;i<50;i++) 
		cout<<"__";
	cout<<endl;
	cout<<"Three Address Code:"<<endl;           //print TAC
	for(int i=0;i<50;i++) 
		cout<<"__";
	cout<<endl;
	int j=0;
	vector<quad>::iterator it;
	it=Array.begin();
	while(it!=Array.end()) 
	{
		if(it->op=="label") 
		{           //it is a label, print it
			cout<<endl<<"L"<<j<<": ";
			it->print();
		}
		else {                         //otherwise give 4 spaces and then print
			cout<<"L"<<j<<": ";
			generateSpaces(4);
			it->print();
		}
		it++;j++;
	}
	for(int i=0;i<50;i++) 
		cout<<"__";      //just for formatting
	cout<<endl;
}

void generateSpaces(int n)
{
	printpattern();
	while(n--) 
		cout<<" ";
	printpattern();
}
string convertIntToString(int a)                    //to convert int to string
{
	stringstream strs;                      //use buffer stringstream
    strs<<a; 
    string temp=strs.str();
    char* integer=(char*) temp.c_str();
	string str=string(integer);
	return str;                              //return string
}
string convertFloatToString(float x)                        //Take float as input and produce string as output
{
	std::ostringstream buff;
	buff<<x;
	return buff.str();
}
void emit(string op, string res, string arg1, string arg2) 
{             //Emit a quad: add the quad into the Array
	quad *q1= new quad(res,arg1,op,arg2);
	printpattern();
	Q.Array.push_back(*q1);
}
void emit(string op, string res, int arg1, string arg2) 
{                 //Emit a quad: add the quad into the Array
	quad *q2= new quad(res,arg1,op,arg2);
	printpattern();
	Q.Array.push_back(*q2);
}
void emit(string op, string res, float arg1, string arg2) 
{                 //Emit a quad: add the quad into the Array
	quad *q3= new quad(res,arg1,op,arg2);
	Q.Array.push_back(*q3);
}
sym* convertType(sym* s, string rettype) 
{                             //convert symbol s into the required return type
	sym* temp=gentemp(new symboltype(rettype));	
	if((*s).type->type=="float")                                      //if type float
	{
		if(rettype=="int")                                      //and converting to int
		{
			emit("=",temp->name,"float2int("+(*s).name+")");
			return temp;
		}
		else if(rettype=="char")                               //or converting to char
		{
			emit("=",temp->name,"float2char("+(*s).name+")");
			return temp;
		}
		return s;
	}
	else if((*s).type->type=="int")                                  //if type int
	{
		if(rettype=="float") 									//and converting to float
		{
			emit("=",temp->name,"int2float("+(*s).name+")");
			return temp;
		}
		else if(rettype=="char") 								//or converting to char
		{
			emit("=",temp->name,"int2char("+(*s).name+")");
			return temp;
		}
		return s;
	}
	else if((*s).type->type=="char") 								  //if type char
	{
		if(rettype=="int") 									//and converting to int
		{
			emit("=",temp->name,"char2int("+(*s).name+")");
			return temp;
		}
		if(rettype=="double") 								//or converting to double
		{
			emit("=",temp->name,"char2double("+(*s).name+")");
			return temp;
		}
		return s;
	}
	return s;
}

void changeTable(symtable* newtable) 
{	       // Change current symbol table
	printpattern();
	ST = newtable;
	printpattern();
} 

bool compareSymbolType(sym*& s1,sym*& s2)
{ 	// Check if the symbols have same type or not
	printpattern();symboltype* type1=s1->type;                         //get the base types
	printpattern();symboltype* type2=s2->type;
	int flag=0;
	if(compareSymbolType(type1,type2)) 
		flag=1;       
	else if(s1=convertType(s1,type2->type)) 
		flag=1;	//if one can be converted to the other. convert them
	else if(s2=convertType(s2,type1->type)) 
		flag=1;
	if(flag)
		return true;
	else 
		return false;
}
bool compareSymbolType(symboltype* t1,symboltype* t2)
{ 	// Check if the symbol types are same or not
	printpattern();
	int flag=0;
	if(t1==NULL && t2==NULL) 
		flag=1;               //if two symboltypes are NULL
	else if(t1==NULL || t2==NULL || t1->type!=t2->type) 
		flag=2;                     //if only one of them is NULL     //if base type isn't same
	
	if(flag==1)
		return true;
	else if(flag==2)
		return false;
	else 
		return compareSymbolType(t1->arrtype,t2->arrtype);       //otherwise check their Array type
}
void backpatch(list<int> list1,int addr)                 //backpatching
{
	string str=convertIntToString(addr);              //get string form of the address
	list<int>::iterator it;
	it=list1.begin();
	printpattern();
	while( it!=list1.end()) 
	{
		Q.Array[*it].res=str;                     //do the backpatching
		it++;
	}
}
list<int> makelist(int init) 
{
	list<int> newlist(1,init);                      //make a new list
	printpattern();
	return newlist;
}
list<int> merge(list<int> &a,list<int> &b)
{
	a.merge(b);                                //merge two existing lists
	printpattern();
	return a;
}
Expression* convertIntToBool(Expression* e)        
{	// Convert any Expression to bool using standard procedure as given in book
	if(e->type!="bool")                
	{
		e->falselist=makelist(nextinstr());    //update the falselist, truelist and also emit general goto statements
		emit("==","",e->loc->name,"0");
		e->truelist=makelist(nextinstr());
		emit("goto","");
	}
}
void update_nextinstr()
{
	instr_count++;
	if(debug_on==1)
	{
		cout<<"Current Line Number:"<<instr_count<<endl;
		cout<<"Press [ENTER] to continue:";
		cin.get();
	}
}
void debug()
{
	if(debug_on==1)
		cout<<instr_count<<endl;
}
Expression* convertBoolToInt(Expression* e) 
{	// Convert any Expression to bool using standard procedure as given in book
	if(e->type=="bool") 
	{
		printpattern();
		e->loc=gentemp(new symboltype("int"));         //use general goto statements and standard procedure
		printpattern();
		backpatch(e->truelist,nextinstr());
		printpattern();
		emit("=",e->loc->name,"true");
		printpattern();
		int p=nextinstr()+1;
		printpattern();
		string str=convertIntToString(p);
		printpattern();
		emit("goto",str);
		printpattern();
		backpatch(e->falselist,nextinstr());
		printpattern();
		emit("=",e->loc->name,"false");
		printpattern();
	}
}
int nextinstr() 
{
	printpattern();
	return Q.Array.size();                //next instruction will be 1+last index and lastindex=size-1. hence return size
}
sym* gentemp(symboltype* t, string str_new) 
{           //generate temp variable
	string tmp_name = "t"+convertIntToString(ST->count++);             //generate name of temporary
	sym* s = new sym(tmp_name);
	(*s).type = t;
	(*s).size=computeSize(t);                        //calculate its size
	(*s).val = str_new;
	ST->table.push_back(*s);                        //push it in ST
	return &ST->table.back();
}
int computeSize(symboltype* t)                   //calculate size function
{
	if(t->type.compare("void")==0)	
		return bt.size[1];
	else if(t->type.compare("char")==0) 
		return bt.size[2];
	else if(t->type.compare("int")==0) 
		return bt.size[3];
	else if(t->type.compare("float")==0) 
		return  bt.size[4];
	else if(t->type.compare("arr")==0) 
		return t->width*computeSize(t->arrtype);     //recursive for arr1s(Multidimensional arr1s)
	else if(t->type.compare("ptr")==0) 
		return bt.size[5];
	else if(t->type.compare("func")==0) 
		return bt.size[6];
	else 
		return -1;
}
string printType(symboltype* t)                    //Print type of variable(imp for multidimensional arr1s)
{
	if(t==NULL) return bt.type[0];
	if(t->type.compare("void")==0)	return bt.type[1];
	else if(t->type.compare("char")==0) return bt.type[2];
	else if(t->type.compare("int")==0) return bt.type[3];
	else if(t->type.compare("float")==0) return bt.type[4];
	else if(t->type.compare("ptr")==0) return bt.type[5]+"("+printType(t->arrtype)+")";       //recursive for ptr
	else if(t->type.compare("arr")==0) 
	{
		string str=convertIntToString(t->width);                                //recursive for arr1s
		return bt.type[6]+"("+str+","+printType(t->arrtype)+")";
	}
	else if(t->type.compare("func")==0) return bt.type[7];
	else return "NA";
}
int main()
{
	bt.addType("null",0);                 //Add base types initially
	bt.addType("void",0);
	bt.addType("char",1);
	bt.addType("int",4);
	bt.addType("float",8);
	bt.addType("ptr",4);
	bt.addType("arr",0);
	bt.addType("func",0);
	instr_count = 0;   // count of instr (used for sanity check)
	debug_on= 0;       // debugging is off
	globalST=new symtable("Global");                         //Global ST
	ST=globalST;
	yyparse();												 //parse
	globalST->update();										 //update the global ST
	cout<<"\n";
	Q.print();	
	globalST->print();										//print all STs
													//print TAC
};
