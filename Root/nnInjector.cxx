//////////////////////////////
//Joshua.Wyatt.Smith@cern.ch//
//////////////////////////////
#include "nnInjector.h"
#include <iostream>

void m_add_nn(string path, string channel, string filename){
	string file = path+channel+"/"+filename;
	string newpath = channel+"/"+filename;
  std::cout<<channel<<" "<< filename<< std::endl;
	TFile *newfile;
	TTree *newtree;
	TChain *fChain = new TChain("nominal");

	newfile = new TFile((newpath.c_str()), "update");
	fChain->Add((file).c_str());

	int nentries = fChain->GetEntries();
	newtree = fChain->CloneTree(0);

	// Define some new branches and activate all others //
 //  ///////////////////// For multiclass ////////////////////////
	// newtree->Branch("ph_ISR_MVA",&m_ph_ISR_MVA,"m_ph_ISR_MVA/F");
	// newtree->Branch("ph_FSR_MVA",&m_ph_FSR_MVA,"m_ph_FSR_MVA/F");
	// newtree->Branch("ph_HFake_MVA",&m_ph_HFake_MVA,"m_ph_HFake_MVA/F");
	// newtree->Branch("ph_eFake_MVA",&m_ph_eFake_MVA,"m_ph_eFake_MVA/F");
	// newtree->Branch("ph_OtherPrompt_MVA",&m_ph_OtherPrompt_MVA,"m_ph_OtherPrompt_MVA/F");   
	//////////////////For Prompt photon tagger ////////////////////
		newtree->Branch("ph_PPT_MVA",&m_ph_PPT_MVA,"m_ph_PPT_MVA/F");   
	//////////////////////////////////////////////////////
	activateBranches(fChain);

	for (int event = 0; event < nentries; event++) {
		fChain->GetEntry(event);
		loadBar(event, nentries, 100, 50);

		unsigned int n_photons = ph_pt->size();
    m_ph_PPT_MVA.resize(n_photons);


		//----------- Neural network
		//////////////////For Prompt photon tagger ////////////////////
    for (UInt_t pht = 0; pht < ph_pt->size(); pht++) {
    	 //----- decorate the pointer with the index value
      // phPtr->auxdecor< int >( "i" ) = i;


			m_NeuralNet_input_values["y_Reta"] = ph_reta->at(pht);
			m_NeuralNet_input_values["y_Rphi"] = ph_rphi->at(pht);
			m_NeuralNet_input_values["y_Rhad"] = ph_rhad->at(pht);
			m_NeuralNet_input_values["y_weta1"] = ph_ws3->at(pht);
			m_NeuralNet_input_values["y_fracs1"] = ph_fracm->at(pht);
			m_NeuralNet_input_values["y_weta2"] = ph_weta2->at(pht);

			m_ph_PPT_MVA[pht]=-99;
			auto out_vals = m_NeuralNet->compute(m_NeuralNet_input_values);
			for (const auto& out: out_vals) {
				m_ph_PPT_MVA[pht] = out.second;
			}
			// std::cout<<m_ph_PPT_MVA[pht]<<std::endl;
		}
		newtree->Fill();

		//////////////////////////////////////////////////////


	}


	newfile->cd();
	newtree->Write();
	newfile->Close();
}

int main()
{

	std::string in_file_name("../json/lwtnn_output.json");
	std::ifstream in_file(in_file_name);
	m_config_netFile = lwt::parse_json(in_file);
	m_NeuralNet = new lwt::LightweightNeuralNetwork(m_config_netFile.inputs, 
	m_config_netFile.layers, m_config_netFile.outputs);


	// path to ntuples from AnalysisTop
	string path = "/eos/atlas/user/c/caudron/TtGamma_ntuples/v007/CR1/";
	string channels[] ={"ejets"};
	string myPath = "/eos/atlas/user/j/jwsmith/reprocessedNtuples/nnInjected/";
	// Define number of regions


	string samples[] = {
	// "301XXX.eegamma.p2952.v007.001.root",
	// "301XXX.enugamma.p2952.v007.001.root",
	// "301XXX.mumugamma.p2952.v007.001.root",
	// "301XXX.munugamma.p2952.v007.001.root",
	// "301XXX.taunugamma.p2952.v007.001.root",
	// "301XXX.tautaugamma.p2952.v007.001.root",
	// "3610XX.VV.p2952.v007.001.root",
	// "3641XX.Wenu.p2952.v007.001.root",
	// "3641XX.Wmunu.p2952.v007.001.root",
	// "3641XX.Wtaunu.p2952.v007.001.root",
	// "3641XX.Zee.p2952.v007.001.root",
	// "3641XX.Zmumu.p2952.v007.001.root",
	// "3641XX.Ztautau.p2952.v007.001.root",
	"410082.ttgamma_noallhad.p2952.v007.001.root",
	"4100XX.ST_others.p2952.v007.001.root"
	// "4100XX.ST_Wt_inclusive.p2952.v007.001.root",
	// "410501.ttbar_nonallhad_P8.p2952.v007.001.root",
	// "data15periodD.p2950.v007.001.root",
	// "data15periodE.p2950.v007.001.root",
	// "data15periodF.p2950.v007.001.root",
	// "data15periodG.p2950.v007.001.root",
	// "data15periodH.p2950.v007.001.root",
	// "data15periodJ.p2950.v007.001.root",
	// "data16periodA.p2950.v007.001.root",
	// "data16periodB.p2950.v007.001.root",
	// "data16periodC.p2950.v007.001.root",
	// "data16periodD.p2950.v007.001.root",
	// "data16periodE.p2950.v007.001.root",
	// "data16periodF.p2950.v007.001.root",
	// "data16periodG.p2950.v007.001.root",
	// "data16periodI.p2950.v007.001.root",
	// "data16periodK.p2950.v007.001.root",
	// "data16periodL.p2950.v007.001.root"
	};



	for (const string &s : samples) {
    for(const string &c : channels){
	    m_add_nn(path,c,s);
    }
	}


	return 0;
}
