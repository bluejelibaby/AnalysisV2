#include "AnalysisTree_HighPt.hh"

using namespace Operation;

namespace OneLepton{
  
  void AnalysisTree_HighPt::BookHistos(){
    
    tree=new TTree("T","test");

    // Event variables
    tree->Branch("wgt",&wgt,"wgt/D");
    tree->Branch("RunNumber",&RunNumber,"RunNumber/I");
    tree->Branch("EventNumber",&EventNumber,"EventNumber/I");
    tree->Branch("LumiSection",&LumiSection,"LumiSection/I");
    tree->Branch("NumPVs",&NumPVs,"NumPVs/I");

    // Trigger
    tree->Branch("trig_Mu9",&trig_Mu9, "trig_Mu9/B");
    tree->Branch("trig_Mu11",&trig_Mu11, "trig_Mu11/B");
    tree->Branch("trig_Mu15",&trig_Mu15, "trig_Mu15/B");
    tree->Branch("trig_Mu5_HT70U",&trig_Mu5_HT70U, "trig_Mu5_HT70U/B");
    tree->Branch("trig_Ele15_LW",&trig_Ele15_LW, "trig_Ele15_LW/B");
    tree->Branch("trig_Ele15_SW",&trig_Ele15_SW, "trig_Ele15_SW/B");
    tree->Branch("trig_Ele17_SW_EleId",&trig_Ele17_SW_EleId, "trig_Ele17_SW_EleId/B");
    tree->Branch("trig_Jet50",&trig_Jet50, "trig_Jet50/B");
    tree->Branch("trig_Jet80",&trig_Jet80, "trig_Jet80/B");

    tree->Branch("unpresc_trig_Mu9",&unpresc_trig_Mu9, "unpresc_trig_Mu9/B");
    tree->Branch("unpresc_trig_Mu11",&unpresc_trig_Mu11, "unpresc_trig_Mu11/B");
    tree->Branch("unpresc_trig_Mu15",&unpresc_trig_Mu15, "unpresc_trig_Mu15/B");
    tree->Branch("unpresc_trig_Mu5_HT70U",&unpresc_trig_Mu5_HT70U, "unpresc_trig_Mu5_HT70U/B");
    tree->Branch("unpresc_trig_Ele15_LW",&unpresc_trig_Ele15_LW, "unpresc_trig_Ele15_LW/B");
    tree->Branch("unpresc_trig_Ele15_SW",&unpresc_trig_Ele15_SW, "unpresc_trig_Ele15_SW/B");
    tree->Branch("unpresc_trig_Ele17_SW_EleId",&unpresc_trig_Ele17_SW_EleId, "unpresc_trig_Ele17_SW_EleId/B");
    tree->Branch("unpresc_trig_Jet50",&unpresc_trig_Jet50, "unpresc_trig_Jet50/B");
    tree->Branch("unpresc_trig_Jet80",&unpresc_trig_Jet80, "unpresc_trig_Jet80/B");

    // Jet variables
    tree->Branch("NJet",&NJet,"NJet/I");
    tree->Branch("NJet30",&NJet30,"NJet30/I");
    tree->Branch("NJet40",&NJet40,"NJet40/I");
    tree->Branch("NJet50",&NJet50,"NJet50/I");
    tree->Branch("NJet60",&NJet60,"NJet60/I");
    tree->Branch("JetPt",JetPt,"JetPt[NJet]/D");
    tree->Branch("JetEta",JetEta,"JetEta[NJet]/D");
    tree->Branch("JetPhi",JetPhi,"JetPhi[NJet]/D");
    tree->Branch("JetCor",JetCor,"JetCor[NJet]/D");
    tree->Branch("JetEMF",JetEMF,"JetEMF[NJet]/D");

    // Muon variables 
    tree->Branch("NMuons",&NMuons,"NMuons/I");
    tree->Branch("MuonPt",MuonPt,"MuonPt[NMuons]/D");
    tree->Branch("MuonEta",MuonEta,"MuonEta[NMuons]/D");
    tree->Branch("MuonPhi",MuonPhi,"MuonPhi[NMuons]/D");
    tree->Branch("MuonChrg",MuonChrg,"MuonChrg[NMuons]/D");
    tree->Branch("MuonType",MuonType,"MuonType[NMuons]/I");
    tree->Branch("MuongPar",MuongPar,"MuongPar[NMuons]/I");
    tree->Branch("MuonGenMother",MuonGenMother,"MuonGenMother[NMuons]/I");
    tree->Branch("MuonInrTrkD0BS",MuonInrTrkD0BS,"MuonInrTrkD0BS[NMuons]/D");
    tree->Branch("MuonInrTrkD0PV",MuonInrTrkD0PV,"MuonInrTrkD0PV[NMuons]/D");
    tree->Branch("MuonInrTrkD0err",MuonInrTrkD0err,"MuonInrTrkD0err[NMuons]/D");
    tree->Branch("MuonGlbTrkD0BS",MuonGlbTrkD0BS,"MuonGlbTrkD0BS[NMuons]/D");
    tree->Branch("MuonGlbTrkD0PV",MuonGlbTrkD0PV,"MuonGlbTrkD0PV[NMuons]/D");
    tree->Branch("MuonGlbTrkD0err",MuonGlbTrkD0err,"MuonGlbTrkD0err[NMuons]/D");
    tree->Branch("MuonRelCombIso",MuonRelCombIso,"MuonRelCombIso[NMuons]/D");

    // Jet-Muon variables
    tree->Branch("MuonClosestPreJetPt",MuonClosestPreJetPt,"MuonClosestPreJetPt[NMuons]/D");
    tree->Branch("MuonClosestPreJetEta",MuonClosestPreJetEta,"MuonClosestPreJetEta[NMuons]/D");
    tree->Branch("MuonClosestPreJetPhi",MuonClosestPreJetPhi,"MuonClosestPreJetPhi[NMuons]/D");
    tree->Branch("MuonClosestPreJetDR",MuonClosestPreJetDR,"MuonClosestPreJetDR[NMuons]/D");
    tree->Branch("MuonClosestComJetPt",MuonClosestComJetPt,"MuonClosestComJetPt[NMuons]/D");
    tree->Branch("MuonClosestComJetEta",MuonClosestComJetEta,"MuonClosestComJetEta[NMuons]/D");
    tree->Branch("MuonClosestComJetPhi",MuonClosestComJetPhi,"MuonClosestComJetPhi[NMuons]/D");
    tree->Branch("MuonClosestComJetDR",MuonClosestComJetDR,"MuonClosestComJetDR[NMuons]/D");

    // Electron variables 
    tree->Branch("NElectrons",&NElectrons,"NElectrons/I");
    tree->Branch("ElectronPt",ElectronPt,"ElectronPt[NElectrons]/D");
    tree->Branch("ElectronEta",ElectronEta,"ElectronEta[NElectrons]/D");
    tree->Branch("ElectronPhi",ElectronPhi,"ElectronPhi[NElectrons]/D");
    tree->Branch("ElectronChrg",ElectronChrg,"ElectronChrg[NElectrons]/D");

    // Jet-Electron variables
    tree->Branch("ElectronClosestPreJetDR",ElectronClosestPreJetDR,"ElectronClosestPreJetDR[NElectrons]/D");
    tree->Branch("ElectronClosestPreJetPt",ElectronClosestPreJetPt,"ElectronClosestPreJetPt[NElectrons]/D");
    tree->Branch("ElectronClosestComJetDR",ElectronClosestComJetDR,"ElectronClosestComJetDR[NElectrons]/D");
    tree->Branch("ElectronClosestComJetPt",ElectronClosestComJetPt,"ElectronClosestComJetPt[NElectrons]/D");


    // General kinematic variables
    tree->Branch("AlphaT",&AlphaT,"AlphaT/D");
    tree->Branch("AlphaT_Had",&AlphaT_Had,"AlphaT_Had/D");
    tree->Branch("AlphaT_Lep",&AlphaT_Lep,"AlphaT_Lep/D");

    // General kinematic variables -std-
    tree->Branch("HT",&HT,"HT/D");
    tree->Branch("HT_Lep",&HT_Lep,"HT_Lep/D");
    tree->Branch("MHT",&MHT,"MHT/D");
    tree->Branch("MHTEta",&MHTEta,"MHTEta/D");
    tree->Branch("MHTPhi",&MHTPhi,"MHTPhi/D");
    tree->Branch("CaloMET",&CaloMET,"CaloMET/D");
    tree->Branch("CaloMETtypeII",&CaloMETtypeII,"CaloMETtypeII/D");
    tree->Branch("CaloMETtypeIIPhi",&CaloMETtypeIIPhi,"CaloMETtypeIIPhi/D");
    tree->Branch("MT",&MT,"MT/D");
    tree->Branch("LP",&LP,"LP/D");
    tree->Branch("BiasedDPhi",&BiasedDPhi,"BiasedDPhi/D");
    tree->Branch("Meff",&Meff,"Meff/D");

    // General kinematic variables -pf-
    tree->Branch("PFMET",&PFMET,"PFMET/D");
    tree->Branch("PFMETPhi",&PFMETPhi,"PFMETPhi/D");

    // General kinematic variables -hybrid-
    tree->Branch("PFMHT_h",&PFMHT_h,"PFMHT_h/D");
    tree->Branch("PFMT_h",&PFMT_h,"PFMT_h/D");
    tree->Branch("PFLP_h",&PFLP_h,"PFLP_h/D");

    tree->Branch("HT12",&HT12,"HT12/D");
    tree->Branch("MHT12",&MHT12,"MHT12/D");
    tree->Branch("MinvMax",&MinvMax,"MinvMax/D");
    tree->Branch("M2",&M2,"M2/D");
    tree->Branch("M3_sca",&M3_sca,"M3_sca/D");
    tree->Branch("M3_vec",&M3_vec,"M3_vec/D");

  }  
  
