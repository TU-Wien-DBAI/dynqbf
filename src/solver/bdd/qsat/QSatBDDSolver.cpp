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

#include <sstream>
#include <iostream>

#include "QSatBDDSolver.h"
#include "../../../Application.h"
#include "../../../Printer.h"

#include "cuddObj.hh"
#include "htd/InducedSubgraphLabelingOperation.hpp"
#include <algorithm>

#include "../../../Utils.h"

namespace solver {
    namespace bdd {
        namespace qsat {

            QSatBDDSolver::QSatBDDSolver(const Application& app)
            : ::Solver(app) {
            }

            Computation* QSatBDDSolver::compute(htd::vertex_t currentNode) {

                BDD bdd = currentClauses();

                const SolverFactory& varMap = app.getSolverFactory();

                std::vector<BDD> cubesAtlevels;
                for (unsigned int i = 0; i < app.getInputInstance()->quantifierCount(); i++) {
                    cubesAtlevels.push_back(app.getBDDManager().getManager().bddOne());
                }
                const htd::ConstCollection<htd::vertex_t> currentVertices = app.getInputInstance()->hypergraph->internalGraph().vertices();
                for (const auto v : currentVertices) {
                    int level = htd::accessLabel<int>(this->app.getInputInstance()->hypergraph->internalGraph().vertexLabel("level", v));
                    BDD vertexVar = varMap.getBDDVariable("a", 0,{v});
                    cubesAtlevels[level - 1] *= vertexVar;
                }

                unsigned int keepUntil = 0;
                if (app.enumerate() && app.getInputInstance()->quantifier(1) == NTYPE::EXISTS) {
                    keepUntil = 1;
                }

                for (unsigned int level = app.getInputInstance()->quantifierCount(); level > keepUntil; level--) {
                    BDD cube = cubesAtlevels[level - 1];
                    if (app.getInputInstance()->quantifier(level) == NTYPE::EXISTS) {
                        bdd = bdd.ExistAbstract(cube, 0);
                    } else {
                        bdd = bdd.UnivAbstract(cube);
                    }
                }

                // TODO FIXME
                std::vector<BDD> currentCubes;
                Computation* c = app.getNSFManager().newComputation(app.getInputInstance()->getQuantifierSequence(), currentCubes, bdd);

                app.getPrinter().solverInvocationResult(currentNode, *c);

                return c;


            }

            BDD QSatBDDSolver::currentClauses() {
                Cudd manager = app.getBDDManager().getManager();

                const SolverFactory& varMap = app.getSolverFactory();

                BDD clauses = manager.bddOne();
                const htd::ConstCollection<htd::Hyperedge> edges = app.getInputInstance()->hypergraph->internalGraph().hyperedges();

                for (const auto& edge : edges) {
                    htd::id_t edgeId = edge.id();
                    const std::vector<bool> &edgeSigns = htd::accessLabel < std::vector<bool>>(app.getInputInstance()->hypergraph->edgeLabel("signs", edgeId));
                    BDD clause = manager.bddZero();

                    std::vector<bool>::const_iterator index = edgeSigns.begin();
                    for (const auto& vertex : edge) {

                        BDD vertexVar = varMap.getBDDVariable("a", 0,{vertex});
                        clause += (*index ? vertexVar : !vertexVar);
                        index++;
                    }
                    clauses *= clause;
                }
                return clauses;
            }

//            RESULT QSatBDDSolver::decide(const Computation & c) {
//                if (c.isUnsat()) {
//                    return RESULT::UNSAT;
//                } else {
//                    return RESULT::SAT;
//                }
//            }
//
//            BDD QSatBDDSolver::solutions(const Computation& c) {
//                ComputationManager& nsfManager = app.getNSFManager();
//                std::vector<BDD> cubesAtlevels;
//                for (unsigned int i = 0; i < app.getInputInstance()->quantifierCount(); i++) {
//                    cubesAtlevels.push_back(app.getBDDManager().getManager().bddOne());
//                }
//                return nsfManager.evaluate(c, cubesAtlevels, true);
//            }
        }
    }
} // namespace solver::bdd::qsat
