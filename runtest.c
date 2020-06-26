#include <stdio.h>

#define TEST(x) test(x, #x)
#include "myfilesystem.h"

/* You are free to modify any part of this file. The only requirement is that when it is run, all your tests are automatically executed */

/* Some example unit test functions */
int success() {
    return 0;
}

int failure() {
    return 1;
}

int no_operation() {
    void * helper = init_fs("before/01_file_data", "before/01_directory_table", "before/01_hash_data", 4); 
    close_fs(helper);
    return 0;
}

int milestone_delete_file() {
    void * helper = init_fs("before/06_file_data", "before/06_directory_table", "before/06_hash_data", 4); 
    int ret = delete_file("wow.file", helper);
    close_fs(helper);
    return ret;
}

int milestone_read_file() {
    void * helper = init_fs("before/10_file_data", "before/10_directory_table", "before/10_hash_data", 4); char buf[11];
    int ret = read_file("file1.txt", 5, 50, buf, helper);
    ret = read_file("file1.txt", 5, 10, buf, helper);
    close_fs(helper);
    return ret;
}

/****************************/

/* Helper function */
void test(int (*test_function) (), char * function_name) {
    int ret = test_function();
    if (ret == 0) {
        printf("Passed %s\n", function_name);
    } else {
        printf("Failed %s returned %d\n", function_name, ret);
    }
}
/************************/

int main(int argc, char * argv[]) {
    
    // You can use the TEST macro as TEST(x) to run a test function named "x"
    TEST(success);
    TEST(failure);
    TEST(no_operation);

    // Add more tests here
    //TEST(milestone_delete_file);
    printf("\n");
    TEST(milestone_read_file);

    return 0;
}
