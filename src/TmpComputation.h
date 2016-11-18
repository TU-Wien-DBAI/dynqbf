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

#include "NSF.h"


#pragma once

class TmpComputation {
public:
    TmpComputation(const std::vector<NTYPE>& quantifierSequence, const BDD& bdd);
    TmpComputation(const TmpComputation& other);
    
    virtual ~TmpComputation();
    
    virtual void apply(std::function<BDD(const BDD&)> f);
    virtual void apply(const BDD& clauses);
    
    virtual void conjunct(const TmpComputation& other);
    
    virtual void remove(const BDD& variable, const unsigned int vl);
    virtual void remove(const std::vector<std::vector<BDD>>& removedVertices);
    virtual void removeApply(const std::vector<std::vector<BDD>>& removedVertices, const BDD& clauses);
    
    virtual const BDD evaluate(Application& app, std::vector<BDD>& cubesAtlevels, bool keepFirstLevel) const;
    bool isUnsat() const;

    virtual void optimize();
    
    const unsigned int maxBDDsize() const;
    const unsigned int leavesCount() const;
    const unsigned int nsfCount() const;

    virtual void print() const;
    
protected:
    NSF* _nsf;    
};