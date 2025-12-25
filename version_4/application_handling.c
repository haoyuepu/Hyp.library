#include "common.h"

// 提交申请
void submitApplication(User user) {
    Application app;
    
    printf("\n=== 提交出校申请 ===\n");
    
    // 自动填充学生信息
    strcpy(app.studentName, user.name);
    strcpy(app.studentId, user.id);
    
    // 获取申请信息
    printf("1. 出校时间 (格式: YYYY-MM-DD HH:MM): ");
    getchar(); // 清除缓冲区
    fgets(app.outTime, 50, stdin);
    app.outTime[strcspn(app.outTime, "\n")] = 0;
    
    printf("2. 预计回校时间 (格式: YYYY-MM-DD HH:MM): ");
    fgets(app.returnTime, 50, stdin);
    app.returnTime[strcspn(app.returnTime, "\n")] = 0;
    
    printf("3. 外出原因: ");
    fgets(app.reason, 100, stdin);
    app.reason[strcspn(app.reason, "\n")] = 0;
    
    printf("4. 目的地: ");
    fgets(app.destination, 100, stdin);
    app.destination[strcspn(app.destination, "\n")] = 0;
    
    printf("5. 联系方式（电话号码）: ");
    fgets(app.phone, 20, stdin);
    app.phone[strcspn(app.phone, "\n")] = 0;
    
    // 设置默认状态
    app.status = 0; // 待审批
    strcpy(app.advisorName, "");
    strcpy(app.approvalTime, "");
    
    // 保存申请
    saveApplication(app);
    
    printf("\n申请已提交，待审批\n");
}

// 查看申请记录
void viewApplications(User user) {
    FILE *file = fopen(APPLICATION_FILE, "rb");
    int count = 0;
    
    printf("\n=== 我的申请记录 ===\n");
    
    if (file != NULL) {
        Application app;
        while (fread(&app, sizeof(Application), 1, file)) {
            if (strcmp(app.studentId, user.id) == 0) {
                count++;
                printf("\n申请 #%d\n", count);
                printf("出校时间: %s\n", app.outTime);
                printf("回校时间: %s\n", app.returnTime);
                printf("外出原因: %s\n", app.reason);
                printf("目的地: %s\n", app.destination);
                printf("联系方式: %s\n", app.phone);
                
                printf("状态: ");
                switch (app.status) {
                    case 0: printf("待审批"); break;
                    case 1: printf("已批准"); break;
                    case 2: printf("已拒绝"); break;
                }
                printf("\n");
                
                if (app.status != 0) {
                    printf("审批人: %s\n", app.advisorName);
                    printf("审批时间: %s\n", app.approvalTime);
                }
                printf("-------------------\n");
            }
        }
        fclose(file);
    }
    
    if (count == 0) {
        printf("暂无申请记录。\n");
    } else {
        printf("共 %d 条申请记录。\n", count);
    }
}

// 查看待审批申请
void viewPendingApplications(User user) {
    FILE *file = fopen(APPLICATION_FILE, "rb");
    Application apps[100];
    int count = 0;
    
    printf("\n=== 待审批名单 ===\n");
    
    if (file != NULL) {
        Application app;
        while (fread(&app, sizeof(Application), 1, file)) {
            if (app.status == 0) { // 只显示待审批的
                apps[count] = app;
                count++;
            }
        }
        fclose(file);
    }
    
    if (count == 0) {
        printf("暂无待审批申请。\n");
        return;
    }
    
    // 显示待审批列表
    for (int i = 0; i < count; i++) {
        printf("\n申请 #%d\n", i + 1);
        printf("学生姓名: %s\n", apps[i].studentName);
        printf("学号: %s\n", apps[i].studentId);
        printf("出校时间: %s\n", apps[i].outTime);
        printf("预计回校时间: %s\n", apps[i].returnTime);
        printf("外出原因: %s\n", apps[i].reason);
        printf("目的地: %s\n", apps[i].destination);
        printf("联系方式: %s\n", apps[i].phone);
        printf("-------------------\n");
    }
    
    // 审批选项
    int choice;
    printf("\n请选择要审批的申请编号 (0-返回): ");
    scanf("%d", &choice);
    
    if (choice > 0 && choice <= count) {
        int approval;
        printf("\n审批申请 #%d\n", choice);
        printf("1. 批准\n");
        printf("2. 拒绝\n");
        printf("请选择: ");
        scanf("%d", &approval);
        
        // 更新申请状态
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timeStr[50];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);
        
        apps[choice-1].status = (approval == 1) ? 1 : 2;
        strcpy(apps[choice-1].advisorName, user.name);
        strcpy(apps[choice-1].approvalTime, timeStr);
        
        // 读取所有申请到临时数组
        Application allApps[100];
        int allCount = 0;
        file = fopen(APPLICATION_FILE, "rb");
        if (file != NULL) {
            while (fread(&allApps[allCount], sizeof(Application), 1, file)) {
                allCount++;
            }
            fclose(file);
        }
        
        // 更新对应的申请
        for (int i = 0; i < allCount; i++) {
            if (strcmp(allApps[i].studentId, apps[choice-1].studentId) == 0 &&
                strcmp(allApps[i].outTime, apps[choice-1].outTime) == 0 &&
                allApps[i].status == 0) { // 只更新待审批的
                allApps[i] = apps[choice-1];
            }
        }
        
        // 保存所有申请回文件
        file = fopen(APPLICATION_FILE, "wb");
        if (file != NULL) {
            for (int i = 0; i < allCount; i++) {
                fwrite(&allApps[i], sizeof(Application), 1, file);
            }
            fclose(file);
        }
        
        printf("审批完成！\n");
    }
}

// 查看审批记录
void viewApprovalRecords(User user) {
    FILE *file = fopen(APPLICATION_FILE, "rb");
    int count = 0;
    
    printf("\n=== 我的审批记录 ===\n");
    
    if (file != NULL) {
        Application app;
        while (fread(&app, sizeof(Application), 1, file)) {
            if (strcmp(app.advisorName, user.name) == 0 && app.status != 0) {
                count++;
                printf("\n审批记录 #%d\n", count);
                printf("学生姓名: %s\n", app.studentName);
                printf("学号: %s\n", app.studentId);
                printf("出校时间: %s\n", app.outTime);
                printf("回校时间: %s\n", app.returnTime);
                printf("外出原因: %s\n", app.reason);
                printf("目的地: %s\n", app.destination);
                
                printf("审批结果: ");
                switch (app.status) {
                    case 1: printf("批准"); break;
                    case 2: printf("拒绝"); break;
                }
                printf("\n");
                
                printf("审批时间: %s\n", app.approvalTime);
                printf("-------------------\n");
            }
        }
        fclose(file);
    }
    
    if (count == 0) {
        printf("暂无审批记录。\n");
    } else {
        printf("共 %d 条审批记录。\n", count);
    }
}
