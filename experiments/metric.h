#ifndef ophidian_METRIC_H
#define ophidian_METRIC_H

#include <chrono>
#include <papi.h>
#include <string>
#include <fstream>

namespace ophidian
{
namespace experiments
{

class Metric
{
public:
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void print_result() = 0;
    virtual void print_file_result(std::string filename) = 0;
};

class Runtime : public Metric
{
    std::chrono::high_resolution_clock::time_point time_start, time_end;
public:
    void start(){
        time_start = std::chrono::high_resolution_clock::now();
    }

    void end(){
        time_end = std::chrono::high_resolution_clock::now();
    }

    void print_result(){
        auto total_time = time_end - time_start;
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(total_time).count()<<" ms"<<std::endl;
    }

    void print_file_result(std::string filename){
        if(filename == "")
        {
            std::cout << "Output file name error!!" << std::endl;
            return;
        }
        auto total_time = time_end - time_start;
        std::ofstream ofs;
        ofs.open (filename, std::ofstream::out | std::ofstream::app);
        ofs << std::chrono::duration_cast<std::chrono::milliseconds>(total_time).count() << " ms\n";
        ofs.close();
    }
};

class Miss : public Metric
{
    int * PAPI_events;
    unsigned int events_size;
    std::vector<long long> events;
public:
    Miss(int events[], unsigned int events_size) : events_size(events_size){
        PAPI_events = events;
    }

    void start(){
        PAPI_start_counters( PAPI_events, events_size );
    }

    void end(){
        long long counters[events_size];
        PAPI_read_counters( counters, events_size );
        events = std::vector<long long>(counters, counters + sizeof counters / sizeof counters[0]);
    }

    void print_result(){
        for(auto e : events)
            std::cout<<e<<" ";
        std::cout<<std::endl;
    }

    void print_file_result(std::string filename){
        if(filename == "")
        {
            std::cout << "Output file name error!!" << std::endl;
            return;
        }
        std::ofstream ofs;
        ofs.open (filename, std::ofstream::out | std::ofstream::app);
        for(auto e : events)
            ofs << e <<" ";
        ofs << "\n";
        ofs.close();
    }
};

} // namespace experiments
} // namespace ophidian

#endif //ophidian_METRIC_H
