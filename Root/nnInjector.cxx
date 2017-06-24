//////////////////////////////
//Joshua.Wyatt.Smith@cern.ch//
//////////////////////////////
#include "nnInjector.h"
#include <iostream>
#include <memory>

using namespace std;


void m_nan_cleaner_upper(vector<float> *variable){
  for(uint i = 0; i < variable->size(); i++){
    std::cout << variable->at(i) <<std::endl;
  }
}

void m_add_branches(
  TChain *fChain, 
  TTree *newtree,
  lwt::LightweightNeuralNetwork *neuralNet){

  int nentries = fChain->GetEntries();

  std::cout<< nentries << " entries" << std::endl;

  // Define some new branches and activate all others //
 //  ///////////////////// For multiclass ////////////////////////
  // newtree->Branch("ph_ISR_MVA",&m_ph_ISR_MVA,"m_ph_ISR_MVA/F");
  // newtree->Branch("ph_FSR_MVA",&m_ph_FSR_MVA,"m_ph_FSR_MVA/F");
  // newtree->Branch("ph_HFake_MVA",&m_ph_HFake_MVA,"m_ph_HFake_MVA/F");
  // newtree->Branch("ph_eFake_MVA",&m_ph_eFake_MVA,"m_ph_eFake_MVA/F");
  // newtree->Branch("ph_OtherPrompt_MVA",&m_ph_OtherPrompt_MVA,"m_ph_OtherPrompt_MVA/F");   
  //////////////////For Prompt photon tagger ////////////////////
    // newtree->Branch("ph_PPT_MVA",&m_ph_PPT_MVA);   
  //////////////////For Prompt photon tagger ////////////////////
  newtree->Branch("event_ELT_MVA",&m_event_ELT_MVA);   
  ////////////////// Branches sorted by btag weight ////////////////////
  // newtree->Branch("jet_tagWeightBin_leading_temp",&jet_tagWeightBin_leading_temp);   
  // newtree->Branch("jet_tagWeightBin_subleading_temp",&jet_tagWeightBin_subleading_temp);   
  // newtree->Branch("jet_tagWeightBin_subsubleading_temp",&jet_tagWeightBin_subsubleading_temp); 
  //////////////////////////////////////////////////////

  activateBranches(fChain);

  for (int event = 0; event < nentries; event++) {

    fChain->GetEntry(event);
    loadBar(event, nentries, 100, 50);

//*weight_mc*weight_pileup*ph_SF_eff_sel*ph_SF_iso_sel*weight_leptonSF*weight_jvt*weight_bTagSF_Continuous*event_norm * event_lumi
    m_NeuralNet_input_values["jet_tagWeightBin_leading"] = jet_tagWeightBin_leading;
    m_NeuralNet_input_values["jet_tagWeightBin_subleading"] = jet_tagWeightBin_subleading;
    m_NeuralNet_input_values["jet_tagWeightBin_subsubleading"] = jet_tagWeightBin_subsubleading;

    m_NeuralNet_input_values["jet_pt_1st"] = jet_pt_1st;
    m_NeuralNet_input_values["jet_pt_2nd"] = jet_pt_2nd;
    m_NeuralNet_input_values["jet_pt_3rd"] = jet_pt_3rd;
    m_NeuralNet_input_values["jet_pt_4th"] = jet_pt_4th;
    m_NeuralNet_input_values["jet_pt_5th"] = jet_pt_5th;
    // m_NeuralNet_input_values["jet_pt_6th"] = jet_pt_6th;

    m_NeuralNet_input_values["event_mwt"] = event_mwt;
    m_NeuralNet_input_values["event_nbjets77"] = event_nbjets77;
    m_NeuralNet_input_values["met_met"] = met_met;
    // m_NeuralNet_input_values["met_phi"] = met_phi;
    m_NeuralNet_input_values["event_HT"] = event_HT;
    m_NeuralNet_input_values["event_njets"] = event_njets;
    // m_NeuralNet_input_values["event_mll"] = event_mll;

    // Photon variabes
    // m_NeuralNet_input_values["ph_mgammalept_sel"] = ph_mgammalept_sel;
    m_NeuralNet_input_values["ph_drsubljet_sel"] = ph_drsubljet_sel;
    m_NeuralNet_input_values["ph_drlept_sel"] = ph_drlept_sel;
    m_NeuralNet_input_values["ph_drleadjet_sel"] = ph_drleadjet_sel;

    m_NeuralNet_input_values["ph_e_sel"] = ph_e_sel;
    m_NeuralNet_input_values["ph_phi_sel"] = ph_phi_sel;
    // m_NeuralNet_input_values["ph_mgammaleptlept_sel"] = ph_mgammaleptlept_sel;
    m_NeuralNet_input_values["ph_HFT_MVA_sel"] = ph_HFT_MVA_sel;
    // m_NeuralNet_input_values["ph_isoFCT_sel"] = ph_isoFCT_sel;
    // m_NeuralNet_input_values["ph_SF_iso_sel"] = ph_SF_iso_sel;
    // m_NeuralNet_input_values["ph_SF_eff_sel"] = ph_SF_eff_sel;
 
    // std::cout << "jet_tagWeightBin_leading = " << jet_tagWeightBin_leading << std::endl; 
    // std::cout << "jet_tagWeightBin_subleading = " << jet_tagWeightBin_subleading << std::endl; 
    // std::cout << "jet_tagWeightBin_subsubleading = " << jet_tagWeightBin_subsubleading << std::endl; 

    // std::cout << "jet_pt_1st = " << jet_pt_1st << std::endl; 
    // std::cout << "jet_pt_2nd = " << jet_pt_2nd << std::endl; 
    // std::cout << "jet_pt_3rd = " << jet_pt_3rd << std::endl; 
    // std::cout << "jet_pt_4th = " << jet_pt_4th << std::endl; 
    // std::cout << "jet_pt_5th = " << jet_pt_5th << std::endl; 
    // // std::cout << "jet_pt_6th = " << jet_pt_6th << std::endl; 

    // std::cout << "event_mwt = " << event_mwt << std::endl; 
    // std::cout << "event_nbjets77 = " << event_nbjets77 << std::endl; 
    // std::cout << "met_met = " << met_met << std::endl; 
    // std::cout << "event_HT = " << event_HT << std::endl; 
    // std::cout << "event_njets = " << event_njets << std::endl; 

 
    // std::cout << "ph_drsubljet_sel = " << ph_drsubljet_sel << std::endl; 
    // std::cout << "ph_drlept_sel = " << ph_drlept_sel << std::endl; 
    // std::cout << "ph_e_sel = " << ph_e_sel << std::endl; 
    // std::cout << "ph_phi_sel = " << ph_phi_sel << std::endl; 
    // std::cout << "ph_drleadjet_sel = " << ph_drleadjet_sel << std::endl; 
    // std::cout << "ph_HFT_MVA_sel = " << ph_HFT_MVA_sel << std::endl; 


    // Fill the tree before calculating NN
    // Calculate lwtnn NN output
    auto out_vals = neuralNet->compute(m_NeuralNet_input_values);
    for (const auto& out: out_vals) {
      //std::cout<<"MVA = "<< out.second << std::endl;
      m_event_ELT_MVA = out.second;
    }

    newtree->Fill();

  }// end event loop


}// end add_nn loop

