#define forni(n) for(int i=0;i<n;i++)
#define forkj(k) for(int j=0;j<k;j++)
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node{
   int es=0,ef=0,lf=INT_MAX,ls,slack,period,afters=0,befores=0;
   string name;
   vector<node*> after;
   vector<node*> before;
   bool firstnode =false;
};

void pre(node* current,int befores,int k,vector<node*> *allnodes);
void inputhandler(node* a,vector<node*> *allnodes);
void createoutputfile(vector<node*> *allnodes,vector<vector<node*>> *allpaths,node* x,vector<vector<node*>> *criticalpat,ostream &np,string databasename,string projectname,string unitofdur);
void inputvalidation(node* c,string s);
void criticalpath(vector<node*> *allnodes,node* a,vector<vector<node*>> *allpaths,vector<vector<node*>> *criticalpat);
void checkef(vector<node*> *allnodes);
void checklf(node* a);
void traversefromfirstnode(node *a);
void paths(node* start,vector<node*> *path ,node* a,int k,vector<vector<node*>> *allpaths);
void printpaths(vector<vector<node*>> *allpaths,ostream& np);
string f= " Input name of last activity (No Spaces allowed):  ";
string l= "\n Input duration of activity ";
string c="\n Does activity ",d=" has any predecessors ? If yes,how many ? If no,type 0 : ";
string e="Input a valid number of predecessors. If yes,how many ? If no,type 0 : ";


int main(){
   char b;
   cout<<"\n\nDisclaimer:\n1)All Project will be created in a table under the current database.\n2)If want to create project into old database,just type the database name(must be same)\n3)Press Enter once done for each prompt\n4)Use underscore instead of spacing\n5)Make sure no similar named sql file in directory before creating a new one\n6)Can't input duration as decimal point,lowest is 1\n\n";
   string databasename;
   b='d';
   while(b=='d'){
    cout<<"\nName of database to save the project? : ";
    cin>>databasename;
    b='c';
    while(b=='c'){
        string projectname;
        cout<<"\nProject Name : ";
        cin>>projectname;
        string unitofdur;
        cout<<"\nUnit for duration e.g. Months/Days/Hours/Minutes for Project "<<projectname<<": ";
        cin>>unitofdur;
        while(!cin.good()){
            cin>>unitofdur;
            cout<<"\nPlease input a valid unit of duration : ";
        }
        vector<node*> *allnodes = new vector<node*>();
        node* a=new node();
        inputhandler(a,allnodes);
        vector<vector<node*>> *allpaths = new vector<vector<node*>>();
        vector<vector<node*>> *criticalpat = new vector<vector<node*>>();
        criticalpath(allnodes,a,allpaths,criticalpat);
        char output;
        if(a->befores == 0){
            cout<<"\nProject must have more than one activity.\n";
        }else{
                cout<<"\nDo you want to export the output to a file for(database storage purpose) or only print it out to terminal? If you want to export,type E. To print out to terminal, type anything else : ";
                cin>>output;
                output=tolower(output);
                if(output=='e'){
                    ofstream newproject;
                    newproject.open(projectname+".sql");
                    createoutputfile(allnodes,allpaths,a,criticalpat,newproject,databasename,projectname,unitofdur);
                    newproject.close();}
                else{
                    createoutputfile(allnodes,allpaths,a,criticalpat,cout,databasename,projectname,unitofdur);
                    cout<<"\n Do you want to save the project in the server?\n";
                    cin>>output;
                    output=tolower(output);
                    if(output=='e'){
                        ofstream newproject;
                        newproject.open(projectname+".sql");
                        createoutputfile(allnodes,allpaths,a,criticalpat,newproject,databasename,projectname,unitofdur);
                        newproject.close();}
        }}
        cout<<"\nType C to create another new project OR D to create a new database OR anything else to quit: ";
        cin.ignore();
        cin>>b;
        b=tolower(b);
        }}
   cout<<"\n"<<"You have quit the program. Thank you and See you again.";
   return 0;
}

void inputhandler(node* a,vector<node*> *allnodes){                                                                                      //initializes first input prompt
    cout<<f;
    cin>>a->name;
    cout<<l<<a->name<<" :  ";
    inputvalidation(a,l);
    allnodes->push_back(a);
    cout<<c<<a->name<<d;
    inputvalidation(a,e);
    int k=1;
    pre(a,a->befores,k,allnodes);
    }

