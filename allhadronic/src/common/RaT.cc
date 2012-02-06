#include "RaT.hh"
#include "AlphaT.hh"
#include "CommonOps.hh"
#include "EventData.hh"
#include "HadronicOps.hh"
#include "HadronicPlottingOps.hh"
#include "Jet.hh"
#include "JetData.hh"
#include "KinSuite.hh"
#include "Math/VectorUtil.h"
#include "BkgdEstPlottingOps.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "Utility.hh"
#include "Vars.hh"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Math/GenVector/Boost.h>

/*
  - pthat
  - mht cleaning
  - aT/HT scatter, different binning?
  - truth!!
*/

using namespace Operation;
using namespace allhadronic;

typedef ROOT::Math::Boost Boost;

// -----------------------------------------------------------------------------
//
RaT::RaT( const Utils::ParameterSet& ps ) :
  // Misc
  dirName_("QcdBkgdEst"),
  nMin_(2),
  nMax_(10),
  verbose_(false),
  filter_(-1),
  noQcd_(false),
  noCleaningInDenom_(false),
  norm_(2.),
  scale_(true),
  scaleSignal_(false),
  scaleSingle_(true),
  maxLeadingJetEta_(0.),
  babyCut_(0.),
  addMuon_(false),
  onlyGenPtHat_(false),
  onlyFull_(false),
  useMeff_(false),
  // Dead ECAL
  deadEcalRegionDrCut_(0.),
  deadEcalRegionEtaCut_(0.),
  minJetPtCut_(0.),
  nBadCells_(0),
  useFile_(false),
  deadECALfile_(""),
  minBiasDeltaPhiCut_(0.),
  dead_(0),
  //RecHit cleaning
  rechit_(0),
  // Analysis defaults
  alphaT_(),
  aT_(0),
  ht_(0),
  pt1_(0.),
  pt2_(0.),
  pt3_(0.),
  // Binning
  inclusive_(true),
  htNbins_(0),
  htXlow_(0.),
  htXhigh_(0.),
  htBins_(),
  htPt1Bins_(),
  htPt2Bins_(),
  htPt3Bins_(),
  offset_(0.),
  // Histograms
  genHistos_(false),
  hVarVsScale_(),
  hVarOverScaleVsJetPt_(),
  hGenPtHat_(),
  hGenPdgId_(),
  hGenStatus_(),
  hGenNuPt_(),
  hGenNuPtMax_(),
  hGenNuMet_(),
  hGenMet_(),
  hGenJetMht_(),
  hGenMetVsGenNuPtMax_(),
  hGenMetVsGenNuMet_(),
  hGenJetMhtVsGenNuMet_(),
  hSMS_(),
  cutFlowHistos_(false),
  hCutFlow_(),
  htHistos_(false),
  hHtDistr_(),
  meffHistos_(false),
  hMeffDistr_(),
  mhtHistos_(false),
  hMhtDistr_(),
  mhtOverHtHistos_(false),
  hMhtOverHtDistr_(),
  mhtOverMeffHistos_(false),
  hMhtOverMeffDistr_(),
  multiHistos_(false),
  hMultiplicity_(),
  hMultiVsScale_(0),
  jetPtHistos_(false),
  hAllJetsPt_(),
  hRecoJetsPt_(),
  hBabyJetsPt_(),
  vertexHistos_(false),
  hNumVertex_(),
  atHistos_(false),
  hAlphaT_(),
  hAlphaTvsScale_(),
  dalitzHistos_(false),
  hDalitz_(),
  minBiasDeltaPhiHistos_(false),
  hMinBiasDeltaPhi_(),
  babyJetsHistos_(false),
  hBabyJets_(),
  babyJetsMhtHistos_(false),
  hBabyJetsMht_(),
  hPassAlphaT_(),
  hPassDeadEcal_(),
  hPassBaby_(),
  hPassTrackless_(),
  hPassRecHit_(),
  hPassMinBiasDPhi_(),
  hFailAlphaT_(),
  hFailDeadEcal_(),
  hFailBaby_(),
  hFailTrackless_(),
  hFailMinBiasDPhi_(),
  // RECO cntrs
//   cntr_baseline(0.),
//   cntr_leading_jet_eta(0.),
//   cntr_odd_jet_veto(0.),
//   cntr_bad_muon_in_jet(0.),
//   cntr_leading_jet_pt(0.),
//   cntr_second_jet_pt(0.),
//   cntr_correct_reco_bin(0.),
//   cntr_jet_multiplicity(0.),
//   cntr_at(0.),
//   cntr_pass_dead_ecal(0.),
//   cntr_pass_baby_cut(0.),
//   cntr_pass_pt_over_ht(0.),
  epochs_(),
  signal_(),
  monitor_(),
  reweight_(),
  names_()
{
  
  vstring signal;
  vstring monitor;
  vdouble reweight;
  
  // Optional parameters
  if ( ps.Contains("DirName") ) dirName_ = ps.Get<std::string>("DirName");
  if ( ps.Contains("MinObjects") ) nMin_ = ps.Get<int>("MinObjects");
  if ( ps.Contains("MaxObjects") ) nMax_ = ps.Get<int>("MaxObjects");
  if ( ps.Contains("Verbose") ) verbose_ = ps.Get<bool>("Verbose");
  if ( ps.Contains("NoQCD") ) noQcd_ = ps.Get<bool>("NoQCD");
  if ( ps.Contains("NoCleaningInDenom") ) noCleaningInDenom_ = ps.Get<bool>("NoCleaningInDenom");
  if ( ps.Contains("Filter") ) filter_ = ps.Get<int>("Filter"); 
  if ( ps.Contains("ScaleInSignalRegion") ) scaleSignal_ = ps.Get<bool>("ScaleInSignalRegion"); 
  if ( ps.Contains("ScaleSingleJetThreshold") ) scaleSingle_ = ps.Get<bool>("ScaleSingleJetThreshold"); 
  if ( ps.Contains("TriggerEpochs") ) epochs_ = ps.Get< std::vector<double> >("TriggerEpochs"); 
  if ( ps.Contains("SignalTriggers") ) signal = ps.Get< vstring >("SignalTriggers"); 
  if ( ps.Contains("MonitorTriggers") ) monitor = ps.Get< vstring >("MonitorTriggers"); 
  if ( ps.Contains("VertexReweighting") ) reweight = ps.Get< vdouble >("VertexReweighting"); 
  if ( ps.Contains("Inclusive") ) inclusive_ = ps.Get<bool>("Inclusive"); 
  if ( ps.Contains("AlphaTDefault") ) aT_ = (uint)ps.Get<int>("AlphaTDefault");
  if ( ps.Contains("HtOffset") ) offset_ = ps.Get<double>("HtOffset"); 
  
  if ( ps.Contains("CutFlowHistos") ) cutFlowHistos_ = ps.Get<bool>("CutFlowHistos"); 
  if ( ps.Contains("HtHistos") ) htHistos_ = ps.Get<bool>("HtHistos"); 
  if ( ps.Contains("MeffHistos") ) meffHistos_ = ps.Get<bool>("MeffHistos"); 
  if ( ps.Contains("MhtHistos") ) mhtHistos_ = ps.Get<bool>("MhtHistos"); 
  if ( ps.Contains("MhtOverHtHistos") ) mhtOverHtHistos_ = ps.Get<bool>("MhtOverHtHistos"); 
  if ( ps.Contains("MhtOverMeffHistos") ) mhtOverMeffHistos_ = ps.Get<bool>("MhtOverMeffHistos"); 
  if ( ps.Contains("MultiplicityHistos") ) multiHistos_ = ps.Get<bool>("MultiplicityHistos"); 
  if ( ps.Contains("JetPtHistos") ) jetPtHistos_ = ps.Get<bool>("JetPtHistos"); 
  if ( ps.Contains("NumVertexHistos") ) vertexHistos_ = ps.Get<bool>("NumVertexHistos"); 
  if ( ps.Contains("AlphaTHistos") ) atHistos_ = ps.Get<bool>("AlphaTHistos"); 
  if ( ps.Contains("DalitzHistos") ) dalitzHistos_ = ps.Get<bool>("DalitzHistos"); 
  if ( ps.Contains("BabyJetsHistos") ) babyJetsHistos_ = ps.Get<bool>("BabyJetsHistos"); 
  if ( ps.Contains("BabyJetsMhtHistos") ) babyJetsMhtHistos_ = ps.Get<bool>("BabyJetsMhtHistos"); 
  if ( ps.Contains("MinBiasDPhiHistos") ) minBiasDeltaPhiHistos_ = ps.Get<bool>("MinBiasDPhiHistos"); 
  if ( ps.Contains("GenHistos") ) genHistos_ = ps.Get<bool>("GenHistos"); 

  if ( ps.Contains("AddMuon") ) addMuon_ = ps.Get<bool>("AddMuon"); 
  if ( ps.Contains("OnlyGenPtHat") ) onlyGenPtHat_ = ps.Get<bool>("OnlyGenPtHat"); 
  if ( ps.Contains("OnlyFull") ) onlyFull_ = ps.Get<bool>("OnlyFull"); 
  if ( ps.Contains("UseMeff") ) useMeff_ = ps.Get<bool>("UseMeff"); 
  
  // Required parameters
  maxLeadingJetEta_ = ps.Get<double>("MaxLeadingJetEta");
  babyCut_ = ps.Get<double>("BabyJetsCut"); 
  alphaT_ = ps.Get< std::vector<double> >("AlphaT"); 
  scale_ = ps.Get<bool>("Scale"); 
  ht_ = ps.Get<int>("HtBin"); 
  pt1_ = ps.Get<double>("MinJetPt1");
  pt2_ = ps.Get<double>("MinJetPt2");
  pt3_ = ps.Get<double>("MinJetPt3");
  htNbins_ = (uint)ps.Get<int>("HtNbins"); 
  htXlow_ = ps.Get<double>("HtXlow"); 
  htXhigh_ = ps.Get<double>("HtXhigh"); 

  // Override binning if defined
  if ( ps.Contains("HtBinning") ) {
    htBins_ = ps.Get< std::vector<double> >("HtBinning"); 
    if ( !htBins_.empty() ) {
      htNbins_ = htBins_.size() - 1;
      htXlow_ = htBins_.front();
      htXhigh_ = htBins_.back();
    }
  }
  
  useFile_ = ps.Get<bool>("UseDeadEcalFile"); 
  deadEcalRegionDrCut_ = ps.Get<double>("DeadEcalRegionDrCut"); 
  deadEcalRegionEtaCut_ = ps.Get<double>("DeadEcalRegionEtaCut"); 
  minJetPtCut_ = ps.Get<double>("MinJetPtCut"); 
  nBadCells_ = ps.Get<int>("NBadCells"); 
  deadECALfile_ = ps.Get<std::string>("DeadEcalFile"); 
  minBiasDeltaPhiCut_ = ps.Get<double>("MinBiasDeltaPhiCut"); 
  dead_ = new DeadECALCut(deadEcalRegionEtaCut_,
			  deadEcalRegionDrCut_,
			  minBiasDeltaPhiCut_,
			  minJetPtCut_,
			  nBadCells_,
			  useFile_,
			  deadECALfile_);

  rechit_ = new sumRecHitPtCut( ps.Get<double>("SumRecHitPtCut") );

  // Calc lumi fractions
  if ( epochs_.size() > 1 ) {

    // Total lumi
    double lumi = 0.;
    std::vector<double>::iterator ii = epochs_.begin();
    std::vector<double>::iterator jj = epochs_.end();
    for ( ; ii != jj; ++ii ) { lumi += *ii; }
    
    // Fractional lumi
    for ( ii = epochs_.begin(); ii != jj; ++ii ) { *ii /= lumi; std::cout << "f_{lumi}: " << *ii << endl; }

    // Integrated fractional lumi
    double integral = 0.;
    for ( ii = epochs_.begin(); ii != jj; ++ii ) { integral += *ii; *ii = integral; }
    
  } else { epochs_.clear(); }
    
  // Parse signal trigger strings
  if ( !signal.empty() ) {
    unsigned int ii = 0;
    unsigned int jj = 0;
    signal_.clear();
    signal_.resize( htNbins_, vstring(100) );
    vstring::const_iterator iter = signal.begin();
    vstring::const_iterator jter = signal.end();
    for ( ; iter != jter; ++iter ) { 
      if ( *iter == "" ) { signal_[ii].resize(jj); ii++; jj = 0; }
      else { 
	if ( ii < signal_.size() && jj < signal_[ii].size() ) { signal_[ii][jj] = *iter; } 
	else { break; }
	jj++; 
      }
    }
    if ( ii < htNbins_ ) { signal_.resize(ii); signal_.resize(htNbins_,vstring(signal_[ii-1])); }

    for ( vvstring::const_iterator i = signal_.begin(); i != signal_.end(); ++i ) {
      std::cout << i->size() << ": ";
      for ( vstring::const_iterator j = i->begin(); j != i->end(); ++j ) {
	std::cout << "\"" << *j << "\" ";
      }
      std::cout << std::endl;
    }
  }

  // Parse monitor reference trigger strings
  if ( !monitor.empty() ) {
    unsigned int ii = 0;
    unsigned int jj = 0;
    monitor_.clear();
    monitor_.resize( htNbins_, vstring(100) );
    vstring::const_iterator iter = monitor.begin();
    vstring::const_iterator jter = monitor.end();
    for ( ; iter != jter; ++iter ) { 
      if ( *iter == "" ) { monitor_[ii].resize(jj); ii++; jj = 0; }
      else { 
	if ( ii < monitor_.size() && jj < monitor_[ii].size() ) { monitor_[ii][jj] = *iter; } 
	else { break; }
	jj++; 
      }
    }
    if ( ii < htNbins_ ) { monitor_.resize(ii); monitor_.resize(htNbins_,vstring(monitor_[ii-1])); }

    for ( vvstring::const_iterator i = monitor_.begin(); i != monitor_.end(); ++i ) {
      std::cout << i->size() << ": ";
      for ( vstring::const_iterator j = i->begin(); j != i->end(); ++j ) {
	std::cout << "\"" << *j << "\" ";
      }
      std::cout << std::endl;
    }
  }

  // Parse vertex reweight factors
  if ( reweight.size() > 1 ) {
    unsigned int ii = 0;
    unsigned int jj = 0;
    reweight_.clear();
    reweight_.resize( htNbins_, vdouble(100) );
    vdouble::const_iterator iter = reweight.begin();
    vdouble::const_iterator jter = reweight.end();
    for ( ; iter != jter; ++iter ) { 
      if ( *iter < 0. ) { reweight_[ii].resize(jj); ii++; jj = 0; }
      else { 
	if ( ii < reweight_.size() && jj < reweight_[ii].size() ) { reweight_[ii][jj] = *iter; } 
	else { break; }
	jj++; 
      }
    }
    if ( ii < htNbins_ ) { reweight_.resize(ii); reweight_.resize(htNbins_,vdouble(reweight_[ii-1])); }
    
    for ( vvdouble::const_iterator i = reweight_.begin(); i != reweight_.end(); ++i ) {
      std::cout << i->size() << ": ";
      for ( vdouble::const_iterator j = i->begin(); j != i->end(); ++j ) {
	std::cout << "\"" << *j << "\" ";
      }
      std::cout << std::endl;
    }
  } else { reweight.clear(); }
  
  // Define binning in terms of HT, Meff and pT thresholds
  binning();
  
  // Add 0. cut value 
  alphaT_.insert( alphaT_.begin(), 0. );
  aT_++; //@@ first value is ZERO
  if ( aT_ >= alphaT_.size() ) { aT_ = 0; }

  // Upper bounds of bins
  if ( ps.Contains("UpBinning") ) {
    upBins_ = ps.Get< std::vector<double> >("UpBinning"); 
    if ( htBins_.size() - upBins_.size() != 1 ) {
      upBins_.clear();
      for ( uint i = 0; i < htBins_.size(); ++i ) { 
	upBins_.push_back( htBins_[i+1] ); 
      }
    }
  }
  
  // Init random number generator
  srand( time(NULL) );
  
}

