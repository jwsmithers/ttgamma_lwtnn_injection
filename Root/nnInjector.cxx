//////////////////////////////
//Joshua.Wyatt.Smith@cern.ch//
//////////////////////////////
#include "nnInjector.h"
#include <iostream>
#include <memory>

using namespace std;


void m_add_ppt_systematics(
  TFile *file,
  std::string source){
  // Open the syst file 
  TFile *syst = new TFile(source.c_str(),"read"); 
  if ( syst->IsOpen() ) std::cout << source << " file opened successfully" 
    << std::endl;
  // Get the two ratio plots
  TH1F* ppt_prompt = (TH1F*)syst->Get("weight_PPT_prompt"); //It's ee, emu and mumu
  ppt_prompt->SetName("weight_PPT_prompt_histo");
  TH1F* ppt_hfake = (TH1F*)syst->Get("weight_PPT_fake");//It's ejets and mujets
  ppt_hfake->SetName("weight_PPT_hfake_histo");

  // Save them
  file->cd();
  ppt_hfake->Draw();
  ppt_hfake->Fit("pol1");
  ppt_hfake->Write();
  std::cout<<"Added hfake PPT syst..."<<std::endl;

  ppt_prompt->Draw();
  ppt_prompt->Fit("pol1");
  ppt_prompt->Write();
  std::cout<<"Added prompt PPT syst..."<<std::endl;
  // To be used later in eventloop
  ppt_systematics_applied = true;
}

void m_add_kfactor(
  TFile *file,
  std::string source_sl, 
  std::string source_dl){
  // Open the kfactor file
  TFile* _f_kfactor_sl = new TFile(source_sl.c_str(),"read");
  if ( _f_kfactor_sl->IsOpen() ) std::cout << source_sl << " file opened successfully" 
    << std::endl;
  TFile* _f_kfactor_dl = new TFile(source_dl.c_str(),"read");
  if ( _f_kfactor_dl->IsOpen() ) std::cout << source_dl << " file opened successfully" 
    << std::endl;

  // Get the two kfactor plots
  TH1F* h_sl = (TH1F*)_f_kfactor_sl->Get("kfactor_nlo_mt_ph_pt_fine");
  h_sl->SetName("kfactor_nlo_mt_ph_pt_fine_SL");

  TH1F* h_dl = (TH1F*)_f_kfactor_dl->Get("kfactor_nlo_mt_ph_pt_fine");
  h_dl->SetName("kfactor_nlo_mt_ph_pt_fine_DL");

  // Save them
  file->cd();
  h_sl->Draw();
  h_sl->Write();
  std::cout<<"Added singlelepton kfactor..."<<std::endl;

  h_dl->Draw();
  h_dl->Write();
  std::cout<<"Added dilepton kfactor..."<<std::endl;
  // To be used later in eventloop
  kfactor_applied = true;
}

void m_add_efake_sf(
  TFile *file,
  std::string source){
  // Open the efake file
  TFile* _f_efake_sf_nominal = new TFile(source.c_str(),"read");
  if ( _f_efake_sf_nominal->IsOpen() ) std::cout << source << " file opened successfully" 
    << std::endl;

  // Get the two efake plots
  TH1F* h_efake_sf_Nominal = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Nominal");
  TH1F* h_efake_sf_RangeDown = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_RangeDown");
  TH1F* h_efake_sf_BkgFunc = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_BkgFunc");
  TH1F* h_efake_sf_SigFunc = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_SigFunc");
  TH1F* h_efake_sf_TypeC = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_TypeC");
  TH1F* h_efake_sf_Stat_Pt2Eta4 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt2Eta4");
  TH1F* h_efake_sf_Stat_Pt3Eta3 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt3Eta3");
  TH1F* h_efake_sf_Stat_Pt4Eta1 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt4Eta1");
  TH1F* h_efake_sf_Stat_Pt4Eta2 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt4Eta2");
  TH1F* h_efake_sf_Stat_Pt4Eta3 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt4Eta3");
  TH1F* h_efake_sf_Stat_Pt4Eta5 = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Stat_Pt4Eta5");
  TH1F* h_efake_sf_Total = (TH1F*)_f_efake_sf_nominal->Get("Final_EFake_SF_Total");

  // Save them
  file->cd();
  h_efake_sf_Nominal->Draw(); h_efake_sf_Nominal->Write();
  h_efake_sf_RangeDown->Draw(); h_efake_sf_RangeDown->Write();
  h_efake_sf_BkgFunc->Draw(); h_efake_sf_BkgFunc->Write();
  h_efake_sf_SigFunc->Draw(); h_efake_sf_SigFunc->Write();
  h_efake_sf_TypeC->Draw(); h_efake_sf_TypeC->Write();
  h_efake_sf_Stat_Pt2Eta4->Draw(); h_efake_sf_Stat_Pt2Eta4->Write();
  h_efake_sf_Stat_Pt3Eta3->Draw(); h_efake_sf_Stat_Pt3Eta3->Write();
  h_efake_sf_Stat_Pt4Eta1->Draw(); h_efake_sf_Stat_Pt4Eta1->Write();
  h_efake_sf_Stat_Pt4Eta2->Draw(); h_efake_sf_Stat_Pt4Eta2->Write();
  h_efake_sf_Stat_Pt4Eta3->Draw(); h_efake_sf_Stat_Pt4Eta3->Write();
  h_efake_sf_Stat_Pt4Eta5->Draw(); h_efake_sf_Stat_Pt4Eta5->Write();
  h_efake_sf_Total->Draw(); h_efake_sf_Total->Write();
  std::cout<<"Added efake SFs..."<<std::endl;

  // To be used later in eventloop
  efake_sf_applied = true;
}

