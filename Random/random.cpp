#include"mrandom.h"

int main(){

    std::cout<< "What do you want to print on the screen?\n";
    std::cout<< "1) Random Integer Values\n2) Random Floating Values\n3) Uniform Distribution Bell Curve\n4) Random Integer Values Between Boundaries\n5) Shuffle a Vector\n6) Shuffle a String\n7) Roll a Dice\n";
    int chosen{};
    std::cin>>chosen;

    switch (chosen)
    {
    case 1:
    {
        std::cout<<"How many random integer numbers will be produced: "; size_t N; std::cin>>N;
        mRand::genNRandInteger(N);
        break;
    }
    case 2:
    {
        std::cout<<"How many random floating numbers will be produced: "; size_t N; std::cin>>N;
        mRand::genNRandFloating(N);
        break;
    }
    case 3:
    {
        std::cout<<"Enter mean and sdev: "; 
        double mn, sdev; 
        std::cin>>mn>>sdev;
        mRand::normalDistCalc(mn, sdev);
        break;
    }
    case 4:
    {
        std::cout<<"how many random integer numbers will be produced: "; size_t N{}; std::cin>>N;
        std::cout<<'\n';
        std::cout<<"Enter Boundaries (Make sure that first element is smaller than second one.): "; size_t B{}, E{}; std::cin>>B>>E;
        try{
            mRand::genNRandInteger(N, B, E);
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<'\n';
        }
        break;
    }
    case 5:
    {
        std::vector<int> ivec{ 0, 2, 4, 6, 8, 10, 12, 14};
        mRand::ShuffleVector(ivec);
        break;
    }
    case 6:
    {
        std::string alphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
        mRand::ShuffleString(alphabet);
        break;
    }
    case 7:
    {
        std::cout<<"Enter how many times the dice will be rolled : "; size_t N; std::cin>>N;
        mRand::rollDice(N);
        break;
    }
    
    default:
        std::cout<<"Undefined Option.\n";
        break;
    }
}