// -----------------------------------------------------------------------------
//
RaT::~RaT() {
//   std::cout << std::fixed 
// 	    << "RECO cut flow:" << std::endl
//     //<< "cntr_signal_region: " << cntr_baseline << std::endl
// 	    << "cntr_correct_reco_bin: " << cntr_correct_reco_bin << std::endl
// 	    << "cntr_leading_jet_eta: " << cntr_leading_jet_eta << std::endl
// 	    << "cntr_bad_muon_in_jet: " << cntr_bad_muon_in_jet << std::endl
// 	    << "cntr_odd_jet_veto: " << cntr_odd_jet_veto << std::endl
// 	    << "cntr_leading_jet_pt: " << cntr_leading_jet_pt << std::endl
// 	    << "cntr_second_jet_pt: " << cntr_second_jet_pt << std::endl
// 	    << "cntr_jet_multiplicity: " << cntr_jet_multiplicity << std::endl
// 	    << "cntr_at: " << cntr_at << std::endl
// 	    << "cntr_pass_dead_ecal: " << cntr_pass_dead_ecal << std::endl 
// 	    << "cntr_pass_baby_cut: " << cntr_pass_baby_cut << std::endl
// 	    << "cntr_pass_pt_over_ht: " << cntr_pass_pt_over_ht << std::endl;

  std::cout << " HT triggers found:  " << std::endl;
  vstring::const_iterator ii = names_.begin();
  vstring::const_iterator jj = names_.end();
  for ( ; ii != jj; ++ii ) {
    std::cout << *ii << std::endl;
  }

}

// -----------------------------------------------------------------------------
//
std::ostream& RaT::Description( std::ostream& ss ) {

  ss << "[RaT::Description]" 
     << std::endl
     << " Writing histograms to directory \"" << dirName_ << "\""
     << "for events with " << nMin_ << "<objects<" << nMax_ << "."
     << std::endl
     << " Verbose=" << verbose_ 
     << std::endl;

  ss << " Thresholds scaled according to HT bins:" << std::endl
     << " --------------------------------------------------------" << std::endl
     << " |  HT  |    (pT1,pT2,pT3) | Meff |          (x1,x2,x3) |" << std::endl
     << " --------------------------------------------------------" << std::endl;
  for ( uint ii = 0; ii < htNbins_; ++ii ) {
    double ht = useMeff_ ? htBins_[ii] - htPt3Bins_[ii] : htBins_[ii];
    double pt1 = htPt1Bins_[ii];
    double pt2 = htPt2Bins_[ii];
    double pt3 = htPt3Bins_[ii];
    double meff = useMeff_ ? htBins_[ii] : htBins_[ii] + htPt3Bins_[ii];
    ss << " | " << std::setw(4) << std::setprecision(3) << ht
       << " | (" << std::setw(4) << std::setprecision(3) << pt1
       << "," << std::setw(4) << std::setprecision(3) << pt2
       << "," << std::setw(4) << std::setprecision(3) << pt3
       << ") | " << std::setw(4) << std::setprecision(4) << meff
       << " | (" << std::setw(5) << std::setprecision(3) << (norm_*pt1/meff)
       << "," << std::setw(5) << std::setprecision(3) << (norm_*pt2/meff) 
       << "," << std::setw(5) << std::setprecision(3) << (norm_*pt3/meff) 
       << ") |" << std::endl;
  }
  ss << " --------------------------------------------------------" << std::endl;
  
  ss << std::fixed << std::setprecision(8);
  return ss;

}

// -----------------------------------------------------------------------------
//
void RaT::binning() {
  
  // HT binning
  if ( htBins_.empty() ) {
    for ( uint ii = 0; ii < htNbins_; ++ii ) { 
      double width = ( htXhigh_ - htXlow_ ) / htNbins_;
      htBins_.push_back(htXlow_+width*ii);
    }
    htBins_.push_back(htXhigh_);
  }
  
  // Normalisation: x_{1} + x_{2} + x_{3} = norm
  
  // pT thresholds that scale with HT
  double meff_default = htBins_[ht_] + pt3_;
  double x3_default = ( norm_ * pt3_ ) / meff_default; 
  double x3_factor = ( norm_ - x3_default ) / x3_default;

  for ( unsigned int iht = 0; iht <= htNbins_; ++iht ) {
    double ht = htBins_[iht];
    double pt3 = ht / x3_factor;
    double meff = ht + pt3;
    double pt1 = pt1_ * meff / meff_default;
    double pt2 = pt2_ * meff / meff_default;
    htPt1Bins_.push_back( scale_ && ( ht <= htBins_[ht_] || scaleSignal_ ) ? pt1 : pt1_ );
    htPt2Bins_.push_back( scale_ && ( ht <= htBins_[ht_] || scaleSignal_ ) ? pt2 : pt2_ );
    htPt3Bins_.push_back( scale_ && ( ht <= htBins_[ht_] || ( scaleSignal_ && scaleSingle_ ) ) ? pt3 : pt3_ );

  }

  // Apply offset to HT binning
  for ( uint ii = 0; ii < htNbins_; ++ii ) { htBins_[ii] += offset_; }

  std::cout << (*this);
  
}