void m_add_hadFake_sf( TFile *file, std::string source )
{
  // Open the hadronic fake file
  TFile* _f_hfake_SFs = new TFile(source.c_str(),"read");
  if ( _f_hfake_SFs->IsOpen() ) std::cout << source << " file opened successfully"
      << std::endl;
  
  // Get the SF historams
  TH1F* hfakeSF_conv_Nominal = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_Nominal");
  TH1F* hfakeSF_conv_ttbarModelling_Sherpa = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_ttbarModelling_Sherpa");
  TH1F* hfakeSF_conv_ttbarModelling_ISRFSRUp = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_ttbarModelling_ISRFSRUp");
  TH1F* hfakeSF_conv_ttbarModelling_ISRFSRDown = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_ttbarModelling_ISRFSRDown");
  TH1F* hfakeSF_conv_BkgSubtraction_ttgamma = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_BkgSubtraction_ttgamma");
  TH1F* hfakeSF_conv_BkgSubtraction_rest = (TH1F*)_f_hfake_SFs->Get("hfakeSF_conv_BkgSubtraction_rest");
  TH1F* hfakeSF_unconv_Nominal = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_Nominal");
  TH1F* hfakeSF_unconv_ttbarModelling_Sherpa = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_ttbarModelling_Sherpa");
  TH1F* hfakeSF_unconv_ttbarModelling_ISRFSRUp = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_ttbarModelling_ISRFSRUp");
  TH1F* hfakeSF_unconv_ttbarModelling_ISRFSRDown = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_ttbarModelling_ISRFSRDown");
  TH1F* hfakeSF_unconv_BkgSubtraction_ttgamma = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_BkgSubtraction_ttgamma");
  TH1F* hfakeSF_unconv_BkgSubtraction_rest = (TH1F*)_f_hfake_SFs->Get("hfakeSF_unconv_BkgSubtraction_rest");
  
  // Save them
  file->cd();
  hfakeSF_conv_Nominal->Draw(); hfakeSF_conv_Nominal->Write();
  hfakeSF_conv_ttbarModelling_Sherpa->Draw(); hfakeSF_conv_ttbarModelling_Sherpa->Write();
  hfakeSF_conv_ttbarModelling_ISRFSRUp->Draw(); hfakeSF_conv_ttbarModelling_ISRFSRUp->Write();
  hfakeSF_conv_ttbarModelling_ISRFSRDown->Draw(); hfakeSF_conv_ttbarModelling_ISRFSRDown->Write();
  hfakeSF_conv_BkgSubtraction_ttgamma->Draw(); hfakeSF_conv_BkgSubtraction_ttgamma->Write();
  hfakeSF_conv_BkgSubtraction_rest->Draw(); hfakeSF_conv_BkgSubtraction_rest->Write();
  hfakeSF_unconv_ttbarModelling_Sherpa->Draw(); hfakeSF_unconv_ttbarModelling_Sherpa->Write();
  hfakeSF_unconv_ttbarModelling_ISRFSRUp->Draw(); hfakeSF_unconv_ttbarModelling_ISRFSRUp->Write();
  hfakeSF_unconv_ttbarModelling_ISRFSRDown->Draw(); hfakeSF_unconv_ttbarModelling_ISRFSRDown->Write();
  hfakeSF_unconv_BkgSubtraction_ttgamma->Draw(); hfakeSF_unconv_BkgSubtraction_ttgamma->Write();
  hfakeSF_unconv_BkgSubtraction_rest->Draw(); hfakeSF_unconv_BkgSubtraction_rest->Write();
  std::cout<<"Added hadronic fake SFs..."<<std::endl;
  
  // To be used later in eventloop
  hadFake_sf_applied = true;
}