void pre(node* current,int befores,int k,vector<node*> *allnodes){                                                                       //prompts if an activity has predecessor
    if(befores==0){
        current->es=0,current->ef=current->period,current->firstnode=true;
   }
    while(befores--){
        node* b=new node();
        cout<<" \n Input activity "<<current->name<<"'s \n \t Predecessor -"<<k<<"'s name : ";
        cin>>b->name;
        bool j=false;
        node* check;
        for(auto i : *allnodes){if(i->name==b->name){check=i;j=true;break;}}
        if(j){
            char p='n';
            while(j){
                char a;
                if(p=='n'){
                    cout<<"This name is already taken by another activity.\n\nType N to create a new one or type P to accept that it is the same activity :  ";
                    cin.ignore();
                    cin>>a;}
                else{
                    a='n';
                    p='n';
                    }
                a=tolower(a);
                    if(a=='n'){
                        cout<<" \n Input activity "<<current->name<<"'s \n \t Predecessor -"<<k<<"'s (New) name : ";
                        cin.ignore();
                        cin>>b->name;
                        j=false;
                        for(auto i : *allnodes){if(i->name==b->name){check=i;j=true;p='n';break;}}
                        if(!j){
                            cout<<" \t Duration : ";
                            inputvalidation(b,l);
                            cin.clear();
                                cin.ignore(INT_MAX,'\n');
                            cout<<"\n \t Does activity "<<b->name<<" has any predecessors ? If yes,how many ? If no,type 0 : ";
                            inputvalidation(b,e);
                            b->afters++;
                            b->after.push_back(current);
                            allnodes->push_back(b);
                            int y=1;
                            pre(b,b->befores,y,allnodes);
                            current->before.push_back(b);}
                }
               if(a=='p'){
                   j=false;
                   for(auto i : current->before) if(i->name==check->name){j=true;break;}
                   if(j){cout<<"\nThe activity is already a predecessor in the current activity.\n"; p='p';}
                   else{
                       cout<<"Added the activity as a predecessor for "<<current->name;
                       check->afters++;
                       check->after.push_back(current);
                       current->before.push_back(b);
                       }
               }
           }}
       else{
               cout<<" \t Duration : ";
               inputvalidation(b,l);
               cout<<"\n \t Does activity "<<b->name<<" has any predecessors ? If yes,how many ? If no,type 0 : ";
               inputvalidation(b,e);
               b->afters++;
               b->after.push_back(current);
               allnodes->push_back(b);
               int y=1;
               pre(b,b->befores,y,allnodes);
               current->before.push_back(b);
       }
       k++;
       }
   }

void createoutputfile(vector<node*> *allnodes,vector<vector<node*>> *allpaths,node* x,vector<vector<node*>> *criticalpat,ostream &newproject,string databasename,string projectname,string unitofdur){    //can choose to print to terminal or sql file
    if(&newproject==&cout){
        newproject<<"\n\n";
        newproject<<"Activity\tDuration("<<unitofdur<<")\tES("<<unitofdur<<")\tEF("<<unitofdur<<")\tLS("<<unitofdur<<")\tLF\t("<<unitofdur<<")Slack("<<unitofdur<<")\tFirstnode\tPredecessor\tAfters\n";
        for(auto k: *allnodes){
            newproject<<k->name<<"\t\t"<<k->period<<"\t\t"<<k->es<<"\t"<<k->ef<<"\t"<<k->ls<<"\t"<<k->lf<<"\t"<<k->slack<<"\t"<<k->firstnode<<"\t\t";
            for(auto s: k->before){
                newproject<<s->name<<" ";
            }
            newproject<<"\t\t";
            for(auto s: k->after){
                newproject<<s->name<<" ";
            }
            newproject<<"\n";
        }
        newproject<<"\n\n";
        newproject<<"All possible paths : "<<"\n";
        printpaths(allpaths,newproject);
        newproject<<"\n"<<"All critical paths : "<<"\n";
        printpaths(criticalpat,newproject);
        newproject<<"\n"<<"Earliest completion time in "<<unitofdur<<" : "<<x->lf<<"\n";}
    else{
        newproject<<"CREATE DATABASE IF NOT EXISTS "+databasename+";\n";
        newproject<<"USE "+databasename+";\n";
        newproject<<"CREATE TABLE IF NOT EXISTS "+projectname+"\n";
        newproject<<"(\n\tActivity VARCHAR(100),\n\tDuration INT,\n\tEarliest_Start INT,\n\tEarliest_Finish INT,\n\tLatest_Start INT,\n\tLatest_Finish INT,\n\tSlack INT,\n\tFirstnode INT,\n\tPredecessors VARCHAR(100),\n\tActivities_after_current_activity VARCHAR(100),\n\tUnit_of_time VARCHAR(30)\n);\n";
        for(auto k: *allnodes){
            newproject<<"INSERT INTO ";
            newproject<<projectname<<" VALUES(\'"<<k->name<<"\',"<<k->period<<","<<k->es<<","<<k->ef<<","<<k->ls<<","<<k->lf<<","<<k->slack<<","<<k->firstnode<<",";
            if(k->before.size()){
                string bef="\'";
                for(auto s: k->before){
                    bef+=s->name;
                    if(s->name!=(k->before).at((k->before).size()-1)->name){
                        bef+=",";
                    }
                }
                bef+="\'";
                newproject<<bef;
                newproject<<",";
            }
            else{
                newproject<<"NULL,";
            }
            if(k->after.size()){
                string aft="\'";
                for(auto s: k->after){
                    aft+=s->name;
                    if(s->name!=(k->after).at((k->after).size()-1)->name){
                        aft+=",";
                    }
                }
                aft+="\'";
                newproject<<aft;
            }
            else{
                newproject<<"NULL";
            }
        newproject<<",\'"<<unitofdur<<"\');\n";
        }
    }
}