// -----------------------------------------------------------------------------
//
bool RaT::Process( Event::Data& ev ) {

//   std::cout << "[RaT::Process] EventNumber: " << ev.GetEventNumber() << std::endl;
  
  // Use as filter for interesting events
  bool keep_event = false;

  // Event weight
  Double_t weight = ev.GetEventWeight();

  // Toy MC using gen jets
  bool do_toy = false;
  std::vector<LorentzV> toy;

  double mass_scale = 0;
  
  // Gen-level info
  try {
    
    //std::cout << std::endl;
    
    // Histogram of pT hat 
    double pt_hat = ev.pthat(); 
    if ( hGenPtHat_[0] ) hGenPtHat_[0]->Fill( pt_hat, weight ); 
    mass_scale = 2. * pt_hat;
    if ( onlyGenPtHat_ ) { return true; }

    // MHT
    int ngenjets = 0;
    LorentzV jets_mht(0.,0.,0.,0.);
    std::vector<Event::Jet const*> jets = ev.JD_CommonJets().accepted;
    for ( uint ii = 0; ii < jets.size(); ++ii ) {
      if ( jets[ii]->Pt() > 50. ) { jets_mht -= *jets[ii]; ngenjets++; }
    }
    
    // MET
    LorentzV gen_met = *(ev.genMetP4True());
    
    // Particles
    LorentzV nu_max(0.,0.,0.,0.);
    LorentzV nu_mht(0.,0.,0.,0.);
    LorentzV mu_mht(0.,0.,0.,0.);
    LorentzV el_mht(0.,0.,0.,0.);
    LorentzV ph_mht(0.,0.,0.,0.);

    // Construct decay chains
    
//     std::vector<const Event::GenObject*> products;
//     typedef std::map<int,const Event::GenObject*> Objects;
//     std::vector<Objects> chains;
//     chains.resize( 2, Objects() ); 
//     std::vector<LorentzV> partons;
//     partons.resize( 2, LorentzV(0.,0.,0.,0.) ); 
    
//     std::vector<Event::GenObject> obj = ev.GenParticles(); 
//     for ( uint ii = 0; ii < obj.size(); ++ii ) {
      
//       Event::GenObject gen = obj[ii];
      
//       if ( gen.GetStatus() == 3 ) {
//   	std::cout << std::fixed
//  		  << std::setprecision(-1)
//  		  << " index: " << ii
//  		  << " GetIndex: " << gen.GetIndex()
//   		  << " Id: " << gen.GetID()
//   		  << " Mother: " <<gen.GetMother()
//   		  << " MotherID: " << gen.GetMotherID()
//   		  << " Et " << gen.Et()
//   		  << " Pt " << gen.Pt()
//   		  << " Eta " << gen.Eta()
//   		  << " Phi " << gen.Phi()
//   		  << " Status " << gen.GetStatus()
//   		  << std::endl;
//       }
      
//       if ( gen.GetStatus() == 3 ) {
// 	if ( gen.GetMother() < 0 && gen.GetIndex() < 2 ) { // colliding protons
// 	  chains[gen.GetIndex()][gen.GetIndex()] = &obj[ii];
// 	} else { // initial state particles
// 	  for ( uint iii = 0; iii < chains.size(); ++iii ) {
// 	    if ( chains[iii].find( gen.GetMother() ) != chains[iii].end() ) {
// 	      chains[iii][gen.GetIndex()] = &obj[ii];
// 	      partons[iii] += obj[ii];
// 	      break;
// 	    }
// 	  }
// 	}
//       }

//       if ( gen.GetStatus() == 3 ) {
// 	if ( gen.GetID() != 2212 && 
// 	     gen.GetMother() >= 0 && 
// 	     gen.GetIndex() >= 2 ) { // not the colliding protons
// 	  products.push_back( &obj[ii] );
// 	}
//       }
      
//     }
    
//     // Keep 2 leading jets and balance with third jet
//     //sort( products.begin(), products.end(), SortByPt );
//     std::vector<LorentzV> tmp; 
//     for ( uint i = 0; i < products.size(); ++i ) { tmp.push_back( *products[i] ); }
//     std::sort( tmp.begin(), tmp.end(), SortByPt );
//     if ( tmp.size() > 1 ) {
//       //chains[0][tmp[0].GetIndex()] = tmp[0];
//       //chains[1][tmp[1].GetIndex()] = tmp[1];
//       partons[0] += tmp[0];
//       partons[1] += tmp[1];
//     }
    
//     // Assign jets to pseudo-jets assuming ET-balancing scheme
//     std::vector<bool> pseudo;
//     AlphaT()(products,pseudo);
//     for ( uint i = 0; i < products.size(); ++i ) {
//       uint idx = pseudo[i] ? 1 : 0;
//       chains[idx][products[i]->GetIndex()] = products[i];
//       partons[idx] += massless(*products[i]);
//     }
    
//     for ( uint i = 0; i < chains.size(); ++i ) {
//       Objects::const_iterator j1 = chains[i].begin();
//       Objects::const_iterator j2 = chains[i].end();
//       //for ( uint j = 0; j < chains[i].size(); ++j ) {
//       for ( ; j1 != j2; ++j1 ) {
// 	std::cout << std::fixed
// 		  << std::setprecision(-1)
// 		  << " i: " << i
// 		  << " j: " << j1->first
// 		  << " Index: " << j1->second->GetIndex()
// 		  << " Id: " << j1->second->GetID()
// 		  << " Mother: " <<j1->second->GetMother()
// 		  << " MotherID: " << j1->second->GetMotherID()
// 		  << " mass " << j1->second->mass() << " "
// 		  << " Et " << j1->second->Et()
// 		  << " Pt " << j1->second->Pt()
// 		  << " Eta " << j1->second->Eta()
// 		  << " Phi " << j1->second->Phi()
// 		  << " degs " << (180./acos(-1.))*j1->second->Phi()
// 		  << " Status " << j1->second->GetStatus()
// 		  << std::endl;
//       }
//     }
    
//     for ( uint i = 0; i < partons.size(); ++i ) {
//       std::cout<< std::fixed
// 	       << std::setprecision(3)
// 	       << " i " << i
// 	       << " Et " << partons[i].Et() << " "
// 	       << " Pt " << partons[i].Pt() << " "
// 	       << " eta " << partons[i].eta() << " "
// 	       << " phi " << partons[i].phi() << " "
// 	       << " degs " << (180./acos(-1.))*partons[i].phi() << " " 
// 	       << " m " << partons[i].mass() << " "
// 	       << " E " << partons[i].E() << " "
// 	       << " Px " << partons[i].Px() << " "
// 	       << " Py " << partons[i].Py() << " "
// 	       << " Pz " << partons[i].Pz() << " "
// 	       << std::endl;
//     }
    
//     for ( uint i = 0; i < partons.size(); ++i ) {
//       partons[i].SetPxPyPzE( partons[i].Px(), partons[i].Py(), 0., partons[i].E() );
//       //partons[i] = massless(partons[i]);
//       partons[i].SetM(0.);
//     }
    
//     partons.resize( 3, LorentzV(0.,0.,0.,0.) ); 
//     partons[2] -= partons[0];
//     partons[2] -= partons[1];
//     partons[2].SetM(0.);
//     //partons[2] = massless(partons[2]);

//     std::cout << " scale: " << ht_scale
// 	      << " " << partons[0].Pt() + partons[1].Pt() 
// 	      << " " << ( partons[0] + partons[1] ).mass() 
// 	      << " " << ( partons[0] + partons[1] + partons[2] ).mass() 
// 	      << " " << partons[2].Pt()
// 	      << " " << partons[2].Px()
// 	      << " " << partons[2].Py()
// 	      << " " << partons[2].Pz()
// 	      << std::endl;
    
//     // Copy parton LV into toy MC container
//     if ( do_toy ) {
//       toy.reserve( partons.size() );
//       std::copy( partons.begin(), partons.end(), back_inserter(toy) );
//     }
    
//     partons.resize( 4, LorentzV(0.,0.,0.,0.) ); 
//     partons[3] -= partons[0];
//     partons[3] -= partons[1];
//     partons[3] -= partons[2];
//     partons[3].SetM(0.);
//     //partons[3] = massless(partons[3]);
    
//     Boost b( 0., 0., partons[2].BoostToCM().Z() );
//     partons.resize( 4, LorentzV(0.,0.,0.,0.) ); 
//     partons[3] = b(partons[2]);

//     for ( uint i = 0; i < partons.size(); ++i ) {
//       std::cout << std::fixed
// 		<< std::setprecision(3)
// 		<< " i " << i
// 		<< " Et " << partons[i].Et() << " "
// 		<< " Pt " << partons[i].Pt() << " "
// 		<< " eta " << partons[i].eta() << " "
// 		<< " phi " << partons[i].phi() << " "
// 		<< " degs " << (180./acos(-1.))*partons[i].phi() << " " 
// 		<< " m " << partons[i].mass() << " "
// 		<< " E " << partons[i].E() << " "
// 		<< " Px " << partons[i].Px() << " "
// 		<< " Py " << partons[i].Py() << " "
// 		<< " Pz " << partons[i].Pz() << " "
// 		<< std::endl;
//     }
    
    std::vector<Event::GenObject> objects = ev.GenParticles(); 
    for ( uint ii = 0; ii < objects.size(); ++ii ) {
      
      Event::GenObject gen = objects[ii];
      
//       if ( gen.GetStatus() == 3 ) {
//   	std::cout << std::scientific
//  		  << std::setprecision(8)
//  		  << " index: " << ii
//   		  << " Id: " << gen.GetID()
//   		  << " Mother: " <<gen.GetMother()
//   		  << " MotherID: " << gen.GetMotherID()
//   		  << " Et " << gen.Et()
//   		  << " Pt " << gen.Pt()
//   		  << " Eta " << gen.Eta()
//   		  << " Phi " << gen.Phi()
//   		  << " Status " << gen.GetStatus()
//   		  << std::endl;
//       }

      //hGenPdgId_[0]->Fill( abs(gen.GetID()), weight ); 
      //hGenStatus_[0]->Fill( gen.GetStatus(), weight ); 
      
      // Neutrinos
      if ( gen.GetStatus() == 1 &&
	   ( abs(gen.GetID()) == 12 ||
	     abs(gen.GetID()) == 14 ||
	     abs(gen.GetID()) == 16 ) ) {
	nu_mht -= gen;
	if ( gen.Pt() > nu_max.Pt() ) { nu_max = gen; }
	hGenNuPt_[0]->Fill( gen.Pt(), weight ); 
      }

      // Muons
      if ( gen.GetStatus() == 1 &&
	   abs(gen.GetID()) == 13 ) {
	mu_mht -= gen;
	//hGenMuPt_[0]->Fill( gen.Pt(), weight ); 
      }

      // Electrons
      if ( gen.GetStatus() == 1 &&
	   abs(gen.GetID()) == 11 ) {
	el_mht -= gen;
	//hGenElPt_[0]->Fill( gen.Pt(), weight ); 
      }
      
      // Photons
      if ( gen.GetStatus() == 1 &&
	   abs(gen.GetID()) == 22 ) {
	ph_mht -= gen;
	//hGenPhPt_[0]->Fill( gen.Pt(), weight ); 
      }
      
    }

    hGenNuMet_[0]->Fill( nu_mht.Pt(), weight ); 
    hGenMetVsGenNuMet_[0]->Fill( nu_mht.Pt(), gen_met.Pt(), weight ); 
    hGenJetMhtVsGenNuMet_[0]->Fill( nu_mht.Pt(), jets_mht.Pt(), weight ); 

    hGenMuMet_[0]->Fill( mu_mht.Pt(), weight ); 
    hGenJetMhtVsGenMuMet_[0]->Fill( mu_mht.Pt(), jets_mht.Pt(), weight ); 

    hGenElMet_[0]->Fill( el_mht.Pt(), weight ); 
    hGenJetMhtVsGenElMet_[0]->Fill( el_mht.Pt(), jets_mht.Pt(), weight ); 

    hGenPhMet_[0]->Fill( ph_mht.Pt(), weight ); 
    hGenJetMhtVsGenPhMet_[0]->Fill( ph_mht.Pt(), jets_mht.Pt(), weight ); 

    //hGenNuPtMax_[0]->Fill( nu_max.Pt(), weight ); 
    //hGenMetVsGenNuPtMax_[0]->Fill( nu_max.Pt(), gen_met.Pt(), weight ); 
    
    // Event selection
    if ( nu_mht.Pt() > 10. || 
 	 mu_mht.Pt() > 10. || 
 	 el_mht.Pt() > 10. || 
 	 ph_mht.Pt() > 10. ) { return false; }
    
    // Histograms
    fill( ngenjets, hGenJetMht_, jets_mht.Pt(), weight ); //hGenJetMht_->Fill( jets_mht.Pt(), weight ); 
    hGenMet_[0]->Fill( gen_met.Pt(), weight ); 
    
  } catch (...){ std::cout << "No gen-level info to print!" << std::endl; }
  
  // SMS 
  try {
    if ( ev.SMSvalid.enabled() && 
	 ev.SMSvalid() && 
	 ev.MG.enabled() && 
	 ev.MLSP.enabled() ) { 
      if ( hSMS_[0] ) hSMS_[0]->Fill( ev.MG(), ev.MLSP(), weight ); 
    }
    //std::cout << std::endl;

  } catch (...){}
  
  // Cut flow counter
  int pass_cntr = 0;
  
  // MET
  LorentzV calo_met = *(ev.metP4caloTypeII());

  // Retrieve "common" jets from ntuple
  std::vector<Event::Jet const*> common(0); 
  if ( do_toy ) {
    for ( uint i = 0; i < toy.size(); ++i ) {
      common.push_back( new Event::Jet( massless(toy[i]), 0., i, true, true, true ) ); 
    }
  } else { common = ev.JD_CommonJets().accepted; }

  // Retrieve "odd" jets from ntuple
  std::vector<Event::Jet const*> odd(0);
  if ( !do_toy ) { odd = ev.JD_CommonJets().odd; }
  
  // Number of HT/Meff bins 
  int nbins = htNbins_; 

  // MHT in signal region
  LorentzV mht_reco_signal(0.,0.,0.,0.);
  double baby_val = 1000.;
  if ( ht_ < htNbins_ ) { 
    
    // Undo muon correction in CaloMET (to be used only when muon vetoes removed!)
    LorentzV met = calo_met;
    if (addMuon_) {
      std::vector<Event::Lepton const*> muons = ev.LD_CommonMuons().accepted;
      std::vector<Event::Lepton const*>::const_iterator imuon = muons.begin();
      std::vector<Event::Lepton const*>::const_iterator jmuon = muons.end();
      for ( ; imuon != jmuon; ++imuon ) { if ( *imuon ) { met += **imuon; } }
    }
    
    std::vector<Event::Jet const*>::const_iterator ireco = common.begin();
    std::vector<Event::Jet const*>::const_iterator jreco = common.end();
    for ( ; ireco != jreco; ++ireco ) {
      if ( (*ireco)->Pt() > htPt3Bins_[ht_] ) { mht_reco_signal -= **ireco; }
    }
    baby_val = met.Pt() > 0. ? ( mht_reco_signal.Pt() / met.Pt() ) : 1000.; 
  }

  // Init some info before HT loop
  int njets = -1;
  int ibin = -1;
  bool correct_reco_bin = false;
  double ht_lower = -1.;
  double ht_upper = -1.;
    
  // Define jet pT thresholds 
  double pt1_threshold = 0.;
  double pt2_threshold = 0.;
  double pt3_threshold = 0.;

  bool third = true;
  Vars tmp;
  
  if (!third) {

    // (Reverse!) Loop through HT/Meff bins 
    for ( int jbin = 0; jbin < nbins; ++jbin ) {
      ibin = (nbins-1) - jbin;
      
      double ht_reco = 0.;
      LorentzV mht_reco(0.,0.,0.,0.);
      std::vector<Event::Jet const*>::const_iterator ireco = common.begin();
      std::vector<Event::Jet const*>::const_iterator jreco = common.end();
      for ( ; ireco != jreco; ++ireco ) {
	if ( (*ireco)->Pt() > htPt3Bins_[ibin] ) { 
	  tmp.push_back( massless(**ireco) );
	  ht_reco += (*ireco)->Et();
	  mht_reco -= **ireco;
	}
      }
      double meff_reco = ht_reco + mht_reco.Pt();
      double var_reco = useMeff_ ? meff_reco : ht_reco;
    
      ht_lower = htBins_[ibin];
      ht_upper = upBins_.empty() ? ( (nbins-ibin) != 1 ? htBins_[ibin+1] : 10000. ) : upBins_[ibin]; 
      if ( inclusive_ ) { if ( var_reco > ht_lower ) { correct_reco_bin = true; } }
      else { if ( var_reco > ht_lower && var_reco < ht_upper ) { correct_reco_bin = true; } }
      
      // Define jet pT threshold
      pt1_threshold = htPt1Bins_[ibin];
      pt2_threshold = htPt2Bins_[ibin];
      pt3_threshold = htPt3Bins_[ibin];
      
      if ( correct_reco_bin ) { break; }
    
    }

  } else {

    // Mass scale
    double var_reco = mass_scale;

    // Loop through bins
    for ( int jbin = 0; jbin < nbins; ++jbin ) {
      
      // Find appropriate bin
      ibin = (nbins-1) - jbin;
      ht_lower = htBins_[ibin];
      ht_upper = upBins_.empty() ? ( (nbins-ibin) != 1 ? htBins_[ibin+1] : 10000. ) : upBins_[ibin]; 
      if ( inclusive_ ) { if ( var_reco > ht_lower ) { correct_reco_bin = true; } }
      else { if ( var_reco > ht_lower && var_reco < ht_upper ) { correct_reco_bin = true; } }
      
      // Define jet pT thresholds 
      pt1_threshold = htPt1Bins_[ibin];
      pt2_threshold = htPt2Bins_[ibin];
      pt3_threshold = htPt3Bins_[ibin];
      
      if ( correct_reco_bin ) { break; }
      
    }
    
//     // Event does not fall in bin
//     if ( !correct_reco_bin ) { return false; }
    
    for ( uint i = 0; i < common.size(); ++i ) {
      if ( common[i]->Pt() > htPt3Bins_[0] ) { 
	tmp.push_back( massless(*common[i]) );
	tmp.update();
	
// 	std::cout << std::fixed
// 		  << std::setprecision(4)
// 		  << "TEST"
// 		  << " nj=" << tmp.njets()
// 		  << " et=" << tmp.jets().back().Et()
// 		  << " ht=" << tmp.ht()
// 		  << " mht=" << tmp.mht().Pt() 
// 		  << " meff=" << tmp.meff()
// 	  //<< " et/meff=" << val
// 	  //<< " ref=" << test
// 	  //<< " diff=" << ( val - test )
// 	  //<< " cache=" << cache
// 		  << std::endl;

       }
     }
    
    // Useful histos
    
    if ( genHistos_ ) { 

      fill( tmp.njets(), hVarVsScale_[0], mass_scale, (1.*tmp.njets()), weight );
      fill( tmp.njets(), hVarVsScale_[1], mass_scale, tmp.ht(), weight );
      fill( tmp.njets(), hVarVsScale_[2], mass_scale, tmp.dht(), weight );
      fill( tmp.njets(), hVarVsScale_[3], mass_scale, tmp.mht().Pt(), weight );
      fill( tmp.njets(), hVarVsScale_[4], mass_scale, tmp.at(), weight );
      fill( tmp.njets(), hVarVsScale_[5], mass_scale, tmp.meff(), weight );
      fill( tmp.njets(), hVarVsScale_[6], mass_scale, tmp.jets().back().Et(), weight );
      fill( tmp.njets(), hVarVsScale_[7], mass_scale, tmp.jets().front().Et(), weight );
      fill( tmp.njets(), hVarVsScale_[8], mass_scale, (tmp.ht()/(1.*tmp.njets())), weight );
    
      fill( tmp.njets(), hVarOverScaleVsJetPt_[0], tmp.jets().back().Et(), (1.*tmp.njets())/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[1], tmp.jets().back().Et(), tmp.ht()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[2], tmp.jets().back().Et(), tmp.dht()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[3], tmp.jets().back().Et(), tmp.mht().Pt()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[4], tmp.jets().back().Et(), tmp.at()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[5], tmp.jets().back().Et(), tmp.meff()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[6], tmp.jets().back().Et(), tmp.jets().back().Et()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[7], tmp.jets().back().Et(), tmp.jets().front().Et()/mass_scale, weight );
      fill( tmp.njets(), hVarOverScaleVsJetPt_[8], tmp.jets().back().Et(), (tmp.ht()/(1.*tmp.njets()))/mass_scale, weight );

    }
    
//     std::cout << std::fixed
//  	      << std::setprecision(3)
//  	      << "SELECTED"
//   	      << " njets=" << tmp.njets()
//   	      << " pt3=" << pt3_threshold
//       //<< " pt1=" << pt1_threshold
//   	      << " mass=" << mass_scale
//   	      << " ibin=" << ibin
//   	      << " correct_reco_bin=" << correct_reco_bin
//   	      << std::endl;

//     // Identify bin using mass scale
//     double var_reco = mass_scale; //useMeff_ ? meff_reco : ht_reco;
//     for ( int jbin = 0; jbin < nbins; ++jbin ) {
//       ibin = (nbins-1) - jbin;
//       ht_lower = htBins_[ibin];
//       ht_upper = upBins_.empty() ? ( (nbins-ibin) != 1 ? htBins_[ibin+1] : 10000. ) : upBins_[ibin]; 
//       if ( inclusive_ ) { if ( var_reco > ht_lower ) { correct_reco_bin = true; } }
//       else { if ( var_reco > ht_lower && var_reco < ht_upper ) { correct_reco_bin = true; } }
//       if ( correct_reco_bin ) { break; }
//     }
  
//     // Event does not fall in bin
//     if ( !correct_reco_bin ) { return false; }
    
//     double test = htPt3Bins_[ht_] / htBins_[ht_];
//     double cache = -1.;
//     for ( uint i = 0; i < common.size(); ++i ) {
//       tmp.push_back( massless(*common[i]) );
//       tmp.update();
      
//       //double val =  useMeff_ ? tmp.jets().back().Et() / tmp.meff() :  tmp.jets().back().Et() / tmp.ht();
//       double val =  tmp.jets().back().Et() / mass_scale;
      
//       if ( cache < 0. || ( val > test && val < cache ) ) { 
// 	cache = val;
// 	njets = tmp.jets().size(); 
	
// 	// Define jet pT thresholds 
// 	pt3_threshold = (int(100.*tmp.jets().back().Pt()))/100.;
// 	pt1_threshold = (htPt1Bins_[ht_]/htPt3Bins_[ht_]) * pt3_threshold;
// 	pt2_threshold = (htPt2Bins_[ht_]/htPt3Bins_[ht_]) * pt3_threshold;
	
//       }
    
//       //tmp.print();
//       std::cout << std::fixed
// 		<< std::setprecision(4)
// 		<< "TEST"
// 		<< " nj=" << tmp.njets()
// 		<< " et=" << tmp.jets().back().Et()
// 		<< " ht=" << tmp.ht()
// 		<< " mht=" << tmp.mht().Pt() 
// 		<< " meff=" << tmp.meff()
// 		<< " et/meff=" << val
// 		<< " ref=" << test
// 		<< " diff=" << ( val - test )
// 		<< " cache=" << cache
// 		<< std::endl;

//     }
    
//     std::cout << std::fixed
// 	      << std::setprecision(3)
// 	      << "SELECTED"
//  	      << " njets=" << njets
//  	      << " pt3=" << pt3_threshold
//       //<< " pt1=" << pt1_threshold
//  	      << " mass=" << mass_scale
//  	      << " ibin=" << ibin
//  	      << " correct_reco_bin=" << correct_reco_bin
//  	      << std::endl;
    
  }
  
  // Event does not fall in bin
  if ( !correct_reco_bin ) { return false; }
  
  // Trigger prescale (if one fires)
  double prescale = 1.;
  
  // Reweighting according to nVertex distributions
  double reweight = 1.;
  
  // Number of vertices
  int nvertices = 0;
  if ( vertexHistos_ ) {
    for ( int ii = 0; ii < ev.GetVertexSize(); ++ii ) {
      if( !ev.GetvertexIsFake(ii) && 
	  fabs( ev.GetvertexPosition(ii).Z() ) < 24. && 
	  ev.GetvertexNdof(ii)> 4 && 
	  ev.GetvertexPosition(ii).Rho() < 2. ) { nvertices++; }
    }
  }
  
  // Re-weight according to nBVertex distributions
  reweight = 1.;
  if ( !reweight_.empty() && ibin < (int)reweight_.size() ) {
    if( nvertices < (int)reweight_[ibin].size() ) {
      reweight = reweight_[ibin][nvertices];
      // 	std::cout << " jbin " << jbin
      // 		  << " ibin " << ibin
      // 		  << " nvertices " << nvertices
      // 		  << " reweight " << reweight
      // 		  << std::endl;
    }
  }
  
  // -------------------- RECO INFO --------------------
  
  // Calculate aT, HT, Meff and MHT from common jets
  std::vector<LorentzV> reco; 
  reco.reserve(10);
  LorentzV mht_reco(0.,0.,0.,0.);
  double at_reco = 0.;
  double ht_reco = 0.;
  double meff_reco = 0.;
  double x1_reco = 0.;
  double x2_reco = 0.;
    
  // Baby jets for dead ECAL cut
  std::vector<LorentzV> baby_jets_for_dead_ecal; 
  baby_jets_for_dead_ecal.reserve(20);
    
  // Baby jets
  std::vector<LorentzV> baby_jets; 
  baby_jets.reserve(20);
  LorentzV baby_mht(0.,0.,0.,0.);
  double baby_ht = 0.;
    
  // Loop through common jets and calc "reco" variables
  std::vector<Event::Jet const*>::const_iterator ireco = common.begin();
  std::vector<Event::Jet const*>::const_iterator jreco = common.end();
  for ( ; ireco != jreco; ++ireco ) {
    if ( (*ireco)->Pt() > pt3_threshold ) { 
      reco.push_back(**ireco); 
      ht_reco += (*ireco)->Et();
      mht_reco -= **ireco;
    } else {
      double scale = htPt3Bins_[0] > 0. ? pt3_threshold / htPt3Bins_[0] : 1.;
      if ( (*ireco)->Pt() > scale*5. ) {
	baby_jets.push_back(**ireco); 
	baby_ht += (*ireco)->Et();
	baby_mht -= **ireco;
      }
      if ( (*ireco)->Pt() > 10. ) {
	baby_jets_for_dead_ecal.push_back(**ireco); 
      }
    }
  }

  // Meff
  meff_reco = ht_reco + mht_reco.Pt();

  double var_reco = mass_scale; //useMeff_ ? meff_reco : ht_reco;

  // Calc AlphaT and Dalitz variables
  std::vector<bool> pseudo_reco;
  at_reco = AlphaT()( reco, pseudo_reco );
  calcDalitzVars( reco, pseudo_reco, mht_reco, x1_reco, x2_reco );
      
  // Odd jet veto
  bool odd_jet_veto = false;
  std::vector<Event::Jet const*>::const_iterator iodd = odd.begin();
  std::vector<Event::Jet const*>::const_iterator jodd = odd.end();
  for ( ; iodd != jodd; ++iodd ) {
    if ( (*iodd)->Pt() >= pt3_threshold ) { odd_jet_veto = true; }
  }
    
  // Bad muon in jets
  bool bad_muon_in_jet = false;
  std::vector<Event::Lepton>::const_iterator imuon = ev.LD_Muons().begin();
  std::vector<Event::Lepton>::const_iterator jmuon = ev.LD_Muons().end();
  for ( ; imuon != jmuon; ++imuon ) {
    if( imuon->Pt() < 10. ) { continue; }
    bool found_match = false;
    std::vector<LorentzV>::const_iterator ijet = reco.begin();
    std::vector<LorentzV>::const_iterator jjet = reco.end();
    for ( ; ijet != jjet; ++ijet ) {
      if ( fabs( ROOT::Math::VectorUtil::DeltaR(*ijet,*imuon) ) < 0.5 ) {
	if ( imuon->Pt() > 0.5 * ijet->Pt() ) { bad_muon_in_jet = true; }
	found_match = true;
      }
    }
  }

  // Order jets by pT
  std::sort( reco.begin(), reco.end(), SortByPt );
      
  // Check multiplicity and pT of leading and second jets
  bool jet_multiplicity = ( reco.size() >= 2 );
  bool leading_jet_pt   = ( reco.size() > 0 && reco[0].Pt() > pt1_threshold );
  bool second_jet_pt    = ( reco.size() > 1 && reco[1].Pt() > pt2_threshold );
  bool leading_jet_eta  = ( reco.size() > 0 && fabs(reco[0].Eta()) < maxLeadingJetEta_ );
    
  // Check if MHT/MET (baby jet cleaning) passes cut
  //if ( true ) baby_val = meff_reco > 0. ? ( mht_reco.Pt() - calo_met.Pt() ) / meff_reco  : 1000.; 
  bool pass_baby_cut = ( baby_val < babyCut_ );       
    
//   // Check if event falls within appropriate HT or Meff bin (last bin is inclusive)
//   correct_reco_bin = false;
//   double ht_lower = htBins_[ibin];
//   double ht_upper = ( (nbins-ibin) != 1 ? htBins_[ibin+1] : 10000. ); 
//   if ( inclusive_ ) { if ( var_reco > ht_lower ) { correct_reco_bin = true; } }
//   else { if ( var_reco > ht_lower && var_reco < ht_upper ) { correct_reco_bin = true; } }
    
//       std::cout << std::fixed << std::setprecision(0)
// 		<< "# " << ev.GetCurrentEntry()
// 		<< " e " << ev.GetEventNumber()
// 		<< " b " << ibin
// 		<< " ht " << htBins_[ibin]
// 		<< " low " << ht_lower
// 		<< " up " << ht_upper
// 		<< " v " << var_reco
// 		<< " j " << reco.size()
// 	//<< " nodd " << odd.size()
// 	//<< " correct_reco_bin " << correct_reco_bin
// 		<< std::endl;

//       std::cout << std::fixed
// 		<< " entry " << ev.GetCurrentEntry()
// 		<< " event " << ev.GetEventNumber()
// 		<< " ibin " << ibin
// 		<< " htBins_[ibin] " << htBins_[ibin]
// 		<< " ht_lower " << ht_lower
// 		<< " ht_upper " << ht_upper
// 		<< " var_reco " << var_reco
// 		<< " reco.size() " << reco.size()
// 		<< " nodd " << odd.size()
// 		<< " correct_reco_bin " << correct_reco_bin
// 		<< std::endl;
    
  // Check if event passes "dead ECAL" cut
  bool pass_dead_ecal = dead_ ? dead_->Process( ev, reco, baby_jets_for_dead_ecal ) : true;
  
  // Track Sum Pt over HT cut
  bool pass_pt_over_ht = passVertexSumPtOverHt( ev, ht_reco );
  
  // Min biased delta phi
  double min_bias_dphi = minBiasDeltaPhi( reco );
  bool pass_min_bias_dphi = ( min_bias_dphi > 0.5 );
  
  // Sum RecHit Pt cleaning cut
  bool pass_rechit = rechit_ ? rechit_->Process(ev) : true; 
    
  // Extract trigger prescale based on if AlphaT is above nominal threshold
  if ( at_reco >= alphaT_[aT_] ) { if ( !signal_.empty() ) prescale = trigger( ev, signal_[ibin] ); }
  else                           { if ( !monitor_.empty() ) prescale = trigger( ev, monitor_[ibin] ); }
    
  // Check if correct reco bin
  //   if ( correct_reco_bin ) { 
  pass_cntr = 1; 
      
  // Record number of jets 
  njets = reco.size();

  //       std::cout << " correct reco bin " << htBins_[ibin] << " " << var_reco << std::endl;
  //       std::cout << "[RaT::Process] Event Summary:" << std::endl
  // 		<< " Entry: " << ev.GetCurrentEntry() << std::endl
  // 		<< " Event: " << ev.GetEventNumber() << std::endl
  // 	//<< " Signal trigger prescale: " << signal
  // 	//<< " Monitor trigger prescale: " << monitor
  // 		<< " Njets: " << reco.size() << std::endl
  // 		<< " Binning variable: " << var_reco << std::endl
  // 		<< " HT: " << ht_reco << std::endl
  // 		<< " (HT bin: " << ibin << ")" << std::endl
  // 		<< " MHT: " << mht_reco.Pt() << std::endl
  // 		<< " Meff: " << meff_reco << std::endl
  // 		<< " AlphaT: " << at_reco << std::endl
  // 		<< " MET consistency: " << baby_val << std::endl
  // 		<< " x1: " << x1_reco << std::endl
  // 		<< " x2: " << x2_reco << std::endl
  // 		<< " njets: " << reco.size() << std::endl
  // 		<< " Njets>=2: " << jet_multiplicity << std::endl
  // 		<< " pT1>threshold: " << leading_jet_pt << std::endl
  // 		<< " pT2>threshold: " << second_jet_pt << std::endl
  // 		<< " eta1<threshold: " << leading_jet_eta << std::endl
  // 		<< " OddJet: " << odd_jet_veto << std::endl
  // 		<< " BadMuonInJet: " << bad_muon_in_jet << std::endl
  // 		<< " PassDeadECAL: " << pass_dead_ecal << std::endl
  // 		<< " PassMetConsistency: " << pass_baby_cut << std::endl;
  //       std::vector<LorentzV>::const_iterator ireco = reco.begin();
  //       std::vector<LorentzV>::const_iterator jreco = reco.end();
  //       for ( ; ireco != jreco; ++ireco ) {
  // 	std::cout << "  ET: " << ireco->Et() 
  // 		  << "  E: " << ireco->E() 
  // 		  << "  pT: " << ireco->Pt() 
  // 		  << " eta: " << ireco->eta()
  // 		  << " phi: " << ireco->phi() 
  // 		  << std::endl;
  //       }

  //       std::cout << " signal.size(): " << ( signal_.size() ? signal_[ibin].size() : 0 )
  //  		<< " monitor.size(): " << ( monitor_.size() ? monitor_[ibin].size() : 0 )
  //  		<< " prescale: "<< prescale
  //  		<< std::endl;
  
  do_toy = true;
      
  // If trigger fired, weight event and continue
  if ( prescale > 0. ) { 
    pass_cntr = 2; 
	
    // Pre-selection
    if ( jet_multiplicity ) {
      pass_cntr = 3; 
      if ( do_toy || leading_jet_pt ) {
	pass_cntr = 4; 
	if ( do_toy || second_jet_pt ) {
	  pass_cntr = 5; 
	  if ( do_toy || leading_jet_eta ) {
	    pass_cntr = 6; 
	    if ( do_toy || !odd_jet_veto ) { 
	      pass_cntr = 7; 
	      if ( do_toy || !bad_muon_in_jet ) {
		pass_cntr = 8; 

		// AlphaT histos
		if ( atHistos_ ) {
		  fill( reco.size(), hAlphaT_[0], at_reco, prescale*weight*reweight ); 
		  fill( reco.size(), hAlphaT_[ibin+1], at_reco, prescale*weight*reweight ); 
		  fill( reco.size(), hAlphaTvsScale_, var_reco, at_reco, prescale*weight*reweight ); 
		}

		// Dalitz plots
		if ( dalitzHistos_ ) {
		  fill( reco.size(), hDalitz_[0], x2_reco, x1_reco, prescale*weight*reweight ); 
		  fill( reco.size(), hDalitz_[ibin+1], x2_reco, x1_reco, prescale*weight*reweight ); 
		}
		    
		// AlphaT loop
		for ( uint iat = 0; iat < ( noQcd_ ? 1 : alphaT_.size() ); ++iat ) {
		      
		  // 		      std::cout << " test iat: " << iat
		  // 				<< " at_reco: " << at_reco
		  // 				<< " aT_: " << aT_
		  // 				<< " alphaT_[iat]: " << alphaT_[iat]
		  // 				<< std::endl;

		  // Check AlphaT is above threshold
		  if ( at_reco >= alphaT_[iat] ) { 
		    if ( iat == aT_ ) pass_cntr = 9; 

		    // Defines HT bin to be used in case of inclusive binning
		    double ht_binned = inclusive_ ? htBins_[ibin] + 1.e-3 : var_reco;
			
		    // Histograms after "bare" AlphaT cut
		    fill( reco.size(), hPassAlphaT_[iat], ht_binned, prescale*weight*reweight ); 
			
		    // Additional histograms 
			
		    if ( jetPtHistos_ ) {
		      for ( uint ijet = 0; ijet < common.size(); ++ijet ) {
			fill( ijet, hAllJetsPt_[0][iat], common[ijet]->Pt(), prescale*weight*reweight ); 
			fill( ijet, hAllJetsPt_[ibin+1][iat], common[ijet]->Pt(), prescale*weight*reweight ); 
		      }
		      for ( uint ijet = 0; ijet < reco.size(); ++ijet ) {
			fill( ijet, hRecoJetsPt_[0][iat], reco[ijet].Pt(), prescale*weight*reweight ); 
			fill( ijet, hRecoJetsPt_[ibin+1][iat], reco[ijet].Pt(), prescale*weight*reweight ); 
		      }
		      for ( uint ijet = 0; ijet < baby_jets.size(); ++ijet ) {
			fill( ijet, hBabyJetsPt_[0][iat], baby_jets[ijet].Pt(), prescale*weight*reweight ); 
			fill( ijet, hBabyJetsPt_[ibin+1][iat], baby_jets[ijet].Pt(), prescale*weight*reweight ); 
		      }
		    }
			
		    if ( vertexHistos_ ) {
		      fill( reco.size(), hNumVertex_[0][iat], nvertices, prescale*weight*reweight ); 
		      fill( reco.size(), hNumVertex_[ibin+1][iat], nvertices, prescale*weight*reweight ); 
		    }

		    if ( htHistos_ ) {
		      fill( reco.size(), hHtDistr_[0][iat], ht_reco, prescale*weight*reweight ); 
		      fill( reco.size(), hHtDistr_[ibin+1][iat], ht_reco, prescale*weight*reweight ); 
		    }

		    if ( meffHistos_ ) {
		      fill( reco.size(), hMeffDistr_[0][iat], meff_reco, prescale*weight*reweight ); 
		      fill( reco.size(), hMeffDistr_[ibin+1][iat], meff_reco, prescale*weight*reweight ); 
		    }

		    if ( mhtOverHtHistos_ ) {
		      fill( reco.size(), hMhtOverHtDistr_[0][iat], (ht_reco>0.?mht_reco.Pt()/ht_reco:0.), prescale*weight*reweight ); 
		      fill( reco.size(), hMhtOverHtDistr_[ibin+1][iat], (ht_reco>0.?mht_reco.Pt()/ht_reco:0.), prescale*weight*reweight ); 
		    }

		    if ( mhtOverMeffHistos_ ) {
		      fill( reco.size(), hMhtOverMeffDistr_[0][iat], (meff_reco>0.?mht_reco.Pt()/meff_reco:0.), prescale*weight*reweight ); 
		      fill( reco.size(), hMhtOverMeffDistr_[ibin+1][iat], (meff_reco>0.?mht_reco.Pt()/meff_reco:0.), prescale*weight*reweight ); 
		    }
			
		    if ( mhtHistos_ ) {
		      fill( reco.size(), hMhtDistr_[0][iat], mht_reco.Pt(), prescale*weight*reweight ); 
		      fill( reco.size(), hMhtDistr_[ibin+1][iat], mht_reco.Pt(), prescale*weight*reweight ); 
		    }
			
		    if ( multiHistos_ ) {
		      fill( reco.size(), hMultiplicity_[0][iat], reco.size(), prescale*weight*reweight ); 
		      fill( reco.size(), hMultiplicity_[ibin+1][iat], reco.size(), prescale*weight*reweight ); 
		      if ( iat == 0 ) hMultiVsScale_->Fill( var_reco, reco.size(), prescale*weight*reweight ); 
		    }
		    if ( minBiasDeltaPhiHistos_ ) {
		      fill( reco.size(), hMinBiasDeltaPhi_[0][iat], min_bias_dphi, prescale*weight*reweight ); 
		      fill( reco.size(), hMinBiasDeltaPhi_[ibin+1][iat], min_bias_dphi, prescale*weight*reweight ); 
		    }
			
		    // Histograms filled after cleaning cuts
		    bool ok = ( noCleaningInDenom_ && ( iat == 0 ) );
		    if ( pass_dead_ecal || ok ) { 
		      if ( iat == aT_ ) pass_cntr = 10; 
		      if ( !onlyFull_ ) fill( reco.size(), hPassDeadEcal_[iat], ht_binned, prescale*weight*reweight ); 
	  
		      // Additional histograms
		      if ( babyJetsHistos_ ) {
			fill( reco.size(), hBabyJets_[0][iat], baby_val, prescale*weight*reweight ); 
			fill( reco.size(), hBabyJets_[ibin+1][iat], baby_val, prescale*weight*reweight ); 
		      }

		      // Additional histograms
		      if ( babyJetsMhtHistos_ ) {
			fill( reco.size(), hBabyJetsMht_[0][iat], baby_mht.Pt(), prescale*weight*reweight ); 
			fill( reco.size(), hBabyJetsMht_[ibin+1][iat], baby_mht.Pt(), prescale*weight*reweight ); 
		      }

		      if ( pass_baby_cut || ok ) { 
			if ( iat == aT_ ) pass_cntr = 11; 
			if ( !onlyFull_ ) fill( reco.size(), hPassBaby_[iat], ht_binned, prescale*weight*reweight ); 

			if ( pass_pt_over_ht || ok ) { 
			  if ( iat == aT_ ) pass_cntr = 12; 
			  if ( !onlyFull_ ) fill( reco.size(), hPassTrackless_[iat], ht_binned, prescale*weight*reweight ); 
	      
			  if ( pass_rechit || ok ) { 
			    if ( iat == aT_ ) pass_cntr = 13; 
			    fill( reco.size(), hPassRecHit_[iat], ht_binned, prescale*weight*reweight ); 
		
			    if ( pass_min_bias_dphi || ok ) { 
			      if ( iat == aT_ ) pass_cntr = 14; 
			      if ( !onlyFull_ ) fill( reco.size(), hPassMinBiasDPhi_[iat], ht_binned, prescale*weight*reweight ); 
				  
			    } // MinBiasDPhi cut
			  } // RecHit cleaning cut
			} // SumVertexPtOverHt cut
		      } // MHT/MET cut
		    } // Dead ECAL cut
		  } // aT cut
		} // AlphaT loop
		  
		// 		  // Decide if event is interesting or not (-1 = no filter; >nbins = all bins; other = particular bin)
		// 		  if ( signal > 0 && 
		// 		       at_reco > alphaT_[aT_] && 
		// 		       pass_dead_ecal &&
		// 		       pass_baby_cut &&
		// 		       pass_pt_over_ht ) { 
		    
		// 		    if ( filter_ >= nbins || ibin == filter_ ) { 
		// 		      keep_event = true; 
		// 		      if ( verbose_ ) { 
		// 		    			std::cout << "[RaT::Process] Event Summary:" << std::endl
		// 		    				  << " Entry: " << ev.GetCurrentEntry() << std::endl
		// 		    				  << " Event: " << ev.GetEventNumber() << std::endl
		// 					  //<< " Signal trigger prescale: " << signal
		// 					  //<< " Monitor trigger prescale: " << monitor
		// 		    				  << " Njets: " << reco.size() << std::endl
		// 		    				  << " Binning variable: " << var_reco << std::endl
		// 		    				  << " HT: " << ht_reco << std::endl
		// 		    				  << " (HT bin: " << ibin << ")" << std::endl
		// 		    				  << " MHT: " << mht_reco.Pt() << std::endl
		// 		    				  << " Meff: " << meff_reco << std::endl
		// 		    				  << " AlphaT: " << at_reco << std::endl
		// 		    				  << " MET consistency: " << baby_val << std::endl
		// 		    				  << " x1: " << x1_reco << std::endl
		// 		    				  << " x2: " << x2_reco << std::endl
		// 		    				  << " njets: " << reco.size() << std::endl
		// 						  << " Njets>=2: " << jet_multiplicity << std::endl
		// 						  << " pT1>threshold: " << leading_jet_pt << std::endl
		// 						  << " pT2>threshold: " << second_jet_pt << std::endl
		// 						  << " eta1<threshold: " << leading_jet_eta << std::endl
		// 						  << " OddJet: " << odd_jet_veto << std::endl
		// 						  << " BadMuonInJet: " << bad_muon_in_jet << std::endl
		// 						  << " PassDeadECAL: " << pass_dead_ecal << std::endl
		// 						  << " PassMetConsistency: " << pass_baby_cut << std::endl;
		// 		    			std::vector<LorentzV>::const_iterator ireco = reco.begin();
		// 		    			std::vector<LorentzV>::const_iterator jreco = reco.end();
		// 		    			for ( ; ireco != jreco; ++ireco ) {
		// 		    			  std::cout << "  ET: " << ireco->Et() 
		// 		    				    << "  E: " << ireco->E() 
		// 		    				    << "  pT: " << ireco->Pt() 
		// 		    				    << " eta: " << ireco->eta()
		// 		    				    << " phi: " << ireco->phi() 
		// 		    				    << std::endl;
		// 		    			}
		// 		      }
		// 		    }
		// 		  }
      
		//       // Determine HT used to fill histograms
		//       double ht_binned = inclusive_ ? htBins_[ibin] + 1.e-3 : var_reco;
      
		//       // HT distributions
		//       for ( uint iat = 0; iat < ( noQcd_? 1 : alphaT_.size() ); ++iat ) {
	
		// 	// Check AlphaT is above threshold
		// 	bool pass_at = ( at_reco > alphaT_[iat] );
	
		// 	// Check if appropriate trigger fired
		// 	int prescale = -1;
		// 	if      ( iat == 0 && monitor > 0 ) { prescale = monitor; }
		// 	else if (  pass_at &&  signal > 0 ) { prescale =  signal; }
		// 	else if ( !pass_at && monitor > 0 ) { prescale = monitor; }
		// 	else                                { continue; }
	
		// 	// Adjust event weight by prescale
		// 	double w = weight;//*prescale;
	
		// 	if ( pass_at ) {
		// 	  fill( reco.size(), hPassAlphaT_[iat], ht_binned, w ); 
		// 	  bool ok = ( noCleaningInDenom_ && ( iat == 0 ) );
		// 	  if ( babyJetsHistos_ ) {
		// 	    fill( reco.size(), hBabyJets_[0][iat], baby_val, w ); 
		// 	    fill( reco.size(), hBabyJets_[ibin+1][iat], baby_val, w ); 
		// 	  }
		// 	  if ( pass_dead_ecal || ok ) { 
		// 	    fill( reco.size(), hPassDeadEcal_[iat], ht_binned, w ); 
		// 	    if ( pass_baby_cut || ok ) { 
		// 	      fill( reco.size(), hPassBaby_[iat], ht_binned, w ); 
		// 	      if ( pass_pt_over_ht || ok ) { 
		// 		fill( reco.size(), hPassTrackless_[iat], ht_binned, w ); 
		// 		if ( pass_min_bias_dphi || ok ) { 
		// 		  fill( reco.size(), hPassMinBiasDPhi_[iat], ht_binned, w ); 
		// 		} else {
		// 		  fill( reco.size(), hFailMinBiasDPhi_[iat], ht_binned, w ); 
		// 		}
		// 	      } else {
		// 		fill( reco.size(), hFailTrackless_[iat], ht_binned, w ); 
		// 		fill( reco.size(), hFailMinBiasDPhi_[iat], ht_binned, w ); 
		// 	      }
		// 	    } else {
		// 	      fill( reco.size(), hFailBaby_[iat], ht_binned, w ); 
		// 	      fill( reco.size(), hFailTrackless_[iat], ht_binned, w ); 
		// 	      fill( reco.size(), hFailMinBiasDPhi_[iat], ht_binned, w ); 
		// 	    }
		// 	  } else {
		// 	    fill( reco.size(), hFailDeadEcal_[iat], ht_binned, w ); 
		// 	    fill( reco.size(), hFailBaby_[iat], ht_binned, w ); 
		// 	    fill( reco.size(), hFailTrackless_[iat], ht_binned, w ); 
		// 	    fill( reco.size(), hFailMinBiasDPhi_[iat], ht_binned, w ); 
		// 	  }
		// 	} else { 
		// 	  fill( reco.size(), hFailAlphaT_[iat], ht_binned, w ); 
		// 	  fill( reco.size(), hFailDeadEcal_[iat], ht_binned, w ); 
		// 	  fill( reco.size(), hFailBaby_[iat], ht_binned, w ); 
		// 	  fill( reco.size(), hFailTrackless_[iat], ht_binned, w ); 
		// 	  fill( reco.size(), hFailMinBiasDPhi_[iat], ht_binned, w ); 
		// 	}
	
		//       } // iat
		    
	      } // bad muon in jet
	    } // odd jet veto
	  } // leading jet eta
	} // second jet pt
      } // leading jet pt
    } // jet multiplicity
  } else { prescale = 1.; } // Trigger fired    

  // -------------------- Debug --------------------

  //     if ( true && correct_reco_bin ) {
  // //       //if ( true ) {
  //       std::cout << "[RaT::Process] RECO info:" << std::endl
  // 		<< " Entry: " << ev.GetCurrentEntry() << std::endl
  // 		<< " Event: " << ev.GetEventNumber() << std::endl
  // 		<< " Njets: " << reco.size() << std::endl
  // 		<< " HT: " << ht_reco << std::endl
  // 		<< " (HT bin: " << ibin << ")" << std::endl
  // 		<< " MHT: " << mht_reco.Pt() << std::endl
  // 		<< " AlphaT: " << at_reco << std::endl
  // 		<< " Meff: " << meff_reco << std::endl
  // 		<< " MET consistency: " << baby_val << std::endl
  // 		<< " x1: " << x1_reco << std::endl
  // 		<< " x2: " << x2_reco << std::endl
  // 		<< " Njets>=2: " << jet_multiplicity << std::endl
  // 		<< " pT1>threshold: " << leading_jet_pt << std::endl
  // 		<< " pT2>threshold: " << second_jet_pt << std::endl
  // 		<< " eta1<threshold: " << leading_jet_eta << std::endl
  // 		<< " OddJet: " << odd_jet_veto << std::endl
  // 		<< " BadMuonInJet: " << bad_muon_in_jet << std::endl
  // 		<< " PassDeadECAL: " << pass_dead_ecal << std::endl
  // 		<< " PassMetConsistency: " << pass_baby_cut << std::endl;
  //     }
    
  //     if ( correct_reco_bin ) {
  //       if ( !jet_multiplicity ||
  // 	   !leading_jet_pt ||
  // 	   !second_jet_pt ||
  // 	   !leading_jet_eta ||
  // 	   odd_jet_veto || 
  // 	   bad_muon_in_jet ||
  // 	   at_reco < alphaT_[aT_] || 
  // 	   !pass_dead_ecal ||
  // 	   !pass_baby_cut ||
  // 	   !pass_pt_over_ht ) { 
  // 	int signal = trigger( ev, signal_[ibin] );
  // 	int monitor = trigger( ev, monitor_[ibin] );
  // 	std::cout << "[RaT::Process] Event Summary:" << std::endl
  // 		  << " Entry: " << ev.GetCurrentEntry() << std::endl
  // 		  << " Event: " << ev.GetEventNumber() << std::endl
  // 		  << " Signal trigger prescale: " << signal
  // 		  << " Monitor trigger prescale: " << monitor
  // 		  << " Njets: " << reco.size() << std::endl
  // 		  << " HT: " << ht_reco << std::endl
  // 		  << " (HT bin: " << ibin << ")" << std::endl
  // 		  << " MHT: " << mht_reco.Pt() << std::endl
  // 		  << " AlphaT: " << at_reco << std::endl
  // 		  << " Meff: " << meff_reco << std::endl
  // 		  << " MET consistency: " << baby_val << std::endl
  // 		  << " x1: " << x1_reco << std::endl
  // 		  << " x2: " << x2_reco << std::endl
  // 		  << " njets: " << reco.size() << std::endl;
  // 	std::vector<LorentzV>::const_iterator ireco = reco.begin();
  // 	std::vector<LorentzV>::const_iterator jreco = reco.end();
  // 	for ( ; ireco != jreco; ++ireco ) {
  // 	  std::cout << "  ET: " << ireco->Et() 
  // 		    << "  E: " << ireco->E() 
  // 		    << "  pT: " << ireco->Pt() 
  // 		    << " eta: " << ireco->eta()
  // 		    << " phi: " << ireco->phi() 
  // 		    << std::endl;
  // 	}
  // 	std::cout << jet_multiplicity << " "
  // 		  << leading_jet_pt << " "
  // 		  << second_jet_pt << " "
  // 		  << leading_jet_eta << " "
  // 		  << !odd_jet_veto << " " 
  // 		  << !bad_muon_in_jet << " "
  // 		  << ( at_reco > alphaT_[aT_] ) << " " 
  // 		  << pass_dead_ecal << " "
  // 		  << pass_baby_cut << " "
  // 		  << pass_pt_over_ht << " "
  // 		  << std::endl;
  //       }
  //     }
    
  // } // nBins
  
  // Cut flow histograms
  if ( cutFlowHistos_ ) {
    if ( njets > (int)nMax_ ) { njets = nMax_; }
    for ( int ipass = 0; ipass <= pass_cntr; ++ipass ) {
      hCutFlow_[0][0]->Fill( ipass*1., prescale*weight*reweight ); 
      hCutFlow_[ibin+1][0]->Fill( ipass*1., prescale*weight*reweight ); 
      hCutFlow_[0][njets]->Fill( ipass*1., prescale*weight*reweight ); 
      hCutFlow_[ibin+1][njets]->Fill( ipass*1., prescale*weight*reweight ); 
    }
  }
  
  return keep_event;
  
}

