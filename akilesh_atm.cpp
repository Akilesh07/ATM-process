#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int load_cash();
int customer_details_entry();
int maintain_customer_details();
int handle_atm_operations();
int user_account(int);
int isvalid(int);
int Check_Balance(int);
int Withdraw_Money(int);
int Transfer_Money(int);
int check_ATM_balance();

struct denominations{
    int two_thousands,five_hundreds,hundreds;
}d;

struct customer_entry{
    int acc_no;
    char Name[50];
    int pin;
    int acc_balance;
}s[100];

int total_balance_in_ATM=0 , no_of_customers = 5;

int load_cash(){	
	cout<<"Enter the number of Two Thousands:\t";
	cin>>d.two_thousands;
	cout<<"Enter the number of Five Hundreds:\t";
	cin>>d.five_hundreds;
	cout<<"Enter the number of Hundreds:\t\t";
	cin>>d.hundreds;
	total_balance_in_ATM += (2000*d.two_thousands)+(500*d.five_hundreds)+(100*d.hundreds);
	cout<<"\n-------------------------------------------------------\n";
	cout<<"Denomination\tNumber\t\tValue\n";
	cout<<"-------------------------------------------------------\n";
	cout<<"2000\t\t"<<d.two_thousands<<"\t\t"<<2000*d.two_thousands<<endl;
	cout<<"-------------------------------------------------------\n";
    cout<<"500\t\t"<<d.five_hundreds<<"\t\t"<<500*d.five_hundreds<<endl;
	cout<<"-------------------------------------------------------\n";
    cout<<"100\t\t"<<d.hundreds<<"\t\t"<<100*d.hundreds<<endl;
	cout<<"-------------------------------------------------------\n";	
	cout<<"Total available cash in the ATM is : "<<total_balance_in_ATM<<endl;
	return 0;
}

int customer_details_entry()
{
    s[0].acc_no =101;
    strcpy(s[0].Name,"Suresh");
    s[0].pin = 2343;
    s[0].acc_balance = 25234;
    
    s[1].acc_no =102;
    strcpy(s[1].Name,"Ganesh");
    s[1].pin = 5432;
    s[1].acc_balance = 34123;
    
    s[2].acc_no =103;
    strcpy(s[2].Name,"Magesh");
    s[2].pin = 7854;
    s[2].acc_balance = 26100;
    
    s[3].acc_no =104;
    strcpy(s[3].Name,"Naresh");
    s[3].pin = 2345;
    s[3].acc_balance = 80000;
    
    s[4].acc_no =105;
    strcpy(s[4].Name,"Harish");
    s[4].pin = 1907;
    s[4].acc_balance = 103400;
    	return 0;
}

int maintain_customer_details(){
    int i;
    cout<<"-----------------------------------------------------\n";
    cout<<"Acc_No\tAccount_Holder\tPin_Number\tAccount_Balance\n";
    cout<<"-----------------------------------------------------\n";
    for(i=0;i<no_of_customers;i++)
	    cout<<s[i].acc_no<<"\t"<<s[i].Name<<"\t\t"<<s[i].pin<<"\t\t "<<s[i].acc_balance<<endl;
		cout<<"---------------------------------------------------\n";    
		return 0;
}

int handle_atm_operations()
{
	int choices,pin,acc_no,flag;
	cout<<"1. Check Balance\n";
	cout<<"2. Withdraw Money\n";
	cout<<"3. Transfer Money\n";
    cout<<"Enter the operation to be performed: ";
    cin>>choices;
	if(choices>0 & choices<4)
	{
		cout<<"Enter your account number \n";
		cin>>acc_no;
		if(acc_no == s[0].acc_no)
			flag = 0;
		else if(acc_no == s[1].acc_no)
			flag = 0;
		else if(acc_no == s[2].acc_no)
			flag = 0;
		else if(acc_no == s[3].acc_no)
			flag = 0;
		else if(acc_no == s[4].acc_no)
			flag = 0;
		else 
			flag = 1;
			
		if(flag==0)
		{
			cout<<"Enter you Pin\n";
			cin>>pin;
			if(isvalid(pin))
			{
				switch(choices)
				{
					case 1:
						Check_Balance(pin);
						break;
					case 2:
						Withdraw_Money(pin);
						break;
					case 3:
						Transfer_Money(pin);
						break;
					default:
					cout<<"Invalid Entry";
						break;
				}
			}
		}
	}
		return 0;
}
 
int user_account(int p)
{
	if(p == s[0].pin)
		return 0;
	else if(p == s[1].pin)
		return 1;
	else if(p == s[2].pin)
		return 2;
	else if(p == s[3].pin)
		return 3;
	else if(p == s[4].pin)
		return 4;
	else 
		return -1;
	return 0;
}

int isvalid(int p)
{
	if(user_account(p) == -1)
		return 0;
	
	return 1;
}