int main(int argc, char** argv)
{
  // gROOT->ProcessLine( "gErrorIgnoreLevel = kFatal;");
  std::cout << "Found " << argc-1 << " files to run over:" << std::endl;
  std::string in_file_name("../json/model13b_600_singlelepton_ELD.json");
  std::ifstream in_file(in_file_name);
  if(!in_file){
    std::cout<<"Error: no nn input file!"<< std::endl;
  }



  // path to ntuples from AnalysisTop
  // string path = "/eos/atlas/user/c/caudron/TtGamma_ntuples/v007/SR1/";
  // string path = "/eos/atlas/user/c/caudron/TtGamma_ntuples/v007/SR1/";
  // Where we read from:
  //string path ="/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007_btagVar/CR1/";
  string path ="/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007_flattened/SR1/";
  // string path = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007/QE2/";
  //string channels[] ={"ejets","mujets"};
  string channels[] ={"ejets", "mujets"};
  // Where we save to:
  //string myPath = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007_btagVar_w_ELT_with_QCD/QE2/";
  string myPath = "../SR1/";


  TTree *newtree;
  TChain *fChain;
  TFile *newfile;
  lwt::LightweightNeuralNetwork *neuralNet;
  lwt::JSONConfig  config_netFile = lwt::parse_json(in_file);
  std::cout << "Neural Network has " << config_netFile.layers.size() << " layers"<< std::endl;

  for (int i = 1; i < argc; ++i) {
    for(const string &c : channels){


      neuralNet = new lwt::LightweightNeuralNetwork(config_netFile.inputs, 
      config_netFile.layers, config_netFile.outputs);


      string filename = argv[i];
      string file = path+c+"/"+filename;
      string newpath = myPath + c+"/"+filename;
      std::cout<<c<<": "<< filename<< std::endl;
      std::cout<<c<<"Saving to "<<newpath<< std::endl;

      newfile = new TFile((newpath.c_str()), "update");

      fChain = new TChain("nominal");
 
      fChain->Add((file).c_str());
      newtree = fChain->CloneTree(0);
      if(fChain->GetEntries() == 0){
        std::cout<<"No events, skipping"<<std::endl;
        continue;
      }
      m_add_branches(fChain,newtree,neuralNet);
      newfile->cd();
      newtree->Write();
      newfile->Close();
    }
  }

  return 0;
}