// -----------------------------------------------------------------------------
//
void RaT::calcDalitzVars( const std::vector<LorentzV>& jets, 
				 const std::vector<bool>& pseudo,
				 const LorentzV& mht, 
				 double& x1, 
				 double& x2 ) {
  
  // Construct pseudo di-jets
  LorentzV mht_massless(0.,0.,0.,0.);
  std::vector<LorentzV> dijets(2,LorentzV(0.,0.,0.,0.));
  for ( unsigned int i = 0; i < jets.size(); ++i ) {
    mht_massless -= massless(jets[i]);
//     std::cout << " i: " << i
// 	      << " massive ET: " << jets[i].Et()
// 	      << " pT: " << jets[i].Pt()
// 	      << " massless ET: " << massless(jets[i]).Et()
// 	      << " pT: " << massless(jets[i]).Pt()
// 	      << std::endl;
    if ( pseudo[i] ) { dijets[0] += massless(jets[i]); }
    else             { dijets[1] += massless(jets[i]); }
  }

  //std::sort( dijets.begin(), dijets.end(), SortByEt );

  // Calculate x1, x2
  x1 = ( norm_ * dijets[0].Pt() ) / ( dijets[0].Pt() + dijets[1].Pt() + mht_massless.Pt() );
  x2 = ( norm_ * dijets[1].Pt() ) / ( dijets[0].Pt() + dijets[1].Pt() + mht_massless.Pt() );

  if ( x2 > x1 ) { double tmp = x2; x2 = x1; x1 = tmp; }

//   std::cout << " ET1: " << dijets[0].Et()
// 	    << " pT1: " << dijets[0].Pt()
// 	    << " ET2: " << dijets[1].Et()
// 	    << " pT2: " << dijets[1].Pt()
// 	    << " MHT: " << mht_massless.Pt()
// 	    << " HT: " << ( dijets[0].Et() + dijets[1].Et() )
// 	    << " Meff: " << ( dijets[0].Et() + dijets[1].Et() + mht_massless.Pt() )
// 	    << " x1: " << x1
// 	    << " x2: " << x2
// 	    << std::endl;
  
}

