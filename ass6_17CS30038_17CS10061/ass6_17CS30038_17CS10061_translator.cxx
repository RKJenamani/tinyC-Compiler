#include "ass6_17CS30038_17CS10061_translator.h"
#include "y.tab.h"
#include<sstream>
#include<string>
#include<iostream>

#define pf printf

long long int instr_count;	// count of instr (used for sanity check)
bool debug_on;			// bool for printing debug output
#define pb push_back
type_n *glob_type;
int glob_width;
int next_instr;
int temp_count=0;
symtab *glob_st =new symtab();
symtab *curr_st = new symtab();
quad_arr glob_quad;
vector <string> vs;
vector <string> cs;
int size_int=4;
int size_double=8;
int size_pointer=8;
int size_char=1;
int size_bool=1;
vector<string> strings_label;
void printpattern()
{ return;}
type_n::type_n(types t,int sz,type_n *n)
{
	printpattern();
	basetp=t;
	printpattern();
	size=sz;
	printpattern();
	next=n;
	printpattern();
}

int type_n::getSize()
{
	if(this==NULL)
		return 0;
	printpattern();
	//return the size of the array by calling the recursive function 
	//here we are not checking for null as if it will reach the final type it will enter the below conditions
	if(((*this).basetp) == tp_arr)
		return (((*this).size)*((*this).next->getSize()));
	printpattern();
	if(((*this).basetp) == tp_void)
		return 0;
	printpattern();
	if(((*this).basetp) == tp_int)
		return size_int;
	printpattern();
	if(((*this).basetp) == tp_double)
		return size_double;
	printpattern();
	if(((*this).basetp) == tp_bool)
		return size_bool;
	printpattern();
	if(((*this).basetp) == tp_char)
		return size_char;
	printpattern();
	if(((*this).basetp) == tp_ptr)
		return size_pointer;
	printpattern();
}

types type_n::getBasetp()
{
	if(this!=NULL)
	{
		printpattern();
		return (*this).basetp;
		printpattern();
	}	
	else
	{
		printpattern();
		return tp_void;
		printpattern();
	}	
		
}

void type_n::printSize()
{
	printpattern();
	pf("%d\n",size);
}

void type_n::print()
{
	if(basetp ==  tp_void)
	{
		printpattern();	
		pf("Void");
	}

	else if(basetp == tp_bool)
	{
		printpattern();
		pf("Bool");

	}	
	else if(basetp == tp_int)	
	{
		printpattern();
		pf("Int");
	}

	else if(basetp == tp_char)	
	{
		printpattern();
		pf("Char");
		printpattern();
	}
	
	else if(basetp == tp_double)
	{
		printpattern();
		pf("Double");
	}

	else if(basetp == tp_ptr)	
	{	
		printpattern();
		pf("ptr(");
		if((*this).next!=NULL)
			(*this).next->print();
		pf(")");
		printpattern();
	}
	else if(basetp == tp_arr)
	{	
		pf("array(%d,",size);
		if((*this).next!=NULL)
			(*this).next->print();
			pf(")");
		printpattern();	
	}		
	else if(basetp == tp_func)
	{
		pf("Function()");
		printpattern();
	}	
	else
	{
			printpattern();
			pf("TYPE NOT FOUND\n");
			exit(-1);
	}
	

}

array::array(string s,int sz,types t)
{
	(*this).base_arr=s;
	printpattern();
	(*this).tp=t;
	printpattern();
	(*this).bsize=sz;
	printpattern();
	(*this).dimension_size=1;
	printpattern();
}

void array::addindex(int i)
{
	(*this).dimension_size=(*this).dimension_size+1;
	printpattern();
	(*this).dims.pb(i);
	printpattern();
}

void funct::print()
{

	pf("Funct(");
	printpattern();
	int i;
	printpattern();
	for(i=0;i<typelist.size();i++)
	{
		printpattern();
		if(i!=0)
			pf(",");
		printpattern();
		pf("%d ",typelist[i]);
		printpattern();
	}
	pf(")");
	printpattern();
}

