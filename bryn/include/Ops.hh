#ifndef bryn_include_Ops_hh
#define bryn_include_Ops_hh

#include "EventData.hh"
#include "Math/VectorUtil.h"
#include "Operation.hh"
#include <map>
// #include "DeadECALDR.hh"


namespace Operation {


class confHT : public Operation::_Base
{
public:
  confHT (float JetEtThreshold,float cutVal);
  ~confHT (){;}
  bool Process( Event::Data&);
  std::ostream& Description( std::ostream& );
private:
  float JetEt_;

  float cut_;
};



class alphaTriggerEmu : public Operation::_Base
{
public:
  alphaTriggerEmu (float aT_Thresh,float JetEtThreshold, float HTThreshold,int maxNjets);
 ~alphaTriggerEmu (){;}
  bool Process( Event::Data&);
  std::ostream& Description( std::ostream& );
private:
  /* data */
  float aTCut_;
  float HtCut_;
  float JetEt_;
  int maxNjets_;
};


class checkTrigExists : public Operation::_Base
{
public:
  checkTrigExists (const Utils::ParameterSet&);
  ~checkTrigExists(){;}
  bool Process( Event::Data&);
  std::ostream& Description( std::ostream& );
private:
  std::vector<std::string> trigList;
};



class findLumisWithTwoPrescales : public Operation::_Base
{
public:
  findLumisWithTwoPrescales ();
  void Start( Event::Data& );
  bool Process( Event::Data& );
  void End( Event::Data& );
  ~findLumisWithTwoPrescales(){;}
  std::ostream& Description( std::ostream& );


private:
  /* data */
  std::map<std::pair<int,int >,std::vector<int> > mm_;
};

  class runLumiCutter_t : public Operation::_Base
  {
  public:
    runLumiCutter_t ( const Utils::ParameterSet& ps );
    ~runLumiCutter_t (){;}
    bool Process( Event::Data & ev );
    std::ostream& Description(std::ostream& ostrm);


  private:
    /* data */
    std::vector<int> _run;
    std::vector<int> _lumi;
  };


}

#endif // bryn_include_Ops_hh





