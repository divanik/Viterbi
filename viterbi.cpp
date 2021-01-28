#include "viterbi.h"

#include <algorithm>
#include <vector>

#include <iostream>
using namespace std;

std::vector<size_t> Markov_process::viterbi (const std::vector<size_t>& got_emissions) {
	using namespace std;
	vector<double> state_probs(states, 0.0);
	vector<double> prev_state_probs(states, 0.0);
	state_probs[0] = 1.0;
	vector<size_t> answer;
	size_t steps = got_emissions.size();
	vector<vector<size_t>> parents(steps, vector<size_t>(states));
	for (size_t i = 0; i < steps; ++i) {
		//cout << i << endl;
		std::swap(prev_state_probs, state_probs);
		for (size_t cur_st = 0; cur_st < states; cur_st++) {
			state_probs[cur_st] = -1;
			for (size_t prev_st = 0; prev_st < states; prev_st++) {
				double try_par = prev_state_probs[prev_st] * trans_probs(prev_st, cur_st);
				if (state_probs[cur_st] < try_par) {
					parents[i][cur_st] = prev_st;
					state_probs[cur_st] = try_par;

				} 
			}
			state_probs[cur_st] *= emit_probs(cur_st, got_emissions[i]);
 		}
	} 
	size_t max_state;
	double max_prob = -1;
	for (size_t i = 0; i < states; i++) {
		if (max_prob < state_probs[i]) {
			max_prob = state_probs[i];
			max_state = i;
		}
	}
	for (size_t i = 0; i < steps; i++) {
		answer.push_back(max_state);
		max_state = parents[steps - i - 1][max_state];
	}
	reverse(answer.begin(), answer.end());
	return answer;
}

std::istream& operator>> (std::istream &in, Markov_process& mp) {
	in >> mp.states >> mp.emits;
	mp.trans_probs.resize(mp.states, mp.states);
	mp.emit_probs.resize(mp.states, mp.emits);
	for (size_t i = 0; i < mp.states; i++) {
		for (size_t j = 0; j < mp.states; j++) {
			in >> mp.trans_probs(i, j);
		}
	}
	for (size_t i = 0; i < mp.states; i++) {
		for (size_t j = 0; j < mp.emits; j++) {
			in >> mp.emit_probs(i, j);
		}
	}
	return in;
}