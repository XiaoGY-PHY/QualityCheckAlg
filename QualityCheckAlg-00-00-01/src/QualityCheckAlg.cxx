#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
//#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"


#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
   typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "QualityCheckAlg/QualityCheckAlg.h"
#include "QualityCheckAlg/PIDAlg.h"

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
//#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include <vector>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
const double xmpi0 =  0.134976;
const double xmjpsi =  3.096900;
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<double> Vdouble;

QualityCheckAlg::QualityCheckAlg(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  
   declareProperty("m_debug", m_debug=false);

   /// Declare the properties  
   declareProperty("Vr0cut", m_vr0cut=1.0);
   declareProperty("Vz0cut", m_vz0cut=10.0);
   declareProperty("Ccoscut",   m_ccoscut=0.93);

   /// pi0 properties
   declareProperty("Pi0MinMass",  m_pi0minmass_cut = 0.115);
   declareProperty("Pi0MaxMass",  m_pi0maxmass_cut = 0.150);
   declareProperty("Pi0ChisqCut", m_pi0chisq_cut   = 20);

   /// Photon properties
   declareProperty("RejectBothInEndcap",  m_rejectEndEnd = false);

   declareProperty("PhotonMinEnergy", m_minEnergy = 0.025);
   declareProperty("PhotonInBarrelOrEndcap",  m_useBarrelEndcap   = true);
   declareProperty("PhotonMaxCosThetaBarrel", m_maxCosThetaBarrel = 0.8);
   declareProperty("PhotonMinCosThetaEndcap", m_minCosThetaEndcap = 0.86);
   declareProperty("PhotonMaxCosThetaEndcap", m_maxCosThetaEndcap = 0.92);
   declareProperty("PhotonMinEndcapEnergy",   m_minEndcapEnergy   = 0.050);

   declareProperty("PhotonApplyTimeCut", m_applyTimeCut = true);
   declareProperty("PhotonMinTime",      m_minTime      = 0.);
   declareProperty("PhotonMaxTime",      m_maxTime      = 14.);
   declareProperty("PhotonDeltaTime",    m_deltaTime    = 10.);

   declareProperty("PhotonApplyDangCut", m_applyDangCut = true);
   declareProperty("PhotonMinDang",      m_minDang      = 0.0);

   /// Limits for number of photons, pi0s and etas
   declareProperty("applyMaxNGoodPhoton",  m_applyMaxNGoodPhoton  =  true);
   declareProperty("MaxNGoodPhoton",       m_maxNGoodPhoton       =  999);
   declareProperty("applyMaxNPi0",         m_applyMaxNPi0         =  true);
   declareProperty("MaxNPi0",              m_maxNPi0              =  999);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode QualityCheckAlg::initialize(){
  MsgStream log(msgSvc(), name());

  log << MSG::INFO << "in initialize()" << endmsg;
  
  StatusCode status;
  NTuplePtr nt1(ntupleSvc(), "FILE1/check");
  if ( nt1 ) m_tuple1 = nt1;
  else {
    m_tuple1 = ntupleSvc()->book ("FILE1/check", CLID_ColumnWiseTuple, "check N-Tuple example");
    if ( m_tuple1 )    {
      status = m_tuple1->addItem ("run",   m_run);
      status = m_tuple1->addItem ("event", m_event);

      status = m_tuple1->addItem ("N_charge",   m_N_charge);
      status = m_tuple1->addItem ("N_good_charge",   m_N_good_charge);

      status = m_tuple1->addItem ("N_shower",   m_N_shower);
      status = m_tuple1->addItem ("N_good_shower",   m_N_good_shower,0,999);
      status = m_tuple1->addIndexedItem("Gam_Eraw", m_N_good_shower, m_Gam_Eraw);
      status = m_tuple1->addIndexedItem("Gam_cosTheta", m_N_good_shower, m_Gam_cosTheta);
      status = m_tuple1->addIndexedItem("NeutralTrack_TrkID", m_N_good_shower, m_Gam_TrkID);
      status = m_tuple1->addIndexedItem("Gam_E3x3", m_N_good_shower, m_Gam_E3x3);
      status = m_tuple1->addIndexedItem("Gam_E5x5", m_N_good_shower, m_Gam_E5x5);
      status = m_tuple1->addIndexedItem("Gam_Time", m_N_good_shower, m_Gam_Time);
      status = m_tuple1->addIndexedItem("Gam_EMClatMoment", m_N_good_shower, m_Gam_EMClatMoment);
      status = m_tuple1->addIndexedItem("Gamma_AngleWithChargeTrk", m_N_good_shower, m_Gam_AngleWithChargeTrk);

      status = m_tuple1->addItem("NumOfPi0", m_nPi0,0,999);
      status = m_tuple1->addIndexedItem("Pi0_UnConMass", m_nPi0, m_Pi0_UnConMass);
      status = m_tuple1->addIndexedItem("Pi0_Chisq", m_nPi0, m_Pi0_Chisq);
      status = m_tuple1->addIndexedItem("Pi0_p4", m_nPi0, 4, m_Pi0_p4);

	 status = m_tuple1->addItem ("mass_jspi",      m_mass_jspi);
	 status = m_tuple1->addItem ("mass_recpipi",   m_mass_recpipi);
	 status = m_tuple1->addItem ("pindex", m_pindex, 0, 200);
	 status = m_tuple1->addIndexedItem("p4_pip", m_pindex, m_p4_pip);
	 status = m_tuple1->addIndexedItem("p4_pim", m_pindex, m_p4_pim);
	 status = m_tuple1->addIndexedItem("p4_pip_from_jpsi", m_pindex, m_p4_pip_from_jpsi);
	 status = m_tuple1->addIndexedItem("p4_pim_from_jspi", m_pindex, m_p4_pim_from_jpsi);
	 status = m_tuple1->addIndexedItem("p4_pi0_from_jspi", m_pindex, m_p4_pi0_from_jpsi);

    }
    else    { 
      log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
      return StatusCode::FAILURE;
    }
  }
  //
  //--------end of book--------
  //

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode QualityCheckAlg::execute() {
	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;
	
	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	int runNo=eventHeader->runNumber();
	int event=eventHeader->eventNumber();

	m_run = runNo;
	m_event = event;

	log << MSG::DEBUG <<"run, evtnum = "
	    << runNo << " , "
	    << event <<endreq;
	
	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
	    << evtRecEvent->totalCharged() << " , "
	    << evtRecEvent->totalNeutral() << " , "
	    << evtRecEvent->totalTracks() <<endreq;

	int totCharge = evtRecEvent->totalCharged();
	int totNeutral = evtRecEvent->totalNeutral();
	
	m_N_charge = totCharge;
	m_N_shower = totNeutral;
	
	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);

	//count good charged tracks
	Vint iGood; iGood.clear();
	int nCharge = 0;
	Hep3Vector xorigin(0,0,0);
//	IVertexDbSvc*  vtxsvc;
//	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
//	if(vtxsvc->isVertexValid())
//	{
//		double* dbv = vtxsvc->PrimaryVertex();
//		double*  vv = vtxsvc->SigmaPrimaryVertex();
//		xorigin.setX(dbv[0]);
//		xorigin.setY(dbv[1]);
//		xorigin.setZ(dbv[2]);
//	}
	for(int i = 0; i < evtRecEvent->totalCharged(); i++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();

		double pch=mdcTrk->p();
		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
		VFHelix helixip(point0,a,Ea);
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double  Rvxy0=fabs(vecipa[0]);  //the nearest distance to IP in xy plane
		double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi0=vecipa[1];
		double ccos=cos(mdcTrk->theta());
		if(fabs(Rvz0) >= m_vz0cut) continue;
		if(fabs(Rvxy0) >= m_vr0cut) continue;
		if(fabs(ccos) >= m_ccoscut) continue;

		nCharge += mdcTrk->charge();
		iGood.push_back(i);//good track for ordinary charged particles!!
	}
	int nGood = iGood.size();
	m_N_good_charge = nGood;

	if(nGood!=4) return StatusCode::SUCCESS;
	if(nCharge!=0) return StatusCode::SUCCESS;

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;

	//*********************      PID pi+ pi-      ********************
	Vint ipip; Vint ipim; ipip.clear(); ipim.clear();
	for(int i = 0; i < nGood; i++)
     {
          EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
          RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
          if(mdcTrk->charge()==1)
          {
			pidAlg.Initialize();
			pidAlg.ParticleIdentify(*itTrk);
			if(pidAlg.isPion())
				ipip.push_back(iGood[i]);
          }
          if(mdcTrk->charge()==-1)
          {
			pidAlg.Initialize();
			pidAlg.ParticleIdentify(*itTrk);
			if(pidAlg.isPion())
				ipim.push_back(iGood[i]);
		}
	}
	int npip = ipip.size(); int npim = ipim.size();
	if (npip!=2) return StatusCode::SUCCESS;
	if (npim!=2) return StatusCode::SUCCESS;

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;

	//*********************     4-momentum for pi+ pi-     *****************
	Vp4 ppip; ppip.clear();
	Vp4 ppim; ppim.clear();
	for(int i = 0; i < npip; i++){
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + ipip[i];
		RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();
		mdcKalTrk->setPidType  (RecMdcKalTrack::pion);
		HepLorentzVector ppip4 = mdcKalTrk->p4(xmass[2]);
		ppip.push_back(ppip4);
	}
	for(int i = 0; i < npim; i++){
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + ipim[i];
		RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();
		mdcKalTrk->setPidType  (RecMdcKalTrack::pion);
		HepLorentzVector ppim4 = mdcKalTrk->p4(xmass[2]);
		ppim.push_back(ppim4);
	}

	int nppip = ppip.size(); int nppim = ppim.size();
	if (nppip!=2) return StatusCode::SUCCESS;
	if (nppim!=2) return StatusCode::SUCCESS;

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;


   //count good shower
   Vdouble Gam_Eraw;                Gam_Eraw.clear();
   Vdouble Gam_cosTheta;            Gam_cosTheta.clear();
   Vint    Gam_TrkID;               Gam_TrkID.clear();
   Vdouble Gam_E3x3;                Gam_E3x3.clear();
   Vdouble Gam_E5x5;                Gam_E5x5.clear();
   Vdouble Gam_Time;                Gam_Time.clear();
   Vdouble Gam_EMClatMoment;        Gam_EMClatMoment.clear();
   Vdouble Gam_AngleWithChargeTrk;  Gam_AngleWithChargeTrk.clear();

   std::vector<EvtRecTrack*> vGoodPhotons; vGoodPhotons.clear();
   for ( int i = evtRecEvent->totalCharged(); i < evtRecEvent->totalTracks(); i++ ) {
      EvtRecTrack* gTrk = *(evtRecTrkCol->begin() + i);
      if ( !validPhoton(gTrk, evtRecEvent, evtRecTrkCol, Gam_Eraw, Gam_cosTheta,
				    Gam_TrkID, Gam_E3x3, Gam_E5x5, Gam_Time,
				    Gam_EMClatMoment, Gam_AngleWithChargeTrk) ) continue;
      vGoodPhotons.push_back(gTrk);
   }
	int nGoodPhoton = vGoodPhotons.size();
	if(m_applyMaxNGoodPhoton && (nGoodPhoton > m_maxNGoodPhoton)) return StatusCode::SUCCESS;
	if(nGoodPhoton<2) return StatusCode::SUCCESS;

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;

	m_N_good_shower = nGoodPhoton;
	for(int i = 0; i < m_N_good_shower; ++i){
		m_Gam_Eraw[i] = Gam_Eraw[i];
		m_Gam_cosTheta[i] = Gam_cosTheta[i];
		m_Gam_TrkID[i] = Gam_TrkID[i];     
		m_Gam_E3x3[i] = Gam_E3x3[i];
		m_Gam_E5x5[i] = Gam_E5x5[i];
		m_Gam_Time[i] = Gam_Time[i];
		m_Gam_EMClatMoment[i] = Gam_EMClatMoment[i];
		m_Gam_AngleWithChargeTrk[i] = Gam_AngleWithChargeTrk[i];
	}

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;

	Vdouble Pi0_UnConMass;   Pi0_UnConMass.clear();
	Vdouble Pi0_Chisq;       Pi0_Chisq.clear();
     Vp4     Pi0_p4;          Pi0_p4.clear();

	KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();
	for(int i1 = 0; i1 < (nGoodPhoton-1); i1++) {
		EvtRecTrack* g1Trk = vGoodPhotons[i1];
		RecEmcShower* g1Shower = g1Trk->emcShower();
		HepLorentzVector g1P4 = getP4(g1Shower);
		
		for(int i2 = i1+1; i2 < nGoodPhoton; i2++) {
			EvtRecTrack* g2Trk = vGoodPhotons[i2];
			RecEmcShower* g2Shower = g2Trk->emcShower();
			HepLorentzVector g2P4 = getP4(g2Shower);
			
			HepLorentzVector p2g = g1P4 + g2P4;
			
			/// If RejectBothInEndcap=true, reject candidate if both photons are in endcaps
			if(m_rejectEndEnd&&bothInEndcap(g1P4,g2P4)) continue;
			
			/// Select pi0 candidates 
			if ((p2g.m() > m_pi0minmass_cut) && (p2g.m() < m_pi0maxmass_cut )) 
			{
				/// Perform pi0 1C KinematicFit 
				kmfit->init();
				kmfit->setIterNumber(5);
				kmfit->AddTrack(0, 0.0, g1Shower);
				kmfit->AddTrack(1, 0.0, g2Shower);
				kmfit->AddResonance(0, xmpi0, 0, 1);
				kmfit->Fit(0);
				kmfit->BuildVirtualParticle(0);

				double pi0_chisq = kmfit->chisq(0);
				if ( pi0_chisq >= m_pi0chisq_cut ) continue;

				HepLorentzVector tot =  kmfit->pfit(0) + kmfit->pfit(1);
				Pi0_UnConMass.push_back(p2g.m());
				Pi0_Chisq.push_back(pi0_chisq);
				Pi0_p4.push_back(tot);
			}
		}
	}

	int nPi0 = Pi0_UnConMass.size();
	if(m_applyMaxNPi0 && (nPi0 > m_maxNPi0)) return StatusCode::SUCCESS;
	if(nPi0 < 1) return StatusCode::SUCCESS;

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;

	m_nPi0 = nPi0;
	for(int i = 0; i < m_nPi0; ++i){
		m_Pi0_UnConMass[i] = Pi0_UnConMass[i];
		m_Pi0_Chisq[i] = Pi0_Chisq[i];
		for(int j = 0; j < 4; ++j) m_Pi0_p4[i][j] = Pi0_p4[i][j];
	}

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;
	if(m_debug) cout << "m_Pi0 = " << m_nPi0 << endl;

	double mPiPiPi0_minus_mjpsi = 999;
	int id_pip = 0;
	int id_pim = 0;
	int id_pip_from_jpsi = 1;
	int id_pim_from_jpsi = 1;
	int id_pi0 = 0;

	for(int p = 0; p < 2; ++p){
		for(int m = 0; m < 2; ++m){
			for(int pi0 = 0; pi0 < m_nPi0; ++pi0){
				HepLorentzVector tmp = ppip[p]+ppim[m]+Pi0_p4[pi0];
				double tmp_diff = tmp.m()-xmjpsi;
				if(fabs(tmp_diff) < fabs(mPiPiPi0_minus_mjpsi)){
					mPiPiPi0_minus_mjpsi = tmp_diff;
					id_pip_from_jpsi = p;
					id_pim_from_jpsi = m;
					id_pip = 1-p;
					id_pim = 1-m;
					id_pi0 = pi0;
				}
			}
		}
	}
	m_pindex = 4;

	m_mass_jspi = (ppip[id_pip_from_jpsi]+ppim[id_pim_from_jpsi]+Pi0_p4[id_pi0]).m();
	HepLorentzVector ecms(0.011*3.686,0,0,3.686);
	HepLorentzVector prec = ecms - ppip[id_pip] -ppim[id_pim];
	m_mass_recpipi = prec.m();

	for(int i = 0; i < 4; ++i){
		m_p4_pip[i] = ppip[id_pip][i];
		m_p4_pim[i] = ppim[id_pim][i];
		m_p4_pip_from_jpsi[i] = ppip[id_pip_from_jpsi][i];
		m_p4_pim_from_jpsi[i] = ppim[id_pim_from_jpsi][i];
		m_p4_pi0_from_jpsi[i] = Pi0_p4[id_pi0][i];
	}

	if(m_debug) cout << "****************** Line: " << __LINE__<<" ******************" << endl;
	m_tuple1->write();
	return StatusCode::SUCCESS;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode QualityCheckAlg::finalize() {
  cout<<"Finish!"<<endl;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;
  return StatusCode::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////

//HepLorentzVector QualityCheckAlg::getP4(RecEmcShower* gTrk, Hep3Vector origin)
//{
//	Hep3Vector Gm_Vec(gTrk->x(), gTrk->y(), gTrk->z());
//	Hep3Vector Gm_Mom = Gm_Vec - origin;
//	Gm_Mom.setMag(gTrk->energy());
//	HepLorentzVector pGm(Gm_Mom, gTrk->energy());
//	return pGm;
//}

HepLorentzVector QualityCheckAlg::getP4(RecEmcShower* gTrk){
   
   double eraw = gTrk->energy();
   double phi =  gTrk->phi();
   double the =  gTrk->theta();
   
   return HepLorentzVector( eraw * sin(the) * cos(phi),
                         eraw * sin(the) * sin(phi),
                   eraw * cos(the),
                   eraw );
}


bool QualityCheckAlg::validPhoton(EvtRecTrack* recTrk, SmartDataPtr<EvtRecEvent> recEvt, SmartDataPtr<EvtRecTrackCol> recTrkCol,
						    Vdouble &Gam_Eraw, Vdouble &Gam_cosTheta, Vint &Gam_TrkID, Vdouble &Gam_E3x3, Vdouble &Gam_E5x5,
						    Vdouble &Gam_Time, Vdouble &Gam_EMClatMoment, Vdouble &Gam_AngleWithChargeTrk) 
{
   if ( !recTrk->isEmcShowerValid() ) return false;

   RecEmcShower *emcTrk = recTrk->emcShower();

   HepLorentzVector shP4 = getP4(emcTrk);
   double cosThetaSh = shP4.vect().cosTheta();


//   /// Minimum energy
//   if (shP4.e() <= m_minEnergy) return false;


   /// Barrel/Endcap
   if ( m_useBarrelEndcap ) {
      bool inBarrelEndcap = false;

      if((fabs(cosThetaSh) < m_maxCosThetaBarrel)
	    &&(shP4.e() > m_minEnergy)) inBarrelEndcap = true;

      if((fabs(cosThetaSh) > m_minCosThetaEndcap)
	    &&(fabs(cosThetaSh) < m_maxCosThetaEndcap)
	    &&(shP4.e() > m_minEndcapEnergy)) inBarrelEndcap = true;

      if ( !inBarrelEndcap ) return false;
   }


   /// Time, only apply timing cuts if "recEvt->totalCharged() > 0"
   if ( m_applyTimeCut ) {
      double time = emcTrk->time();
      if ( recEvt->totalCharged() > 0 ) {
	 if ( time < m_minTime || time > m_maxTime ) return false;
      }
      else {
	 RecEmcShower* firstG = (*(recTrkCol->begin()))->emcShower();
	 double deltaTime = fabs(time - firstG->time());
	 if ( deltaTime > m_deltaTime ) return false;
      }
   }

   double tmp_dang = 0;
   /// Dang
   if (recEvt->totalCharged() > 0) 
   {
      Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());
      double dang = 200.; 

      for (int j = 0; j < recEvt->totalCharged(); j++) {
     	 EvtRecTrackIterator jtTrk = recTrkCol->begin() + j;
     	 if ( !(*jtTrk)->isExtTrackValid() ) continue;
     	 RecExtTrack* extTrk = (*jtTrk)->extTrack();
     	 if ( extTrk->emcVolumeNumber() == -1 ) continue;
     	 Hep3Vector extpos = extTrk->emcPosition();
     	 double  angd1 = extpos.angle(emcpos);
     	 if ( angd1 < dang ) dang = angd1;
      }

      if ( dang < 200 ) {
	   dang = dang * 180 / (CLHEP::pi);
	   tmp_dang = dang;
	   if (m_applyDangCut && dang <= m_minDang ) return false;
      }
   }

	Gam_Eraw.push_back(shP4.e());
	Gam_cosTheta.push_back(cosThetaSh);
	Gam_TrkID.push_back((recTrk)->trackId());
	Gam_AngleWithChargeTrk.push_back(fabs(tmp_dang));
	Gam_E3x3.push_back(emcTrk->e3x3());
	Gam_E5x5.push_back(emcTrk->e5x5());
	Gam_Time.push_back(emcTrk->time());
	Gam_EMClatMoment.push_back(emcTrk->latMoment());

   return true;
}


bool QualityCheckAlg::bothInEndcap(HepLorentzVector g1_P4, HepLorentzVector g2_P4){

  double g1_CosTheta = g1_P4.vect().cosTheta();
  double g2_CosTheta = g2_P4.vect().cosTheta();

  bool g1InEndcap = false;
  bool g2InEndcap = false;

  if((fabs(g1_CosTheta) > m_minCosThetaEndcap)
     &&(fabs(g1_CosTheta) < m_maxCosThetaEndcap)) g1InEndcap = true;

  if((fabs(g2_CosTheta) > m_minCosThetaEndcap)
     &&(fabs(g2_CosTheta) < m_maxCosThetaEndcap)) g2InEndcap = true;

  if(g1InEndcap&&g2InEndcap) return( true );

  return( false );
}
/////////////////////////////////////////////////////////////////////////////

