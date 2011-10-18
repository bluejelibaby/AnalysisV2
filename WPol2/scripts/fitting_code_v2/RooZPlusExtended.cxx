/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooZPlusExtended.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(RooZPlusExtended) 

 RooZPlusExtended::RooZPlusExtended(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _fL,
                        RooAbsReal& _fR,
                        RooAbsReal& _fs) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   fL("fL","fL",this,_fL),
   fR("fR","fR",this,_fR),
   fs("fs","fs",this,_fs)
 { 
 } 


 RooZPlusExtended::RooZPlusExtended(const RooZPlusExtended& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   fL("fL",this,other.fL),
   fR("fR",this,other.fR),
   fs("fs",this,other.fs)
 { 

   rbin=10;

   dir = "RECO_PolPlots_50toinf/";
   //dir="RECO_ElPolPlots_PostMHT50/";

   pHist1 = dir+"RECO_CosThetaStar1Sol1CorrPlus_LH";
   pHist2 = dir+"RECO_CosThetaStar1Sol1CorrPlus_RH";
   pHist3 = dir+"RECO_CosThetaStar1Sol1CorrPlus_LO";

   //fW=new TFile("../results/reco_mc/RecoRoutines_Z-selection_ZJets_TuneZ2_7TeV_alpgen_tauola.root");
   fW=new TFile("../results10/reco_mc/RecoRoutines_Z-selection_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.Spring11-PU_S1_START311_V1G1-v1.AODSIM.root");
 
   mc1 = (TH1D*)fW->Get(pHist1); mc1->Rebin(rbin);
   mc2 = (TH1D*)fW->Get(pHist2); mc2->Rebin(rbin);
   mc3 = (TH1D*)fW->Get(pHist3); mc3->Rebin(rbin);


 } 



 Double_t RooZPlusExtended::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE

  Double_t f;
  Double_t xx = x;

   // Helicity templates
  Double_t m1val = mc1->GetBinContent(mc1->FindBin(xx));
  Double_t m2val = mc2->GetBinContent(mc2->FindBin(xx));
  Double_t m3val = mc3->GetBinContent(mc3->FindBin(xx));
  
  // Signal PDF
  // f = (fL * m1val) + (fR * m2val) + ((1-fL-fR) * m3val) + (fs * (m1val - m2val)); 
  f = (0.5*fL*(m1val-m2val)) + (0.5*(1-fR)*(m1val+m2val)) + (fR*m3val)  + (fs * (m1val - m2val));
  
  return f; 
 
   //   return 1.0 ; 
 } 



