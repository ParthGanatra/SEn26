#include <vector>

#define MAXLEVEL 10
#define MAXLEN 100000
#define pb push_back
#define mp make_pair
#define delta 1.2

#define WAVETYPES 22
#define impulse 0
#define leading_diagonals 1
#define diagonals 2
#define zigzag 3
#define flat 4
#define double_zigzag 5
#define tripple_zigzag 6
#define double_threes 7
#define tripple_threes 8
#define c_traingle 9
#define e_triangle 10
#define MAXSIZE 500


using namespace std;


struct Monowave
{
	int startindex;
	int endindex;
	
	Monowave(int si,int ei):startindex(si),endindex(ei)
	{
	
	}
};

class Wavecount{
	  public:
	  vector<double> prices;
	  vector < vector <int> > wavecount;
	  
	  private:
	  vector< vector <int> >  dp[MAXLEVEL][22][5];
	  vector< vector <int> >  subwave_used[MAXLEVEL][22][5];
	  vector<Monowave> monowave;
	  
	  public:
	  void add_point(double price);	
  	  private:
  	  void remove_first_point();
  	  bool add_point_in_monowave(double price);
  	  void check_dp();
  	  void find_waves(int level,int i,int j);
  	  void assign_wavecount(int i,int j, int level,int wave_number);
};




