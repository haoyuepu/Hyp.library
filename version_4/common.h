#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

// 数据结构定义
typedef struct {
    char name[50];
    char id[20];
    char password[20];
    int role; // 0: 学生, 1: 辅导员
} User;

typedef struct {
    char studentName[50];
    char studentId[20];
    char outTime[50];
    char returnTime[50];
    char reason[100];
    char destination[100];
    char phone[20];
    int status; // 0: 待审批, 1: 已批准, 2: 已拒绝
    char advisorName[50];
    char approvalTime[50];
} Application;

// 文件路径常量
#define USER_FILE "D:\\school_management_system\\version_4\\users.dat"
#define APPLICATION_FILE "D:\\school_management_system\\version_4\\applications.dat"

// 函数声明

// 数据管理函数
void initDataFiles();
void generateTestData();
void saveApplication(Application app);

// 用户认证函数
void loginSystem(User *currentUser);

// 菜单函数
int studentMenu(User user);
int advisorMenu(User user);

// 申请处理函数
void submitApplication(User user);
void viewApplications(User user);
void viewPendingApplications(User user);
void viewApprovalRecords(User user);

#endif // COMMON_H
