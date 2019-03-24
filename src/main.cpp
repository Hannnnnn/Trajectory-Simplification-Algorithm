#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include "../inc/trajectory.hpp"
#include "../inc/dp.hpp"
#pragma comment(linker, "/STACK:1024000000,1024000000") 

Trajectory<Point> traj;

int main(int argc,char *argv[]){
    if(argc == 1){
        return 0;
    }

    double error_bound = std::stod(argv[1]);
    DP dp{error_bound};

    double tx,ty,tt;
    double averge_rate,temp_rate;

    double start_time = clock();

    for(int i = 0 ; i < 101; i++){

        std::string file_name = "../dataset/taxi_clean/A000" + std::to_string(i);
        freopen(file_name.c_str(),"r",stdin);

        while(scanf("%lf %lf %lf",&tt,&ty,&tx) == 3){
            traj.push(Point{tx,ty,tt});
        }

        std::cout << "Running on No." << i << " trajectory..." << std::endl;
        std::cout << "Trajectory size:" << traj.size() << std::endl;

        auto result = dp.compress(traj,0,traj.size() - 1);
        temp_rate = (double) (traj.size() - result.size())/ traj.size();
        averge_rate += temp_rate;

        std::cout << "Compressed trajectory size:" << result.size() << std::endl;
        std::cout << "Compression rate:" << temp_rate << std::endl;
        
        fclose(stdin);
    
    }

    double end_time = clock();

    averge_rate /= 101;
    freopen("result.txt","w",stdout);
    std::cout << "Error Bound: " << error_bound << "m" << std::endl;
    std::cout << "Average Compression Ratio: " << averge_rate * 100 << "\%" << std::endl;
    std::cout << "Running time " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s"<< std::endl;

    fclose(stdout);
    
    return 0;
}