//
// Created by Melissa on 04/10/2023.
//

#include "GSet.h"

int GSet::get_id() const {
    return id;
}

bool GSet::is_simple() const {
    return simple;
}

std::pair<GSet, GSet> GSet::get_sets() {
    return std::pair<GSet, GSet>(*set1, *set2);
}

bool GSet::operator==(const GSet &set) const {
    return this->id == set.id;
}

bool GSet::operator!=(const GSet &set) const {
    return this->id != set.id;
}