void inputvalidation(node *c,string s){                                                                                                  // to ensure only a valid int value is inputted
    if(s==l){
        cin>>c->period;
        while(!cin.good() || c->period<1)
    {
        cout<<"\t\n Invalid Input Try Again!!! Input Must be more than 0 and without chars. \n\n";
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<s<<" "<<c->name<<" : ";
        inputvalidation(c,s);
    }
    }
    if(s==e){
        cin>>c->befores;
        while(!cin.good() || c->befores<0)
    {
        cout<<"\t\n Invalid Input Try Again!!! Input Must be more than 0 and without chars. \n\n";
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cout<<"For activity "<<c->name<<" "<<s;
        inputvalidation(c,s);
    }
    }
}

void criticalpath(vector<node*> *allnodes,node* a,vector<vector<node*>> *allpaths,vector<vector<node*>> *criticalpat){                   //to call other funcs to calculate all the values in nodes
   checkef(allnodes);
   checklf(a);
   for(auto l:*allnodes){
       if(l->firstnode){
           for(auto z:l->after){
               l->lf=min(l->lf,z->ls);
               l->ls=l->lf-l->period;
           }
       }
   }
   for(auto l:*allnodes){
       l->slack=l->lf-l->ef;
   }
   for(auto l:*allnodes){
       if(l->firstnode){
           vector<node*> *path = new vector<node*>();
           path->push_back(l);
           int k=0;
           paths(l,path,a,k,allpaths);
       }}
   for(auto pat:*allpaths){
       bool critical = true;
       for(auto act:pat){
           if(act->slack){
               critical=false;
           }
       }
       if(critical) criticalpat->push_back(pat);
   }
}

void checkef(vector<node*> *allnodes){                                                                                                   //to position es n ef calculation at firstnode
   for(auto l:*allnodes){
       if(l->firstnode){
           traversefromfirstnode(l);
       }
   }
}

void traversefromfirstnode(node *a){                                                                                                     //to calculate es n ef
   forni(a->afters){
       node* aft = a->after.at(i);
       aft->es=max(aft->es,a->ef);
       aft->ef=aft->es+aft->period;
       traversefromfirstnode(aft);
       if(aft->afters==0){
           aft->ls=aft->es,aft->lf=aft->ls+aft->period;
       }
       }
}

void checklf(node* a){                                                                                                                   //to calculate ls n lf
   forni(a->befores){
       node *bef=a->before.at(i);
       bef->lf=min(bef->lf,a->ls);
       bef->ls=bef->lf-bef->period;
       checklf(bef);
   }
}

void paths(node* start,vector<node*> *path ,node* a,int k,vector<vector<node*>> *allpaths){                                              //finds all possible path
   k++;
   if(start->afters){
       forni(start->afters){
           if(i==0){
               bool check=true;
               for(auto z:*path){
                   if(z==a){
                       check=false;break;}
                   }
               if(check){                                                                                  //ensures last node name is not entered more than once if already exist in path
                   path->push_back(start->after.at(i));}}
               else{path->at(k)=start->after.at(i);}
               paths(start->after.at(i),path,a,k,allpaths);
       }
   }
   else{
       allpaths->push_back(*path);
   }
}

void printpaths(vector<vector<node*>> *allpaths,ostream& np){                                                                                        //prints paths
       for(auto pathy: *allpaths){
           for(auto pa: pathy){
               np<<pa->name;
               if(pa!=pathy.at(pathy.size()-1)){
                   np<<"->";
               }
           }
           np<<"\n";
   }
}
