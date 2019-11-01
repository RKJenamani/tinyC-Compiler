#include "ass6_17CS30038_17CS10061_translator.h"
#include "y.tab.h"

#define fpf fprintf

extern quad_arr glob_quad;
extern int next_instr;
map<int,int> mp_set;
stack<string> params_stack;
stack<int> types_stack;
stack<int> offset_stack;
stack<int> ptrarr_stack;
extern std::vector< string > vs;
extern std::vector<string> cs;
int add_off;
void printdebug()
{ return;}
void symtab::mark_labels()
{
	int count=1;
	printdebug();
	for(int i=0;i<next_instr;i++)
	{
		printdebug();
		switch(glob_quad.arr[i].op)
		{
			case Q_GOTO: printdebug();
			case Q_IF_EQUAL: printdebug();
			case Q_IF_NOT_EQUAL: printdebug();
			case Q_IF_EXPRESSION: printdebug();
			case Q_IF_NOT_EXPRESSION: printdebug();
			case Q_IF_LESS: printdebug();
			case Q_IF_GREATER: printdebug();
			case Q_IF_LESS_OR_EQUAL: printdebug();
			case Q_IF_GREATER_OR_EQUAL: printdebug();
			if(glob_quad.arr[i].result!="-1")
			{	
				printdebug();
				if(mp_set.find(atoi(glob_quad.arr[i].result.c_str()))==mp_set.end())
				{
					printdebug();
					mp_set[atoi(glob_quad.arr[i].result.c_str())]=count;
					printdebug();
					count++;
					printdebug();				
				}
			}
		}
	}
}

void symtab::function_prologue(FILE *fp,int count)
{
	printdebug();
	fpf(fp,"\n\t.globl\t%s",name.c_str());
	printdebug();
	fpf(fp,"\n\t.type\t%s, @function",name.c_str());
	printdebug();
	fpf(fp,"\n%s:",name.c_str());
	printdebug();
	fpf(fp,"\n.LFB%d:",count);
	printdebug();
	fpf(fp,"\n\tpushq\t%%rbp");
	printdebug();
	fpf(fp,"\n\tmovq\t%%rsp, %%rbp");
	printdebug();
	int t=-offset;
	printdebug();
	fpf(fp,"\n\tsubq\t$%d, %%rsp",t);
	printdebug();
}

