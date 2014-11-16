#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<map>

using namespace std;

class ReturnedData
{
public:
  string head,seq;
  vector<string> comm;
};

ReturnedData parseFastaFile(string path);
vector< vector<int> > digramFreqMatrix(map<string,int> freq);
vector< vector<int> > parseScoringFile(string path);
pair<int,int> scoreSequence(string,string,vector< vector<int> > sm);
map<string,int> digramFreqScores(string seq);


tuple<int,int,string> findHighScore(string seq, vector<string> needles,vector< vector<int> > sm);

//
//
//
//PARSEFASTAFILE
ReturnedData parseFastaFile(string path)
{
  fstream dataFile;
  dataFile.open(path,fstream::in);
  ReturnedData R;
  char buf[200];
  while(dataFile.getline(buf,200))
    {
      if(buf[0]=='>'){R.head=buf;}
      else if(buf[0]==';'){R.comm.push_back(buf);}
      else R.seq=R.seq+buf;
}
 
  return R;
}
//
//
//
//DIGRAMFREQMATRIX
vector< vector<int> > digramFreqMatrix(map<string,int> freq)
{
  vector< vector<int> > freqm;
  vector<int> tv;
  //vector<int> vector_G;
  //vector<int> vector_C;
  //vector<int> vector_T;
  
  tv.push_back(freq["AA"]);
  tv.push_back(freq["AG"]);
  tv.push_back(freq["AC"]);
  tv.push_back(freq["AT"]);
  freqm.push_back(tv);
  tv.clear();
  //I use the clear func so do not need to vectorG/C/T
  
  tv.push_back(freq["GA"]);
  tv.push_back(freq["GG"]);
  tv.push_back(freq["GC"]);
  tv.push_back(freq["GT"]);
  freqm.push_back(tv);
  tv.clear();

  tv.push_back(freq["CA"]);
  tv.push_back(freq["CG"]);
  tv.push_back(freq["CC"]);
  tv.push_back(freq["CT"]);
  freqm.push_back(tv);
  tv.clear();

  tv.push_back(freq["TA"]);
  tv.push_back(freq["TG"]);
  tv.push_back(freq["TC"]);
  tv.push_back(freq["TT"]);
  freqm.push_back(tv);
  tv.clear();

  return freqm;

}
//
//
//
//DIGRAMFREQSCORES
 map<string,int> digramFreqScores(string seq){
 map<string,int> freq;
 string ts;
 int ti;
for(int i=0;i<seq.size()-1;i++)
  { ts ="";
    ts =ts+seq[i]+seq[i+1];
    ti =freq[ts];
    freq[ts]=ti+1;
  }
return freq;
}

//
//
//
//SOCRESQUENCE

pair<int,int> scoreSequence(string haystack,string needle,vector< vector<int> > sm){
  map<string,int> smap;
  int maxscore=0;
  int maxpos=0;
  smap["AA"]=sm.at(0).at(0);
  smap["AG"]=sm.at(0).at(1);
  smap["AC"]=sm.at(0).at(2);
  smap["AT"]=sm.at(0).at(3);

  smap["GA"]=sm.at(1).at(0);
  smap["GG"]=sm.at(1).at(1);
  smap["GC"]=sm.at(1).at(2);
  smap["GT"]=sm.at(1).at(3);

  smap["CA"]=sm.at(2).at(0);
  smap["CG"]=sm.at(2).at(1);
  smap["CC"]=sm.at(2).at(2);
  smap["CT"]=sm.at(2).at(3);

  smap["TA"]=sm.at(3).at(0);
  smap["TG"]=sm.at(3).at(1);
  smap["TC"]=sm.at(3).at(2);
  smap["TT"]=sm.at(3).at(3);

  for(int i=0;i<haystack.size()-needle.size();i++)
    {
      int sum=0;
      string ts="";
      for(int ii=0;ii<needle.size();ii++)
	{
	  ts=ts+haystack[i+ii]+needle[ii];
	  sum=sum+smap[ts];
	  ts ="";
}
      if(sum>=maxscore)
	{maxscore=sum;maxpos=i;}
}
  pair<int,int> posscore;
  posscore.first=maxpos;
  posscore.second=maxscore;
  cout<<"needle: "<<needle<<" maxposition: "<<maxpos<<" maxscore: "<<maxscore<<endl;
  return posscore;
}

//
//
//
//PARSEASCORINGFILE
vector< vector<int> > parseScoringFile(string path)
{
  fstream dataFile;
  dataFile.open(path,fstream::in);
  vector< vector<int> > R;
  vector<int> tv;
  char buf[200];
  while(dataFile.getline(buf,200,','))
    {
      tv.push_back(stoi(buf));
      dataFile.getline(buf,200,',');
      tv.push_back(stoi(buf));
      dataFile.getline(buf,200,',');
      tv.push_back(stoi(buf));
      dataFile.getline(buf,200);
      tv.push_back(stoi(buf));
      R.push_back(tv);
      tv.clear();
}
  return R;

}


int main( int argc, char ** argv  )
{
  string path=argv[1];
  ifstream filename;
  filename.open(path,fstream::in);
  
  ReturnedData R =parseFastaFile(path);
  map<string,int> freq =digramFreqScores(R.seq);
  vector< vector<int> > freqm = digramFreqMatrix(freq);
  for(vector<int> tv:freqm){
    for(int ti: tv)    
      {cout<<ti<<"  ";}
  cout<<endl;
 }

 cout<<" please give me the scoring PATH: ";
 cin>>path;

vector< vector<int> > sm=parseScoringFile(path);
for(vector<int> tv: sm)
  {
    for(int ti: tv)
      {cout<<ti<<"  ";}

    cout<<endl;
}
 int number;
 string nee;
cout<<"the amount of NEEDLES : ";
cin>>number;
vector<string> needles;
for(int i=0;i<number;i++){
  cout<<"The sequences of NEEDLES : "<<i+1<<" : ";
  cin>>nee;
  needles.push_back(nee);
}
tuple<int,int,string> highps = findHighScore(R.seq,needles,sm);
 cout<<"MaxNeedle: "<<get<2>(highps)<<endl;
 cout<<"MaxPosition: "<<get<0>(highps)<<endl;
 cout<<"MaxScore: "<<get<1>(highps)<<endl;
}

tuple<int,int,string> findHighScore(string seq,vector<string> needles,vector< vector<int> > sm)
{
  pair<int,int> tposscore;
  tuple<int,int,string> highps;
  for(int i=0;i<needles.size();i++)
    {
      tposscore = scoreSequence(seq,needles.at(i),sm);
      if(tposscore.second>get<1>(highps))
	{
	  get<0>(highps)=tposscore.first;
          get<1>(highps)=tposscore.second;
          get<2>(highps)=needles.at(i);      
        }
    }
  return highps;
}