// // -----------------------------------------------------------------------------
// //
// void RaT::fill( uint multiplicity,
// 		       double alpha_t,
// 		       double at_cut,
// 		       std::vector<TH1D*>& his,
// 		       double val,
// 		       double weight ) {
  
//   // Events passing AlphaT
//   if ( alpha_t >= at_cut ) {
//     if ( !his.empty() && 
// 	 multiplicity >= nMin_ ) { 
//       if ( his[0] ) his[0]->Fill( val, weight ); 
//     }
//     if ( multiplicity >= nMin_ && 
// 	 multiplicity <= nMax_ &&
// 	 multiplicity < his.size() ) {
//       if ( his[multiplicity] ) his[multiplicity]->Fill( val, weight ); 
//     }
//   }

// }

// -----------------------------------------------------------------------------
//
void RaT::fill( uint multiplicity,
		std::vector<TH1D*>& his,
		double valx,
		double weight ) {
  
  if ( his.empty() ) { return; }
  //if ( multiplicity < nMin_ ) { return; }
  
  if ( his[0] ) his[0]->Fill( valx, weight ); 
  
  if ( his.size() == 1 ) { return; }
  //if ( multiplicity >= his.size() ) { return; }

  if ( multiplicity < nMax_ ) { 
    if ( his[multiplicity] ) his[multiplicity]->Fill( valx, weight ); 
  } else { 
    if ( his[nMax_] ) his[nMax_]->Fill( valx, weight ); 
  }
  
}

