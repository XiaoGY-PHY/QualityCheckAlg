#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

//#include "VertexFit/IVertexDbSvc.h"
//#include "VertexFit/VertexFit.h"
//#include "VertexFit/Helix.h"

#include "QualityCheckAlg/PIDAlg.h"

PIDAlg::PIDAlg()
{
	m_recTrk = NULL;
	m_isLoose = false;
	m_probElectron = -1.;
	m_probMuon = -1.;
	m_probPion = -1.;
	m_probKaon = -1.;
	m_probProton = -1.;
	pid = ParticleID::instance();
}

void PIDAlg::Initialize(){
	m_recTrk = NULL;
	m_probElectron = -1.;
	m_probMuon = -1.;
	m_probPion = -1.;
	m_probKaon = -1.;
	m_probProton = -1.;
}

void PIDAlg::ParticleIdentify(EvtRecTrack* recTrk){
	m_recTrk = recTrk;
}

PIDAlg::~PIDAlg(){}

std::vector<double> PIDAlg::AllProb(){
	std::vector<double> Prob_All;		Prob_All.clear();
	Prob_All.push_back(m_probElectron);
	Prob_All.push_back(m_probMuon);
	Prob_All.push_back(m_probPion);
	Prob_All.push_back(m_probKaon);
	Prob_All.push_back(m_probProton);

	return Prob_All;
}

bool PIDAlg::isElectron()
{
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(m_recTrk);
	pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc()); // use PID sub-system
	pid->identify(pid->onlyElectron() | pid->onlyPion() | pid->onlyKaon());
	pid->calculate();
	if(!(pid->IsPidInfoValid())) return false;

	m_probElectron = pid->probElectron();
	m_probMuon = pid->probMuon();
	m_probPion = pid->probPion();
	m_probKaon = pid->probKaon();
	m_probProton = pid->probProton();

	if (m_isLoose && (m_probElectron > 0.)) return true;
	else if (m_probElectron > 0.001 && (m_probElectron / (m_probElectron + m_probPion + m_probKaon) > 0.8)) return true;
	return false;
}
bool PIDAlg::isMuon()
{
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(m_recTrk);
//	pid->usePidSys(pid->useDedx() | pid->useTofCorr()); // use pid sub-system
	pid->usePidSys(pid->useDedx() | pid->useTofCorr() | pid->useEmc()); // use pid sub-system
	pid->identify(pid->onlyMuon() | pid->onlyElectron() | pid->onlyKaon());
	pid->calculate();
	if(!(pid->IsPidInfoValid())) return false;

	m_probElectron = pid->probElectron();
	m_probMuon = pid->probMuon();
	m_probPion = pid->probPion();
	m_probKaon = pid->probKaon();
	m_probProton = pid->probProton();

	if (m_isLoose && (m_probMuon > 0.)) return true;
	else if (m_probMuon >= 0.001 && m_probMuon >= m_probElectron && m_probMuon >= m_probKaon) return true;
	return false;
}
bool PIDAlg::isPion()
{
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(m_recTrk);
	pid->usePidSys(pid->useDedx() | pid->useTofCorr()); // use pid sub-system
//	pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTof()); // use pid sub-system
	pid->identify(pid->onlyPion() | pid->onlyKaon());
	pid->calculate();
	if(!(pid->IsPidInfoValid())) return false;

	m_probElectron = pid->probElectron();
	m_probMuon = pid->probMuon();
	m_probPion = pid->probPion();
	m_probKaon = pid->probKaon();
	m_probProton = pid->probProton();

	if (m_isLoose && (m_probPion > 0.)) return true;
	else if (m_probPion >= 0. && m_probPion >= m_probKaon) return true;
	return false;
}
bool PIDAlg::isKaon()
{
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(4);
	pid->setRecTrack(m_recTrk);
	pid->usePidSys(pid->useDedx() | pid->useTofCorr()); // use pid sub-system
//	pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTof()); // use pid sub-system
	pid->identify(pid->onlyPion() | pid->onlyKaon());
	pid->calculate();
	if(!(pid->IsPidInfoValid())) return false;

	m_probElectron = pid->probElectron();
	m_probMuon = pid->probMuon();
	m_probPion = pid->probPion();
	m_probKaon = pid->probKaon();
	m_probProton = pid->probProton();

	if (m_isLoose && (m_probKaon > 0.)) return true;
	else if (m_probKaon >= 0. && m_probKaon >= m_probPion) return true;
	return false;
}
bool PIDAlg::isProton()
{
	pid->init();
	pid->setMethod(pid->methodProbability());
	pid->setChiMinCut(8);
	pid->setRecTrack(m_recTrk);
	pid->usePidSys(pid->useDedx() | pid->useTofCorr()); // use PID sub-system
//	pid->identify(pid->onlyPion() | pid->onlyKaon());
	pid->identify(pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());
	pid->calculate();
	if(!(pid->IsPidInfoValid())) return false;

	m_probElectron = pid->probElectron();
	m_probMuon = pid->probMuon();
	m_probPion = pid->probPion();
	m_probKaon = pid->probKaon();
	m_probProton = pid->probProton();
	
	if (m_isLoose && (m_probProton > 0.)) return true;
	else if (m_probProton >= 0. && m_probProton >= m_probPion && m_probProton >= m_probKaon) return true;
	return false;
}

PIDAlg pidAlg;
