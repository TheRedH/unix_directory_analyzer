# pragma once

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <array>
#include <map>
#include <limits>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <algorithm>

#define OUT // indicator of out parameters

using namespace std;

struct FileInfo
{
    string name;
    string path;
    uint64_t size;
    string type;
};

struct DirStat
{
    uint64_t file_count;
    uint64_t size;
    array<string, 200> file_types;
    array<int, 200> file_types_count;
    int file_types_size;
    char min_file_size_path[250];
    char max_file_size_path[250];
    uint64_t min_file_size;
    uint64_t max_file_size;
};

struct SharedMemory
{
    DirStat stat;
    int fd;
    string name;
};

struct ThreadData
{
    FileInfo dir;
    DirStat* shared_stat;
    pthread_mutex_t* mutex_lock;
};

FileInfo get_file_info(string path);
DirStat get_dir_stat(const FileInfo& dir);
void* thread_function(void* args);
void get_sub_dirs(const FileInfo& dir_info, OUT vector<FileInfo>& sub_dirs);
void update_dir_stat(const DirStat& from_stat, DirStat& to_stat);  // updates to_stat with from_stat statistics
void print_final_result(const DirStat& stat);
int calculate_full_dir_stat_by_sub_processes(const FileInfo& dir, SharedMemory* shared_mem, sem_t* sem_lock);
int calculate_full_dir_stat_by_threads(const FileInfo& dir, DirStat* process_stat, pthread_mutex_t* mutex_lock);
int process_sub_dirs_by_sub_processes(const vector<FileInfo>& sub_dirs, SharedMemory* shared_mem, sem_t* sem_lock);
int process_sub_dirs_by_threads(const vector<FileInfo>& sub_dirs, DirStat* process_stat, pthread_mutex_t* mutex_lock);
int clean_up_process(DirStat* shm, string shm_name, int shm_fd, sem_t* sem, string sem_name);