funct::funct(vector<types> tpls)
{
	typelist=tpls;
	printpattern();
}
symdata::symdata(string n)
{
	name=n;
	//pf("sym%s\n",n.c_str());
	size=0;
	tp_n=NULL;
	offset=-1;
	var_type="";
	isInitialized=false;
	isFunction=false;
	isArray=false;
	ispresent=true;
	arr=NULL;
	fun=NULL;
	nest_tab=NULL;
	isdone=false;
	isptrarr=false;
	isGlobal=false;
}

void symdata::createarray()
{
	printpattern();
	arr=new array((*this).name,(*this).size,tp_arr);
	printpattern();
}


symtab::symtab()
{
	printpattern();
	name="";
	printpattern();
	offset=0;
	printpattern();
	no_params=0;
	printpattern();
}

symtab::~symtab()
{
	int i=0;
	printpattern();
	for(;i<symbol_tab.size();i++)
	{
		printpattern();
		type_n *p1=(*symbol_tab[i]).tp_n;
		printpattern();
		type_n *p2;
		while(true)
		{
			printpattern();
			if(p1 == NULL)
				break;
			printpattern();
			p2=p1;
			printpattern();
			p1=(*p1).next;
			printpattern();
			delete p2;
		}
	}
	printpattern();
}
int symtab::findg(string n)
{
	printpattern();
	for(int i=0;i<vs.size();i++)
	{
		printpattern();
		if(vs[i]==n)
			return 1;
	}
	printpattern();
	for(int i=0;i<cs.size();i++)
	{
		printpattern();
		if(cs[i]==n)
			return 2;
	}
	printpattern();
	return 0;
}
type_n *CopyType(type_n *t)
{
	/*Duplicates the input type and returns the pointer to the newly created type*/
	if(t == NULL) 
		return t;
	printpattern();
	type_n *ret = new type_n((*t).basetp);
	printpattern();
	(*ret).size = (*t).size;
	(*ret).basetp = (*t).basetp;
	printpattern();
	(*ret).next = CopyType((*t).next);
	printpattern();
	return ret;
}

symdata* symtab::lookup(string n)
{
	int i;
	//pf("%s-->%s\n",name.c_str(),n.c_str());
	for(i=0;i<symbol_tab.size();i++)
	{
		printpattern();
		//pf("Flag1\n");
		if((*symbol_tab[i]).name == n)
		{
			printpattern();
			return symbol_tab[i];
		}
	}
	printpattern();
	//pf("Flag2\n");
	//pf("k%d\n",symbol_tab.size());
	symdata *temp_o=new symdata(n);
	printpattern();
	(*temp_o).i_val.int_val=0;
	printpattern();
	symbol_tab.pb(temp_o);
	printpattern();
	//pf("lol%s\n",temp_o->name.c_str());
	//pf("%d\n",symbol_tab.size());
	return symbol_tab[symbol_tab.size()-1];
}

symdata* symtab::lookup_2(string n)
{
	int i;
	printpattern();
	for(i=0;i<symbol_tab.size();i++)
	{
		printpattern();
		if(symbol_tab[i]->name == n)
		{
			printpattern();
			return symbol_tab[i];
		}
	}
	printpattern();
	for(i=0;i<(*glob_st).symbol_tab.size();i++)
	{
		printpattern();
		if((*glob_st).symbol_tab[i]->name == n)
		{
			printpattern();
			return (*glob_st).symbol_tab[i];
		}
	}
	printpattern();
	symdata *temp_o=new symdata(n);
	printpattern();
	(*temp_o).i_val.int_val=0;
	printpattern();
	symbol_tab.pb(temp_o);
	printpattern();
	return symbol_tab[symbol_tab.size()-1];
}

