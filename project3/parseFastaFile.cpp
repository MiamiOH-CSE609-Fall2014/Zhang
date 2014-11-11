#include<string>
#include<iostream>
#include<vector>
#include<tuple>
#include<fstream>
#include<cstdlib>
#include"parseFastaFile.h"
using namespace std;

tuple<string,vector<string>,string> parseFastaFile(string filepath)
{
  string header;
  string sequence;
  vector<string> comments;
  fstream dnaData;
  dnaData.open(filepath,fstream::in);
  char buf[200];
  while(dnaData.getline(buf,200))
    {
      if(buf[0]=='>'){header=buf;}
      else if(buf[0]==';'){comments.push_back(buf);}
      else{sequence=sequence+buf;}
}
  tuple<string,vector<string>,string> DNA{header,comments,sequence};
  return DNA;
}
