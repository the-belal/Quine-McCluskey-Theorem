#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct st {
    ll value;
    string BiNum="";

};
struct Essential {
    string minterms="";
    set<int>implicant;

};
string DecimalToBinary(ll num, int sz)
{
    string st;
    while (num>0)
    {
        st+=num%2+'0';
        num/=2;
    }
    while (sz>st.size())
    {
        st.push_back('0');
    }
    reverse(st.begin(),st.end());
    return st;
}
int main()
{
    ll numOfVariables,numOfMinterms;
    cout<<"Enter Number Of Variables:\n";
    cin>>numOfVariables;
    cout<<"Enter Number of Minterms:"<<endl;
    cin>>numOfMinterms;
    cout<<"Enter minterms separated by space:\n";
    st minterms[numOfMinterms+5];
    for (int i=0; i<numOfMinterms; i++)
    {
        cin>>minterms[i].value;
        minterms[i].BiNum=DecimalToBinary(minterms[i].value,numOfVariables); // Decimal To Binary Conversion
    }
    ll numberOfDontcare,temp;
    vector<ll>dontcare;
    cout<<"Enter Number of Don't care minterms: "<<endl;
    cin>>numberOfDontcare;
    if (numberOfDontcare>0)
    cout<<"Enter Don't Care minterms:\n";
    for (int i=0;i<numberOfDontcare;i++)
    {
        cin>>temp;
        dontcare.push_back(temp);
    }
    //-------------step1--------------------------//
    vector<string>group[10005];
    //------GROUPING BASED ON NUM OF ONE------------
    for (int i=0; i<numOfMinterms; i++)
    {
        group[__builtin_popcount(minterms[i].value)].push_back(minterms[i].BiNum);
    }

    for (int i=0; i<dontcare.size(); i++)
    {
        group[__builtin_popcount(dontcare[i])].push_back(DecimalToBinary(dontcare[i],numOfVariables));
    }

    //------------------Matching untill it matches with groups--------------
    vector<Essential>Final_result1,Final_result2;
    Essential temp_essential;
    ///Assigning minterms with binary values
    for (int i=0; i<numOfMinterms; i++)
    {
        temp_essential.minterms=minterms[i].BiNum;
        temp_essential.implicant.insert(minterms[i].value);
        Final_result1.push_back(temp_essential);
        temp_essential.implicant.clear();
    }
    for (int i=0;i<dontcare.size();i++)
    {
        temp_essential.minterms=DecimalToBinary(dontcare[i],numOfVariables);
        temp_essential.implicant.insert(dontcare[i]);
        Final_result1.push_back(temp_essential);
        temp_essential.implicant.clear();
    }

    set<int>::iterator it;
    set<int>temp_set;
    int loop=0;

    while (loop<numOfVariables)
    {
        map<string,bool>check_duplicate;
        //cout<<loop<<":\n";
        if (loop%2==0)
        {

            Final_result2.clear();
            for (int i=0; i<Final_result1.size(); i++)
            {
                int cnt=0;
                for (int j=0; j<Final_result1.size(); j++)
                {
                    if (i!=j)
                    {
                        int Mismatch=0;
                        for (int k=0; k<Final_result1[j].minterms.size(); k++)
                        {
                            if (Final_result1[i].minterms[k]!=Final_result1[j].minterms[k])
                                Mismatch++;
                            if (Mismatch>1) break;
                        }

                        if (Mismatch==1)
                        {
                            cnt++;
                            temp_essential.minterms=Final_result1[i].minterms;
                            for (int k=0; k<Final_result1[j].minterms.size(); k++)
                            {
                                if (Final_result1[i].minterms[k]!=Final_result1[j].minterms[k])
                                    {
                                        temp_essential.minterms[k]='-';
                                        if (check_duplicate[temp_essential.minterms]) break;

                                        for (it=Final_result1[i].implicant.begin();it!=Final_result1[i].implicant.end();it++)
                                        {
                                            temp_essential.implicant.insert(*it);
                                        }
                                        for (it=Final_result1[j].implicant.begin();it!=Final_result1[j].implicant.end();it++)
                                        {
                                            temp_essential.implicant.insert(*it);
                                        }

                                        Final_result2.push_back(temp_essential);

                                        //Final_result2.push_back(temp);
                                        check_duplicate[temp_essential.minterms]=true;
                                        temp_essential.implicant.clear();
                                        break;
                                    }
                            }

                        }
                    }
                }
                if (cnt==0)
                {
                    if (check_duplicate[Final_result1[i].minterms]) continue;
                    Final_result2.push_back(Final_result1[i]);

                    check_duplicate[Final_result1[i].minterms]=true;
                }
            }
            for (int i=0;i<Final_result2.size();i++)
            {
                for (it=Final_result2[i].implicant.begin();it!=Final_result2[i].implicant.end();it++)
                {
                    cout<<(*it)<<' ';
                }
                cout<<endl;
            }
        }
        else
        {


            Final_result1.clear();
            for (int i=0; i<Final_result2.size(); i++)
            {
                int cnt=0;
                for (int j=0; j<Final_result2.size(); j++)
                {
                    if (i!=j)
                    {
                        int Mismatch=0;
                        for (int k=0; k<Final_result2[j].minterms.size(); k++)
                        {
                            if (Final_result2[i].minterms[k]!=Final_result2[j].minterms[k])
                                Mismatch++;
                            if (Mismatch>1) break;
                        }

                        if (Mismatch==1)
                        {
                            cnt++;
                            temp_essential.minterms=Final_result2[i].minterms;
                            for (int k=0; k<Final_result2[j].minterms.size(); k++)
                            {
                                if (Final_result2[i].minterms[k]!=Final_result2[j].minterms[k])
                                    {
                                        temp_essential.minterms[k]='-';
                                        if (check_duplicate[temp_essential.minterms]) break;

                                        for (it=Final_result2[i].implicant.begin();it!=Final_result2[i].implicant.end();it++)
                                        {
                                            temp_essential.implicant.insert(*it);
                                        }
                                        for (it=Final_result2[j].implicant.begin();it!=Final_result2[j].implicant.end();it++)
                                        {
                                            temp_essential.implicant.insert(*it);
                                        }

                                        Final_result1.push_back(temp_essential);

                                        //Final_result2.push_back(temp);
                                        check_duplicate[temp_essential.minterms]=true;
                                        temp_essential.implicant.clear();
                                        break;
                                    }
                            }

                        }
                    }
                }

                if (cnt==0)
                {
                    //cout<<i<<endl;
                    if (check_duplicate[Final_result2[i].minterms]) continue;
                    Final_result1.push_back(Final_result2[i]);

                    check_duplicate[Final_result2[i].minterms]=true;
                }
            }

            for (int i=0;i<Final_result1.size();i++)
            {
                for (it=Final_result1[i].implicant.begin();it!=Final_result1[i].implicant.end();it++)
                {
                    cout<<(*it)<<' ';
                }
                cout<<endl;
            }

        }
        loop++;
    }
    cout<<"Prime Implicants: "<<endl;

    map<int,int>chk_essential;
    vector<string>result;
    if (Final_result1.size()==0)
    {
        for (int i=0;i<Final_result2.size();i++)
        {
            cout<<Final_result2[i].minterms<<' ';
            for (it=Final_result2[i].implicant.begin();it!=Final_result2[i].implicant.end();it++)
                {
                    cout<<(*it)<<' ';
                    chk_essential[(*it)]++;
                }
            cout<<endl;
        }
        cout<<endl;
        cout<<"Simplified Sum of Product form of given Minterms:"<<endl;
        for (int i=0;i<Final_result2.size();i++)
        {
            if (i>0) cout<<"+";
            for (int j=0;j<numOfVariables;j++)
            {
                if (Final_result2[i].minterms[j]=='-') continue;

                cout<<(char)('A'+j);

                if (Final_result2[i].minterms[j]=='0') cout<<"'";
            }

        }
        cout<<endl;
        map<ll,bool>taken;
        for (int i=0;i<numOfMinterms;i++)
        {
            //cout<<minterms[i].value<<endl;
            if (chk_essential[minterms[i].value]==1)
            {
                //cout<<minterms[i].value<<endl;
                for (int j=0;j<Final_result2.size();j++)
                {
                    for (it=Final_result2[j].implicant.begin();it!=Final_result2[j].implicant.end();it++)
                    {
                        if ((*it)==minterms[i].value)
                        {
                            result.push_back(Final_result2[j].minterms);
                            taken[(*it)]=true;
                            for (it=Final_result2[j].implicant.begin();it!=Final_result2[j].implicant.end();it++)
                                taken[(*it)]=true;

                            break;
                        }
                    }
                }
            }
        }

        for (int i=0;i<numOfMinterms;i++)
        {
            if (taken[minterms[i].value]==false)
            {
                for (int j=0;j<Final_result2.size();j++)
                {
                    for (it=Final_result2[j].implicant.begin();it!=Final_result2[j].implicant.end();it++)
                    {
                        if ((*it)==minterms[i].value)
                        {
                            result.push_back(Final_result2[j].minterms);
                            taken[(*it)]=true;
                            for (it=Final_result2[j].implicant.begin();it!=Final_result2[j].implicant.end();it++)
                                taken[(*it)]=true;

                            break;
                        }
                    }
                }
            }
        }




    }
    else {



        for (int i=0;i<Final_result1.size();i++) {
            cout<<Final_result1[i].minterms<<' ';
            for (it=Final_result1[i].implicant.begin();it!=Final_result1[i].implicant.end();it++)
                {
                    cout<<(*it)<<' ';
                chk_essential[(*it)]++;
                }
            cout<<endl;
        }

    cout<<"Sum of Product form of given Minterms:"<<endl;
        for (int i=0;i<Final_result1.size();i++)
        {
            if (i>0) cout<<"+";
            for (int j=0;j<numOfVariables;j++)
            {
                if (Final_result1[i].minterms[j]=='-') continue;

                cout<<(char)('A'+j);

                if (Final_result1[i].minterms[j]=='0') cout<<"'";
            }

        }
        cout<<endl;

        map<ll,bool>taken;

        for (int i=0;i<numOfMinterms;i++)
        {

            if (chk_essential[minterms[i].value]==1)
            {
                //cout<<minterms[i].value<<endl;
                for (int j=0;j<Final_result1.size();j++)
                {

                    for (it=Final_result1[j].implicant.begin();it!=Final_result1[j].implicant.end();it++)
                    {
                        if ((*it)==minterms[i].value)
                        {
                            result.push_back(Final_result1[j].minterms);
                            taken[(*it)]=true;
                            for (it=Final_result1[j].implicant.begin();it!=Final_result1[j].implicant.end();it++)
                                taken[(*it)]=true;

                            break;
                        }
                    }
                }
            }
        }

        for (int i=0;i<numOfMinterms;i++)
        {
            if (taken[minterms[i].value]==false)
            {
                for (int j=0;j<Final_result1.size();j++)
                {
                    for (it=Final_result1[j].implicant.begin();it!=Final_result1[j].implicant.end();it++)
                    {
                        if ((*it)==minterms[i].value)
                        {
                            result.push_back(Final_result1[j].minterms);
                            taken[(*it)]=true;
                            for (it=Final_result1[j].implicant.begin();it!=Final_result1[j].implicant.end();it++)
                                taken[(*it)]=true;

                            break;
                        }
                    }
                }
            }
        }



    }
    cout<<"Essential Implicants:"<<endl;
    map<string,bool>chk_final;
    for (int i=0;i<result.size();i++)
    {
        //cout<<result[i]<<endl;

            if (chk_final[result[i]]==false) {
                 chk_final[result[i]]=true;
            if (i>0) cout<<"+";
            for (int j=0;j<numOfVariables;j++)
            {
                if (result[i][j]=='-') continue;

                cout<<(char)('A'+j);

                if (result[i][j]=='0') cout<<"'";
            }

            }




    }
    cout<<endl;


    return 0;

}