symdata* symtab::search(string n)
{
	int i;
	printpattern();
	for(i=0;i<symbol_tab.size();i++)
	{
		printpattern();
		if((*symbol_tab[i]).name==n && symbol_tab[i]->ispresent)
		{
			printpattern();
			return (symbol_tab[i]);
		}
	}
	printpattern();
	return NULL;
}

symdata* symtab::gentemp(type_n *type)
{
	char c[10];
	printpattern();
	sprintf(c,"t%03d",temp_count);
	printpattern();
	temp_count++;
	printpattern();
	symdata *temp=lookup(c);
	printpattern();
	int temp_sz;
	printpattern();
	if(type==NULL)
		temp_sz=0;
	else if(((*type).basetp) == tp_void)
		temp_sz=0;
	else if(((*type).basetp) == tp_int)
		temp_sz=size_int;
	else if(((*type).basetp) == tp_double)
		temp_sz=size_double;
	else if(((*type).basetp) == tp_bool)
		temp_sz=size_bool;
	else if(((*type).basetp) == tp_char)
		temp_sz=size_char;
	else if(((*type).basetp) == tp_ptr)
		temp_sz=size_pointer;
	else
		temp_sz=(*type).getSize();
	printpattern();
	(*temp).size=temp_sz;
	printpattern();
	(*temp).var_type="temp";
	printpattern();
	(*temp).tp_n=type;
	printpattern();
	(*temp).offset=(*this).offset;
	printpattern();
	(*this).offset=(*this).offset+((*temp).size);
	printpattern();
	return temp;
}

void symtab::update(symdata *sm,type_n *type,basic_val initval,symtab *next)
{
	(*sm).tp_n=CopyType(type);
	printpattern();
	(*sm).i_val=initval;
	printpattern();
	(*sm).nest_tab=next;
	printpattern();
	int temp_sz;
	printpattern();
	if((*sm).tp_n==NULL)
		temp_sz=0;
	else if((((*sm).tp_n)->basetp) == tp_void)
		temp_sz=0;
	else if((((*sm).tp_n)->basetp) == tp_int)
		temp_sz=size_int;
	else if((((*sm).tp_n)->basetp) == tp_double)
		temp_sz=size_double;
	else if((((*sm).tp_n)->basetp) == tp_bool)
		temp_sz=size_bool;
	else if((((*sm).tp_n)->basetp) == tp_char)
		temp_sz=size_char;
	else if((((*sm).tp_n)->basetp) == tp_ptr)
		temp_sz=size_pointer;
	else
		temp_sz=(*sm).tp_n->getSize();
	printpattern();
	(*sm).size=temp_sz;
	printpattern();
	(*sm).offset=(*this).offset;
	printpattern();
	(*this).offset=(*this).offset+((*sm).size);
	printpattern();
	(*sm).isInitialized=false;
	printpattern();
}

