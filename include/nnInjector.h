//////////////////////////////
//Joshua.Wyatt.Smith@cern.ch//
//////////////////////////////
#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <fstream>
#include "TCut.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include <string>
#include <TChainElement.h>
#include "TH1D.h"
#include "TH1F.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include <sstream>
#include "TLorentzVector.h"
#include <memory>
#include <typeinfo>
#include "TGraph.h"
#include "lwtnn/NNLayerConfig.hh"
#include "lwtnn/LightweightNeuralNetwork.hh"
#include "lwtnn/parse_json.hh"
#include "lwtnn/Stack.hh" // <-- added for exceptions
using namespace std;

void     m_add_nn();
////////For multiclass /////////////
// std::vector<float> m_ph_ISR_MVA;
// std::vector<float> m_ph_FSR_MVA;
// std::vector<float> m_ph_HFake_MVA;
// std::vector<float> m_ph_eFake_MVA;
// std::vector<float> m_ph_OtherPrompt_MVA;
/////////////////////////////////////////////
////////For PPT /////////////
std::vector<float> m_ph_PPT_MVA;
/////////////////////////////////////////////
lwt::JSONConfig m_config_netFile;
std::map<std::string,double> m_NeuralNet_input_values;
lwt::LightweightNeuralNetwork *m_NeuralNet;
/////////////////////////////////////////////


