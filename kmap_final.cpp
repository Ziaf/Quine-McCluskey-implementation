#include<iostream>
#include<conio.h>
#include<vector>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<stdio.h>
#include<algorithm>


using namespace std;

class expression
{
public:
    vector<string> boolean;
    vector<string> boolean1;
    int n,term,top2,top,top1,top3,minterm[100],var[100];
    int stk[100],stk1[100],stk2[100],stk3[100];
    char exp[10];
    int i;
     vector<string> arr;
    vector<string> gp[100];
    vector<string> no_prime_implicant;
    vector<string> temp_prime;
    vector<string> prime_implicant;
public:
expression()
{
    top=-1;
    top1=-1;
    top2=-1;
    top3=-1;
    i=0;
}
void noofterms()
{
    cout<<"example how to give input ---( A+AB')---All letters should be in capital letters and for complement use ' and first mention no.of different variables in your expression "<<endl;
    cout<<"enter the no. of variables:";
    cin>>n;
    term=1;
    for(int i=1;i<=n;i++)
    {
        term=term*2;

    }
    cout<<term;
    for(int i=0;i<term;i++)
    {
        decimal_to_binary(i);
    }
}
void decimal_to_binary(int m)
{
    int c, d, count;
    char *pointer;
    count = 0;
    pointer = (char*)malloc(32+1);
    if ( pointer == NULL )
    exit(EXIT_FAILURE);
    for ( c = n-1 ; c >= 0 ; c-- )
    {
        d = m >> c;
        if ( d & 1 )
        *(pointer+count) = 1 + '0';
        else
        *(pointer+count) = 0 + '0';
        count++;
    }
    *(pointer+count) = '\0';

    boolean.push_back(pointer);
    //cout<<boolean[m]<<endl;
}
void enterexp()
{
    cout<<"enter the expression:";
    cin>>exp;
}
void push(int n)
{
    top=top+1;
    stk[top]=n;
}
int pop()
{
    int ch=stk[top];
    top=top-1;
    return ch;
}
void push1(int n)
{
    top1=top1+1;
    stk1[top1]=n;
}
int pop1()
{
    int ch=stk1[top1];
    top1=top1-1;
    return ch;
}
void push2(int n)
{
    top2=top2+1;
    stk2[top2]=n;
}
int pop2()
{
    int ch=stk2[top2];
    top2=top2-1;
    return ch;
}
void push3(int n)
{
    top3=top3+1;
    stk3[top3]=n;
   // cout<<" stk3:"<<stk3[top3+1]<<" ";
}
int pop3()
{
    int ch=stk3[top3];
    top3=top3-1;
    return ch;
}
void calexp()
{
    for(int j=0;j<boolean.size();j++)
    {
        string str1=boolean[j];
        cout<<str1<<"    ";
        for(int i=0;i<str1.length();i++)
        {
            int l=str1[i];
            var[i]=l-48;
        }
    int i=0;
    while(exp[i]!='\0')
    {
        if(exp[i]=='(')
        {
            i=i+1;
            while(exp[i]!=')')
            {
                if(exp[i]!='+')
                {
                    if(exp[i]=='\'')
                    {
                        int k=pop2();
                        //cout<<k;
                        push2(~k);
                    }
                    else
                    {
                        int a=exp[i]-65;
                        push2(var[a]);
                    }
                }

                if(exp[i]=='+'||exp[i+1]==')')
                {
                    int c=pop2();
                    int res=1;
                    while(top2!=-1)
                    {
                        res=res&c;
                        c=pop2();
                    }
                    res=res&c;
                    push3(res);
                }
                i++;
            }
            int exp_or=0;
            int c=pop3();
            while(top3!=-1)
            {
                exp_or=exp_or|c;
                c=pop3();
            }
            exp_or=exp_or|c;
            push( exp_or);
        }
        if(exp[i]!='+'&&exp[i]!='('&&exp[i]!=')')
        {
            if(exp[i]=='\'')
            {
                    push(~pop());
            }
            else
            {
                int a=(exp[i]-65);
                push(var[a]);
            }
        }
        if(exp[i]=='+')
        {
            int c=pop();
            int res=1;
            while(top!=-1)
            {
                res=res&c;
                c=pop();
            }
            res=res&c;
            push1(res);
            //cout<<"result is :"<<res<<endl;
        }
        if(exp[i+1]=='\0')
        {
            int c=pop();
            int res=1;
            while(top!=-1)
            {
                res=res&c;
                c=pop();
            }
            res=res&c;
            push1(res);
        }
        i++;
    }
    int exp_or=0;
    while(top1!=-1)
    {
        int k=pop1();
        exp_or=exp_or|k;
    }
    minterm[j]=exp_or;
    cout<<"   final:"<<exp_or<<"   "<<j<<" "<<exp_or<<endl;
    }
    cout<<"bye"<<endl;
}
void extractminterm()
{
   // boolean.erase (boolean.begin(),boolean.end());
    int b=boolean.size();
    for(int i=0;i<term;i++)
    {
        if(minterm[i]!=0)
        {
            decimal_to_binary(i);
           // cout<<i<<endl;
        }

    }
     for(int i=b;i<boolean.size();i++)
    {

       // cout<<boolean[i]<<endl;
        boolean1.push_back(boolean[i]);
    }
    cout<<"MINTERMS:";
    for(int i=0;i<boolean1.size();i++)
         cout<<boolean1[i]<<endl;
}
/*void getminterm()
{
    cout<<"I'm here";
    boolean.clear();
    cout<<"I'm here";
    for(int i=0;i<term;i++)
    {
        if(minterm[i]!=0)
        {
            decimal_to_binary(i);
        }
    }
    for(int i=0;i<boolean.size();i++)
    {
        cout<<boolean[i]<<endl;
    }
}*/
void tabulating()
{

    for(int i=0;i<boolean1.size();i++)
    {
        int occ=0;
        for(int k=0;k<n;k++)
        {
            if(boolean1[i].at(k)=='1')
                occ++;
        }
        gp[occ].push_back(boolean1[i]);
    }
    //cout<<endl<<"LLLLLL"<<endl;
    float total=(n+1)*((n+1)+1)/2;
    int l=(int)total;
    int c=0,m=n;
    for(int j=n+1;j>=1;j--)
    {
        for(int k=1;k<j;k++)
        {
            m=m+1;
            gp[m]=generate_list(gp[c],gp[c+1]);
            c++;
        }
        c++;
    }
   // cout<<endl<<"check: "<<m<<endl;
    for(int i=0;i<=m;i++)
    {
         temp_prime.insert(temp_prime.end(), gp[i].begin(), gp[i].end());
    }
    for(int l=0; l<temp_prime.size();l++)
    {
        int f=0;
        for(int m=0;m<no_prime_implicant.size();m++)
        {
            if(temp_prime[l] == no_prime_implicant[m])
                f=1;
        }
        if(!f)
            prime_implicant.push_back(temp_prime[l]);
    }
    remove_duplicates(prime_implicant);
    cout<<"SOP:";
     for(int i=0;i<prime_implicant.size();i++)
     {
         string str=prime_implicant[i];
         for(int j=0;j<str.length();j++)
         {
             if(str[j]=='1')
             {
                 char ch=j+65;
                 cout<<ch;
             }
              if(str[j]=='0')
             {
                 char ch=j+65;
                 cout<<ch<<"\'";
             }
             if(str[j]=='-')
             {
                 continue;
             }

        }
        if(i!=prime_implicant.size()-1)
        cout<<"+";
     }
      cout<<endl<<"POS:";
     for(int i=0;i<prime_implicant.size();i++)
     {
         string str=prime_implicant[i];
         cout<<"(";
         for(int j=0;j<str.length();j++)
         {
             if(str[j]=='0')
             {
                 char ch=j+65;
                 cout<<ch;
                 if(str[j+1]=='0'||str[j+1]=='1')
                    cout<<"+";
             }
              if(str[j]=='1')
             {
                 char ch=j+65;
                 cout<<ch<<"\'";
                 if(str[j+1]=='0'||str[j+1]=='1')
                    cout<<"+";
             }
             if(str[j]=='-')
             {
                 continue;
             }

        }
        //if(i!=prime_implicant.size()-1)
        cout<<").";
     }
     //cout<<prime_implicant[i]<<" ";
     cout<<endl<<"IT'S OK";
}


vector<string> generate_list(vector<string> st1, vector<string> st2)
{
    if(st1.size()==0 || st2.size()==0)
    {
        vector<string> st;
        return (st);
    }
    vector<string> templist;
    for(int i=0;i<st1.size();i++)
    {
        for(int j=0;j<st2.size();j++)
        {
            if(num_differences(st1[i], st2[j])==1)
            {
                no_prime_implicant.push_back(st1[i]);
                no_prime_implicant.push_back(st2[j]);
                int k = 0;
                while(st1[i].at(k)==st2[j].at(k))
                    k++;
                string tmpstr = st1[i];
                tmpstr.at(k) = '-';
                templist.push_back(tmpstr);
            }
        }
    }
    return templist;
}

int num_differences(string str1, string str2)
{
    int differ=0;
    if(str1.length()==str2.length())
    {
        for(int k=0;k<str1.length();k++)
        {
            if(str1.at(k)!=str2.at(k))
                differ++;
        }
    }
    return differ;
}
void remove_duplicates(vector<string>& vec)
{
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
};
int main()
{
    char *pointer;
    expression e;
    e.noofterms();
    e.enterexp();
    e.calexp();
    e.extractminterm();
    e.tabulating();
    return 0;
}
