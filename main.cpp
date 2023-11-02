#include <iostream>
#include <iomanip>

#include "Karger.h"
#include "IO.h"
#include "Naive.h"

int main() {
    IO io;
    auto m = io.load_data("test.txt");

    SuperGraph *s = new SuperGraph(m);
    Karger karger(s);
    Naive naive(m);

    int minimal_cut = INT_MAX;
    for (int i = 0; i < 10000; i++) {
        auto e = karger.min_cut();
        if (e.size() < minimal_cut) {
            minimal_cut = e.size();
        }
    }
    int niter = 10000;

    int n_min = 0;
    int k_min = 0;
    for (int k = 0; k < niter; k++) {

        auto e = karger.min_cut();
        if (e.size() == minimal_cut) {
            k_min++;
        }

        auto a = naive.min_cut();
        if (a.size() == minimal_cut) {
            n_min++;
        }
    }

    double kp = static_cast<double>(k_min)/niter;
    std::cout << "Karger: " << k_min << " minimal cuts founded of " << niter;
    std::cout << " iterations, probability: " << kp << std::endl;

    double np = static_cast<double>(n_min)/niter;
    std::cout << "Naive: " << n_min << " minimal cuts founded of " << niter;
    std::cout << " iterations, probability: " << np << std::endl;
}
