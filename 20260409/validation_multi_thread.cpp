#include <bits/stdc++.h>
using namespace std;

// 快速随机数生成器（线程局部）
thread_local mt19937 tls_gen(random_device{}());
thread_local uniform_int_distribution<> tls_dis(1, 1000);

// 生成测试集
void generate_testset(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = tls_dis(tls_gen);
    }
}

// 选择排序（待测算法）
void select_sort(int* arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        int minindex = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minindex]) {
                minindex = j;
            }
        }
        if(minindex != i) {
            int tmp = arr[i];
            arr[i] = arr[minindex];
            arr[minindex] = tmp;
        }
    }
}

// 基准算法
void stl_sort(int* arr, int n) {
    sort(arr, arr + n);
}

// 比对两个数组
int compare(int* a, int* b, int n) {
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) return 0;
    }
    return 1;
}

// 拷贝数组
void copy_array(int* src, int* dst, int n) {
    memcpy(dst, src, n * sizeof(int));
}

// 单轮测试
int run_single_test(int testscale, int* testset, int* result, int* expected, int* original) {
    // 生成测试数据
    generate_testset(testset, testscale);
    copy_array(testset, original, testscale);
    
    // 待测算法
    copy_array(original, result, testscale);
    select_sort(result, testscale);
    
    // 基准算法
    copy_array(original, expected, testscale);
    stl_sort(expected, testscale);
    
    // 比对
    return compare(result, expected, testscale);
}

// 线程工作函数
void worker_thread(int thread_id, long long start_idx, long long end_idx, 
                   int testscale, atomic<long long>* completed, 
                   atomic<int>* has_error, int* failed_testset, 
                   int* failed_result, int* failed_expected, 
                   int* failed_flag, mutex* result_mutex) {
    
    // 每个线程独立的内存（避免竞争）
    int* testset = new int[testscale];
    int* result = new int[testscale];
    int* expected = new int[testscale];
    int* original = new int[testscale];
    
    for(long long i = start_idx; i < end_idx && !has_error->load(); i++) {
        int passed = run_single_test(testscale, testset, result, expected, original);
        
        if(!passed && !has_error->load()) {
            has_error->store(1);
            lock_guard<mutex> lock(*result_mutex);
            *failed_flag = 1;
            copy_array(original, failed_testset, testscale);
            copy_array(result, failed_result, testscale);
            copy_array(expected, failed_expected, testscale);
            break;
        }
        
        long long done = ++(*completed);
        if(done % 1000 == 0) {
            lock_guard<mutex> lock(*result_mutex);
            cout << "\r进度: " << done << "/" << (start_idx + (end_idx - start_idx)) << flush;
        }
    }
    
    delete[] testset;
    delete[] result;
    delete[] expected;
    delete[] original;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long testscale, testtimes;
    cin >> testscale >> testtimes;
    
    unsigned int num_threads = thread::hardware_concurrency();
    cout << "使用 " << num_threads << " 个线程\n";
    
    // 分配内存
    int* testset = new int[testscale];
    int* result = new int[testscale];
    int* expected = new int[testscale];
    int* original = new int[testscale];
    
    atomic<long long> completed(0);
    atomic<int> has_error(0);
    int failed_flag = 0;
    mutex result_mutex;
    
    // 失败时保存数据的内存
    int* failed_testset = new int[testscale];
    int* failed_result = new int[testscale];
    int* failed_expected = new int[testscale];
    
    auto start_time = chrono::steady_clock::now();
    
    // 创建线程
    vector<thread> threads;
    long long tests_per_thread = testtimes / num_threads;
    
    for(unsigned int t = 0; t < num_threads; t++) {
        long long start_idx = t * tests_per_thread;
        long long end_idx = (t == num_threads - 1) ? testtimes : start_idx + tests_per_thread;
        
        threads.emplace_back(worker_thread, t, start_idx, end_idx, testscale,
                            &completed, &has_error, failed_testset, 
                            failed_result, failed_expected, &failed_flag, &result_mutex);
    }
    
    // 等待所有线程完成
    for(auto& th : threads) {
        th.join();
    }
    
    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    
    // 输出结果
    cout << "\n\n========== 结果 ==========\n";
    if(!has_error.load() && !failed_flag) {
        cout << "✅ 通过！\n";
        cout << "测试次数: " << testtimes << "\n";
        cout << "测试规模: " << testscale << "\n";
        cout << "耗时: " << duration.count() << " ms\n";
        cout << "速度: " << (testtimes * 1000.0 / duration.count()) << " 次/秒\n";
    } else {
        cout << "❌ 失败！\n";
        cout << "\n原始数据（前100个）:\n";
        for(int i = 0; i < min(100, (int)testscale); i++) {
            cout << failed_testset[i] << " ";
        }
        cout << "\n\n你的排序结果（前100个）:\n";
        for(int i = 0; i < min(100, (int)testscale); i++) {
            cout << failed_result[i] << " ";
        }
        cout << "\n\n正确结果（前100个）:\n";
        for(int i = 0; i < min(100, (int)testscale); i++) {
            cout << failed_expected[i] << " ";
        }
        cout << "\n";
    }
    
    // 释放内存
    delete[] testset;
    delete[] result;
    delete[] expected;
    delete[] original;
    delete[] failed_testset;
    delete[] failed_result;
    delete[] failed_expected;
    
    return has_error.load() ? 1 : 0;
}