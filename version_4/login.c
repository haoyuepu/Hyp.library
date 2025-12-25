#include "common.h"

// 登录系统
void loginSystem(User *currentUser) {
    char id[20], password[20];
    int found = 0;
    FILE *file;
    
    while (!found) {
        printf("\n=== 登录 ===\n");
        printf("学工号: ");
        scanf("%s", id);
        printf("登录密码: ");
        scanf("%s", password);
        
        // 验证用户
        file = fopen(USER_FILE, "rb");
        if (file != NULL) {
            User user;
            while (fread(&user, sizeof(User), 1, file)) {
                if (strcmp(user.id, id) == 0 &&
                    strcmp(user.password, password) == 0) {
                    *currentUser = user;
                    found = 1;
                    break;
                }
            }
            fclose(file);
        }
        
        if (!found) {
            printf("登录失败！请检查学工号和密码。\n");
        }
    }
    
    printf("\n登录成功！欢迎 %s (%s)\n", currentUser->name, 
           currentUser->role == 0 ? "学生" : "辅导员");
}
