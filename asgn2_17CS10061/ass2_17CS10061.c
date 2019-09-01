#define MAX_BUFF_SIZE 100 
// #include <stdio.h>
int printStr(char *input_string)		 // prints string "input_string"		
{
	char buffer[MAX_BUFF_SIZE]; 		
	int i;
	for(i=0;input_string[i]!='\0';i++)
		buffer[i]=input_string[i];			// copyings contents of string into buffer	

	int num_bytes = i;

	__asm__ __volatile__ (				
	"movl $1, %%eax \n\t"				
	"movq $1, %%rdi \n\t"					
	"syscall \n\t"
	:										
	:"S"(buffer), "d"(num_bytes)				
	);
	return num_bytes;					
}
int readInt(int *num_pointer)					// reads an Integer		
{
	char buffer[1];
	char temp[20];
	int validity_flag=1; 						//1-> Valid Int 0-> Invalid Int
	int length=0;								//length of string
	while(1) 
	{
	 	__asm__ __volatile__ 
	 	(
	 		"syscall"
	 		:
	 		:"a"(0), "D"(0), "S"(buffer), "d"(1)		
	 	);

		if(buffer[0]==' ' || buffer[0]=='\t'|| buffer[0]=='\n') 
			break;							
		else if ((((int)buffer[0] <= '0' + 9 && (int)buffer[0] >= 0 + '0') ) || buffer[0]=='-') 
			temp[length++]=buffer[0];							
		else
			validity_flag=0;
	}
	if(validity_flag==0 || (temp[0]=='-' && length==1) )								
	{
		*num_pointer=1;
		return 0;
	}	
	if(!( length>0 && length<=9 )){						
		return 0;
	}
	int num=0;
	int start_index = (temp[0]=='-')? 1:0;  // starts from 1 when negative as temp[0]=='-'
	for(int i=start_index ; i<length ;i++)			 
	{
		num*=10;
		if(temp[i]=='-')  					// is any "-" in between then error!
		{
			*num_pointer=1;
			return 0;
		}
		num+=temp[i]-'0';
	}
	*num_pointer= (temp[0]=='-')? -num: num; 		//if num is negative num_pointer = -num;
	return 1;
}

int printInt(int n) 								//Prints an Integer
{
	char buff[MAX_BUFF_SIZE], zero='0';		
	int i=0;
	if(n == 0) 
		buff[i++]=zero;			
	else
	{
		int j,k,bytes;
		if(n < 0) 
		{
			buff[i++]='-';		
			n = -n;				
		}
		while(n)
		{
			int rem = n%10;		
			buff[i++] = (char)(zero+rem);	
			n /= 10;				
		}
		if(buff[0] == '-') 		
			j = 1;
		else j = 0;
			k=i-1;
		while(j<k)					
		{
			char temp=buff[j];		
			buff[j++] = buff[k];	
			buff[k--] = temp;		
		}
		buff[i]='\n';				
		bytes = i+1;
		__asm__ __volatile__ 
		(
			"movl $1, %%eax \n\t"
			"movq $1, %%rdi \n\t"
			"syscall \n\t"
			:
			:"S"(buff), "d"(bytes)
		);

	}
		return i;
}

int readFlt(float *num_pointer)
{
	char buffer[1];
	char temp[20];
	int validity_flag=1;
	int length=0;
	while (1) {
	 __asm__ __volatile__ ("syscall"::"a"(0), "D"(0), "S"(buffer), "d"(1));		
		if(buffer[0]==' ' || buffer[0]=='\t' || buffer[0]=='\n') break;				
		else if ((((int)buffer[0] <= '0' + 9 && (int)buffer[0] >= 0 + '0') ) || buffer[0]=='-' || buffer[0]=='.') 
			temp[length++]=buffer[0];							
		else
			validity_flag=0;
	}
	if(length > 12 || length == 0 )
	{																			
		return 0;
	}
	if(validity_flag==0 || (temp[0]=='-' && length==1))
	{
		*num_pointer=1;
		return 0;
	}	
	int p=1;
	int dec_flag=0;
	float num=0.0;
	int start_index = (temp[0]=='-')? 1:0;
	for(int i=start_index;i<length;i++)
	{
		// printf("i:%d",i);
		if(temp[i]=='-')
		{
			*num_pointer=1;
			return 0;
		}
		if(temp[i]=='.')
		{
			if(dec_flag==0)
			{
				dec_flag=1;
			}
			else
			{
				*num_pointer=1;
				return 0;
			}
			continue;
		}
		if(dec_flag)
		{
			p*=10;
			num+=((float)((int)temp[i]-'0'))/p;
		}
		else
		{
			num*=10;				
			num+=((int)temp[i]-'0');
		}			
	}
	*num_pointer = (temp[0]=='-')? -num: num;
	return 1;
}
int printFlt(float input_num)
{
	char buffer[MAX_BUFF_SIZE];
	int i=0,j;
	int count=0;
	int bytes=0;
	if(input_num==0) 
		buffer[0]='0';
	else 
	{
		int negative=0;
		if(input_num<0) 
		{
			buffer[0]='-';
			count++;
			negative=1;
			input_num=-input_num;
		}		
		int t = (int) input_num;
		while ( !( ( input_num - ((int)input_num) ) < 0.00001 || ( ((int)input_num) - input_num ) > 0.00001) ) //checking for equality in double			
		{
			// printf("num:%f\n",input_num);
			input_num*=10.0;
			count++;			
		}
		// printf("Input_num:%f\ncount%d\n",input_num,count);
		int decimal_index=count;
		do
		{
			count++;
			t=t/10;
		}while(t!=0);
		decimal_index = count - decimal_index+negative;
		// printf("decimal_index:%d\n",decimal_index);
		i=count+1;
		int int_input_num = (int)input_num;
		int remainder = 0;
		while(count>=negative) 
		{
			if (count==decimal_index)
			{
				// printf(".\n"); 
				buffer[count--]='.';	
			}	
			else 
			{
				remainder=int_input_num%10;
				// printf("%d-%d\n",count,remainder);
				buffer[count--]=(char)(remainder+'0');
				int_input_num/=10.0;
			}
		}
	}
	buffer[i]='\n';
	bytes=i+1;

	__asm__ __volatile__ 
	(
		"movl $1, %%eax \n\t"
		"movq $1, %%rdi \n\t"
		"syscall \n\t"
		:
		:"S"(buffer),"d"(bytes)
	);
	return bytes;
}
