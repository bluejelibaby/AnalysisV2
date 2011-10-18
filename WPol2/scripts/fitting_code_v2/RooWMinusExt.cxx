 /***************************************************************************** 
  * Project: RooFit                                                           * 
  *                                                                           * 
  * This code was autogenerated by RooClassFactory                            * 
  *****************************************************************************/ 

 // Your description goes here... 

 #include "Riostream.h" 

 #include "RooWMinusExt.h" 
 #include "RooAbsReal.h" 
 #include "RooAbsCategory.h" 
 #include <math.h> 
 #include "TMath.h" 

 ClassImp(RooWMinusExt) 

 RooWMinusExt::RooWMinusExt(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _f1,
                        RooAbsReal& _f2,
                        RooAbsReal& _fs,
                        RooAbsReal& _fm) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   f1("f1","f1",this,_f1),
   f2("f2","f2",this,_f2),
   fs("fs","fs",this,_fs),
   fm("fm","fm",this,_fm)
 { 
 } 


 RooWMinusExt::RooWMinusExt(const RooWMinusExt& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   f1("f1",this,other.f1),
   f2("f2",this,other.f2),
   fs("fs",this,other.fs),
   fm("fm",this,other.fm)
 { 

    rbin=10;

   dir = "RECO_PolPlots_50toinf/";
   //dir="RECO_ElPolPlots_PostMHT50/";

   pHist1 = dir+"RECO_ICVarPFMinus_LH";
   pHist2 = dir+"RECO_ICVarPFMinus_RH";
   pHist3 = dir+"RECO_ICVarPFMinus_LO";

   fW=new TFile("RecoRoutines_W-selection_WJets_madgraph_Fall2010Z2.root");
 
   mc1 = (TH1D*)fW->Get(pHist1); mc1->Rebin(rbin);
   mc2 = (TH1D*)fW->Get(pHist2); mc2->Rebin(rbin);
   mc3 = (TH1D*)fW->Get(pHist3); mc3->Rebin(rbin);



 } 



 Double_t RooWMinusExt::evaluate() const 
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
  //f = (0.5*f1*(m1val-m2val)) + (0.5*(1-f2)*(m1val+m2val)) + (f2*m3val);
   f = (f1*0.5*(m1val-m2val)) + ((1-f2)*0.5*(m1val+m2val)) + (f2*m3val)  +fs *  0.065* m3val+ fs * ( 0.00254 * 0.5 * (m1val - m2val)) + fm *  0.01* m3val + fm * 0.0043 * 0.5 * (m1val - m2val);
  // return 1.0 ; 
  return f;  
 } 



