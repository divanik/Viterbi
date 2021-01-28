#pragma once

#include <Eigen>
#include <istream>
#include <vector>

class Markov_process {
	size_t states;
	size_t emits;
	Eigen::MatrixXd trans_probs;
	Eigen::MatrixXd emit_probs;
public:
	std::vector<size_t> viterbi (const std::vector<size_t>&);
	friend std::istream& operator>> (std::istream &in, Markov_process& mp);

};
