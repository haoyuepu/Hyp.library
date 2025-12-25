#include "common.h"

// 初始化数据文件
void initDataFiles() {
    FILE *file;
    
    // 检查用户文件是否存在
    file = fopen(USER_FILE, "rb");
    if (file == NULL) {
        // 创建新文件
        file = fopen(USER_FILE, "wb");
        if (file != NULL) {
            fclose(file);
        }
    } else {
        fclose(file);
    }
    
    // 检查申请文件是否存在
    file = fopen(APPLICATION_FILE, "rb");
    if (file == NULL) {
        // 创建新文件
        file = fopen(APPLICATION_FILE, "wb");
        if (file != NULL) {
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

// 生成测试数据
void generateTestData() {
    FILE *file = fopen(USER_FILE, "rb");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        if (ftell(file) > 0) {
            fclose(file);
            return; // 文件已有数据，不生成测试数据
        }
        fclose(file);
    }
    
    printf("正在生成测试数据...\n");
    
    // 创建测试用户
    User testUsers[5] = {
        {"张三", "2021001", "123456", 0},
        {"李四", "2021002", "123456", 0},
        {"王五", "2021003", "123456", 0},
        {"赵老师", "T001", "admin123", 1},
        {"钱老师", "T002", "admin123", 1}
    };
    
    // 保存测试用户
    file = fopen(USER_FILE, "ab");
    if (file != NULL) {
        for (int i = 0; i < 5; i++) {
            fwrite(&testUsers[i], sizeof(User), 1, file);
        }
        fclose(file);
    }
    
    printf("测试数据生成完成！\n");
}

// 保存申请
void saveApplication(Application app) {
    FILE *file = fopen(APPLICATION_FILE, "ab");
    if (file != NULL) {
        size_t result = fwrite(&app, sizeof(Application), 1, file);
        fclose(file);
        
        if (result == 1) {
            // 移除文件保存路径的显示
        } else {
            printf("警告：申请保存可能不完整！\n");
        }
    } else {
        printf("错误：无法打开文件 %s 进行保存！\n", APPLICATION_FILE);
    }
}
