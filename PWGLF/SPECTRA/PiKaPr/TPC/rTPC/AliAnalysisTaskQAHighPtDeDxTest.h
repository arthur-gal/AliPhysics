#ifndef ALIANALYSISTASKQAHIGHPTDEDX_H
#define ALIANALYSISTASKQAHIGHPTDEDX_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice */
/* $Id$ */


// ROOT includes
#include <TList.h>
#include <TH1.h>
#include <TProfile.h>
#include <TTreeStream.h>
#include <TRandom.h>
#include <TObject.h>

// AliRoot includes
#include <AliAnalysisTaskSE.h>
#include <AliESDEvent.h>
#include <AliAODEvent.h>
#include <AliMCEvent.h>
#include <AliAnalysisFilter.h>
#include <AliStack.h>
#include <AliGenEventHeader.h>
#include <AliVHeader.h>
#include <AliAODMCParticle.h> 
#include <AliESDtrackCuts.h>
#include <AliPIDResponse.h>
#include "AliTPCPIDResponse.h"
#include <AliEventCuts.h>
#include "AliVTrack.h"



class AliAnalysisTaskQAHighPtDeDxTest : public AliAnalysisTaskSE {
	public:


		AliAnalysisTaskQAHighPtDeDxTest();
		AliAnalysisTaskQAHighPtDeDxTest(const char *name);
		virtual ~AliAnalysisTaskQAHighPtDeDxTest();






		//AliAnalysisTaskQAHighPtDeDx(const char *name="<default name>");
		//virtual ~AliAnalysisTaskQAHighPtDeDx() { /*if (fOutputList) delete fOutputList;*/}//;

		virtual void   UserCreateOutputObjects();
		virtual void   UserExec(Option_t *option);

		Bool_t   GetAnalysisMC() { return fAnalysisMC; }   
		Double_t GetVtxCut() { return fVtxCut; }   
		Double_t GetEtaCut() { return fEtaCut; }     
		//Double_t GetMinPt() { return fMinPt; }   
		//Int_t    GetTreeOption() { return fTreeOption; }  

		virtual void  SetTrigger(UInt_t ktriggerInt) {ftrigBit = ktriggerInt;}
		virtual void  SetTrackFilterGolden(AliAnalysisFilter* trackF) {fTrackFilterGolden = trackF;}
		virtual void  SetTrackFilterTPC(AliAnalysisFilter* trackF) {fTrackFilterTPC = trackF;}
		virtual void  SetTrackFilter2015PbPb(AliAnalysisFilter* trackF) {fTrackFilter2015PbPb = trackF;}
		virtual void  SetCentralityEstimator(const char * centEst) {fCentEst = centEst;}
		virtual void  SetAnalysisType(const char* analysisType) {fAnalysisType = analysisType;}
		virtual void  SetAnalysisMC(Bool_t isMC) {fAnalysisMC = isMC;}
		//  virtual void  SetVtxCut(Double_t vtxCut){fVtxCut = vtxCut;}
		virtual void  SetNcl(const Int_t ncl){fNcl = ncl;}
		virtual void  SetEtaCut(Double_t etaCut){fEtaCut = etaCut;}
		virtual void  SetPileUpRej(Bool_t isrej) {fPileUpRej = isrej;}   
		virtual void  SetMinCent(Float_t minvalc) {fMinCent = minvalc;}
		virtual void  SetMaxCent(Float_t maxvalc) {fMaxCent = maxvalc;}
		virtual void  SetStoreMcIn(Bool_t value) {fStoreMcIn = value;}
		virtual void  SetAnalysisPbPb(Bool_t isanaPbPb) {fAnalysisPbPb = isanaPbPb;}
		virtual void  SetAnalysisTask(Bool_t PostCalib) {fdEdxCalibrated = PostCalib;}
		virtual void  SetAnalysisPID(Bool_t makePid) {fMakePid = makePid;}

	private:
		virtual Float_t GetVertex(const AliVEvent* event) const;
		virtual void AnalyzeESD(AliESDEvent* esd); 
		virtual void AnalyzeAOD(AliAODEvent* aod); 
		virtual void ProduceArrayTrksESD(AliESDEvent* event, const Int_t cent);
		virtual void ProduceArrayV0ESD(AliESDEvent* event, const Int_t cent );
		virtual void ProduceArrayTrksAOD(AliAODEvent* event);
		virtual void ProduceArrayV0AOD(AliAODEvent* event);
		Short_t   GetPidCode(Int_t pdgCode) const;
		void      ProcessMCTruthESD( const Int_t cent );
		void      ProcessMCTruthAOD(); 

