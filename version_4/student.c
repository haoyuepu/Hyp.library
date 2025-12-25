#include "common.h"

// 学生菜单
int studentMenu(User user) {
    int choice;
    
    do {
        printf("\n=== 学生菜单 ===\n");
        printf("1. 提交申请\n");
        printf("2. 查看申请记录（含状态）\n");
        printf("3. 切换账号\n");
        printf("4. 退出程序\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                submitApplication(user);
                break;
            case 2:
                viewApplications(user);
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