void symtab::print()
{
	pf("____________________________________________ %s ____________________________________________\n",name.c_str());
	printpattern();
	pf("Offset = %d\nStart Quad Index = %d\nEnd Quad Index =  %d\n",offset,start_quad,end_quad);
	printpattern();
	pf("Name\tValue\tvar_type\tsize\tOffset\tType\n\n");
    printpattern();
    for(int i = 0; i<(symbol_tab).size(); i++)
    {
    	printpattern();
        if(symbol_tab[i]->ispresent==false)
        	continue;
        printpattern();
        symdata * t = symbol_tab[i];
        printpattern();
        pf("%s\t",symbol_tab[i]->name.c_str()); 
        if((*t).isInitialized)
        {
        	printpattern();
        	if(((*t).tp_n)->basetp == tp_char) 
        		pf("%c\t",((*t).i_val).char_val);
        	else if(((*t).tp_n)->basetp == tp_int) 
        		pf("%d\t",((*t).i_val).int_val);
        	else if(((*t).tp_n)->basetp == tp_double) 
        		pf("%.3lf\t",((*t).i_val).double_val);
       	 	else pf("----\t");
       	 	printpattern();
      	}
      	else
      		pf("null\t");
      	printpattern();
        pf("%s",(*t).var_type.c_str());
        printpattern();
        pf("\t\t%d\t%d\t",(*t).size,(*t).offset);
        printpattern();
		if((*t).var_type == "func")
			pf("ptr-to-St( %s )",(*t).nest_tab->name.c_str());
		printpattern();
		if((*t).tp_n != NULL)
			((*t).tp_n)->print();
		pf("\n");
	}
	printpattern();
	pf("\n");
	printpattern();
	pf("x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n");
}
list* makelist(int i)
{
	list *temp = (list*)malloc(sizeof(list));
	printpattern();
	(*temp).index=i;
	printpattern();
	(*temp).next=NULL;
	printpattern();
	return temp;
}
list* merge(list *lt1,list *lt2)
{
	list *temp = (list*)malloc(sizeof(list));
	printpattern();
	list *p1=temp;
	printpattern();
	int flag=0;
	printpattern();
	list *l1=lt1;
	printpattern();
	list *l2=lt2;
	printpattern();
	while(l1!=NULL)
	{
		flag=1;
		printpattern();
		(*p1).index=(*l1).index;
		printpattern();
		if((*l1).next!=NULL)
		{
			(*p1).next=(list*)malloc(sizeof(list));
			p1=(*p1).next;
		}
		printpattern();
		l1=(*l1).next;
	}
	while(l2!=NULL)
	{
		printpattern();
		if(flag==1)
		{
			printpattern();
			(*p1).next=(list*)malloc(sizeof(list));
			printpattern();
			p1=(*p1).next;
			printpattern();
			flag=0;
			printpattern();
		}
		(*p1).index=l2->index;
		printpattern();
		if(l2->next!=NULL)
		{
			printpattern();
			(*p1).next=(list*)malloc(sizeof(list));
			printpattern();
			p1=(*p1).next;
			printpattern();
		}
		l2=l2->next;
		printpattern();
	}
	printpattern();
	(*p1).next=NULL;
	printpattern();
	return temp;
}

quad::quad(opcode opc,string a1,string a2,string rs)
{
	(*this).op=opc;
	printpattern();
	(*this).arg1=a1;
	printpattern();
	(*this).result=rs;
	printpattern();
	(*this).arg2=a2;
	printpattern();
}

void quad::print_arg()
{
	printpattern();
	pf("\t%s\t=\t%s\top\t%s\t",result.c_str(),arg1.c_str(),arg2.c_str());
	printpattern();
}

quad_arr::quad_arr()
{
	printpattern();
	next_instr=0;
	printpattern();
}

