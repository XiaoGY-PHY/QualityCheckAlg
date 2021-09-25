#ifndef Physics_PIDAlg_H
#define Physics_PIDAlg_H 

#include "ParticleID/ParticleID.h"
#include <vector>
class PIDAlg
{
	public:
		PIDAlg();
		~PIDAlg();

		void Initialize();
		void ParticleIdentify(EvtRecTrack*);

		bool isElectron();
		bool isMuon();
		bool isPion();
		bool isKaon();
		bool isProton();

		inline double probElectron(){return m_probElectron;}
		inline double probMuon(){return m_probMuon;}
		inline double probPion(){return m_probPion;}
		inline double probKaon(){return m_probKaon;}
		inline double probProton(){return m_probProton;}
		std::vector<double> AllProb();


	private:
		EvtRecTrack* m_recTrk;
        ParticleID *pid;
		bool m_isLoose;

		double m_probElectron;
		double m_probMuon;
		double m_probPion;
		double m_probKaon;
		double m_probProton;

};

extern PIDAlg pidAlg;

#endif
