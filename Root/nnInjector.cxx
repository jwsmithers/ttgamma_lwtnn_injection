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

  newtree->Branch("jet_pt_1st",&m_jet_pt_1st);   
  newtree->Branch("jet_pt_2nd",&m_jet_pt_2nd);   
  newtree->Branch("jet_pt_3rd",&m_jet_pt_3rd);   
  newtree->Branch("jet_pt_4th",&m_jet_pt_4th);   
  newtree->Branch("jet_pt_5th",&m_jet_pt_5th);   
  newtree->Branch("jet_pt_6th",&m_jet_pt_6th);   

  newtree->Branch("ph_drsubljet_sel",&m_ph_drsubljet_sel);   
  newtree->Branch("ph_drlept_sel",&m_ph_drlept_sel);   
  newtree->Branch("ph_e_sel",&m_ph_e_sel);   
  newtree->Branch("ph_phi_sel",&m_ph_phi_sel);   
  newtree->Branch("ph_drleadjet_sel",&m_ph_drleadjet_sel);   
  newtree->Branch("ph_mgammalept_sel",&m_ph_mgammalept_sel);   
  newtree->Branch("ph_mgammaleptlept_sel",&m_ph_mgammaleptlept_sel);   
  newtree->Branch("ph_HFT_MVA_sel",&m_ph_HFT_MVA_sel);   
  newtree->Branch("ph_isoFCT_sel",&m_ph_isoFCT_sel);   

  newtree->Branch("jet_tagWeightBin_leading",&m_jet_tagWeightBin_leading);   
  newtree->Branch("jet_tagWeightBin_subleading",&m_jet_tagWeightBin_subleading);   
  newtree->Branch("jet_tagWeightBin_subsubleading",&m_jet_tagWeightBin_subsubleading);   

  newtree->Branch("ph_SF_eff_sel",&m_ph_SF_eff_sel);   
  newtree->Branch("ph_SF_iso_sel",&m_ph_SF_iso_sel);   

  newtree->Branch("event_ELD_MVA",&m_event_ELD_MVA);   

  activateBranches(fChain);

  for (int event = 0; event < nentries; event++) {

    fChain->GetEntry(event);
    loadBar(event, nentries, 100, 50);
    
    if(selph_index1<0){continue;}

    // If we run on nominal samples we need to add variables.
    // if(Run_on_Full_Samples==true){
    // Get good photons
    m_ph_drsubljet_sel = ph_drsubljet->at(selph_index1);
    m_ph_drlept_sel = ph_drlept->at(selph_index1);
    m_ph_e_sel = ph_e->at(selph_index1);
    m_ph_phi_sel = ph_phi->at(selph_index1);
    m_ph_drleadjet_sel = ph_drleadjet->at(selph_index1);
    m_ph_mgammalept_sel = ph_mgammalept->at(selph_index1);
    m_ph_mgammaleptlept_sel = ph_mgammaleptlept->at(selph_index1);
    m_ph_HFT_MVA_sel = ph_HFT_MVA->at(selph_index1);
    m_ph_isoFCT_sel = ph_isoFCT->at(selph_index1);

    // Get good weights
    m_ph_SF_eff_sel = ph_SF_eff->at(selph_index1);
    m_ph_SF_iso_sel = ph_SF_iso->at(selph_index1);

    // Get certain jets 
    for(uint jetn = 0; jetn < jet_pt->size();jetn++){
      try {
        m_jet_pt_1st = jet_pt->at(0);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_2nd = jet_pt->at(1);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_3rd = jet_pt->at(2);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_4th = jet_pt->at(3);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_5th = jet_pt->at(4);
        } catch(const std::out_of_range& oor) {
        continue;
        }
      try {
        m_jet_pt_6th = jet_pt->at(5);
        } catch(const std::out_of_range& oor) {
        continue;
        }
    }

    // Sort btag weigths and add to mbranch // 
    std::sort (jet_tagWeightBin->begin(), jet_tagWeightBin->end(), std::greater<int>()); 

    for (uint sorted = 0; sorted < jet_tagWeightBin->size(); sorted++) {
      try {
      m_jet_tagWeightBin_leading = jet_tagWeightBin->at(0);
      } catch(const std::out_of_range& oor) {
        continue;
      }
      try {
      m_jet_tagWeightBin_subleading = jet_tagWeightBin->at(1);
      } catch(const std::out_of_range& oor) {
        continue;
      }
     try {
      m_jet_tagWeightBin_subsubleading = jet_tagWeightBin->at(2);
      } catch(const std::out_of_range& oor) {
        continue;
      }
    }

    m_NeuralNet_input_values["jet_tagWeightBin_leading"] = m_jet_tagWeightBin_leading;
    m_NeuralNet_input_values["jet_tagWeightBin_subleading"] = m_jet_tagWeightBin_subleading;
    m_NeuralNet_input_values["jet_tagWeightBin_subsubleading"] = m_jet_tagWeightBin_subsubleading;

    m_NeuralNet_input_values["jet_pt_1st"] = m_jet_pt_1st;
    m_NeuralNet_input_values["jet_pt_2nd"] = m_jet_pt_2nd;
    m_NeuralNet_input_values["jet_pt_3rd"] = m_jet_pt_3rd;
    m_NeuralNet_input_values["jet_pt_4th"] = m_jet_pt_4th;
    m_NeuralNet_input_values["jet_pt_5th"] = m_jet_pt_5th;
    m_NeuralNet_input_values["jet_pt_6th"] = m_jet_pt_6th;

    // Photon variabes
    m_NeuralNet_input_values["ph_mgammalept_sel"] = m_ph_mgammalept_sel;
    m_NeuralNet_input_values["ph_drsubljet_sel"] = m_ph_drsubljet_sel;
    m_NeuralNet_input_values["ph_drlept_sel"] = m_ph_drlept_sel;
    m_NeuralNet_input_values["ph_drleadjet_sel"] = m_ph_drleadjet_sel;

    m_NeuralNet_input_values["ph_e_sel"] = m_ph_e_sel;
    m_NeuralNet_input_values["ph_phi_sel"] = m_ph_phi_sel;
    m_NeuralNet_input_values["ph_mgammaleptlept_sel"] = m_ph_mgammaleptlept_sel;
    m_NeuralNet_input_values["ph_HFT_MVA_sel"] = m_ph_HFT_MVA_sel;
    m_NeuralNet_input_values["ph_isoFCT_sel"] = m_ph_isoFCT_sel;
    m_NeuralNet_input_values["ph_SF_iso_sel"] = m_ph_SF_iso_sel;
    m_NeuralNet_input_values["ph_SF_eff_sel"] = m_ph_SF_eff_sel;


   
    m_NeuralNet_input_values["event_mwt"] = event_mwt;
    m_NeuralNet_input_values["event_nbjets77"] = event_nbjets77;
    m_NeuralNet_input_values["met_met"] = met_met;
    m_NeuralNet_input_values["met_phi"] = met_phi;
    m_NeuralNet_input_values["event_HT"] = event_HT;
    m_NeuralNet_input_values["event_njets"] = event_njets;
    m_NeuralNet_input_values["event_mll"] = event_mll;


    // Fill the tree before calculating NN
    // Calculate lwtnn NN output
    auto out_vals = neuralNet->compute(m_NeuralNet_input_values);
    for (const auto& out: out_vals) {
      //std::cout<<"MVA = "<< out.second << std::endl;
      m_event_ELD_MVA = out.second;
    }

    newtree->Fill();

  }// end event loop


}// end add_nn loop

int main(int argc, char** argv)
{
  // gROOT->ProcessLine( "gErrorIgnoreLevel = kFatal;");
  std::cout << "Found " << argc-1 << " files to run over:" << std::endl;
  std::string in_file_name("../json/model2_400_dilepton_ELD.json");
  std::ifstream in_file(in_file_name);
  if(!in_file){
    std::cout<<"Error: no nn input file!"<< std::endl;
  }

  // path to ntuples from AnalysisTop
  // Where we read from:
  string path = "/eos/atlas/user/c/caudron/TtGamma_ntuples/v007/CR1/";
  //string path = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007/QE2/";
  //string channels[] ={"ejets"};
  string channels[] ={"ee", "emu","mumu"};
  // Where we save to:
  //string myPath = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007_btagVar_w_ELD_with_QCD/QE2/";
  string myPath = "../CR1/";


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

      //fChain = new TChain("nominal_Loose");
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