void m_add_branches(
  TChain *fChain_func, 
  TTree *newT,
  lwt::LightweightNeuralNetwork *neuralNet,
  TFile *file){

  int nentries = fChain_func->GetEntries();

  std::cout<< nentries << " entries" << std::endl;

  newT->Branch("weight_PPT_hfake_fit",&m_weight_PPT_hfake_fit);
  newT->Branch("weight_PPT_prompt_fit",&m_weight_PPT_prompt_fit);
  newT->Branch("weight_PPT_hfake_bin",&m_weight_PPT_hfake_bin);
  newT->Branch("weight_PPT_prompt_bin",&m_weight_PPT_prompt_bin);
  if(ppt_systematics_applied){
    _ppt_prompt = (TH1F*)file->Get("weight_PPT_prompt_histo");
    _ppt_hfake = (TH1F*)file->Get("weight_PPT_hfake_histo");
  }

  newT->Branch("ph_kfactor_correct","vector<float>",&m_ph_kfactor_correct);
  if(kfactor_applied){
    _h_kfactor_sl = (TH1F*)file->Get("kfactor_nlo_mt_ph_pt_fine_SL");
    _h_kfactor_dl = (TH1F*)file->Get("kfactor_nlo_mt_ph_pt_fine_DL");
  }
  
  newT->Branch("efake_sf_Nominal","vector<float>",&m_efake_sf_Nominal);
  newT->Branch("efake_sf_RangeDown","vector<float>",&m_efake_sf_RangeDown);
  newT->Branch("efake_sf_BkgFunc","vector<float>",&m_efake_sf_BkgFunc);
  newT->Branch("efake_sf_SigFunc","vector<float>",&m_efake_sf_SigFunc);
  newT->Branch("efake_sf_TypeC","vector<float>",&m_efake_sf_TypeC);
  newT->Branch("efake_sf_Stat_Pt2Eta4","vector<float>",&m_efake_sf_Stat_Pt2Eta4);
  newT->Branch("efake_sf_Stat_Pt3Eta3","vector<float>",&m_efake_sf_Stat_Pt3Eta3);
  newT->Branch("efake_sf_Stat_Pt4Eta1","vector<float>",&m_efake_sf_Stat_Pt4Eta1);
  newT->Branch("efake_sf_Stat_Pt4Eta2","vector<float>",&m_efake_sf_Stat_Pt4Eta2);
  newT->Branch("efake_sf_Stat_Pt4Eta3","vector<float>",&m_efake_sf_Stat_Pt4Eta3);
  newT->Branch("efake_sf_Stat_Pt4Eta5","vector<float>",&m_efake_sf_Stat_Pt4Eta5);
  newT->Branch("efake_sf_Total","vector<float>",&m_efake_sf_Total);
  if(efake_sf_applied){
    _h_efake_sf_Nominal = (TH1F*)file->Get("Final_EFake_SF_Nominal");
    _h_efake_sf_RangeDown = (TH1F*)file->Get("Final_EFake_SF_RangeDown");
    _h_efake_sf_BkgFunc = (TH1F*)file->Get("Final_EFake_SF_BkgFunc");
    _h_efake_sf_SigFunc = (TH1F*)file->Get("Final_EFake_SF_SigFunc");
    _h_efake_sf_TypeC = (TH1F*)file->Get("Final_EFake_SF_TypeC");
    _h_efake_sf_Stat_Pt2Eta4 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt2Eta4");
    _h_efake_sf_Stat_Pt3Eta3 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt3Eta3");
    _h_efake_sf_Stat_Pt4Eta1 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt4Eta1");
    _h_efake_sf_Stat_Pt4Eta2 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt4Eta2");
    _h_efake_sf_Stat_Pt4Eta3 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt4Eta3");
    _h_efake_sf_Stat_Pt4Eta5 = (TH1F*)file->Get("Final_EFake_SF_Stat_Pt4Eta5");
    _h_efake_sf_Total = (TH1F*)file->Get("Final_EFake_SF_Total");
  }
    
  newT->Branch("hadFake_sf_Nominal","vector<float>",&m_hadFake_sf_Nominal);
  newT->Branch("hadFake_sf_ttbarModelling_Sherpa","vector<float>",&m_hadFake_sf_ttbarModelling_Sherpa);
  newT->Branch("hadFake_sf_ttbarModelling_ISRFSRUp","vector<float>",&m_hadFake_sf_ttbarModelling_ISRFSRUp);
  newT->Branch("hadFake_sf_ttbarModelling_ISRFSRDn","vector<float>",&m_hadFake_sf_ttbarModelling_ISRFSRDn);
  newT->Branch("hadFake_sf_BkgSubtraction_ttgamma","vector<float>",&m_hadFake_sf_BkgSubtraction_ttgamma);
  newT->Branch("hadFake_sf_BkgSubtraction_rest","vector<float>",&m_hadFake_sf_BkgSubtraction_rest);
  if(hadFake_sf_applied){
    _hadFake_sf_conv_Nominal = (TH1F*)file->Get("hfakeSF_conv_Nominal");
    _hadFake_sf_conv_ttbarModelling_Sherpa = (TH1F*)file->Get("hfakeSF_conv_ttbarModelling_Sherpa");
    _hadFake_sf_conv_ttbarModelling_ISRFSRUp = (TH1F*)file->Get("hfakeSF_conv_ttbarModelling_ISRFSRUp");
    _hadFake_sf_conv_ttbarModelling_ISRFSRDown = (TH1F*)file->Get("hfakeSF_conv_ttbarModelling_ISRFSRDown");
    _hadFake_sf_conv_BkgSubtraction_ttgamma = (TH1F*)file->Get("hfakeSF_conv_BkgSubtraction_ttgamma");
    _hadFake_sf_conv_BkgSubtraction_rest = (TH1F*)file->Get("hfakeSF_conv_BkgSubtraction_rest");
    _hadFake_sf_unconv_Nominal = (TH1F*)file->Get("hfakeSF_unconv_Nominal");
    _hadFake_sf_unconv_ttbarModelling_Sherpa = (TH1F*)file->Get("hfakeSF_unconv_ttbarModelling_Sherpa");
    _hadFake_sf_unconv_ttbarModelling_ISRFSRUp = (TH1F*)file->Get("hfakeSF_unconv_ttbarModelling_ISRFSRUp");
    _hadFake_sf_unconv_ttbarModelling_ISRFSRDown = (TH1F*)file->Get("hfakeSF_unconv_ttbarModelling_ISRFSRDown");
    _hadFake_sf_unconv_BkgSubtraction_ttgamma = (TH1F*)file->Get("hfakeSF_unconv_BkgSubtraction_ttgamma");
    _hadFake_sf_unconv_BkgSubtraction_rest = (TH1F*)file->Get("hfakeSF_unconv_BkgSubtraction_rest");
  }

  newT->Branch("jet_pt_1st_correct",&m_jet_pt_1st_correct);   
  newT->Branch("jet_pt_2nd_correct",&m_jet_pt_2nd_correct);   
  newT->Branch("jet_pt_3rd_correct",&m_jet_pt_3rd_correct);   
  newT->Branch("jet_pt_4th_correct",&m_jet_pt_4th_correct);   
  newT->Branch("jet_pt_5th_correct",&m_jet_pt_5th_correct);   
  newT->Branch("jet_pt_6th_correct",&m_jet_pt_6th_correct);   

  newT->Branch("jet_tagWeightBin_leading_correct",&m_jet_tagWeightBin_leading_correct);   
  newT->Branch("jet_tagWeightBin_subleading_correct",&m_jet_tagWeightBin_subleading_correct);   
  newT->Branch("jet_tagWeightBin_subsubleading_correct",&m_jet_tagWeightBin_subsubleading_correct);   

  newT->Branch("event_ELD_MVA_all_correct","vector<float>",&m_event_ELD_MVA_all_correct);   
  newT->Branch("event_ELD_MVA_correct",&m_event_ELD_MVA_correct);   

  newT->Branch("dPhi_lep",&m_dPhi_lep);   
  newT->Branch("dEta_lep",&m_dEta_lep);   


  activateBranches(fChain_func);

  for (int event = 0; event < nentries; event++) {
    
    fChain_func->GetEntry(event);
    loadBar(event, nentries, 100, 50);


    // Add the lep delta phi and delta eta variable
    m_dPhi_lep=0;
    m_dEta_lep=0;
    TLorentzVector lep1;
    TLorentzVector lep2;
    if(is_ee){
    lep1.SetPtEtaPhiE(el_pt->at(0),el_eta->at(0),el_phi->at(0),el_e->at(0)); 
    lep2.SetPtEtaPhiE(el_pt->at(1),el_eta->at(1),el_phi->at(1),el_e->at(1)); 
    }
    else if(is_emu){
    lep1.SetPtEtaPhiE(el_pt->at(0),el_eta->at(0),el_phi->at(0),el_e->at(0));
    lep2.SetPtEtaPhiE(mu_pt->at(0),mu_eta->at(0),mu_phi->at(0),mu_e->at(0));
    }
    else if(is_mumu){
    lep1.SetPtEtaPhiE(mu_pt->at(0),mu_eta->at(0),mu_phi->at(0),mu_e->at(0));
    lep2.SetPtEtaPhiE(mu_pt->at(1),mu_eta->at(1),mu_phi->at(1),mu_e->at(1));
    }

    m_dPhi_lep=lep1.DeltaPhi(lep2);
    m_dEta_lep=lep1.Eta()-lep2.Eta();

    m_jet_pt_1st_correct=0;
    m_jet_pt_2nd_correct=0;
    m_jet_pt_3rd_correct=0;
    m_jet_pt_4th_correct=0;
    m_jet_pt_5th_correct=0;
    m_jet_pt_6th_correct=0;
    
    // Get certain jets 
    for(uint jetn = 0; jetn < jet_pt->size();jetn++){
      try {
        m_jet_pt_1st_correct = jet_pt->at(0);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_2nd_correct = jet_pt->at(1);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_3rd_correct = jet_pt->at(2);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_4th_correct = jet_pt->at(3);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_5th_correct = jet_pt->at(4);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_6th_correct = jet_pt->at(5);
        } catch(const std::out_of_range& oor) {
        continue;
        }
    }

    // Sort btag weigths and add to mbranch // 
    m_jet_tagWeightBin_leading_correct=-2;
    m_jet_tagWeightBin_subleading_correct=-2;
    m_jet_tagWeightBin_subsubleading_correct=-2;


    std::sort (jet_tagWeightBin->begin(), jet_tagWeightBin->end(), std::greater<int>()); 

    for (uint sorted = 0; sorted < jet_tagWeightBin->size(); sorted++) {
      try {
      m_jet_tagWeightBin_leading_correct = jet_tagWeightBin->at(0);
      } catch(const std::out_of_range& oor) {
        continue;
      }
      try {
      m_jet_tagWeightBin_subleading_correct = jet_tagWeightBin->at(1);
      } catch(const std::out_of_range& oor) {
        continue;
      }
     try {
      m_jet_tagWeightBin_subsubleading_correct = jet_tagWeightBin->at(2);
      } catch(const std::out_of_range& oor) {
        continue;
      }
    }

    m_event_ELD_MVA_all_correct->resize(ph_pt->size());
    m_ph_kfactor_correct->resize(ph_pt->size());
    m_efake_sf_Nominal->resize(ph_pt->size());
    m_efake_sf_RangeDown->resize(ph_pt->size());
    m_efake_sf_BkgFunc->resize(ph_pt->size());
    m_efake_sf_SigFunc->resize(ph_pt->size());
    m_efake_sf_TypeC->resize(ph_pt->size());
    m_efake_sf_Stat_Pt2Eta4->resize(ph_pt->size());
    m_efake_sf_Stat_Pt3Eta3->resize(ph_pt->size());
    m_efake_sf_Stat_Pt4Eta1->resize(ph_pt->size());
    m_efake_sf_Stat_Pt4Eta2->resize(ph_pt->size());
    m_efake_sf_Stat_Pt4Eta3->resize(ph_pt->size());
    m_efake_sf_Stat_Pt4Eta5->resize(ph_pt->size());
    m_efake_sf_Total->resize(ph_pt->size());
    m_hadFake_sf_Nominal->resize(ph_pt->size());
    m_hadFake_sf_ttbarModelling_Sherpa->resize(ph_pt->size());
    m_hadFake_sf_ttbarModelling_ISRFSRUp->resize(ph_pt->size());
    m_hadFake_sf_ttbarModelling_ISRFSRDn->resize(ph_pt->size());
    m_hadFake_sf_BkgSubtraction_ttgamma->resize(ph_pt->size());
    m_hadFake_sf_BkgSubtraction_rest->resize(ph_pt->size());

    for(int photon = 0 ; photon < ph_pt->size(); photon++){
      m_event_ELD_MVA_all_correct->at(photon)=-99;

      m_NeuralNet_input_values["jet_tagWeightBin_leading_correct"] = m_jet_tagWeightBin_leading_correct;
      m_NeuralNet_input_values["jet_tagWeightBin_subleading_correct"] = m_jet_tagWeightBin_subleading_correct;
      m_NeuralNet_input_values["jet_tagWeightBin_subsubleading_correct"] = m_jet_tagWeightBin_subsubleading_correct;

      m_NeuralNet_input_values["jet_pt_1st_correct"] = m_jet_pt_1st_correct;
      m_NeuralNet_input_values["jet_pt_2nd_correct"] = m_jet_pt_2nd_correct;
      m_NeuralNet_input_values["jet_pt_3rd_correct"] = m_jet_pt_3rd_correct;
      m_NeuralNet_input_values["jet_pt_4th_correct"] = m_jet_pt_4th_correct;
      m_NeuralNet_input_values["jet_pt_5th_correct"] = m_jet_pt_5th_correct;
      m_NeuralNet_input_values["jet_pt_6th_correct"] = m_jet_pt_6th_correct;

      // Photon variables
      m_NeuralNet_input_values["ph_mgammalept_sel"] = ph_mgammalept->at(photon);
      m_NeuralNet_input_values["ph_drsubljet_sel"] = ph_drsubljet->at(photon);
      m_NeuralNet_input_values["ph_drlept_sel"] = ph_drlept->at(photon);
      m_NeuralNet_input_values["ph_drleadjet_sel"] = ph_drleadjet->at(photon);

      m_NeuralNet_input_values["ph_e_sel"] = ph_e->at(photon);
      m_NeuralNet_input_values["ph_phi_sel"] = ph_phi->at(photon);
      m_NeuralNet_input_values["ph_mgammaleptlept_sel"] = ph_mgammaleptlept->at(photon);
      m_NeuralNet_input_values["ph_HFT_MVA_sel"] = ph_HFT_MVA->at(photon);
      m_NeuralNet_input_values["ph_isoFCT_sel"] = ph_isoFCT->at(photon);
      m_NeuralNet_input_values["ph_SF_iso_sel"] = ph_SF_iso->at(photon);
      m_NeuralNet_input_values["ph_SF_eff_sel"] = ph_SF_eff->at(photon);

      m_NeuralNet_input_values["event_mwt"] = event_mwt;
      m_NeuralNet_input_values["event_nbjets77"] = event_nbjets77;
      m_NeuralNet_input_values["met_met"] = met_met;
      m_NeuralNet_input_values["met_phi"] = met_phi;
      m_NeuralNet_input_values["event_HT"] = event_HT;
      m_NeuralNet_input_values["event_njets"] = event_njets;
      m_NeuralNet_input_values["event_mll"] = event_mll;


      // Calculate lwtnn NN output
      auto out_vals = neuralNet->compute(m_NeuralNet_input_values);
      for (const auto& out: out_vals) {
        //std::cout<<"MVA all = "<< out.second << std::endl;
        m_event_ELD_MVA_all_correct->at(photon) = out.second;
      }
      
      // How we handle PPT weights
      if(ppt_systematics_applied){
        float PPT_x_value = ph_HFT_MVA->at(photon);

        // Hfake derive fit weight
        TF1 *_ppt_hfake_fit = (TF1*)_ppt_hfake->GetFunction("pol1");
        m_weight_PPT_hfake_fit = _ppt_hfake_fit->Eval(PPT_x_value);
        // Hfake derive bin weight
        int hfake_bin_number = _ppt_hfake->GetXaxis()->FindBin(PPT_x_value);
        m_weight_PPT_hfake_bin = _ppt_hfake->GetBinContent(hfake_bin_number);

        // Prompt derive fit weight
        TF1 *_ppt_prompt_fit = (TF1*)_ppt_prompt->GetFunction("pol1");
        m_weight_PPT_prompt_fit = _ppt_prompt_fit->Eval(PPT_x_value);
        // Prompt derive bin weight
        int promt_bin_number = _ppt_prompt->GetXaxis()->FindBin(PPT_x_value);
        m_weight_PPT_prompt_bin = _ppt_prompt->GetBinContent(promt_bin_number);
        
      }
      delete _ppt_hfake_fit;
      delete _ppt_prompt_fit;
      
      // Add in the Kfactor weights
      m_ph_kfactor_correct->at(photon)=1;
      if(kfactor_applied){
        float photon_pt = ph_pt->at(photon)*0.001;
        if(is_singlelepton){
          int kfactor_pt_bin_number = _h_kfactor_sl->GetXaxis()->FindBin(photon_pt);
          if (photon_pt >= _h_kfactor_sl->GetXaxis()->GetXmax())
            kfactor_pt_bin_number = _h_kfactor_sl->GetXaxis()->GetLast();
          m_ph_kfactor_correct->at(photon) = _h_kfactor_sl->GetBinContent(kfactor_pt_bin_number);
        }
        if (is_dilepton){
          int kfactor_pt_bin_number = _h_kfactor_dl->GetXaxis()->FindBin(photon_pt);
          if (photon_pt >= _h_kfactor_dl->GetXaxis()->GetXmax())
            kfactor_pt_bin_number = _h_kfactor_dl->GetXaxis()->GetLast();
          m_ph_kfactor_correct->at(photon) = _h_kfactor_dl->GetBinContent(kfactor_pt_bin_number);
        }
      }
      
      // Add in the eamma fake SFs
      m_efake_sf_Nominal->at(photon)=1;
      m_efake_sf_RangeDown->at(photon)=1;
      m_efake_sf_BkgFunc->at(photon)=1;
      m_efake_sf_SigFunc->at(photon)=1;
      m_efake_sf_TypeC->at(photon)=1;
      m_efake_sf_Stat_Pt2Eta4->at(photon)=1;
      m_efake_sf_Stat_Pt3Eta3->at(photon)=1;
      m_efake_sf_Stat_Pt4Eta1->at(photon)=1;
      m_efake_sf_Stat_Pt4Eta2->at(photon)=1;
      m_efake_sf_Stat_Pt4Eta3->at(photon)=1;
      m_efake_sf_Stat_Pt4Eta5->at(photon)=1;
      m_efake_sf_Total->at(photon)=1;
      if(efake_sf_applied){
        float photon_pt = ph_pt->at(photon)*0.001;
        float photon_eta = fabs(ph_eta->at(photon));
        int efake_sf_eta_bin_number = _h_efake_sf_Nominal->GetXaxis()->FindBin(photon_eta);
        int efake_sf_pt_bin_number = _h_efake_sf_Nominal->GetYaxis()->FindBin(photon_pt);
        if (efake_sf_eta_bin_number > _h_efake_sf_Nominal->GetNbinsX()) efake_sf_eta_bin_number = _h_efake_sf_Nominal->GetNbinsX();
        if (efake_sf_pt_bin_number > _h_efake_sf_Nominal->GetNbinsY()) efake_sf_pt_bin_number = _h_efake_sf_Nominal->GetNbinsY();

        m_efake_sf_Nominal->at(photon) = _h_efake_sf_Nominal->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Nominal->at(photon) = _h_efake_sf_Nominal->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_RangeDown->at(photon) = _h_efake_sf_RangeDown->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_BkgFunc->at(photon) = _h_efake_sf_BkgFunc->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_SigFunc->at(photon) = _h_efake_sf_SigFunc->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_TypeC->at(photon) = _h_efake_sf_TypeC->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt2Eta4->at(photon) = _h_efake_sf_Stat_Pt2Eta4->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt3Eta3->at(photon) = _h_efake_sf_Stat_Pt3Eta3->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt4Eta1->at(photon) = _h_efake_sf_Stat_Pt4Eta1->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt4Eta2->at(photon) = _h_efake_sf_Stat_Pt4Eta2->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt4Eta3->at(photon) = _h_efake_sf_Stat_Pt4Eta3->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Stat_Pt4Eta5->at(photon) = _h_efake_sf_Stat_Pt4Eta5->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
        m_efake_sf_Total->at(photon) = _h_efake_sf_Total->GetBinContent(efake_sf_eta_bin_number, efake_sf_pt_bin_number);
      }
      
      // Add in the hadronic fake SFs
      m_hadFake_sf_Nominal->at(photon) = 1;
      m_hadFake_sf_ttbarModelling_Sherpa->at(photon) = 1;
      m_hadFake_sf_ttbarModelling_ISRFSRUp->at(photon) = 1;
      m_hadFake_sf_ttbarModelling_ISRFSRDn->at(photon) = 1;
      m_hadFake_sf_BkgSubtraction_ttgamma->at(photon) = 1;
      m_hadFake_sf_BkgSubtraction_rest->at(photon) = 1;

      if(hadFake_sf_applied)
      {
        //Apply had-fake SF only for tight and isolated photons:
        if( ph_isTight->at(photon) && ph_isoFCT->at(photon))
        {
          float pt = ph_pt->at(photon)*1000;
          float absEta = fabs(ph_eta->at(photon));
          int bin_number = 0;

          if(ph_conversionType->at(photon)==0)
          { //Unconverted photons:
            if(absEta<0.60){
              if(pt>=20 && pt<30) bin_number = 1;
              if(pt>=30) bin_number = 2;
            }
            if(absEta>=0.60 && absEta<1.37){
              if(pt>=20 && pt<30) bin_number = 3;
              if(pt>=30) bin_number = 4;
            }
            if(absEta>1.52 && absEta<=2.37){
              bin_number = 5;
            }
            if(bin_number!=0){
              m_hadFake_sf_Nominal->at(photon) = _hadFake_sf_unconv_Nominal->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_Sherpa->at(photon) = _hadFake_sf_unconv_ttbarModelling_Sherpa->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_ISRFSRUp->at(photon) = _hadFake_sf_unconv_ttbarModelling_ISRFSRUp->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_ISRFSRDn->at(photon) = _hadFake_sf_unconv_ttbarModelling_ISRFSRDown->GetBinContent(bin_number);
              m_hadFake_sf_BkgSubtraction_ttgamma->at(photon) = _hadFake_sf_unconv_BkgSubtraction_ttgamma->GetBinContent(bin_number);
              m_hadFake_sf_BkgSubtraction_rest->at(photon) = _hadFake_sf_unconv_BkgSubtraction_rest->GetBinContent(bin_number);
            }
          }
          else if (ph_conversionType->at(photon)==1 || ph_conversionType->at(photon)==2 || ph_conversionType->at(photon)==3 || ph_conversionType->at(photon)==4 || ph_conversionType->at(photon)==5)
          { //Converted photons:
            if(absEta<0.60)
              bin_number = 1;
            if(absEta>=0.60 && absEta<1.37){
              if(pt>=20 && pt<30) bin_number = 2;
              if(pt>=30) bin_number = 3;
            }
            if(absEta>1.52 && absEta<=2.37){
              if(pt>=20 && pt<50) bin_number = 4;
              if(pt>=50) bin_number = 5;
            }
            if(bin_number!=0){
              m_hadFake_sf_Nominal->at(photon) = _hadFake_sf_conv_Nominal->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_Sherpa->at(photon) = _hadFake_sf_conv_ttbarModelling_Sherpa->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_ISRFSRUp->at(photon) = _hadFake_sf_conv_ttbarModelling_ISRFSRUp->GetBinContent(bin_number);
              m_hadFake_sf_ttbarModelling_ISRFSRDn->at(photon) = _hadFake_sf_conv_ttbarModelling_ISRFSRDown->GetBinContent(bin_number);
              m_hadFake_sf_BkgSubtraction_ttgamma->at(photon) = _hadFake_sf_conv_BkgSubtraction_ttgamma->GetBinContent(bin_number);
              m_hadFake_sf_BkgSubtraction_rest->at(photon) = _hadFake_sf_conv_BkgSubtraction_rest->GetBinContent(bin_number);
            }
          } 
        }
      }


    } // end loop over photons

      // Save good photons in ELD as cross check
    if(selph_index1 >= 0) {
      m_event_ELD_MVA_correct = m_event_ELD_MVA_all_correct->at(selph_index1);
    }


    newT->Fill();


  }// end event loop


}// end add_nn loop

