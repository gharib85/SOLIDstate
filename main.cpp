#include "Modules/SOLIDstate.hpp"

#include <armadillo>
using namespace arma;
using namespace solid;



int main(int argc, char *argv[])
{

	ArgvParser::Parse(argc, argv);
	
	Info::Start();
		
	int L = 6;

	QuantumSystem<SpMat, double> qSystem;

	qSystem.SelectEnsemble<Canonical>(L,L/2);
	//qSystem.SelectEnsemble<ParityGrandCanonical>(L,0);
	//qSystem.SelectEnsemble<GrandCanonical>(L);

	Info::ShowSectors(qSystem.hilbertSpace.ensemble);
	//Info::ShowSectors(qSystem); // other implementation 
	
	vec mu(L); mu.fill(0);
	//mu.set_size(L);
	//mu.fill(1);

	sp_mat V(L,L);
	//V.set_size(L, L);
	//for(int i=0;i<L;i++) V(i,(i+1)%L) = 1.0;

	sp_mat t(L,L);
	for(int i=0;i<L;i++) t(i,(i+1)%L) = 1.0;
	for(int i=0;i<L;i++) t((i+1)%L,i) = 1.0;
	//mat(t).print();

	Parameters<double> param;

	param["M"] = mu;
	param["V"] = -V;
	param["t"] = -t;

	qSystem.parameters = param;


	qSystem.SelectHamiltonian<KitaevHamiltonian>();
	qSystem.Fill();

	//MatrixElementFiller::Fill(qSystem);
	//qSystem.hamiltonian.matrixElements.print();

	///* eigen problem
	//mat eigvec;
	//vec eigval;
	//eig_sym(eigval,eigvec,qSystem.hamiltonian.matrixElements);
	//eigval.t().print();

	qSystem.quantumState = Eigensolver::FindGroundState(qSystem);
	
	double E = qSystem.quantumState.energy;
	double H = Laboratory::Measure(qSystem,qSystem.quantumState);
	std::cout << "Energy=" << E << "\t <H>=" << H << std::endl;

	return 0;

/*
	qSystem.SelectObservable<ParticleNumberOperator>(L);
	MatrixElementFiller::Fill(qSystem);
	ParticleNumberOperator<Mat,double>::Preprocessing(qSystem.hamiltonian.matrixElements);


	qSystem.hamiltonian.matrixElements.print();

	qSystem.SelectObservable<ParityOperator>(L);
	MatrixElementFiller::Fill(qSystem);
	ParityOperator<Mat,double>::Preprocessing(qSystem.hamiltonian.matrixElements);

	qSystem.hamiltonian.matrixElements.print();

	qSystem.parameters = param;
	qSystem.SelectHamiltonian<KitaevHamiltonian>();
	qSystem.Fill();
	qSystem.hamiltonian.matrixElements.print();
*/

	Info::Time();

	return 0;
}