Float_t         weight_mc;
Float_t         weight_pileup;
Float_t         weight_leptonSF;
Float_t         weight_photonSF;
Float_t         weight_bTagSF_77;
Float_t         weight_bTagSF_85;
Float_t         weight_bTagSF_70;
Float_t         weight_bTagSF_Continuous;
Float_t         weight_jvt;
Float_t         weight_pileup_UP;
Float_t         weight_pileup_DOWN;
ULong64_t       eventNumber;
UInt_t          runNumber;
UInt_t          randomRunNumber;
UInt_t          mcChannelNumber;
Float_t         mu;
UInt_t          backgroundFlags;
UInt_t          hasBadMuon;
vector<float>   *el_pt;
vector<float>   *el_eta;
vector<float>   *el_cl_eta;
vector<float>   *el_phi;
vector<float>   *el_e;
vector<float>   *el_charge;
vector<float>   *el_topoetcone20;
vector<float>   *el_ptvarcone20;
vector<char>    *el_CF;
vector<float>   *el_d0sig;
vector<float>   *el_delta_z0_sintheta;
vector<int>     *el_true_type;
vector<int>     *el_true_origin;
vector<int>     *el_true_typebkg;
vector<int>     *el_true_originbkg;
vector<float>   *mu_pt;
vector<float>   *mu_eta;
vector<float>   *mu_phi;
vector<float>   *mu_e;
vector<float>   *mu_charge;
vector<float>   *mu_topoetcone20;
vector<float>   *mu_ptvarcone30;
vector<float>   *mu_d0sig;
vector<float>   *mu_delta_z0_sintheta;
vector<int>     *mu_true_type;
vector<int>     *mu_true_origin;
vector<float>   *ph_pt;
vector<float>   *ph_eta;
vector<float>   *ph_phi;
vector<float>   *ph_e;
vector<float>   *ph_iso;
vector<float>   *jet_pt;
vector<float>   *jet_eta;
vector<float>   *jet_phi;
vector<float>   *jet_e;
vector<float>   *jet_mv2c00;
vector<float>   *jet_mv2c10;
vector<float>   *jet_mv2c20;
vector<float>   *jet_ip3dsv1;
vector<float>   *jet_jvt;
vector<char>    *jet_passfjvt;
vector<int>     *jet_truthflav;
vector<int>     *jet_truthPartonLabel;
vector<char>    *jet_isTrueHS;
vector<char>    *jet_isbtagged_77;
vector<char>    *jet_isbtagged_85;
vector<char>    *jet_isbtagged_70;
vector<int>     *jet_tagWeightBin;
Float_t         met_met;
Float_t         met_phi;
Int_t           ejets_2015;
Int_t           ejets_2016;
Int_t           mujets_2015;
Int_t           mujets_2016;
Int_t           emu_2015;
Int_t           emu_2016;
Int_t           emuSS_2015;
Int_t           emuSS_2016;
Int_t           ee_2015;
Int_t           ee_2016;
Int_t           eeSS_2015;
Int_t           eeSS_2016;
Int_t           mumu_2015;
Int_t           mumu_2016;
Int_t           mumuSS_2015;
Int_t           mumuSS_2016;
Char_t          HLT_mu20_iloose_L1MU15;
Char_t          HLT_e60_lhmedium_nod0;
Char_t          HLT_mu26_ivarmedium;
Char_t          HLT_e26_lhtight_nod0_ivarloose;
Char_t          HLT_e140_lhloose_nod0;
Char_t          HLT_mu50;
Char_t          HLT_e60_lhmedium;
Char_t          HLT_e24_lhmedium_L1EM20VH;
Char_t          HLT_e120_lhloose;
vector<char>    *el_trigMatch_HLT_e60_lhmedium_nod0;
vector<char>    *el_trigMatch_HLT_e26_lhtight_nod0_ivarloose;
vector<char>    *el_trigMatch_HLT_e140_lhloose_nod0;
vector<char>    *el_trigMatch_HLT_e60_lhmedium;
vector<char>    *el_trigMatch_HLT_e24_lhmedium_L1EM20VH;
vector<char>    *el_trigMatch_HLT_e120_lhloose;
vector<char>    *mu_trigMatch_HLT_mu26_ivarmedium;
vector<char>    *mu_trigMatch_HLT_mu50;
vector<char>    *mu_trigMatch_HLT_mu20_iloose_L1MU15;
vector<float>   *ph_topoetcone20;
vector<float>   *ph_topoetcone30;
vector<float>   *ph_topoetcone40;
vector<float>   *ph_ptcone20;
vector<float>   *ph_ptcone30;
vector<float>   *ph_ptcone40;
vector<float>   *ph_ptvarcone20;
vector<float>   *ph_ptvarcone30;
vector<float>   *ph_ptvarcone40;
vector<char>    *ph_isoFCTCO;
vector<char>    *ph_isoFCT;
vector<char>    *ph_isoFCL;
vector<char>    *ph_isTight;
vector<char>    *ph_isLoose;
vector<char>    *ph_isTight_daod;
vector<char>    *ph_isHFake;
vector<char>    *ph_isHadronFakeFailedDeltaE;
vector<char>    *ph_isHadronFakeFailedFside;
vector<char>    *ph_isHadronFakeFailedWs3;
vector<char>    *ph_isHadronFakeFailedERatio;
vector<float>   *ph_rhad1;
vector<float>   *ph_rhad;
vector<float>   *ph_reta;
vector<float>   *ph_weta2;
vector<float>   *ph_rphi;
vector<float>   *ph_ws3;
vector<float>   *ph_wstot;
vector<float>   *ph_fracm;
vector<float>   *ph_deltaE;
vector<float>   *ph_eratio;
vector<float>   *ph_emaxs1;
vector<float>   *ph_f1;
vector<float>   *ph_e277;
vector<unsigned int> *ph_OQ;
vector<unsigned int> *ph_author;
vector<int>     *ph_conversionType;
vector<float>   *ph_caloEta;
vector<unsigned int> *ph_isEM;
vector<int>     *ph_nVertices;
vector<float>   *ph_SF_eff;
vector<float>   *ph_SF_effUP;
vector<float>   *ph_SF_effDO;
vector<float>   *ph_SF_iso;
vector<float>   *ph_SF_lowisoUP;
vector<float>   *ph_SF_lowisoDO;
vector<float>   *ph_SF_trkisoUP;
vector<float>   *ph_SF_trkisoDO;
vector<float>   *ph_drleadjet;
vector<float>   *ph_dralljet;
vector<float>   *ph_drsubljet;
vector<float>   *ph_drlept;
vector<float>   *ph_mgammalept;
vector<float>   *ph_mgammaleptlept;
Int_t           selph_index1;
Int_t           selph_index2;
Int_t           selhf_index1;
vector<int>     *ph_truthType;
vector<int>     *ph_truthOrigin;
vector<int>     *ph_truthAncestor;
vector<int>     *ph_mc_pid;
vector<int>     *ph_mc_barcode;
vector<float>   *ph_mc_pt;
vector<float>   *ph_mc_eta;
vector<float>   *ph_mc_phi;
vector<float>   *ph_mcel_dr;
vector<float>   *ph_mcel_pt;
vector<float>   *ph_mcel_eta;
vector<float>   *ph_mcel_phi;
vector<float>   *mcph_pt;
vector<float>   *mcph_eta;
vector<float>   *mcph_phi;
vector<int>     *mcph_ancestor;
vector<int>     *el_truthAncestor;
vector<char>    *el_isoGradient;
vector<int>     *el_mc_pid;
vector<float>   *el_mc_charge;
vector<float>   *el_mc_pt;
vector<float>   *el_mc_eta;
vector<float>   *el_mc_phi;
vector<float>   *mu_mc_charge;
vector<float>   *jet_mcdr_tW1;
vector<float>   *jet_mcdr_tW2;
vector<float>   *jet_mcdr_tB;
vector<float>   *jet_mcdr_tbW1;
vector<float>   *jet_mcdr_tbW2;
vector<float>   *jet_mcdr_tbB;
vector<int>     *lepton_type;
Float_t         event_HT;
Float_t         event_mll;
Float_t         event_mwt;
Int_t           event_njets;
Int_t           event_nbjets70;
Int_t           event_nbjets77;
Int_t           event_nbjets85;
Int_t           event_ngoodphotons;
Int_t           event_photonorigin;
Int_t           event_photonoriginTA;
Int_t           event_nhadronfakes;
vector<float>   *ph_HFT_MVA;
Int_t           ph_nHFT_MVA;
Double_t        event_norm;
Double_t        event_lumi;



