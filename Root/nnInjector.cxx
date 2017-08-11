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

  newtree->Branch("event_ELD_MVA_correct",&m_event_ELD_MVA_correct);   


  activateBranches(fChain);

  for (int event = 0; event < nentries; event++) {

    fChain->GetEntry(event);
    loadBar(event, nentries, 100, 50);
    
      m_NeuralNet_input_values["jet_tagWeightBin_leading_correct"] = jet_tagWeightBin_leading_correct;
      m_NeuralNet_input_values["jet_tagWeightBin_subleading_correct"] = jet_tagWeightBin_subleading_correct;
      m_NeuralNet_input_values["jet_tagWeightBin_subsubleading_correct"] = jet_tagWeightBin_subsubleading_correct;

      m_NeuralNet_input_values["jet_pt_1st_correct"] = jet_pt_1st_correct;
      m_NeuralNet_input_values["jet_pt_2nd_correct"] = jet_pt_2nd_correct;
      m_NeuralNet_input_values["jet_pt_3rd_correct"] = jet_pt_3rd_correct;
      m_NeuralNet_input_values["jet_pt_4th_correct"] = jet_pt_4th_correct;
      m_NeuralNet_input_values["jet_pt_5th_correct"] = jet_pt_5th_correct;
      m_NeuralNet_input_values["jet_pt_6th_correct"] = jet_pt_6th_correct;

      // Photon variables
      m_NeuralNet_input_values["ph_mgammalept_sel"] = ph_mgammalept_sel;
      m_NeuralNet_input_values["ph_drsubljet_sel"] = ph_drsubljet_sel;
      m_NeuralNet_input_values["ph_drlept_sel"] = ph_drlept_sel;
      m_NeuralNet_input_values["ph_drleadjet_sel"] = ph_drleadjet_sel;

      m_NeuralNet_input_values["ph_e_sel"] = ph_e_sel;
      m_NeuralNet_input_values["ph_phi_sel"] = ph_phi_sel;
      m_NeuralNet_input_values["ph_mgammaleptlept_sel"] = ph_mgammaleptlept_sel;
      m_NeuralNet_input_values["ph_HFT_MVA_sel"] = ph_HFT_MVA_sel;
      m_NeuralNet_input_values["ph_isoFCT_sel"] = ph_isoFCT_sel;
      m_NeuralNet_input_values["ph_SF_iso_sel"] = ph_SF_iso_sel;
      m_NeuralNet_input_values["ph_SF_eff_sel"] = ph_SF_eff_sel;

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
        m_event_ELD_MVA_correct = out.second;
      }

    newtree->Fill();


  }// end event loop


}// end add_nn loop

int main(int argc, char** argv)
{
  //gROOT->ProcessLine( "gErrorIgnoreLevel = kFatal;");
  std::cout << "Found " << argc-1 << " files to run over:" << std::endl;
  std::string in_file_name=("../json/model4_300_dilepton_ELD.json");
  //std::string in_file_name=("../json/model4_100_singlelepton_ELD.json");
  std::ifstream in_file(in_file_name);

  if(!in_file){
    std::cout<<"Error: no nn input file!"<< std::endl;
  }

  // path to ntuples from AnalysisTop
  // Where we read from:
  //string path = "root://eosuser//eos/user/c/caudron/TtGamma_ntuples/v009/CR1/";
  string path = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_training/SR1/";
  // string path = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_training/QE2/";
  // string path = "/eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v008/CR1/";
  // string path = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/v007/QE2/";
  string channels[] ={"ee","emu","mumu"};
  // string channels[] ={"mujets"};

  // Where we save to:
  //string myPath = "root://eosatlas//eos/atlas/user/j/jwsmith/reprocessedNtuples/v009_flattened/SR1/";
  string myPath = "../SR1/";

  TFile *newfile;
  TFile *oldFile;
  TTree *newtree;
  TChain *fChain;


  m_config_netFile = new lwt::JSONConfig(lwt::parse_json(in_file));
  std::cout << ": NN has " << m_config_netFile->layers.size() << " layers"<< std::endl;
  m_neuralNet = new lwt::LightweightNeuralNetwork(m_config_netFile->inputs, 
  m_config_netFile->layers, m_config_netFile->outputs);

  for (int i = 1; i < argc; ++i) {
    for(const string &c : channels){

      string filename = argv[i];
      string file = path+c+"/"+filename;
      string newpath = myPath + c+"/"+filename;
      std::cout<<c<<": "<< filename<< std::endl;
      std::cout<<c<<": Saving to "<<newpath<< std::endl;

      oldFile = new TFile((file.c_str()), "read");

      TList* list = oldFile->GetListOfKeys() ;
      if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
      TIter next(list) ;
      TKey* key ;
      TObject* obj ;
          
      while ( key = (TKey*)next() ) {

        obj = key->ReadObj() ;
        if ( (strcmp(obj->IsA()->GetName(),"TTree")!=0) || (strcmp("sumWeights",obj->GetName()) == 0) ) {
          printf("Not running over: %s \n",obj->GetName()); continue; 
        }
        printf("#####################################\n");
        printf("Currently working on %s \n",obj->GetName());
        printf("#####################################\n");


        newfile = new TFile((newpath.c_str()), "update");
        fChain = new TChain(obj->GetName());
   
        fChain->Add((file).c_str());

        newtree = fChain->CloneTree(0);
        if(fChain->GetEntries() == 0){
          std::cout<<"No events, skipping"<<std::endl;
          continue;
        }
        m_add_branches(fChain,newtree,m_neuralNet);

        newfile->cd();
        newtree->Write();
        newfile->Close();

      } // end loop over trees
    } // end  loop over channels
  } // end loop over files

  return 0;
}
