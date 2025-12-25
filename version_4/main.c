#include "common.h"

// 主函数
int main() {
    User currentUser;
    int menuResult;
    
    // 设置控制台编码为UTF-8（解决中文乱码问题）
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001); // 设置输入编码也为UTF-8
#endif
    
    printf("=== 进出校审核管理系统 ===\n\n");
    
    // 初始化数据文件
    initDataFiles();
    
    // 生成测试数据（如果文件为空）
    generateTestData();
    
    do {
        // 登录系统
        loginSystem(&currentUser);
        
        // 根据角色显示菜单
        if (currentUser.role == 0) {
            menuResult = studentMenu(currentUser);
        } else {
            menuResult = advisorMenu(currentUser);
        }
        
        // 根据菜单返回值决定下一步操作
        if (menuResult == 1) {
            printf("\n重新登录...\n");
        } else if (menuResult == 2) {
            printf("\n退出系统...\n");
            break;
        }
    } while (menuResult == 1); // 如果返回1（切换账号），则重新登录
    
    printf("\n感谢使用进出校审核管理系统！\n");
    return 0;
}
