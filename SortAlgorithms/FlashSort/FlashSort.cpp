#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> flashSort(std::vector<int> unsorted_vec){
    const std::size_t m = static_cast<std::size_t>(0.45 * unsorted_vec.size());
    auto [min_it, max_it] = std::minmax_element(unsorted_vec.begin(), unsorted_vec.end());

    if (*min_it == *max_it) return unsorted_vec;
    

    double c1 = static_cast<double>(m - 1) / (*max_it - *min_it);

    std::vector<int> l(m, 0);
    for (std::size_t j{}; j < unsorted_vec.size(); ++j) 
        ++l[static_cast<std::size_t>(c1 * (unsorted_vec[j] - *min_it))];


    for (std::size_t p{1}; p < m; ++p)
        l[p] += l[p - 1];
    

    std::iter_swap(max_it, unsorted_vec.begin());

    int t, flash, j{}, k = m - 1, hold;

    for(std::size_t move{}; move < unsorted_vec.size() - 1; ) {
        while (j > l[k] - 1) {
            ++j;
            k = static_cast<int>(c1 * (unsorted_vec[j] - *min_it));
        }

        if (k < 0)
            break;

        flash = unsorted_vec[j];
        while (j != l[k]) {
            k = static_cast<int>(c1 * (flash - *min_it));
            hold = unsorted_vec[(t = --l[k])];
            unsorted_vec[t] = flash;
            flash = hold;
            ++move;
        }
    }

    for (j = 1; j < unsorted_vec.size(); ++j) {
        hold = unsorted_vec[j];
        int i = j - 1;
        while (i >= 0 && unsorted_vec[i] > hold) {
            unsorted_vec[i + 1] = unsorted_vec[i];
            --i;
        }
        unsorted_vec[i + 1] = hold;
    }
    return unsorted_vec;
}

int main() {
    std::vector<int> ivec{23, 1, 45, 6, 3, 8};
    std::vector<int> sorted_vec = flashSort(ivec);
    std::cout<< "The sorted vector is: ";
    for (auto&& ival: sorted_vec) {
        std::cout << ival << " ";
    }
}