void quad_arr::emit(opcode opc, string arg1, string arg2, string result)
{
	printpattern();
	if(result.size()!=0)
	{
		printpattern();
		quad new_elem(opc,arg1,arg2,result);
		printpattern();
		arr.pb(new_elem);
		printpattern();
	}
	else if(arg2.size()!=0)
	{
		printpattern();
		quad new_elem(opc,arg1,"",arg2);
		printpattern();
		arr.pb(new_elem);
		printpattern();
	}
	else if(arg1.size()!=0)
	{
		printpattern();
		quad new_elem(opc,"","",arg1);
		printpattern();
		arr.pb(new_elem);
		printpattern();
	}
	else
	{
		printpattern();
		quad new_elem(opc,"","","");
		printpattern();
		arr.pb(new_elem);
		printpattern();
	}
	next_instr++;
	printpattern();
}
void quad_arr::emit2(opcode opc,string arg1, string arg2, string result)
{
	if(result.size()==0)
	{
		printpattern();
		quad new_elem(opc,arg1,arg2,"");
		printpattern();
		arr.pb(new_elem);
	}
}
void quad_arr::emit(opcode opc, int val, string operand)
{
	char str[20];
	printpattern();
	sprintf(str, "%d", val);
	if(operand.size()==0)
	{
		printpattern();
		quad new_quad(opc,"","",str);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	else
	{
		printpattern();
		quad new_quad(opc,str,"",operand);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	printpattern();
	next_instr=next_instr+1;
	printpattern();
}

void quad_arr::emit(opcode opc, double val, string operand)
{
	char str[20];
	printpattern();
	sprintf(str, "%lf", val);
	printpattern();
	if(operand.size()==0)
	{
		printpattern();
		quad new_quad(opc,"","",str);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	else
	{
		printpattern();
		quad new_quad(opc,str,"",operand);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	printpattern();
	next_instr=next_instr+1;
	printpattern();
}

void quad_arr::emit(opcode opc, char val, string operand)
{
	char str[20];
	printpattern();
	sprintf(str, "'%c'", val);
	printpattern();
	if(operand.size()==0)
	{
		printpattern();
		quad new_quad(opc,"","",str);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	else
	{
		printpattern();
		quad new_quad(opc,str,"",operand);
		printpattern();
		arr.pb(new_quad);
		printpattern();
	}
	printpattern();
	next_instr=next_instr+1;
}

void quad_arr::print()
{
	opcode op;
	printpattern();
	string arg1;
	printpattern();
	string arg2;
	printpattern();
	string result;
	printpattern();
	for(int i=0;i<next_instr;i++)
	{

		op=arr[i].op;
		printpattern();
		arg1=arr[i].arg1;
		printpattern();
		arg2=arr[i].arg2;
		printpattern();
		result=arr[i].result;
		printpattern();
		pf("%3d : ",i);
		printpattern();
		if(Q_PLUS<=op && op<=Q_NOT_EQUAL)
	    {
	        pf("%s",result.c_str());
	        printpattern();
	        pf("\t=\t");
	        printpattern();
	        pf("%s",arg1.c_str());
	        printpattern();
	        pf(" ");
	        printpattern();
            if( Q_PLUS == op) 
            	pf("+"); 
            else if( Q_MINUS == op) 
            	pf("-"); 
            else if (Q_MULT == op) 
            	pf("*"); 
            else if(op == Q_DIVIDE) 
            	pf("/");
            else if( Q_MODULO ==op) 
            	pf("%%"); 
            else if( Q_LEFT_OP == op) 
            	pf("<<"); 
            else if (op == Q_RIGHT_OP) 
            	pf(">>"); 
            else if(op == Q_XOR) 
            	pf("^"); 
            else if (op== Q_AND) 
            	pf("&"); 
            else if( Q_OR == op) 
            	pf("|"); 
            else if (Q_LOG_AND == op) 
            	pf("&&"); 
            else if(op == Q_LOG_OR) 
            	pf("||"); 
            else if( Q_LESS == op) 
            	pf("<"); 
            else if( Q_LESS_OR_EQUAL == op) 
            	pf("<="); 
            else if(Q_GREATER_OR_EQUAL == op) 
            	pf(">="); 
            else if (Q_GREATER == op) 
            	pf(">"); 
            else if (Q_EQUAL == op) 
            	pf("=="); 
            else if(Q_NOT_EQUAL == op) 
            		pf("!=");
        
	        pf(" ");
	        printpattern();
	       	pf("%s\n",arg2.c_str());
	       	printpattern();
	    }
	    else if(Q_UNARY_MINUS<=op && op<=Q_ASSIGN)
	    {
	        pf("%s",result.c_str());
	        printpattern();
	        pf("\t=\t");
	        printpattern();    
            if( Q_UNARY_MINUS == op) 
            	pf("-"); 
            else if (op == Q_UNARY_PLUS)  
            	pf("+"); 
            else if(op == Q_COMPLEMENT) 
            	pf("~"); 
            else if(op== Q_NOT)  
            	pf("!"); 
        	printpattern();
	        pf("%s\n",arg1.c_str());
	        printpattern();
	    }
	    else if(op == Q_GOTO)
	    {
	    	pf("goto ");
	    	printpattern();
	    	pf("%s\n",result.c_str());
	    	printpattern();
	    }
	    else if(Q_IF_EQUAL<=op && op<=Q_IF_GREATER_OR_EQUAL)
	    {
	        pf("if  ");pf("%s",arg1.c_str());pf(" ");
	        printpattern();
            //Conditional Jump
            if(Q_IF_LESS == op) 
            	pf("<"); 
            else if( Q_IF_GREATER == op) 
            	pf(">"); 
            else if(op == Q_IF_LESS_OR_EQUAL ) 
            	pf("<="); 
            else if(op == Q_IF_GREATER_OR_EQUAL ) 
            	pf(">="); 
            else if (op == Q_IF_EQUAL ) 
            	pf("=="); 
            else if(op == Q_IF_NOT_EQUAL )
            	pf("!="); 
            else if (op == Q_IF_EXPRESSION ) 
            	pf("!= 0"); 
            else if (op == Q_IF_NOT_EXPRESSION)  
            	pf("== 0"); 
	        pf("%s",arg2.c_str());
	        printpattern();
	        pf("\tgoto ");
	        printpattern();
	        pf("%s\n",result.c_str()); 
	        printpattern();           
	    }
	    else if(Q_CHAR2INT<=op && op<=Q_DOUBLE2INT)
	    {
	        pf("%s",result.c_str());pf("\t=\t");
	        printpattern();
            if(op == Q_CHAR2INT) 
            { 
            	pf(" Char2Int(");
            	printpattern();
            	pf("%s",arg1.c_str());pf(")\n"); 
            }
            else if(op == Q_CHAR2DOUBLE) 
            {
            	pf(" Char2Double(");
            	printpattern();
            	pf("%s",arg1.c_str());pf(")\n"); 
            }
            else if(op == Q_INT2CHAR) 
            {
            	pf(" Int2Char(");
            	printpattern();
            	pf("%s",arg1.c_str());
            	printpattern();
            	pf(")\n"); 
        	}
            else if(op == Q_DOUBLE2CHAR ) 
            {
            	pf(" Double2Char(");
            	printpattern();
            	pf("%s",arg1.c_str());
            	printpattern();
            	pf(")\n");
            }
            else if(op == Q_INT2DOUBLE)
            { 
            	pf(" Int2Double(");
            	printpattern();
            	pf("%s",arg1.c_str());
            	printpattern();
            	pf(")\n"); 
            }
            else if(op == Q_DOUBLE2INT)
            { 
            	pf(" Double2Int(");
            	printpattern();
            	pf("%s",arg1.c_str());
            	printpattern();
            	pf(")\n"); 
            }	
            printpattern();
	                    
	    }
	    else if(op == Q_PARAM)
	    {
	    	printpattern();
	        pf("param\t");pf("%s\n",result.c_str());
	        printpattern();
	    }
	    else if(op == Q_CALL)
	    {
	    	printpattern();
	        if(!result.c_str())
					pf("call %s, %s\n", arg1.c_str(), arg2.c_str());
			else if(result.size()==0)
			{
				printpattern();
				pf("call %s, %s\n", arg1.c_str(), arg2.c_str());
			}
			else
			{
				printpattern();
				pf("%s\t=\tcall %s, %s\n", result.c_str(), arg1.c_str(), arg2.c_str());
			}	    
	    }
	    else if(op == Q_RETURN)
	    {
	        pf("return\t");
	        printpattern();
	        pf("%s\n",result.c_str());
	        printpattern();
	    }
	    else if( op == Q_RINDEX)
	    {
	    	printpattern();
	        pf("%s\t=\t%s[%s]\n", result.c_str(), arg1.c_str(), arg2.c_str());
	        printpattern();
	    }
	    else if(op == Q_LINDEX)
	    {
	    	printpattern();
	        pf("%s[%s]\t=\t%s\n", result.c_str(), arg1.c_str(), arg2.c_str());
	        printpattern();
	    }
	    else if(op == Q_LDEREF)
	    {
	    	printpattern();
	        pf("*%s\t=\t%s\n", result.c_str(), arg1.c_str());
	    }
	    else if(op == Q_RDEREF)
	    {
	    	printpattern();
	    	pf("%s\t=\t* %s\n", result.c_str(), arg1.c_str());
	    }
	    else if(op == Q_ADDR)
	    {
	    	printpattern();
	    	pf("%s\t=\t& %s\n", result.c_str(), arg1.c_str());
	    }
	}
}

void backpatch(list *l,int i)
{
	list *temp =l;
	printpattern();
	list *temp2;
	printpattern();
	char str[10];
	printpattern();
	sprintf(str,"%d",i);
	printpattern();
	while(temp!=NULL)
	{
		printpattern();
		glob_quad.arr[(*temp).index].result = str;
		printpattern();
		temp2=temp;
		printpattern();
		temp=(*temp).next;
		printpattern();
		free(temp2);
	}
}

void typecheck(expresn *e1,expresn *e2,bool isAssign)
{
	types type1,type2;
	printpattern();
	//if((*e2).type)
	if(e1->type==NULL)
	{
		printpattern();
		e1->type = CopyType((*e2).type);
	}
	else if((*e2).type==NULL)
	{
		printpattern();
		(*e2).type =CopyType(e1->type);
	}
	printpattern();
	type1=((*e1).type)->basetp;
	printpattern();
	type2=((*e2).type)->basetp;
	printpattern();
	if(type1==type2)
	{
		printpattern();
		return;
	}
	if(!isAssign)
	{
		if(type1>type2)
		{
			printpattern();
			symdata *temp = (*curr_st).gentemp((*e1).type);
			printpattern();
			if(type1 == tp_int && type2 == tp_char)
				glob_quad.emit(Q_CHAR2INT, (*e2).loc->name, (*temp).name);
			else if(type1 == tp_double && type2 == tp_int)
				glob_quad.emit(Q_INT2DOUBLE,(*e2).loc->name, (*temp).name);
			(*e2).loc = temp;
			printpattern();
			(*e2).type = (*temp).tp_n;
			printpattern();
		}
		else
		{
			printpattern();
			symdata *temp = (*curr_st).gentemp((*e2).type);
			printpattern();
			if(type2 == tp_int && type1 == tp_char)
				glob_quad.emit(Q_CHAR2INT, e1->loc->name, (*temp).name);
			else if(type2 == tp_double && type1 == tp_int)
				glob_quad.emit(Q_INT2DOUBLE, e1->loc->name, (*temp).name);	
			printpattern();
			e1->loc = temp;
			printpattern();
			e1->type = (*temp).tp_n;
		}		
	}
	else
	{
		printpattern();
		symdata *temp = (*curr_st).gentemp(e1->type);
		if(type1 == tp_int && type2 == tp_double)
			glob_quad.emit(Q_DOUBLE2INT, (*e2).loc->name, (*temp).name);
		else if(type1 == tp_double && type2 == tp_int)
			glob_quad.emit(Q_INT2DOUBLE, (*e2).loc->name, (*temp).name);
		else if(type1 == tp_char && type2 == tp_int)
			glob_quad.emit(Q_INT2CHAR, (*e2).loc->name, (*temp).name);
		else if(type1 == tp_int && type2 == tp_char)
			glob_quad.emit(Q_CHAR2INT, (*e2).loc->name, (*temp).name);
		else
		{
			printpattern();
			pf("%s %s Types compatibility not defined\n",e1->loc->name.c_str(),(*e2).loc->name.c_str());
			printpattern();
			exit(-1);
		}
		(*e2).loc = temp;
		printpattern();
		(*e2).type = (*temp).tp_n;
		printpattern();
	}
}

void print_list(list *root)
{
	int flag=0;
	printpattern();
	while(root!=NULL)
	{
		pf("%d ",root->index);
		printpattern();
		flag=1;
		printpattern();
		root=root->next;
	}
	if(flag==0)
	{
		printpattern();
		pf("Empty List\n");
	}
	else
	{
		printpattern();
		pf("\n");
	}
}
void conv2Bool(expresn *e)
{
	if(((*e).type)->basetp!=tp_bool)
	{
		((*e).type) = new type_n(tp_bool);
		printpattern();
		(*e).falselist=makelist(next_instr);
		printpattern();
		glob_quad.emit(Q_IF_EQUAL,(*e).loc->name,"0","-1");
		printpattern();
		(*e).truelist = makelist(next_instr);
		printpattern();
		glob_quad.emit(Q_GOTO,-1);
		printpattern();
	}
}
void update_nextinstr()
{
	instr_count++;
	if(debug_on==1)
	{
		std::cout<<"Current Line Number:"<<instr_count<<std::endl;
		printpattern();
		std::cout<<"Press [ENTER] to continue:";
		printpattern();
		std::cin.get();
		printpattern();
	}
}
void debug()
{
	printpattern();
	if(debug_on==1)
		std::cout<<instr_count<<std::endl;
	printpattern();
}

int main()
{
	instr_count = 0;   // count of instr (used for sanity check)
	debug_on= 0;       // debugging is off
	symdata *temp_printi=new symdata("printInt");
	(*temp_printi).tp_n=new type_n(tp_int);
	(*temp_printi).var_type="func";
	(*temp_printi).nest_tab=glob_st;
	(*glob_st).symbol_tab.pb(temp_printi);
	
	symdata *temp_readi=new symdata("readInt");
	temp_readi->tp_n=new type_n(tp_int);
	temp_readi->var_type="func";
	temp_readi->nest_tab=glob_st;
	(*glob_st).symbol_tab.pb(temp_readi);
	
	symdata *temp_prints=new symdata("printStr");
	(*temp_prints).tp_n=new type_n(tp_int);
	(*temp_prints).var_type="func";
	(*temp_prints).nest_tab=glob_st;
	(*glob_st).symbol_tab.pb(temp_prints);
	yyparse();
	(*glob_st).name="Global";
	pf("_________________________________________________________________________________");
	pf("\nGenerated Quads for the program\n");
	glob_quad.print();
	pf("_________________________________________________________________________________\n");
	pf("Symbol table Maintained For the Given Program\n");
	(*glob_st).print();
	set<string> setty;
	setty.insert("Global");
	pf("_________________________________________________________________________________\n");
	FILE *fp;
	fp = fopen("output.s","w");
	fprintf(fp,"\t.file\t\"output.s\"\n");
	for (int i = 0; i < strings_label.size(); ++i)
	{
		fprintf(fp,"\n.STR%d:\t.string %s",i,strings_label[i].c_str());	
	}
	set<string>setty_1;
	(*glob_st).mark_labels();
	(*glob_st).global_variables(fp);
	setty_1.insert("Global");
	int count_l=0;
	for (int i = 0; i < (*glob_st).symbol_tab.size(); ++i)
	{
		if((((*glob_st).symbol_tab[i])->nest_tab)!=NULL)
		{
			if(setty_1.find((((*glob_st).symbol_tab[i])->nest_tab)->name)==setty_1.end())
			{
				(*glob_st).symbol_tab[i]->nest_tab->assign_offset();
				(*glob_st).symbol_tab[i]->nest_tab->print();
				(*glob_st).symbol_tab[i]->nest_tab->function_prologue(fp,count_l);
				(*glob_st).symbol_tab[i]->nest_tab->function_restore(fp);
				(*glob_st).symbol_tab[i]->nest_tab->gen_internal_code(fp,count_l);
				setty_1.insert((((*glob_st).symbol_tab[i])->nest_tab)->name);
				(*glob_st).symbol_tab[i]->nest_tab->function_epilogue(fp,count_l,count_l);
				count_l++;
			}
		}
	}
	fprintf(fp,"\n");
	return 0;
}