int Check_Balance(int p)
{
	int i;
	i = user_account(p);
	cout<<i;
	cout<<"---------------------------------------------------\n";
	cout<<"Your Account Balance is : "<<s[i].acc_balance;
	cout<<"\n---------------------------------------------------\n";	
	return 0;
}


int Withdraw_Money(int p)
{
	int i,amt;
	cout<<"NOTE : Your withdrawal money should be above 100 and below 10000\n";
	cout<<"Enter the Amount to be Withdrawn : ";
	cin>>amt;
	if(amt<100 || amt>10000 || amt%100 != 0)        // condition for amount<10000
		cout<<"Enter the valid amount\n";
	else if(amt>total_balance_in_ATM)
		cout<<"The ATM has insufficient funds";
	else
		{
			i = user_account(p);
			if(amt > s[i].acc_balance)
				cout<<"The account balance is lower than entered withdrawal amount";
			else
			{
				int amtt = amt;
				if(amtt<=5000){
					if(amtt>=1500){
						int hun;
						hun = ((amtt%500)/100)+10;      // minimum 10 hundreds + (1-4) hundreds are given
						d.hundreds -= hun;              // now amount will surely be divisible by 500
						amtt -= hun*100;	            
						d.two_thousands -= amtt/2000;     // minimum one 2000 note will be given
			  			amtt = amtt%2000;
			  			d.five_hundreds -= amtt/500;      
				  	}
				  	else{
				  		d.hundreds -= amtt/100;	            // for amounts less than 1500 we can fully give 100s
					}
				}
				else{
						int hun;
						hun = (amtt%500)/100);          // maximum of 5 hundreds only
						d.hundreds -= hun;              // now amount will surely be divisible by 500
						amtt -= hun*100;	            
						d.two_thousands -= amtt/2000;     // minimum two 2000 note will be given
			  			amtt = (amtt%2000)+2000;
			  			d.five_hundreds -= amtt/500;      // minimum 2 500s will be given as 2000 has been subtracted		
				}
				s[i].acc_balance -= amt;			  	
			  	total_balance_in_ATM -= amt;
				cout<<"-----Please Collect the Cash-----Visit again------\n";
			}
		}
			return 0;
}

int Transfer_Money(int p)
{
    int amt,i,j,acc,valid;
	cout<<"NOTE: Max transfer limit per transaction is above 1000 and below 10000\n";
 	cout<<"Enter the Amount to be transfered : ";
 	cin>>amt;
	if(amt<100 || amt>10000 || amt%100 != 0)
		cout<<"Enter the valid amount\n";
 	i = user_account(p);
 	if(amt > s[i].acc_balance)
	   cout<<"Account balance is lower than entered amount\n"; 
	else
	{
		cout<<"Enter the Account Number to which the money has to be transfered : ";
	  	cin>>acc;
	  	for(j=0;j<no_of_customers;j++)
	  	{
	  		if(s[j].acc_no == acc)
	  		   {
				 valid = 1;
	  		     break;
				} 
		  }
		if(valid)
		{
		  	s[i].acc_balance -= amt;
		  	s[j].acc_balance += amt;
		  	cout<<"-------------TRANSACTION SUCCESSFULL-------------\n";
		}
		else
		 cout<<"Invalid Account number\n";
	}	  
		return 0;
 }


int check_ATM_balance()
{
	int total=total_balance_in_ATM;
	cout<<"\n-------------------------------------------------------\n";
	cout<<"Denomination\tNumber\t\tValue\n";
	cout<<"-------------------------------------------------------\n";
	cout<<"2000\t\t"<<d.two_thousands<<"\t\t"<<2000*d.two_thousands<<endl;
	cout<<"-------------------------------------------------------\n";
    cout<<"500\t\t"<<d.five_hundreds<<"\t\t"<<500*d.five_hundreds<<endl;
	cout<<"-------------------------------------------------------\n";
    cout<<"100\t\t"<<d.hundreds<<"\t\t"<<100*d.hundreds<<endl;
	cout<<"-------------------------------------------------------\n";	
    cout<<"Total available cash in the ATM is : "<<total<<endl;
		return 0;
}

int main()
{
	int choice;
	customer_details_entry();
    do{
        cout<<"\n-----------Welcome to the ATM service--------------\n";
		cout<<"1. Load Cash to ATM\n";
    	cout<<"2. Maintain Customer Details\n";
		cout<<"3. Handle ATM Process\n";
		cout<<"4. Check ATM Balance\n";
		cout<<"5. Quit\n";
		cout<<"---------------------------------------------------\n\n";
    	cout<<"Enter your choice: \n ";
		cin>>choice;
        switch(choice)
        {
		case(1):
            		load_cash();
            		break;
		case(2):
	        		maintain_customer_details();
                	break;
		case(3):
                	handle_atm_operations();
                	break;
		case(4):
					check_ATM_balance();
            		break;
	}
    }while(choice!=5);
    
    return 0;
}