		Short_t   GetPythiaEventProcessType(Int_t pythiaType);
		Short_t   GetDPMjetEventProcessType(Int_t dpmJetType);
		ULong64_t GetEventIdAsLong(AliVHeader* header) const;

		TParticle* FindPrimaryMother(AliStack* stack, Int_t label);
		Int_t      FindPrimaryMotherLabel(AliStack* stack, Int_t label);

		AliAODMCParticle* FindPrimaryMotherAOD(AliAODMCParticle* startParticle);

		TParticle* FindPrimaryMotherV0(AliStack* stack, Int_t label);
		Int_t      FindPrimaryMotherLabelV0(AliStack* stack, Int_t label, Int_t& nSteps);
		Bool_t PhiCut(Double_t pt, Double_t phi, Double_t q, Float_t   mag, TF1* phiCutLow, TF1* phiCutHigh);
		Float_t GetMaxDCApTDep( TF1 *fcut, Double_t pt );
		Double_t EtaCalibrationNeg(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationPos(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationNegEl(const Int_t centrality, const Double_t Eta);
		Double_t EtaCalibrationPosEl(const Int_t centrality, const Double_t Eta);



		AliAODMCParticle* FindPrimaryMotherAODV0(AliAODMCParticle* startParticle, Int_t& nSteps);



		static const Double_t fgkClight;   // Speed of light (cm/ps)
		//  static const Int_t nCent=10;   // Speed of light (cm/ps)

		AliESDEvent* fESD;                  //! ESD object
		AliAODEvent* fAOD;                  //! AOD object
		AliEventCuts fEventCuts;
		AliMCEvent*  fMC;                   //! MC object
		AliStack*    fMCStack;              //! MC ESD stack
		TClonesArray* fMCArray;             //! MC array for AOD
		AliPIDResponse* fPIDResponse;       //! Pointer to PIDResponse
		AliAnalysisFilter* fTrackFilter2015PbPb;    //  Track Filter, set 2010 with golden cuts
		AliAnalysisFilter* fTrackFilterGolden;    //  Track Filter, set 2010 with golden cuts
		AliAnalysisFilter* fTrackFilterTPC; // track filter for TPC only tracks
		TString       fCentEst;             // V0A , V0M, 
		TString       fAnalysisType;        //  "ESD" or "AOD"
		Bool_t        fAnalysisMC;          //  Real(kFALSE) or MC(kTRUE) flag
		Bool_t        fAnalysisPbPb;        //  true you want to analyze PbPb data, false for pp
		//  Boolt_t       fAnalysisTask;
		UInt_t        ftrigBit;
		TRandom*      fRandom;              //! random number generator
		Bool_t        fPileUpRej;           // kTRUE is pile-up is rejected



		//
		// Cuts and options
		//

		Double_t     fVtxCut;             // Vtx cut on z position in cm
		Int_t  fNcl;             // Eta cut used to select particles
		Double_t     fEtaCut;             // Eta cut used to select particles
		Int_t        cent; //minimum centrality
		Float_t      fMinCent; //minimum centrality
		Float_t      fMaxCent; //maximum centrality
		Bool_t       fStoreMcIn;          // Store MC input tracks

		//
		// Help variables
		//
		Short_t      fMcProcessType;      // -1=invalid, 0=data, 1=ND, 2=SD, 3=DD
		Short_t      fTriggeredEventMB;   // 1 = triggered, 0 = not trigged (MC only)
		Short_t      fVtxStatus;          // -1 = no vtx, 0 = outside cut, 1 = inside cut
		Float_t      fZvtx;               // z vertex
		Float_t      fZvtxMC;             // z vertex MC (truth)
		Int_t        fRun;                // run no
		ULong64_t    fEventId;            // unique event id

		//
		// Output objects
		//
		TList*        fListOfObjects;     //! Output list of objects
		//  TH1I*         fEvents;            //! No of accepted events
		//  TH1I*         fVtx;               //! Event vertex info
		TH1F*         fVtxMC;             //! Event vertex info for ALL MC events
		//  TH1F*         fVtxBeforeCuts;     //! Vertex z dist before cuts
		//  TH1F*         fVtxAfterCuts;      //! Vertex z dist after cuts
		//  TH1F* fn1;
		//  TH1F* hEvents;
		Bool_t       fdEdxCalibrated;
		Bool_t       fMakePid;
		TH1F* fcent;
		TH1F* fcentAfterPrimaries;
		TH1F* fcentAfterV0s;


		// Histograms for PreCalibration

		TH2D *hMIPVsEta[10];
		TProfile *pMIPVsEta[10];
		TH2D *hMIPVsEtaV0s[10];
		TProfile *pMIPVsEtaV0s[10];
		TH2D *hPlateauVsEta[10];
		TProfile *pPlateauVsEta[10];
		TH2D *hPhi[10];

		TH2D     *hMIPVsNch[10][4];
		TProfile *pMIPVsNch[10][4];

		TH2D     *hMIPVsPhi[10][4];
		TProfile *pMIPVsPhi[10][4];
		TH2D     *hPlateauVsPhi[10][4];
		TProfile *pPlateauVsPhi[10][4];


		// Histograms for PostCalibration


		TH1D *hPtAll[10];
		TH1D *hPtAllPos[10];
		TH1D *hPtAllNeg[10];
		TH1D *hPtPos[10][4];
		TH1D *hPtNeg[10][4];
		TH2D *hPtVsP[10][4];

		TH2D *hDeDxVsP[10][4];

		TH2D *hnSigmaPiPos[10][4];
		TH2D *hnSigmaKPos[10][4];
		TH2D *hnSigmaPPos[10][4];

		TH2D *hnSigmaPiNeg[10][4];
		TH2D *hnSigmaKNeg[10][4];
		TH2D *hnSigmaPNeg[10][4];

		TH2D* histPiV0[10][4];
		TH1D* histpPiV0[10][4];

		TH2D* histPV0[10][4];
		TH1D* histpPV0[10][4];

		TH2D* histPiTof[10][4];
		TH1D* histpPiTof[10][4];

		TH2D* histEV0[10][4];

		TH1D* hMcIn[11][7];
		TH1D* hMcOut[11][7];
		TH1D* hMcInNeg[11][7];
		TH1D* hMcInPos[11][7];
		TH1D* hMcOutNeg[11][7];
		TH1D* hMcOutPos[11][7];


		TH2D* hDCAxyVsPtPiNeg[10];
		TH2D* hDCAxyVsPtPiNegC[10];
		TH2D* hDCAxyVsPtKNeg[10];
		TH2D* hDCAxyVsPtKNegC[10];
		TH2D* hDCAxyVsPtPNeg[10];
		TH2D* hDCAxyVsPtPNegC[10];
		TH2D* hDCAxyVsPtPiPos[10];
		TH2D* hDCAxyVsPtPiPosC[10];
		TH2D* hDCAxyVsPtKPos[10];
		TH2D* hDCAxyVsPtKPosC[10];
		TH2D* hDCAxyVsPtPPos[10];
		TH2D* hDCAxyVsPtPPosC[10];

		//    [Cent][Pid][Charge: 0:neutral 1:Neg 2:Pos]
		TH2D* hDCApTPrim[10][7][3];
		TH2D* hDCApTWDec[10][7][3];
		TH2D* hDCApTMate[10][7][3];

		TH2D* hDCApTPrim2[10][7][3];
		TH2D* hDCApTWDec2[10][7][3];
		TH2D* hDCApTMate2[10][7][3];





		TF1* fEtaCalibrationNeg;
		TF1* fEtaCalibration;
		TF1* felededxfitPos;
		TF1* felededxfitNeg;
		TF1* fcutDCAxy;


		AliAnalysisTaskQAHighPtDeDxTest(const AliAnalysisTaskQAHighPtDeDxTest&);            // not implemented
		AliAnalysisTaskQAHighPtDeDxTest& operator=(const AliAnalysisTaskQAHighPtDeDxTest&); // not implemented

		//TTree*        fTree;              //! Debug tree 

		ClassDef(AliAnalysisTaskQAHighPtDeDxTest, 1);    //Analysis task for high pt analysis 
};

#endif