// -----------------------------------------------------------------------------
//
void RaT::fill( uint multiplicity,
		std::vector<TH2D*>& his,
		double valx,
		double valy,
		double weight ) {
  
  if ( his.empty() ) { return; }
  //if ( multiplicity < nMin_ ) { return; }
  
  if ( his[0] ) his[0]->Fill( valx, valy, weight ); 
  
  if ( his.size() == 1 ) { return; }
  //if ( multiplicity >= his.size() ) { return; }
  
  if ( multiplicity < nMax_ ) { 
    if ( his[multiplicity] ) his[multiplicity]->Fill( valx, valy, weight ); 
  } else { 
    if ( his[nMax_] ) his[nMax_]->Fill( valx, valy, weight ); 
  }

//   if ( multiplicity < nMax_ ) { 
//     if ( his[multiplicity] ) his[multiplicity]->Fill( valx, valy, weight ); 
//   } else  { 
//     if ( his[nMax_] ) his[nMax_]->Fill( valx, valy, weight ); 
//   }

}

// -----------------------------------------------------------------------------
//
void RaT::fill2d( uint multiplicity,
			 std::vector<TH2D*>& his,
			 double x, 
			 double y,
			 double weight ) {
  
  if ( !his.empty() && 
       multiplicity >= nMin_ ) { 
    if ( his[0] ) { his[0]->Fill( x, y, weight ); }
  }
  if ( multiplicity >= nMin_ && 
       multiplicity <= nMax_ &&
       multiplicity < his.size() ) { 
    if ( his[multiplicity] ) { his[multiplicity]->Fill( x, y, weight ); }
  }

}

// -----------------------------------------------------------------------------
//
void RaT::Start( Event::Data& ev ) {
  
  // Top-level directory
  initDir( ev.OutputFile(), dirName_.c_str() );

  try {

    ev.pthat(); 
    
    std::vector<std::string> var;
    var.push_back("N_{jets}");
    var.push_back("H_{T} (GeV)");
    var.push_back("#DeltaH_{T} (GeV)");
    var.push_back("H_{T}^{miss} (GeV)");
    var.push_back("#alpha_{T}");
    var.push_back("M_{eff} (GeV)");
    var.push_back("E_{T}^{jet,min} (GeV)");
    var.push_back("E_{T}^{jet,max} (GeV)");
    var.push_back("#hat{E_{T}^{jet}} (GeV)");
    
    std::vector<double> range;
    range.resize( var.size(), 1000. );
    range[0] = 10.;
    range[1] = 1000.;
    range[2] = 500.;
    range[3] = 200.;
    range[4] = 1.;
    range[5] = 1000.;
    range[6] = 500.;
    range[7] = 500.;
    range[8] = 500.;
    
    if ( genHistos_ ) {

      hVarVsScale_.resize( var.size(), vTH2D() );
      for ( uint i = 0; i < var.size(); ++i ) {
	std::stringstream ss; ss << "hVarVsScale_" << i;
	std::stringstream sss; sss << ";2.#hat{p_{T}} (GeV);" << var[i]; 
	BookHistArray( hVarVsScale_[i],
		       ss.str().c_str(),
		       sss.str().c_str(),
		       100,0.,1000.,
		       100,0.,range[i],
		       nMax_+1, 0, 1, true );
      }
      
      hVarOverScaleVsJetPt_.resize( var.size(), vTH2D() );
      for ( uint i = 0; i < var.size(); ++i ) {
	std::stringstream ss; ss << "VarOverScaleVsJetPt_" << i;
	std::stringstream sss; sss << ";E_{T}^{jet,min} (GeV);" << var[i] << " / 2.#hat{p_{T}} (GeV)"; 
	BookHistArray( hVarOverScaleVsJetPt_[i],
		       ss.str().c_str(),
		       sss.str().c_str(),
		       100,0.,500.,
		       100,0.,2.*range[i]/1000,
		       nMax_+1, 0, 1, true );
      }

    }
    
    BookHistArray( hGenPtHat_,
		   "GenPtHat",
		   ";#hat{p_{T}} [GeV];", 
		   400,0.,2000.,
		   1, 0, 1, true );

//     BookHistArray( hGenPdgId_,
// 		   "GenPdgId",
// 		   ";Code;", 
// 		   10001,-0.5,10000.5,
// 		   1, 0, 1, true );

//     BookHistArray( hGenStatus_,
// 		   "GenStatus",
// 		   ";Code;", 
// 		   11,-0.5,10.5,
// 		   1, 0, 1, true );

    BookHistArray( hGenNuPt_,
		   "GenNuPt",
		   ";p_{T}^{#nu} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

//     BookHistArray( hGenNuPtMax_,
// 		   "GenNuPtMax",
// 		   ";p_{T}^{max,#nu} (GeV);", 
// 		   50,0.,500.,
// 		   1, 0, 1, true );

    BookHistArray( hGenNuMet_,
		   "GenNuMet",
		   ";E_{T}^{miss,#nu} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

    BookHistArray( hGenMuMet_,
		   "GenMuMet",
		   ";E_{T}^{miss,#mu} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

    BookHistArray( hGenElMet_,
		   "GenElMet",
		   ";E_{T}^{miss,e} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

    BookHistArray( hGenPhMet_,
		   "GenPhMet",
		   ";E_{T}^{miss,#gamma} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

    BookHistArray( hGenMet_,
		   "GenMet",
		   ";E_{T}^{miss} (GeV);", 
		   50,0.,500.,
		   1, 0, 1, true );

    BookHistArray( hGenJetMht_,
		   "GenJetMht",
		   ";H_{T}^{miss} (GeV);", 
		   50,0.,500.,
		   nMax_+1, 0, 1, true );
    
//     BookHistArray( hGenMetVsGenNuPtMax_,
// 		   "GenMetVsGenNuPtMax",
// 		   ";p_{T}^{max,#nu} (GeV);E_{T}^{miss} (GeV)", 
// 		   50,0.,500.,
// 		   50,0.,500.,
// 		   1, 0, 1, true );

    BookHistArray( hGenMetVsGenNuMet_,
		   "GenMetVsGenNuMet",
		   ";E_{T}^{miss,#nu} (GeV);E_{T}^{miss} (GeV)", 
		   50,0.,500.,
		   50,0.,500.,
		   1, 0, 1, true );
    
    BookHistArray( hGenJetMhtVsGenNuMet_,
 		   "GenJetMhtVsGenNuMet",
 		   ";E_{T}^{miss,#nu} (GeV);H_{T}^{miss} (GeV)", 
 		   50,0.,500.,
 		   50,0.,500.,
 		   1, 0, 1, true );

    BookHistArray( hGenJetMhtVsGenMuMet_,
 		   "GenJetMhtVsGenMuMet",
 		   ";E_{T}^{miss,#mu} (GeV);H_{T}^{miss} (GeV)", 
 		   50,0.,500.,
 		   50,0.,500.,
 		   1, 0, 1, true );

    BookHistArray( hGenJetMhtVsGenElMet_,
 		   "GenJetMhtVsGenElMet",
 		   ";E_{T}^{miss,e} (GeV);H_{T}^{miss} (GeV)", 
 		   50,0.,500.,
 		   50,0.,500.,
 		   1, 0, 1, true );

    BookHistArray( hGenJetMhtVsGenPhMet_,
 		   "GenJetMhtVsGenPhMet",
 		   ";E_{T}^{miss,#gamma} (GeV);H_{T}^{miss} (GeV)", 
 		   50,0.,500.,
 		   50,0.,500.,
 		   1, 0, 1, true );
    
  } catch (...){}
  if ( onlyGenPtHat_ ) { return; }
  
  try {
    if ( ev.SMSvalid.enabled() && ev.SMSvalid() ) { 
      BookHistArray( hSMS_,
		     "SMS",
		     "SMS;m_{gluino} (GeV);m_{LSP} (GeV)", 
		     22,100.,1200.,
		     44,50.,1150.,
		     1, 0, 1, true );
    }
  } catch (...){}
  
  if ( cutFlowHistos_ ) {

    std::vector<std::string> cuts;
    cuts.push_back("PreSelection");
    //cuts.push_back("MhtAbove100GeV");
    cuts.push_back("UsedInHtBin");
    cuts.push_back("TriggerFired");
    cuts.push_back("JetMultiplicity");
    cuts.push_back("LeadingJetPt");
    cuts.push_back("SecondJetPt");
    cuts.push_back("LeadingJetEta");
    cuts.push_back("OddJetVeto");
    cuts.push_back("BadMuonInJet");
    cuts.push_back("AlphaT");
    cuts.push_back("DeadEcal");
    cuts.push_back("MhtOverMet");
    cuts.push_back("SumVertexPtOverHt");
    cuts.push_back("RecHitCleaning");
    cuts.push_back("MinBiasDPhi");

    std::vector<double> ybins;
    for ( uint ii = 0; ii < cuts.size(); ++ii ) { ybins.push_back(-0.5+ii*1.); }
    
    hCutFlow_.resize( htNbins_+1, vTH1D() );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      std::stringstream ss;
      ss << "HtCutFlow_" << ht(ii);
      BookHistArray( hCutFlow_[ii], 
		     ss.str(),
		     ";Cut;Events passing", 
		     15,-0.5,14.5,
		     //cuts.size()-1, &(cuts.front()),
		     nMax_+1, 0, 1, true );
    }
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj <= nMax_; ++jj ) { 
 	for ( uint kk = 0; kk < cuts.size(); ++kk ) { 
 	  hCutFlow_[ii][jj]->GetXaxis()->SetBinLabel(kk+1,TString(cuts[kk])); 
 	}
      }
    }

  }
  
  if ( jetPtHistos_ ) {

    hAllJetsPt_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "JetsAllPt_" << ht(ii) << "_" << at(jj);
	BookHistArray( hAllJetsPt_[ii][jj], 
		       ss.str(),
		       ";P_{T}^{all};", 
		       500, 0., 1000., 
		       nMax_+1, 0, 1, true );
      }
    }

    hRecoJetsPt_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "JetsRecoPt_" << ht(ii) << "_" << at(jj);
	BookHistArray( hRecoJetsPt_[ii][jj], 
		       ss.str(),
		       ";P_{T}^{jet};", 
		       500, 0., 1000., 
		       nMax_+1, 0, 1, true );
      }
    }

    hBabyJetsPt_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "JetsBabyPt_" << ht(ii) << "_" << at(jj);
	BookHistArray( hBabyJetsPt_[ii][jj], 
		       ss.str(),
		       ";P_{T}^{baby};", 
		       500, 0., 1000., 
		       nMax_+1, 0, 1, true );
      }
    }

  }
  
  if ( vertexHistos_ ) {
    hNumVertex_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "NumVertex_" << ht(ii) << "_" << at(jj);
	BookHistArray( hNumVertex_[ii][jj], 
		       ss.str(),
		       ";N_{vertex};", 
		       51, -0.5, 50.5, 
		       nMax_+1, 0, 1, true );
      }
    }
  }

  if ( atHistos_ ) {

    hAlphaT_.resize( htNbins_+1, vTH1D() );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      std::stringstream ss;
      ss << "AlphaT_" << ht(ii);
      BookHistArray( hAlphaT_[ii], 
		     ss.str(),
		     ";#alpha_{T};", 
		     1000, 0., 1., 
		     nMax_+1, 0, 1, true );
    }

    double low = 1.*int( useMeff_ ? htXlow_ : htXlow_ + htPt3Bins_[0] );
    double high = 1.*int( useMeff_ ? htXhigh_ : htXhigh_ + htPt3Bins_[htNbins_] );
    int nbin = int(high - low);
    BookHistArray( hAlphaTvsScale_,
		   "AlphaTvsScale",
		   useMeff_?";M_{eff} (GeV);#alpha_{T}":";HT (GeV);#alpha_{T}", 
		   nbin,low,high,
		   1000,0.,1.,
		   nMax_+1, 0, 1, true );

  }
  
  if ( dalitzHistos_ ) {
    hDalitz_.resize( htNbins_+1, vTH2D() );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      std::stringstream ss;
      ss << "Dalitz_" << ht(ii);
      BookHistArray( hDalitz_[ii], 
		     ss.str(),
		     ";x_{2};x_{1};", 
		     100, 0., 1., 
		     50, 0.5, 1., 
		     nMax_+1, 0, 1, true );
    }
  }
  
  if ( multiHistos_ ) {
    
    hMultiplicity_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "Multiplicity_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMultiplicity_[ii][jj], 
		       ss.str(),
		       ";N_{jet};", 
		       51, -0.5, 50.5, 
		       1, 0, 1, true );
      }
    }
    
    double low = 1.*int( useMeff_ ? htXlow_ : htXlow_ + htPt3Bins_[0] );
    double high = 1.*int( useMeff_ ? htXhigh_ : htXhigh_ + htPt3Bins_[htNbins_] );
    int nbin = int(high - low);
    hMultiVsScale_ = new TH2D( "MultiVsScale",
			       (useMeff_?";M_{eff} (GeV);N_{jet}":";HT (GeV);N_{jet}"), 
			       nbin,low,high,
			       51, -0.5, 50.5 );
    hMultiVsScale_->Sumw2();
    
  }
  
  if ( htHistos_ ) {

    double low = 1.*int( useMeff_ ? htXlow_ - htPt3Bins_[0] : htXlow_ );
    double high = 1.*int( useMeff_ ? htXhigh_ - htPt3Bins_[htNbins_] : htXhigh_ );
    int nbin = int(high - low);

    hHtDistr_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "HtDistr_" << ht(ii) << "_" << at(jj);
	BookHistArray( hHtDistr_[ii][jj],
		       ss.str(),
		       ";HT (GeV);", 
		       nbin, low, high,
		       nMax_+1, 0, 1, true );
      }
    }

  }

  if ( meffHistos_ ) {

    double low = 1.*int( useMeff_ ? htXlow_ : htXlow_ + htPt3Bins_[0] );
    double high = 1.*int( useMeff_ ? htXhigh_ : htXhigh_ + htPt3Bins_[htNbins_] );
    int nbin = int(high - low);

    hMeffDistr_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "MeffDistr_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMeffDistr_[ii][jj],
		       ss.str(),
		       ";M_{eff} (GeV);",
		       nbin, low, high,
		       nMax_+1, 0, 1, true );
      }
    }

  }
  
  if ( mhtHistos_ ) {
    hMhtDistr_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "MhtDistr_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMhtDistr_[ii][jj],
		       ss.str(),
		       ";MHT (GeV);", 
		       500, 0., 1000., 
		       nMax_+1, 0, 1, true );
      }
    }
  }

  if ( mhtOverHtHistos_ ) {
    hMhtOverHtDistr_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "MhtOverHtDistr_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMhtOverHtDistr_[ii][jj],
		       ss.str(),
		       ";MHT/HT (GeV);", 
		       500, 0., 1., 
		       nMax_+1, 0, 1, true );
      }
    }
  }

  if ( mhtOverMeffHistos_ ) {
    hMhtOverMeffDistr_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "MhtOverMeffDistr_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMhtOverMeffDistr_[ii][jj],
		       ss.str(),
		       ";MHT/Meff (GeV);", 
		       500, 0., 1., 
		       nMax_+1, 0, 1, true );
      }
    }
  }
  
  if ( minBiasDeltaPhiHistos_ ) {
    hMinBiasDeltaPhi_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "MinBiasDeltaPhi_" << ht(ii) << "_" << at(jj);
	BookHistArray( hMinBiasDeltaPhi_[ii][jj], 
		       ss.str(),
		       ";#Delta#phi^{*}_{min} [radians];", 
		       320, 0., 3.2,
		       nMax_+1, 0, 1, true );
      }
    }
  }
  
  if ( babyJetsHistos_ ) {
    hBabyJets_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "BabyJets_" << ht(ii) << "_" << at(jj);
	BookHistArray( hBabyJets_[ii][jj],
		       ss.str(),
		       ";Baby jet cleaning variable;", 
		       500,0.,10.,
		       nMax_+1, 0, 1, true );
      }
    }
  }

  if ( babyJetsMhtHistos_ ) {
    hBabyJetsMht_.resize( htNbins_+1, vvTH1D( alphaT_.size(), vTH1D() ) );
    for ( uint ii = 0; ii <= htNbins_; ++ii ) { 
      for ( uint jj = 0; jj < alphaT_.size(); ++jj ) { 
	std::stringstream ss;
	ss << "BabyJetsMht_" << ht(ii) << "_" << at(jj);
	BookHistArray( hBabyJetsMht_[ii][jj],
		       ss.str(),
		       ";Baby jets MHT;", 
		       500,0.,1000.,
		       nMax_+1, 0, 1, true );
      }
    }
  }
  
  hPassAlphaT_.resize( alphaT_.size(), vTH1D() );
  for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
    std::stringstream ss;
    ss << "HtAfterAlphaT_" << at(ii);
    BookHistArray( hPassAlphaT_[ii], 
		   ss.str(),
		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		   htNbins_, &htBins_.front(), 
		   nMax_+1, 0, 1, true );
  }
  
  if ( !onlyFull_ ) {

    hPassDeadEcal_.resize( alphaT_.size(), vTH1D() );
    for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
      std::stringstream ss;
      ss << "HtAfterDeadEcal_" << at(ii);
      BookHistArray( hPassDeadEcal_[ii], 
		     ss.str(),
		     useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		     htNbins_, &htBins_.front(), 
		     nMax_+1, 0, 1, true );
    }
  
    hPassBaby_.resize( alphaT_.size(), vTH1D() );
    for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
      std::stringstream ss;
      ss << "HtAfterBaby_" << at(ii);
      BookHistArray( hPassBaby_[ii], 
		     ss.str(),
		     useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		     htNbins_, &htBins_.front(), 
		     nMax_+1, 0, 1, true );
    }
  
    hPassTrackless_.resize( alphaT_.size(), vTH1D() );
    for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
      std::stringstream ss;
      ss << "HtAfterTrackless_" << at(ii);
      BookHistArray( hPassTrackless_[ii], 
		     ss.str(),
		     useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		     htNbins_, &htBins_.front(), 
		     nMax_+1, 0, 1, true );
    }

    hPassMinBiasDPhi_.resize( alphaT_.size(), vTH1D() );
    for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
      std::stringstream ss;
      ss << "HtAfterMinBiasDPhi_" << at(ii);
      BookHistArray( hPassMinBiasDPhi_[ii], 
		     ss.str(),
		     useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		     htNbins_, &htBins_.front(), 
		     nMax_+1, 0, 1, true );
    }

  }

  hPassRecHit_.resize( alphaT_.size(), vTH1D() );
  for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
    std::stringstream ss;
    ss << "HtAfterRecHit_" << at(ii);
    BookHistArray( hPassRecHit_[ii], 
		   ss.str(),
		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
		   htNbins_, &htBins_.front(), 
		   nMax_+1, 0, 1, true );
  }