int main(int argc, char** argv)
{
  // gROOT->ProcessLine( "gErrorIgnoreLevel = kFatal;");

  // path to ntuples from AnalysisTop
  // Where we read from:
  string path = "root://eosatlas//eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v010/CR1S/";
  //string path = "root://eosatlas//eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v010/SR1S/";//FIX ME!
  //string path = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v010/QE2/p3315/";
  //string channels[] ={"ee","emu","mumu"};
  string channels[] ={"ejets"};

  // Where we save to:
  // string myPath = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_flattened/CR1S/";
  string myPath = "root://eosatlas//eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v010_february18/CR1S/";
  //string myPath = "/afs/cern.ch/user/g/ghasemi/test/";//FIX ME! 
  //string myPath = "root://eosatlas//eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v010_february18/QE2/";


  std::cout << "Found " << argc-1 << " files to run over:" << std::endl;
  std::string in_file_name;
  for(const string &ch : channels){
    if(ch=="ejets" || ch=="mujets"){
      in_file_name=("model4_150_singlelepton_ELD.json");
    } 
    else if(ch=="ee" || ch=="mumu" || ch=="emu"){
      in_file_name=("model4_300_dilepton_ELD.json");
    }
  }

  std::ifstream in_file(in_file_name);
  if(!in_file){
    std::cout<<"Error: no nn input file!"<< std::endl;
  }


  m_config_netFile = new lwt::JSONConfig(lwt::parse_json(in_file));
  std::cout << ": "<<in_file_name << " has " << m_config_netFile->layers.size() << " layers"<< std::endl;
  m_neuralNet = new lwt::LightweightNeuralNetwork(m_config_netFile->inputs, 
  m_config_netFile->layers, m_config_netFile->outputs);


  for (int i = 1; i < argc; ++i) {
    for(const string &c : channels){

      TFile *newfile=nullptr;
      TFile *oldFile=nullptr;


      string filename = argv[i];
      string file = path+c+"/"+filename;
      std::cout<<c<<": Reading from "<<path<< std::endl;
      string newpath = myPath + c+"/"+filename;
      std::cout<<c<<": "<< filename<< std::endl;
      std::cout<<c<<": Saving to "<<newpath<< std::endl;

      newfile = new TFile((newpath.c_str()), "recreate");

      // If singlelepton, add PPT systs. If not, defualt value is 1
      if ( (c.find("ejets") != std::string::npos) ||
           (c.find("mujets") != std::string::npos) ){
        m_add_ppt_systematics(newfile,"weights_PPT-2018-02-08-1.root");
      }

      // reset some variables:
      is_singlelepton=false;
      is_dilepton=false;
      is_ee=false;
      is_emu=false;
      is_mumu=false;

      if ( (c.find("ejets") != std::string::npos) ||
          (c.find("mujets") != std::string::npos) ){
          is_singlelepton=true;
      }
      else if (c.find("ee") != std::string::npos){
          is_dilepton=true;
          is_ee=true;
      }
      else if (c.find("emu") != std::string::npos){
          is_dilepton=true;
          is_emu=true;
      }
      else if (c.find("mumu") != std::string::npos){
          is_dilepton=true;
          is_mumu=true;
      }

      // If ttgamma add the kfactors
      if(filename.find("ttgamma") != std::string::npos){
        m_add_kfactor(newfile,
          "kfactor_sinlepton_theory_fineBin.root",
          "kfactor_dilepton_theory_fineBin.root");
      }

      // add efake sf files
        m_add_efake_sf(newfile,
          "EFakeSFs_Final.root");
      
      // add hadronic fake sf files
      m_add_hadFake_sf( newfile, "hfake_SF_final_3D.root" );

      oldFile = new TFile((file.c_str()), "read");

      // Do a loop over all trees
      TList* list = oldFile->GetListOfKeys() ;
      if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
      TIter next(list) ;
      TKey* key ;
      TObject* obj ;
          

      std::string oldkeyname;
      while ( (key = (TKey*)next()) ) {

        bool alreadyseen = (oldkeyname == key->GetName());

        if (alreadyseen){
        	continue;
      	}
      	oldkeyname = key->GetName();
      	TChain *fChain=nullptr;
        TTree *newtree=nullptr;

        obj = key->ReadObj() ;
        if ( (strcmp(obj->IsA()->GetName(),"TTree")!=0) || (strcmp("sumWeights",obj->GetName()) == 0)) {
          printf("Not running over: %s \n",obj->GetName()); continue; 
        }
        printf("#####################################\n");
        printf("Currently working on %s \n",obj->GetName());
        printf("#####################################\n");

        fChain = new TChain(obj->GetName());
   
        fChain->Add((file).c_str());
        newfile->cd(); // Make sure we are in new file otherwise shit breaks.
        newtree = fChain->CloneTree(0); // We get 0 entries here, because we fill it later
       if(fChain->GetEntries() == 0){
         std::cout<<"No events, skipping"<<std::endl;
         delete newtree;
         delete fChain;
         continue;
       }
        m_add_branches(fChain,newtree,m_neuralNet,newfile);

        newfile->cd();
        newtree->Write();

        delete newtree;
        delete fChain;

      } // end loop over trees
      delete newfile;
      delete oldFile;
    } // end  loop over channels
  } // end loop over files

  return 0;
}
