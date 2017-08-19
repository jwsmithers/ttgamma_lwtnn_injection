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
  TChain *fChain_func, 
  TTree *newT,
  lwt::LightweightNeuralNetwork *neuralNet){

  int nentries = fChain_func->GetEntries();

  std::cout<< nentries << " entries" << std::endl;

  newT->Branch("jet_pt_1st_correct",&m_jet_pt_1st_correct);   
  newT->Branch("jet_pt_2nd_correct",&m_jet_pt_2nd_correct);   
  newT->Branch("jet_pt_3rd_correct",&m_jet_pt_3rd_correct);   
  newT->Branch("jet_pt_4th_correct",&m_jet_pt_4th_correct);   
  newT->Branch("jet_pt_5th_correct",&m_jet_pt_5th_correct);   
  newT->Branch("jet_pt_6th_correct",&m_jet_pt_6th_correct);   

  newT->Branch("ph_drsubljet_sel",&m_ph_drsubljet_sel);   
  newT->Branch("ph_drlept_sel",&m_ph_drlept_sel);   
  newT->Branch("ph_e_sel",&m_ph_e_sel);   
  newT->Branch("ph_phi_sel",&m_ph_phi_sel);   
  newT->Branch("ph_drleadjet_sel",&m_ph_drleadjet_sel);   
  newT->Branch("ph_mgammalept_sel",&m_ph_mgammalept_sel);   
  newT->Branch("ph_mgammaleptlept_sel",&m_ph_mgammaleptlept_sel);   
  newT->Branch("ph_HFT_MVA_sel",&m_ph_HFT_MVA_sel);   
  newT->Branch("ph_isoFCT_sel",&m_ph_isoFCT_sel);   

  newT->Branch("jet_tagWeightBin_leading_correct",&m_jet_tagWeightBin_leading_correct);   
  newT->Branch("jet_tagWeightBin_subleading_correct",&m_jet_tagWeightBin_subleading_correct);   
  newT->Branch("jet_tagWeightBin_subsubleading_correct",&m_jet_tagWeightBin_subsubleading_correct);   

  newT->Branch("ph_SF_eff_sel",&m_ph_SF_eff_sel);   
  newT->Branch("ph_SF_iso_sel",&m_ph_SF_iso_sel);   

  newT->Branch("event_ELD_MVA_all_correct","vector<float>",&m_event_ELD_MVA_all_correct);   
  newT->Branch("event_ELD_MVA_correct",&m_event_ELD_MVA_correct);   


  activateBranches(fChain_func);

  for (int event = 0; event < nentries; event++) {

    fChain_func->GetEntry(event);
    loadBar(event, nentries, 100, 50);

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
    } // end loop over photons

      // Save good photons
    if(selph_index1 >= 0) {
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
      m_event_ELD_MVA_correct = m_event_ELD_MVA_all_correct->at(selph_index1);
    }

    newT->Fill();


  }// end event loop


}// end add_nn loop

int main(int argc, char** argv)
{
  gROOT->ProcessLine( "gErrorIgnoreLevel = kFatal;");
  std::cout << "Found " << argc-1 << " files to run over:" << std::endl;
  //std::string in_file_name=("model4_300_dilepton_ELD.json");
  std::string in_file_name=("model4_150_singlelepton_ELD.json");
  std::ifstream in_file(in_file_name);

  if(!in_file){
    std::cout<<"Error: no nn input file!"<< std::endl;
  }

  // path to ntuples from AnalysisTop
  // Where we read from:
  string path = "root://eosuser//eos/user/c/caudron/TtGamma_ntuples/v009/CR1S/";
  //string path = "/eos/user/j/jwsmith/reprocessedNtuples/v009/QE2_yichen/";
  //string channels[] ={"ee","emu","mumu"};
  string channels[] ={"ejets"};

  // Where we save to:
  //string myPath = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_flattened/QE2/";
  string myPath = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_flattened/CR1S/";
  //string myPath = "../CR1/";


  m_config_netFile = new lwt::JSONConfig(lwt::parse_json(in_file));
  std::cout << ": "<<in_file_name << " has " << m_config_netFile->layers.size() << " layers"<< std::endl;
  m_neuralNet = new lwt::LightweightNeuralNetwork(m_config_netFile->inputs, 
  m_config_netFile->layers, m_config_netFile->outputs);


  for (int i = 1; i < argc; ++i) {
    for(const string &c : channels){

      TFile *newfile=nullptr;
      TFile *oldFile=nullptr;
      TTree *newtree_nominal=nullptr;
      TChain *fChain_nominal=nullptr;


      string filename = argv[i];
      string file = path+c+"/"+filename;
      std::cout<<c<<": Reading from "<<path<< std::endl;
      string newpath = myPath + c+"/"+filename;
      std::cout<<c<<": "<< filename<< std::endl;
      std::cout<<c<<": Saving to "<<newpath<< std::endl;

      newfile = new TFile((newpath.c_str()), "recreate");
      // Nominal tree
      if (filename.find("QCDfakes") != std::string::npos) {
        fChain_nominal = new TChain("nominal_Loose");
      }
      else {
        fChain_nominal = new TChain("nominal");
      }
 
      fChain_nominal->Add((file).c_str());


      newtree_nominal = fChain_nominal->CloneTree(0);
      if(fChain_nominal->GetEntries() == 0){
        std::cout<<"No events, skipping"<<std::endl;
        continue;
      }
      printf("#################################################\n");
      printf("Currently working on nominal tree (outside loop) \n");
      printf("#################################################\n");
      m_add_branches(fChain_nominal,newtree_nominal,m_neuralNet);

      newfile->cd();
      newtree_nominal->Write();
      delete newtree_nominal;
      delete fChain_nominal;
      

      oldFile = new TFile((file.c_str()), "read");


      // Do a loop over all trees that are not nominal
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
        if ( (strcmp(obj->IsA()->GetName(),"TTree")!=0) || (strcmp("sumWeights",obj->GetName()) == 0) 
          || (strcmp("nominal",obj->GetName()) == 0) || (strcmp("nominal_Loose",obj->GetName()) == 0)) {
          printf("Not running over: %s \n",obj->GetName()); continue; 
        }
        printf("#####################################\n");
        printf("Currently working on %s \n",obj->GetName());
        printf("#####################################\n");

        fChain = new TChain(obj->GetName());
   
        fChain->Add((file).c_str());

        newtree = fChain->CloneTree(0); // We get 0 entries here, because we fill it later
       if(fChain->GetEntries() == 0){
         std::cout<<"No events, skipping"<<std::endl;
         continue;
       }
        m_add_branches(fChain,newtree,m_neuralNet);

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