//Some new variables
float ISR_MVA = -1;
float FSR_MVA = -1;
float hadronfake_MVA = -1;
float egammafake_MVA = -1;
float other_MVA = -1;

void activateBranches(TChain *chain){
	// Activate branches for MC chain
	#define SETBRANCH(branchName) chain->SetBranchAddress(#branchName,&branchName)
	SETBRANCH(weight_mc);
	SETBRANCH(weight_pileup);
	SETBRANCH(weight_leptonSF);
	SETBRANCH(weight_photonSF);
	SETBRANCH(weight_bTagSF_77);
	SETBRANCH(weight_bTagSF_85);
	SETBRANCH(weight_bTagSF_70);
	SETBRANCH(weight_bTagSF_Continuous);
	SETBRANCH(weight_jvt);
	SETBRANCH(weight_pileup_UP);
	SETBRANCH(weight_pileup_DOWN);
	SETBRANCH(eventNumber);
	SETBRANCH(runNumber);
	SETBRANCH(randomRunNumber);
	SETBRANCH(mcChannelNumber);
	SETBRANCH(mu);
	SETBRANCH(backgroundFlags);
	SETBRANCH(hasBadMuon);
	SETBRANCH(el_pt);
	SETBRANCH(el_eta);
	SETBRANCH(el_cl_eta);
	SETBRANCH(el_phi);
	SETBRANCH(el_e);
	SETBRANCH(el_charge);
	SETBRANCH(el_topoetcone20);
	SETBRANCH(el_ptvarcone20);
	SETBRANCH(el_CF);
	SETBRANCH(el_d0sig);
	SETBRANCH(el_delta_z0_sintheta);
	SETBRANCH(el_true_type);
	SETBRANCH(el_true_origin);
	SETBRANCH(el_true_typebkg);
	SETBRANCH(el_true_originbkg);
	SETBRANCH(mu_pt);
	SETBRANCH(mu_eta);
	SETBRANCH(mu_phi);
	SETBRANCH(mu_e);
	SETBRANCH(mu_charge);
	SETBRANCH(mu_topoetcone20);
	SETBRANCH(mu_ptvarcone30);
	SETBRANCH(mu_d0sig);
	SETBRANCH(mu_delta_z0_sintheta);
	SETBRANCH(mu_true_type);
	SETBRANCH(mu_true_origin);
	SETBRANCH(ph_pt);
	SETBRANCH(ph_eta);
	SETBRANCH(ph_phi);
	SETBRANCH(ph_e);
	SETBRANCH(ph_iso);
	SETBRANCH(jet_pt);
	SETBRANCH(jet_eta);
	SETBRANCH(jet_phi);
	SETBRANCH(jet_e);
	SETBRANCH(jet_mv2c00);
	SETBRANCH(jet_mv2c10);
	SETBRANCH(jet_mv2c20);
	SETBRANCH(jet_ip3dsv1);
	SETBRANCH(jet_jvt);
	SETBRANCH(jet_passfjvt);
	SETBRANCH(jet_truthflav);
	SETBRANCH(jet_truthPartonLabel);
	SETBRANCH(jet_isTrueHS);
	SETBRANCH(jet_isbtagged_77);
	SETBRANCH(jet_isbtagged_85);
	SETBRANCH(jet_isbtagged_70);
	SETBRANCH(jet_tagWeightBin);
	SETBRANCH(met_met);
	SETBRANCH(met_phi);
	SETBRANCH(ejets_2015);
	SETBRANCH(ejets_2016);
	SETBRANCH(mujets_2015);
	SETBRANCH(mujets_2016);
	SETBRANCH(emu_2015);
	SETBRANCH(emu_2016);
	SETBRANCH(emuSS_2015);
	SETBRANCH(emuSS_2016);
	SETBRANCH(ee_2015);
	SETBRANCH(ee_2016);
	SETBRANCH(eeSS_2015);
	SETBRANCH(eeSS_2016);
	SETBRANCH(mumu_2015);
	SETBRANCH(mumu_2016);
	SETBRANCH(mumuSS_2015);
	SETBRANCH(mumuSS_2016);
	SETBRANCH(HLT_mu20_iloose_L1MU15);
	SETBRANCH(HLT_e60_lhmedium_nod0);
	SETBRANCH(HLT_mu26_ivarmedium);
	SETBRANCH(HLT_e26_lhtight_nod0_ivarloose);
	SETBRANCH(HLT_e140_lhloose_nod0);
	SETBRANCH(HLT_mu50);
	SETBRANCH(HLT_e60_lhmedium);
	SETBRANCH(HLT_e24_lhmedium_L1EM20VH);
	SETBRANCH(HLT_e120_lhloose);
	SETBRANCH(el_trigMatch_HLT_e60_lhmedium_nod0);
	SETBRANCH(el_trigMatch_HLT_e26_lhtight_nod0_ivarloose);
	SETBRANCH(el_trigMatch_HLT_e140_lhloose_nod0);
	SETBRANCH(el_trigMatch_HLT_e60_lhmedium);
	SETBRANCH(el_trigMatch_HLT_e24_lhmedium_L1EM20VH);
	SETBRANCH(el_trigMatch_HLT_e120_lhloose);
	SETBRANCH(mu_trigMatch_HLT_mu26_ivarmedium);
	SETBRANCH(mu_trigMatch_HLT_mu50);
	SETBRANCH(mu_trigMatch_HLT_mu20_iloose_L1MU15);
	SETBRANCH(ph_topoetcone20);
	SETBRANCH(ph_topoetcone30);
	SETBRANCH(ph_topoetcone40);
	SETBRANCH(ph_ptcone20);
	SETBRANCH(ph_ptcone30);
	SETBRANCH(ph_ptcone40);
	SETBRANCH(ph_ptvarcone20);
	SETBRANCH(ph_ptvarcone30);
	SETBRANCH(ph_ptvarcone40);
	SETBRANCH(ph_isoFCTCO);
	SETBRANCH(ph_isoFCT);
	SETBRANCH(ph_isoFCL);
	SETBRANCH(ph_isTight);
	SETBRANCH(ph_isLoose);
	SETBRANCH(ph_isTight_daod);
	SETBRANCH(ph_isHFake);
	SETBRANCH(ph_isHadronFakeFailedDeltaE);
	SETBRANCH(ph_isHadronFakeFailedFside);
	SETBRANCH(ph_isHadronFakeFailedWs3);
	SETBRANCH(ph_isHadronFakeFailedERatio);
	SETBRANCH(ph_rhad1);
	SETBRANCH(ph_rhad);
	SETBRANCH(ph_reta);
	SETBRANCH(ph_weta2);
	SETBRANCH(ph_rphi);
	SETBRANCH(ph_ws3);
	SETBRANCH(ph_wstot);
	SETBRANCH(ph_fracm);
	SETBRANCH(ph_deltaE);
	SETBRANCH(ph_eratio);
	SETBRANCH(ph_emaxs1);
	SETBRANCH(ph_f1);
	SETBRANCH(ph_e277);
	SETBRANCH(ph_OQ);
	SETBRANCH(ph_author);
	SETBRANCH(ph_conversionType);
	SETBRANCH(ph_caloEta);
	SETBRANCH(ph_isEM);
	SETBRANCH(ph_nVertices);
	SETBRANCH(ph_SF_eff);
	SETBRANCH(ph_SF_effUP);
	SETBRANCH(ph_SF_effDO);
	SETBRANCH(ph_SF_iso);
	SETBRANCH(ph_SF_lowisoUP);
	SETBRANCH(ph_SF_lowisoDO);
	SETBRANCH(ph_SF_trkisoUP);
	SETBRANCH(ph_SF_trkisoDO);
	SETBRANCH(ph_drleadjet);
	SETBRANCH(ph_dralljet);
	SETBRANCH(ph_drsubljet);
	SETBRANCH(ph_drlept);
	SETBRANCH(ph_mgammalept);
	SETBRANCH(ph_mgammaleptlept);
	SETBRANCH(selph_index1);
	SETBRANCH(selph_index2);
	SETBRANCH(selhf_index1);
	SETBRANCH(ph_truthType);
	SETBRANCH(ph_truthOrigin);
	SETBRANCH(ph_truthAncestor);
	SETBRANCH(ph_mc_pid);
	SETBRANCH(ph_mc_barcode);
	SETBRANCH(ph_mc_pt);
	SETBRANCH(ph_mc_eta);
	SETBRANCH(ph_mc_phi);
	SETBRANCH(ph_mcel_dr);
	SETBRANCH(ph_mcel_pt);
	SETBRANCH(ph_mcel_eta);
	SETBRANCH(ph_mcel_phi);
	SETBRANCH(mcph_pt);
	SETBRANCH(mcph_eta);
	SETBRANCH(mcph_phi);
	SETBRANCH(mcph_ancestor);
	SETBRANCH(el_truthAncestor);
	SETBRANCH(el_isoGradient);
	SETBRANCH(el_mc_pid);
	SETBRANCH(el_mc_charge);
	SETBRANCH(el_mc_pt);
	SETBRANCH(el_mc_eta);
	SETBRANCH(el_mc_phi);
	SETBRANCH(mu_mc_charge);
	SETBRANCH(jet_mcdr_tW1);
	SETBRANCH(jet_mcdr_tW2);
	SETBRANCH(jet_mcdr_tB);
	SETBRANCH(jet_mcdr_tbW1);
	SETBRANCH(jet_mcdr_tbW2);
	SETBRANCH(jet_mcdr_tbB);
	SETBRANCH(lepton_type);
	SETBRANCH(event_HT);
	SETBRANCH(event_mll);
	SETBRANCH(event_mwt);
	SETBRANCH(event_njets);
	SETBRANCH(event_nbjets70);
	SETBRANCH(event_nbjets77);
	SETBRANCH(event_nbjets85);
	SETBRANCH(event_ngoodphotons);
	SETBRANCH(event_photonorigin);
	SETBRANCH(event_photonoriginTA);
	SETBRANCH(event_nhadronfakes);
	SETBRANCH(ph_HFT_MVA);
	SETBRANCH(ph_nHFT_MVA);
	SETBRANCH(event_norm);
	SETBRANCH(event_lumi);
	#undef SETBRANCH
	}
// A progress bar
static inline void loadBar(int x, int n, int r, int w)
{
	// Only update r times.
	if (x % (n / r + 1) != 0) {
		return;
	}
	// Calculuate the ratio of complete-to-incomplete.
	float ratio = x / (float)n;
	int c = ratio * w;
	// Show the percentage complete.
	printf("%3d%% [", (int)(ratio * 100));
	// Show the load bar.
	for (int x = 0; x < c; x++) {
		printf("=");
	}
	for (int x = c; x < w; x++) {
		printf(" ");
	}
	// ANSI Control codes to go back to the
	// previous line and clear it.
	printf("]\n\033[F\033[J");
}
