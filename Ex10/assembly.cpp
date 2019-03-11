#include<iostream>
#include<string>
#include<regex>
#include<iterator> 
#include<string.h>
#include<map>
using namespace std;
int main()
{  
    regex Assign("[a-zA-Z]+=[0-9]+"); 
    regex Assign2("[a-zA-Z]+=[a-zA-Z]+\\+[0-9]+"); 
    regex Assign3("[a-zA-Z]+=[a-zA-Z]+\\+[a-zA-Z]+"); 
    regex Number("[0-9]+");
    regex Number2("\\=[0-9]+");
    regex Identifier("[a-zA-Z]+");
    regex IF("if [a-zA-Z]+\\>[a-zA-Z]+");
    regex IF2("if [a-zA-Z]+\\>[0-9]+");
    regex LineNo("L[0-9]+ ");
    regex GOTO("goto L[0-9]+");
    string arr[20]={"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
    map<string,string> m;
    int i=0;
    smatch m1,m2,m3,m4,m5,m6,m7,m8,m9; 
    string s;
    string output="";
    while(getline(cin,s))
    {

          if(regex_search(s, m1, LineNo)){
                string t = s.substr(m1.position(),m1.length());
                regex_search(t, m2, Number);
                string t2=s.substr(m2.position(),m2.length());
                output+="L"+t2+": ";
                string s1="L"+t2;
                //cout<<"S: "<<s<<endl;
                // string s2=s.substr(0+s1.length(),s.length()-1);
             
                // int i=0,j=0;
                // while(s2[i])
                // {
                //     if(s2[i]!=' ')
                //     {
                //         s2[j++]=s2[i];
                //     }
                //     i++;
                // }
                  // cout<<"S2: "<<s2<<endl;
                if(regex_search(s, m1, Assign)){
                //cout<<"S: "<<s<<endl;
                string t = s.substr(m1.position(),m1.length());
                //cout<<"T: "<<t<<endl;
                regex_search(t, m2, Number);
                string t2=t.substr(m2.position(),m2.length());
                //cout<<"T2: "<<t2<<endl;
                //string t4(t2.begin()+1,t2.end());
                //cout<<t4<<endl;
                regex_search(t, m3, Identifier);
                string t3=t.substr(m3.position(),m3.length());
                if(m.find(t3)==m.end())
                {
                    m[t3]=arr[i];
                    ++i;
                }
               // cout<<t2<<endl;
                output+="MOV "+m[t3]+",#"+t2+"\n";
            }
        }
         else if(regex_search(s, m1, Assign)){
            string t = s.substr(m1.position(),m1.length());
            //cout<<t<<endl;
            regex_search(t, m2, Number);
            string t2=s.substr(m2.position(),m2.length());
            //cout<<t2<<endl;
            //string t4(t2.begin()+1,t2.end());
            //cout<<t4<<endl;
            regex_search(t, m3, Identifier);
            string t3=s.substr(m3.position(),m3.length());
            if(m.find(t3)==m.end())
            {
                m[t3]=arr[i];
                ++i;
            }
           // cout<<t2<<endl;
            output+="MOV "+m[t3]+",#"+t2+"\n";
        }
        else  if(regex_search(s, m1, Assign2)){
            //a=b+3
            string t = s.substr(m1.position(),m1.length());
            regex_search(t, m2, Number);
            string t2=s.substr(m2.position(),m2.length()); //3
            regex Identifier1("[a-zA-Z]+=");
            regex Identifier2("=[a-zA-Z]+");
            regex_search(t, m3, Identifier1);
            string t3=s.substr(m3.position(),m3.length()); //a=
            regex_search(t, m4, Identifier2);
            string t4=s.substr(m4.position(),m4.length()); //=b
            regex_search(t3, m5, Identifier);
            string t5=s.substr(m5.position(),m5.length()); //a
            regex_search(t4, m6, Identifier);
            string t6=s.substr(m6.position(),m6.length()); //b
            if(m.find(t5)==m.end())
            {
                m[t5]=arr[i];
                ++i;
            }
            if(m.find(t6)==m.end())
            {
                m[t6]=arr[i];
                ++i;
            }
            output+="ADD "+m[t6]+",#"+t2+"\n";
            output+="MOV "+m[t5]+","+m[t6]+"\n";
        }
        else  if(regex_search(s, m1, Assign3)){
            //a=b+c
            string t = s.substr(m1.position(),m1.length());
            regex Identifier1("[a-zA-Z]+=");
            regex Identifier2("=[a-zA-Z]+");
            regex Identifier3("\\+[a-zA-Z]");
            regex_search(t, m3, Identifier1);
            string t1=s.substr(m3.position(),m3.length()); //a=
            regex_search(t, m4, Identifier2);
            string t2=s.substr(m4.position(),m4.length()); //=b
            regex_search(t, m5, Identifier3);
            string t3=s.substr(m5.position(),m5.length()); //+c
            regex_search(t1, m6, Identifier);
            string t4(t1.begin(),t1.end()-1);
            string t5(t2.begin()+1,t2.end());
            string t6(t3.begin()+1,t3.end());
            if(m.find(t4)==m.end())
            {
                m[t4]=arr[i];
                ++i;
            }
            if(m.find(t5)==m.end())
            {
                m[t5]=arr[i];
                ++i;
            }
            if(m.find(t6)==m.end())
            {
                m[t6]=arr[i];
                ++i;
            }
            //cout<<"T: "<<t1<<" "<<t2<<" "<<t3<<" "<<t4<<" "<<t5<<" "<<t6<<endl;
            output+="ADD "+m[t5]+","+m[t6]+"\n";
            output+="MOV "+m[t4]+","+m[t5]+"\n";
        }
          if(regex_search(s, m1, IF)){
            //cout<<"MATCH";
            regex ID1("[a-zA-Z]+\\>");
            regex ID2("\\>[a-zA-Z]+");
             //cout<<i<<" A ";
            string t = s.substr(m1.position(),m1.length());
            regex_search(t, m2, ID1);
            string t2=s.substr(m2.position(),m2.length());
            regex_search(t, m3,ID2);
            // cout<<i<<" B ";
            string t3=s.substr(m3.position(),m3.length());
             // cout<<t2<<" C ";
            string t4(t2.begin(),t2.end()-1);
              //cout<<i<<" D ";
            string t5(t3.begin()+1,t3.end());
             // cout<<i<<" E ";
            if(m.find(t4)==m.end())
            {
                m[t4]=arr[i];
                ++i;
                //cout<<i<<" ";
            }
            if(m.find(t5)==m.end())
            {
                m[t5]=arr[i];
                ++i;
                //cout<<i<<" ";
            }
            output+="CMP "+m[t4]+","+m[t5]+"\nJGT ";
            if(regex_search(s, m1, GOTO)){
                string t6 = s.substr(m1.position(),m1.length());
                regex_search(t6, m2, LineNo);
                string t7(t6.end()-2,t6.end());
                //cout<<t6<<" "<<t7;
                output+=t7+"\n";
            }
        }
       else if(regex_search(s, m1, GOTO)){
            string t1 = s.substr(m1.position(),m1.length());
            regex_search(t1, m2, LineNo);
            string t2(t1.end()-2,t1.end());
            output+="JMP "+t2+"\n";
        }

    }//while
    cout<<output;
    return 0; 
}