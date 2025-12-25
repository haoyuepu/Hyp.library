#include "common.h"

// 辅导员菜单
int advisorMenu(User user) {
    int choice;
    
    do {
        printf("\n=== 辅导员菜单 ===\n");
        printf("1. 待审批名单\n");
        printf("2. 审批记录\n");
        printf("3. 切换账号\n");
        printf("4. 退出程序\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                viewPendingApplications(user);
                break;
            case 2:
                viewApprovalRecords(user);
                break;
            case 3:
                printf("切换账号...\n");
                return 1; // 返回1表示切换账号
            case 4:
                printf("退出程序...\n");
                return 2; // 返回2表示退出程序
            default:
                printf("无效选择！\n");
        }
    } while (choice != 3 && choice != 4);
    
    return 0; // 正常情况下不会执行到这里
}
