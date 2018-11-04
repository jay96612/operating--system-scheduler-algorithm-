// header files
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
// main function
int main()
{  // variabels
    string name,temp;
    int quantum,n;
    // opening file
    ifstream fp1("inputFile.txt",ios::binary);
    if(!fp1)  // checking for error
    {
        cout<<"Error in opening file ";
        exit(1);
    }
    // reading file
    fp1>>temp;
    if(temp.compare("Name:")==0)
    fp1>>name;
    
    fp1>>temp;
    if(temp.compare("Q:")==0)
    fp1>>quantum;

     fp1>>temp;
    if(temp.compare("NumofProc:")==0)
    fp1>>n;
    
    cout<<"name: "<<name<<"\nQ: "<<quantum<<"\nnumofProc: "<<n<<endl;
    
    int matrix[n][3],index=-1;
    int AT,CPUT;
    string PN;
    string temp2,temp3;
    fp1>>temp>>temp2>>temp3;
 
    if(temp.compare("ProcessName:")==0 && temp2.compare("ArrivalTime:")==0 && temp3.compare("CPUTime:")==0)
    {
    cout<<endl<<temp<<" "<<temp2<<" "<<temp3<<" \n";
// reading value of AT and CPUTime
    while(fp1>>PN>>AT>>CPUT)
    {
        int P=0;
        for(int i=1;i<PN.length();i++)
        P=P*10+PN[i]-48;  // extracting integer

        matrix[++index][0]=P;
        matrix[index][1]=AT;
        matrix[index][2]=CPUT;

    }
    }
    fp1.close(); // clsing file
     for(int i=0;i<n;i++)
    { for(int j=0;j<3;j++)
         cout<<matrix[i][j]<<"             ";
        cout<<endl;
    }
    int CT[n+1],WT[n+1],TAT[n+1],TP;
    float sumWT=0,sumTAT=0,x=0;
    // FOR FCFS calculation
    if(name.compare("FCFS")==0)
    {   //cout<<"\nFCFS\n";
        for(int i=0;i<n;i++)
        {  int ProcessN,at,cpuT;
            ProcessN=matrix[i][0];
            at=matrix[i][1];
            cpuT=matrix[i][2];
        // CT TAT calculation
        //CT=AT+CPUT
        //TAT=CT-AT
        //WT=TAT-CPUT 
            x+=cpuT;
            CT[ProcessN]=x;
            TAT[ProcessN]=CT[ProcessN]-at;
            WT[ProcessN]=TAT[ProcessN]-cpuT;
        // sum 
            sumTAT+=TAT[ProcessN];
            sumWT+=WT[ProcessN];
                cout<<"\nprocessNo.:  "<<ProcessN<<", CT: "<<CT[ProcessN]<<endl;
        }
    }
    // FOR RR calculation
    else if(name.compare("RR")==0)
    {   
       
        while(1)
    {   bool isEnd=0;
          for(int i=0;i<n;i++)
        {  int ProcessN,at,cpuT;
            if(matrix[i][2]>0)
            {   isEnd=1;
                ProcessN=matrix[i][0];
                at=matrix[i][1];
                if(matrix[i][2]>=quantum)
                cpuT=quantum;
                else
                cpuT=matrix[i][2];
                matrix[i][2]-=quantum;
            
        // CT TAT calculation
        //CT=AT+CPUT
        //TAT=CT-AT
        //WT=TAT-CPUT 
            x+=cpuT;
            CT[ProcessN]=x;
            TAT[ProcessN]=CT[ProcessN]-at;
            WT[ProcessN]=TAT[ProcessN]-cpuT;
        cout<<"\nprocessNo.:  "<<ProcessN<<", CT: "<<CT[ProcessN]<<endl;
        }   
    }
    if(isEnd==0)
    break;
    }
        for(int i=1;i<=n;i++)
        {
             // sum 
            sumTAT+=TAT[i];
            sumWT+=WT[i];
        }
    }
   float avgWT,avgTAT;
   cout<<"\nTotal WT = "<<sumWT;
    cout<<"\nTotal TAT = "<<sumTAT;
    // avg caclulation
    avgWT=sumWT/n;
    avgTAT=sumTAT/n;
    cout<<"\n\nAVG. WT = "<<avgWT;
    cout<<"\nAVG. TAT = "<<avgTAT;
    cout<<"\nThroughPut = "<<n<<endl;

    return 0;
} 