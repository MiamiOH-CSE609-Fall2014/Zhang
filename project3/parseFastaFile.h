//tuple have three elements
//string header
//string sequence
//vector<string> comments


#include<string>
#include<vector>
using namespace std;

class ReturnedData
{
 public:
  string head;
  string seq;
  vector<string> comm;
};

ReturnedData parseFastaFile(string);
