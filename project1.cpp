#include<vector>
#include<iostream>
using namespace std;

  int main()
{
  int row1,col1;
  int row2,col2;
  cout<<"Input the first Matrix's row:"<<endl;
  cin>>row1;
  cout<<"Input the first Matrix's column:"<<endl;
  cin>>col1;
  cout<<"Then input the second Matrix's row:"<<endl;
  cin>>row2;
  cout<<"Then input the secong Matrix's column:"<<endl;
  cin>>col2;
 
  if(col1!=row2||row1<0||row2<0||col1<0||col2<0){cout<<"Your Input is not right"<<endl;return 1;}
 
 else{
   cout<<"Now please input all the members of these two matrix one by one"<<endl;
  vector<vector<int> > M1(row1);
   int mm;
   for(int m=0;m<row1;m++)
   {  M1[m].resize(col1);
    for(int n=0;n<col1;n++)
   {cin>>mm; M1[m][n]=mm;}
   }
  
   
   vector<vector<int> > M2(row2);
   int mm2;
   for(int m=0;m<row2;m++)
   {  M2[m].resize(col2);
    for(int n=0;n<col2;n++)
      {cin>>mm2; M2[m][n]=mm2;}
   }



     vector<vector<int> >M3(row1);
    for(int m=0;m<row1;m++)
    {M3[m].resize(col2);
      for(int n=0;n<col2;n++)
   	 {
   	   M3[m][n]=0;
   	   for(int t=0;t<row2;t++)
         M3[m][n]+=M1[m][t]*M2[t][n];}
   }



   
   cout<<"The first Matrix is : "<<endl;
   for(int i=0;i<row1;i++){
     for(int j=0;j<col1;j++){
	  cout<<M1[i][j]<<" ";}
	cout<<endl;}

   cout<<"The second Matrix is :"<<endl;
   for(int i=0;i<row2;i++){
     for(int j=0;j<col2;j++){
	  cout<<M2[i][j]<<" ";}
	cout<<endl;}

       cout<<"The multilication Matrix is:"<<endl;
     for(int i=0;i<row1;i++){
     for(int j=0;j<col2;j++){
   	   cout<<M3[i][j]<<" ";}
       cout<<endl;}


  }



}
