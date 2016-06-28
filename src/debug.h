// (c) Copyright 2016 Josh Wright
#pragma once

#include <iostream> // for std::cerr and std::endl
#include <typeinfo> // for typeid(T).name()
#include <cstring> // for strlen() and basename()
#include <cxxabi.h> // for abi::__cxa_demangle()

/*for print_trace()*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/prctl.h>
/*source:
http://stackoverflow.com/questions/4636456/how-to-get-a-stack-trace-for-c-using-gcc-with-line-number-information/4732119#4732119
 */
//void print_trace() {
//    char pid_buf[30];
//    sprintf(pid_buf, "%d", getpid());
//    char name_buf[512];
//    name_buf[readlink("/proc/self/exe", name_buf, 511)]=0;
//    prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);
//    int child_pid = fork();
//    if (!child_pid) {
//        dup2(2,1); // redirect output to stderr
//        fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
//        execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
//        abort(); /* If gdb failed to start */
//    } else {
//        waitpid(child_pid,NULL,0);
//    }
//}



/*use this basename() if your <string.h> doesn't provide one*/
//const char* basename(const char* string) {
//    /*simple basename function which doesn't require dynamically allocating a
//     * second C String*/
//    const char *first = string;
//    const char *last = string + strlen(string);
//    const char *current = last;
//    while (current > first) {
//        if (*(current -1) == '/') {
//            break;
//        }
//        current--;
//    }
//    return current;
//}

template<typename T>
void __debug_log(T v, const char *l, const char *f, int line, bool p) {
    /*debug logger that uses template type resolution to print whatever we give it*/
    std::cerr << basename(f) << ":" << line << " ";
    if (p) {
        /*gcc-specific way to demangle the type names, probably not portable*/
        std::cerr << abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL) <<
        " ";
    }
    std::cerr << l << "=" << v << std::endl;
}

#define debug_log(x) __debug_log(x, #x, __FILE__, __LINE__, true)
#define debug_log_type(x) __debug_log(x, #x, __FILE__, __LINE__, true)
#define debug_log_notype(x) __debug_log(x, #x, __FILE__, __LINE__, false)


void __test(bool expr, const char* expr_str, const std::string &message, const char *file, int line);

#define test(expr, label) __test(expr, #expr, label, __FILE__, __LINE__)
