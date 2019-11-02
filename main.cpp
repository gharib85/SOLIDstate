#include "Modules/SOLIDstate.hpp"

#include <armadillo>
using namespace arma;
using namespace solid;

#include "Modules/QuantumDynamics/DynamicsSchedule.hpp"
#include <functional>

int main(int argc, char *argv[])
{

	ArgvParser::Parse(argc, argv);

	Info::Start();

	// number of sites
	int L = 4;

	QuantumSystem<Mat, double> qSystem;

	//qSystem.SelectEnsemble<Canonical>(L,L/2);
	qSystem.SelectEnsemble<ParityGrandCanonical>(L, 0);
	//qSystem.SelectEnsemble<GrandCanonical>(L);

	Info::ShowSectors(qSystem.hilbertSpace.ensemble);
	//Info::ShowSectors(qSystem); // other implementation

	sp_mat mu(L, L);
	//mu.set_size(L);
	//mu = eye<sp_mat>(L,L);

	sp_mat V(L, L);
	//V.set_size(L, L);
	//for(int i=0;i<L;i++) V(i,(i+1)%L) = 1.0;

	sp_mat t(L, L);
	for (int i = 0; i < L - 1; i++)
		t(i, (i + 1) % L) = 1.0;
	for (int i = 0; i < L - 1; i++)
		t((i + 1) % L, i) = 1.0;
	//mat(t).print();

	sp_mat delta(L, L);
	for (int i = 0; i < L - 1; i++)
		delta(i, i + 1) = 1.0; // a+ a+
	for (int i = 0; i < L - 1; i++)
		delta(i + 1, i) = 1.0; // a  a
	//mat(delta).print();

	Parameters<double> param;

	param["M"] = mu;		// TODO non-diag ignored!
	param["V"] = V;			// TODO diag ignored!
	param["t"] = t;			// TODO diag ignored!
	param["delta"] = delta; // TODO diag ignored!

	qSystem.parameters = param;

	qSystem.SelectHamiltonian<KitaevHamiltonian>();
	qSystem.Fill();

	qSystem.hamiltonian.matrixElements.print();

	//MatrixElementFiller::Fill(qSystem);
	//qSystem.hamiltonian.matrixElements.print();

	///* eigen problem
	//mat eigvec;
	//vec eigval;
	//eig_sym(eigval,eigvec,qSystem.hamiltonian.matrixElements);
	//eigval.t().print();

	qSystem.quantumState = Eigensolver::FindGroundState(qSystem);

	double E = qSystem.quantumState.energy;
	double H = Laboratory::Measure(qSystem, qSystem.quantumState);
	std::cout << "Energy=" << E << "\t <H>=" << H << std::endl;

	//std::function<void()> fun;
	//fun = []() -> double{return 3;};

	/*
	mat(t).print("t=0.0");
	fun(t,0.50);
	mat(t).print("t=0.5");
	*/

	Schedule<sp_mat> t_schedule = [L](auto &A, auto t) {for(int i=0;i<L-1;i++) A(i,i+1) += 0.1 * t; };
	Schedule<sp_mat> V_schedule = [L](auto &A, auto t) {for(int i=0;i<L-1;i++) A(i,i+1) += -0.1 * t; };

	DynamicsSchedule<sp_mat> schedule;

	ScheduleMap<sp_mat> dict;
	dict["t"] = t_schedule;
	dict["V"] = V_schedule;

	schedule.dict = dict;

 	for (const auto& [label,val] : schedule.dict)
	{
    	//std::cout << label << std::endl;
		val(param[label],0.0);
		mat(param[label]).print(label+":");
		val(param[label],100.0);
		mat(param[label]).print(label+":");
	}

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