//   hFailAlphaT_.resize( alphaT_.size(), vTH1D() );
//   for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
//     std::stringstream ss;
//     ss << "HtFailingAlphaT_" << at(ii);
//     BookHistArray( hFailAlphaT_[ii], 
// 		   ss.str(),
// 		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
// 		   htNbins_, &htBins_.front(), 
// 		   nMax_+1, 0, 1, true );
//   }
  
//   hFailDeadEcal_.resize( alphaT_.size(), vTH1D() );
//   for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
//     std::stringstream ss;
//     ss << "HtFailingDeadEcal_" << at(ii);
//     BookHistArray( hFailDeadEcal_[ii], 
// 		   ss.str(),
// 		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
// 		   htNbins_, &htBins_.front(), 
// 		   nMax_+1, 0, 1, true );
//   }
  
//   hFailBaby_.resize( alphaT_.size(), vTH1D() );
//   for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
//     std::stringstream ss;
//     ss << "HtFailingBaby_" << at(ii);
//     BookHistArray( hFailBaby_[ii], 
// 		   ss.str(),
// 		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
// 		   htNbins_, &htBins_.front(), 
// 		   nMax_+1, 0, 1, true );
//   }
  
//   hFailTrackless_.resize( alphaT_.size(), vTH1D() );
//   for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
//     std::stringstream ss;
//     ss << "HtFailingTrackless_" << at(ii);
//     BookHistArray( hFailTrackless_[ii], 
// 		   ss.str(),
// 		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
// 		   htNbins_, &htBins_.front(), 
// 		   nMax_+1, 0, 1, true );
//   }
  
//   hFailMinBiasDPhi_.resize( alphaT_.size(), vTH1D() );
//   for ( uint ii = 0; ii < alphaT_.size(); ++ii ) { 
//     std::stringstream ss;
//     ss << "HtFailingMinBiasDPhi_" << at(ii);
//     BookHistArray( hFailMinBiasDPhi_[ii], 
// 		   ss.str(),
// 		   useMeff_?";M_{eff} (GeV);":";HT (GeV);", 
// 		   htNbins_, &htBins_.front(), 
// 		   nMax_+1, 0, 1, true );
//   }
  
}

// -----------------------------------------------------------------------------
//
std::string RaT::ht( int ii ) {
  std::stringstream ss;
  ss << ( useMeff_ ? "Meff" : "HT" );
  if ( ii == 0 ) { ss << "0"; }
  else { ss << (int(10.*htBins_[ii-1])/10.); }
  return ss.str();
}

// -----------------------------------------------------------------------------
//
std::string RaT::at( int ii ) {
  std::stringstream ss;
  ss << "aT" << alphaT_[ii]; 
  return ss.str();
}

// -----------------------------------------------------------------------------
//
Double_t RaT::DeadECALDR(TString deadECALfile,float jetphi,float jeteta, int nBad){
  // cout << " hi ho " << deadECALfile << endl;
  TLorentzVector testjetVec(0,0,0,0);
  double DRmin = 100;
  testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);

  //cout << " in dead ecal " << endl;
  ifstream myfile(deadECALfile);
  if(!myfile.good()) cout << "file is not there " << endl;
  if(myfile.is_open()){

    while(!myfile.eof()){

      float phi,eta;
      int iEta,iPhi,nBadCells;
      myfile>>eta;
      myfile>>phi;
      myfile>>iEta;
      myfile>>iPhi;
      myfile>>nBadCells;
      // cout <<eta<< " "<< phi<<endl;
      if(nBadCells > nBad){
	TLorentzVector testVec(0,0,0,0);
	testVec.SetPtEtaPhiE(100,eta,phi,100);
	float DR = fabs(ROOT::Math::VectorUtil::DeltaR(testVec,testjetVec));
	if(DR < DRmin) DRmin = DR;
      }
    }
   
    myfile.close();
  } 
  return DRmin;

}

// -----------------------------------------------------------------------------
//
bool RaT::deadECALCut( Event::Data& ev,
			      std::vector<LorentzV>& jets,
			      LorentzV met,
			      std::vector<LorentzV>& baby_jets ) {
  
  double biasedDPhi = 100;

  float deadECALDR = 10;

  LorentzV loweredMHT = met;
  for(std::vector<LorentzV>::const_iterator iM = baby_jets.begin();iM != baby_jets.end();++iM){
    if( (iM)->Pt() > minJetPtCut_)
      loweredMHT -= (*iM);
  }

  for( std::vector<LorentzV>::const_iterator i = jets.begin();
       i != jets.end();
       ++i ){

    float newBiasDPhi = fabs(ROOT::Math::VectorUtil::DeltaPhi(*i,loweredMHT + (*i))) ;

    if(newBiasDPhi < biasedDPhi){
      biasedDPhi = newBiasDPhi;
      if (useFile_) { deadECALDR = DeadECALDR_File(deadECALfile_,(i)->Phi(),(i)->Eta(),nBadCells_); }
      else {
	try{deadECALDR = DeadECALDR( ev,(i)->Phi(),(i)->Eta(),nBadCells_);}
	catch(...){
	  deadECALDR = DeadECALDR_File(deadECALfile_,(i)->Phi(),(i)->Eta(),nBadCells_);
        }
      }
    }
  }

  for( std::vector<LorentzV>::const_iterator iI = baby_jets.begin(); iI != baby_jets.end();
       ++iI) {
    if((iI)->Pt() > minJetPtCut_){
      float newBiasDPhi_2 = fabs(ROOT::Math::VectorUtil::DeltaPhi(*iI, loweredMHT + (*iI) )) ;
      if(newBiasDPhi_2 < biasedDPhi){
	biasedDPhi = newBiasDPhi_2;
	if (useFile_) { deadECALDR = DeadECALDR_File(deadECALfile_,(iI)->Phi(),(iI)->Eta(),nBadCells_); }
	else {
	  try{deadECALDR = DeadECALDR(ev,(iI)->Phi(),(iI)->Eta(),nBadCells_);}
	  catch(...){
	    deadECALDR = DeadECALDR_File(deadECALfile_,(iI)->Phi(),(iI)->Eta(),nBadCells_);
	  } 
	} 
      }
    }
  }
  
  if( biasedDPhi < minBiasDeltaPhiCut_ ){
    if(deadECALDR < deadEcalRegionDrCut_)return false;
  }
  
  return true;
  
}

  // -----------------------------------------------------------------------------
  //
  Double_t RaT::DeadECALDR( Event::Data& ev,float jetphi,float jeteta, int nBad){
    double DRmin = 100;
    TLorentzVector testjetVec(0,0,0,0);
    TLorentzVector testVec(0,0,0,0);
    int idx = 0;
 
    testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);
    for(std::vector<PolarLorentzV>::const_iterator ii=ev.ecalDeadTowerTrigPrimP4()->begin();ii!=ev.ecalDeadTowerTrigPrimP4()->end();++ii,++idx){
      if((int)ev.ecalDeadTowerNBadXtals()->at(idx) >= nBad){//hard coded I know
	testVec.SetPtEtaPhiE(100,(*ii).Eta(),(*ii).Phi(),100);
	float DR = fabs(ROOT::Math::VectorUtil::DeltaR(*ii,testjetVec));
	if(DR < DRmin) DRmin = DR;
      }
    
    }

    return DRmin;
  }

  //-----------------------------------------------------------------------------
  //
  Double_t RaT::DeadECALDR_File(TString deadECALfile,float jetphi,float jeteta, int nBad){
    // cout << " hi ho " << deadECALfile << endl;
    TLorentzVector testjetVec(0,0,0,0);
    double DRmin = 100;
    testjetVec.SetPtEtaPhiE(100,jeteta,jetphi,100);

    //cout << " in dead ecal " << endl;
    ifstream myfile(deadECALfile);
    if(!myfile.good()) cout << "file is not there " << endl;
    if(myfile.is_open()){

      while(!myfile.eof()){

	float phi,eta;
	int iEta,iPhi,nBadCells;
	myfile>>eta;
	myfile>>phi;
	myfile>>iEta;
	myfile>>iPhi;
	myfile>>nBadCells;
	// cout <<eta<< " "<< phi<<endl;
	if(nBadCells >= nBad){
	  TLorentzVector testVec(0,0,0,0);
	  testVec.SetPtEtaPhiE(100,eta,phi,100);
	  float DR = fabs(ROOT::Math::VectorUtil::DeltaR(testVec,testjetVec));
	  if(DR < DRmin) DRmin = DR;
	}
      }
   
      myfile.close();
    } 
    return DRmin;

  } 