  bool AnalysisTree_HighPt::Process(Event::Data &ev) {

 
    if (leptonType_ == "Muons") {
      if ( ev.LD_CommonMuons().accepted.size() ) {
        theLepton_ = ev.LD_CommonMuons().accepted;
        lepFlavour = 2;
      } else { return false; }
    }

    else if (leptonType_ == "Electrons") {
      if ( ev.LD_CommonElectrons().accepted.size() ) {
        theLepton_ = ev.LD_CommonElectrons().accepted;
        lepFlavour = 1;
	//	if (ev.LD_SecElectrons().size()) { thePFLepton_ = ev.LD_SecElectrons(); }
      } else { return false; }
    }

    else {
      throw std::invalid_argument("Wrong Lepton Type supplied [for: mu= Muons, el= Electrons]");
      return false;
    }
    
    // print out HLT's
    //    cout << "\n";
    //    cout << " New Event " << "\n";
    //    for(std::map<std::string,bool>::const_iterator
    //	  it=ev.hlt()->begin();it!=ev.hlt()->end();++it){
    //      std::cout << it->first << " " << it->second << std::endl;
    //    }

      
    // Fill Event variables 
    wgt = ev.GetEventWeight();
    RunNumber = ev.RunNumber();     // cout << "RunNumber:   " << ev.RunNumber()   << " " << RunNumber   << "\n";
    EventNumber = ev.EventNumber(); // cout << "EventNumber: " << ev.EventNumber() << " " << EventNumber << "\n";
    LumiSection = ev.LumiSection(); // cout << "LumiSection: " << ev.LumiSection() << " " << LumiSection << "\n";
    NumPVs = ev.GetVertexSize();

    // Fill the HLT variables
    // HLT_Mu
    std::map<std::string,bool>::const_iterator itMu1=ev.hlt()->find("HLT_Mu9");
    if(itMu1==ev.hlt()->end()) trig_Mu9 = false;
    else trig_Mu9 = itMu1->second;
    std::map<std::string,bool>::const_iterator itMu2=ev.hlt()->find("HLT_Mu11");
    if(itMu2==ev.hlt()->end()) trig_Mu11 = false;
    else trig_Mu11 = itMu2->second;
    std::map<std::string,bool>::const_iterator itMu3=ev.hlt()->find("HLT_Mu15_v1");
    if(itMu3==ev.hlt()->end()) trig_Mu15 = false;
    else trig_Mu15 = itMu3->second;
    std::map<std::string,bool>::const_iterator itMu4=ev.hlt()->find("HLT_Mu5_HT70U_v3");
    if(itMu4==ev.hlt()->end()) trig_Mu5_HT70U = false;
    else trig_Mu5_HT70U = itMu4->second;

    // HLT_Ele
    std::map<std::string,bool>::const_iterator itEl1=ev.hlt()->find("HLT_Ele15_LW_L1R");
    if(itEl1==ev.hlt()->end()) trig_Ele15_LW = false;
    else trig_Ele15_LW = itEl1->second;
    std::map<std::string,bool>::const_iterator itEl2=ev.hlt()->find("HLT_Ele15_SW_L1R");
    if(itEl2==ev.hlt()->end()) trig_Ele15_SW = false;
    else trig_Ele15_SW = itEl2->second;
    std::map<std::string,bool>::const_iterator itEl3=ev.hlt()->find("HLT_Ele17_SW_EleId_L1R");
    if(itEl3==ev.hlt()->end()) trig_Ele17_SW_EleId = false;
    else trig_Ele17_SW_EleId = itEl3->second;

    // HLT_Jet
    std::map<std::string,bool>::const_iterator itJt1=ev.hlt()->find("HLT_Jet50");
    if(itJt1==ev.hlt()->end()) trig_Jet50 = false;
    else trig_Jet50 = itJt1->second;
    std::map<std::string,bool>::const_iterator itJt2=ev.hlt()->find("HLT_Jet80");
    if(itJt2==ev.hlt()->end()) trig_Jet80 = false;
    else trig_Jet80 = itJt2->second;


    // check if the triggers where unprescaled

    //  -- muons --
    std::map<std::string,int>::const_iterator itMuPreSc1=ev.hlt_prescaled()->find("HLT_Mu9");
    if (itMuPreSc1==ev.hlt_prescaled()->end()) unpresc_trig_Mu9 = false;
    else if (itMuPreSc1->second == 1) unpresc_trig_Mu9 = true; 
    else unpresc_trig_Mu9 = false;
    std::map<std::string,int>::const_iterator itMuPreSc2=ev.hlt_prescaled()->find("HLT_Mu11");
    if (itMuPreSc2==ev.hlt_prescaled()->end()) unpresc_trig_Mu11 = false;
    else if (itMuPreSc2->second == 1) unpresc_trig_Mu11 = true; 
    else unpresc_trig_Mu11 = false;
    std::map<std::string,int>::const_iterator itMuPreSc3=ev.hlt_prescaled()->find("HLT_Mu15_v1");
    if (itMuPreSc3==ev.hlt_prescaled()->end()) unpresc_trig_Mu15 = false;
    else if (itMuPreSc3->second == 1) unpresc_trig_Mu15 = true; 
    else unpresc_trig_Mu15 = false;
    std::map<std::string,int>::const_iterator itMuPreSc4=ev.hlt_prescaled()->find("HLT_Mu5_HT70U_v3");
    if (itMuPreSc4==ev.hlt_prescaled()->end()) unpresc_trig_Mu5_HT70U = false;
    else if (itMuPreSc4->second == 1) unpresc_trig_Mu5_HT70U = true; 
    else unpresc_trig_Mu5_HT70U = false;

    //  -- electrons --
    std::map<std::string,int>::const_iterator itElPreSc1=ev.hlt_prescaled()->find("HLT_Ele15_LW_L1R");
    if (itElPreSc1==ev.hlt_prescaled()->end()) unpresc_trig_Ele15_LW = false;
    else if (itElPreSc1->second == 1) unpresc_trig_Ele15_LW = true; 
    else unpresc_trig_Ele15_LW = false;
    std::map<std::string,int>::const_iterator itElPreSc2=ev.hlt_prescaled()->find("HLT_Ele15_SW_L1R");
    if (itElPreSc2==ev.hlt_prescaled()->end()) unpresc_trig_Ele15_SW = false;
    else if (itElPreSc2->second == 1) unpresc_trig_Ele15_SW = true; 
    else unpresc_trig_Ele15_SW = false;
    std::map<std::string,int>::const_iterator itElPreSc3=ev.hlt_prescaled()->find("HLT_Ele17_SW_EleId_L1R");
    if (itElPreSc3==ev.hlt_prescaled()->end()) unpresc_trig_Ele17_SW_EleId = false;
    else if (itElPreSc3->second == 1) unpresc_trig_Ele17_SW_EleId = true; 
    else unpresc_trig_Ele17_SW_EleId = false;

    // -- jets --
    std::map<std::string,int>::const_iterator itJtPreSc1=ev.hlt_prescaled()->find("HLT_Jet50");
    if (itJtPreSc1==ev.hlt_prescaled()->end()) unpresc_trig_Jet50 = false;
    else if (itJtPreSc1->second == 1) unpresc_trig_Jet50 = true; 
    else unpresc_trig_Jet50 = false;
    std::map<std::string,int>::const_iterator itJtPreSc2=ev.hlt_prescaled()->find("HLT_Jet80");
    if (itJtPreSc2==ev.hlt_prescaled()->end()) unpresc_trig_Jet80 = false;
    else if (itJtPreSc2->second == 1) unpresc_trig_Jet80 = true; 
    else unpresc_trig_Jet80 = false;


    
    // Fill the Jet variables
    NJet = ev.JD_CommonJets().accepted.size();
    UInt_t countJts = 0;
    UInt_t countJts30 = 0; UInt_t countJts40 = 0; UInt_t countJts50 = 0; UInt_t countJts60 = 0;
    for ( std::vector<Event::Jet const *>::const_iterator iJ = ev.JD_CommonJets().accepted.begin();
	  iJ != ev.JD_CommonJets().accepted.end();
	  iJ++ ) {

      if ( ((*iJ)->Pt()>30.) && (fabs((*iJ)->Eta())<2.4) ) {
	countJts30++;
      }
      
      if ( ((*iJ)->Pt()>40.) && (fabs((*iJ)->Eta())<2.4) ) {
        countJts40++;
      }
      
      if ( ((*iJ)->Pt()>50.) && (fabs((*iJ)->Eta())<2.4) ) {
        countJts50++;
      }

      if ( ((*iJ)->Pt()>60.) && (fabs((*iJ)->Eta())<2.4) ) {
        countJts60++;
      }
      
      JetPt[countJts] = (*iJ)->Pt();
      JetEta[countJts] = (*iJ)->Eta();
      JetPhi[countJts] = (*iJ)->Phi();
      JetCor[countJts] =  ev.GetJetCorrFactor((*iJ)->GetIndex());
      JetEMF[countJts] = (*iJ)->GetEmFrac();

      countJts++;
    } // ~ end of loop over the common Jts.
    NJet30 = countJts30;
    NJet40 = countJts40;
    NJet50 = countJts50;
    NJet60 = countJts60;


    // Fill the Muon variables
    NMuons = ev.LD_CommonMuons().accepted.size();
    UInt_t countMus = 0;
    for (std::vector<Event::Lepton const *>::const_iterator iMu = ev.LD_CommonMuons().accepted.begin(); 
	 iMu != ev.LD_CommonMuons().accepted.end(); iMu++) {

      MuonPt[countMus] = (*iMu)->Pt();
      MuonEta[countMus] = (*iMu)->Eta();
      MuonPhi[countMus] = (*iMu)->Phi();
      MuonChrg[countMus] = (*iMu)->GetCharge();
      MuonInrTrkD0BS[countMus] = ev.GetMuonInnerTrackDxyBS((*iMu)->GetIndex());
      MuonInrTrkD0PV[countMus] = ev.GetMuonInnerTrackDxy((*iMu)->GetIndex());
      MuonInrTrkD0err[countMus] = ev.GetMuonInnerTrackDxyError((*iMu)->GetIndex());
      MuonGlbTrkD0BS[countMus] = ev.GetMuonGlobalTrackdxyBS((*iMu)->GetIndex());
      MuonGlbTrkD0PV[countMus] = ev.GetMuonGlobalTrackdxy((*iMu)->GetIndex());
      MuonGlbTrkD0err[countMus] = ev.GetMuonGlobalTrackdxyError((*iMu)->GetIndex());
      MuonRelCombIso[countMus] = (*iMu)->GetCombIsolation();

      if (genInfo_) {
	int iMatch = ev.leptonMatch(*iMu,2);
	MuonType[countMus] = ev.leptonType(iMatch); 
	//	  MuongPar[countMus] = ExtendedType(ev,*iMu,2);
	if ( iMatch>=0) { MuonGenMother[countMus] = abs(ev.MC_GenLeptons()[iMatch]->GetMotherID()); }
      }
      
      // Fill the Jet-Muon variables
      double muonPreJetPt_ = -999.;
      double muonPreJetEta_ = -999.;
      double muonPreJetPhi_ = -999.;
      double muonPreJetDRmin_ = 999.;
      double muonComJetPt_ = -999.;
      double muonComJetEta_ = -999.;
      double muonComJetPhi_ = -999.;
      double muonComJetDRmin_ = 999.;
      
      for (std::vector<Event::Jet>::const_iterator iMuj1=ev.JD_Jets().begin(); iMuj1!=ev.JD_Jets().end(); ++iMuj1) {
	double tmpMuonPreJetDR_ = fabs(ROOT::Math::VectorUtil::DeltaR(**iMu,*iMuj1));
	if (tmpMuonPreJetDR_ < muonPreJetDRmin_) { 
          muonPreJetPt_  = (iMuj1)->Pt();
          muonPreJetEta_ = (iMuj1)->Eta();
          muonPreJetPhi_ = (iMuj1)->Phi();
          muonPreJetDRmin_ = tmpMuonPreJetDR_;
	}
      } // ~end of loop over the PreJets
      MuonClosestPreJetPt[countMus]  = muonPreJetPt_;
      MuonClosestPreJetEta[countMus] = muonPreJetEta_;
      MuonClosestPreJetPhi[countMus] = muonPreJetPhi_;
      MuonClosestPreJetDR[countMus]  = muonPreJetDRmin_;
      
      for (std::vector<Event::Jet const *>::const_iterator iMuj2=ev.JD_CommonJets().accepted.begin(); iMuj2!=ev.JD_CommonJets().accepted.end(); iMuj2++) {
	double tmpMuonComJetDR_ = fabs(ROOT::Math::VectorUtil::DeltaR(**iMu,**iMuj2));
	if (tmpMuonComJetDR_ < muonComJetDRmin_) { 
          muonComJetPt_  = (*iMuj2)->Pt();
          muonComJetEta_ = (*iMuj2)->Eta();
          muonComJetPhi_ = (*iMuj2)->Phi();
          muonComJetDRmin_ = tmpMuonComJetDR_;
	}
      } // ~ end of loop over the common Jts.
      MuonClosestComJetPt[countMus]  = muonComJetPt_;
      MuonClosestComJetEta[countMus] = muonComJetEta_;
      MuonClosestComJetPhi[countMus] = muonComJetPhi_;
      MuonClosestComJetDR[countMus]  = muonComJetDRmin_;

      countMus++;
    } // ~ end of loop over the Common Muons.
  

    // Fill the Electron variables
    NElectrons = ev.LD_CommonElectrons().accepted.size();
    UInt_t countEls = 0;
    for (std::vector<Event::Lepton const *>::const_iterator iEl = ev.LD_CommonElectrons().accepted.begin(); 
	 iEl != ev.LD_CommonElectrons().accepted.end(); iEl++) {
      
      ElectronPt[countEls] = (*iEl)->Pt();
      ElectronEta[countEls] = (*iEl)->Eta();
      ElectronPhi[countEls] = (*iEl)->Phi();
      ElectronChrg[countEls] = (*iEl)->GetCharge();
      if (genInfo_) {
	int iMatch = ev.leptonMatch(*iEl,1);
	ElectronType[countEls] = ev.leptonType(iMatch); 
	//	  ElectrongPar[countEls] = ExtendedType(ev,*iEl,2);
	if ( iMatch>=0) { ElectronGenMother[countEls] = abs(ev.MC_GenLeptons()[iMatch]->GetMotherID()); }
      }
      
      // Fill the Jet-Electron variables
      double electronPreJetPt_ = -999.;
      double electronPreJetDRmin_ = 999.;
      double electronComJetPt_ = -999.;
      double electronComJetDRmin_ = 999.;
      
      for (std::vector<Event::Jet>::const_iterator iElj1=ev.JD_Jets().begin(); iElj1!=ev.JD_Jets().end(); ++iElj1) {
	double tmpElectronPreJetDR_ = fabs(ROOT::Math::VectorUtil::DeltaR (**iEl,*iElj1));
	if (tmpElectronPreJetDR_ < electronPreJetDRmin_) { electronPreJetDRmin_ = tmpElectronPreJetDR_; electronPreJetPt_ = (iElj1)->Pt(); }
      } // ~end of loop over the PreJets
      ElectronClosestPreJetDR[countEls] = electronPreJetDRmin_;
      ElectronClosestPreJetPt[countEls] = electronPreJetPt_; 
      
      for (std::vector<Event::Jet const *>::const_iterator iElj2=ev.JD_CommonJets().accepted.begin(); iElj2!=ev.JD_CommonJets().accepted.end(); iElj2++) {
	double tmpElectronComJetDR_ = fabs(ROOT::Math::VectorUtil::DeltaR (**iEl,**iElj2));
	if (tmpElectronComJetDR_ < electronComJetDRmin_) { electronComJetDRmin_ = tmpElectronComJetDR_; electronComJetPt_ = (*iElj2)->Pt(); }
      } // ~ end of loop over the common Jts.
      ElectronClosestComJetDR[countEls] = electronComJetDRmin_;
      ElectronClosestComJetPt[countEls] = electronComJetPt_; 	

      countEls++;
    } // ~ end of loop over the Common Electrons.
    


    // Fill the General variables

    if ( (ev.CommonObjects().size() >= mMinNumOfObjs_) && (ev.CommonObjects().size()<= mMaxNumOfObjs_) ) {
      AlphaT = ev.CommonAlphaT();
    } else { AlphaT = -999.; }
    if ( (ev.HadronicObjects().size() >= mMinNumOfObjs_) && (ev.HadronicObjects().size()<= mMaxNumOfObjs_) ) {
      AlphaT_Had = ev.HadronicAlphaT();
    } else { AlphaT_Had = -999.; }
    if ( (ev.LeptonicObjects().size() >= mMinNumOfObjs_) && (ev.LeptonicObjects().size()<= mMaxNumOfObjs_) ) {
      AlphaT_Lep = ev.LeptonicAlphaT();
    } else { AlphaT_Lep = -999.; }

    BiasedDPhi = ev.CommonMinBiasDPhi();


    // ------------------------------------
    // Fill the General variables -std-

    HT               = ev.CommonHT();
    HT_Lep           = ev.CommonHT() + theLepton_.at(0)->Pt();
    MHT              = (ev.CaloMETtypeII() + *(theLepton_.at(0))).Pt();    
    MHTEta           = (ev.CaloMETtypeII() + *(theLepton_.at(0))).Eta();
    MHTPhi           = (ev.CaloMETtypeII() + *(theLepton_.at(0))).Phi();
    CaloMET          = ev.CaloMET().Pt();
    CaloMETtypeII    = ev.CaloMETtypeII().Pt();
    CaloMETtypeIIPhi = ev.CaloMETtypeII().Phi();
    MT               = sqrt(2.*(theLepton_.at(0)->Pt())*(ev.CaloMETtypeII().Pt())*(1.-cos(ROOT::Math::VectorUtil::DeltaPhi(*(theLepton_.at(0)),ev.CaloMETtypeII())))) ;
    LP               = (((theLepton_.at(0)->Px())*((ev.CaloMETtypeII()+(*(theLepton_.at(0)))).Px()))+((theLepton_.at(0)->Py())*((ev.CaloMETtypeII()+(*(theLepton_.at(0)))).Py())))/
      ( ((ev.CaloMETtypeII()+(*(theLepton_.at(0)))).Pt())*((ev.CaloMETtypeII()+(*(theLepton_.at(0)))).Pt()) );
    Meff = HT_Lep + ev.PFMET().Pt();


    PFMET    = ev.PFMET().Pt();
    PFMETPhi = ev.PFMET().Phi();


    // "hybrid" version of PFMHT, PFMT, PFLP
    PFMHT_h = (ev.PFMET() + *(theLepton_.at(0))).Pt();
    PFMT_h  = sqrt(2.*(theLepton_.at(0)->Pt())*(ev.PFMET().Pt())*(1.-cos(ROOT::Math::VectorUtil::DeltaPhi(*(theLepton_.at(0)),ev.PFMET())))) ;
    PFLP_h  = (((theLepton_.at(0)->Px())*((ev.PFMET()+(*(theLepton_.at(0)))).Px()))+((theLepton_.at(0)->Py())*((ev.PFMET()+(*(theLepton_.at(0)))).Py())))/
      ( ((ev.PFMET()+(*(theLepton_.at(0)))).Pt())*((ev.PFMET()+(*(theLepton_.at(0)))).Pt()) );
    																	


    // Fill the M3 variables

    if (ev.JD_CommonJets().accepted.size()>=2) {

      TLorentzVector jeta1;  TLorentzVector jeta2;
      jeta1.SetPxPyPzE(ev.JD_CommonJets().accepted[0]->Px(),ev.JD_CommonJets().accepted[0]->Py(),ev.JD_CommonJets().accepted[0]->Pz(),ev.JD_CommonJets().accepted[0]->E());
      jeta2.SetPxPyPzE(ev.JD_CommonJets().accepted[1]->Px(),ev.JD_CommonJets().accepted[1]->Py(),ev.JD_CommonJets().accepted[1]->Pz(),ev.JD_CommonJets().accepted[1]->E());

      HT12 = jeta1.Pt()+jeta2.Pt();
      TLorentzVector tmpJet; tmpJet = jeta1 + jeta2; MHT12 = tmpJet.Pt();
      M2 = (jeta1 + jeta2).M();


      // calculate MinvMax
      MinvMax = -10.;
      int count1j = 0; int count2j = 0;
      for (std::vector<Event::Jet const *>::const_iterator ij1=ev.JD_CommonJets().accepted.begin(); ij1!=ev.JD_CommonJets().accepted.end(); ij1++) {

        TLorentzVector jj1;
        count1j++;
        jj1.SetPxPyPzE((*ij1)->Px(),(*ij1)->Py(),(*ij1)->Pz(),(*ij1)->E());

	for (std::vector<Event::Jet const *>::const_iterator ij2=ev.JD_CommonJets().accepted.begin(); ij2!=ev.JD_CommonJets().accepted.end(); ij2++) {

          TLorentzVector jj2;
          count2j++;
          if (count2j>count1j) { jj2.SetPxPyPzE((*ij2)->Px(),(*ij2)->Py(),(*ij2)->Pz(),(*ij2)->E()); }


          //      cout << ev.EventNumber() << " " << ev.JD_CommonJets().accepted.size() << " " << count1j << " " << count2j << " ";
          //      cout << MinvMax << " " << (jj1+jj2).Pt() << "\n";
          if ( ((jj1+jj2).M()) > MinvMax) { MinvMax = (jj1+jj2).M(); }

        } // 2nd iteration over jets
      } // 1st iteration over jets
      
    } // ~ end of cheking if there are at leasy 2 jets in the event
    else { M2 = -999.; HT12 = -999.; MHT12 = -999.; MinvMax = -999.; }



    if (ev.JD_CommonJets().accepted.size()>=3) {

      // calculate M3_sca
      TLorentzVector jetb1;  TLorentzVector jetb2; TLorentzVector jetb3;
      jetb1.SetPxPyPzE(ev.JD_CommonJets().accepted[0]->Px(),ev.JD_CommonJets().accepted[0]->Py(),ev.JD_CommonJets().accepted[0]->Pz(),ev.JD_CommonJets().accepted[0]->E());
      jetb2.SetPxPyPzE(ev.JD_CommonJets().accepted[1]->Px(),ev.JD_CommonJets().accepted[1]->Py(),ev.JD_CommonJets().accepted[1]->Pz(),ev.JD_CommonJets().accepted[1]->E());
      jetb3.SetPxPyPzE(ev.JD_CommonJets().accepted[2]->Px(),ev.JD_CommonJets().accepted[2]->Py(),ev.JD_CommonJets().accepted[2]->Pz(),ev.JD_CommonJets().accepted[2]->E());

      M3_sca = (jetb1 + jetb2 + jetb3).M();


      // calculate M3_vec
      TLorentzVector j; j.SetPxPyPzE(0.,0.,0.,0.);
      M3_vec = -10.;
      int count1 = 0; int count2 = 0; int count3 = 0;
      for (std::vector<Event::Jet const *>::const_iterator ija=ev.JD_CommonJets().accepted.begin(); ija!=ev.JD_CommonJets().accepted.end(); ija++) {

        TLorentzVector j1;
        count1++;
        j1.SetPxPyPzE((*ija)->Px(),(*ija)->Py(),(*ija)->Pz(),(*ija)->E());
	
        for (std::vector<Event::Jet const *>::const_iterator ijb=ev.JD_CommonJets().accepted.begin(); ijb!=ev.JD_CommonJets().accepted.end(); ijb++) {
	  
          TLorentzVector j2;
          count2++;
          if (count2>count1) { j2.SetPxPyPzE((*ijb)->Px(),(*ijb)->Py(),(*ijb)->Pz(),(*ijb)->E()); }

          for (std::vector<Event::Jet const *>::const_iterator ijc=ev.JD_CommonJets().accepted.begin(); ijc!=ev.JD_CommonJets().accepted.end(); ijc++) {
	    
            TLorentzVector j3;
            count3++;
            if (count3>count2) { j3.SetPxPyPzE((*ijc)->Px(),(*ijc)->Py(),(*ijc)->Pz(),(*ijc)->E()); }
	    
            //      cout << ev.EventNumber() << " " << ev.JD_CommonJets().accepted.size() << " " << count1 << " " << count2 << " " << count3 << " ";
            //      cout << M3_vec << " " << j.Pt() << " " << (j1+j2+j3).Pt() << "\n";
            if ( ((j1+j2+j3).Pt()) > j.Pt()) { j.SetPxPyPzE((j1+j2+j3).Px(),(j1+j2+j3).Py(),(j1+j2+j3).Pz(),(j1+j2+j3).E()); M3_vec = (j1+j2+j3).M(); }

          } // 3nd iteration over jets
        } // 2nd iteration over jets
      } // 1st iteration over jets

    } else { M3_sca = -999.;  M3_vec = -999.; }


    tree->Fill();

    return true;
    
    } // ~end of process AnalysisTree_HighPt

} // ~end of namespace
