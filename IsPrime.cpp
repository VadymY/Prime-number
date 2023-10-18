// IsPrime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <string>

using namespace std;

bool isPrimeMulti(unsigned long long number)
{
    auto isPrime = [&]() {
        bool response = true;
        if (number > 1)
        {
            //const unsigned long long limit = number / 2;
            const unsigned long long limit = sqrt(static_cast<double>(number + 1ull));
            for (unsigned long long i = 2; i <= limit; ++i) {
                if (number % i == 0) {
                    response = false;
                    break;
                }
            }
        }
        else
        {
            response = false;
        }

        return response;
    };


    int core_count = thread::hardware_concurrency();

    unsigned long long thread_count_max = number / 1000;
    unsigned int real_thread_count = 2;
    if (thread_count_max == 0u)
    {
        real_thread_count = 0u;
    }
    else
    {
        real_thread_count = (thread_count_max > core_count) ? 16u : core_count * 2;
    }

    atomic<bool> ret_code = true;

    auto checkPrime = [&](const unsigned long long& shift, const unsigned long long& block) {
        if (number > 1)
        {
            unsigned long long shift_loc = (shift < 2) ? 2u : shift;
            const unsigned long long limit = shift + block;
            for (unsigned long long i = shift_loc; i < limit; ++i) {
                if (ret_code) {
                    if (number % i == 0) {
                        ret_code = false;
                        return;
                    }
                }
                else
                {
                    return;
                }
            }
        }
        else
        {
            ret_code = false;
        }
    };


    if (real_thread_count < 2u)
    {
        return isPrime();
    }

    //unsigned long long number_limit = number / 2;
    const unsigned long long number_limit = sqrt(static_cast<double>(number + 1ull));
    unsigned long long main_block = number_limit / real_thread_count;
    unsigned long long last_block = main_block;
    bool isLast = true;
    if (real_thread_count * main_block != number_limit)
    {
        main_block = number_limit / (real_thread_count + 1ul);
        last_block = number_limit - (real_thread_count + 1ul) * main_block;
        if (last_block == 0)
        {
            ++real_thread_count;
            isLast = false;
        }
    }

    vector<thread> vec_thread(real_thread_count);
    vector<unsigned int> vec_blocks(real_thread_count, main_block);
    if (isLast) {
        vec_blocks.back() = last_block;
    }
    unsigned int shift = 0;
    for (unsigned int i = 0; i < real_thread_count; ++i)
    {
        vec_thread.emplace_back(thread(checkPrime, shift, vec_blocks[i]));
        shift += vec_blocks[i];
    }

    for (auto& item : vec_thread)
    {
        if (item.joinable())
        {
            item.join();
        }
    }

    return ret_code;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        char* pEnd;
        unsigned long long number = strtoull(argv[1], &pEnd, 10);
        if (string(argv[1]) == to_string(number))
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            bool res = isPrimeMulti(number); 
            auto t2 = std::chrono::high_resolution_clock::now();
            cout << boolalpha;
            cout << "number = " << number << ", is prime = " << res << ", time (mS) = " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }
        else
        {
            cout << "number = " << argv[1] << " is overflow or negative" << endl;
        }
    }
}