// -----------------------------------------------------------------------------
//
bool RaT::passVertexSumPtOverHt( Event::Data& ev, double ht ) {

  if( !ev.vertexSumPt.enabled() ) { return true; }
  
  double vertex_pt = 0.;
  std::vector<floatle>::const_iterator ivtx = ev.vertexSumPt()->begin();
  std::vector<floatle>::const_iterator jvtx = ev.vertexSumPt()->end();
  for ( ; ivtx != jvtx; ++ivtx ) { 

    int pos = static_cast<int>( ivtx - ev.vertexSumPt()->begin() );
    
    if( !ev.vertexIsFake()->at( pos ) && 
	ev.vertexNdof()->at( pos ) > 4 &&
	fabs( ev.vertexPosition()->at( pos ).Z() ) < 24.0 && 
	ev.vertexPosition()->at( pos ).Rho() < 2.0 ) { vertex_pt += *ivtx; }
    
  }
  
  if ( vertex_pt / ( ht > 0. ? ht : ev.CommonHT() ) > 0.1 ) { return true; } 
  else { return false; }

}

// -----------------------------------------------------------------------------
//
int RaT::trigger( const Event::Data& ev, const vstring& triggers ) { 
  
  if ( epochs_.empty() && triggers.empty() ) { return 1; }
  
  int prescale = -1;

  if ( !epochs_.empty() ) { 

    // Use random number to determine trigger to use
    double rdm = rand() / double(RAND_MAX);
    int index = -1;
    for ( uint ii = 0; ii < epochs_.size(); ++ii ) {
      if ( rdm < epochs_[ii] ) { index = ii; break; }
    }
    if ( index < 0 || index >= (int)triggers.size() ) { return prescale; }
    
    // Extract trigger thresholds
    double ht = 0., mht = 0., at = 0.;
    thresholds( triggers[index], ht, mht, at );
    
//     std::cout << " rdm: " << rdm
// 	      << " index: " << index
// 	      << " trigger: " << triggers[index]
// 	      << " ht: " << ht
// 	      << " mht: " << mht
// 	      << " at: " << at
// 	      << " hltHt: " << hltHt(ev,ht)
// 	      << " hltMht: " << hltMht(ev,ht)
// 	      << std::endl;
    
    // HT_MHT cross-trigger
    if ( ht > 0. && hltHt(ev,ht) && mht > 0. && hltMht(ev,mht) ) { return 1; }
    // HT utility trigger
    else if ( ht > 0. && hltHt(ev,ht) ) { return 1; }

    return prescale;

  }
  
  vstring::const_iterator iname = triggers.begin();
  vstring::const_iterator jname = triggers.end();
  for ( ; iname != jname; ++iname ) {
    
    // Find trigger 
    const std::map<std::string,bool>* triggers = ev.hlt();
    std::map<std::string,bool>::const_iterator itrigger = triggers->find(*iname); 
    if ( itrigger == triggers->end() ) { continue; }

    // Check if trigger fired
    if ( !itrigger->second ) { continue; }
    
    // Find prescale
    std::map<std::string,int>::const_iterator iprescale = ev.hlt_prescaled()->find(itrigger->first);
    if ( iprescale == ev.hlt_prescaled()->end() ) { continue; }
    
    // Store lowest prescale of triggers that fire
    if ( prescale < 0 || iprescale->second < prescale ) { prescale = iprescale->second; }
    
  }
  
  return prescale;
  
}

// -----------------------------------------------------------------------------
//
double RaT::minBiasDeltaPhi( const std::vector<LorentzV>& objects ) { 

  // Calculate recoil
  LorentzV recoil = LorentzV(0.,0.,0.,0.);
  std::vector<LorentzV>::const_iterator ii = objects.begin();
  std::vector<LorentzV>::const_iterator jj = objects.end();
  for ( ; ii != jj; ++ii ) { recoil += *ii; }
  recoil.SetPxPyPzE( -recoil.Px(), -recoil.Py(), -recoil.Pz(), recoil.E() );

  // Test each configuration
  double min = 10.;
  ii = objects.begin();
  jj = objects.end();
  for ( ; ii != jj; ++ii ) { 
    recoil += *ii; 
    double test = fabs( ROOT::Math::VectorUtil::DeltaPhi( *ii, recoil ) );
    if ( test < min ) { min = test; }
    recoil -= *ii;
  }

  return min;

}

// -----------------------------------------------------------------------------
//
void RaT::thresholds( std::string trigger,
			     double& ht, 
			     double& mht,
			     double& at ) {
  
  ht  = 0.;
  mht = 0.;
  at  = 0.;
  
  std::size_t ht_pos = trigger.find("_HT");
  std::size_t mht_pos = trigger.find("_MHT");
  std::size_t v_pos = trigger.find("_v");
  
  std::string ht_str = trigger.substr( ht_pos+3, mht_pos );
  std::string mht_str = trigger.substr( mht_pos+4, v_pos );
  
  std::stringstream ht_ss; ht_ss << ht_str;
  std::stringstream mht_ss; mht_ss << mht_str;
  
  ht_ss >> ht;
  mht_ss >> mht;
  
}

// -----------------------------------------------------------------------------
//
bool RaT::hltHt( const Event::Data& ev, double ht_cut ) {
  
  // Retrieve input jets
  const std::vector<Event::Jet> jets = ev.JD_Jets();
  
  // Some initialization
  int njets = 0;
  double ht = 0.;
  
  // Loop through jets
  for ( unsigned int i = 0; i < jets.size(); ++i ) {
    
    // Construct jet object
    LorentzV jet( jets[i] );
    
    // Extract jet ET
    double et = jet.E() / cosh(jet.Eta() ); //@@ assume massless jet
    
    // Check jet is within acceptance
    if ( et < 40. || fabs(jet.Eta()) > 3. ) { continue; }
    
    njets++;
    ht += et;
    
    // Reject monojet events
    if ( njets < 2 ) { continue; }

    //std::cout << "[RaT::hltHt] HT: " << ht << std::endl;
    
    // Check if above HT threshold
    if ( ht >= ht_cut ) { return true; } 
    
  }
  
  return false;

}  

// -----------------------------------------------------------------------------
//
bool RaT::hltMht( const Event::Data& ev, double mht_cut ) {
  
  // Retrieve input jets
  const std::vector<Event::Jet> jets = ev.JD_Jets();
  
  // Some initialization
  int njets_3 = 0;
  double mhx_3 = 0.;
  double mhy_3 = 0.;
  int njets_5 = 0;
  double mhx_5 = 0.;
  double mhy_5 = 0.;
  
  // Loop through jets
  for ( unsigned int i = 0; i < jets.size(); ++i ) {
    
    // Construct jet object
    LorentzV jet( jets[i] );
    
    // Extract jet ET
    double et = jet.E() / cosh(jet.Eta() ); //@@ assume massless jet
    
    // Check jet is within acceptance (eta < 5)
    if ( et < 30. || fabs(jet.Eta()) > 5. ) { continue; }
    
    // Variables used in MHT calculation
    njets_5++;
    mhx_5 -= et * cos( jet.Phi() );
    mhy_5 -= et * sin( jet.Phi() );
    
    // Check jet is within acceptance (eta < 3)
    if ( et < 30. || fabs(jet.Eta()) > 3. ) { continue; }
    
    // Variables used in MHT calculation
    njets_3++;
    mhx_3 -= et * cos( jet.Phi() );
    mhy_3 -= et * sin( jet.Phi() );
    
  }
  
  // Calc MHT
  double mht_3 = sqrt( mhx_3*mhx_3 + mhy_3*mhy_3 );
  double mht_5 = sqrt( mhx_5*mhx_5 + mhy_5*mhy_5 );
  
  int njets = 0;
  double mht = 0.;
  
  // Find minimum of MHT(eta<3,eta<5) 
  if ( mht_3 < mht_5 ) { njets = njets_3; mht = mht_3; }
  else                 { njets = njets_5; mht = mht_5; }
  
  // Reject mono-jet events
  if ( njets < 2 ) { return false; }

  //std::cout << "[RaT::hltMht] MHT: " << mht << std::endl;
    
  // Check if above MHT threshold
  if ( mht >= mht_cut ) { return true; } 
  
  return false;

}

// -----------------------------------------------------------------------------
//
bool RaT::hltHtAlphaT( const Event::Data& ev, 
			      double ht_cut, 
			      double at_cut ) {
  
  // Retrieve input jets
  const std::vector<Event::Jet> jets = ev.JD_Jets();
  
  // Some initialization
  int njets = 0;
  double ht = 0.;
  double dht = 0.;
  double mhx = 0.;
  double mhy = 0.;
  
  // Loop through jets
  for ( unsigned int i = 0; i < jets.size(); ++i ) {
    
    // Construct jet object
    LorentzV jet( jets[i] );
    
    // Extract jet ET
    double et = jet.E() / cosh(jet.Eta() ); //@@ assume massless jet
    
    // Check jet is within acceptance
    if ( et < 40. || fabs(jet.Eta()) > 3. ) { continue; }
    
    // Variables used in AlphaT calculation
    njets++;
    ht += et;
    dht += ( njets < 2 ? et : -1.* et ); //@@ only use for njets < 4
    mhx -= et * cos( jet.Phi() );
    mhy -= et * sin( jet.Phi() );
    
    // Reject monojet events
    if ( njets < 2 ) { continue; }
    
    // Calc MHT and AlphaT 
    double mht = sqrt( mhx*mhx + mhy*mhy );
    double aT = 0.;
    if ( njets == 2 || njets == 3 ) {
      aT = ( ht - fabs(dht) ) / ( 2. * sqrt( ( ht*ht ) - ( mht*mht ) ) );
    } else if ( njets > 3 ) {
      aT = 1. / ( 2. * sqrt( ( 1. - ( (mht/ht) * (mht/ht) ) ) ) );
    }
    
    // Check if above HT and AlphaT thresholds
    if ( ( ht >= ht_cut ) && ( aT >= at_cut ) ) { return true; } 
    
  }
  
  return false;

}  



// -----------------------------------------------------------------------------
//
// void RaT::counter( int ht, int njets, int cut, double weight ) {
//   if ( njets > nMax_ ) { njets = nMax_; }
//   if ( cutFlowHistos_ ) {
    
//     if (ht) hCutFlow_[ht][0]->Fill( cut*1., weight ); 
//     hCutFlow_[0][0]->Fill( cut*1., weight ); 
    
    
//     if ( !ht && !njets && hCutFlow_[0][0] ) { 
//       hCutFlow_[0][0]->Fill( cut*1., weight ); 
//     }
//     if ( !ht && njets && hCutFlow_[0][njets] ) {
//       hCutFlow_[0][0]->Fill( cut*1., weight );
//       hCutFlow_[0][njets]->Fill( cut*1., weight );
//     }
//     if ( ht && !njets && hCutFlow_[ht][0] ) { 
//       hCutFlow_[0][0]->Fill( cut*1., weight );
//       hCutFlow_[ht][0]->Fill( cut*1., weight );
//     }
//     if ( ht && njets && hCutFlow_[ht][njets] ) {
//       hCutFlow_[ht][njets]->Fill( cut*1., weight );
//     }

//   }
// }


// 	  // Retrieve trigger and prescale info from event
// 	  int prescale = -1; 
// 	  if ( !triggers_.empty() ) {
// 	    vstring::const_iterator iname = triggers_.begin();
// 	    vstring::const_iterator jname = triggers_.end();
// 	    for ( ; iname != jname; ++iname ) {

// 	      // Find trigger 
// 	      const std::map<std::string,bool>* triggers = ev.hlt();
// 	      std::map<std::string,bool>::const_iterator itrigger = triggers->find(*iname); 
// 	      if ( itrigger == triggers->end() ) { 
// 		//std::cout << " missing name " << *iname << std::endl;
// 		continue; 
// 	      }

// 	      // Find prescale
// 	      std::map<std::string,int>::const_iterator iprescale = ev.hlt_prescaled()->find(itrigger->first);
// 	      if ( iprescale == ev.hlt_prescaled()->end() ) { 
// 		//std::cout << " missing prescale " << *iname << std::endl;
// 		continue; 
// 	      }
	      
// 	      // Extract HT value
// 	      double trigger_ht = -1.;
// 	      size_t pos = itrigger->first.find("HLT_HT");
// 	      std::string substr = itrigger->first.substr(pos+6,3);
// 	      if ( pos != std::string::npos ) { trigger_ht = 1.*atoi( substr.c_str() ); }
// // 	      std::cout << " trigger " << itrigger->first
// // 			<< " pos " << pos 
// // 			<< " substr " << substr
// // 			<< " trigger_ht " << trigger_ht
// // 			<< std::endl;

// 	      // HT monitor trigger names comprise 12 characters
// 	      bool monitor_trigger = ( itrigger->first.size() == 12 );
	      
// 	      // Use only HT monitor (signal) triggers for left (right) side; use unprescaled HT monitor triggers always
// 	      bool use_trigger = ( ( ( at_reco > alphaT_[aT_] ) && !monitor_trigger ) || 
// 				   ( ( at_reco < alphaT_[aT_] ) &&  monitor_trigger ) );//||
// 	      //( monitor_trigger && iprescale->second == 1 ) );
	      
// // 	      if ( trigger_ht != 250 &&
// // 		   trigger_ht != 260 &&
// // 		   trigger_ht != 300 &&
// // 		   trigger_ht != 350 ) {
// //  	      if ( monitor_trigger ) {
// //  		std::cout << "TEST  "
// // 			  << itrigger->first << " "
// // 			  << itrigger->second << " "
// //  			  << at_reco << " "
// //  			  << monitor_trigger << " "
// //  			  << trigger_ht << " "
// //  			  << use_trigger << " "
// //  			  << iprescale->second << " "
// //  			  << ht_reco << " "
// //  			  << htBins_[ibin] << " "
// //  			  << ibin
// //  			  << std::endl;
// //  	      }

// 	      // HT offset to guarantee plateau
// 	      double offset = 1.e-3;
	      
// 	      // Store lowest prescale of triggers that fire
// 	      if ( itrigger->second && 
// 		   (htBins_[ibin]+offset) > trigger_ht && 
// 		   //(ht_reco+offset) > trigger_ht && 
// 		   use_trigger &&
// 		   ( prescale < 0 || iprescale->second < prescale ) ) { 
// 		prescale = iprescale->second; 
// 	      }

// // 	      std::cout << " trigger " << itrigger->first
// // 			<< " fired " << itrigger->second
// // 			<< " trigger_ht " << trigger_ht
// // 			<< " ht_reco " << ht_reco
// // 			<< " prescale " << iprescale->second
// // 			<< std::endl;

// 	    }
// 	  } else { prescale = 1; }