void symtab::global_variables(FILE *fp)
{
	printdebug();
	for(int i=0;i<symbol_tab.size();i++)
	{
		printdebug();
		if(symbol_tab[i]->name[0]!='t' &&symbol_tab[i]->tp_n!=NULL&&symbol_tab[i]->var_type!="func")
		{
			printdebug();
			if(symbol_tab[i]->tp_n->basetp==tp_int)
			{
				printdebug();
				vs.push_back(symbol_tab[i]->name);
				printdebug();
				if(symbol_tab[i]->isInitialized==false)
				{
					printdebug();
					fpf(fp,"\n\t.comm\t%s,4,4",symbol_tab[i]->name.c_str());
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\t.globl\t%s",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.data");
					printdebug();
					fpf(fp,"\n\t.align 4");
					printdebug();
					fpf(fp,"\n\t.type\t%s, @object",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.size\t%s ,4",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n%s:",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.long %d",symbol_tab[i]->i_val.int_val);
					printdebug();
				}
		    }
		    if(symbol_tab[i]->tp_n->basetp==tp_char)
			{
				printdebug();
				cs.push_back(symbol_tab[i]->name);
				printdebug();
				if(symbol_tab[i]->isInitialized==false)
				{
					printdebug();
					fpf(fp,"\n\t.comm\t%s,1,1",symbol_tab[i]->name.c_str());
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\t.globl\t%s",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.data");
					printdebug();
					fpf(fp,"\n\t.type\t%s, @object",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.size\t%s ,1",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n%s:",symbol_tab[i]->name.c_str());
					printdebug();
					fpf(fp,"\n\t.byte %c",symbol_tab[i]->i_val.char_val);
					printdebug();
				}
				printdebug();
		    }
			printdebug();
		}
		printdebug();
	}
	printdebug();
	fpf(fp,"\n\t.text");
	printdebug();
}
void symtab::assign_offset()
{
	int curr_offset=0;
	int param_offset=16;
	no_params=0;
	printdebug();
	for(int i = (symbol_tab).size()-1; i>=0; i--)
    {
		printdebug();
        if(symbol_tab[i]->ispresent==false)
        	continue;
		printdebug();
        if(symbol_tab[i]->var_type=="param" && symbol_tab[i]->isdone==false)
        {
			printdebug();
        	no_params++;
			printdebug();
        	if(symbol_tab[i]->tp_n && symbol_tab[i]->tp_n->basetp==tp_arr)
        	{
				printdebug();
        		if(symbol_tab[i]->tp_n->size==-1)
        		{
					printdebug();
        			symbol_tab[i]->isptrarr=true;
					printdebug();
        		}
				printdebug();
        		symbol_tab[i]->size=8;
				printdebug();
        	}
			printdebug();
        	symbol_tab[i]->offset=curr_offset-symbol_tab[i]->size;
			printdebug();
        	curr_offset=curr_offset-symbol_tab[i]->size;
			printdebug();
        	symbol_tab[i]->isdone=true;
			printdebug();
        }
        if(no_params==6)
        	break;
		printdebug();
    }
    for(int i = 0; i<(symbol_tab).size(); i++)
    {
        if(symbol_tab[i]->ispresent==false)
        	continue;
		printdebug();
        if(symbol_tab[i]->var_type!="return"&&symbol_tab[i]->var_type!="param" && symbol_tab[i]->isdone==false)
        {
			printdebug();
        	symbol_tab[i]->offset=curr_offset-symbol_tab[i]->size;
			printdebug();
        	curr_offset=curr_offset-symbol_tab[i]->size;
			printdebug();
        	symbol_tab[i]->isdone=true;
			printdebug();
        }
        else if(symbol_tab[i]->var_type=="param" && symbol_tab[i]->isdone==false)
        {
			printdebug();
        	if(symbol_tab[i]->tp_n && symbol_tab[i]->tp_n->basetp==tp_arr)
        	{
				printdebug();
        		if(symbol_tab[i]->tp_n->size==-1)
        		{
					printdebug();
        			symbol_tab[i]->isptrarr=true;
					printdebug();
        		}
				printdebug();
        		symbol_tab[i]->size=8;
				printdebug();
        	}
			printdebug();
        	symbol_tab[i]->isdone=true;
			printdebug();
        	no_params++;
			printdebug();
        	symbol_tab[i]->offset=param_offset;
			printdebug();
        	param_offset=param_offset+symbol_tab[i]->size;
			printdebug();
        }
		printdebug();
    }
	printdebug();
    offset=curr_offset;
	printdebug();
}
string symtab::assign_reg(int type_of,int no)
{
	string s="NULL";
	printdebug();
	if(type_of==tp_char){
		printdebug();
        switch(no){
            case 0: 
					printdebug();
            		s = "dil";
					printdebug();
                    break;
            case 1: 
					printdebug();
            		s = "sil";
					printdebug();
                    break;
            case 2: 
					printdebug();
            		s = "dl";
					printdebug();
                    break;
            case 3: 
					printdebug();
            		s = "cl";
					printdebug();
                    break;
            case 4: 
					printdebug();
            		s = "r8b";
					printdebug();
                    break;
            case 5: 
					printdebug();
            		s = "r9b";
					printdebug();
                    break;
        }
		printdebug();
    }
    else if(type_of == tp_int){
        switch(no){
            case 0: 
					printdebug();
            		s = "edi";
					printdebug();
                    break;
            case 1: 
            		printdebug();
            		s = "esi";
					printdebug();
                    break;
            case 2: 
            		printdebug();
            		s = "edx";
					printdebug();
                    break;
            case 3: 
            		printdebug();
            		s = "ecx";
					printdebug();
                    break;
            case 4: 
            		printdebug();
            		s = "r8d";
					printdebug();
                    break;
            case 5: 
            		printdebug();
            		s = "r9d";
					printdebug();
                    break;
        }
		printdebug();
    }
    else
    {
        switch(no){
            case 0: 
            		printdebug();
            		s = "rdi";
					printdebug();
                    break;
            case 1: 
            		printdebug();
            		s = "rsi";
					printdebug();
                    break;
            case 2: 
            		printdebug();
            		s = "rdx";
					printdebug();
                    break;
            case 3: 
            		printdebug();
            		s = "rcx";
					printdebug();
                    break;
            case 4: 
            		printdebug();
            		s = "r8";
					printdebug();
                    break;
            case 5: 
            		printdebug();
            		s = "r9";
					printdebug();
                    break;
        }
		printdebug();
    }
	printdebug();
    return s;
}
int symtab::function_call(FILE *fp)
{
	
	int c=0;
	printdebug();
	fpf(fp,"\n\tpushq %%rbp");
	printdebug();
	int count=0;
	printdebug();
	while(count<6 && params_stack.size())
	{
		printdebug();
		string p=params_stack.top();
		printdebug();
		int btp=types_stack.top();
		printdebug();
		int off=offset_stack.top();
		printdebug();
		int parr=ptrarr_stack.top();
		printdebug();
		params_stack.pop();
		printdebug();
		types_stack.pop();
		printdebug();
		offset_stack.pop();
		printdebug();
		ptrarr_stack.pop();
		printdebug();
		string temp_str=assign_reg(btp,count);
		printdebug();
		if(temp_str!="NULL")
		{
			printdebug();
			if(btp==tp_int)
			{	
				printdebug();
				fpf(fp,"\n\tmovl\t%d(%%rbp) , %%%s",off,temp_str.c_str());
				printdebug();
			}
			else if(btp==tp_char)
			{
				printdebug();
				fpf(fp,"\n\tmovb\t%d(%%rbp), %%%s",off,temp_str.c_str());
				printdebug();
			}
			else if(btp==tp_arr && parr==1)
			{
				printdebug();
				fpf(fp,"\n\tmovq\t%d(%%rbp), %%%s",off,temp_str.c_str());
				printdebug();
			}
			else if(btp==tp_arr)
			{
				printdebug();
				fpf(fp,"\n\tleaq\t%d(%%rbp), %%%s",off,temp_str.c_str());
				printdebug();
			}
			else
			{
				printdebug();
				fpf(fp,"\n\tmovq\t%d(%%rbp), %%%s",off,temp_str.c_str());
				printdebug();
			}
			printdebug();
			count++;
			printdebug();
		}
		printdebug();
	}
	while(params_stack.size())
	{
		printdebug();
		string p=params_stack.top();
		printdebug();
		int btp=types_stack.top();
		printdebug();
		int off=offset_stack.top();
		printdebug();
		int parr=ptrarr_stack.top();
		printdebug();
		params_stack.pop();
		printdebug();
		types_stack.pop();
		printdebug();
		offset_stack.pop();
		printdebug();
		ptrarr_stack.pop();
		printdebug();
		if(btp==tp_int)
		{	
			printdebug();
			fpf(fp,"\n\tsubq $4, %%rsp");
			printdebug();
			fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off);
			printdebug();
			fpf(fp,"\n\tmovl\t%%eax, (%%rsp)");
			printdebug();
			c+=4;
			printdebug();
		}
		else if(btp==tp_arr && parr==1)
		{
			printdebug();
			fpf(fp,"\n\tsubq $8, %%rsp");
			printdebug();
			fpf(fp,"\n\tmovq\t%d(%%rbp), %%rax",off);
			printdebug();
			fpf(fp,"\n\tmovq\t%%rax, (%%rsp)");
			printdebug();
			c+=8;
			printdebug();
		}
		else if(btp==tp_arr)
		{
			printdebug();
			fpf(fp,"\n\tsubq $8, %%rsp");
			printdebug();
			fpf(fp,"\n\tleaq\t%d(%%rbp), %%rax",off);
			printdebug();
			fpf(fp,"\n\tmovq\t%%rax, (%%rsp)");
			printdebug();
			c+=8;
			printdebug();
		}
		else if(btp==tp_char)
		{
			printdebug();
			fpf(fp,"\n\tsubq $4, %%rsp");
			printdebug();
			fpf(fp,"\n\tmovsbl\t%d(%%rbp), %%eax",off);
			printdebug();
			fpf(fp,"\n\tmovl\t%%eax, (%%rsp)");
			printdebug();
			c+=4;
			printdebug();
		}
		else
		{
			printdebug();
			fpf(fp,"\n\tsubq $8, %%rsp");
			printdebug();
			fpf(fp,"\n\tmovq\t%d(%%rbp), %%rax",off);
			printdebug();
			fpf(fp,"\n\tmovq\t%%rax, (%%rsp)");
			printdebug();
			c+=8;
			printdebug();
		}
		printdebug();
	}
	printdebug();
	return c;
	
}
void symtab::function_restore(FILE *fp)
{
	printdebug();
	int count=0;
	printdebug();
	string regname;
	printdebug();
	for(int i=symbol_tab.size()-1;i>=0;i--)
	{
		printdebug();
	    if(symbol_tab[i]->ispresent==false)
	    	continue;
		printdebug();
	    if(symbol_tab[i]->var_type=="param" && symbol_tab[i]->offset<0)
	    {
			printdebug();
		    if(symbol_tab[i]->tp_n->basetp == tp_char){
				printdebug();
	            regname = assign_reg(tp_char,count);
				printdebug();
	            fpf(fp,"\n\tmovb\t%%%s, %d(%%rbp)",regname.c_str(),symbol_tab[i]->offset);
				printdebug();
	        }
	        else if(symbol_tab[i]->tp_n->basetp == tp_int){
				printdebug();
	            regname = assign_reg(tp_int,count);
				printdebug();
	            fpf(fp,"\n\tmovl\t%%%s, %d(%%rbp)",regname.c_str(),symbol_tab[i]->offset);
				printdebug();
	        }
	        else {
				printdebug();
	            regname = assign_reg(10,count);
				printdebug();
	            fpf(fp,"\n\tmovq\t%%%s, %d(%%rbp)",regname.c_str(),symbol_tab[i]->offset);
				printdebug();
	        }
			printdebug();
	    	count++;
			printdebug();
	    }
		printdebug();
	    if(count==6)
	    	break;
		printdebug();
    }
}
void symtab::gen_internal_code(FILE *fp,int ret_count)
{
	int i;			
	printdebug();	
	for(i = start_quad; i <=end_quad; i++)
	{
		printdebug();
		opcode &opx =glob_quad.arr[i].op;
		printdebug();
		string &arg1x =glob_quad.arr[i].arg1;
		printdebug();
		string &arg2x =glob_quad.arr[i].arg2;
		printdebug();
		string &resx =glob_quad.arr[i].result;
		printdebug();
		int offr,off1,off2;
		printdebug();
		int flag1=1;
		printdebug();
		int flag2=1;
		printdebug();
		int flag3=1;
		printdebug();
		int j;
		printdebug();
		fpf(fp,"\n# %d:",i);
		printdebug();
		if(search(resx))
		{
			printdebug();
			offr = search(resx)->offset;
			printdebug();
			fpf(fp,"res = %s ",search(resx)->name.c_str());
			printdebug();
		}
		else if(glob_quad.arr[i].result!=""&& findg(glob_quad.arr[i].result))
		{
			printdebug();
			flag3=0;
			printdebug();
		}
		if(search(arg1x))
		{
			printdebug();
			off1 = search(arg1x)->offset;
			printdebug();
			fpf(fp,"arg1 = %s ",search(arg1x)->name.c_str());
			printdebug();
		}
		else if(glob_quad.arr[i].arg1!="" && findg(glob_quad.arr[i].arg1))
		{
			printdebug();
			flag1=0;
			printdebug();		
		}
		if(search(arg2x))
		{
			printdebug();
			off2 = search(arg2x)->offset;
			printdebug();
			fpf(fp,"arg2 = %s ",search(arg2x)->name.c_str());
			printdebug();
		}
		else if(glob_quad.arr[i].arg2!="" && findg(glob_quad.arr[i].arg2))
		{
			printdebug();
			flag2=0;
			printdebug();
		}
		if(flag1==0)
		{
			printdebug();
			if(findg(arg1x)==2)
			{
				printdebug();
				fpf(fp,"\n\tmovzbl\t%s(%%rip), %%eax",arg1x.c_str());
				printdebug();
			}
			else
			{
				printdebug();
				fpf(fp,"\n\tmovl\t%s(%%rip), %%eax",arg1x.c_str());
				printdebug();
			}
			printdebug();
		}
		if(flag2==0)
		{
			printdebug();
			if(findg(arg1x)==2)
			{
				printdebug();
				fpf(fp,"\n\tmovzbl\t%s(%%rip), %%edx",arg2x.c_str());
				printdebug();
			}
			else
			{
				printdebug();
				fpf(fp,"\n\tmovl\t%s(%%rip), %%edx",arg2x.c_str());
				printdebug();
			}
			printdebug();
		}
		if(mp_set.find(i)!=mp_set.end())
		{
			//Generate Label here
			printdebug();
			fpf(fp,"\n.L%d:",mp_set[i]);
			printdebug();
		}
		switch(opx)
		{
			case Q_PLUS:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					if(flag1!=0)
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					if(flag2!=0)
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\taddl\t%%edx, %%eax");
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				else 
				{
					printdebug();
					if(flag1!=0)
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					if(flag2!=0)
					{
						if(arg2x[0]>='0' && arg2x[0]<='9')
						{
							printdebug();
							fpf(fp,"\n\tmovl\t$%s, %%edx",arg2x.c_str());
							printdebug();
						}
						else
						{
							printdebug();
							fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
							printdebug();
						}
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\taddl\t%%edx, %%eax");
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				printdebug();
				break;
			case Q_MINUS:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					if(flag2!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%edx",off2);
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\tsubl\t%%edx, %%eax");
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				else
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					// Direct Number access
					if(flag2!=0)
					{
						if(arg2x[0]>='0' && arg2x[0]<='9')
						{
							printdebug();
							fpf(fp,"\n\tmovl\t$%s, %%edx",arg2x.c_str());
							printdebug();
						}
						else
						{
							printdebug();
							fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
							printdebug();
						}
						printdebug();
					}
					fpf(fp,"\n\tsubl\t%%edx, %%eax");
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				printdebug();
				break;
			case Q_MULT:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					if(flag2!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%edx",off2);
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\timull\t%%edx, %%eax");
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				else
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					if(flag2!=0)
					{
						printdebug();
						if(arg2x[0]>='0' && arg2x[0]<='9')
						{
							printdebug();
							fpf(fp,"\n\tmovl\t$%s, %%ecx",arg2x.c_str());
							printdebug();
							fpf(fp,"\n\timull\t%%ecx, %%eax");
							printdebug();
						}
						else
						{
							printdebug();
							fpf(fp,"\n\timull\t%d(%%rbp), %%eax",off2);
							printdebug();
						}
						printdebug();
					}
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				printdebug();
				break;
			case Q_DIVIDE:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\tcltd");
					printdebug();
					if(flag2!=0)
					{
						printdebug();
						fpf(fp,"\n\tidivl\t%d(%%rbp), %%eax",off2);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tidivl\t%%edx, %%eax");
						printdebug();
					}
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovb\t%%al, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}
				else
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\tcltd");
					printdebug();
					if(flag2!=0)
					{
						printdebug();
						fpf(fp,"\n\tidivl\t%d(%%rbp), %%eax",off2);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tidivl\t%%edx, %%eax");
						printdebug();
					}
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %s(%%rip)",resx.c_str());
						printdebug();
					}
					printdebug();
				}	
				printdebug();
				break;
			case Q_MODULO:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcltd");
					printdebug();
					fpf(fp,"\n\tidivl\t%d(%%rbp), %%eax",off2);
					printdebug();
					fpf(fp,"\n\tmovl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcltd");
					printdebug();
					fpf(fp,"\n\tidivl\t%d(%%rbp), %%eax",off2);
					printdebug();
					fpf(fp,"\n\tmovl\t%%edx, %d(%%rbp)",offr);
					printdebug();
				}
				printdebug();
				break;
			case Q_UNARY_MINUS:
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tnegl\t%%eax");
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tnegl\t%%eax");
					printdebug();
					fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
					printdebug();
				}
				printdebug();
				break;
			case Q_ASSIGN:
				if(arg1x[0]>='0' && arg1x[0]<='9')
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t$%s, %d(%%rbp)",arg1x.c_str(),offr);
						printdebug();
					}
					printdebug();
				}
				else if(arg1x[0] == '\'')
				{
					//Character
					printdebug();
					fpf(fp,"\n\tmovb\t$%d, %d(%%rbp)",(int)arg1x[1],offr);
					printdebug();
				}
				else if(flag1 && search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
					printdebug();
				}
				else if(flag1&&search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_int)
				{
					printdebug();
					if(flag1!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
						printdebug();
					}
					printdebug();
					fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
					printdebug();
				}
				else if(search(resx)!=NULL && search(resx)->tp_n!=NULL)
				{
					printdebug();
					fpf(fp,"\n\tmovq\t%d(%%rbp), %%rax",off1);
					printdebug();
					fpf(fp,"\n\tmovq\t%%rax, %d(%%rbp)",offr);
					printdebug();
				}
				else
				{
					printdebug();
					if(flag3!=0)
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
						printdebug();
					}
					else
					{
						printdebug();
						fpf(fp,"\n\tmovl\t%%eax, %s(%%rip)",resx.c_str());
						printdebug();
					}
				}
				printdebug();
				break;
			case Q_PARAM:
				if(resx[0] == '_')
				{
					//string
					printdebug();
					char* temp = (char*)resx.c_str();
					printdebug();
					fpf(fp,"\n\tmovq\t$.STR%d,\t%%rdi",atoi(temp+1));
					printdebug();
				}
				else
				{
					params_stack.push(resx);
					printdebug();
					//printf("resx--> %s\n",resx.c_str());
					// printdebug();
					types_stack.push(search(resx)->tp_n->basetp);
					printdebug();
					offset_stack.push(offr);
					printdebug();
					if(search(resx)->isptrarr==true)
					{
						ptrarr_stack.push(1);
						printdebug();
					}
					else
					{
						ptrarr_stack.push(0);
						printdebug();
					}
				}
				printdebug();
				break;
			case Q_GOTO:
				if(resx!="-1"&& atoi(resx.c_str())<=end_quad)
					fpf(fp,"\n\tjmp .L%d",mp_set[atoi(resx.c_str())]);
				else 
					fpf(fp,"\n\tjmp\t.LRT%d",ret_count);
				printdebug();
				break;
			case Q_CALL:
				add_off=function_call(fp);
				printdebug();
				fpf(fp,"\n\tcall\t%s",arg1x.c_str());
				printdebug();
				if(resx=="")
				{
					printdebug();
				}
				else if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_int)
				{
					fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
					printdebug();
				}
				else if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
				}
				else if(search(resx)!=NULL && search(resx)->tp_n!=NULL)
				{
					printdebug();
					fpf(fp,"\n\tmovq\t%%rax, %d(%%rbp)",offr);	
				}
				else
				{	
					printdebug();
					fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
				}
				if(arg1x=="printStr")
				{
					printdebug();
					fpf(fp,"\n\taddq $8 , %%rsp");
				}
				else 
				{
					printdebug();
					fpf(fp,"\n\taddq $%d , %%rsp",add_off);
				}
				printdebug();
				break;
			case Q_IF_LESS:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tjl .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tjl .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				break;
			case Q_IF_LESS_OR_EQUAL:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tjle .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tjle .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				printdebug();
				break;
			case Q_IF_GREATER:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tjg .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tjg .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				printdebug();
				break;
			case Q_IF_GREATER_OR_EQUAL:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tjge .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tjge .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				printdebug();
				break;
			case Q_IF_EQUAL:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tje .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tje .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				break;
			case Q_IF_NOT_EQUAL:
				if(search(arg1x)!=NULL && search(arg1x)->tp_n!=NULL&&search(arg1x)->tp_n->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tcmpb\t%d(%%rbp), %%al",off2);
					printdebug();
					fpf(fp,"\n\tjne .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off1);
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off2);
					printdebug();
					fpf(fp,"\n\tcmpl\t%%edx, %%eax");
					printdebug();
					fpf(fp,"\n\tjne .L%d",mp_set[atoi(resx.c_str())]);
					printdebug();
				}
				printdebug();
				break;
			case Q_ADDR:
				printdebug();
				fpf(fp,"\n\tleaq\t%d(%%rbp), %%rax",off1);
				printdebug();
				fpf(fp,"\n\tmovq\t%%rax, %d(%%rbp)",offr);
				printdebug();
				break;
			case Q_LDEREF:
				printdebug();
				fpf(fp,"\n\tmovq\t%d(%%rbp), %%rax",offr);
				printdebug();
				fpf(fp,"\n\tmovl\t%d(%%rbp), %%edx",off1);
				printdebug();
				fpf(fp,"\n\tmovl\t%%edx, (%%rax)");
				printdebug();
				break;
			case Q_RDEREF:
				printdebug();
				fpf(fp,"\n\tmovq\t%d(%%rbp), %%rax",off1);
				printdebug();
				fpf(fp,"\n\tmovl\t(%%rax), %%eax");
				printdebug();
				fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
				printdebug();
				break;
			case Q_RINDEX:
				// Get Address, subtract offset, get memory
				if(search(arg1x)&&search(arg1x)->isptrarr==true)
				{
					fpf(fp,"\n\tmovq\t%d(%%rbp), %%rdx",off1);
					printdebug();
					fpf(fp,"\n\tmovslq\t%d(%%rbp), %%rax",off2);
					printdebug();
					fpf(fp,"\n\taddq\t%%rax, %%rdx");
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tleaq\t%d(%%rbp), %%rdx",off1);
					printdebug();
					fpf(fp,"\n\tmovslq\t%d(%%rbp), %%rax",off2);
					printdebug();
					fpf(fp,"\n\taddq\t%%rax, %%rdx");
					printdebug();
				}
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->next&&search(resx)->tp_n->next->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t(%%rdx), %%eax");
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, %d(%%rbp)",offr);
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t(%%rdx), %%eax");
					printdebug();
					fpf(fp,"\n\tmovl\t%%eax, %d(%%rbp)",offr);
					printdebug();
				}
				break;
			case Q_LINDEX:
				if(search(resx)&&search(resx)->isptrarr==true)
				{
					printdebug();
					fpf(fp,"\n\tmovq\t%d(%%rbp), %%rdx",offr);
					printdebug();
					fpf(fp,"\n\tmovslq\t%d(%%rbp), %%rax",off1);
					printdebug();
					fpf(fp,"\n\taddq\t%%rax, %%rdx");
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tleaq\t%d(%%rbp), %%rdx",offr);
					printdebug();
					fpf(fp,"\n\tmovslq\t%d(%%rbp), %%rax",off1);
					printdebug();
					fpf(fp,"\n\taddq\t%%rax, %%rdx");
					printdebug();
				}
				if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->next && search(resx)->tp_n->next->basetp == tp_char)
				{
					printdebug();
					fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",off2);
					printdebug();
					fpf(fp,"\n\tmovb\t%%al, (%%rdx)");
					printdebug();
				}
				else
				{
					printdebug();
					fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",off2);
					printdebug();
					fpf(fp,"\n\tmovl\t%%eax, (%%rdx)");
					printdebug();
				}
				printdebug();
				break;
			case Q_RETURN:
				//printf("return %s\n",resx.c_str());
				if(resx!="")
				{
					printdebug();
					if(search(resx)!=NULL && search(resx)->tp_n!=NULL&&search(resx)->tp_n->basetp == tp_char)
					{
						fpf(fp,"\n\tmovzbl\t%d(%%rbp), %%eax",offr);
						printdebug();
					}
					else
					{
						fpf(fp,"\n\tmovl\t%d(%%rbp), %%eax",offr);
						printdebug();
					}
					printdebug();
				}
				else
				{
					fpf(fp,"\n\tmovl\t$0, %%eax");
					printdebug();
				}
				//printf("Happy\n");
				fpf(fp,"\n\tjmp\t.LRT%d",ret_count);
				printdebug();
				break;
			default:
			break;
		}
	}
}

void symtab::function_epilogue(FILE *fp,int count,int ret_count)
{
	printdebug();
	fpf(fp,"\n.LRT%d:",ret_count);
	printdebug();
	fpf(fp,"\n\taddq\t$%d, %%rsp",offset);
	printdebug();
	fpf(fp,"\n\tmovq\t%%rbp, %%rsp");
	printdebug();
	fpf(fp,"\n\tpopq\t%%rbp");
	printdebug();
	fpf(fp,"\n\tret");
	printdebug();
	fpf(fp,"\n.LFE%d:",count);
	printdebug();
	fpf(fp,"\n\t.size\t%s, .-%s",name.c_str(),name.c_str());
	printdebug();
}

