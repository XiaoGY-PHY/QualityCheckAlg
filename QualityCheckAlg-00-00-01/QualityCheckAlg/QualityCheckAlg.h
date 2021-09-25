#ifndef Physics_Analysis_QualityCheckAlg_H
#define Physics_Analysis_QualityCheckAlg_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
//#include "VertexFit/ReadBeamParFromDb.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<double> Vdouble;

class QualityCheckAlg : public Algorithm {

public:
  QualityCheckAlg(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();  

private:

  //ReadBeamParFromDb m_reader;
  HepLorentzVector getP4(RecEmcShower* gTrk);
  bool validPhoton(EvtRecTrack* recTrk, SmartDataPtr<EvtRecEvent> recEvt, SmartDataPtr<EvtRecTrackCol> recTrkCol,
                                  Vdouble &Gam_Eraw, Vdouble &Gam_cosTheta, Vint &Gam_TrkID, Vdouble &Gam_E3x3, Vdouble &Gam_E5x5,
                                  Vdouble &Gam_Time, Vdouble &Gam_EMClatMoment, Vdouble &Gam_AngleWithChargeTrk);
  bool bothInEndcap(HepLorentzVector g1_P4, HepLorentzVector g2_P4);

  bool m_debug;

  double m_vr0cut;
  double m_vz0cut;
  double m_ccoscut;

  double m_pi0minmass_cut;
  double m_pi0maxmass_cut;
  double m_pi0chisq_cut;

  bool m_rejectEndEnd;
  double m_minEnergy;
  bool m_useBarrelEndcap;
  double m_maxCosThetaBarrel;
  double m_minCosThetaEndcap;
  double m_maxCosThetaEndcap;
  double m_minEndcapEnergy;

  bool m_applyTimeCut;
  double m_minTime;
  double m_maxTime;
  double m_deltaTime;

  bool m_applyDangCut;
  double m_minDang;

  bool m_applyMaxNGoodPhoton;
  int m_maxNGoodPhoton;
  bool m_applyMaxNPi0;
  int m_maxNPi0;
  
  // define Ntuples here

  NTuple::Tuple*  m_tuple1;
  NTuple::Item<int>  m_run;
  NTuple::Item<int>  m_event;

  NTuple::Item<int>  m_N_charge;
  NTuple::Item<int>  m_N_good_charge;

  NTuple::Item<int>  m_N_shower;
  NTuple::Item<int>  m_N_good_shower;
  NTuple::Array<double>  m_Gam_Eraw;
  NTuple::Array<double>  m_Gam_cosTheta;
  NTuple::Array<int>     m_Gam_TrkID;
  NTuple::Array<double>  m_Gam_E3x3;
  NTuple::Array<double>  m_Gam_E5x5;
  NTuple::Array<double>  m_Gam_Time;
  NTuple::Array<double>  m_Gam_EMClatMoment;
  NTuple::Array<double>  m_Gam_AngleWithChargeTrk;

  NTuple::Item<int>  m_nPi0;
  NTuple::Array<double>  m_Pi0_UnConMass;
  NTuple::Array<double>  m_Pi0_Chisq;
  NTuple::Matrix<double>  m_Pi0_p4;

  NTuple::Item<double>  m_mass_jspi;
  NTuple::Item<double>  m_mass_recpipi;
  NTuple::Item<int>  m_pindex;
  NTuple::Array<double>  m_p4_pip;
  NTuple::Array<double>  m_p4_pim;
  NTuple::Array<double>  m_p4_pip_from_jpsi;
  NTuple::Array<double>  m_p4_pim_from_jpsi;
  NTuple::Array<double>  m_p4_pi0_from_jpsi;
};

#endif 
