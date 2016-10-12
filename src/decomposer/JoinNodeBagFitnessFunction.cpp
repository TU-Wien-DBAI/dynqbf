/*
Copyright 2016, Guenther Charwat
WWW: <http://dbai.tuwien.ac.at/proj/decodyn/dynqbf>.

This file is part of dynQBF.

dynQBF is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

dynQBF is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with dynQBF.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "JoinNodeBagFitnessFunction.h"
#include <math.h> 

// TODO: This will soon be removed!

namespace decomposer {

    JoinNodeBagFitnessFunction::JoinNodeBagFitnessFunction(void) {
    }

    JoinNodeBagFitnessFunction::~JoinNodeBagFitnessFunction() {
    }

    htd::FitnessEvaluation * JoinNodeBagFitnessFunction::fitness(const htd::IMultiHypergraph & graph,
            const htd::ITreeDecomposition & decomposition) const {
        HTD_UNUSED(graph)

        std::vector<htd::vertex_t> joinNodes;

        decomposition.copyJoinNodesTo(joinNodes);

        double joinNodeBagSum = 0.0;

        for (htd::vertex_t joinNode : joinNodes) {
            joinNodeBagSum += decomposition.bagSize(joinNode);
        }
        return new htd::FitnessEvaluation(1, -joinNodeBagSum);

    }

    JoinNodeBagFitnessFunction * JoinNodeBagFitnessFunction::clone(void) const {
        return new JoinNodeBagFitnessFunction();
    }
}