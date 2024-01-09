#include <algorithm>
#include <iostream>
#include <vector>

std::vector<double> bucket_sort(const std::vector<double>& unsorted_vec){
    std::vector<std::vector<double>> dvec_vec(unsorted_vec.size());

    std::for_each(unsorted_vec.begin(), unsorted_vec.end(), [N = unsorted_vec.size(), &dvec_vec](auto dval)
                  { dvec_vec[static_cast<std::size_t>(N * dval)].push_back(dval); });

    std::for_each(dvec_vec.begin(), dvec_vec.end(), [](auto& elem_dvec)
                   { std::sort(elem_dvec.begin(), elem_dvec.end());});

    std::vector<double> sorted_vec;
    sorted_vec.reserve(unsorted_vec.size());
    std::for_each(dvec_vec.begin(), dvec_vec.end(), [&sorted_vec](const auto& elem_dvec)
                  { std::copy(elem_dvec.begin(), elem_dvec.end(), std::back_inserter(sorted_vec)); });

    return sorted_vec;
}
 
// Driver program to test above function
int main()
{
    std::vector<double> dvec{ 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 };
    auto sorted_vec = bucket_sort(dvec);
 
    std::cout << "Unsorted vector is: ";
    for (auto&& dval: dvec)
        std::cout << dval << " ";

    std::cout <<"\n";\

    std::cout << "Sorted vector is: ";
    for (auto&& dval: sorted_vec)
        std::cout << dval << " ";
}