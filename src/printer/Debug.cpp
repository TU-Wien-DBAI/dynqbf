/*
Copyright 2016-2017, Guenther Charwat
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

#include <iostream>

#include "Debug.h"
#include "../Application.h"
#include "../Utils.h"

namespace printer {

    Debug::Debug(Application& app, bool newDefault)
    : Printer(app, "debug", "Debug output writer", newDefault) {
    }
    void Debug::beforeComputation() {
        std::cout << "### Computation ###" << std::endl;
    }
    
    void Debug::solverInvocationResult(const htd::vertex_t vertex, const Computation& computation) {
        std::cout << "Node " << vertex << ": " << std::endl;
        computation.print(false);
        std::cout << std::endl;
    }

} // namespace printer
