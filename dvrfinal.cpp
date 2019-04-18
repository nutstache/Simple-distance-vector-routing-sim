#include<iostream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> disttable;
vector<vector<int>> loctable;
vector<char> name;
void findmin(int currnode,int findnode){
	int temp=INT_MAX,loc=-1,val;
	if(loctable[currnode][findnode]!=-1){
		temp=disttable[currnode][findnode];
		loc=loctable[currnode][findnode];
	}
	for(int i=0;i<disttable.size();i++){
		if(currnode==i)								//No need to check for same router
			continue;
		if(loctable[currnode][i]==-1 || loctable[i][findnode]==-1)//check if path exists
			continue;
		val=disttable[currnode][i]+disttable[i][findnode];
		if(temp>val){
			temp=val;
			loc=loctable[currnode][i];
		}
	}
	if(loctable[currnode][findnode]!=-1 && disttable[currnode][findnode]<temp){ //check for immediate neighbour
		loc=findnode;
		temp=disttable[currnode][findnode];
	}
	loctable[currnode][findnode]=loc;
	disttable[currnode][findnode]=temp;
}
int findrouter(char ch){
	for(int i=0;i<name.size();i++){
		if(ch==name[i])
			return i;
	}
	
}
void displayfn(){
	int n=disttable.size();
	for(int i=0;i<n;i++){
		cout<<"\nTable "<<name[i]<<" :\n";
		cout<<"Router\tHops\tNext Router\n";
		for(int j=0;j<n;j++)
			if(disttable[i][j]!=-1)
				cout<<name[j]<<"\t"<<disttable[i][j]<<"\t"<<name[loctable[i][j]]<<"\n";
			else
				cout<<name[j]<<"\t~\t-\n";
		for(int j=0;j<40;j++)
			cout<<"-";
		cout<<"\n";
	}
	for(int j=0;j<40;j++)
		cout<<"-";
	cout<<"\n";
}
void getdata(){
	int n,pn,a,b,c;
	cout<<"Enter number of routers: ";
	cin>>n;
	disttable.resize(n);
	loctable.resize(n);
	name.resize(n);
	cout<<"Router name(char): \n";
	for(int i=0;i<n;i++){
		cout<<"Enter name of router "<<i<<" : ";
		cin>>name[i];
	}
	for(int i=0;i<n;i++){
		disttable[i].resize(n);
		loctable[i].resize(n);
		for(int j=0;j<n;j++){
			disttable[i][j]=-1;
			loctable[i][j]=-1;
		}
		loctable[i][i]=i;
		disttable[i][i]=0;
	}
	cout<<"Enter number of paths ";
	cin>>pn;
	char ch1,ch2;
	for(int i=0;i<pn;i++){
		cout<<"Enter path (router1,router2,distance):";
		cin>>ch1>>ch2>>c;
		a=findrouter(ch1);
		b=findrouter(ch2);
		disttable[a][b]=c;
		disttable[b][a]=c;
		loctable[a][b]=b;
		loctable[b][a]=a;
	}
}
void routerUpdate(){
	int n=loctable.size();
	for(int k=0;k<n-1;k++){ 				//n-1 iterations for stable network
		cout<<"\nIteration "<<k+1<<"\n";
		for(int i=0;i<n;i++){				//Check Each router
			for(int j=0;j<n;j++){			//Updating a router to find min route to network
				if(i==j)					//No need to update its own location as it'll be 0 always
					continue;
				findmin(i,j);				//Set min path for i->j
			}
		}	
		displayfn();
	}
}
int main(){
	getdata();
	cout<<"\n\nInitial Tables :\n";
	displayfn();
	cout<<"\n";
	routerUpdate();
	
	return 0;
}
