
/***************************************************************************** 
  * Project: RooFit                                                           * 
  *                                                                           * 
  * This code was autogenerated by RooClassFactory                            * 
  *****************************************************************************/ 

 // Your description goes here... 

 #include "Riostream.h" 

 #include "RooWPlus.h" 
 #include "RooAbsReal.h" 
 #include "RooAbsCategory.h" 
 #include <math.h> 
 #include "TMath.h" 

 ClassImp(RooWPlus) 

   RooWPlus::RooWPlus(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _fL,
                 	RooAbsReal& _fR
                        ) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   fL("fL","fL",this,_fL),
   fR("fR","fR",this,_fR)

 { 
 } 


 RooWPlus::RooWPlus(const RooWPlus& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   fL("fL",this,other.fL),
   fR("fR",this,other.fR)

 { 

   rbin=10;

   dir = "RECO_PolPlots_50toinf/";
   //dir="RECO_ElPolPlots_PostMHT50/";

   pHist1 = dir+"RECO_ICVarPFPlus_LH";
   pHist2 = dir+"RECO_ICVarPFPlus_RH";
   pHist3 = dir+"RECO_ICVarPFPlus_LO";

   fW=new TFile("RecoRoutines_W-selection_WJets_madgraph_June2010.root");
   // fW = new TFile("eWPol_Signal_Wjets.root");

   mc1 = (TH1D*)fW->Get(pHist1); mc1->Rebin(rbin);
   mc2 = (TH1D*)fW->Get(pHist2); mc2->Rebin(rbin);
   mc3 = (TH1D*)fW->Get(pHist3); mc3->Rebin(rbin);

 } 

 Double_t RooWPlus::evaluate() const 
 { 

   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   Double_t f;
   Double_t xx = x;

   // Helicity templates
   Double_t m1val = mc1->GetBinContent(mc1->FindBin(xx));
   Double_t m2val = mc2->GetBinContent(mc2->FindBin(xx));
   Double_t m3val = mc3->GetBinContent(mc3->FindBin(xx));

   // Signal PDF
   //f = (fL * m1val) + (fR * m2val) + ((1-fL-fR) * m3val); 
   f = (fL * m1val) + ( (1-fL) *  (fR * m2val)) + ( (1-fL) * (1-fR) * m3val )  ;

   return f; 

 } 



